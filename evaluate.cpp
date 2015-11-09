// Simple Expression Evaluation Implementation file
// This describes the functionality for evaluating very simple
// arithmetic expressions.  Given a string consisting of operators
// and operands, it will evaluate that expression and return its value.
//
// The expressions may consist of the following:
// -- single-digit integer values
// -- simple arithmetic operators ( +, -, *, /, % )
// -- matched parentheses for grouping

// This implementation consists of a set of mutually-recursive 
// functions. which will track the structure of the expression.
//
// A sum expression is the sum or difference of one or more products.
// A product expression is the product or quotient of one or more factors.
// A factor may be a number or a parenthesized sum expression.
using namespace std;

#include "tokenize.h"
#include <iostream>

int parens(const char[], int&);
int mult(const char[], int&);
int add(const char[], int&);
int findlength(const char[]);


// linearly walk through function and evaluate chunks
int evaluate(const char expr[])
{
	int length = findlength(expr);
	int current = 0, sum = 0;
	char term;
	findFirstToken(expr, current);
	while (current < length) // iterate through function
	{
		term = expr[current];
		if (term == '(')
		{
			// Find 2nd parenthesis
			int counter = 1, end = current;
			advance(expr, end);
			while (counter != 0)  // find other )
			{
				if (expr[end] == '(')
					counter += 1;
				if (expr[end] == ')')
					counter -= 1;
				advance(expr, end);
			}
			if (expr[end] == '*' || expr[end] == '/' || expr[end] == '%')
			{
				current = end;
				sum +=mult(expr, current);
			}
			else
				sum += parens(expr, current);

		}
		if (term == '+' || term == '-')
			sum += add(expr, current);
		if (term == '*' || term == '/' || term == '%')
			sum += mult(expr, current);
		else
			advance(expr, current);
	}
	// deal with fringe cases of addition
	goback(expr, current);
	int extra = integerValue(expr, current);
	goback(expr, current);
	if (expr[current] == '+')
		sum += extra;
	if (expr[current] == '-')
		sum -= extra;


	return sum;
}

int parens(const char expr[], int& current)
{
	cout << "parens";
	advance(expr, current);
	int end  = current;
	int counter = 1;
	// Find 2nd parenthesis
	while (counter != 0)  // find other )
	{
		if (expr[end] == '(')
			counter += 1;
		if (expr[end] == ')')
			counter -= 1;
		else
			advance(expr, end);
	}
	char term;
	int sum = 0;
	while (current <= end) // iterate through function
	{
		term = expr[current];
		if (term == '(')
			sum += parens(expr, current);
		if (term == '+' || term == '-')
			sum += add(expr, current);
		if (term == '*' || term == '/' || term == '%')
			sum += mult(expr, current);
		else
			advance(expr, current);
	}
	// deal with fringe cases of addition
	goback(expr, current);
	int extra = integerValue(expr, current);
	goback(expr, current);
	if (expr[current] == '+')
		sum += extra;
	if (expr[current] == '-')
		sum -= extra;

	cout << expr[current];

	return sum;
}



int mult(const char expr[], int& current)
{
	cout << "mult ";
	int reverse = current, flag, left, right;
	advance(expr, current);
	if (expr[current] == '*')
		flag = 1;
	if (expr[current] == '/')
		flag = 0;
	if (expr[current] == '%')
		flag = 2;
	while (expr[reverse != '+' && expr[reverse] != '-') // solve right



	while (expr[current != '+' && expr[current] != '-') // solve right



	return 20;

}


// find left and right with mult or paren, add left and right
int add(const char expr[], int& current)
{
	cout << "add ";
	int sum, flag;
	int reverse = current;
	if (expr[current] == '+')
		flag = 1;
	if (expr[current] == '-')
		flag = 0;

	goback(expr, reverse);
	advance(expr, current);
	int left = integerValue(expr, reverse), right = integerValue(expr, current);
	goback(expr, reverse);
	advance(expr, current);

	if (expr[reverse] == '*' || expr[reverse] == '/' || expr[reverse] == '%')
		left = mult(expr, reverse);
	if (expr[current] == '*' || expr[current] == '/' || expr[current] == '%')
		right = mult(expr, current);
	if (flag == 1)
		sum = left + right;
	if (flag == 0)
		sum = left-right;
	return sum;
}

int findlength(const char expr[])
{
	int i = 0;
	while (expr[i] != '\0')
	{
		i += 1;
	}
	return i;
}