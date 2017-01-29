/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "common.h"

#include "dfa.h"

// DFA

struct _dfa_t
{
	bool is_dirty;
	size_t n_syms;
	
	vector_t * data;
};

dfa_t *
dfa_alloc (size_t n_syms)
{
	dfa_t * self = (dfa_t *) malloc (sizeof (dfa_t));
	
	self->n_syms = n_syms;
	self->is_dirty = false;
	
	self->data = vector_alloc (sizeof (size_t) * n_syms);
	
	return self;
}

void
dfa_set (dfa_t * self, size_t state_id, size_t * dest)
{
	assert (self != NULL);
	assert (dest != NULL);
	
	size_t cap = sizeof (size_t) * self->n_syms;
	
	size_t * buf = (size_t *) malloc (cap);
	memcpy (buf, dest, cap);
	
	vector(self->data, state_id, size_t *) = buf;
	
	// Enlarge vector for validation
	
	self->is_dirty = true;
	
	size_t max_id = 0;
	
	for (size_t i = 0; i < self->n_syms; i++)
		if (dest[i] > max_id) max_id = dest[i];
	
	vector_id (self->data, max_id);
}

size_t
dfa_get (dfa_t * self, size_t state_id, size_t sym_id)
{
	assert (self != NULL);
	assert (state_id < dfa_get_n_state (self));
	assert (sym_id < dfa_get_n_symbol (self));
	
	size_t * sym = vector(self->data, state_id, size_t *);
	assert (sym != NULL);
	
	return sym[sym_id];
}

size_t
dfa_get_n_state (dfa_t * self)
{
	assert (self != NULL);
	
	return vector_get_size (self->data);
}

size_t
dfa_get_n_symbol (dfa_t * self)
{
	assert (self != NULL);
	
	return self->n_syms;
}

bool
dfa_verify (dfa_t * self)
{
	assert (self != NULL);
	
	size_t len = vector_get_size (self->data);
	size_t i = 0;
	
	bool out = true;
	
	while ((i < len) && out)
	{
		if (vector(self->data, i, size_t *) == NULL)
			out = false;
		else
			i++;
	}
	
	self->is_dirty = !out;
	return out;
}

static void
dfa_free_elmts (dfa_t * self)
{
	assert (self != NULL);
	assert (self->data != NULL);
	
	size_t len = vector_get_size (self->data);
	
	for (size_t i = 0; i < len; i++)
	{
		size_t ** elmt = vector_id (self->data, i);
		
		free (*elmt);
		*elmt = NULL;
	}
}

void
dfa_free (dfa_t * self)
{
	if (self != NULL)
	{
		if (self->data != NULL)
		{
			dfa_free_elmts (self);
			vector_clean (&self->data);
		}
		
		free (self);
	}
}

void
dfa_clean (dfa_t ** self)
{
	assert (self != NULL);
	
	dfa_free (*self);
	*self = NULL;
}

// DFA Exec

struct _dfa_exec_t
{
	size_t state;
	
	dfa_t * dfa;
};

dfa_exec_t *
dfa_exec_alloc (dfa_t * dfa, size_t initial)
{
	assert (dfa != NULL);
	assert (!dfa->is_dirty);
	assert (initial < dfa_get_n_state (dfa));
	
	dfa_exec_t * self = (dfa_exec_t *) malloc (sizeof (dfa_exec_t));
	
	self->dfa = dfa;
	self->state = initial;
	
	return self;
}

void
dfa_exec_push (dfa_exec_t * self, size_t sym_id)
{
	assert (self != NULL);
	assert (sym_id < dfa_get_n_symbol (self->dfa));
	
	self->state = dfa_get (self->dfa, self->state, sym_id);
}

size_t
dfa_exec_get_state (dfa_exec_t * self)
{
	assert (self != NULL);
	
	return self->state;
}

void
dfa_exec_free (dfa_exec_t * self)
{
	if (self != NULL)
	{
		self->dfa = NULL;
		
		free (self);
	}
}

void
dfa_exec_clean (dfa_exec_t ** self)
{
	assert (self != NULL);
	
	dfa_exec_free (*self);
	*self = NULL;
}

