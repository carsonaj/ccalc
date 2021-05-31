#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/integer.h"
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

void mod_delete(ModularInt *x) {
    assert(x != NULL);
    free(x);

    return;
}

void mod_copy(ModularInt *x, ModularInt *y) {
    y->modulus = x->modulus;
    y->residue = x->residue;

    return;
}

void mod_print(ModularInt *m, int newline) {
    int modulus = m->modulus;
    int residue = m->residue;

    switch(newline) {
        case TRUE: 
            printf("%dmod%d\n", residue, modulus);
            break;
        case FALSE:
            printf("%dmod%d", residue, modulus);
            break;
    }

    return;
}


// algebra

int mod_equal(ModularInt *m, ModularInt *n) {
    if (m->modulus != n->modulus) 
        return FALSE;
    else if (m->residue != n->residue)
        return FALSE;

    return TRUE;
}

int mod_is_zero(ModularInt *m) {
    assert(m->modulus > 1);
    int res = (m->residue == 0);

    return res;
}

void mod_zero(ModularInt *z) {
    assert(z->modulus > 1);
    z->residue = 0;

    return;
}

void mod_identity(ModularInt *e) {
    assert(e->modulus > 1);
    e->residue = 1;

    return;
}

// arguments must be initialized
void mod_sum(ModularInt *m, ModularInt *n, ModularInt *sum) {
    int p = m->modulus;
    int mr = m->residue;
    int nr = n->residue;

    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(n->modulus = p);
    assert((nr >= 0) && (nr < p));

    assert(sum->modulus = p);

    sum->residue = reduce(mr + nr, p);

    assert((0 <= sum->residue) && (sum->residue < p));

    return;
}

void mod_product(ModularInt *m, ModularInt *n, ModularInt *prod) {
    int p = m->modulus;
    int mr = m->residue;
    int nr = n->residue;

    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(n->modulus = p);
    assert((nr >= 0) && (nr < p));

    assert(prod->modulus = p);

    prod->residue = reduce(mr * nr, p);

    assert((0 <= prod->residue) && (prod->residue < p));
    

    return;
}

void mod_negative(ModularInt *m, ModularInt *neg) {
    int p = m->modulus;
    int mr = m->residue;

    assert(p > 1);
    assert((mr >= 0) && (mr < p));

    assert(neg->modulus = p);
    neg->residue = reduce(-mr, p);

    return;
}

void mod_inverse(ModularInt *m, ModularInt *inv) {
    int p = m->modulus;
    int mr = m->residue;

    assert(p > 1);
    assert((mr >= 0) && (mr < p));
    assert(inv->modulus = p);

    int gcd, a, b;
    int_gcd(mr, p, &gcd, &a, &b);
    assert(gcd == 1);
    
    inv->residue = int_reduce(a, p);

    return;
}