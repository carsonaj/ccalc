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
    t_init_dbl(&check);
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
    t_init_dbl(&coef);
    t_dbl(-2.1, &coef);
    ply_set_coef(p, 2, coef);

    tvalue out = ply_get_coef(p, 2);
    tvalue check; 
    t_init_dbl(&check);
    t_dbl(-2.1000000000000000000000001, &check);

    assert(t_equal(out, check) == TRUE);

    ply_delete(p);

    //  ======================================

    return;
}

void test_ply_fill() {
    Polynomial *p = ply_create(DBL, 2);
    tvalue coefs[3];
    t_init_dbls(coefs, 3);

    int i;
    for (i=0; i<3; i++) {
        assert(coefs[i].type == DBL);
        assert(coefs[i].val.dblval == 0);
    }

    double vals[3] = {1, 2, 3};
    t_dbls(vals, coefs, 3);

    ply_fill(p, coefs);

    ply_delete(p);
    for (i=0; i<3; i++) {
        t_delete(&coefs[i]);
    }

    return;
}

void test_ply_fill_dbl() {
    Polynomial *p = ply_create(DBL, 2);
    double coefs[3] = {0, 1, 2};
    ply_fill_dbl(p, coefs);

    int i;
    for (i=0; i<3; i++) {
        assert(p->coefs[i].type == DBL);
        assert(p->coefs[i].val.dblval == i);
    }

    ply_delete(p);

    return;
}

// add clear function to clear poly coeffs (freeing any pointer memory for alg nums) 
// then use clear function in copy, sum, product, inv, zero, etc functions

void test_ply_copy() {
    // DBL ======================================
    Polynomial *p = ply_create(DBL, 4);
    double coefs[5] = {1, -2, 3, -5, 6};
    ply_fill_dbl(p, coefs);
    assert(ply_get_coef(p, 0).val.dblval == 1);
    assert(ply_get_coef(p, 1).val.dblval == -2);
    assert(ply_get_coef(p, 2).val.dblval == 3);
    assert(ply_get_coef(p, 3).val.dblval == -5);
    assert(ply_get_coef(p, 4).val.dblval == 6);

    Polynomial *copy = ply_create(DBL, 3);
    ply_copy(p, copy);

    assert(ply_get_coef(copy, 0).val.dblval == 1);
    assert(ply_get_coef(copy, 1).val.dblval == -2);
    assert(ply_get_coef(copy, 2).val.dblval == 3);
    assert(ply_get_coef(copy, 3).val.dblval == -5);
    assert(ply_get_coef(copy, 4).val.dblval == 6);
    assert(ply_equal(p, copy) == TRUE);

    ply_delete(p);
    ply_delete(copy);

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
    assert(p4->deg == 0);
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
    t_init_dbl(&coef2);
    t_dbl(0.0000000000000000000000001, &coef2);
    tvalue coef3;
    t_init_dbl(&coef3);
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

    t_delete(&coef2);
    t_delete(&coef3);


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
    t_init_dbl(&s1);
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

    t_delete(&s1);

    return;
}

void test_ply_negative() {
    Polynomial *p1 = ply_create(DBL, 3);
    Polynomial *neg1 = ply_create(DBL, 1);
    Polynomial *check1 = ply_create(DBL, 3);
    double coef_p1[4] = {-1.5, 2, 3, 1};
    double coef_ch1[4] = {1.5, -2, -3, -1};
    ply_fill_dbl(p1, coef_p1);
    ply_fill_dbl(check1, coef_ch1);
    ply_negative(p1, neg1);

    assert(neg1->deg == 3);
    assert(ply_equal(check1, neg1) == TRUE);

    ply_delete(p1);
    ply_delete(neg1);
    ply_delete(check1);

    return;
}

/*
void test_sub_division() {
    Polynomial *f1 = ply_create(DBL, 3);
    Polynomial *g1 = ply_create(DBL, 2);
    Polynomial *q1 = ply_create(DBL, 0);
    Polynomial *r1 = ply_create(DBL, 0);
    Polynomial *check_q1 = ply_create(DBL, 1);
    Polynomial *check_r1 = ply_create(DBL, 2);

    double coef_f1[4] = {-1, 2, 3, 4};
    double coef_g1[3] = {-2, -3, -2};
    double coef_qcheck1[2] = {0, -2};
    double coef_rcheck1[3] = {-1, -2, -3};

    ply_fill_dbl(f1, coef_f1);
    ply_fill_dbl(g1, coef_g1);
    ply_fill_dbl(check_q1, coef_qcheck1);
    ply_fill_dbl(check_r1, coef_rcheck1);
    sub_division(f1, g1, q1, r1);

    assert(q1->deg == 1);
    assert(r1->deg == 2);
    assert(ply_equal(q1, check_q1) == TRUE);
    assert(ply_equal(r1, check_r1) == TRUE);

    ply_delete(f1);
    ply_delete(g1);
    ply_delete(q1);
    ply_delete(r1);
    ply_delete(check_q1);
    ply_delete(check_r1);
    
    return;
}
*/

void test_ply_division() {
    Polynomial *f1 = ply_create(DBL, 3);
    Polynomial *g1 = ply_create(DBL, 2);
    Polynomial *q1 = ply_create(DBL, 0);
    Polynomial *r1 = ply_create(DBL, 0);
    Polynomial *check_q1 = ply_create(DBL, 1);
    Polynomial *check_r1 = ply_create(DBL, 1);

    double coef_f1[4] = {-1, 2, 3, 4};
    double coef_g1[3] = {-2, -3, -2};
    double coef_qcheck1[2] = {1.5, -2};
    double coef_rcheck1[2] = {2, 2.5};

    ply_fill_dbl(f1, coef_f1);
    ply_fill_dbl(g1, coef_g1);
    ply_fill_dbl(check_q1, coef_qcheck1);
    ply_fill_dbl(check_r1, coef_rcheck1);
    ply_division(f1, g1, q1, r1);

    assert(q1->deg == 1);
    assert(r1->deg == 1);
    assert(ply_equal(q1, check_q1) == TRUE);
    assert(ply_equal(r1, check_r1) == TRUE);

    ply_delete(f1);
    ply_delete(g1);
    ply_delete(q1);
    ply_delete(r1);
    ply_delete(check_q1);
    ply_delete(check_r1);

    Polynomial *f2 = ply_create(DBL, 3);
    Polynomial *g2 = ply_create(DBL, 4);
    Polynomial *q2 = ply_create(DBL, 0);
    Polynomial *r2 = ply_create(DBL, 0);
    Polynomial *check_q2 = ply_create(DBL, 0);
    Polynomial *check_r2 = ply_create(DBL, 3);

    double coef_f2[4] = {-1, 2, 3, 4};
    double coef_g2[5] = {-2, -3, -2, 1, 4};
    double coef_qcheck2[1] = {0};
    double coef_rcheck2[4] = {-1, 2, 3, 4};

    ply_fill_dbl(f2, coef_f2);
    ply_fill_dbl(g2, coef_g2);
    ply_fill_dbl(check_q2, coef_qcheck2);
    ply_fill_dbl(check_r2, coef_rcheck2);
    ply_division(f2, g2, q2, r2);

    assert(q2->deg == 0);
    assert(r2->deg == 3);
    assert(ply_equal(q2, check_q2) == TRUE);
    assert(ply_equal(r2, check_r2) == TRUE);

    ply_delete(f2);
    ply_delete(g2);
    ply_delete(q2);
    ply_delete(r2);
    ply_delete(check_q2);
    ply_delete(check_r2);

    return;
}

void test_ply_gcd_1() {
    Polynomial *f = ply_create(DBL, 3);
    Polynomial *g = ply_create(DBL, 2);
    Polynomial *gcd = ply_create(DBL, 0);
    Polynomial *a = ply_create(DBL, 0);
    Polynomial *b = ply_create(DBL, 0);
    Polynomial *gcd_check = ply_create(DBL, 1);
    Polynomial *a_check = ply_create(DBL, 0);
    Polynomial *b_check = ply_create(DBL, 1);

    double coef_f[4] = {-6, -5, 2, 1};
    double coef_g[3] = {-9, 0, 1};
    double coef_gcd_check[2] = {3, 1};
    double coef_a_check[2] = {.25};
    double coef_b_check[2] = {-.5, -.25};

    ply_fill_dbl(f, coef_f);
    ply_fill_dbl(g, coef_g);
    ply_fill_dbl(gcd_check, coef_gcd_check);
    ply_fill_dbl(a_check, coef_a_check);
    ply_fill_dbl(b_check, coef_b_check);

    ply_gcd(f, g, gcd, a, b);

    assert(ply_equal(gcd, gcd_check) == TRUE);
    assert(ply_equal(a, a_check) == TRUE);
    assert(ply_equal(b, b_check) == TRUE);
    

    ply_delete(f);
    ply_delete(g);
    ply_delete(gcd);
    ply_delete(a);
    ply_delete(b);
    ply_delete(gcd_check);
    ply_delete(a_check);
    ply_delete(b_check);

    return;
}

void test_ply_gcd_2() {
    Polynomial *f = ply_create(DBL, 2);
    Polynomial *g = ply_create(DBL, 3);
    Polynomial *gcd = ply_create(DBL, 0);
    Polynomial *a = ply_create(DBL, 0);
    Polynomial *b = ply_create(DBL, 0);
    Polynomial *gcd_check = ply_create(DBL, 1);
    Polynomial *a_check = ply_create(DBL, 1);
    Polynomial *b_check = ply_create(DBL, 0);

    double coef_g[4] = {-6, -5, 2, 1};
    double coef_f[3] = {-9, 0, 1};
    double coef_gcd_check[2] = {3, 1};
    double coef_b_check[2] = {.25};
    double coef_a_check[2] = {-.5, -.25};

    ply_fill_dbl(f, coef_f);
    ply_fill_dbl(g, coef_g);
    ply_fill_dbl(gcd_check, coef_gcd_check);
    ply_fill_dbl(a_check, coef_a_check);
    ply_fill_dbl(b_check, coef_b_check);

    ply_gcd(f, g, gcd, a, b);

    assert(ply_equal(gcd, gcd_check) == TRUE);
    assert(ply_equal(a, a_check) == TRUE);
    assert(ply_equal(b, b_check) == TRUE);
    

    ply_delete(f);
    ply_delete(g);
    ply_delete(gcd);
    ply_delete(a);
    ply_delete(b);
    ply_delete(gcd_check);
    ply_delete(a_check);
    ply_delete(b_check);

    return;
}

void test_ply_mod_reduce() {
    Polynomial *p = ply_create(DBL, 4);
    Polynomial *m = ply_create(DBL, 2);
    Polynomial *check = ply_create(DBL, 0);

    double coef_p[5] = {2, 0, 6, 0, 1}; 
    double coef_m[3] = {5, 0, 1};
    double coef_check[3] = {-3};

    ply_fill_dbl(p, coef_p);
    ply_fill_dbl(m, coef_m);
    ply_fill_dbl(check, coef_check);

    ply_mod_reduce(p, m);
    assert(ply_equal(p, check));

    ply_delete(p);
    ply_delete(m);
    ply_delete(check);

    return;
}

void test_ply_mod_inverse() {
    Polynomial *p = ply_create(DBL, 4);
    Polynomial *m = ply_create(DBL, 2);
    Polynomial *inv = ply_create(DBL, 0);
    Polynomial *check = ply_create(DBL, 1);

    double coef_p[5] = {-9, -18, -8, 2, 1}; 
    double coef_m[3] = {1, 0, 1};
    double coef_check[2] = {0, 1.0/20.0};

    ply_fill_dbl(p, coef_p);
    ply_fill_dbl(m, coef_m);
    ply_fill_dbl(check, coef_check);

    ply_mod_inverse(p, inv, m);
    assert(ply_equal(inv, check));

    ply_delete(p);
    ply_delete(m);
    ply_delete(inv);
    ply_delete(check);

    return;
}

void test_ply_mod_sum() {
    Polynomial *p = ply_create(DBL, 3);
    Polynomial *q = ply_create(DBL, 3);

    Polynomial *m = ply_create(DBL, 2);
    Polynomial *sum = ply_create(DBL, 0);
    Polynomial *check = ply_create(DBL, 1);

    double coef_p[4] = {-1, 0, 1, 2}; 
    double coef_q[4] = {1, 0, 0, -1}; 
    double coef_m[3] = {-2, 1, 1};
    double coef_check[2] = {0, 2};

    ply_fill_dbl(p, coef_p);
    ply_fill_dbl(q, coef_q);
    ply_fill_dbl(m, coef_m);
    ply_fill_dbl(check, coef_check);

    ply_mod_sum(p, q, sum, m);
    assert(ply_equal(sum, check));

    ply_delete(p);
    ply_delete(q);
    ply_delete(m);
    ply_delete(sum);
    ply_delete(check);

    return;
}

void test_ply_mod_product() {
    Polynomial *p = ply_create(DBL, 2);
    Polynomial *q = ply_create(DBL, 3);

    Polynomial *m = ply_create(DBL, 3);
    Polynomial *prod = ply_create(DBL, 0);
    Polynomial *check = ply_create(DBL, 2);

    double coef_p[3] = {0, 2, 3}; 
    double coef_q[4] = {1, 0, 0, 1}; 
    double coef_m[4] = {-3, 0, 0, 1};
    double coef_check[3] = {0, 8, 12};

    ply_fill_dbl(p, coef_p);
    ply_fill_dbl(q, coef_q);
    ply_fill_dbl(m, coef_m);
    ply_fill_dbl(check, coef_check);

    ply_mod_product(p, q, prod, m);
    assert(ply_equal(prod, check));

    ply_delete(p);
    ply_delete(q);
    ply_delete(m);
    ply_delete(prod);
    ply_delete(check);

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
    test_ply_fill(); // passed
    test_ply_fill_dbl(); // passed
    test_ply_copy();
    test_ply_equal(); 
    test_ply_is_zero();
    test_ply_zero();
    test_ply_sum();
    test_ply_product();
    test_ply_scale();
    test_ply_negative();
    //test_sub_division(); passed
    test_ply_division();
    test_ply_gcd_1();
    test_ply_gcd_2();
    test_ply_mod_reduce();
    test_ply_mod_inverse();
    test_ply_mod_sum();
    test_ply_mod_product();


    return 0;
}