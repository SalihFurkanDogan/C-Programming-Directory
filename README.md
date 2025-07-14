# Contact Directory Application (C Language)

This is a console-based **Contact Directory Application** written in the C programming language. It allows users to **add**, **delete**, **update**, **list**, and **search** for persons. The application uses dynamic memory allocation and stores contacts in a **linked list** structure.

## Features

- Add a new person to the directory
- Delete a person by ID
- Update person details
- List all persons
- Search for persons by name, surname, email, address, or phone number
- Prevents adding duplicate phone numbers

## Data Structures

- `PERSON`: Stores individual person's information
- `Node`: A node in the linked list, holding a `PERSON`
- `DIRECTORY`: Represents the entire directory and the list of persons

## File Structure

All code is included in a single `.c` file. To compile and run:

gcc -o directory_app main.c
./directory_app
