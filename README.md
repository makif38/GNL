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

A `static char *stash` inside the function holds unprocessed bytes from the previous call. Each invocation appends new `read()` chunks to the stash until a `\n` is found, extracts and returns the line, then trims the stash to whatever remains. On EOF with an empty stash, it frees the stash and returns `NULL`.

A single string was chosen over a linked list because it is the minimal structure for this problem — it stores exactly the bytes not yet delivered to the caller, nothing more. It is correct for any `BUFFER_SIZE` value since the stash absorbs the mismatch between chunk size and line length.

---

## Instructions

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

Files to submit: `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`

**Bonus** (multiple file descriptors simultaneously):

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
```

---

## Usage Example

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## Resources

- [man read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [man open(2)](https://man7.org/linux/man-pages/man2/open.2.html)
- [Static storage duration – cppreference](https://en.cppreference.com/w/c/language/storage_duration)
- [Norminette](https://github.com/42School/norminette)

**AI usage:** Claude (Anthropic) was used to clarify how `static` variables persist between calls, discuss edge cases (`BUFFER_SIZE=1`, empty files, no trailing newline). The implementation code was written by hand.