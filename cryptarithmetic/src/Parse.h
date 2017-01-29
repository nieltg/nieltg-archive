/*
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Wed Jan 19 2017
 * Topik     : Bruteforce
 * Deskripsi : Cryptarithmetic
 */

#pragma once

#include <stdexcept>
#include <iostream>

class Parse
{
public:
	static const size_t MAX_LENGTH = 1000;
	
	enum class Type
	{ ADDEND, SUM, END };
	
	class Token;
	
	Parse (std::istream& i) : is_sum_tokn (false), in (i) {}
	
	Token next (void) throw (std::underflow_error);
	
private:
	bool is_sum_tokn;
	std::istream& in;
};

class Parse::Token
{
public:
	const Parse::Type type;
	const std::string text;
	
	Token (Parse::Type a, std::string b) : type (a), text (b) {}
};
