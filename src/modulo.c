#include <stdio.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/modulo.h"
#include "../include/matrix.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

void mod_print(Modulo m, int newline) {
    int modulus = m.modulus;
    int residue = m.residue;

    switch(newline) {
        case TRUE: 
            printf("%dmodulo%d\n", residue, modulus);
            break;
        case FALSE:
            printf("%dmodulo%d", residue, modulus);
            break;
    }

    return;
}

int mod_equal(Modulo m, Modulo n) {
    if (m.type != n.type)
        return FALSE;
    else if (m.modulus != n.modulus) 
        return FALSE;
    else if (m.residue != n.residue)
        return FALSE;

    return TRUE;
}

int mod_is_zero(Modulo m) {
    int res = (m.residue == 0);

    return res;
}

void mod_zero(Modulo *z) {
    assert(z->type == MOD);
    assert(z->modulus > 1);
    z->residue = 0;

    return;

}

// arguments must be initialized
void mod_sum(Modulo m, Modulo n, Modulo *sum) {
    int p = m.modulus;
    int mr = m.residue;
    int nr = n.residue;

    assert(m.type == MOD);
    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(n.type == MOD);
    assert(n.modulus = p);
    assert((nr >= 0) && (nr < p));

    assert(sum->type == MOD);
    assert(sum->modulus = p);
    sum->residue = (mr + nr) % p;

    return;
}

void mod_product(Modulo m, Modulo n, Modulo *prod) {
    int p = m.modulus;
    int mr = m.residue;
    int nr = n.residue;

    assert(m.type == MOD);
    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(n.type == MOD);
    assert(n.modulus = p);
    assert((nr >= 0) && (nr < p));

    assert(prod->type == MOD);
    assert(prod->modulus = p);
    prod->residue = (mr * nr) % p;

    return;
}
void mod_neg(Modulo m, Modulo *neg) {
    int p = m.modulus;
    int mr = m.residue;

    assert(m.type == MOD);
    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(neg->type == MOD);
    assert(neg->modulus = p);
    neg->residue = (-mr) % p + p;

    return;
}

void mod_inv(Modulo m, Modulo *inv) {
    int p = m.modulus;
    int mr = m.residue;

    assert(m.type == MOD);
    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(inv->type == MOD);
    assert(inv->modulus = p);
    //inv->residue = ;

    return;
}