_This project has been created as part of the 42 curriculum by vsack_

## Description:

The project getnextline is a function that efficently reads any file line by line programmed in C.

The whole projects includes 3 files one header file one file for utils and one with the main gnl code.<br>
The utils include modified functions from libft such as:

`ft_strdup`<br>
`ft_strjoin`<br>
`ft_strchr`<br>
`ft_strlen`<br>
`ft_substr`<br>

**The main gnl code is these 4 functions:**

### get_next_line<br>
The primary entry point. It validates the file descriptor and `BUFFER_SIZE`. It allocates a temporary read buffer and checks the static `stash` variable. If the `stash` does not contain a newline, it calls `read_and_stash` to accumulate data. Once data is available, it orchestrates the extraction of the line, updates the static variable, frees the temporary buffer, and returns the final string.
### read_and_stash
Handles the system `read` calls. It reads data from the file descriptor in chunks defined by `BUFFER_SIZE`. The read characters are appended to the existing `stash` variable using ft_strjoin. The loop continues until a newline character \n is detected in the buffer, the read returns `0` (EOF), or an error occurs.
### extract_line
Parses the accumulated data. It calculates the length of the string inside `stash` up to and including the first newline character (or the end of the string if EOF is reached). It allocates the exact memory required for this segment, copies the characters over, null-terminates the string, and returns it.
### update_stash
Manages the static state for subsequent calls. It determines the length of the data remaining in `stash` after the extracted line. It allocates a new memory block for these remaining characters, copies them into the new block, frees the old `stash` to prevent memory leaks, and returns the updated pointer to be stored statically.

## Why this solution

The reason i used this alorithm has a few reasons.<br>
#### 1. Dynamic Buffer Management
The buffer is dynamically allocated and freed with a single call go `get_next_line` which minimizes persistent memory footprint.Freeing the buffer immediately after the read loop ensures no unnecessary memory is held when the function is idle.
#### 2. State Preservation and Cleanup
The stash is updated with destructive reallocation in update_stash and freed if `read()` return `-1`. This overwriting of static pointer prevents data corruption. And explicitly freeing the stash on a -1 read error guarantees memory safety and prevents leaks if a file descriptor becomes invalid mid-read.
#### 3. Early Return
The guard clause `if (fd < 0 || BUFFER_SIZE <= 0)` is evaluated prior to any variable allocation. This prevents `malloc` calls that would immediately be freed which saves CPU cycles and safeguards `read()` from processing invalid file descriptors
#### 4. Iterative Concatenation
The accumulator loop dynamically resizes the `stash` using `ft_strjoin` and continuous reallocation.
Because the total lenght of lines is unknown and dictated by the location of `\n` or EOF dynamically concatenating strings is the most reasonable method to process lines exceeding `BUFFER_SIZE` in my opinion. Reassingning the pointer `stash = ptr` handles the state extension safely.
## Instructions:
To use gnl just git clone this repo and compile with the command:

	cc main.c get_next_line.c get_next_line_utils.c
Then just type the command
	
	./a.out yourfile.example
To configure the Buffer size append this to the compilation command where n is the buffer size

	-D BUFFER_SIZE=n


## Resources:

Most of the research was done in the manual to see how the read function really works. Also asking peers was helpful for understanding memory leaks and other bugs.<br>
What was of great help was this website: https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line which included a great youtube video on the topic of get next line.<br>
The use of AI was minimized. While I did use Gemini i did not use it to create code but to understand difficult concepts and deepen understanding.

**Tester used:**<br>
https://github.com/xicodomingues/francinette