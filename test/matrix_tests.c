#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/array.h"
#include "../include/matrix.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

// define tests:

// data structure: 

void test_mat_create() {
    // DBL ======================================
    Matrix *mat2 = mat_create(DBL, 2, 3);
    assert(mat2->nrow == 2);
    assert(mat2->ncol == 3);
    mat_delete(mat2);

    return;
}

void test_mat_print() {
    // DBL ======================================
    Matrix *mat = mat_create(DBL, 2, 3);
    double entries[6] = {1, 2, 3, 4, 5, 6};
    mat_fill_dbl(mat, entries);

    mat_print(mat);
    mat_delete(mat);

    // PLY ======================================
    Matrix *mat2 = mat_create(PLY, 1, 2);
    tvalue entries2[2];
    tvalue entry0;
    tvalue entry1;

    Polynomial *p = ply_create(DBL, 2);
    double coefs[3] = {-1.5, 3, 2};
    ply_fill_dbl(p, coefs);
    entry0.type = PLY;
    entry0.val.plyval = p;

    t_copy(entry0, &entry1);
    entries2[0] = entry0;
    entries2[1] = entry1;

    mat_fill(mat2, entries2);
    mat_print(mat2);

    ply_delete(p);
    mat_delete(mat2);

    return;
}

void test_mat_set_entry() {
    // DBL ======================================
    tvalue entry;
    t_dbl(.5, &entry);
    Matrix *mat = mat_create(DBL, 3, 4);

    mat_set_entry(mat, 1, 2, entry);
    assert(mat->entries[6].val.dblval == .5);
    mat_delete(mat);

    // PLY ======================================
    Matrix *mat2 = mat_create(PLY, 1, 1);

    Polynomial *p = ply_create(DBL, 2);
    double coefs[3] = {.5, 2, -1.2};
    ply_fill_dbl(p, coefs);

    tvalue entry2;
    entry2.type = PLY;
    entry2.val.plyval = p;

    mat_set_entry(mat2, 0, 0, entry2);

    assert(t_equal(mat_get_entry(mat2, 0, 0), entry2));

    ply_delete(p);
    mat_delete(mat2);

    //  ======================================


    return;
}

void test_mat_get_entry() {
    // DBL ======================================
    tvalue entry;
    t_dbl(.5, &entry);
    Matrix *mat = mat_create(DBL, 3, 4);
    mat_set_entry(mat, 1, 2, entry);
    assert(mat_get_entry(mat, 1, 2).val.dblval == .5);
    mat_delete(mat);

    // PLY ======================================
    Matrix *mat2 = mat_create(PLY, 1, 1);

    Polynomial *p = ply_create(DBL, 2);
    double coefs[3] = {.5, 2, -1.2};
    ply_fill_dbl(p, coefs);

    tvalue entry2;
    entry2.type = PLY;
    entry2.val.plyval = p;

    mat_set_entry(mat2, 0, 0, entry2);

    assert(t_equal(mat_get_entry(mat2, 0, 0), entry2));

    ply_delete(p);
    mat_delete(mat2);

    //  ======================================

    return;
}

void test_mat_fill() {
    // DBL ======================================
    Matrix *mat = mat_create(DBL, 2, 3);
    double dentries[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    tvalue tentries[6];
    t_dbls(dentries, tentries, 6);
    mat_fill(mat, tentries);
    
    int i;
    for (i=1; i<6; i++) {
        assert(mat->entries[i].val.dblval == i+1);
    }

    mat_delete(mat);

    // PLY ======================================
    Matrix *mat_ply = mat_create(PLY, 1, 2);
    tvalue entries_ply[2];
    tvalue entry_ply0;
    tvalue entry_ply1;

    Polynomial *p = ply_create(DBL, 2);
    double coefs[3] = {-1.5, 3, 2};
    ply_fill_dbl(p, coefs);
    entry_ply0.type = PLY;
    entry_ply0.val.plyval = p;

    t_copy(entry_ply0, &entry_ply1);
    entries_ply[0] = entry_ply0;
    entries_ply[1] = entry_ply1;

    mat_fill(mat_ply, entries_ply);
    tvalue ply00 = mat_get_entry(mat_ply, 0, 0);
    tvalue ply01 = mat_get_entry(mat_ply, 0, 1);
    assert(t_equal(ply00, entry_ply0) == TRUE);
    assert(t_equal(ply01, entry_ply1) == TRUE);

    ply_delete(p);
    mat_delete(mat_ply);

    //  ======================================


    return;
}

void test_mat_fill_dbl() {
    Matrix *mat = mat_create(DBL, 2, 3);
    double entries[6] = {1, 2, 3, 4, 5, 6};
    mat_fill_dbl(mat, entries);

    int i;
    for (i=0; i<6; i++) {
        assert(mat->entries[i].val.dblval == i+1);
    }
    mat_delete(mat);

    return;
}

void test_mat_equal() {
    // DBL ======================================
    Matrix *mat1 = mat_create(DBL, 2, 3);
    double entries1[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    mat_fill_dbl(mat1, entries1);

    Matrix *mat2 = mat_create(DBL, 1, 3);
    double entries2[3] = {1.0, 2.0, 3.0};
    mat_fill_dbl(mat2, entries2);
    
    Matrix *mat3 = mat_create(DBL, 2, 3);
    double entries3[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 7.0};
    mat_fill_dbl(mat3, entries3);

    Matrix *mat4 = mat_create(DBL, 2, 3);
    double entries4[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    mat_fill_dbl(mat4, entries4);

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
    // DBL ======================================
    Matrix *m = mat_create(DBL, 3, 3);
    Matrix *rm = mat_create(DBL, 2, 3);
    Matrix *rmc = mat_create(DBL, 2, 3);

    double m_entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double rmc_entries[6] = {4, 5, 6, 7, 8, 9};

    mat_fill_dbl(m, m_entries);
    mat_fill_dbl(rmc, rmc_entries);
    int rows_arr[2] = {1, 2};
    mat_get_rows(m, rm, rows_arr);

    assert(mat_equal(rm, rmc));
    mat_delete(m);
    mat_delete(rm);
    mat_delete(rmc);

    return;
}

void test_mat_get_cols() {
    // DBL ======================================
    Matrix *m = mat_create(DBL, 3, 3);
    Matrix *cm = mat_create(DBL, 3, 2);
    Matrix *cmc = mat_create(DBL, 3, 2);

    double m_entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double cmc_entries[6] = {1, 2, 4, 5, 7, 8};


    mat_fill_dbl(m, m_entries);
    mat_fill_dbl(cmc, cmc_entries);
    int cols_arr[2] = {0, 1};
    mat_get_cols(m, cm, cols_arr);

    assert(mat_equal(cm, cmc));
    mat_delete(m);
    mat_delete(cm);
    mat_delete(cmc);

    return; 
} 

void test_mat_join() {
    // DBL ======================================

    //vertical join, axis = 0:
    Matrix *A = mat_create(DBL, 2, 3);
    Matrix *B = mat_create(DBL, 1, 3);
    Matrix *J = mat_create(DBL, 3, 3);
    Matrix *C = mat_create(DBL, 3, 3);

    double entriesA[6] = {1, 2, 3, 4 ,5, 6};
    double entriesB[3] = {7, 8, 9};
    double entriesC[9] = {1, 2, 3, 4 ,5, 6, 7, 8, 9};

    mat_fill_dbl(A, entriesA);
    mat_fill_dbl(B, entriesB);
    mat_fill_dbl(C, entriesC);

    mat_join(A, B, 0, J);

    assert(mat_equal(J, C) == TRUE);

    mat_delete(A);
    mat_delete(B);
    mat_delete(J);
    mat_delete(C);
    
    //horizontal join, axis = 1:
    Matrix *D = mat_create(DBL, 3, 2);
    Matrix *E = mat_create(DBL, 3, 1);
    Matrix *K = mat_create(DBL, 3, 3);
    Matrix *F = mat_create(DBL, 3, 3);

    double entriesD[6] = {1, 2, 4, 5, 7, 8};
    double entriesE[3] = {3, 6, 9};
    double entriesF[9] = {1, 2, 3, 4 ,5, 6, 7, 8, 9};

    mat_fill_dbl(D, entriesD);
    mat_fill_dbl(E, entriesE);
    mat_fill_dbl(F, entriesF);

    mat_join(D, E, 1, K);

    assert(mat_equal(K, F) == TRUE);

    mat_delete(D);
    mat_delete(E);
    mat_delete(K);
    mat_delete(F);

    return;
}

// mathematics: 

void test_mat_row_op1() {
    // DBL ======================================
    Matrix *mat = mat_create(DBL, 3, 3);
    Matrix *cmat = mat_create(DBL, 3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, 7, 8, 9, 4, 5, 6};

    mat_fill_dbl(mat, entries); 
    mat_fill_dbl(cmat, centries);

    mat_row_op1(mat, 1, 2);
    assert(mat_equal(cmat, mat) == TRUE);

    mat_delete(mat);
    mat_delete(cmat);

    return;
}

void test_mat_row_op2() {
    // DBL ======================================
    Matrix *mat = mat_create(DBL, 3, 3);
    Matrix *cmat = mat_create(DBL, 3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, 8, 10, 12, 7, 8, 9};
    mat_fill_dbl(mat, entries); 
    mat_fill_dbl(cmat, centries);

    tvalue tval;
    t_dbl(2, &tval);

    mat_row_op2(mat, 1, tval);
    assert(mat_equal(cmat, mat) == TRUE);

    mat_delete(mat);
    mat_delete(cmat);

    return;
}

void test_mat_row_op3() {
    // DBL ======================================
    Matrix *mat = mat_create(DBL, 3, 3);
    Matrix *cmat = mat_create(DBL, 3, 3);
    double entries[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double centries[9] = {1, 2, 3, -3, -3, -3, 7, 8, 9};
    mat_fill_dbl(mat, entries); 
    mat_fill_dbl(cmat, centries);

    tvalue tval;
    t_dbl(-1, &tval);

    mat_row_op3(mat, 1, 2, tval);
    assert(mat_equal(cmat, mat) == TRUE);

    mat_delete(mat);
    mat_delete(cmat);

    return;
}

void test_mat_product() {
    // DBL ======================================
    Matrix *m1 = mat_create(DBL, 2,3);
    Matrix *m2 = mat_create(DBL, 3,2);
    Matrix *p = mat_create(DBL, 2,2);
    Matrix *pc = mat_create(DBL, 2,2);

    double ent1[6] = {1, 1, 1, 2, 2, 2};
    double ent2[6] = {1, 1, 2, 2, 3, 3};
    double entc[4] = {6, 6, 12, 12};

    mat_fill_dbl(m1, ent1);
    mat_fill_dbl(m2, ent2);
    mat_fill_dbl(pc, entc);

    mat_product(m1, m2, p);
    assert(mat_equal(p, pc) == TRUE);

    mat_delete(m1);
    mat_delete(m2);
    mat_delete(p);
    mat_delete(pc);

    return;
}

void test_mat_had_product() {
    // DBL ======================================
    Matrix *m1 = mat_create(DBL, 2,2);
    Matrix *m2 = mat_create(DBL, 2,2);
    Matrix *p = mat_create(DBL, 2,2);
    Matrix *pc = mat_create(DBL, 2,2);

    double ent1[4] = {1, 1, 2, 2};
    double ent2[4] = {3, 3, -1, -1};
    double entc[4] = {3, 3, -2, -2};

    mat_fill_dbl(m1, ent1);
    mat_fill_dbl(m2, ent2);
    mat_fill_dbl(pc, entc);

    mat_had_product(m1, m2, p);
    assert(mat_equal(p, pc) == TRUE);

    mat_delete(m1);
    mat_delete(m2);
    mat_delete(p);
    mat_delete(pc);

    return;
}

void test_mat_scale() {
    // DBL ======================================
    Matrix *m = mat_create(DBL, 2,2);
    Matrix *mc = mat_create(DBL, 2,2);

    tvalue k; 
    t_dbl(-2, &k);

    double ent[4] = {1, 1, 2, 2};
    double entc[4] = {-2, -2, -4, -4};

    mat_fill_dbl(m, ent);
    mat_fill_dbl(mc, entc);

    mat_scale(k, m);
    assert(mat_equal(m, mc) == TRUE);

    mat_delete(m);
    mat_delete(mc);

    return;
}

void test_mat_sum() {
    // DBL ======================================
    Matrix *m1 = mat_create(DBL, 2,2);
    Matrix *m2 = mat_create(DBL, 2,2);
    Matrix *p = mat_create(DBL, 2,2);
    Matrix *pc = mat_create(DBL, 2,2);

    double ent1[4] = {1, 4, 2, 2};
    double ent2[4] = {3, 3, -1, -1};
    double entc[4] = {4, 7, 1, 1};

    mat_fill_dbl(m1, ent1);
    mat_fill_dbl(m2, ent2);
    mat_fill_dbl(pc, entc);

    mat_sum(m1, m2, p);
    assert(mat_equal(p, pc) == TRUE);

    mat_delete(m1);
    mat_delete(m2);
    mat_delete(p);
    mat_delete(pc);

    return;
}

void test_mat_transpose() {
    // DBL ======================================
    Matrix *m = mat_create(DBL, 2,2);
    Matrix *mc = mat_create(DBL, 2,2);

    double ent[4] = {1, 4, 3, -1};
    double entc[4] = {1, 3, 4, -1};

    mat_fill_dbl(m, ent);
    mat_fill_dbl(mc, entc);

    mat_transpose(m);
    assert(mat_equal(m, mc) == TRUE);

    mat_delete(m);
    mat_delete(mc);

    return;
}

// algorithms:

void test_mat_ref() {
    // DBL ======================================
    Matrix *A = mat_create(DBL, 3, 3);
    Matrix *B = mat_create(DBL, 4, 3);
    Matrix *checkA = mat_create(DBL, 3, 3);
    Matrix *checkB = mat_create(DBL, 4, 3);

    double A_entries[9] = {2, 4, 6, 2, 4, 2, 1, 3, 1};
    double cA_entries[9] = {1, 2, 3, 0, 1, -2, 0, 0, 1};
    double B_entries[12] = {-1, -3, -2, -2, 0, 2, 2, 3, -2, 3, -3, -1};
    double cB_entries[12] = {1, 3, 2, 0, 1, 1, 0, 0, 1, 0, 0, 0};


    mat_fill_dbl(A, A_entries);
    mat_fill_dbl(checkA, cA_entries);
    mat_fill_dbl(B, B_entries);
    mat_fill_dbl(checkB, cB_entries);

    mat_ref(A);
    mat_ref(B);

    assert(mat_equal(A, checkA) == TRUE);
     assert(mat_equal(B, checkB) == TRUE);

    mat_delete(A);
    mat_delete(checkA);
    mat_delete(B);
    mat_delete(checkB);

    return;
}

void test_mat_rref() {
    // DBL ======================================
    Matrix *A = mat_create(DBL, 3, 3);
    Matrix *B = mat_create(DBL, 4, 3);
    Matrix *checkA = mat_create(DBL, 3, 3);
    Matrix *checkB = mat_create(DBL, 4, 3);

    double A_entries[9] = {2, 4, 6, 2, 4, 2, 1, 3, 1};
    double cA_entries[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    double B_entries[12] = {-1, -3, -2, -2, 0, 2, 2, 3, -2, 3, -3, -1};
    double cB_entries[12] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};


    mat_fill_dbl(A, A_entries);
    mat_fill_dbl(checkA, cA_entries);
    mat_fill_dbl(B, B_entries);
    mat_fill_dbl(checkB, cB_entries);

    mat_rref(A);
    mat_rref(B);

    assert(mat_equal(A, checkA) == TRUE);
     assert(mat_equal(B, checkB) == TRUE);

    mat_delete(A);
    mat_delete(checkA);
    mat_delete(B);
    mat_delete(checkB);

    return;
}

void test_mat_solve() {
    // DBL ======================================
    Matrix *A = mat_create(DBL, 3, 3);
    Matrix *b = mat_create(DBL, 3, 1);
    Matrix *x = mat_create(DBL, 3, 1);
    Matrix *checkx = mat_create(DBL, 3, 1);

    double entries_A[9] = {1, 1, 1, 0, 2, 5, 2, 5, -1};
    double entries_b[9] = {6, -4, 27};
    double entries_checkx[9] = {5, 3, -2};

    mat_fill_dbl(A, entries_A);
    mat_fill_dbl(b, entries_b);
    mat_fill_dbl(checkx, entries_checkx);

    mat_solve(A, b, x);

    assert(mat_equal(x, checkx) == TRUE);

    mat_delete(A);
    mat_delete(b);
    mat_delete(x);
    mat_delete(checkx);

    return;
}
//===========================================================================================
//===========================================================================================

// run tests:
int main() {

    // data structure:
    //test_mat_print();
    test_mat_create();
    test_mat_set_entry();
    test_mat_get_entry();
    test_mat_fill();
    test_mat_equal(); 
    test_mat_get_rows();
    test_mat_get_cols();
    test_mat_join();
    

    // mathematics:
    test_mat_row_op1();
    test_mat_row_op2();
    test_mat_row_op3();
    test_mat_product();
    test_mat_had_product();
    test_mat_scale();
    test_mat_sum();
    test_mat_transpose();

    // algorithms:
    test_mat_ref();
    test_mat_rref();
    test_mat_solve();
    
    return 0;
}

//===========================================================================================
//===========================================================================================