#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

// define tests:
void test_t_print() {
    tvalue x;
    x.type = DBL;
    x.val.dblval = 2.3;
    
    t_print(x, FALSE);

    Polynomial *p = ply_create(DBL, 2);
    double coefs[3] = {-1.5, 2, 1};
    ply_fill_dbl(p, coefs);

    tvalue y;
    y.type = PLY;
    y.val.plyval = p;

    t_print(y, FALSE);

    ply_delete(p);
    return;
}

void test_t_dbl() {
    tvalue tval;
    t_dbl(3.2, &tval);

    assert(tval.type == DBL);
    assert(tval.val.dblval == 3.2);

    return;
}

void test_t_dbls() {
    tvalue tvals[3];
    double vals[3] = {1, 2, 3};
    t_dbls(vals, tvals, 3);

    assert(tvals[0].type == DBL);
    assert(tvals[0].val.dblval == 1);
    assert(tvals[1].type == DBL);
    assert(tvals[1].val.dblval == 2);
    assert(tvals[2].type == DBL);
    assert(tvals[2].val.dblval == 3);

    return;
}

void test_t_copy() {
    tvalue tval1;
    tvalue tval2;
    t_dbl(3.0, &tval1);
    t_dbl(4.0, &tval2);

    t_copy(tval1, &tval2);
    assert(tval2.val.dblval == 3.0);

    return;
}

void test_t_equal() {
    tvalue tval1;
    t_dbl(1.0, &tval1);
    tvalue tval2;
    t_dbl(2.1, &tval2);
    tvalue tval3; 
    tval3.type = DBL;
    tval3.val.dblval = 1.0000000001;

    assert(t_equal(tval1, tval2) == FALSE);
    assert(t_equal(tval1, tval3) == TRUE);

    return;
}

void test_t_is_zero() {
    tvalue tval1;
    tval1.type = DBL;
    tval1.val.dblval = 0.00000000000000001;

    tvalue tval2;
    tval2.type = DBL;
    tval2.val.dblval = 2.1;

    assert(t_is_zero(tval1) == TRUE);
    assert(t_is_zero(tval2) == FALSE);
}

void test_t_zero() {
    tvalue z;
    t_zero(DBL, &z);
    assert(z.val.dblval == 0.0);

    return;
}

void test_t_identity() {
    tvalue e;
    t_identity(DBL, &e);
    tvalue x; 
    t_dbl(3.0, &x);

    tvalue prod;
    t_product(x, e, &prod);

    assert(t_equal(x, prod));

    return;
}

void test_t_neg() {
    tvalue x;
    tvalue neg;
    tvalue check;

    t_dbl(2.3, &x);
    t_neg(x, &neg);
    t_dbl(-2.3, &check);
    
    assert(t_equal(neg, check) == TRUE);

    return;
}

void test_t_inv() {
    tvalue x; 
    tvalue inv;
    tvalue check;
    t_dbl(2, &x);
    t_inv(x, &inv);
    t_dbl(0.5, &check);
    assert(t_equal(inv, check) == TRUE);

    return;
}

void test_t_sum() {
    tvalue tval1;
    tvalue tval2;
    tvalue sum;  
    tvalue check;

    t_dbl(2.0, &tval1);
    t_dbl(-3.0, &tval2);
    t_sum(tval1, tval2, &sum);
    t_dbl(-1.0, &check);
    
    assert(t_equal(sum, check) == TRUE);

    return;
}

void test_t_product() {
    tvalue tval1;
    tvalue tval2;
    tvalue prod;  
    tvalue check;

    t_dbl(2.0, &tval1);
    t_dbl(-3.0, &tval2);
    t_product(tval1, tval2, &prod);
    t_dbl(-6.0, &check);
    
    assert(t_equal(prod, check) == TRUE);

    return;
}

//===========================================================================================
//===========================================================================================

// run tests:
int main() {
    //test_t_print(); // passed
    test_t_dbl(); // passed
    test_t_dbls(); // passed
    test_t_copy(); // passed
    test_t_equal(); // passed
    test_t_is_zero(); // passed
    test_t_zero(); // passed
    test_t_identity();
    test_t_neg(); // passed
    test_t_inv(); // passed
    test_t_sum(); // passed
    test_t_product(); // passed

    return 0;
}   