/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#ifndef _COMMON_H_
#define _COMMON_H_ 1

#include <stdlib.h>
#include <stdbool.h>

// Vector

struct _vector_t;
typedef struct _vector_t vector_t;

vector_t *
        vector_alloc (size_t elmt_size);

size_t  vector_get_size (vector_t * self);

bool    vector_is_elmt_id (vector_t * self, size_t id);

#define vector(self, id, type) \
        *((type *) vector_id (self, id))
#define vector_next(self, type) \
        vector(self, vector_get_size (self), type)

void *  vector_id (vector_t * self, size_t id);

void    vector_compact (vector_t * self);

void *  vector_release (vector_t * self);
void    vector_reset (vector_t * self);

void    vector_free (vector_t * self);
void    vector_clean (vector_t ** self);

// Index

struct _index_t;
typedef struct _index_t index_t;

index_t *
        index_alloc ();

size_t  index_get_size (index_t * self);

char *  index_get_by_id (index_t * self, size_t id);

size_t  index_get (index_t * self, char * val);
bool    index_peek (index_t * self, char * value, size_t * out);

char ** index_release (index_t * self);
void    index_reset (index_t * self);

void    index_free (index_t * self);
void    index_clean (index_t ** self);

#endif

