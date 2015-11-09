// Token List Implementation file
// Not a true linked list; just support for iterators
#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;
#include "tokenlist.h"

//  output operation
//  Display all of the tokens in the list
//  Parameters:
//  	stream	(modified output stream)	where to output to
//	t	(input reference to TokenList)	what to output
//  Returns:
//  	output stream, for use by additional << operators
ostream& operator<<( ostream &stream, TokenList &t )
{
    for (ListIterator iter = t.begin(); iter != t.end(); iter.advance() )
    {
	if (iter.currentIsInteger())		// output a number
	    stream << iter.integerValue() << " ";
	else					// output a character
	    stream << iter.tokenChar() << " ";
    }
    return stream;
}

//  begin
//  Creates an iterator to refer to the beginning of the data
//  HINT:  This does the same thing as "findFirstToken"
ListIterator TokenList::begin()
{
    int pos = 0;
	while (data[pos] == ' ')
	{
		pos += 1;
	}

    return ListIterator( this, &data[pos] );
}

//  end
//  Creates an iterator to refer to the end of the data
//  The end is indicated by a null character in the array.
ListIterator TokenList::end()
{
    return ListIterator( this, &data[strlen(data)] );
}

//  advance
//  moves the iterator to the next token
//  (indicated by a non-space character)
//  NOTE:  The current token could have been a number with multiple digits
void ListIterator::advance()	
{
	curr += 1;
	while (currentIsInteger()) // if token is integer, advance until it no longer is
	{
		curr += 1;
	}
	while (tokenChar() == ' ')
		curr += 1;

}

void ListIterator::retreat()
{
	curr -= 1;
	while (isdigit(*(curr-1))) // if token is integer, return to first
	{
		curr -= 1;
	}
	while (tokenChar() == ' ')
		curr -= 1;
}
