## Code Flow Diagram

### Start
- The program begins execution.

### `get_next_line(fd)`
- Main entry point of the program.
- Reads the next line from the file descriptor `fd`.

### `make_list(&list, fd)`
- Reads data from the file descriptor into a buffer until a newline character is encountered.
- Adds the buffer content into the linked list `list`.
- Continues reading until a newline character is found in the data.

### While not `new_line(list)`
- Checks if there is a newline character in the content of any node in the list.

### Read data from `fd` into buffer
- Continues reading data from the file descriptor into the buffer.

### Add buffer content to list
- Appends the buffer content to the linked list.

### Check if newline in list
- Determines if a newline character is found in the list's content.

### End While
- Loop ends when a newline character is found in the list's content.

### `get_line(list)`
- Calculates the length of the next line.
- Copies the content of the list until a newline character is encountered into a new string.
- Returns the new string.

### `clear_list(&list)`
- Extracts the last incomplete line from the list.
- Releases memory allocated for the list.
- Prepares for the next call to `get_next_line`.

### `release(&list, clean, buffer)`
- Releases memory allocated for the list.
- If `clean->content[0]` is not empty, assigns `clean` to the list. Otherwise, frees `clean` and `buffer`.

### End
- The program ends execution.
