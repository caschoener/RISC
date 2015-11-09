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

int mult(const char[], int, int);
int add(const char[], int, int);
int findlength(const char[]);


// linearly walk through function and evaluate chunks
int evaluate(const char expr[])
{
	return add(expr, 0, findlength(expr));
}




int mult(const char expr[], int start, int end)
{
	int current = start, sum = 1, finder, value;
	char term;

	if (currentIsInteger(expr, current)) // initial value from first piece of product
		value = integerValue(expr, current);
	else
	{
		int counter = 1;
		while (counter != 0)  // find other )
		{
			advance(expr, current);
			if (expr[current] == '(')
				counter += 1;
			if (expr[current] == ')')
				counter -= 1;
		}
		goback(expr, current);
		value = add(expr, start, current);
	}


	return value;
}


int add(const char expr[], int start, int end)
{
	int sum = 0, current = start, previousPlus = start, flag = 0;
	char term;

	while (current <= end) // iterate through function
	{
		term = expr[current];
		if (term == '(') // find other paren, skip past
		{
			flag = 1;
			int counter = 1;
			while (counter != 0)  // find other )
			{
				advance(expr, current);
				if (expr[current] == '(')
					counter += 1;
				if (expr[current] == ')')
					counter -= 1;
			}
		}

		else if (term == '+' || term == '-' || term == '\0')//add section to the left to sum, store previousplus location
		{

			if (previousPlus == start)
			{
				if (flag == 1) // flag is 1 if parenthesis exist
				{
					goback(expr, current);
					advance(expr, previousPlus);
					flag = 0;
				}
				goback(expr, current);
				sum += mult(expr, previousPlus, current);
				advance(expr, current);
				advance(expr, current);
				previousPlus = current;
				goback(expr, current);
			}
			else
			{
				goback(expr, previousPlus);
				term = expr[previousPlus];
				advance(expr, previousPlus);
				if (flag == 1)
				{
					goback(expr, current);
					advance(expr, previousPlus);
				}
				goback(expr, current);
				if (term == '+')
					sum += mult(expr, previousPlus, current);
				if (term == '-')
					sum -= mult(expr, previousPlus, current);
				if (flag == 1)
				{
					flag = 0;
					advance(expr, current);
				}
				advance(expr, current);
				previousPlus = current;
				advance(expr, previousPlus);
				advance(expr, current);
			}
		}
		advance(expr, current);

	}// once no + are left in outer level
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