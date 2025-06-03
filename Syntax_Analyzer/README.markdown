# Compiler Frontend: Lexical and Syntax Analysis with Intermediate Code Generation

## Description
This project implements a compiler frontend in C++ that performs lexical analysis, syntax analysis, postfix expression generation, and intermediate code generation for a simple expression language. It supports variable assignments and arithmetic expressions with operators for addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), modulus (`%`), exponentiation (`^`), and unary minus (`~`). The program reads input from a file, builds a syntax tree, converts it to postfix notation, and generates stack-based intermediate code.

## Features
- **Lexical Analysis**: Tokenizes input into identifiers, integers, and operators.
- **Syntax Analysis**: Parses tokens to construct a syntax tree for assignments and expressions.
- **Postfix Generation**: Converts the syntax tree into postfix notation.
- **Intermediate Code Generation**: Produces stack-based intermediate code from the postfix expression.
- **Supported Operations**: `+`, `-`, `*`, `/`, `%`, `^`, `~` (unary minus), and `=` (assignment).

## How to Use
1. Ensure you have a C++ compiler installed (e.g., `g++`).
2. Prepare your input in a text file. By default, the program reads from `input.txt`. To use a different file:
   - Open `main.cpp` and locate the line `if ((in_fp = fopen("input.txt", "r")) == NULL)`.
   - Replace `"input.txt"` with your desired file name (e.g., `"myinput.txt"`).
3. Save your input file in the same directory as `main.cpp`.
4. Compile the code:
   ```bash
   g++ -o compiler main.cpp
   ```
5. Run the program:
   ```bash
   ./compiler
   ```
6. The program will:
   - Display parsing steps.
   - Show the infix and postfix expressions.
   - Output stack-based intermediate code.

## Input Format
- Input should be a single assignment statement or expression, with tokens separated by spaces.
- **Variables**: Single letters (a-z, A-Z).
- **Literals**: Integers (e.g., `1`, `42`).
- **Operators**: `+`, `-`, `*`, `/`, `%`, `^`, `~` (unary minus), `=` (assignment).
- **Parentheses**: Used for grouping expressions.
- **Example**: `A = (A - B) + (C % D) * (D ^ 3)`

## Examples

### Test Case 1
**Input (input.txt):**
```
A = (A - B) + (C % D) * (D ^ 3)
```

**Output:**
```
Next token is: 11, Next lexeme is A
Enter <assignment>
Next token is: 20, Next lexeme is =
Next token is: 25, Next lexeme is (
Enter <expr>
...
Successfully Parsed Expression
Infix Expression: (A = ((A - B) + ((C % D) * (D ^ 3))))
Postfix Expression: A A B - C D % D 3 ^ * + =
push A
push A
push B
pop B
pop A
subtract
push T0
push C
push D
pop D
pop C
mod
push T1
push D
push 3
pop 3
pop D
multiply
push T2
pop T2
pop T1
add
push T3
pop T3
store T0
```

### Test Case 2
**Input (input.txt):**
```
t = (4 * x + 9 * y - 18) / (x + y + z)
```

**Output:**
```
Next token is: 11, Next lexeme is t
Enter <assignment>
Next token is: 20, Next lexeme is =
Next token is: 25, Next lexeme is (
Enter <expr>
...
Successfully Parsed Expression
Infix Expression: (t = ((((4 * x) + (9 * y)) - 18) / ((x + y) + z)))
Postfix Expression: t 4 x * 9 y * + 18 - x y + z + / =
push t
push 4
push x
pop x
pop 4
multiply
push T0
push 9
push y
pop y
pop 9
multiply
push T1
pop T1
pop T0
add
push T2
push 18
pop 18
pop T2
subtract
push T3
push x
push y
pop y
pop x
add
push T4
push z
pop z
pop T4
add
push T5
pop T5
pop T3
divide
push T6
pop T6
store t
```

## Code Structure
- `main.cpp`: Contains all functionality, including:
  - **Lexical Analyzer**: Functions like `lex()`, `lookup()`, and `getChar()` for tokenization.
  - **Syntax Analyzer**: Recursive descent parsing with `assignment()`, `expr()`, `term()`, and `factor()`.
  - **SyntaxTree struct**: Defines nodes for the syntax tree.
  - **Helper Functions**: `printExpression()`, `generatePostfix()`, `generateIntermediateCode()`.


## Future Work
- Add support for floating-point numbers.
- Enhance error handling for malformed input.
- Allow input from command line or standard input.
- Expand the language with features like conditionals or loops.
