### Overview

This repository provides an efficient and reusable implementation of the `get_next_line` function in C, which reads lines from a file descriptor (`fd`) one at a time. It handles reading data from the file descriptor in chunks defined by `BUFFER_SIZE`, ensuring proper memory management and efficient line retrieval.

### Functions Overview

1. **`get_next_line`**
   - Reads the next line from the file descriptor.
   - **Parameters**:
     - `fd`: File descriptor from which to read.
   - **Returns**:
     - Pointer to the next line read from the file.
   - **Flow**:
     - Checks for invalid file descriptors or buffer sizes.
     - Reads data from the file descriptor in chunks and stores it in a linked list.
     - Retrieves the next line from the linked list and returns it.
     - Clears the linked list after retrieving the line.

2. **`make_list`**
   - Reads data from the file descriptor and stores it in a linked list.
   - **Parameters**:
     - `list`: Pointer to the linked list.
     - `fd`: File descriptor from which to read.
   - **Flow**:
     - Reads data from the file descriptor in chunks and adds it to the linked list until a newline is encountered.

3. **`add_list`**
   - Adds a new node to the linked list.
   - **Parameters**:
     - `list`: Pointer to the linked list.
     - `buffer`: Data to be stored in the new node.
   - **Flow**:
     - Allocates memory for a new node and adds it to the end of the linked list.

4. **`give_line`**
   - Retrieves the next line from the linked list.
   - **Parameters**:
     - `list`: Pointer to the linked list.
   - **Returns**:
     - Pointer to the next line.
   - **Flow**:
     - Allocates memory for the next line and copies it from the linked list.

5. **`clear_list`**
   - Clears the linked list after retrieving the line.
   - **Parameters**:
     - `list`: Pointer to the linked list.
   - **Flow**:
     - Extracts the remaining data in the last node of the list and updates the list accordingly.

6. **`release`**
   - Releases memory used by the linked list.
   - **Parameters**:
     - `list`: Pointer to the linked list.
     - `clean`: Pointer to a temporary list node.
     - `buffer`: Temporary buffer for data extraction.
   - **Flow**:
     - Frees memory used by the linked list nodes and handles special cases where the last node may need partial retention.

7. **`len_new_line`**
   - Calculates the length of the next line.
   - **Parameters**:
     - `list`: Pointer to the linked list.
   - **Returns**:
     - Length of the next line.
   - **Flow**:
     - Iterates through the linked list to find the newline character and calculates the length of the line.

8. **`copy_string`**
   - Copies the next line from the linked list to a string.
   - **Parameters**:
     - `list`: Pointer to the linked list.
     - `str`: Pointer to the destination string.
   - **Flow**:
     - Copies data from the linked list nodes to the destination string until a newline character is encountered.

9. **`find_last`**
   - Finds the last node in the linked list.
   - **Parameters**:
     - `list`: Pointer to the linked list.
   - **Returns**:
     - Pointer to the last node.
   - **Flow**:
     - Traverses the linked list to find the last node.

10. **`new_line`**
    - Checks if a newline character exists in the current chunk of data.
    - **Parameters**:
      - `list`: Pointer to the linked list.
    - **Returns**:
      - `1` if a newline character exists, `0` otherwise.
    - **Flow**:
      - Iterates through the current chunk of data to find a newline character.
