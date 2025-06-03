// This is part a, here i only deal with the postfix. Part b is in the other file.

/*
One important thing to notice here is that i am not taking a "".txt" as a command line input.
Instead in the main function the input file it looks for is "input.txt" that is located in the
same directory. So, if your test file has a specific name, please change the file name "input.txt"
to the desired name in the main function.
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

int charClass;
string lexeme;
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

// Lexical Analyzer
void addChar();
void getChar();
void getNonBlank();
int lex();

// Syntax Analyzer
void assign();
void expr();
void term();
void factor();
void exp();
void getNextToken();

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define FLOAT_LIT 9
#define INT_LIT 10
#define IDENT 11
#define DOT 16
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

vector<string> intermediateCode;
vector<string> updatedInter;
unordered_map<string, double> variables;
stack<double> operandStack;

void addToIntermediateCode(string lexemeStr)
{
    intermediateCode.push_back(lexemeStr);

    if (lexemeStr == "=")
    {
        int value = stod(intermediateCode[intermediateCode.size() - 2]); // If the postfix is correct and the current token is =. Then the previouse token must be a value that would be assigned to a variable.
        string key = intermediateCode[intermediateCode.size() - 3];      // This gets the variable
        variables[key] = value;
    }
}

/*In this loop below we are only trying to get the postfix statement that we are gonna use for evaluating expression.
If we are assigning values to a variable, then we expect an equal to appear in every 3rd position.
So, if i + 1 (since i start from 0 we add 1) is divisible by 3 then we must see a = sign at that position. If we don't
see an equal sign at position that means we are currently dealing with the postfix statement(a b c + +, here no equal sign at the 3rd position)
that we need to evaluate. So, we get the first lexeme of the postfix statement by saving the position (position = i - 2, if there is no = sign at 3rd position)
*/

void modifyData()
{

    int position = -1;

    // Identify the starting position of the postfix expression
    for (int i = 0; i < intermediateCode.size(); i++)
    {
        if ((i + 1) % 3 == 0 && intermediateCode[i] != "=")
        {
            position = i - 2;
            break;
        }
    }

    // Check if a valid position was found
    if (position == -1)
    {
        cerr << "No postfix expression found in intermediateCode." << endl;
        return;
    }

    // Copy postfix expression to updatedInter
    for (int i = position; i < intermediateCode.size(); i++)
    {
        updatedInter.push_back(intermediateCode[i]);
    }
}

void printStack(double a, string operationDone)
{

    stack<double> tempStack = operandStack;
    vector<double> arr;

    cout << operationDone << a << " in the stack." << endl;
    cout << "The stack currently has: ";

    while (!tempStack.empty())
    {
        arr.push_back(tempStack.top());
        tempStack.pop();
    }

    int i = arr.size() - 1;
    while (i >= 0)
    {
        cout << arr[i] << " ";
        i--;
    }

    cout << endl
         << endl;
}

void doOperation(string a)
{
    double result = 0;
    cout << "Encountered " << a << endl;
    double operand2 = operandStack.top();
    operandStack.pop();
    printStack(operand2, "Popped ");

    double operand1 = operandStack.top();
    operandStack.pop();
    printStack(operand1, "Popped ");

    if (a == "+")
    {
        result = operand1 + operand2;
        cout << "Adding: " << operand1 << " + " << operand2 << " = " << result << endl;
    }

    else if (a == "-")
    {
        result = operand1 - operand2;
        cout << "Substracting: " << operand1 << " - " << operand2 << " = " << result << endl;
    }

    else if (a == "/")
    {
        result = operand1 / operand2;
        cout << "Dividing: " << operand1 << " / " << operand2 << " = " << result << endl;
    }

    else if (a == "%")
    {
        result = fmod(operand1, operand2);
        cout << "Mod: " << operand1 << " % " << operand2 << " = " << result << endl;
    }

    else if (a == "*")
    {
        result = operand1 * operand2;
        cout << "Multiplication: " << operand1 << " * " << operand2 << " = " << result << endl;
    }

    else if (a == "^")
    {
        result = pow(operand1, operand2);
        cout << "Power: " << operand1 << " ^ " << operand2 << " = " << result << endl;
    }

    operandStack.push(result);
    printStack(result, "Pushed ");
}

double evaluatePostfix()
{
    for (string a : updatedInter)
    {
        if (isdigit(a[0]) || a[0] == '.')
        {
            operandStack.push(stod(a));
            printStack(stod(a), "Pushed ");
        }

        else if (isalpha(a[0]))
        {
            auto it = variables.find(a);
            if (it != variables.end())
            {
                operandStack.push(it->second);
                printStack(it->second, "Pushed ");
            }
        }

        else if (a == "+")
        {
            doOperation(a);
        }

        else if (a == "-")
        {
            doOperation(a);
        }

        else if (a == "/")
        {
            doOperation(a);
        }

        else if (a == "~")
        {
            cout << "Encountered " << a << endl;
            double operand1 = operandStack.top();
            operandStack.pop();
            printStack(operand1, "Popped ");
            double result = -1 * operand1;
            cout << "Unary minus: " << "-1 * " << operand1 << " = " << result << endl
                 << endl;
            operandStack.push(result);
            printStack(result, "Pushed ");
        }

        else if (a == "%")
        {
            doOperation(a);
        }

        else if (a == "^")
        {
            doOperation(a);
        }

        else if (a == "*")
        {
            doOperation(a);
        }

        else
        {
            cout << "Invalid notation. Exiting program. " << endl;
            exit(0);
        }
    }

    return operandStack.top();
}

int main()
{
    if ((in_fp = fopen("input.txt", "r")) == NULL)
        printf("ERROR - cannot open input.txt \n");
    else
    {
        getChar();
        while (nextToken != EOF)
        {
            lex();
        }
        fclose(in_fp);
    }

    cout << "\n\n";

    modifyData();

    double result = evaluatePostfix();
    cout << "Result of postfix expression: " << result << endl;

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
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    case '^':
        addChar();
        nextToken = EXPONENT_OP;
        break;
    case '%':
        addChar();
        nextToken = MOD_OP;
        break;
    case '~':
        addChar();
        nextToken = UNARY_MINUS_OP;
        break;
    case '.':
        addChar();
        nextToken = DOT;
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
    lexeme = lexeme + nextChar;
    if (lexeme.length() >= 98)
    {
        cout << "Error, lexeme length is too large. Exiting";
        exit(0);
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
        charClass = EOF;
}

void getNonBlank()
{
    while (nextChar == ' ' || nextChar == '\t' || nextChar == '\n')
    {
        getChar();
    }
}

int lex()
{
    lexeme = "";
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
            nextToken = INT_LIT;
        }
        if (nextChar == '.')
        {
            addChar();
            getChar();
            if (isdigit(nextChar))
            {
                nextToken = FLOAT_LIT;
                while (isdigit(nextChar))
                {
                    addChar();
                    getChar();
                }
            }
            else
            {
                return EOF;
            }
        }
        break;

    case UNKNOWN:
        lookup(nextChar);
        if (nextChar == '.')
        {
            getChar();
            while (isdigit(nextChar))
            {
                addChar();
                getChar();
            }
            nextToken = FLOAT_LIT;
        }
        getChar();
        break;

    case EOF:
        nextToken = EOF;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is " << nextToken << ", next lexeme is " << lexeme << endl;

    if (nextToken != EOF)
    {
        addToIntermediateCode(lexeme);
    }

    return nextToken;
}
