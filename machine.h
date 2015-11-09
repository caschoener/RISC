// A simple RISC machine
// This structure represents a simple machine that can evaluate
// arithmetic expressions.  In addition to the expected arithmetic
// operations, it includes relational operations and branching
// for the conditional operator, and simple support for function calls.
//
// The machine is expected to have a pre-allocated stack space
// for named variables and an arbitrarily long list of temporary
// registers, both represented by integer arrays here (to hold values).
// The machine also has a separate memory area holding all of the
// instructions defined below.
//
// Most of these instructions are also immutable -- once constructed,
// they cannot be changed -- only displayed and executed.

#include <iostream>
using namespace std;

class Instruction
{
   protected:
	int valueTemp;		// register computed or tested
				// additional fields defined later
	Instruction( int temp )
	{
	    valueTemp = temp;
	}
   public:
	friend ostream& operator<<( ostream&, const Instruction & );
	virtual string toString() const = 0; // CHANGED from toString { }
	virtual void execute( int [], int [], int &, int &  ) const { } // temps, stack, stackPointer, programCounter
};


class Val : public Instruction // put value into register
{
private:
	int value;
public:
	string toString() const;
	void execute(int[], int[], int &, int &) const;
	Val(int temp, int num) : Instruction(temp) {
		value = num;
	}
};

class Var : public Instruction
{
private:
	int stackLocation;
public:
	string toString() const;
	void execute(int[], int[], int &, int &) const;
	Var(int temp, int loc) : Instruction(temp) {
		stackLocation = loc;
	}

};
class Assign : public Instruction // put value into register
{
private:
	int tempsloc;
	int stackLocation;
public:
	string toString() const;
	void execute(int[], int[], int &, int &) const;
	Assign(int temp, int num, int loc) : Instruction(temp) {
		tempsloc = num;
		stackLocation = loc;
	}
};




class Print: public Instruction
{
   public:
	string toString() const;
	void execute( int [], int [], int &, int & ) const;
	Print( int temp ) : Instruction(temp) { }
};

// also, as was pointed out in the assignment description,
// all of the arithmetic instructions are very simple and can
// be made children of a more general class (not defined here yet)
// All that is declared here is a new override to the execute method,
// and a constructor that simply calls the constructor for Compute,
// passing along all three relevant registers and the addition symbol.

class Compute : public Instruction
{
private:
	string oper;
protected:
	int a,b;
public:
	string toString() const;
	Compute(int result, int argA, int argB, string operr) :
		Instruction(result)
	{
		b = argA;
		a = argB;
		oper = operr;
	}
	virtual void execute(int[], int[], int &, int &) const {}
};

class Add: public Compute
{
   public:
	void execute( int [], int [], int &, int & ) const;
	Add( int result, int argA, int argB ) : 
		Compute(result, argA, argB, "+") { }
	};

class Sub : public Compute
{
public:
	void execute(int[], int[], int &, int &) const;
	Sub(int result, int argA, int argB) :
		Compute(result, argA, argB, "-") { }
};

class Mult : public Compute
{
public:
	void execute(int[], int[], int &, int &) const;
	Mult(int result, int argA, int argB) :
		Compute(result, argA, argB, "*") { }
};

class Div : public Compute
{
public:
	void execute(int[], int[], int &, int &) const;
	Div(int result, int argA, int argB) :
		Compute(result, argA, argB, "/") { }
};

class Mod : public Compute
{
public:
	void execute(int[], int[], int &, int &) const;
	Mod(int result, int argA, int argB) :
		Compute(result, argA, argB, "%") { }
};

//TODO Comparatives