/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#ifndef _DFA_H_
#define _DFA_H_ 1

#include <stdlib.h>
#include <stdbool.h>

// DFA

struct _dfa_t;
typedef struct _dfa_t dfa_t;

dfa_t * dfa_alloc (size_t n_syms);

void    dfa_set (dfa_t * self, size_t state_id, size_t * dest);
size_t  dfa_get (dfa_t * self, size_t state_id, size_t sym_id);

size_t  dfa_get_n_state (dfa_t * self);
size_t  dfa_get_n_symbol (dfa_t * self);

bool    dfa_verify (dfa_t * self);

void    dfa_free (dfa_t * self);
void    dfa_clean (dfa_t ** self);

// DFA Exec

struct _dfa_exec_t;
typedef struct _dfa_exec_t dfa_exec_t;

dfa_exec_t *
        dfa_exec_alloc (dfa_t * dfa, size_t initial);

void    dfa_exec_push (dfa_exec_t * self, size_t sym_id);
size_t  dfa_exec_get_state (dfa_exec_t * self);

void    dfa_exec_free  (dfa_exec_t * self);
void    dfa_exec_clean (dfa_exec_t ** self);

#endif

