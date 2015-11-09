// evaluates with postfix

using namespace std;
#include <iostream>
#include "tokenlist.h"
#include "token.h"

void add(ListIterator &, TokenList &);
void mult(ListIterator &, TokenList &);
void parens(ListIterator &, TokenList &);



int evaluate(const char exin[])
{
	TokenList expr(exin), postfix, sum;
	ListIterator curr = expr.begin();

	add(curr, postfix);
	cout << "infix version:  " << postfix << '/n';
	Token temp;
	while (!postfix.empty())
	{
		temp = postfix.pop_front();
		if (temp.isInteger())
		{
			sum.push_front(temp);
		}
		else
		{
			int a = sum.pop_front().integerValue();
			int b = sum.pop_front().integerValue();
			switch (temp.tokenChar()){
			case '+':
				sum.push_front(b + a);
				break;
			case '-':
				sum.push_front(b - a);
				break;
			case '*':
				sum.push_front(b*a);
				break;
			case '/':
				sum.push_front(b / a);
				break;
			case '%':
				sum.push_front(b % a);
				break;
			}
		}
	}

	return sum.pop_front().integerValue();
}

void add(ListIterator &curr, TokenList &postfix)
{
	char oper;
	mult(curr, postfix);
	oper = curr.tokenChar();
	while (oper == '+' || oper == '-')
	{
		curr.advance();
		mult(curr, postfix);
		postfix.push_back(oper);
		oper = curr.tokenChar();
	}
}
//mult
//called by add, multiplies all terms until it reaches a +,-, or )
//calls paren to find value of terms which are multiplied together
void mult(ListIterator &curr, TokenList &postfix)
{
	parens(curr,postfix);
	while (curr.tokenChar() == '*' || curr.tokenChar() == '/' || curr.tokenChar() == '%')
	{
		char tok = curr.tokenChar();
		curr.advance();
		parens(curr, postfix);
		postfix.push_back(tok);
	}
}

//paren
//called by mult, finds value of chunk inside operators
//returns either standalone integer or calls add to find value of expression inside ( )
void parens(ListIterator &curr, TokenList &postfix)
{

	if (curr.currentIsInteger())
	{
		postfix.push_back(curr.integerValue());
		curr.advance();
	}
	else
	{
		curr.advance();
		add(curr,postfix);
		curr.advance();
	}
}
