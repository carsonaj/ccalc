#ifndef MODULO_H
#define MODULO_H
#include "type.h"


//structure 
ModularInt *mod_create(int residue, int modulus);
void mod_delete(ModularInt *x);
void mod_print(ModularInt *m, int newline);

// algebra
int mod_equal(ModularInt *m, ModularInt *n);
int mod_is_zero(ModularInt *m);

void mod_zero(ModularInt *z);
void mod_sum(ModularInt *m, ModularInt *n, ModularInt *sum);
void mod_product(ModularInt *m, ModularInt *n, ModularInt *prod);
void mod_negative(ModularInt *m, ModularInt *neg);
void mod_inv(ModularInt *m, ModularInt *inv);

#endif