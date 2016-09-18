/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "common.h"

#include "parse.h"

// Parse

#define TOKEN_WS " \f\n\r\t\v"

struct _parse_t
{
	index_t * map_sym;
	index_t * map_state;
	
	char * flags;
	
	size_t first_id;
	bool first_id_nul;
	
	dfa_t * dfa;
};

parse_t *
parse_alloc (void)
{
	parse_t * self = (parse_t *) malloc (sizeof (parse_t));
	
	self->map_sym = NULL;
	self->map_state = NULL;
	self->flags = NULL;
	
	self->first_id = 0;
	self->first_id_nul = true;
	
	self->dfa = NULL;
	
	return self;
}

static void
process_sym (parse_t * self, char * buf)
{
	char * tok_buf;
	char * tok = strtok_r (buf, TOKEN_WS, &tok_buf);
	
	index_t * map = index_alloc ();
	
	while (tok != NULL)
	{
		index_get (map, tok);
		tok = strtok_r (NULL, TOKEN_WS, &tok_buf);
	}
	
	index_free (self->map_sym);
	self->map_sym = map;
}

static size_t
process_delta_row (char * buf, int n_max, char ** row)
{
	char * tok_buf;
	char * tok = strtok_r (buf, TOKEN_WS, &tok_buf);
	
	size_t i = 0;
	
	while (tok != NULL)
	{
		row[i++] = tok;
		
		tok = strtok_r (NULL, TOKEN_WS, &tok_buf);
		
		if (i >= n_max)
		{
			if (tok != NULL)
				fprintf (stderr, "%s: warning: Excess state detected\n",
				         program_invocation_short_name);
			
			tok = NULL;
		}
	}
	
	return i;
}

static void
process_delta (parse_t * self, index_t * db_id, vector_t * db_f, size_t * dst_b,
               char * attr, char * key, char ** dst)
{
	size_t key_id = index_get (db_id, key);
	unsigned char flags = 0;
	
	if (attr != NULL)
	{
		for (char * att_str = attr; *att_str != '\0'; att_str++)
		{
			switch (*att_str)
			{
			case '>':
				flags |= FLAG_INITIAL;
				
				if (self->first_id_nul)
				{
					self->first_id = key_id;
					self->first_id_nul = false;
				}
				else
					fprintf (stderr, "%s: warning: Ignoring 2nd initial flag\n",
					         program_invocation_short_name);
				break;
				
			case '*':
				flags |= FLAG_FINAL;
				break;
			
			default:
				fprintf (stderr, "%s: warning: Ignoring unknown attribute\n",
						 program_invocation_short_name);
			}
		}
	}
	
	size_t n_sym = index_get_size (self->map_sym);
	
	for (size_t i = 0; i < n_sym; i++)
		dst_b[i] = index_get (db_id, dst[i]);
	
	vector(db_f, key_id, char) = flags;
	dfa_set (self->dfa, key_id, dst_b);
}

void
parse_load (parse_t * self, FILE * input)
{
	assert (self != NULL);
	assert (input != NULL);
	
	size_t bsi = 0;
	char * buf = NULL;
	
	// Process symbols
	
	if (getline (&buf, &bsi, input) != -1)
		process_sym (self, buf);
	
	// Process deltas
	
	size_t n_sym = index_get_size (self->map_sym);
	
	dfa_free (self->dfa);
	self->dfa = dfa_alloc (n_sym);
	
	size_t n_par = n_sym + 1;
	size_t n_max = n_sym + 2;
	
	char ** row = (char **) malloc (n_max * sizeof (char *));
	size_t * ic = (size_t *) malloc (n_sym * sizeof (size_t));
	
	index_t * db_id = index_alloc ();
	vector_t * db_flag = vector_alloc (sizeof (char));
	
	while (getline (&buf, &bsi, input) != -1)
	{
		size_t n = process_delta_row (buf, n_max, row);
		
		if (n == n_par)
			process_delta (self, db_id, db_flag, ic, NULL, row[0], &row[1]);
		else
		if (n == n_max)
			process_delta (self, db_id, db_flag, ic, row[0], row[1], &row[2]);
		else
		if (n != 0)
			fprintf (stderr, "%s: warning: Ignoring incompatible data in row\n",
			         program_invocation_short_name);
	}
	
	index_free (self->map_state);
	self->map_state = db_id;
	
	self->flags = (char *) vector_release (db_flag);
	vector_clean (&db_flag);
	
	free (row);
	free (ic);
}

size_t
parse_get_first_id (parse_t * self)
{
	assert (self != NULL);
	
	return self->first_id;
}

char
parse_get_flags (parse_t * self, size_t id)
{
	assert (self != NULL);
	assert (id < index_get_size (self->map_state));
	
	return self->flags[id];
}

size_t
parse_get_n_state (parse_t * self)
{
	assert (self != NULL);
	
	return self->n_state;
}

char *
parse_get_state (parse_t * self, size_t id)
{
	assert (self != NULL);
	assert (id < index_get_size (self->map_state));
	
	return index_get_by_id (self->map_state, id);
}

size_t
parse_get_n_symbol (parse_t * self)
{
	assert (self != NULL);
	
	return index_get_size (self->map_sym);
}

char *
parse_get_symbol (parse_t * self, size_t id)
{
	assert (self != NULL);
	assert (id < index_get_size (self->map_sym));
	
	return index_get_by_id (self->map_sym, id);
}

bool
parse_get_symbol_id (parse_t * self, char * value, size_t * id)
{
	assert (self != NULL);
	assert (value != NULL);
	
	return index_peek (self->map_sym, value, id);
}

dfa_t *
parse_get_dfa (parse_t * self)
{
	assert (self != NULL);
	
	return self->dfa;
}

void
parse_free (parse_t * self)
{
	if (self != NULL)
	{
		index_clean (&self->map_sym);
		index_clean (&self->map_state);
		
		free (self->flags);
		self->flags = NULL;
		
		dfa_clean (&self->dfa);
		
		free (self);
	}
}

void
parse_clean (parse_t ** self)
{
	assert (self != NULL);
	
	parse_free (*self);
	*self = NULL;
}

