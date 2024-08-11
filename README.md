# Compiler Project

## Overview

This project is a compiler written in C using YACC and LEX. It generates a ready-to-use C++ file that processes user input according to the rules defined in a new language specification. The input for the compiler is provided in a file named `INPUT.txt`.

## Components

- **YACC (Yet Another Compiler Compiler)**: Used for parsing the language and generating a syntax tree.
- **LEX (Lexical Analyzer Generator)**: Used for tokenizing the input according to the language rules.
- **C++ Output File**: The resulting C++ file processes the input based on the new language's grammar.

## How It Works

1. **Define the Language**: Specify the grammar and lexical rules of the new language in the YACC and LEX files.
2. **Compile the YACC and LEX Files**: Use YACC and LEX to generate the C source files.
3. **Compile the C Code**: Compile the generated C code to produce the final C++ output file.
4. **Run the Compiler**: The compiler processes the `INPUT.txt` file according to the specified language rules and produces the desired output.

## Building the Project

1. **Install YACC and LEX**: Make sure YACC and LEX are installed on your system.
2. **Generate C Source Files and Build the Program**: Run the following commands to build the project:
   ```sh
   make
   ./parse
   make test
   ./test
