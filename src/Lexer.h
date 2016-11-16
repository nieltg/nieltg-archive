/*
 * Lexer.h by @nieltg
 */

#pragma once

#include <stdbool.h>

#define TOKEN_NAN  '?'
#define TOKEN_END  '!'

#define TOKEN_NUM  '0'

#define TOKEN_ADD  '+'
#define TOKEN_SUB  '-'
#define TOKEN_MUL  '*'
#define TOKEN_DIV  '/'

#define TOKEN_L_P  '('
#define TOKEN_R_P  ')'


typedef struct _Token  Token;
typedef struct _Lexer  Lexer;

struct _Token
{
	char type;

	double val;
};

struct _Lexer
{
	const char*  buf;

	size_t  pos;
	size_t  len;

	Token   tok;
};


#define Lexer_IsAvail(self)  ((self)->pos < (self)->len)
#define Lexer_IsEmpty(self)  (!Lexer_IsAvail(self))

#define Lexer_Char(self)     (self)->buf[(self)->pos]

#define Lexer_Token(self)    (self)->tok


// Constructor

void
Lexer_Create (Lexer*       self,
              const char*  text);


// Engine

bool
Lexer_Next (Lexer*  self);
