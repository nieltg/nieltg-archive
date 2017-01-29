#include <stdlib.h>
#include <stdio.h>

#include "Parser.h"

void
do_calc (const char*  buf)
{
	Parser parse;
	Parser_Create (&parse);
	
	if (Parser_Parse (&parse, buf))
		printf ("%f\n", Parser_Value(&parse));
	else
		printf ("SINTAK ERROR\n");
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
