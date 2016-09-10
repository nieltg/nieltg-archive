/* 
 * NIM/Nama  : 13515071 / Daniel Pintara
 * Tanggal   : Fri Sep 9, 2016
 * Topik     : DFA
 * Deskripsi : Implementasi DFA pada vending machine sederhana
 */

#ifndef _DFA_H_
#define _DFA_H_ 1

// DFA Delta

struct _dfa_delta_priv_t;
typedef struct _dfa_delta_priv_t dfa_delta_priv_t;

typedef struct
{
	dfa_delta_priv_t * _priv;
	
	size_t first_id;
	size_t * delta;
}
dfa_delta_t;

dfa_delta_t *
        dfa_delta_alloc (size_t nstates, size_t nsyms);

#define dfa_delta_first(obj) \
        obj->first
#define dfa_delta(obj, x, y) \
        obj->delta[x][y]

size_t  dfa_delta_get_states_count (dfa_delta_t * self);
size_t  dfa_delta_get_symbols_count (dfa_delta_t * self);

void    dfa_delta_free (dfa_delta_t * self);
void    dfa_delta_clean (dfa_delta_t ** self);

// DFA

struct _dfa_t;
typedef struct _dfa_t dfa_t;

dfa_t * dfa_alloc (dfa_delta_t * dt);

void    dfa_push (dfa_t * self, size_t sym_id);
size_t  dfa_get_state (dfa_t * self);

void    dfa_free  (dfa_t * self);
void    dfa_clean (dfa_t ** self);

#endif

