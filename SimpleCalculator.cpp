#include "SimpleCalculator.h"
#include <iostream>
#include <cmath>
#include <cctype>
#include <stdexcept>

using namespace std;

SimpleCalculator::SimpleCalculator()
{
    
}

// Precondition: a and b are operands, and op is an arithmetic operator.
// Postcondition: Returns the result of the operation.
double SimpleCalculator::applyOperator(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;

    case '-':
        return a - b;

    case '*':
        return a * b;

    case '/':
        if (b == 0)
            throw runtime_error("Division by zero.");

        return a / b;

    case '^':
        return pow(a, b);

    default:
        throw runtime_error("Invalid operator.");
    }
}

// Precondition: op is an arithmetic operator.
// Postcondition: Returns the precedence of the operator.
short SimpleCalculator::precedence(char op)
{
    switch (op)
    {
    case '^':
        return 3;

    case '*':
    case '/':
        return 2;

    case '+':
    case '-':
        return 1;

    default:
        return 0;
    }
}

// Precondition: The operand stack contains at least two operands.
// Postcondition: Performs the operation and pushes the result.
void SimpleCalculator::processOperator(char op)
{
	const short TWO = 2; 
    if (operands.size() < TWO)
    {
        throw runtime_error("Invalid expression.");
    }

    double b = operands.top();
    operands.pop();

    double a = operands.top();
    operands.pop();

    operands.push(applyOperator(a, b, op));
}

// Precondition: expression contains an arithmetic expression.
// Postcondition: Returns the evaluated result.
double SimpleCalculator::evaluate(const string& expression)
{
	const short ONE = 1; 
	bool hasParentheses = false; // Flag to track if the expression contains parentheses.
    // Check whether the expression starts with '('.
    size_t first = expression.find_first_not_of(" \t\n\r");

    if (first == string::npos || expression[first] != '(')
    {
        throw runtime_error("Parentheses don't match.");
    }
    // Clear both stacks.
    while (!operands.empty())
    {
        operands.pop();
    }

    while (!operators.empty())
        operators.pop();

	bool expectOperand = true; // Flag to track if we expect an operand next.
	// Iterate through the expression character by character.
    for (size_t i = 0; i < expression.length(); i++)
    {
		char ch = expression[i]; // Current character in the expression.
        if (isspace(static_cast<unsigned char>(ch)))
            continue;

        // Handle negative numbers.
        if ((ch == '-' || ch == '+') && expectOperand && i + ONE < expression.length() && (isdigit(static_cast<unsigned char>(expression[i + ONE])) || expression[i + ONE] == '.'))
        {
            size_t length;
            double number = stod(expression.substr(i), &length);

            operands.push(number);
			i += length - ONE; // Move the index to the end of the number.
            expectOperand = false;
        }
        // Handle positive numbers.
        else if (isdigit(static_cast<unsigned char>(ch)) || ch == '.')
        {
            if (!expectOperand)
            {
                throw runtime_error("ERROR: Invalid arithmetic expression.");
            }

            size_t length;
            double number = stod(expression.substr(i), &length);

            operands.push(number);
            i += length - ONE;
            expectOperand = false;
        }
        // Handle opening parentheses.
        else if (ch == '(')
        {
            if (!expectOperand)
            {
                throw runtime_error("Invalid expression.");
            }
			hasParentheses = true; // Set the flag to true since we encountered an opening parenthesis.

            operators.push(ch);
        }
        // Handle closing parentheses.
        else if (ch == ')')
        {
            if (expectOperand)
            {
                throw runtime_error("Invalid expression.");
            }

            while (!operators.empty() && operators.top() != '(')
            {
                char op = operators.top();
                operators.pop();

                processOperator(op);
            }

            if (operators.empty())
            {
                throw runtime_error("Parentheses don't match.");
            }

            operators.pop();
            expectOperand = false;
        }
        // Handle arithmetic operators.
        else if (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' || ch == '^')
        {
            if (expectOperand)
            {
                throw runtime_error("Invalid expression.");
            }

            while (!operators.empty() && operators.top() != '(' && (precedence(operators.top()) > precedence(ch) || (precedence(operators.top()) == precedence(ch) && ch != '^')))
            {
                char op = operators.top();
                operators.pop();

                processOperator(op);
            }

            operators.push(ch);
            expectOperand = true;
        }
        else
        {
            throw runtime_error("Invalid character.");
        }
    }

    if (expectOperand)
        throw runtime_error("Invalid expression.");

    // Process remaining operators.
    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();

        if (op == '(')
        {
            throw runtime_error("Parentheses don't match.");
        }

        processOperator(op);
    }

    if (!hasParentheses)
    {
        throw runtime_error("Parentheses don't match.");
    }

    if (operands.size() != ONE)
    {
        throw runtime_error("Invalid expression.");
    }

    return operands.top();
}

// Precondition: expression contains an infix arithmetic expression.
// Postcondition: Returns the equivalent postfix expression.
// Throws an exception if the expression is invalid.
string SimpleCalculator::infixToPostfix(const string& expression)
{
    stack<char> opStack;
    string postfix = "";

    bool expectOperand = true;
    int parenthesesCount = 0;

    for (size_t i = 0; i < expression.length(); i++)
    {
        char ch = expression[i];

        // Ignore spaces.
        if (isspace(static_cast<unsigned char>(ch)))
        {
            continue;
        }

        // Handle negative and positive numbers.
        if ((ch == '-' || ch == '+') && expectOperand)
        {
            size_t next = i + 1;

            // Skip spaces after the sign.
            while (next < expression.length() && isspace(static_cast<unsigned char>(expression[next])))
            {
                next++;
            }

            // Check whether the sign belongs to a number.
            if (next < expression.length() && (isdigit(static_cast<unsigned char>(expression[next])) || expression[next] == '.'))
            {
                postfix += ch;

                i = next;

                bool hasDigit = false;
                bool hasDecimal = false;

                while (i < expression.length() && (isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.'))
                {
                    if (expression[i] == '.')
                    {
                        if (hasDecimal)
                        {
                            throw runtime_error("Invalid decimal number.");
                        }

                        hasDecimal = true;
                    }
                    else
                    {
                        hasDigit = true;
                    }

                    postfix += expression[i];
                    i++;
                }

                if (!hasDigit)
                {
                    throw runtime_error("Invalid number.");
                }

                postfix += ' ';
                i--;

                expectOperand = false;
                continue;
            }
        }

        // Handle numbers.
        if (isdigit(static_cast<unsigned char>(ch)) || ch == '.')
        {
            // Two operands cannot appear without an operator.
            if (!expectOperand)
            {
                throw runtime_error("Missing operator between operands.");
            }

            bool hasDigit = false;
            bool hasDecimal = false;

            while (i < expression.length() && (isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.'))
            {
                if (expression[i] == '.')
                {
                    if (hasDecimal)
                    {
                        throw runtime_error("Invalid decimal number.");
                    }

                    hasDecimal = true;
                }
                else
                {
                    hasDigit = true;
                }

                postfix += expression[i];
                i++;
            }

            if (!hasDigit)
            {
                throw runtime_error("Invalid number.");
            }

            postfix += ' ';
            i--;

            expectOperand = false;
        }

        // Handle variables.
        else if (isalpha(static_cast<unsigned char>(ch)))
        {
            if (!expectOperand)
            {
                throw runtime_error("Missing operator between operands.");
            }

            while (i < expression.length() && isalnum(static_cast<unsigned char>(expression[i])))
            {
                postfix += expression[i];
                i++;
            }

            postfix += ' ';
            i--;

            expectOperand = false;
        }

        // Handle opening parentheses.
        else if (ch == '(')
        {
            if (!expectOperand)
            {
                throw runtime_error("Missing operator before '('.");
            }

            opStack.push(ch);
            parenthesesCount++;
        }

        // Handle closing parentheses.
        else if (ch == ')')
        {
            if (parenthesesCount == 0)
            {
                throw runtime_error("Parentheses don't match.");
            }

            if (expectOperand)
            {
                throw runtime_error("Missing operand before ')'.");
            }

            while (!opStack.empty() && opStack.top() != '(')
            {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }

            if (opStack.empty())
            {
                throw runtime_error("Parentheses don't match.");
            }

            opStack.pop();
            parenthesesCount--;

            expectOperand = false;
        }

        // Handle arithmetic operators.
        else if (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' || ch == '^')
        {
            // An operator must have a left operand.
            if (expectOperand)
            {
                throw runtime_error("Missing operand before operator.");
            }

            while (!opStack.empty() && opStack.top() != '(' && (precedence(opStack.top()) > precedence(ch) || (precedence(opStack.top()) == precedence(ch) && ch != '^')))
            {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }

            opStack.push(ch);

            // After an operator, another operand is required.
            expectOperand = true;
        }

        else
        {
            throw runtime_error("Invalid character.");
        }
    }

    // Check whether the expression ends with an operator.
    if (expectOperand)
    {
        throw runtime_error("Missing operand at the end of expression.");
    }

    // Check unmatched parentheses.
    if (parenthesesCount != 0)
    {
        throw runtime_error("Parentheses don't match.");
    }

    // Process remaining operators.
    while (!opStack.empty())
    {
        if (opStack.top() == '(')
        {
            throw runtime_error("Parentheses don't match.");
        }

        postfix += opStack.top();
        postfix += ' ';
        opStack.pop();
    }

    // Remove the last space.
    if (!postfix.empty())
    {
        postfix.pop_back();
    }

    return postfix;
}

