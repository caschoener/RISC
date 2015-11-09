#include <iostream>
using namespace std;
#include "evaluate.h"
int main()
{
	char userInput[80];
	while (1)
	{
		cin.getline(userInput, 80);
		cout << endl << evaluate(userInput) << endl;
	}
	return 0;
}


