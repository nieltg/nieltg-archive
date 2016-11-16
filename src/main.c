#include <stdlib.h>
#include <stdio.h>

#include "Lexer.h"

void
do_calc (char*  buf)
{
	Lexer parse;
	Lexer_Create (&parse, buf);
	
	bool loop = true;
	
	while (loop && Lexer_Next (&parse))
	{
		Token* tok = &Lexer_Token(&parse);
		
		if (tok->type == TOKEN_NAN)
			loop = false;
		else
		{
			printf ("Token %c\n", tok->type);
			printf (" val: %lf\n", tok->val);
		}
	}
}

int
main (void)
{
	char* buf = NULL;
	size_t si;
	
	puts ("Calculator v0.1");
	puts ("By: 13515002 Wenny, 13515071 Daniel\n");
	
	printf ("> ");
	
	if (getline (&buf, &si, stdin) != -1)
		do_calc (buf);
	
	free (buf);
}
