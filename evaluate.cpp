// evaluates with postfix

using namespace std;
#include <iostream>
#include "tokenlist.h"
#include "token.h"
#include "vartree.h"

void add(ListIterator &, TokenList &);
void mult(ListIterator &, TokenList &);
void parens(ListIterator &, TokenList &);
void equals(ListIterator &, TokenList &);




int evaluate(const char exin[], VarTree &vars)
{
	TokenList expr(exin), postfix, sum;
	ListIterator curr = expr.begin();
	equals(curr, postfix);
	Token temp;
	int a, b;
	while (!postfix.empty())
	{
		temp = postfix.pop_front();
		if (temp.isInteger() || temp.isVar())
		{
			sum.push_front(temp);
		}
		else
		{
			Token atok = sum.pop_front();
			Token btok = sum.pop_front();
			if (atok.isVar())
			{
				a = vars.lookup(atok.tokenText());
			}
			else
				a = atok.integerValue();
			if (btok.isVar())
			{
				b = vars.lookup(btok.tokenText());
			}
			else
				b = btok.integerValue();

			switch (temp.tokenChar()){
			case '=': 
				vars.assign(btok.tokenText(), a);
				sum.push_front(a);
				break;
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

void equals(ListIterator &curr, TokenList &postfix)
{
	char oper;
	add(curr, postfix);
	oper = curr.tokenChar();
	while (oper == '=')
	{
		curr.advance();
		add(curr, postfix);
		postfix.push_back(oper);
		oper = curr.tokenChar();
	}
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
	
	if (curr.currentIsInteger() || curr.currentIsVar())
	{
		postfix.push_back(curr.token());
		curr.advance();
	}
	else
	{
		curr.advance();
		equals(curr,postfix);
		curr.advance();
	}
}
