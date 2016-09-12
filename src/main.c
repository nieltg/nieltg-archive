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

static char *
take_flag (char * flag)
{
	char afl = 0;
	char * out = NULL;
	
	if (*flag & FLAG_INITIAL)
	{
		afl = FLAG_INITIAL;
		out = "initial";
	}
	else
	if (*flag & FLAG_FINAL)
	{
		afl = FLAG_FINAL;
		out = "final";
	}
	
	*flag &= ~afl;
	return out;
}

static void
print_state (parse_t * parse, size_t cs)
{
	printf ("%s", parse_get_state (parse, cs));
	
	char flags = parse_get_flags (parse, cs);
	
	if (flags != 0)
	{
		char * str;
		printf (" (");
		
		if ((str = take_flag (&flags)) != NULL)
			printf ("%s", str);
		
		while ((str = take_flag (&flags)) != NULL)
			printf (", %s", str);
		
		printf (")");
	}
	
	printf ("\n");
}

static int
do_ask (size_t * id)
{
	printf ("N: ");
	return scanf ("%zu", id);
}

static void
do_program (parse_t * parse)
{
	size_t id;
	
	dfa_t * dfa = parse_get_dfa (parse);
	size_t fi = parse_get_first_id (parse);
	
	dfa_exec_t * dx = dfa_exec_alloc (dfa, fi);
	size_t cs = dfa_exec_get_state (dx);
	
	printf ("Initial: ");
	print_state (parse, cs);
	
	while (do_ask (&id) == 1)
	{
		dfa_exec_push (dx, id);
		cs = dfa_exec_get_state (dx);
		
		printf ("State: ", id);
		print_state (parse, cs);
	}
}

int
main (int argc, char ** argv)
{
	char * o_path;
	
	char opt_ch;
	bool opt_fail = false;
	
	while ((opt_ch = getopt (argc, argv, "i:")) != -1)
	{
		switch (opt_ch)
		{
		case 'i':
			o_path = optarg;
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
		fprintf (stderr, "Usage: %s -i DFA_FILE\n", argv[0]);
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
		parse_t * parse = parse_alloc ();
		
		parse_load (parse, handle);
		fclose (handle);
		
		do_program (parse);
	}
	
	return EXIT_SUCCESS;
}

