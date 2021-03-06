#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "type.h"
#include "matrix.h"

#define MAX_DEG 100

// structure
Polynomial *ply_create(dtype t, int deg);
void ply_delete(Polynomial *poly);
void ply_fill(Polynomial *poly, tvalue *coefs);
void ply_fill_dbl(Polynomial *poly, double *coefs);
void ply_fill_mod(Polynomial *poly, int *coefs, int modulus);
tvalue ply_get_coef(Polynomial *poly, int i);
void ply_set_coef(Polynomial *poly, int i, tvalue val);
void ply_copy(Polynomial *p, Polynomial *q);
void ply_print(Polynomial *poly, int newline);
void ply_print_dbl(Polynomial *poly, int newline);

// mathematics

// algebra
int ply_equal(Polynomial *p, Polynomial *q);
int ply_is_zero(Polynomial *p);
void ply_zero(Polynomial *z);
void ply_sum(Polynomial *poly1, Polynomial *poly2, Polynomial *sum);
void ply_product(Polynomial *poly1, Polynomial *poly2, Polynomial *prod);
void ply_scale(tvalue s, Polynomial *p, Polynomial *sp);
void ply_negative(Polynomial *p, Polynomial *neg);
void ply_division(Polynomial *f, Polynomial *g, Polynomial *q, Polynomial *r); 
void ply_gcd(Polynomial *f, Polynomial *g, Polynomial *gcd, Polynomial *a, Polynomial *b);
void ply_mod_reduce(Polynomial *p, Polynomial *m);
void ply_mod_inverse(Polynomial *p, Polynomial *inv, Polynomial *m);
void ply_mod_sum(Polynomial *p, Polynomial *q, Polynomial *sum, Polynomial *m);
void ply_mod_product(Polynomial *p, Polynomial *q, Polynomial *prod, Polynomial *m);
/*
// analysis
tvalue ply_evaluate(Polynomial *poly, tvalue *x);
Polynomial ply_differentiate(Polynomial poly, int n);
*/
#endif