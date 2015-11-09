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

// TokenList constructor
// converts a character string into a list of tokens
// Parameter:
// 	expr	(input char pointer)	// string to examine
// Pre-condition:  str may not be a null pointer
//     and is assumed to actually point at a valid expression.
TokenList::TokenList( const char expr[])
{
    head = NULL;			// clear these here too
    tail = NULL;
	head = new ListElement;
	int i = 0;
	ListElement *iter;
	iter = head;
	while (expr[i] == ' ')
		i++;
	if (isdigit(expr[i]))
		iter->token = expr[i] - 48;
	else
		iter->token = expr[i];
	while (expr[i+1] != NULL)
	{
		i++;
		if (expr[i] != ' ') // for each token in expression
		{
			iter->next = new ListElement;
			iter = iter->next;
			if (isdigit(expr[i]))
				iter->token =  expr[i] - 48;
			else
				iter->token = expr[i];
		}
	}
	tail = iter;
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
