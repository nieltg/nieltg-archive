/*
 * Parser.h by @nieltg
 */

#pragma once

#include <setjmp.h>
#include <stdbool.h>

#include "Lexer.h"


typedef struct _Parser  Parser;

struct _Parser
{
	Lexer   lex;
	jmp_buf jmp;

	double val;
};


// Selector


#define Parser_Value(self)  (self)->val

// Constructor

void
Parser_Create (Parser*  self);


// Engine

bool
Parser_Parse (Parser*      self,
              const char*  text);
