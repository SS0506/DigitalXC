Secret Santa Game - Full Stack Engineer Coding Challenge

 Overview

This project automates the Secret Santa game for a company event. Given a list of employees in CSV format, the program assigns a "secret child" to each employee, ensuring that:
- An employee does not choose themselves as their secret child.
- An employee does not receive the same secret child as last year (if applicable).
- Each employee must have exactly one secret child.
- Each secret child is assigned to only one employee.

The program reads input employee information from a CSV file, processes the Secret Santa assignments, and generates a new CSV file containing the result.

 Project Structure


SecretSantaGame/
│
├── input/
│   └── employees.csv                  -- Input file containing employee information (Employee_Name, Employee_EmailID)
│   └── last_year_assignments.csv      -- Optional: Previous year's Secret Santa assignments
│
├── output/
│   └── secret_santa_assignments.csv   -- Generated file with Secret Santa assignments
│
├── src/
│   └── main.cpp                       -- Main C++ source file
│
├── README.md                          -- Project documentation
└── Makefile                           -- Optional: To compile the program


 Requirements

- C++ Compiler: This project is implemented in C++.
- Standard Libraries: The program uses standard C++ libraries such as `<fstream>`, `<iostream>`, `<vector>`, `<string>`, `<map>`, `<unordered_set>`, `<random>`, `<stdexcept>`, and `<sstream>`.
- Logging: The program uses basic logging to track significant events during execution.

 Installation and Setup

1. Clone the repository:
   
   bash
   git clone <repository_url>
   cd SecretSantaGame
   

2. Compile the program:
   
   Ensure you have a C++ compiler installed (e.g., `g++` or `cl` for Microsoft Visual Studio). You can compile the program with the following command:

   For GCC or Clang:
   
   bash
   g++ src/main.cpp -o secret_santa_game 

   For Microsoft Visual Studio's command line tools (`cl`), use the following command (ensure `/EHsc` flag is included for exception handling):

   bash
   cl /EHsc src/main.cpp
   

3. Run the Program:

   After compiling, run the executable:

   For Linux/macOS:

   bash
   ./secret_santa_game

   For Windows with `cl`:

   bash
   secret_santa_game.exe
   

4. Input File:

   Place the input file `employees.csv` in the `input/` folder. The CSV should contain the following columns:

   - Employee_Name: The name of the employee.
   - Employee_EmailID: The email ID of the employee.

   Example format:

   csv
   Employee_Name,Employee_EmailID
   John Doe,john@example.com
   Jane Smith,jane@example.com
   

   Optionally, if you have previous year's assignments, place them in `last_year_assignments.csv` in the same folder.

5. Output File:

   The program will generate a new file `secret_santa_assignments.csv` in the `output/` folder, containing the following columns:

   - Employee_Name: The name of the employee.
   - Employee_EmailID: The email ID of the employee.
   - Secret_Child_Name: The name of the assigned secret child.
   - Secret_Child_EmailID: The email ID of the assigned secret child.

   Example output format:

   csv
   Employee_Name,Employee_EmailID,Secret_Child_Name,Secret_Child_EmailID
   John Doe,john@example.com,Jane Smith,jane@example.com
   Jane Smith,jane@example.com,John Doe,john@example.com
   

 Features

1. No Self-Assignments: Employees cannot assign themselves as their secret child.
2. Avoid Previous Year Assignments: If applicable, the program ensures that employees do not receive the same secret child as they did in the previous year.
3. Balanced Assignments: Each employee will be assigned one secret child, and each child will be assigned exactly one employee.
4. Output in CSV Format: The program generates an output CSV file that contains the assignment results.
5. Error Handling: The program checks for missing or malformed input files and will show an appropriate error message.
6. Logging: The program logs significant events, such as successful assignment generation, missing files, and errors.

 Error Handling

- File Missing/Corrupted: If the input files are missing or the data is malformed, an appropriate error message will be displayed.
- Invalid Data: The program will catch invalid data, such as missing email IDs or names, and prompt the user to correct the input.
- Exception Handling: The program uses C++ exception handling to manage runtime errors gracefully. Ensure your compiler is set up to handle exceptions with the `/EHsc` flag for Visual Studio users.

 Testing

The program includes basic unit tests to ensure correctness. You can add more test cases to check edge cases, such as when there is only one employee or when the input data is empty.

To run tests (if implemented), you can use the following framework:

1. Unit Tests in C++: Consider using a testing framework like [Google Test](https://github.com/google/googletest) for writing unit tests and running them.

 Logging

- The program logs key events like file reading, assignments, and errors. This helps keep track of its internal processes and aids in debugging.
- Logs are printed to the console, but you can easily extend the program to log to a file if desired.

 Documentation

This repository contains the following files:

- README.md: This documentation.
- `src/main.cpp`: The main C++ file that contains the logic for parsing input and generating assignments.
- `input/`: Folder for input CSV files.
- `output/`: Folder where the generated Secret Santa assignments are stored.



