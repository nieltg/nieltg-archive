/*
 * Parser.c by @nieltg
 */

#define _GNU_SOURCE
#include <errno.h>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer.h"

#include "Parser.h"


// Constructor

void
Parser_Create (Parser*  self)
{
	assert (self != NULL);

	Parser_Value(self) = 0;
}


// Engine

static double
sum (Parser*  self);

static bool
accept (Parser*  self,
        char     tok_type,
		Token*   out)
{
	assert (self != NULL);

	Token* tok = &Lexer_Token(&self->lex);

	if (tok->type == tok_type)
	{
		if (out != NULL)
			*out = Lexer_Token(&self->lex);

		Lexer_Next (&self->lex);
		return true;
	}

	return false;
}

static void
expect (Parser*  self,
        char     tok_type,
		Token*   out)
{
	assert (self != NULL);

	if (!accept (self, tok_type, out))
	{
		fprintf (stderr, "%s: Parse: %s is expected, but got %s.\n",
		         program_invocation_short_name,
				 Token_Explain (tok_type),
				 Token_Explain (Lexer_Token(&self->lex).type));

		longjmp (self->jmp, 1);
	}
}

static double
value (Parser*  self)
{
	assert (self != NULL);

	double o;

	if (accept (self, TOKEN_L_P, NULL))
	{
		o = sum (self);
		expect (self, TOKEN_R_P, NULL);
	}
	else
	if (accept (self, TOKEN_SUB, NULL))
		o = -1 * value (self);
	else
	{
		Token tok;

		expect (self, TOKEN_NUM, &tok);
		o = tok.val;
	}

	return o;
}

static double
product (Parser*  self)
{
	assert (self != NULL);

	double a = value (self);
	double o = a;

	bool loop = true;

	while (loop)
	{
		if (accept (self, TOKEN_MUL, NULL))
			o *= value (self);
		else
		if (accept (self, TOKEN_DIV, NULL))
			o /= value (self);
		else
			loop = false;
	}

	return o;
}

static double
sum (Parser*  self)
{
	assert (self != NULL);

	double a = product (self);
	double o = a;

	bool loop = true;

	while (loop)
	{
		if (accept (self, TOKEN_ADD, NULL))
			o += product (self);
		else
		if (accept (self, TOKEN_SUB, NULL))
			o -= product (self);
		else
			loop = false;
	}

	return o;
}

static double
expr (Parser*  self)
{
	assert (self != NULL);

	double o = sum (self);
	expect (self, TOKEN_END, NULL);

	return o;
}

bool
Parser_Parse (Parser*      self,
              const char*  text)
{
	assert (self != NULL);
	assert (text != NULL);

	Lexer_Create (&self->lex, text);
	Lexer_Next (&self->lex);

	int val = setjmp (self->jmp);
	bool cn = (val == 0);

	if (cn)
		Parser_Value(self) = expr (self);

	return cn;
}
