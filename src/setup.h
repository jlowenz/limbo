// vim:filetype=c:textwidth=80:shiftwidth=4:softtabstop=4:expandtab
/*
 * Functions for generating setups from universally quantified static and boxed
 * clauses.
 *
 * The univ_clause attribute of univ_clause_t should return NULL if the clause
 * variable assignment is not permitted.
 *
 * setup_clauses_ground() substitutes all variables with standard names from ns,
 * and substitutes prepends all prefixes of elements from zs to the box
 * formulas.
 *
 * setup_pel() comptues the positive versions of all literals in the setup. Note
 * that for the split literals, you also need to consider those from the query.
 *
 * setup_propagate_units() computes a new setup which is closed under
 * resolution of its unit clauses with all other clauses. More precisely, for
 * each resolvent of a unit clause there is a clause in the new setup which
 * subsumes this resolvent. It may appear wasteful, but we need to create a
 * new setup anyway because the ordering could be confused otherwise. We use a
 * lazy copy to reduce the amount of copying.
 *
 * schwering@kbsg.rwth-aachen.de
 */
#ifndef _SETUP_H_
#define _SETUP_H_

#include "literal.h"
#include "set.h"
#include "term.h"

SET_DECL(litset, literal_t *);
SET_ALIAS(clause, litset, literal_t *);
SET_ALIAS(pelset, litset, literal_t *);
SET_DECL(setup, clause_t *);
SET_ALIAS(cnf, setup, clause_t *);

typedef struct {
    stdset_t names;
    varset_t vars;
    const clause_t *(*univ_clause)(const varmap_t *map);
} univ_clause_t;

typedef union { univ_clause_t c; } box_univ_clause_t;

VECTOR_DECL(univ_clauses, univ_clause_t *);
VECTOR_DECL(box_univ_clauses, box_univ_clause_t *);

enum query_type { EQ, NEQ, LIT, OR, AND, NEG, EX, ACT };
struct query;
typedef struct query query_t;
typedef struct { stdname_t n1; stdname_t n2; } query_names_t;
typedef struct { query_t *phi; } query_unary_t;
typedef struct { query_t *phi1; query_t *phi2; } query_binary_t;
typedef struct { query_t *(*phi)(stdname_t x); } query_exists_t;
typedef struct { stdname_t n; query_t *phi; } query_action_t;
struct query {
    enum query_type type;
    union {
        literal_t lit;
        query_names_t eq;
        query_names_t neq;
        query_binary_t or;
        query_binary_t and;
        query_unary_t neg;
        query_exists_t ex;
        query_action_t act;
    } u;
};

const clause_t *clause_empty(void);
bool clause_subsumes(const clause_t *c, const clause_t *d);

stdset_t bat_hplus(
        const box_univ_clauses_t *box_cs,
        const univ_clauses_t *cs,
        const stdset_t *query_names,
        int n_query_vars);

setup_t setup_ground_clauses(
        const box_univ_clauses_t *dynamic_bat,
        const univ_clauses_t *static_bat,
        const stdset_t *hplus,
        const stdvecset_t *query_zs);
pelset_t setup_pel(const setup_t *setup);
setup_t setup_propagate_units(const setup_t *setup, const litset_t *split);

bool query_test(
        const box_univ_clauses_t *dynamic_bat,
        const univ_clauses_t *static_bat,
        const litset_t *sensing_results,
        query_t *phi,
        int k);
void query_free(query_t *phi);

#endif

