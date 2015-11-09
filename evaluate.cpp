// evaluates with binary tree

using namespace std;
#include <iostream>
#include "tokenlist.h"
#include "token.h"
#include "exprtree.h"
#include "funmap.h"

//Each function calls the lower precedence function repeatedly while until it runs out of applicable operators
//Each time a lower precedence function is called, its operator is made the root, with the previous root as left child and result as right child

ExprNode * add(ListIterator &);
ExprNode * mult(ListIterator &);
ExprNode * parens(ListIterator &);
ExprNode * equals(ListIterator &);
ExprNode * condit(ListIterator &);
ExprNode * relate(ListIterator &);
void compile(const char expr[], VarTree &vars, FunctionDef &funs,
	Instruction *prog[], int &pBegin, int &pEnd);



void compile(const char exin[], VarTree &vars, FunctionDef &funs,
	Instruction *prog[], int &pBegin, int &pEnd, int &regL)
{
	TokenList expr(exin);
	ExprNode *tree;
	ListIterator curr = expr.begin();
	if (curr.tokenText() == "deffn")
	{
		curr.advance();
		string name = curr.tokenText();
		funs[name].name = name; // lol
		int i = 0;
		curr.advance();
		while (curr.tokenText() != ")")
		{
			curr.advance();
			funs[name].parameter[i] = curr.tokenText();
			curr.advance();
			i++;
		}
		curr.advance();
		curr.advance();
		funs[name].functionBody = equals(curr);
		funs[name].locals = new VarTree;
	}

	tree = equals(curr);
	tree->compile(vars, funs, prog, pBegin, pEnd, regL);
	prog[pEnd] = new Print(regL - 1);
	pEnd++;
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
	ExprNode * right;
	if (curr.tokenText() == "-")
	{
		curr.advance();
		right = mult(curr);
		root = new Operation(NULL, "l-", right);
	}
	else if (curr.tokenText() == "!")
	{
		curr.advance();
		right = mult(curr);
		root = new Operation(NULL, "l!", right);
	}
	else
		root = mult(curr);
	oper = curr.tokenChar();
	while (oper == "+" || oper == "-")
	{
		curr.advance();
		right = mult(curr);
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
		string name = curr.tokenText();
		curr.advance();
		if (curr.tokenText() == "(") // if is function call
		{
			ExprNode *params[10];
			int i = 0;
			while (curr.tokenText() != ")")
			{
				curr.advance();
				params[i] = equals(curr);
				i++;
			}
			root = new Function(name, params, i);
			curr.advance(); //past )
		}
		else
		{
			root = new Variable(name);
		}
	}
	else
	{
		curr.advance();
		root = equals(curr);
		curr.advance();
	}
	return root;
}