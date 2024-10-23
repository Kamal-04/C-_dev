# Library Management System

This is a basic C++ project that simulates a simple library management system using MySQL as the backend database. The system allows an administrator to add books and register students, while students can borrow available books.

## Features

- **Admin Functions**:
  - Add new books to the library database.
  - Register new students.

- **User Functions**:
  - View available books in the library.
  - Borrow books if they are available.

## Database

The system connects to a MySQL database named `mydb` and interacts with the following tables:

- **`lib`**: Stores book information (`Name`, `Quantity`).
- **`student`**: Stores registered student IDs.

## Prerequisites

To run this project, ensure you have:

- MySQL installed and running.
- The following MySQL tables created:

  ```sql
  CREATE TABLE lib (
    Name VARCHAR(255),
    Quantity INT
  );

  CREATE TABLE student (
    Id VARCHAR(255)
  );
