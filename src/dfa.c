/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#include "dfa.h"

// DFA Delta

struct _dfa_delta_priv_t
{
	size_t n_sym;
	size_t n_state;
}

dfa_delta_t *
dfa_delta_alloc (size_t nstates, size_t nsyms)
{
	dfa_delta_t * self =
		(dfa_delta_t *) malloc (sizeof (dfa_delta_t));
	
	dfa_delta_priv_t * priv =
		(dfa_delta_priv_t *) malloc (sizeof (dfa_delta_priv_t));
	
	self->_priv = priv;
	
	priv->n_sym = nsyms;
	priv->n_state = nstates;
	
	self->first_id = 0;
	self->delta = (size_t *) calloc (nstates * nsyms, sizeof (size_t));
	
	return self;
}

size_t
dfa_delta_get_states_count (dfa_delta_t * self)
{
	assert (self != NULL);
	assert (self->_priv != NULL);
	
	return self->_priv->n_state;
}

size_t
dfa_delta_get_symbols_count (dfa_delta_t * self)
{
	assert (self != NULL);
	assert (self->_priv != NULL);
	
	return self->_priv->n_sym;
}

void
dfa_delta_free (dfa_delta_t * self)
{
	if (self != NULL)
	{
		if (self->_priv != NULL)
		{
			free (self->_priv);
			self->priv = NULL;
		}
	
		if (self->delta != NULL)
		{
			free (self->delta);
			self->delta = NULL;
		}
		
		free (self);
	}
}

void
dfa_delta_clean (dfa_delta_t ** self)
{
	assert (self != NULL);
	
	dfa_delta_free (*self);
	*self = NULL;
}

// DFA

struct _dfa_t
{
	size_t state;
	
	dfa_delta_t * delta;
}

dfa_t *
dfa_alloc (dfa_delta_t * dt)
{
	assert (dt != NULL);
	
	dfa_t * self = (dfa_t *) malloc (sizeof (dfa_t));
	
	self->delta = dt;
	self->state = dfa_delta_first (dt);
}

void
dfa_push (dfa_t * self, size_t sym_id)
{
	assert (self != NULL);
	assert (sym_id < dfa_delta_get_symbols_count (self->delta));
	
	state = dfa_delta (self->delta, self->state, sym_id);
}

size_t
dfa_get_state (dfa_t * self)
{
	assert (self != NULL);
	
	return self->state;
}

void
dfa_free (dfa_t * self)
{
	if (self != NULL)
	{
		if (self->delta != NULL)
		{
			dfa_delta_free (self->delta);
			self->delta = NULL;
		}
		
		free (self);
	}
}

void
dfa_clean (dfa_t ** self)
{
	assert (self != NULL);
	
	dfa_delta_free (*self);
	*self = NULL;
}

