#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/modular_int.h"

#define TRUE 1
#define FALSE 0

// define tests:

void test_mod_print() {
    ModularInt *x = mod_create(3, 5);
    mod_print(x, TRUE);
    printf("\n\n");
    mod_delete(x);


    return;
}

void test_mod_create() {
    ModularInt *x = mod_create(3, 5);
    assert(x->modulus == 5);
    assert(x->residue == 3);
    mod_delete(x);

    ModularInt *y = mod_create(8, 5);
    assert(y->modulus == 5);
    assert(y->residue == 3);
    mod_delete(y);

    return;
}

void test_mod_equal() {
    ModularInt *x1 = mod_create(3, 5);
    ModularInt *x2 = mod_create(3, 6);
    ModularInt *x3 = mod_create(2, 5);
    ModularInt *x4 = mod_create(3, 5);

    assert(mod_equal(x1, x2) == FALSE);
    assert(mod_equal(x1, x3) == FALSE);
    assert(mod_equal(x1, x4) == TRUE);

    mod_delete(x1);
    mod_delete(x2);
    mod_delete(x3);
    mod_delete(x4);

    return;
}

void test_mod_is_zero() {
    ModularInt *x1 = mod_create(3, 5);
    ModularInt *x2 = mod_create(0, 5);
    ModularInt *x3 = mod_create(5, 5);

    assert(mod_is_zero(x1) == FALSE);
    assert(mod_is_zero(x2) == TRUE);
    assert(mod_is_zero(x3) == TRUE);

    mod_delete(x1);
    mod_delete(x2);
    mod_delete(x3);

    return;
}

void test_mod_zero() {
    ModularInt *x = mod_create(4, 5);
    mod_zero(x);
    assert(mod_is_zero(x));

    mod_delete(x);

    return;
}

void test_mod_sum() {
    ModularInt *x1 = mod_create(4, 5);
    ModularInt *x2 = mod_create(3, 5);
    ModularInt *sum = mod_create(0, 5);
    ModularInt *check = mod_create(2, 5);

    mod_sum(x1, x2, sum);

    assert(mod_equal(sum, check));

    mod_delete(x1);
    mod_delete(x2);
    mod_delete(sum);
    mod_delete(check);
    
    return;
}

void test_mod_product() {
    ModularInt *x1 = mod_create(4, 5);
    ModularInt *x2 = mod_create(3, 5);
    ModularInt *prod = mod_create(0, 5);
    ModularInt *check = mod_create(2, 5);

    mod_product(x1, x2, prod);

    assert(mod_equal(prod, check));

    mod_delete(x1);
    mod_delete(x2);
    mod_delete(prod);
    mod_delete(check);

    return;
}

void test_mod_negative() {
    ModularInt *x1 = mod_create(4, 5);
    ModularInt *neg = mod_create(20, 5);
    ModularInt *check = mod_create(1, 5);

    mod_negative(x1, neg);

    assert(mod_equal(neg, check));

    mod_delete(x1);
    mod_delete(neg);
    mod_delete(check);

    return;
}

void test_mod_inv() {
    ModularInt *x1 = mod_create(4, 5);
    ModularInt *inv = mod_create(20, 5);
    ModularInt *check = mod_create(4, 5);

    mod_inv(x1, inv);

    assert(mod_equal(inv, check));

    mod_delete(x1);
    mod_delete(inv);
    mod_delete(check);

    return;
}


//===========================================================================================
//===========================================================================================

// run tests:

int main() {
    //test_mod_print();
    test_mod_create();
    test_mod_equal();
    test_mod_is_zero();
    test_mod_zero();
    test_mod_sum();
    test_mod_product();
    test_mod_negative();
    test_mod_inv();

    return 0;
}