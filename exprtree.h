//  Expression Tree Header File
//  Describes the elements of an expression tree, using
//  derived classes to represent polymorphism.
//  All objects in this structure are immutable --
//  once constructed, they are never changed.
//  They only be displayed or evaluated.
#include <iostream>
using namespace std;
#include "vartree.h"
#include "funmap.h"
#include "machine.h"
class ExprNode
{
public:
	friend ostream& operator<<(ostream&, const ExprNode &);
	virtual string toString() const = 0;	// facilitates << operator
	virtual void compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const = 0;  // evaluate this node
};
class Value : public ExprNode
{
private:
	int value;
public:
	string toString() const;	// facilitates << operator
	void compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const;
	Value(int v)
	{
		value = v;
	}
};

class Variable : public ExprNode
{
private:
	string name;
public:
	string toString() const;	// facilitates << operator
	void compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const;
	Variable(string var)
	{
		name = var;
	}
};

class Operation : public ExprNode
{
private:
	string oper;
	ExprNode *left, *right;	 // operands
public:
	string toString() const;	// facilitates << operator
	void compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const;
	Operation(ExprNode *l, string o, ExprNode *r)
	{
		left = l;
		right = r;
		oper = o;
	}
};

class Conditional : public ExprNode
{
private:
	ExprNode *test, *trueCase, *falseCase;
public:
	string toString() const;	// facilitates << operator
	void compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const;
	Conditional(ExprNode *b, ExprNode *t, ExprNode *f)
	{
		test = b;
		trueCase = t;
		falseCase = f;
	}
};

class Function : public ExprNode
{
private:
	string name;
	ExprNode *params[10];
	int length; //number of parameters, used for tostring
public:
	string toString() const;
	void compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const;
	Function(string n, ExprNode *inparams[], int len)
	{
		length = len;
		while (len >= 0)
		{
			params[len] = inparams[len];
			len--;
		}
		name = n;
	}
};