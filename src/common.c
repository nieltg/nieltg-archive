/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "common.h"

// Vector

#define DEFAULT_INCREMENT  8

struct _vector_t
{
	size_t cap;
	size_t size;
	
	size_t elmt;
	size_t incr;
	
	void * data;
};

static void
vector_adjust (vector_t * self)
{
	assert (self != NULL);
	
	if (self->cap > 0)
		self->data = (void **) realloc (self->data, self->cap * self->elmt);
	else
		self->data = NULL;
}

vector_t *
vector_alloc (size_t elmt_size)
{
	vector_t * self = (vector_t *) malloc (sizeof (vector_t));
	
	self->elmt = elmt_size;
	self->incr = DEFAULT_INCREMENT;
	
	self->cap = 0;
	self->size = 0;
	self->data = NULL;
	
	return self;
}

size_t
vector_get_size (vector_t * self)
{
	assert (self != NULL);
	
	return self->size;
}

void * vector_id (vector_t * self, size_t id)
{
	assert (self != NULL);
	
	size_t nsi = id + 1;
	self->size = (nsi > self->size) ? nsi : self->size;
	
	if (self->size > self->cap)
	{
		self->cap = ((self->size / self->incr) + 1) * self->incr;
		vector_adjust (self);
	}
	
	return self->data + (self->elmt * id);
}

void vector_compact (vector_t * self)
{
	assert (self != NULL);
	
	if (self->cap != self->size)
	{
		self->cap = self->size;
		vector_adjust (self);
	}
}

void * vector_release (vector_t * self)
{
	assert (self != NULL);
	
	vector_compact (self);
	
	void * data = self->data;
	
	self->cap = 0;
	self->size = 0;
	self->data = NULL;
	
	return data;
}

void vector_free (vector_t * self)
{
	if (self != NULL)
	{
		free (self->data);
		self->data = NULL;
		
		free (self);
	}
}

void vector_clean (vector_t ** self)
{
	assert (self != NULL);
	
	vector_free (*self);
	*self = NULL;
}

// Index

#define DEFAULT_CAPACITY  32

struct _index_pair_t;
typedef struct _index_pair_t index_pair_t;

struct _index_pair_t
{
	size_t id;
	
	index_pair_t * next;
};

struct _index_t
{
	vector_t * data;
	
	size_t cap;
	index_pair_t ** index;
};

index_t *
index_alloc (void)
{
	index_t * self = (index_t *) malloc (sizeof (index_t));
	
	self->cap = DEFAULT_CAPACITY;
	self->index = (index_pair_t **) calloc (self->cap, sizeof (index_pair_t));
	
	self->data = vector_alloc (sizeof (char *));
	
	return self;
}

size_t
index_get_size (index_t * self)
{
	assert (self != NULL);
	
	return vector_get_size (self->data);
}

static index_pair_t *
index_alloc_pair (size_t id)
{
	index_pair_t * ip = (index_pair_t *) malloc (sizeof (index_pair_t));
	
	ip->id = id;
	ip->next = NULL;
	
	return ip;
}

static index_pair_t *
index_find_pair (index_t * self, size_t hash_val, char * value)
{
	assert (self != NULL);
	assert (value != NULL);
	
	index_pair_t * ip = self->index[hash_val];
	index_pair_t * it = NULL;
	bool loop = true;
	
	while ((ip != NULL) && loop)
	{
		char * src = vector(self->data, ip->id, char *);
		
		if (strcmp (src, value) == 0)
			loop = false;
		else
		{
			it = ip;
			ip = ip->next;
		}
	}
	
	if (loop)
	{
		size_t id = vector_get_size (self->data);
		vector(self->data, id, char *) = strdup (value);
		
		ip = index_alloc_pair (id);
		
		if (it == NULL)
			self->index[hash_val] = ip;
		else
			it->next = ip;
	}
	
	return ip;
}

static unsigned long
index_hash (char * str)
{
	unsigned long hash = 0xFF;
	unsigned char c;
	
	while ((c = (unsigned char) *(str++)))
	{
		hash = (hash << 2) + c;
	}
	
	return hash;
}

size_t
index_get (index_t * self, char * value)
{
	assert (self != NULL);
	assert (value != NULL);
	
	size_t hash_value = (size_t) (index_hash (value) % self->cap);
	index_pair_t * ip = index_find_pair (self, hash_value, value);
	
	return ip->id;
}

static void
index_free_pairs (index_t * self)
{
	assert (self != NULL);
	assert (self->index != NULL);
	
	for (size_t i = 0; i < self->cap; i++)
	{
		index_pair_t * ip = self->index[i];
	
		while (ip != NULL)
		{
			ip = ip->next;
			free (ip);
		}
		
		self->index[i] = NULL;
	}
}

char **
index_release (index_t * self)
{
	assert (self != NULL);
	
	char ** out = (char **) vector_release (self->data);
	index_free_pairs (self);
	
	return out;
}

void
index_free (index_t * self)
{
	if (self != NULL)
	{
		if (self->index != NULL)
		{
			index_free_pairs (self);
		
			free (self->index);
			self->index = NULL;
		}
		
		vector_clean (&self->data);
		
		free (self);
	}
}

void
index_clean (index_t ** self)
{
	assert (self != NULL);
	
	index_free (*self);
	*self = NULL;
}

