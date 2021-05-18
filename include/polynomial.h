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
tvalue ply_get_coef(Polynomial *poly, int i);
void ply_set_coef(Polynomial *poly, int i, tvalue val);
void ply_copy(Polynomial *p, Polynomial *q);
void ply_print(Polynomial *poly);
void ply_print_dbl(Polynomial *poly);

// mathematics

// algebra
int ply_equal(Polynomial *p, Polynomial *q);
Polynomial *ply_zero();
int ply_is_zero(Polynomial *p);
Polynomial ply_sum(Polynomial *poly1, Polynomial *poly2, Polynomial *sum);
Polynomial ply_product(Polynomial *poly1, Polynomial *poly2, Polynomial *prod);
Polynomial ply_scale(tvalue s, Polynomial *p);
Polynomial ply_neg(Polynomial *p);
Matrix ply_division(Polynomial *f, Polynomial *g);
Matrix ply_gcd(Polynomial *p, Polynomial *q);
Polynomial ply_mod_reduce(Polynomial *p, Polynomial *m);
Polynomial ply_mod_inv(Polynomial *p, Polynomial *m);
Polynomial ply_mod_sum(Polynomial *p, Polynomial *q, Polynomial *m);
Polynomial ply_mod_product(Polynomial *p, Polynomial q, Polynomial *m);

// analysis
tvalue ply_evaluate(Polynomial *poly, tvalue *x);
Polynomial ply_differentiate(Polynomial poly, int n);

#endif