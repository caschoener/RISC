// Expression Tree Implementation File
// These functions manage an expression tree that describes
// arithmetic expressions using integer variables and values.
// Some functions construct a tree from a character string that
// represents the expression, and then the tree can be traversed
// and compiled.
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

//// A Value is just an integer value -- easy to compile
//// Unfortunately, the string class does not have a constructor for it
string Value::toString() const
{
	ostringstream convert;	// output string stream
	convert << value;		// 'output' into the stream
	return convert.str();	// and extract its string equivalent
}

void Value::compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const
{
	prog[pEnd] = new Val(regL, value);
	pEnd++;
	regL++;
}

//
////  A variable is just an alphabetic string -- easy to display
////  TO compile, would need to look it up in the data structure
string Variable::toString() const
{
	return name;
}

void Variable::compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const
{
	prog[pEnd] = new Var(regL, v.lookup(name));
	pEnd++;
	regL++;
}

void Conditional::compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const
{
	//if (test->compile(v, funs, prog))
	//	return trueCase->compile(v, funs, prog);
	//else
	//	return falseCase->compile(v, funs, prog);
}

string Conditional::toString() const
{
	string a = test->toString() + "?" + trueCase->toString() + ":" + falseCase->toString();
	return a;
}

void Operation::compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const
{
	if (oper == "=") //vartree now stores position in stack
	{
		int loc;
		int size = v.size();
		string name = left->toString();
		if (v.lookup(name) == 0)
		{
			v.assign(name, size);
			loc = size;
		}
		else
			loc = v.lookup(name); // loc is stack position
		right->compile(v, funs, prog, pBegin, pEnd, regL);
		prog[pEnd] = new Assign(regL,regL-1, loc);
	}
	else
	{
		left->compile(v, funs, prog, pBegin, pEnd, regL);
		int a = regL-1;
		right->compile(v, funs, prog, pBegin, pEnd, regL);
		int b = regL-1;
		//if (oper == ">")
		//	return left->compile(v, funs, prog) > right->compile(v, funs, prog);
		//if (oper == "<")
		//	return left->compile(v, funs, prog) < right->compile(v, funs, prog);
		//if (oper == ">=")
		//	return left->compile(v, funs, prog) >= right->compile(v, funs, prog);
		//if (oper == "<=")
		//	return left->compile(v, funs, prog) <= right->compile(v, funs, prog);
		//if (oper == "==")
		//	return left->compile(v, funs, prog) == right->compile(v, funs, prog);
		//if (oper == "!=")
		//	return left->compile(v, funs, prog) != right->compile(v, funs, prog);
		if (oper == "+")
			prog[pEnd] = new Add(regL, a,b);
		if (oper == "-")
			prog[pEnd] = new Sub(regL, a, b);
		if (oper == "*")
			prog[pEnd] = new Mult(regL, a,b);
		if (oper == "/")
			prog[pEnd] = new Div(regL, a, b);
	}
	pEnd++;
	regL++;
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

void Function::compile(VarTree &v, FunctionDef &funs, Instruction *prog[], int &pBegin, int &pEnd, int &regL) const
{
	//int i = 0;
	//FunDef def = funs.at(name);
	//ExprNode * tester;
	//while (def.parameter[i] != "")
	//{
	//	def.locals->assign(def.parameter[i], (*(params + i))->compile(v, funs, prog));
	//	i++;
	//}
	//return def.functionBody->compile(*def.locals, funs, prog);
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