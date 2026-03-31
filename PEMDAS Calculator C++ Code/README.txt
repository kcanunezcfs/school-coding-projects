PEMDAS Calculator in C++

This project is a C++ console-based calculator that evaluates mathematical expressions using the PEMDAS rule (Parentheses, Exponents, Multiplication, Division, Addition, and Subtraction). It accepts user input in infix notation, converts it into postfix notation, and then computes the result using a linked list-based stack implementation. The uploaded source shows the infix-to-postfix conversion, postfix evaluation, custom stack, expression validation, and formatted output.

Features
Evaluates mathematical expressions based on PEMDAS
Supports:
Addition +
Subtraction -
Multiplication *
Division /
Exponents ^
Parentheses ()
Multi-digit numbers
Decimal values
Validates expressions before solving
Uses a custom linked list stack
Displays results in 2 decimal places
How It Works

The program asks the user to enter a mathematical expression. It then:

Validates the expression
Converts the infix expression to postfix
Evaluates the postfix expression
Displays the final result

The main program flow and prompt are implemented in main(), where the expression is read with getline, validated, converted, and evaluated.

Example Input and Output
Example 1
Enter a mathematical expression: 2+3*4
Result: 14.00