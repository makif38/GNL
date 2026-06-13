*This project has been created as part of the 42 curriculum by akkaraka.*
---
# get_next_line
## Description
`get_next_line` is a C function that reads and returns one line at a time from a file descriptor. Repeated calls return successive lines; it returns `NULL` on EOF or error.
```c
char *get_next_line(int fd);
```
The project focuses on two key concepts: **static variables** to persist state between calls, and **low-level I/O** via `read()`. The `BUFFER_SIZE` macro, set at compile time, controls how many bytes are read per `read()` call.
---
## Algorithm
`read()` delivers fixed-size chunks; the caller wants one `\n`-terminated line. These boundaries rarely align, so leftover bytes must survive between calls.
A `static char rest` inside the function holds unprocessed bytes from the previous call. Each invocation appends new `read()` chunks to the rest until a `\n` is found, extracts and returns the line, then trims the rest to whatever remains. On EOF with an empty rest, it returns `NULL`.
A static array was chosen to avoid heap allocation for the leftover buffer, eliminating any risk of memory leaks from the persistent state. The line itself is built dynamically with `ft_strjoin` to support lines of any length regardless of `BUFFER_SIZE`.
### Bonus
The bonus extends `get_next_line` to handle multiple file descriptors simultaneously. Instead of a single static buffer, a `static char rest[MAX_FD][BUFFER_SIZE + 1]` array is used, giving each file descriptor its own independent leftover buffer. This allows interleaved reads across different file descriptors without losing state.
---
## Instructions
```bash
# Mandatory
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -g

# Bonus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -g
```
Files to submit:
- Mandatory: `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`
- Bonus: `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`
---
## Usage Example
### Mandatory
```c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
    int     fd;
    int     i;
    char    *line;

    i = 1;
    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d for fd %d: %s\n", i, fd, line);
        free(line);
        i++;
    }
    close(fd);
}
```
### Bonus — Multiple File Descriptors
```c
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>
int main(void)
{
    int     fd1;
    int     fd2;
    int     fd3;
    char    *line;

    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);
    fd3 = open("test3.txt", O_RDONLY);
    line = get_next_line(fd1); printf("fd1: %s\n", line); free(line);
    line = get_next_line(fd2); printf("fd2: %s\n", line); free(line);
    line = get_next_line(fd3); printf("fd3: %s\n", line); free(line);
    line = get_next_line(fd1); printf("fd1: %s\n", line); free(line);
    line = get_next_line(fd2); printf("fd2: %s\n", line); free(line);
    line = get_next_line(fd3); printf("fd3: %s\n", line); free(line);
    close(fd1);
    close(fd2);
    close(fd3);
}
```
---
## Resources
- [man read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [man open(2)](https://man7.org/linux/man-pages/man2/open.2.html)

**AI usage:** Claude (Anthropic) was used to clarify how `static` variables persist between calls, discuss edge cases (`BUFFER_SIZE=1`, empty files, no trailing newline), fixing memory leaks, and designing the multi-fd bonus approach. The implementation code was written by hand.