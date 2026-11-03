*This project has been created as part of the 42 curriculum by amradwan.*

# get_next_line

## Description

`get_next_line` is a C function that reads a file descriptor and returns **one line per call**, including the terminating `\n` when there is one. Calling it in a loop reads the whole file (or stdin) line by line until it returns `NULL`.

The goal of the project is to learn about:

- **Static variables**: keeping state between function calls.
- **File descriptors and the `read` system call**.
- **Dynamic memory management**: no leaks, and every allocation failure handled.

Prototype:

```c
char *get_next_line(int fd);
```

Return value:

| Case | Returns |
|------|---------|
| A line was read | The line, ending with `\n` (the last line may not have one) |
| End of file reached, nothing left | `NULL` |
| Error (`read` failure, `malloc` failure, invalid `fd`) | `NULL` |

Files:

- `get_next_line.c`: the main function.
- `get_next_line_utils.c`: helper functions (`ft_strlen`, `ft_strjoin`,`ft_substr`).
- `get_next_line.h`: prototypes and the `BUFFER_SIZE` default.
- `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`: the bonus version (several file descriptors at once, see [Bonus](#bonus)).

## Instructions

### Compilation

`BUFFER_SIZE` is defined at compile time with the `-D` flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

Any positive value works (e.g. `1`, `42`, `9999`, `10000000`).

### Usage

Include the header and call the function in a loop:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

To read from standard input, use `fd = 0`.

### Bonus compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

### Memory check

```bash
valgrind --leak-check=full ./gnl
```

## Algorithm

The core idea: **`read` returns fixed-size chunks that don't match line boundaries, so we need somewhere to keep the extra data between calls.** That place is a `static char *` (called `temp`), which keeps its value after the function returns.

Each call to `get_next_line` does this:

1. **Validate input.** If `BUFFER_SIZE <= 0` or `fd < 0`, return `NULL`.
2. **Read and accumulate.** Allocate a temporary buffer of `BUFFER_SIZE + 1` bytes. Read a chunk with `read`, null-terminate it, and append it to `temp` using `ft_strjoin`. After each append, check with `ft_strchr` whether `temp` now contains a `\n`. Stop as soon as it does, or when `read` returns `0` (end of file). If `read` returns `-1`, free everything and return `NULL`.
3. **Check for end of file.** If `temp` is `NULL` or empty, there is nothing left to return, so return `NULL`.
4. **Extract the line.** Scan `temp` up to and including the first `\n` (or up to the end of the string if there is none), and copy that part into a newly allocated string. This is the value returned to the caller.
5. **Keep the remainder.** Use `ft_substr` to build a new `temp` containing everything after the extracted line, then free the old one. If nothing remains, free `temp` and set it to `NULL`, so the next call starts clean.
6. **Free the read buffer** and return the line.

### Why this design

- **A static variable** is the simplest way to persist the leftover data between calls without global variables (which are forbidden).
- **Looping until a `\n` is found** guarantees correctness for any `BUFFER_SIZE`: if the buffer is smaller than the line, we keep reading; if it is larger, the extra data stays in `temp` for the next call.
- **Joining into a new string** (instead of resizing in place) keeps the helpers simple and reusable, at the cost of copying the accumulated data on every read.
- **Setting `temp` to `NULL` after freeing it** avoids dangling pointers and double frees, since `temp` survives between calls.
- **Every allocation is checked.** On any failure (`malloc` or `read`), everything allocated is freed and `NULL` is returned, so the function never leaks.

### Complexity

Reading a line of length `L` with a buffer of size `B` takes about `L / B` reads. Since each `ft_strjoin` copies the accumulated string, the cost for very long lines (with a small `BUFFER_SIZE`) grows quadratically with the number of reads. For normal line lengths this is negligible, and it is the trade-off for a simple and safe implementation.

## Bonus

The bonus version can read from **several file descriptors at the same time**, using **only one static variable**. You can call it for fd 3, then fd 4, then fd 5, then fd 3 again, and each file descriptor continues exactly from where it stopped, without mixing lines between files.

```c
line = get_next_line(fd3);   /* first line of file 3 */
line = get_next_line(fd4);   /* first line of file 4 */
line = get_next_line(fd3);   /* second line of file 3 */
```

### Bonus algorithm

The reading logic is exactly the same as in the mandatory part. The only change is **where the leftover data is stored**:

- Mandatory: `static char *temp;`, one leftover string for the whole program.
- Bonus: `static char *temp[1024];`, one leftover string **per file descriptor**, and each call works on `temp[fd]`.

Each call to `get_next_line(fd)` only reads, extracts and updates `temp[fd]`, so the leftover of one file descriptor is never touched by a call on another one. The array is a single static variable, so the "only one static variable" rule is respected. If a file descriptor is negative or does not fit in the array, the function returns `NULL`.

### Why an array

- **Direct access:** `temp[fd]` finds the state of any file descriptor immediately, with no searching.
- **Simple memory management:** no nodes to create, search or delete. When a file is finished, `temp[fd]` is freed and set to `NULL`, like in the mandatory part.
- **Trade-off:** the number of file descriptors is limited by the array size (1024 is the usual default limit of open files per process), and the array uses a fixed amount of static memory (about 8 KB on a 64-bit system) even if only one file is read. A linked list would remove this limit, but it needs more code and more memory handling.

## Resources

- `man 2 read`: behavior of the `read` system call and its return values.
- `man 3 malloc` / `man 3 free`: dynamic memory allocation.
- `man 1 valgrind` and the [Valgrind documentation](https://valgrind.org/docs/manual/manual.html): detecting memory leaks and invalid accesses.
- [Static variables in C (GeeksforGeeks)](https://www.geeksforgeeks.org/static-variables-in-c/): how `static` keeps state between calls.
- [File descriptors (Wikipedia)](https://en.wikipedia.org/wiki/File_descriptor).

### Use of AI

AI (Claude) was used as a helper, not to write the project:

- **Understanding the subject:** explaining what the project requires and what each function does.
- **Code review:** pointing out possible memory leaks and unhandled failures of `read`, `malloc`, `ft_strjoin` and `ft_substr`, and explaining why `temp` must be set to `NULL` after being freed.
- **Refactoring advice:** suggesting how to split the main function into smaller ones.
- **Bonus design:** discussing the options to keep one reading state per file descriptor (array or linked list).
- **Documentation:** drafting this README.

All the code was written, tested and understood by the author.