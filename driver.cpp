#include <iostream>
using namespace std;
#include "evaluate.h"
int main()
{
	char userInput[80];
	VarTree vars;		// initially empty tree


	cout <<evaluate("Five = 2 + 3", vars) << endl;
	cout <<evaluate(" Five * 4 ", vars) << endl;
	cout <<evaluate("Age = 2+3*Five", vars) << endl;
	cout << vars;
	cout << endl << "Try one yourself:  ";
	cin.getline(userInput, 80);
	cout <<evaluate(userInput, vars) << endl;
	cout << endl << "Try another:  ";
	cin.getline(userInput, 80);
	cout<< evaluate(userInput, vars) << endl;
}