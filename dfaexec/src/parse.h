/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#ifndef _PARSE_H_
#define _PARSE_H_ 1

#include <stdlib.h>

#include "dfa.h"

// Parse

struct _parse_t;
typedef struct _parse_t parse_t;

#define FLAG_FINAL    (1 << 0)
#define FLAG_INITIAL  (1 << 1)

parse_t *
        parse_alloc (void);

void    parse_load (parse_t * self, FILE * input);

size_t  parse_get_first_id (parse_t * self);

char    parse_get_flags (parse_t * self, size_t id);
char *  parse_get_state (parse_t * self, size_t id);
char *  parse_get_symbol (parse_t * self, size_t id);
bool    parse_get_symbol_id (parse_t * self, char * value, size_t * id);

dfa_t * parse_get_dfa (parse_t * self);

void    parse_free (parse_t * self);
void    parse_clean (parse_t ** self);

#endif

