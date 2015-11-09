// Token List Implementation file
//
// This tokenizer will scan a character string representing
// an expression, and will return a list of tokens.
// --- only integers and operators are supported (no names)

// The standard C library has some useful functions for us
#include <string.h>
#include <ctype.h>

// And to get the definition of a token:
#include "tokenlist.h"
bool isOperator(const char *&str)
{
	if ((*str == '+' || *str == '-' || *str == '%' || *str == '*'
		|| *str == '/' || *str == '(' || *str == ')' || *str == '=' 
		|| *str == '>' || *str == '<' || *str == '!') || *str == ':' || *str == '?' || *str == ',')
		return 1;
	else
		return 0;
}
void getToken(const char *&str, Token &token)
{
	string temp;			// temporary text to work with

	while (*str == ' ')			// skip any spaces
		str++;

	if (*str == NULL)			// at end of string
	{
		token = Token();
	}
	else if (isdigit(*str))
	{
		token = Token(atoi(str));		// convert to integer
		while (isdigit(*str))
			str++;			// scan past the intie
	}
	else if (isOperator(str))
	{
		temp = *str;
		str++;
		if (*str == '=')
		{
			temp += *str;
			str++;
		}
		token = Token(temp);
	}
	else
	{
		while (!isdigit(*(str))&&!(*(str) == ' ')&&!isOperator(str)&&!(*str == NULL))
		{
			temp += *str;
			str++;
		}
		token = Token(temp);
	}
}

// TokenList constructor
// converts a character string into a list of tokens
// Parameter:
// 	expr	(input char pointer)	// string to examine
// Pre-condition:  str may not be a null pointer
//     and is assumed to actually point at a valid expression.
TokenList::TokenList(const char expr[])
{
	head = NULL;			// clear these here too
	tail = NULL;
	Token current;
	const char *str = expr;		// a copy of the pointer to work with
	getToken(str, current);		// get the first token
	while (!current.isNull())
	{
		push_back(current);
		getToken(str, current);	// get another token
	}
	if (tail != NULL) // tail gets formatted wrong if - is in front, too lazy to figure out why
		tail->next = NULL;
}

//  output operation
//  Display all of the tokens in the list
ostream& operator<<( ostream &stream, TokenList &t )
{
    for (ListIterator iter = t.begin(); iter != t.end(); iter.advance())
    {
	stream << iter.token() << " ";
    }
    return stream;
}

//  Creates an iterator to refer to the beginning of the list
ListIterator TokenList::begin()
{
    return ListIterator( this, head );
}

//  Creates an iterator to refer after the end of the list
//  This list is simple:  it ends with NULL
ListIterator TokenList::end()
{
    return ListIterator( this, NULL );
}

//  Add a new element to the back of the list
//  Parameter:
//       t	(input Token)	the new item to add
void TokenList::push_back(Token t)
{
	if (head == NULL)
	{
		head = new ListElement;
		head->token = t;
		head->next = tail;
	}
	else if (tail == NULL)
	{
		tail = new ListElement;
		tail->token = t;
		head->next = tail;
	}
	else
	{
		tail->next = new ListElement;
		tail = tail->next;
		tail->token = t;
		tail->next = NULL;
	}
}

//  Add a new element to the front of the list
//  Parameter:
//       t	(input Token)	the new item to add
void TokenList::push_front(Token t)
{
	ListElement *temp;
	temp = new ListElement;
	temp->next = head;
	temp->token = t;
	head = temp;

}

//  Remove and return the element at the front of the list
Token TokenList::pop_front()
{
	if (head == NULL)
		return '/0';
	ListElement *temp;
	temp = head;
	head = head->next;

	return temp->token;
}
