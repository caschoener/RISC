// Expression Tree Implementation File
// These functions manage an expression tree that describes
// arithmetic expressions using integer variables and values.
// Some functions construct a tree from a character string that
// represents the expression, and then the tree can be traversed
// and evaluated.
#include <iostream>
#include <sstream>
using namespace std;
#include "exprtree.h"
#include "tokenlist.h"

// Outputting any tree node will simply output its string version
ostream& operator<<(ostream &stream, const ExprNode &e)
{
	return stream << e.toString();
}

// A Value is just an integer value -- easy to evaluate
// Unfortunately, the string class does not have a constructor for it
string Value::toString() const
{
	ostringstream convert;	// output string stream
	convert << value;		// 'output' into the stream
	return convert.str();	// and extract its string equivalent
}

int Value::evaluate(VarTree &v, FunctionDef &funs) const
{
	return value;
}

//  A variable is just an alphabetic string -- easy to display
//  TO evaluate, would need to look it up in the data structure
string Variable::toString() const
{
	return name;
}

int Variable::evaluate(VarTree &v, FunctionDef &funs) const
{
	return v.lookup(name);
}

int Conditional::evaluate(VarTree &v, FunctionDef &funs) const
{
	if (test->evaluate(v, funs))
		return trueCase->evaluate(v, funs);
	else
		return falseCase->evaluate(v, funs);
}

string Conditional::toString() const
{
	string a = test->toString() + "?" + trueCase->toString() + ":" + falseCase->toString();
	return a;
}

int Operation::evaluate(VarTree &v, FunctionDef &funs) const
{
	if (oper == "=")
	{
		v.assign(left->toString(), right->evaluate(v, funs));
		return right->evaluate(v, funs);
	}
	if (oper == ">")
		return left->evaluate(v, funs) > right->evaluate(v, funs);
	if (oper == "<")
		return left->evaluate(v, funs) < right->evaluate(v, funs);
	if (oper == ">=")
		return left->evaluate(v, funs) >= right->evaluate(v, funs);
	if (oper == "<=")
		return left->evaluate(v, funs) <= right->evaluate(v, funs);
	if (oper == "==")
		return left->evaluate(v, funs) == right->evaluate(v, funs);
	if (oper == "!=")
		return left->evaluate(v, funs) != right->evaluate(v, funs);

	if (oper == "+")
		return left->evaluate(v, funs) + right->evaluate(v, funs);
	if (oper == "-")
		return left->evaluate(v, funs) - right->evaluate(v, funs);
	if (oper == "*")
		return left->evaluate(v, funs) * right->evaluate(v, funs);
	if (oper == "/")
		return left->evaluate(v, funs) / right->evaluate(v, funs);
	if (oper == "l-")
		return -(right->evaluate(v, funs));
	if (oper == "l!")
		return !(right->evaluate(v, funs));
	else // if oper == %
		return left->evaluate(v, funs) % right->evaluate(v, funs);

}

string Operation::toString() const
{
	string a;
	if (oper == "l-")
		a = "-" + right->toString();
	else if (oper == "l!")
		a = "!" + right->toString();
	else a = left->toString() + oper + right->toString();
	return a;
}

int Function::evaluate(VarTree &v, FunctionDef &funs) const
{
	int i = 0;
	FunDef def = funs.at(name);
	ExprNode * tester;
	while (def.parameter[i] != "")
	{
		def.locals->assign(def.parameter[i], (*(params + i))->evaluate(v, funs));
		i++;
	}
	return def.functionBody->evaluate(*def.locals, funs);
}

string Function::toString() const
{
	string a = name + '(';
	int i = 0;
	while (i < length)
	{
		a += (*(params + i))->toString();
		i++;
		if (i < length)
			a += ',';
	}
	a += ')';
	return a;
}