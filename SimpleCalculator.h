#pragma once
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class SimpleCalculator
{
private:
	stack<double> operands; // Stack to hold operands
	stack<char> operators; // Stack to hold operators
	double applyOperator(double a, double b, char op); // Function to apply an operator to two operands
	short precedence(char op); // Function to determine the precedence of an operator
	void processOperator(char op); // Function to process an operator
	
public:
	SimpleCalculator(); // Constructor
	double evaluate(const string& expression); // Function to evaluate an arithmetic expression
	string infixToPostfix(const string& expression); // Option 2

};


