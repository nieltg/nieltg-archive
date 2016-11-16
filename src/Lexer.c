/*
 * Lexer.c by @nieltg
 */

#define _GNU_SOURCE
#include <errno.h>

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Lexer.h"


// Constructor

void
Lexer_Create (Lexer*       self,
              const char*  text)
{
	assert (self != NULL);
	assert (text != NULL);

	self->buf = text;

	self->pos = 0;
	self->len = strlen (text);

	self->tok.type = TOKEN_NAN;
	self->tok.val = 0;
}


// Engine

static void
_Lexer_SkipBlank (Lexer*  self)
{
	assert (self != NULL);

	bool loop = true;

	while (loop && Lexer_IsAvail(self))
	{
		if (isblank (Lexer_Char(self)) || Lexer_Char(self) == '\n')
			self->pos++;
		else
			loop = false;
	}
}

static void
_Lexer_SkipDigit (Lexer*  self)
{
	assert (self != NULL);

	bool loop = true;

	while (loop && Lexer_IsAvail(self))
	{
		if (isdigit (Lexer_Char(self)))
			self->pos++;
		else
			loop = false;
	}
}

static void
_Lexer_ParseDigit (Lexer*  self)
{
	assert (self != NULL);

	size_t cp = self->pos;
	bool ival = false;

	_Lexer_SkipDigit (self);

	if (Lexer_IsAvail(self))
	{
		if (Lexer_Char(self) == '.')
		{
			size_t np = ++self->pos;

			_Lexer_SkipDigit (self);

			if (np == self->pos)
			{
				fprintf (stderr, "%s: Lex warning: Invalid number format\n",
				         program_invocation_short_name);

				ival = true;
			}
		}
	}

	if (ival)
		self->tok.type = TOKEN_NAN;
	else
	{
		char *dummy;

		self->tok.type = TOKEN_NUM;
		self->tok.val = strtod (&self->buf[cp], &dummy);
	}

}

bool
Lexer_Next (Lexer*  self)
{
	assert (self != NULL);

	bool out = false;

	self->tok.type = TOKEN_NAN;
	self->tok.val = 0;

	_Lexer_SkipBlank (self);

	if (Lexer_IsAvail(self))
	{
		char ch = Lexer_Char(self);

		switch (ch)
		{
		case TOKEN_ADD:
		case TOKEN_SUB:
		case TOKEN_MUL:
		case TOKEN_DIV:
		case TOKEN_L_P:
		case TOKEN_R_P:
			self->tok.type = ch;
			self->pos++;
			break;

		default:
			if ((ch == '.') || isdigit (ch))
				_Lexer_ParseDigit (self);
			else
			{
				if (isprint (ch))
					fprintf (stderr, "%s: Lex warning: Unknown token: %c\n",
					         program_invocation_short_name, ch);
				else
					fprintf (stderr, "%s: Lex warning: Unknown token: \\x%x\n",
					         program_invocation_short_name, ch);

				self->pos++;
			}

			break;
		}

		out = true;
	}
	else
		self->tok.type = TOKEN_END;

	return out;
}

const char*
Token_Explain (char  tok_type)
{
	switch (tok_type)
	{
	case TOKEN_NAN:
		return "TOKEN_NAN";

	case TOKEN_END:
		return "TOKEN_END";

	case TOKEN_NUM:
		return "TOKEN_NUM";

	case TOKEN_ADD:
		return "TOKEN_ADD";

	case TOKEN_SUB:
		return "TOKEN_SUB";

	case TOKEN_MUL:
		return "TOKEN_MUL";

	case TOKEN_DIV:
		return "TOKEN_DIV";

	case TOKEN_L_P:
		return "TOKEN_L_P";

	case TOKEN_R_P:
		return "TOKEN_R_P";
	}

	return "(invalid)";
}
