#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/array.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

// define tests:

// data structure: 

void test_ply_create() {
    Polynomial *p = ply_create(DBL, 3);
    assert(p->deg == 3);
    ply_delete(p); 

    return;
}

void test_ply_print() {
    Polynomial *p = ply_create(DBL, 3);
    double coefs[4] = {1, 3, 2, -1};
    ply_fill_dbl(p, coefs);
    ply_print(p);

    ply_delete(p);

    return;
}

void test_ply_get_coef() {
    Polynomial *p = ply_create(DBL, 4);
    double coefs[5] = {1, -2, 3, -.5, 6};
    ply_fill_dbl(p, coefs);
    tvalue coef = ply_get_coef(p, 2);
    tvalue check = t_dbl(3);
    assert(t_equal(coef, check) == TRUE);

    ply_delete(p);

    return;
}

void test_ply_set_coef() {
    Polynomial *p = ply_create(DBL, 4);
    tvalue coef = t_dbl(-2.1);
    ply_set_coef(p, 2, coef);

    tvalue out = ply_get_coef(p, 2);
    tvalue check = t_dbl(-2.1000000000000000000000001);

    assert(t_equal(out, check) == TRUE);

    ply_delete(p);

    return;

}

void test_ply_copy() {
    Polynomial *p = ply_create(DBL, 4);
    double coefs[5] = {1, -2, 3, -.5, 6};
    ply_fill_dbl(p, coefs);
    Polynomial *copy = ply_create(DBL, 4);
    ply_copy(p, copy);
    assert(ply_equal(p, copy) == TRUE);

    ply_delete(p);
    ply_delete(copy);

    return;
}

void test_ply_equal() {
    Polynomial *p1 = ply_create(DBL, 2);
    double coefs1[3] = {.2, -1, -1.2};
    ply_fill_dbl(p1, coefs1);

    Polynomial *p2 = ply_create(DBL, 2);
    double coefs2[3] = {.2, -1, -1.2};
    ply_fill_dbl(p2, coefs2);

    Polynomial *p3 = ply_create(DBL, 2);
    double coefs3[3] = {.2, -1, -1.3};
    ply_fill_dbl(p3, coefs3);

    Polynomial *p4 = ply_create(DBL, 0);
    double coefs4[1] = {0};
    ply_fill_dbl(p4, coefs4);

    Polynomial *p5 = ply_create(DBL, 0);
    double coefs5[1] = {.00000000000000000000000000001};
    ply_fill_dbl(p5, coefs5);
    
    assert(ply_equal(p1, p2) == TRUE);
    assert(ply_equal(p2, p3) == FALSE);
    assert(ply_equal(p1, p4) == FALSE);
    assert(ply_equal(p4, p5) == TRUE); 
    
    ply_delete(p1);
    ply_delete(p2);
    ply_delete(p3);
    ply_delete(p4);
    ply_delete(p5);

    return;
}

void test_ply_is_zero() {
    Polynomial *p1 = ply_create(DBL, 2);
    Polynomial *p2 = ply_create(DBL, 0);
    Polynomial *p3 = ply_create(DBL, 0);

    double coefs[3] = {1, 2, 3};
    tvalue coef2 = t_dbl(0.0000000000000000000000001);
    tvalue coef3 = t_dbl(0);

    ply_fill_dbl(p1, coefs);
    ply_set_coef(p2, 0, coef2);
    ply_set_coef(p3, 0, coef3);

    assert(ply_is_zero(p1) == FALSE);
    assert(ply_is_zero(p2) == TRUE);
    assert(ply_is_zero(p3) == TRUE);

    ply_delete(p1);
    ply_delete(p2);
    ply_delete(p3);

    return;
}

//===========================================================================================
//===========================================================================================

// run tests:
int main() {

    // data structure:
    test_ply_create();
    //test_ply_print();
    test_ply_get_coef();
    test_ply_set_coef();
    test_ply_copy();
    test_ply_equal(); // 6 errors from 3 contexts
    test_ply_is_zero();

    return 0;
}