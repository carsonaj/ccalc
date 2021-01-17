#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/array.h"
#include "../include/matrix.h"

#define TRUE 1
#define FALSE 0

// define tests:

// data structure: 

void test_mat_create() {
    Matrix *mat2 = mat_create(DBL, 2, 3);
    assert(mat2->nrow == 2);
    assert(mat2->ncol == 3);
    mat_delete(mat2);

    return;
}

void test_mat_set_entry() {
    Matrix *mat = mat_create(DBL, 3, 4);
    mat_set_entry(mat, 1, 2, tdbl(.5));
    assert(mat->data.vals.dblvals[6] == .5);
    mat_delete(mat);

    return;
}
/*
void test_mat_get_entry() {
    Matrix *mat = mat_create(3, 4);
    mat_set_entry(mat, 1, 2, .5);
    assert(mat_get_entry(mat, 1, 2) == .5);
    mat_delete(mat);

    return;
}

void test_mat_fill() {
    Matrix *mat = mat_create(2, 3);
    double entries[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    mat_fill(mat, entries);
    
    int i;
    for (i=1; i<6; i++) {
        assert(mat->data[i] == i+1);
    }

    mat_delete(mat);

    return;
}

void test_mat_equal() {
    Matrix *mat1 = mat_create(2, 3);
    double entries1[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    mat_fill(mat1, entries1);
    Matrix *mat2 = mat_create(1, 3);
    double entries2[3] = {1.0, 2.0, 3.0};
    mat_fill(mat2, entries2);
    Matrix *mat3 = mat_create(2, 3);
    double entries3[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 7.0};
    mat_fill(mat3, entries3);
    Matrix *mat4 = mat_create(2, 3);
    double entries4[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    mat_fill(mat4, entries4);

    assert(mat_equal(mat1, mat2) == FALSE);
    assert(mat_equal(mat1, mat3) == FALSE);
    assert(mat_equal(mat1, mat4) == TRUE);

    mat_delete(mat1);
    mat_delete(mat2);
    mat_delete(mat3);
    mat_delete(mat4);

    return;
}

void test_mat_get_rows() {
    Matrix *m = mat_create(3, 3);
    Matrix *rm = mat_create(2, 3);
    Matrix *rmc = mat_create(2, 3);

    double m_entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double rmc_entries[6] = {4, 5, 6, 7, 8, 9};

    mat_fill(m, m_entries);
    mat_fill(rmc, rmc_entries);
    int rows_arr[2] = {1, 2};
    mat_get_rows(m, rm, rows_arr);

    assert(mat_equal(rm, rmc));
    mat_delete(m);
    mat_delete(rm);
    mat_delete(rmc);

    return;
}

void test_mat_get_cols() {
    Matrix *m = mat_create(3, 3);
    Matrix *cm = mat_create(3, 2);
    Matrix *cmc = mat_create(3, 2);

    double m_entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double cmc_entries[6] = {1, 2, 4, 5, 7, 8};

    mat_fill(m, m_entries);
    mat_fill(cmc, cmc_entries);
    int cols_arr[2] = {0, 1};
    mat_get_cols(m, cm, cols_arr);

    assert(mat_equal(cm, cmc));
    mat_delete(m);
    mat_delete(cm);
    mat_delete(cmc);

    return; 
} 

// mathematics: 

void test_mat_row_op1() {
    Matrix *mat = mat_create(3, 3);
    Matrix *cmat = mat_create(3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, 7, 8, 9, 4, 5, 6};
    mat_fill(mat, entries); 
    mat_fill(cmat, centries);

    mat_row_op1(mat, 1, 2);
    assert(mat_equal(cmat, mat) == TRUE);

    mat_delete(mat);
    mat_delete(cmat);

    return;
}

void test_mat_row_op2() {
    Matrix *mat = mat_create(3, 3);
    Matrix *cmat = mat_create(3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, 8, 10, 12, 7, 8, 9};
    mat_fill(mat, entries); 
    mat_fill(cmat, centries);

    mat_row_op2(mat, 1, 2);
    assert(mat_equal(cmat, mat) == TRUE);

    mat_delete(mat);
    mat_delete(cmat);

    return;
}

void test_mat_row_op3() {
    Matrix *mat = mat_create(3, 3);
    Matrix *cmat = mat_create(3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, -3, -3, -3, 7, 8, 9};
    mat_fill(mat, entries); 
    mat_fill(cmat, centries);

    mat_row_op3(mat, 1, 2, -1);
    assert(mat_equal(cmat, mat) == TRUE);

    mat_delete(mat);
    mat_delete(cmat);

    return;
}

void test_mat_product() {
    Matrix *m1 = mat_create(2,3);
    Matrix *m2 = mat_create(3,2);
    Matrix *p = mat_create(2,2);
    Matrix *pc = mat_create(2,2);

    double ent1[6] = {1, 1, 1, 2, 2, 2};
    double ent2[6] = {1, 1, 2, 2, 3, 3};
    double entc[4] = {6, 6, 12, 12};

    mat_fill(m1, ent1);
    mat_fill(m2, ent2);
    mat_fill(pc, entc);

    mat_product(m1, m2, p);
    assert(mat_equal(p, pc) == TRUE);

    mat_delete(m1);
    mat_delete(m2);
    mat_delete(p);
    mat_delete(pc);

    return;
}

void test_mat_had_product() {
    Matrix *m1 = mat_create(2,2);
    Matrix *m2 = mat_create(2,2);
    Matrix *p = mat_create(2,2);
    Matrix *pc = mat_create(2,2);

    double ent1[4] = {1, 1, 2, 2};
    double ent2[4] = {3, 3, -1, -1};
    double entc[4] = {3, 3, -2, -2};

    mat_fill(m1, ent1);
    mat_fill(m2, ent2);
    mat_fill(pc, entc);

    mat_had_product(m1, m2, p);
    assert(mat_equal(p, pc) == TRUE);

    mat_delete(m1);
    mat_delete(m2);
    mat_delete(p);
    mat_delete(pc);

    return;
}

void test_mat_scale() {
    Matrix *m = mat_create(2,2);
    double k = -2;
    Matrix *mc = mat_create(2,2);

    double ent[4] = {1, 1, 2, 2};
    double entc[4] = {-2, -2, -4, -4};

    mat_fill(m, ent);
    mat_fill(mc, entc);

    mat_scale(k, m);
    assert(mat_equal(m, mc) == TRUE);

    mat_delete(m);
    mat_delete(mc);

    return;
}

void test_mat_sum() {
    Matrix *m1 = mat_create(2,2);
    Matrix *m2 = mat_create(2,2);
    Matrix *p = mat_create(2,2);
    Matrix *pc = mat_create(2,2);

    double ent1[4] = {1, 4, 2, 2};
    double ent2[4] = {3, 3, -1, -1};
    double entc[4] = {4, 7, 1, 1};

    mat_fill(m1, ent1);
    mat_fill(m2, ent2);
    mat_fill(pc, entc);

    mat_sum(m1, m2, p);
    assert(mat_equal(p, pc) == TRUE);

    mat_delete(m1);
    mat_delete(m2);
    mat_delete(p);
    mat_delete(pc);

    return;
}

void test_mat_transpose() {
    Matrix *m = mat_create(2,2);
    Matrix *mc = mat_create(2,2);

    double ent[4] = {1, 4, 3, -1};
    double entc[4] = {1, 3, 4, -1};

    mat_fill(m, ent);
    mat_fill(mc, entc);

    mat_transpose(m);
    assert(mat_equal(m, mc) == TRUE);

    mat_delete(m);
    mat_delete(mc);

    return;
}
//===========================================================================================
//===========================================================================================
*/
// run tests:
int main() {

    // data structure:
    test_mat_create();
    test_mat_set_entry();/*
    test_mat_get_entry();
    test_mat_fill();
    test_mat_equal();
    test_mat_get_rows();
    test_mat_get_cols();
    

    // mathematics:
    test_mat_row_op1();
    test_mat_row_op2();
    test_mat_row_op3();
    test_mat_product();
    test_mat_had_product();
    test_mat_scale();
    test_mat_sum();
    test_mat_transpose();
    */
    return 0;
}

//===========================================================================================
//===========================================================================================