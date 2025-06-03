# Postfix Expression Evaluator with Lexical Analysis

## Description
This project implements a lexical analyzer that tokenizes input from a file and evaluates postfix expressions. It supports basic arithmetic operations, exponentiation, modulus, and unary minus, along with variable assignments. The code is written in C++ and processes input from a hardcoded file named "input.txt".

## Features
- Token recognition for identifiers, integers, floats, and various operators.
- Support for variable assignments and usage in expressions.
- Evaluation of postfix expressions with step-by-step stack visualization.
- Handles operations: `+`, `-`, `*`, `/`, `^`, `%`, and unary minus (`~`).

## How to Use
1. Ensure you have a C++ compiler installed (e.g., `g++`).
2. Place your input in a file named "input.txt" in the same directory as the source code.
   - If your input file has a different name, update the file name in the `main` function of the code (look for `fopen("input.txt", "r")`).
3. Compile the code using: `g++ -o evaluator main.cpp`
4. Run the program: `./evaluator`
5. The program will process the input, display the tokenization steps, and show the evaluation process with the final result.

## Input Format
The input should be provided in a file (e.g., "input.txt"). Each token must be separated by spaces. The program supports:
- **Variable assignments**: e.g., `a 1 =` assigns the value `1` to variable `a`.
- **Postfix expressions**: e.g., `b ~ b 2 ^ 4 a * c * - .5 ^ + 2 a * /` evaluates the expression using assigned variables.

## Example
**Input (input.txt):**
```
a 1 =
b 6 =
c 8 =
b ~ b 2 ^ 4 a * c * - .5 ^ + 2 a * /
```

**Output:**
```
Next token is 11, next lexeme is a
Next token is 11, next lexeme is 1
Next token is 20, next lexeme is =
Next token is 11, next lexeme is b
Next token is 11, next lexeme is 6
Next token is 20, next lexeme is =
Next token is 11, next lexeme is c
Next token is 11, next lexeme is 8
Next token is 20, next lexeme is =
Next token is 11, next lexeme is b
Next token is 17, next lexeme is ~
...
Pushed 6 in the stack.
The stack currently has: 6
Encountered ~
Popped 6 in the stack.
The stack currently has:
Unary minus: -1 * 6 = -6
Pushed -6 in the stack.
The stack currently has: -6
...
Result of postfix expression: -2
```

## Code Structure
- `main.cpp`: Contains the main function and the lexical analyzer implementation.
- **Lexical analyzer functions**: `addChar`, `getChar`, `getNonBlank`, `lex`, `lookup`.
- **Postfix evaluation logic**: `evaluatePostfix`, `doOperation`, `printStack`.
- **Data structures**: Stacks for evaluation, vectors for intermediate code, `unordered_map` for variables.

## Limitations
- Lexeme length is limited to 98 characters; longer lexemes will cause the program to exit with an error.
- The program assumes correctly formatted input. Invalid inputs may lead to unexpected behavior.
- The input file name ("input.txt") is hardcoded and must be updated in the code if a different file is used.

## Future Work
- Implement a syntax analyzer to build and traverse a syntax tree for more complex expression handling (planned for Part B).
- Enhance error handling for invalid inputs or expressions.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. *(Note: Please add a LICENSE file to your repository if you intend to use the MIT License or specify a different license.)*