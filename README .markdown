# Lexical and Syntax Analyzer

This repository, `lexical_and_syntax_analyzer`, houses two projects that explore essential stages of a compiler frontend:

1. **Lexical Analyzer**: Converts input source code into tokens and evaluates postfix expressions directly.
2. **Syntax Analyzer**: Processes input into tokens, checks their structure against a grammar, and generates a syntax tree, postfix notation, and intermediate code.

Both projects are written in C++ and serve as educational tools to demonstrate how compilers process and understand source code. They share the initial step of lexical analysis but differ in their subsequent goals—one focuses on evaluation, the other on structured parsing and code generation.

## Projects

### Lexical Analyzer
- **Location**: `lexical_analyzer` folder
- **Purpose**: Breaks down input into manageable tokens and performs direct evaluation of postfix expressions, supporting basic arithmetic and variables.
- **More Info**: See the [Lexical Analyzer README](lexical_analyzer/README.md) for detailed instructions and examples.

### Syntax Analyzer
- **Location**: `syntax_analyzer` folder
- **Purpose**: Tokenizes input, ensures it follows a defined grammar by building a syntax tree, and produces postfix notation and intermediate code for further processing.
- **More Info**: See the [Syntax Analyzer README](syntax_analyzer/README.md) for detailed instructions and examples.

## General Concept
- The **Lexical Analyzer** is like a scanner that reads raw code and organizes it into meaningful pieces (tokens), then uses those pieces to compute results immediately.
- The **Syntax Analyzer** takes this a step further, acting like a checker and builder—it verifies the tokens make sense together and constructs a structured representation for use in later compilation stages.
