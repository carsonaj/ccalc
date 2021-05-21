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
    // DBL ======================================
    Polynomial *p = ply_create(DBL, 3);
    assert(p->deg == 3);
    ply_delete(p); 

    //  ======================================

    return;
}

void test_ply_print() {
    // DBL ======================================
    Polynomial *p = ply_create(DBL, 3);
    double coefs[4] = {1, 3, 2, -1};
    ply_fill_dbl(p, coefs);
    ply_print(p, FALSE);

    ply_delete(p);

    //  ======================================

    return;
}

void test_ply_get_coef() {
    // DBL ======================================
    Polynomial *p = ply_create(DBL, 4);
    double coefs[5] = {1, -2, 3, -.5, 6};
    ply_fill_dbl(p, coefs);
    tvalue coef = ply_get_coef(p, 2);
    tvalue check; 
    t_dbl(3, &check);
    assert(t_equal(coef, check) == TRUE);

    ply_delete(p);

    //  ======================================

    return;
}

void test_ply_set_coef() {
    // DBL ======================================
    Polynomial *p = ply_create(DBL, 4);
    tvalue coef; 
    t_dbl(-2.1, &coef);
    ply_set_coef(p, 2, coef);

    tvalue out = ply_get_coef(p, 2);
    tvalue check; 
    t_dbl(-2.1000000000000000000000001, &check);

    assert(t_equal(out, check) == TRUE);

    ply_delete(p);

    //  ======================================

    return;

}

void test_ply_copy() {
    // DBL ======================================
    Polynomial *p = ply_create(DBL, 4);
    double coefs[5] = {1, -2, 3, -.5, 6};
    ply_fill_dbl(p, coefs);
    Polynomial *copy = ply_create(DBL, 4);
    ply_copy(p, copy);
    assert(ply_equal(p, copy) == TRUE);

    ply_delete(p);
    ply_delete(copy);

    //  ======================================

    return;
}

void test_ply_equal() {
    // DBL ======================================
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

    //  ======================================


    return;
}

void test_ply_is_zero() {
    // DBL ======================================
    Polynomial *p1 = ply_create(DBL, 2);
    Polynomial *p2 = ply_create(DBL, 0);
    Polynomial *p3 = ply_create(DBL, 0);

    double coefs[3] = {1, 2, 3};
    tvalue coef2;
    t_dbl(0.0000000000000000000000001, &coef2);
    tvalue coef3;
    t_dbl(0, &coef3);

    ply_fill_dbl(p1, coefs);
    ply_set_coef(p2, 0, coef2);
    ply_set_coef(p3, 0, coef3);

    assert(ply_is_zero(p1) == FALSE);
    assert(ply_is_zero(p2) == TRUE);
    assert(ply_is_zero(p3) == TRUE);

    ply_delete(p1);
    ply_delete(p2);
    ply_delete(p3);

    //  ======================================


    return;
}

void test_ply_zero() {
    Polynomial *z = ply_create(DBL, 3);
    ply_zero(z);

    assert(z->deg == 0);
    assert(t_is_zero(ply_get_coef(z, 0)) == TRUE);

    ply_delete(z);
}

void test_ply_sum() {
    Polynomial *p1 = ply_create(DBL, 3);
    Polynomial *q1 = ply_create(DBL, 1);
    Polynomial *sum1 = ply_create(DBL, 1);
    Polynomial *check1 = ply_create(DBL, 3);

    Polynomial *p2 = ply_create(DBL, 3);
    Polynomial *q2 = ply_create(DBL, 3);
    Polynomial *sum2 = ply_create(DBL, 0);
    Polynomial *check2 = ply_create(DBL, 2);

    double coef_p1[4] = {-1.5, 2, 3, 1};
    double coef_q1[2] = {0, -1};
    double coef_ch1[4] = {-1.5, 1, 3, 1};

    double coef_p2[4] = {-1.5, 2, 3, 1};
    double coef_q2[4] = {0, -1, 1, -1};
    double coef_ch2[3] = {-1.5, 1, 4};

    ply_fill_dbl(p1, coef_p1);
    ply_fill_dbl(q1, coef_q1);
    ply_fill_dbl(check1, coef_ch1);
    ply_sum(p1, q1, sum1);

    ply_fill_dbl(p2, coef_p2);
    ply_fill_dbl(q2, coef_q2);
    ply_fill_dbl(check2, coef_ch2);
    ply_sum(p2, q2, sum2);

    assert(sum1->deg == 3);
    assert(ply_equal(sum1, check1) == TRUE);

    assert(sum2->deg == 2);
    assert(ply_equal(sum2, check2) == TRUE);

    ply_delete(p1);
    ply_delete(q1);
    ply_delete(sum1);
    ply_delete(check1);

    ply_delete(p2);
    ply_delete(q2);
    ply_delete(sum2);
    ply_delete(check2);

    return;
}

void test_ply_product() {
    Polynomial *p1 = ply_create(DBL, 3);
    Polynomial *q1 = ply_create(DBL, 1);
    Polynomial *prod1 = ply_create(DBL, 1);
    Polynomial *check1 = ply_create(DBL, 4);

    double coef_p1[4] = {-1.5, 2, 3, 1};
    double coef_q1[2] = {1, -1};
    double coef_ch1[5] = {-1.5, 3.5, 1, -2, -1};

    ply_fill_dbl(p1, coef_p1);
    ply_fill_dbl(q1, coef_q1);
    ply_fill_dbl(check1, coef_ch1);
    ply_product(p1, q1, prod1);

    assert(prod1->deg == 4);
    assert(ply_equal(prod1, check1) == TRUE);

    ply_delete(p1);
    ply_delete(q1);
    ply_delete(prod1);
    ply_delete(check1);

    return;
}

void test_ply_scale() {
    tvalue s1;
    t_dbl(2.0, &s1);
    Polynomial *p1 = ply_create(DBL, 3);
    Polynomial *sp1 = ply_create(DBL, 0);
    Polynomial *check1 = ply_create(DBL, 3);
    double coef_p1[4] = {-1.5, 2, 3, 1};
    double coef_ch1[4] = {-3, 4, 6, 2};
    ply_fill_dbl(p1, coef_p1);
    ply_fill_dbl(check1, coef_ch1);
    ply_scale(s1, p1, sp1);

    assert(sp1->deg == 3);
    assert(ply_equal(check1, sp1) == TRUE);

    ply_delete(p1);
    ply_delete(sp1);
    ply_delete(check1);

    return;
}

void test_ply_neg() {
    Polynomial *p1 = ply_create(DBL, 3);
    Polynomial *neg1 = ply_create(DBL, 1);
    Polynomial *check1 = ply_create(DBL, 3);
    double coef_p1[4] = {-1.5, 2, 3, 1};
    double coef_ch1[4] = {1.5, -2, -3, -1};
    ply_fill_dbl(p1, coef_p1);
    ply_fill_dbl(check1, coef_ch1);
    ply_neg(p1, neg1);

    assert(neg1->deg == 3);
    assert(ply_equal(check1, neg1) == TRUE);

    ply_delete(p1);
    ply_delete(neg1);
    ply_delete(check1);

    return;
}


//===========================================================================================
//===========================================================================================

// run tests:
int main() {

    // data structure:

    //test_ply_print(); 
    test_ply_create();
    test_ply_get_coef();
    test_ply_set_coef();
    test_ply_copy();
    test_ply_equal(); 
    test_ply_is_zero();
    test_ply_zero();
    test_ply_sum();
    test_ply_product();
    test_ply_scale();
    test_ply_neg();

    return 0;
}