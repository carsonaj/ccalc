#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/matrix.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

static int reduce(int n, int p) {
    if (n < 0) {
        return n % p + p;
    }
    else {
        return n % p;
    }
}

ModularInt *mod_create(int residue, int modulus) {
    assert(modulus > 1);
    ModularInt *x = malloc(sizeof(ModularInt));
    x->modulus = modulus;
    x->residue = reduce(residue, modulus);

    assert((0 <= x->residue) && (x->residue < modulus));

    return x;
}

void mod_print(ModularInt m, int newline) {
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

int mod_equal(ModularInt m, ModularInt n) {
    if (m.modulus != n.modulus) 
        return FALSE;
    else if (m.residue != n.residue)
        return FALSE;

    return TRUE;
}

int mod_is_zero(ModularInt m) {
    int res = (m.residue == 0);

    return res;
}

void mod_zero(ModularInt *z) {
    assert(z->modulus > 1);
    z->residue = 0;

    return;

}

// arguments must be initialized
void mod_sum(ModularInt m, ModularInt n, ModularInt *sum) {
    int p = m.modulus;
    int mr = m.residue;
    int nr = n.residue;

    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(n.modulus = p);
    assert((nr >= 0) && (nr < p));

    assert(sum->modulus = p);

    sum->residue = reduce(mr + nr, p);

    assert((0 <= sum->residue) && (sum->residue < p));

    return;
}

void mod_product(ModularInt m, ModularInt n, ModularInt *prod) {
    int p = m.modulus;
    int mr = m.residue;
    int nr = n.residue;

    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(n.modulus = p);
    assert((nr >= 0) && (nr < p));

    assert(prod->modulus = p);

    prod->residue = reduce(mr * nr, p);

    assert((0 <= prod->residue) && (prod->residue < p));
    

    return;
}

void mod_neg(ModularInt m, ModularInt *neg) {
    int p = m.modulus;
    int mr = m.residue;

    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(neg->modulus = p);
    neg->residue = reduce(-mr, p);

    return;
}

void mod_inv(ModularInt m, ModularInt *inv) {
    int p = m.modulus;
    int mr = m.residue;

    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(inv->modulus = p);
    //inv->residue = ;

    return;
}