#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"
#include "matrix.h"

#define TRUE 1
#define FALSE 0

// define tests:

// data structure: 

void test_mat_create() {
    Matrix *mat = mat_create(7, 8);
    Matrix *mat2 = mat_create(2, 3);
    assert(mat2->rows == 2);
    assert(mat2->cols == 3);
    mat_delete(mat2);

    return;
}

void test_mat_set_entry() {
    Matrix *mat = mat_create(3, 4);
    mat_set_entry(mat, 1, 2, .5);
    assert(mat->data[6] == .5);
    mat_delete(mat);

    return;
}

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
        assert(mat->data[i] = i+1);
    }

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

void test_mat_copy_rows() {

}

void test_mat_copy_cols() {
    
} 

// mathematics: 


//===========================================================================================
//===========================================================================================

// run tests:
int main() {
    test_mat_create();
    test_mat_set_entry();
    test_mat_get_entry();
    test_mat_fill();
    test_mat_equal();
    
    return 0;
}

//===========================================================================================
//===========================================================================================