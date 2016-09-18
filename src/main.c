/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "parse.h"
#include "dfa.h"

static void
print_syms (parse_t * parse)
{
	printf ("\nSymbols: ");
	
	size_t len = parse_get_n_symbol (parse);
	
	if (len > 0)
	{
		printf ("%s", parse_get_symbol (parse, 0));
		
		for (size_t i = 1; i < len; i++)
			printf (", %s", parse_get_symbol (parse, i));
	}
	else
		printf ("(no symbol)");
	
	printf ("\n");
}

static void
print_state (parse_t * parse, dfa_exec_t * dx)
{
	size_t c_s = dfa_exec_get_state (dx);
	char flags = parse_get_flags (parse, c_s);
	
	printf ("%s%s\n",
	        parse_get_state (parse, c_s),
	        (flags & FLAG_FINAL) ? " (final)" : "");
}

static void
do_symbol (parse_t * parse, dfa_exec_t * dx, unsigned int * cnt,
           char * tok)
{
	size_t id;
	
	if (parse_get_symbol_id (parse, tok, &id))
	{
		dfa_exec_push (dx, id);
		
		printf ("State [%u]: ", (*cnt)++);
		print_state (parse, dx);
	}
	else
		fprintf (stderr, "%s: warning: Unknown symbol: %s\n",
		         program_invocation_short_name, tok);
}

#define TOKEN_WS " \f\n\r\t\v"

static bool
do_single (parse_t * parse, dfa_exec_t * dx, unsigned int * cnt)
{
	bool out = false;
	
	char * buf = NULL;
	size_t len;
	
	printf ("\nAlphabet: ");
	
	if (getline (&buf, &len, stdin) != 0)
	{
		char * tok;
		char * tok_buf;
		
		tok = strtok_r (buf, TOKEN_WS, &tok_buf);
		
		if (tok != NULL)
		{
			do
			{
				do_symbol (parse, dx, cnt, tok);
				tok = strtok_r (NULL, TOKEN_WS, &tok_buf);
			}
			while (tok != NULL);
			
			out = true;
		}
	}
	
	return out;
}

int
main (int argc, char ** argv)
{
	bool success = false;
	
	char * o_path = NULL;
	bool o_cont = false;
	
	char opt_ch;
	bool opt_fail = false;
	
	while ((opt_ch = getopt (argc, argv, "i:c")) != -1)
	{
		switch (opt_ch)
		{
		case 'i':
			o_path = optarg;
			break;
			
		case 'c':
			o_cont = true;
			break;
			
		case '?':
			opt_fail = true;
			break;
			
		default:
			abort ();
		}
	}
	
	FILE * handle;
	
	if (opt_fail)
		fprintf (stderr, "Usage: %s -i DFA_FILE [-c]\n", argv[0]);
	else
	if (o_path == NULL)
		fprintf (stderr, "%s: No input DFA\n",
		         program_invocation_short_name);
	else
	if ((handle = fopen (o_path, "r")) == NULL)
		fprintf (stderr, "%s: Unable to open '%s': %s\n",
		         program_invocation_short_name, o_path, strerror (errno));
	else
	{
		puts ("DFAExec by Daniel Pintara (NIM: 13515071)");
		
		parse_t * parse = parse_alloc ();
		
		parse_load (parse, handle);
		fclose (handle);
		
		dfa_t * dfa = parse_get_dfa (parse);
		
		if (!dfa_verify (dfa))
			fprintf (stderr, "%s: DFA is incomplete\n", 
			         program_invocation_short_name);
		else
		{
			size_t fi = parse_get_first_id (parse);
			dfa_exec_t * dx = dfa_exec_alloc (dfa, fi);
			
			print_syms (parse);
			
			printf ("Initial: ");
			print_state (parse, dx);
			
			unsigned int cnt = 1;
			
			printf ("\n");
			printf ("Use space to separate symbols then press Enter\n");
			
			if (o_cont)
			{
				printf ("Press Enter twice (blank line) to quit program\n");
				
				while (do_single (parse, dx, &cnt));
			}
			else
				do_single (parse, dx, &cnt);
			
			dfa_exec_clean (&dx);
			success = true;
		}
	}
	
	return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}
