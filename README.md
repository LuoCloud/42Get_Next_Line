*This project has been created as part of the 42 curriculum by wli-ting.*

# get_next_line

## Description

`get_next_line` is a C function that reads a text file (or any file descriptor) and returns its content **one line at a time**, on each successive call, without ever needing to know the size of the file in advance.

The core challenge of the project is that the `read()` system call does not know or care about lines — it only knows how to pull a fixed number of bytes off a file descriptor. A line can be shorter than that chunk, longer than it, or span across several chunks. So the function has to:

- Read the file in fixed-size chunks (`BUFFER_SIZE`, configurable at compile time).
- Keep the "leftover" data from a chunk that doesn't end exactly at a newline, so it isn't lost between calls.
- Detect when a full line (ending in `\n` or at end-of-file) has been assembled, and hand only that portion back to the caller.
- Remember its position between calls, since it's called repeatedly on the same fd until the file is exhausted.

The mandatory part supports reading from a single file descriptor at a time. The **bonus** part extends this to handle several file descriptors in parallel (e.g. reading line-by-line from two different files interleaved) without mixing up their contents.

## Instructions

### Compiling

The project follows the standard 42 Makefile-less exercise format — you compile the sources directly with `BUFFER_SIZE` and `DELIMITER` passed in as macros:

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

For the bonus version:

```
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

`BUFFER_SIZE` can be set to any positive value to test the function's robustness (very small values stress-test the leftover/join logic, very large values test performance on big files).

### Usage

Include `get_next_line.h` (or `get_next_line_bonus.h`), open a file descriptor, and call `get_next_line(fd)` in a loop. Each call returns:

- A newly allocated string containing the next line (including the trailing `\n` if one was present in the file), or
- `NULL` once there is nothing left to read, or if an error occurs.

Example loop pattern:

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    // use the line
    free(line);
}
close(fd);
```

The caller is responsible for freeing each returned line.

## Algorithm — explanation and justification

The implementation is built around a **static buffer that persists between calls**, plus three cooperating helper steps:

1. **Accumulate (`read_buffer`)** — Every call to `get_next_line` reuses a `static` variable that holds whatever was read on previous calls but not yet returned. As long as no newline has been found yet, the function keeps calling `read()` and appending each newly read chunk onto this stash with a join operation. This continues until either a `\n` shows up in the accumulated buffer, `read()` returns 0 (end of file), or it returns -1 (error).

2. **Extract the line (`get_buffer`)** — Once the stash contains at least one full line, this step scans it for the delimiter and copies everything up to and including it (or up to the end of the string, if EOF was reached with no trailing newline) into a new string. That string is what gets returned to the caller.

3. **Save the remainder (`get_leftover`)** — Whatever comes *after* the extracted line in the stash is not needed yet, so it's copied into a fresh string and stored back into the static buffer for the next call to pick up where this one left off. The old buffer is freed to avoid leaks.

**Why a static variable?** The function has no other way to "remember" its place between separate calls — C functions don't retain state on their own. A static local variable is the standard, minimal-overhead way to persist that leftover data across calls without exposing it to the caller or relying on global variables.

**Why read in chunks of `BUFFER_SIZE` instead of one byte at a time or the whole file at once?** Reading one byte at a time would mean one system call per character, which is extremely slow — system calls are expensive relative to memory operations. Reading the entire file in one shot defeats the purpose of the exercise (handling arbitrarily large files without loading them entirely into memory) and would fail or waste memory on very large inputs. A fixed-size buffer strikes the balance: a small, constant number of system calls relative to file size, and a memory footprint that doesn't scale with file size.

**Why free and reallocate the stash on every join instead of growing it in place?** This keeps the memory-management logic simple and leak-free: at any point there is exactly one heap allocation representing "everything read so far," and each join operation cleanly replaces it. This trades a bit of performance (repeated copying) for a much lower risk of memory bugs, which fits the constraints of the exercise (no `realloc`-based dynamic array is required).

**Bonus: multiple file descriptors.** The single-fd version uses one static `char *`. To support several file descriptors independently, the bonus version instead uses a **static array of buffers**, indexed by the file descriptor number. This way, each fd keeps its own leftover data completely separate from the others, so interleaved reads (e.g. alternating `get_next_line(fd1)` and `get_next_line(fd2)`) don't corrupt each other's state. The rest of the algorithm (accumulate → extract → save leftover) is identical; only the storage is made per-fd instead of global.

## Resources

- [Linux man page — `read(2)`](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux man page — `open(2)`](https://man7.org/linux/man-pages/man2/open.2.html)
- 42 School subject PDF for `get_next_line`
- General C references on static variables and their scope/lifetime (e.g. cppreference, K&R *The C Programming Language*)

**Use of AI:** An AI assistant (Claude) was used to help structure and phrase this README file — organizing the Description, Instructions, and Algorithm-explanation sections, and putting the reasoning behind the design choices (static buffer, chunked reads, per-fd storage for the bonus) into clear prose. The AI was not used to write the `get_next_line` implementation itself; the source code and the underlying algorithmic decisions are the author's own.
