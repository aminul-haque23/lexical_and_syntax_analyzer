/*
Change the name of the input file in the main function in order to read the file. 
My code reads from input.txt file
*/ 


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
#include <vector>
using namespace std;

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define INT_LIT 10
#define IDENT 11
#define UNARY_MINUS_OP 17
#define MOD_OP 18
#define EXPONENT_OP 19
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

// Structure for syntax tree nodes
struct SyntaxTree
{
    string value;          // Node value (operator or operand)
    SyntaxTree *left;  // Left child
    SyntaxTree *right; // Right child

    SyntaxTree(string val) : value(val), left(nullptr), right(nullptr) {}
};


// Global variables
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;
vector<string> postfix_array;

// Function declarations
void addChar();
void getChar();
void getNonBlank();
int lex();
void error();
void getNextToken();
SyntaxTree *assignment();
SyntaxTree *expr();
SyntaxTree *term();
SyntaxTree *factor();
void generatePostfix(SyntaxTree *node, string &postfix);
void generateIntermediateCode(const vector<string> &postfix);
void printExpression(SyntaxTree *node);


int main()
{
    if ((in_fp = fopen("input.txt", "r")) == NULL)
        printf("ERROR - cannot open input.txt \n");
    else
    {
        getChar();
        getNextToken();
        SyntaxTree *syntaxTree = assignment(); // Start parsing with assignment
        if (nextToken != EOF)
        {
            error();
        }
        else
        {
            cout << "Successfully Parsed Expression" << endl;
            
            // Print infix expression
            cout << "Infix Expression: ";
            printExpression(syntaxTree);
            cout << endl;

            // Generate and print postfix expression
            string postfix = "";
            generatePostfix(syntaxTree, postfix);
            cout << "Postfix Expression: " << postfix << endl;

            // Generate the intermediate code
            generateIntermediateCode(postfix_array);
        }
        fclose(in_fp);
    }
    return 0;
}

int lookup(char ch)
{
    switch (ch)
    {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '%':
        addChar();
        nextToken = MOD_OP;
        break;
    case '~':
        addChar();
        nextToken = UNARY_MINUS_OP;
        break;
    case '^':
        addChar();
        nextToken = EXPONENT_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

void addChar()
{
    if (lexLen <= 98)
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
    {
        printf("Error - lexeme is too long \n");
    }
}

void getChar()
{
    if ((nextChar = getc(in_fp)) != EOF)
    {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
    {
        charClass = EOF;
    }
}

void getNonBlank()
{
    while (isspace(nextChar))
        getChar();
}

int lex()
{
    lexLen = 0;
    getNonBlank();
    switch (charClass)
    {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT)
        {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT)
        {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}

void error()
{
    cout << "Syntax Error" << endl;
    exit(1);
}

void getNextToken()
{
    nextToken = lex();
}

SyntaxTree *assignment()
{
    cout << "Enter <assignment>" << endl;
    SyntaxTree *node = nullptr;

    if (nextToken == IDENT)
    {
        string ident = lexeme;
        getNextToken();

        if (nextToken == ASSIGN_OP) 
        {
            string op = lexeme; 
            getNextToken();

            SyntaxTree *rhs = expr();

            node = new SyntaxTree(op);
            node->left = new SyntaxTree(ident); 
            node->right = rhs;                     
        }
        else
        {
            error(); 
        }
    }
    else
    {
        node = expr(); 
    }

    cout << "Exit <assignment>" << endl;
    return node;
}


SyntaxTree *expr()
{
    cout << "Enter <expr>" << endl;
    SyntaxTree *node = term();
    while (nextToken == ADD_OP || nextToken == SUB_OP)
    {
        string op = lexeme; 
        getNextToken();
        SyntaxTree *newNode = new SyntaxTree(op);
        newNode->left = node;    
        newNode->right = term(); 
        node = newNode;          
    }
    cout << "Exit <expr>" << endl;
    return node;
}



SyntaxTree *term()
{
    cout << "Enter <term>" << endl;
    SyntaxTree *node = factor();
    while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP || nextToken == EXPONENT_OP)
    {
        string op = lexeme; 
        getNextToken();
        SyntaxTree *newNode = new SyntaxTree(op);
        newNode->left = node;      
        newNode->right = factor(); 
        node = newNode;            
    }
    cout << "Exit <term>" << endl;
    return node;
}

SyntaxTree *factor()
{
    cout << "Enter <factor>" << endl;
    SyntaxTree *node = nullptr;
    if (nextToken == INT_LIT || nextToken == IDENT)
    {
        node = new SyntaxTree(lexeme); 
        getNextToken();
    }
    else if (nextToken == LEFT_PAREN)
    {
        getNextToken();
        node = expr(); 
        if (nextToken == RIGHT_PAREN)
        {
            getNextToken();
        }
        else
        {
            error();
        }
    }
    else if (nextToken == UNARY_MINUS_OP)
    {
        string op = lexeme; 
        getNextToken();
        node = new SyntaxTree(op); 
        node->right = factor();        
    }
    else
    {
        error();
    }
    cout << "Exit <factor>" << endl;
    return node;
}

void printExpression(SyntaxTree *node)
{
    if (node == nullptr)
        return;

    if (node->left == nullptr && node->right == nullptr) 
    {
        cout << node->value; 
    }
    else 
    {
        cout << "(";                      
        printExpression(node->left);     
        cout << " " << node->value << " "; 
        printExpression(node->right);    
        cout << ")";                      
    }
}


void generatePostfix(SyntaxTree *node, string &postfix)
{
    if (node == nullptr)
        return;
    generatePostfix(node->left, postfix);
    generatePostfix(node->right, postfix);
    postfix_array.push_back(node->value);
    postfix += node->value + " ";
}

void print(vector<string> arr){
    cout << "Postfix array: ";
    for (string e : arr){
        cout << e << " ";
    }
    cout << endl;
}



void generateIntermediateCode(const vector<string> &postfix)
{
    stack<string> tempStack; 
    int tempCounter = 0;     
    for (const string &token : postfix)
    {
        if (isalpha(token[0]) || isdigit(token[0])) 
        {
            cout << "push " << token << endl;
            tempStack.push(token); 
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%")
        {
            string operand2 = tempStack.top();
            tempStack.pop();
            string operand1 = tempStack.top();
            tempStack.pop();

            string tempVar = "T" + to_string(tempCounter++);
            cout << "pop " << operand2 << endl;
            cout << "pop " << operand1 << endl;

            if (token == "+")
                cout << "add" << endl;
            else if (token == "-")
                cout << "subtract" << endl;
            else if (token == "*")
                cout << "multiply" << endl;
            else if (token == "/")
                cout << "divide" << endl;
            else if (token == "%")
                cout << "mod" << endl;
            else if(token == "^")
                cout << "exponent" << endl;

            cout << "push " << tempVar << endl;
            tempStack.push(tempVar);
        }
        else if (token == "=") 
        {
            string value = tempStack.top();
            tempStack.pop();
            string variable = tempStack.top();
            tempStack.pop();
            cout << "pop " << value << endl;
            cout << "store " << variable << endl;
        }
    }
}


