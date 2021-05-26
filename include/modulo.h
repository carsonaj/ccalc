#ifndef MODULO_H
#define MODULO_H
#include "type.h"
#include "matrix.h"

//structure
void mod_print(Modulo m, int newline);

// algebra
int mod_equal(Modulo m, Modulo n);
int mod_is_zero(Modulo m);

void mod_zero(Modulo *z);
void mod_sum(Modulo m, Modulo n, Modulo *sum);
void mod_product(Modulo m, Modulo n, Modulo *prod);
void mod_neg(Modulo m, Modulo *neg);

#endif