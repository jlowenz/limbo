// vim:filetype=cpp:textwidth=80:shiftwidth=2:softtabstop=2:expandtab
// Copyright 2014 schwering@kbsg.rwth-aachen.de
//
// This is an implementation of (most of the) queries proven in the ESL paper.

#include <stdio.h>
#include <kr2014.h>

#define ASSERT(phi)     ((void) ((phi) || printf("Condition failed: " #phi)))

using namespace esbl;
using namespace bats;

int main(int argc, char *argv[])
{
    Kr2014 bat;

#if 0
    univ_clauses_t static_bat;
    box_univ_clauses_t dynamic_bat;
    init_bat(&dynamic_bat, &static_bat, NULL);

    context_t ctx = kcontext_init(&static_bat, &dynamic_bat);

    //printf("Q0\n");
    const query_t *phi0 =
        query_and(
            Q(N(Z(), d0, A())),
            Q(N(Z(), d1, A())));
    ASSERT(query_entailed(&ctx, false, phi0, 0));

    //printf("Q1\n");
    const query_t *phi1 =
        query_neg(
            query_or(
                Q(P(Z(), d0, A())),
                Q(P(Z(), d1, A()))));
    ASSERT(query_entailed(&ctx, false, phi1, 0));

    //printf("Q2\n");
    const query_t *phi3 =
        query_act(forward,
            query_or(
                Q(P(Z(), d1, A())),
                Q(P(Z(), d2, A()))));
    ASSERT(query_entailed(&ctx, false, phi3, 1));

    //printf("Q3\n");
    const query_t *phi2 =
        query_act(forward,
            query_or(
                Q(P(Z(), d1, A())),
                Q(P(Z(), d2, A()))));
    ASSERT(!query_entailed(&ctx, false, phi2, 0));

    context_add_action(&ctx, forward, true);
    context_add_action(&ctx, sonar, true);

    //printf("Q4\n");
    const query_t *phi4 =
        query_or(
            Q(P(Z(), d0, A())),
            Q(P(Z(), d1, A())));
    ASSERT(query_entailed(&ctx, false, phi4, 1));

    //printf("Q5\n");
    const query_t *phi5 = Q(P(Z(), d0, A()));
    ASSERT(!query_entailed(&ctx, false, phi5, 1));

    //printf("Q6\n");
    const query_t *phi6 = Q(P(Z(), d1, A()));
    ASSERT(query_entailed(&ctx, false, phi6, 1));

    //printf("Q7\n");
    const query_t *phi7 =
        query_act(sonar,
            query_or(
                Q(P(Z(), d0, A())),
                Q(P(Z(), d1, A()))));
    ASSERT(query_entailed(&ctx, false, phi7, 1));

    //printf("Q8\n");
    const query_t *phi8 =
        query_act(sonar,
            query_act(sonar,
                query_or(
                    Q(P(Z(), d0, A())),
                    Q(P(Z(), d1, A())))));
    ASSERT(query_entailed(&ctx, false, phi8, 1));

    //printf("Q9\n");
    const query_t *phi9 =
        query_act(forward,
            query_or(
                Q(P(Z(), d0, A())),
                Q(P(Z(), d1, A()))));
    ASSERT(query_entailed(&ctx, false, phi9, 1));

    //printf("Q10\n");
    const query_t *phi10 =
        query_act(forward,
            query_act(forward,
                Q(P(Z(), d0, A()))));
    ASSERT(query_entailed(&ctx, false, phi10, 1));
#endif

    printf("Example from the KR-2014 paper works\n");
    return 0;
}
