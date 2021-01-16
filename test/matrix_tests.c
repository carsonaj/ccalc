#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/array.h"
#include "../include/matrix.h"

#define TRUE 1
#define FALSE 0

// define tests:

// data structure: 

void test_dblmat_create() {
    DoubleMatrix *mat2 = dblmat_create(2, 3);
    assert(mat2->nrow == 2);
    assert(mat2->ncol == 3);
    dblmat_delete(mat2);

    return;
}

void test_dblmat_set_entry() {
    DoubleMatrix *mat = dblmat_create(3, 4);
    dblmat_set_entry(mat, 1, 2, .5);
    assert(mat->data[6] == .5);
    dblmat_delete(mat);

    return;
}

void test_dblmat_get_entry() {
    DoubleMatrix *mat = dblmat_create(3, 4);
    dblmat_set_entry(mat, 1, 2, .5);
    assert(dblmat_get_entry(mat, 1, 2) == .5);
    dblmat_delete(mat);

    return;
}

void test_dblmat_fill() {
    DoubleMatrix *mat = dblmat_create(2, 3);
    double entries[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    dblmat_fill(mat, entries);
    
    int i;
    for (i=1; i<6; i++) {
        assert(mat->data[i] == i+1);
    }

    dblmat_delete(mat);

    return;
}

void test_dblmat_equal() {
    DoubleMatrix *mat1 = dblmat_create(2, 3);
    double entries1[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    dblmat_fill(mat1, entries1);
    DoubleMatrix *mat2 = dblmat_create(1, 3);
    double entries2[3] = {1.0, 2.0, 3.0};
    dblmat_fill(mat2, entries2);
    DoubleMatrix *mat3 = dblmat_create(2, 3);
    double entries3[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 7.0};
    dblmat_fill(mat3, entries3);
    DoubleMatrix *mat4 = dblmat_create(2, 3);
    double entries4[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    dblmat_fill(mat4, entries4);

    assert(dblmat_equal(mat1, mat2) == FALSE);
    assert(dblmat_equal(mat1, mat3) == FALSE);
    assert(dblmat_equal(mat1, mat4) == TRUE);

    dblmat_delete(mat1);
    dblmat_delete(mat2);
    dblmat_delete(mat3);
    dblmat_delete(mat4);

    return;
}

void test_dblmat_get_rows() {
    DoubleMatrix *m = dblmat_create(3, 3);
    DoubleMatrix *rm = dblmat_create(2, 3);
    DoubleMatrix *rmc = dblmat_create(2, 3);

    double m_entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double rmc_entries[6] = {4, 5, 6, 7, 8, 9};

    dblmat_fill(m, m_entries);
    dblmat_fill(rmc, rmc_entries);
    int rows_arr[2] = {1, 2};
    dblmat_get_rows(m, rm, rows_arr);

    assert(dblmat_equal(rm, rmc));
    dblmat_delete(m);
    dblmat_delete(rm);
    dblmat_delete(rmc);

    return;
}

void test_dblmat_get_cols() {
    DoubleMatrix *m = dblmat_create(3, 3);
    DoubleMatrix *cm = dblmat_create(3, 2);
    DoubleMatrix *cmc = dblmat_create(3, 2);

    double m_entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double cmc_entries[6] = {1, 2, 4, 5, 7, 8};

    dblmat_fill(m, m_entries);
    dblmat_fill(cmc, cmc_entries);
    int cols_arr[2] = {0, 1};
    dblmat_get_cols(m, cm, cols_arr);

    assert(dblmat_equal(cm, cmc));
    dblmat_delete(m);
    dblmat_delete(cm);
    dblmat_delete(cmc);

    return; 
} 

// mathematics: 

void test_dblmat_row_op1() {
    DoubleMatrix *mat = dblmat_create(3, 3);
    DoubleMatrix *cmat = dblmat_create(3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, 7, 8, 9, 4, 5, 6};
    dblmat_fill(mat, entries); 
    dblmat_fill(cmat, centries);

    dblmat_row_op1(mat, 1, 2);
    assert(dblmat_equal(cmat, mat) == TRUE);

    dblmat_delete(mat);
    dblmat_delete(cmat);

    return;
}

void test_dblmat_row_op2() {
    DoubleMatrix *mat = dblmat_create(3, 3);
    DoubleMatrix *cmat = dblmat_create(3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, 8, 10, 12, 7, 8, 9};
    dblmat_fill(mat, entries); 
    dblmat_fill(cmat, centries);

    dblmat_row_op2(mat, 1, 2);
    assert(dblmat_equal(cmat, mat) == TRUE);

    dblmat_delete(mat);
    dblmat_delete(cmat);

    return;
}

void test_dblmat_row_op3() {
    DoubleMatrix *mat = dblmat_create(3, 3);
    DoubleMatrix *cmat = dblmat_create(3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, -3, -3, -3, 7, 8, 9};
    dblmat_fill(mat, entries); 
    dblmat_fill(cmat, centries);

    dblmat_row_op3(mat, 1, 2, -1);
    assert(dblmat_equal(cmat, mat) == TRUE);

    dblmat_delete(mat);
    dblmat_delete(cmat);

    return;
}

void test_dblmat_product() {
    DoubleMatrix *m1 = dblmat_create(2,3);
    DoubleMatrix *m2 = dblmat_create(3,2);
    DoubleMatrix *p = dblmat_create(2,2);
    DoubleMatrix *pc = dblmat_create(2,2);

    double ent1[6] = {1, 1, 1, 2, 2, 2};
    double ent2[6] = {1, 1, 2, 2, 3, 3};
    double entc[4] = {6, 6, 12, 12};

    dblmat_fill(m1, ent1);
    dblmat_fill(m2, ent2);
    dblmat_fill(pc, entc);

    dblmat_product(m1, m2, p);
    assert(dblmat_equal(p, pc) == TRUE);

    dblmat_delete(m1);
    dblmat_delete(m2);
    dblmat_delete(p);
    dblmat_delete(pc);

    return;
}

void test_dblmat_had_product() {
    DoubleMatrix *m1 = dblmat_create(2,2);
    DoubleMatrix *m2 = dblmat_create(2,2);
    DoubleMatrix *p = dblmat_create(2,2);
    DoubleMatrix *pc = dblmat_create(2,2);

    double ent1[4] = {1, 1, 2, 2};
    double ent2[4] = {3, 3, -1, -1};
    double entc[4] = {3, 3, -2, -2};

    dblmat_fill(m1, ent1);
    dblmat_fill(m2, ent2);
    dblmat_fill(pc, entc);

    dblmat_had_product(m1, m2, p);
    assert(dblmat_equal(p, pc) == TRUE);

    dblmat_delete(m1);
    dblmat_delete(m2);
    dblmat_delete(p);
    dblmat_delete(pc);

    return;
}

void test_dblmat_scale() {
    DoubleMatrix *m = dblmat_create(2,2);
    double k = -2;
    DoubleMatrix *mc = dblmat_create(2,2);

    double ent[4] = {1, 1, 2, 2};
    double entc[4] = {-2, -2, -4, -4};

    dblmat_fill(m, ent);
    dblmat_fill(mc, entc);

    dblmat_scale(k, m);
    assert(dblmat_equal(m, mc) == TRUE);

    dblmat_delete(m);
    dblmat_delete(mc);

    return;
}

void test_dblmat_sum() {
    DoubleMatrix *m1 = dblmat_create(2,2);
    DoubleMatrix *m2 = dblmat_create(2,2);
    DoubleMatrix *p = dblmat_create(2,2);
    DoubleMatrix *pc = dblmat_create(2,2);

    double ent1[4] = {1, 4, 2, 2};
    double ent2[4] = {3, 3, -1, -1};
    double entc[4] = {4, 7, 1, 1};

    dblmat_fill(m1, ent1);
    dblmat_fill(m2, ent2);
    dblmat_fill(pc, entc);

    dblmat_sum(m1, m2, p);
    assert(dblmat_equal(p, pc) == TRUE);

    dblmat_delete(m1);
    dblmat_delete(m2);
    dblmat_delete(p);
    dblmat_delete(pc);

    return;
}

void test_dblmat_transpose() {
    DoubleMatrix *m = dblmat_create(2,2);
    DoubleMatrix *mc = dblmat_create(2,2);

    double ent[4] = {1, 4, 3, -1};
    double entc[4] = {1, 3, 4, -1};

    dblmat_fill(m, ent);
    dblmat_fill(mc, entc);

    dblmat_transpose(m);
    assert(dblmat_equal(m, mc) == TRUE);

    dblmat_delete(m);
    dblmat_delete(mc);

    return;
}
//===========================================================================================
//===========================================================================================

// run tests:
int main() {

    // data structure:
    test_dblmat_create();
    test_dblmat_set_entry();
    test_dblmat_get_entry();
    test_dblmat_fill();
    test_dblmat_equal();
    test_dblmat_get_rows();
    test_dblmat_get_cols();
    

    // mathematics:
    test_dblmat_row_op1();
    test_dblmat_row_op2();
    test_dblmat_row_op3();
    test_dblmat_product();
    test_dblmat_had_product();
    test_dblmat_scale();
    test_dblmat_sum();
    test_dblmat_transpose();
    
    return 0;
}

//===========================================================================================
//===========================================================================================