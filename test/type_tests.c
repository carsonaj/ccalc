#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/modular_int.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

// define tests:
void test_t_print() {
    tvalue x;
    t_init_dbl(&x);
    x.type = DBL;
    x.val.dblval = 2.3;
    
    t_print(x, FALSE);
    t_delete(&x);

    Polynomial *p = ply_create(DBL, 2);
    double coefs[3] = {-1.5, 2, 1};
    ply_fill_dbl(p, coefs);

    tvalue y;
    t_init_ply(DBL, &y);
    t_ply(p, &y);

    t_print(y, FALSE);

    ply_delete(p);
    t_delete(&y);
    return;
}

void test_t_init_dbl() {
    tvalue x;
    t_init_dbl(&x);
    assert(x.type == DBL);
    assert(x.val.dblval == 0);

    t_delete(&x);

    return;
}

void test_t_dbl() {
    tvalue tval;
    t_init_dbl(&tval);
    t_dbl(3.2, &tval);

    assert(tval.type == DBL);
    assert(tval.val.dblval == 3.2);

    return;
}

void test_t_init_dbls() {
    tvalue tvals[3];
    t_init_dbls(tvals, 3);

    int i;
    for (i=0; i<3; i++) {
    assert(tvals[i].type == DBL);
    assert(tvals[i].val.dblval == 0);
    }
    
    for (i=0; i<3; i++) {
        t_delete(&tvals[i]);
    }

    return;
}

void test_t_dbls() {
    tvalue tvals[3];
    t_init_dbls(tvals, 3);
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

void test_t_init_mod() {
    tvalue tval;
    t_init_mod(&tval);
    assert(tval.type == MOD);
    assert(tval.val.modval->modulus == 2);
    assert(tval.val.modval->residue == 0);

    t_delete(&tval);

    return;
}

void test_t_mod() {
    tvalue tval;
    t_init_mod(&tval);
    ModularInt *x = mod_create(4, 7);
    t_mod(x, &tval);

    assert(tval.type == MOD);
    assert(tval.val.modval->modulus == 7);
    assert(tval.val.modval->residue == 4);

    mod_delete(x);
    t_delete(&tval);
    
    return;
}

void test_t_init_ply() {
    tvalue tval;
    t_init_ply(DBL, &tval);

    t_delete(&tval);
    
    return;
}

void test_t_copy_2() {
    tvalue tval1;
    t_init_dbl(&tval1);

    tvalue tval2;
    t_init_dbl(&tval2);

    t_dbl(3.0, &tval1);
    t_dbl(4.0, &tval2);

    t_copy(tval1, &tval2);
    assert(tval2.val.dblval == 3.0);

    t_delete(&tval1);
    t_delete(&tval2);

    return;
}

void test_t_copy_3() {
    tvalue tval1;
    t_init_ply(DBL, &tval1);

    tvalue tval2;
    t_init_ply(DBL, &tval2);

    Polynomial *p = ply_create(DBL, 3);
    double p_coef[4] = {-1, 2, .3, -3};
    ply_fill_dbl(p, p_coef);
    t_ply(p, &tval1);

    t_copy(tval1, &tval2);
    assert(t_equal(tval1, tval2));
    assert(ply_equal(tval2.val.plyval, p));

    ply_delete(p);
    t_delete(&tval1);
    t_delete(&tval2);

    return;
}

void test_t_copy_4() {
    tvalue tval1;
    tvalue tval2;

    t_init_mod(&tval1);
    t_init_mod(&tval2);

    ModularInt *x = mod_create(3, 11);
    t_mod(x, &tval1);
    
    t_copy(tval1, &tval2);

    assert(tval2.val.modval->modulus == 11);
    assert(tval2.val.modval->residue == 3);

    t_delete(&tval1);
    t_delete(&tval2);
    mod_delete(x);
}

void test_t_equal_2() {
    tvalue tval1;
    t_init_dbl(&tval1);
    t_dbl(1.0, &tval1);
    tvalue tval2;
    t_init_dbl(&tval2);
    t_dbl(2.1, &tval2);

    tvalue tval3; 
    t_init_dbl(&tval3);
    t_dbl(1.0000000001, &tval3);

    assert(t_equal(tval1, tval2) == FALSE);
    assert(t_equal(tval1, tval3) == TRUE);

    t_delete(&tval1);
    t_delete(&tval2);
    t_delete(&tval3);

    return;
}

void test_t_equal_3() {
    tvalue tval1;
    t_init_ply(DBL, &tval1);
    tvalue tval2;
    t_init_ply(DBL, &tval2);

    Polynomial *p1 = ply_create(DBL, 2);
    Polynomial *p2 = ply_create(DBL, 3);

    double coef1[3] = {1, 2, 3};
    double coef2[4] = {-2, .5, 3, 1};

    ply_fill_dbl(p1, coef1);
    ply_fill_dbl(p2, coef2);

    t_ply(p1, &tval1);
    t_ply(p2, &tval2);

    assert(t_equal(tval1, tval2) == FALSE);

    ply_delete(p1);
    ply_delete(p2);
    t_delete(&tval1);
    t_delete(&tval2);

    return;
}

void test_t_equal_4() {
    tvalue tval1;
    tvalue tval2;
    tvalue tval3;
    tvalue tval4;
    t_init_mod(&tval1);
    t_init_mod(&tval2);
    t_init_mod(&tval3);
    t_init_mod(&tval4);

    ModularInt *x2 = mod_create(0, 3);
    ModularInt *x3 = mod_create(1, 2);
    ModularInt *x4 = mod_create(0, 2);

    t_mod(x2, &tval2);
    t_mod(x3, &tval3);
    t_mod(x4, &tval4);

    assert(t_equal(tval1, tval2) == FALSE);
    assert(t_equal(tval1, tval3) == FALSE);
    assert(t_equal(tval1, tval4) == TRUE);

    mod_delete(x2);
    mod_delete(x3);
    mod_delete(x4);
    t_delete(&tval1);
    t_delete(&tval2);
    t_delete(&tval3);
    t_delete(&tval4);

    return;

}

void test_t_is_zero_1() {
    tvalue tval1;
    tval1.type = INT;
    tval1.val.intval = 0;

    tvalue tval2;
    tval2.type = INT;
    tval2.val.intval = 2;

    assert(t_is_zero(tval1) == TRUE);
    assert(t_is_zero(tval2) == FALSE);

    t_delete(&tval1);
    t_delete(&tval2);
}

void test_t_is_zero_2() {
    tvalue tval1;
    tval1.type = DBL;
    tval1.val.dblval = 0.00000000000000001;

    tvalue tval2;
    tval2.type = DBL;
    tval2.val.dblval = 2.1;

    assert(t_is_zero(tval1) == TRUE);
    assert(t_is_zero(tval2) == FALSE);

    t_delete(&tval1);
    t_delete(&tval2);
}

void test_t_is_zero_3() {
    tvalue tval1;
    t_init_ply(DBL, &tval1);
    Polynomial *p1 = ply_create(DBL, 2);
    double coef_p1[3] = {1, 2, 3};
    ply_fill_dbl(p1, coef_p1);
    t_ply(p1, &tval1);

    tvalue tval2;
    t_init_ply(DBL, &tval2);
    Polynomial *p2 = ply_create(DBL, 0);
    double coef_p2[1] = {0};
    ply_fill_dbl(p2, coef_p2);
    t_ply(p2, &tval2);

    assert(t_is_zero(tval1) == FALSE);
    assert(t_is_zero(tval2) == TRUE);

    ply_delete(p1);
    t_delete(&tval1);

    ply_delete(p2);
    t_delete(&tval2);

    return;
}

void test_t_is_zero_4() {
    tvalue tval1;
    tvalue tval2;
    t_init_mod(&tval1);
    t_init_mod(&tval2);
    ModularInt *x2 = mod_create(1, 3);
    t_mod(x2, &tval2);

    assert(t_is_zero(tval1) == TRUE);
    assert(t_is_zero(tval2) == FALSE);

    mod_delete(x2);
    t_delete(&tval1);
    t_delete(&tval2);

    return;
}

void test_t_zero_2() {
    tvalue z;
    t_init_dbl(&z);
    t_zero(&z);
    assert(z.val.dblval == 0.0);

    t_delete(&z);

    return;
}

void test_t_zero_3() {
    tvalue z;
    t_init_ply(DBL, &z);
    t_zero(&z);
    assert(t_is_zero(z) == TRUE);

    t_delete(&z);

    return;
}

void test_t_zero_4() {
    tvalue z;
    t_init_mod(&z);
    t_zero(&z);
    assert(t_is_zero(z) == TRUE);

    t_delete(&z);

    return;
}

void test_t_identity_2() {
    tvalue e;
    t_init_dbl(&e);
    t_identity(&e);
    tvalue x; 
    t_init_dbl(&x);
    t_dbl(3.0, &x);

    tvalue prod;
     t_init_dbl(&prod);
    t_product(x, e, &prod);

    assert(t_equal(x, prod));

    t_delete(&e);
    t_delete(&x);
    t_delete(&prod);

    return;
}

void test_t_negative_2() {
    tvalue x;
    t_init_dbl(&x);
    tvalue neg;
    t_init_dbl(&neg);
    tvalue check;
    t_init_dbl(&check);

    t_dbl(2.3, &x);
    t_negative(x, &neg);
    t_dbl(-2.3, &check);
    
    assert(t_equal(neg, check) == TRUE);

    t_delete(&x);
    t_delete(&neg);
    t_delete(&check);

    return;
}

void test_t_negative_3() {
    tvalue x;
    t_init_ply(DBL, &x);
    double coef_x[3] = {1, 0, -3};
    Polynomial *px = ply_create(DBL, 2);
    ply_fill_dbl(px, coef_x);
    t_ply(px, &x);

    tvalue neg;
    t_init_ply(DBL, &neg);
    t_negative(x, &neg);

    tvalue check;
    t_init_ply(DBL, &check);
    double coef_check[3] = {-1, 0, 3};
    Polynomial *pcheck = ply_create(DBL, 2);
    ply_fill_dbl(pcheck, coef_check);
    t_ply(pcheck, &check);
    
    assert(t_equal(neg, check) == TRUE);

    ply_delete(px);
    ply_delete(pcheck);

    t_delete(&x);
    t_delete(&neg);
    t_delete(&check);

    return;
}

void test_t_negative_4() {
    tvalue x;
    tvalue neg;
    tvalue check;

    t_init_mod(&x);
    t_init_mod(&neg);
    t_init_mod(&check);
    
    ModularInt *xm = mod_create(4, 11);
    ModularInt *xcheck = mod_create(7, 11);
    t_mod(xm, &x);
    t_negative(x, &neg);
    t_mod(xcheck, &check);
    
    assert(t_equal(neg, check) == TRUE);

    mod_delete(xm);
    mod_delete(xcheck);

    t_delete(&x);
    t_delete(&neg);
    t_delete(&check);

    return;
}

void test_t_inverse_1() {
    tvalue x; 
    t_init_dbl(&x);
    tvalue inv;
    t_init_dbl(&inv);
    tvalue check;
    t_init_dbl(&check);
    t_dbl(2, &x);
    t_inverse(x, &inv);
    t_dbl(0.5, &check);
    assert(t_equal(inv, check) == TRUE);

    return;
}

void test_t_inverse_2() {
    tvalue x; 
    tvalue inv;
    tvalue check; 

    t_init_mod(&x);
    t_init_mod(&inv);
    t_init_mod(&check);

    ModularInt *xm = mod_create(4, 11);
    ModularInt *xcheck = mod_create(3, 11);
    
    t_mod(xm, &x);
    t_mod(xcheck, &check);

    t_inverse(x, &inv);

    assert(t_equal(inv, check) == TRUE);

    mod_delete(xm);
    mod_delete(xcheck);
    t_delete(&x);
    t_delete(&inv);
    t_delete(&check);

    return;
}

void test_t_sum_1() {
    tvalue tval1;
    tvalue tval2;
    tvalue sum;  
    tvalue check;
    t_init_int(&tval1);
    t_init_int(&tval2);
    t_init_int(&sum);
    t_init_int(&check);

    t_int(2, &tval1);
    t_int(-3, &tval2);
    t_sum(tval1, tval2, &sum);
    t_int(-1, &check);
    
    assert(t_equal(sum, check) == TRUE);

    return;
}

void test_t_sum_2() {
    tvalue tval1;
    t_init_dbl(&tval1);
    tvalue tval2;
    t_init_dbl(&tval2);
    tvalue sum;  
    t_init_dbl(&sum);
    tvalue check;
    t_init_dbl(&check);

    t_dbl(2.0, &tval1);
    t_dbl(-3.0, &tval2);
    t_sum(tval1, tval2, &sum);
    t_dbl(-1.0, &check);
    
    assert(t_equal(sum, check) == TRUE);

    t_delete(&tval1);
    t_delete(&tval2);
    t_delete(&sum);
    t_delete(&check);

    return;
}

void test_t_sum_3() {
    tvalue tval1;
    t_init_ply(DBL, &tval1);
    double coef_1[3] = {1, 2, 3};
    Polynomial *p1 = ply_create(DBL, 2);
    ply_fill_dbl(p1, coef_1);   
    t_ply(p1, &tval1);
    assert(tval1.val.plyval->deg == 2);

    tvalue tval2;
    t_init_ply(DBL, &tval2);
    double coef_2[3] = {-1, -2, -3};
    Polynomial *p2 = ply_create(DBL, 2);
    ply_fill_dbl(p2, coef_2);   
    t_ply(p2, &tval2);
    assert(tval2.val.plyval->deg == 2);

    tvalue sum;  
    t_init_ply(DBL, &sum);
    t_sum(tval1, tval2, &sum);

    tvalue check;
    t_init_ply(DBL, &check);
    t_zero(&check);
    assert(check.val.plyval->deg == 0);
    
    assert(t_equal(sum, check) == TRUE);

    t_delete(&tval1);
    t_delete(&tval2);
    t_delete(&sum);
    t_delete(&check);

    ply_delete(p1);
    ply_delete(p2);

    return;
}

void test_t_sum_4() {
    tvalue tval1;
    tvalue tval2;
    tvalue sum;  
    tvalue check;
    t_init_mod(&tval1);
    t_init_mod(&tval2);
    t_init_mod(&sum);
    t_init_mod(&check);

    ModularInt *x1 = mod_create(4, 5);
    ModularInt *x2 = mod_create(3, 5);
    ModularInt *xcheck = mod_create(2, 5);

    t_mod(x1, &tval1);
    t_mod(x2, &tval2);
    t_sum(tval1, tval2, &sum);
    t_mod(xcheck, &check);
    
    assert(t_equal(sum, check) == TRUE);

    mod_delete(x1);
    mod_delete(x2);
    mod_delete(xcheck);

    t_delete(&tval1);
    t_delete(&tval2);
    t_delete(&sum);
    t_delete(&check);

    return;
}

void test_t_product_1() {
    tvalue tval1;
    tvalue tval2;
    tvalue prod;  
    tvalue check;
    t_init_int(&tval1);
    t_init_int(&tval2);
    t_init_int(&prod);
    t_init_int(&check);

    t_int(2, &tval1);
    t_int(-3, &tval2);
    t_product(tval1, tval2, &prod);
    t_int(-6, &check);
    
    assert(t_equal(prod, check) == TRUE);

    return;
}

void test_t_product_2() {
    tvalue tval1;
    tvalue tval2;
    tvalue prod;  
    tvalue check;
    t_init_dbl(&tval1);
    t_init_dbl(&tval2);
    t_init_dbl(&prod);
    t_init_dbl(&check);

    t_dbl(2.0, &tval1);
    t_dbl(-3.0, &tval2);
    t_product(tval1, tval2, &prod);
    t_dbl(-6.0, &check);
    
    assert(t_equal(prod, check) == TRUE);

    return;
}

void test_t_product_3() {
    tvalue tval1;
    tvalue tval2;
    tvalue prod;  
    tvalue check;

    t_init_ply(DBL, &tval1);
    t_init_ply(DBL, &tval2);
    t_init_ply(DBL, &prod);
    t_init_ply(DBL, &check);

    double coef1[3] = {1, 2, 3};
    double coef2[3] = {1, -2, 3};
    double coefcheck[5] = {1, 0, 2, 0, 9};

    Polynomial *p1 = ply_create(DBL, 2);
    Polynomial *p2 = ply_create(DBL, 2);
    Polynomial *pcheck = ply_create(DBL, 4);

    ply_fill_dbl(p1, coef1);
    ply_fill_dbl(p2, coef2);
    ply_fill_dbl(pcheck, coefcheck);

    t_ply(p1, &tval1);
    t_ply(p2, &tval2);
    t_product(tval1, tval2, &prod);
    t_ply(pcheck, &check);
    
    assert(t_equal(prod, check) == TRUE);

    ply_delete(p1);
    ply_delete(p2);
    ply_delete(pcheck);

    t_delete(&tval1);
    t_delete(&tval2);
    t_delete(&prod);
    t_delete(&check);

    return;
}

void test_t_product_4() {
    tvalue tval1;
    tvalue tval2;
    tvalue prod;  
    tvalue check;
    t_init_mod(&tval1);
    t_init_mod(&tval2);
    t_init_mod(&prod);
    t_init_mod(&check);

    ModularInt *x1 = mod_create(4, 5);
    ModularInt *x2 = mod_create(2, 5);
    ModularInt *xcheck = mod_create(3, 5);

    t_mod(x1, &tval1);
    t_mod(x2, &tval2);
    t_product(tval1, tval2, &prod);
    t_mod(xcheck, &check);
    
    assert(t_equal(prod, check) == TRUE);

    mod_delete(x1);
    mod_delete(x2);
    mod_delete(xcheck);

    t_delete(&tval1);
    t_delete(&tval2);
    t_delete(&prod);
    t_delete(&check);

    return;
}


//===========================================================================================
//===========================================================================================

// run tests:
int main() {

    //test_t_print(); // passed
    test_t_init_dbl(); // passed
    test_t_dbl(); // passed
    test_t_init_dbls(); // passed
    test_t_dbls(); // passed
    test_t_init_mod(); //passed
    test_t_mod(); // passed
    test_t_init_ply(); // passed
    test_t_copy_2(); // passed
    test_t_copy_3(); // passed
    test_t_equal_2(); // passed
    test_t_equal_3(); //  passed
    test_t_equal_4(); // passed
    test_t_is_zero_1(); // passed
    test_t_is_zero_2(); // passed
    test_t_is_zero_3(); // passed
    test_t_is_zero_4(); // passed
    test_t_zero_2(); // passed
    test_t_zero_3(); // passed
    test_t_zero_4(); // passed
    test_t_identity_2(); // passed
    test_t_negative_2(); // passed
    test_t_negative_3(); // passed
    test_t_negative_4(); // passed
    test_t_inverse_1(); // passed
    test_t_inverse_2(); // passed
    test_t_sum_1(); // passed
    test_t_sum_2(); // passed
    test_t_sum_3(); // passed
    test_t_sum_4(); // passed
    test_t_product_1(); // passed
    test_t_product_2(); // passed
    test_t_product_3(); // passed
    test_t_product_4(); // passed
    

    return 0;
}   