#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "array.h"
#include "matrix.h"

#define TRUE 1
#define FALSE 0


// data structure:

Matrix *mat_create(int n, int p) {
    assert(n * p <= MAX_SIZE);
    assert((n > 0) && (p > 0));

    Matrix *mat = malloc(sizeof(Matrix));
    assert(mat != NULL);
    mat->rows = n;
    mat->cols = p;
    mat->data = malloc(n * p * sizeof(double));
    assert(mat->data != NULL);

    return mat;
}

void mat_delete(Matrix *mat) {
    assert(mat != NULL);
    free(mat->data);
    free(mat);

    return;
}

// fill by row
// make sure length of entries is rows*cols
void mat_fill(Matrix *mat, double *entries) {
    int n = mat->rows;
    int p = mat->cols;

    int i;
    for (i=0; i<n*p; i++) {
        mat->data[i] = entries[i];
    }

    return;
}

void mat_set_entry(Matrix *mat, int i, int j, double val){
    assert((i <= mat->rows) && (j <= mat->cols));
    mat->data[i * mat->cols + j] = val;

    return;
}

double mat_get_entry(Matrix *mat, int i, int j) {
    assert((i <= mat->rows) && (j <= mat->cols));
    double entry = mat->data[i * mat->cols + j];

    return entry;
} 

void mat_print(Matrix *mat) {
    int rows = mat->rows;
    int cols = mat->cols;
    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            double entry = mat_get_entry(mat, i, j);
            printf("%6.2f ", entry);
        }
        printf("\n");
    }
}

int mat_equal(Matrix *mat1, Matrix *mat2) {
    int n1 = mat1->rows;
    int p1 = mat1->cols;
    int n2 = mat2->rows;
    int p2 = mat2->cols;
    int b1 = (n1 == n2);
    int b2 = (p1 == p2);
    int b3 = arr_equal(mat1->data, mat2->data, n1 * p1, n2 * p2);

    if (b1 && b2 && b3) {
        return TRUE;
    }
    return FALSE;

}

// make sure length of rows_arr is row_mat->rows
void mat_get_rows(Matrix *mat, Matrix *row_mat, int *rows_arr) {
    int rows = row_mat->rows;
    int cols = mat->cols;

    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            double entry = mat_get_entry(mat, rows_arr[i], j);
            mat_set_entry(row_mat, i, j, entry);
        }
    }

    return;
}

// make sure length of cols_arr is col_mat->cols
void mat_get_cols(Matrix *mat, Matrix *col_mat, int *cols_arr) {
    int rows = mat->rows;
    int cols = col_mat->cols;

    int i, j;
    for (j=0; j<cols; j++) {
        for (i=0; i<rows; i++) {
            double entry = mat_get_entry(mat, i, cols_arr[j]);
            mat_set_entry(col_mat, i, j, entry);
        }
    }

    return;
}
//--------------------------------------------------------------------------------

// mathematics:

// elementary row operations:

// (type 1) swaps rows i,j
void mat_row_op1(Matrix *mat, int i, int j) {
    int cols = mat->cols;
    int rows_arr[1] = {i};
    Matrix *temp_i = mat_create(1, cols);
    mat_get_rows(mat, temp_i, rows_arr);
    int col;
    for (col=0; col<cols; col=col+1) {
        double entry_j = mat_get_entry(mat, j, col);
        mat_set_entry(mat, i, col, entry_j);
        double entry_i = mat_get_entry(temp_i, 0, col);
        mat_set_entry(mat, j, col, entry_i);
    }

    mat_delete(temp_i);
    
    return;
}

// (type 2) multiplies row i by a constant k
void mat_row_op2(Matrix *mat, int i, double k) {
    int cols = mat->cols;
    int j;
    for (j=0; j<cols; j=j+1) {
        double entry = k * mat_get_entry(mat, i, j);
        mat_set_entry(mat, i, j, entry);
    }

    return;
}

// (type 3) multiplies row j by constant k and adds it to row i
void mat_row_op3(Matrix *mat, int i, int j, double k) {
    int cols = mat->cols;
    int col;
    for (col=0; col<cols; col=col+1) {
        double entry = mat_get_entry(mat, i, col) + k * mat_get_entry(mat, j, col);
        mat_set_entry(mat, i, col, entry);
    }

    return;
}

// standard matrix product
void mat_product(Matrix *A, Matrix *B, Matrix *prod) {
    assert(A->cols == B->rows);
    assert(A->rows == prod->rows);
    assert(B->cols == prod->cols);
    int m, n, p;
    m = A->rows;
    n = A->cols;
    p = B->cols;

    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<p; j=j+1) {

            double kron_prod[n];
            int k;
            for (k=0; k<n; k=k+1) {
                kron_prod[k] = mat_get_entry(A, i, k) * mat_get_entry(B, k, j);
            }

            double entry = arr_sum(kron_prod, n);
            mat_set_entry(prod, i, j, entry);
        }
    }

    return;
}

// Hadamard product
void mat_had_product(Matrix *A, Matrix *B, Matrix *prod) {
    assert(A->rows == B->rows);
    assert(A->cols == B->cols);
    assert(A->rows == prod->rows);
    assert(A->cols == prod->cols);

    int rows = A->rows;
    int cols = A->cols;

    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            double entry = mat_get_entry(A, i, j) * mat_get_entry(B, i, j);
            mat_set_entry(prod, i, j, entry);
        }
    }

    return;
}

void mat_scale(double k, Matrix *mat) {
    int rows = mat->rows;
    int cols = mat->cols;

    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            double entry = k * mat_get_entry(mat, i, j);
            mat_set_entry(mat, i, j, entry);
        }
    }

    return;
}

void mat_sum(Matrix *A, Matrix *B, Matrix *sum) {
    assert(A->rows == B->rows);
    assert(A->cols == B->cols);
    assert(A->rows == sum->rows);
    assert(A->cols == sum->cols);
    int m = A->rows;
    int n = A->cols;

    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<n; j=j+1) {
            double entry = mat_get_entry(A, i, j) + mat_get_entry(B, i, j);
            mat_set_entry(sum, i, j, entry);
        }
    }

    return;
}

void mat_transpose(Matrix *mat) {
    int rows = mat->rows;
    int cols = mat->cols;

    int i, j;
    for (i=1; i<rows; i++) {
        for (j=0; j<i; j++) {
            double entry_ij = mat_get_entry(mat, i, j);
            double entry_ji = mat_get_entry(mat, j, i);
            mat_set_entry(mat, j, i, entry_ij);
            mat_set_entry(mat, i, j, entry_ji);
        }
    }

    return;
}