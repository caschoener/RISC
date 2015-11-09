// evaluates with binary tree

using namespace std;
#include <iostream>
#include "tokenlist.h"
#include "token.h"
#include "exprtree.h"

//Each function calls the lower precedence function repeatedly while until it runs out of applicable operators
//Each time a lower precedence function is called, its operator is made the root, with the previous root as left child and result as right child

ExprNode * add(ListIterator &);
ExprNode * mult(ListIterator &); 
ExprNode * parens(ListIterator &);
ExprNode * equals(ListIterator &);
ExprNode * condit(ListIterator &);
ExprNode * relate(ListIterator &);


int evaluate(const char exin[], VarTree &vars)
{
	TokenList expr(exin), postfix, sum;
	ListIterator curr = expr.begin();
	ExprNode *tree;
	tree = equals(curr);

	cout << *tree << " : ";
	Token temp;

	return tree->evaluate(vars);
}

ExprNode * equals(ListIterator &curr)
{
	string oper;
	ExprNode * left = condit(curr);
	ExprNode * root = left;
	if (curr.tokenChar() == NULL)
		return root;
	oper = curr.tokenText();
	if (oper == "=")
	{
		curr.advance();
		ExprNode * right = condit(curr);
		root = new Operation(left, oper, right);
	}
	return root;
}
ExprNode * condit(ListIterator &curr)
{
	string oper;
	ExprNode * test = relate(curr);
	ExprNode * root = test;
	oper = curr.tokenChar();
	if (oper == "?")
	{
		curr.advance();
		ExprNode * left = relate(curr);
		curr.advance();
		ExprNode * right = relate(curr);
		root = new Conditional(test, left, right);
	}
	return root;
}
ExprNode * relate(ListIterator &curr)
{
	string oper;
	ExprNode * left = add(curr);
	ExprNode * root = left;
	if (curr.tokenChar() == NULL)
		return root;
	oper = curr.tokenText();
	if (oper == ">" || oper == "<" || oper == ">=" || oper == "<=" || oper == "==" || oper == "!=")
	{
		curr.advance();
		ExprNode * right = add(curr);
		root = new Operation(left, oper, right);
	}
	return root;
}

ExprNode * add(ListIterator &curr)
{
	string oper;
	ExprNode * root;
	root = mult(curr);
	oper = curr.tokenChar();
	while (oper == "+" || oper == "-")
	{
		curr.advance();
		ExprNode * right = mult(curr);
		root = new Operation(root, oper, right);
		oper = curr.tokenChar();
	}
	return root;
}
//mult
//called by add, multiplies all terms until it reaches a +,-, or )
//calls paren to find value of terms which are multiplied together
ExprNode * mult(ListIterator &curr)
{
	string oper;
	ExprNode * root = parens(curr);
	oper = curr.tokenChar();
	while (oper == "*" || oper == "/" || oper == "%")
	{
		curr.advance();
		ExprNode * right = mult(curr);
		root = new Operation(root, oper, right);
		oper = curr.tokenChar();
	}
	return root;
}

//paren
//called by mult, finds value of chunk inside operators
//returns either standalone integer or calls add to find value of expression inside ( )
ExprNode * parens(ListIterator &curr)
{
	ExprNode * root;
	if (curr.currentIsInteger())
	{
		root = new Value(curr.integerValue());
		curr.advance();
	}
	else if (curr.currentIsVar())
	{
		root = new Variable(curr.tokenText());
		curr.advance();
	}
	else
	{
		curr.advance();
		root = equals(curr);
		curr.advance();
	}
	return root;
}
