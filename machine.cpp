// Machine Implementation File
// This implementation represents a simple machine that can evaluate
// arithmetic expressions.  In addition to the expected arithmetic
// operations, it includes relational operations and branching
// for the conditional operator, and simple support for function calls.
//
// The machine is expected to have a pre-allocated stack space
// for named variables and an arbitrarily long list of temporary
// registers, both represented by integer arrays here (to hold values).
// The machine also has a separate memory area holding all of the
// instructions defined below.

#include <iostream>
#include <sstream>
using namespace std;

#include "machine.h"

ostream& operator<<( ostream &stream, const Instruction &i )
{
    return stream << i.toString();
}

//  Here follow implementations of toString() and execute()
//  for all of the derived classes of the Instruction.

string Var::toString() const
{
	return to_string(stackLocation) + "Var ->" + to_string(valueTemp) ;
}
string Assign::toString() const
{
	return to_string(tempsloc) + "assign ->"  + to_string(stackLocation);
}

string Print::toString() const
{
	return "Print" + to_string(valueTemp);
}

string Compute::toString() const
{
	return to_string(a) + oper + to_string(b);
}

string Val::toString() const
{
	return to_string(value) + "val ->" + to_string(valueTemp);
}



void Print::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	cout << temps[valueTemp] << endl;
}


void Val::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	temps[valueTemp] = value;
}

void Assign::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	temps[valueTemp] = temps[tempsloc];
	stack[stackPointer + stackLocation] = tempsloc;
}

void Var::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	temps[valueTemp] = temps[stack[stackPointer + stackLocation]];
}

//Compute children

void Add::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	temps[valueTemp] = temps[a] + temps[b];
}
void Sub::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	temps[valueTemp] = temps[a] - temps[b];
}

void Mult::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	temps[valueTemp] = temps[a] * temps[b];
}
void Div::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	temps[valueTemp] = temps[a] / temps[b];
}

void Mod::execute(int temps[], int stack[], int &stackPointer, int &programCounter) const
{
	temps[valueTemp] = temps[a] % temps[b];
}

//Comparatives