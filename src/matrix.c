#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/array.h"
#include "../include/matrix.h"

#define TRUE 1
#define FALSE 0


// data structure:

DoubleMatrix *dblmat_create(int n, int p) {
    assert(n * p <= MAX_SIZE);
    assert((n > 0) && (p > 0));

    DoubleMatrix *mat = malloc(sizeof(DoubleMatrix));
    assert(mat != NULL);
    mat->nrow = n;
    mat->ncol = p;
    mat->data = malloc(n * p * sizeof(double));
    assert(mat->data != NULL);

    return mat;
}

void dblmat_delete(DoubleMatrix *mat) {
    assert(mat != NULL);
    free(mat->data);
    free(mat);

    return;
}

void dblmat_print(DoubleMatrix *mat) {
    int rows = mat->nrow;
    int cols = mat->ncol;
    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            double entry = dblmat_get_entry(mat, i, j);
            printf("%6.2f ", entry);
        }
        printf("\n");
    }
}

void dblmat_set_entry(DoubleMatrix *mat, int i, int j, double val){
    assert((i <= mat->nrow) && (j <= mat->ncol));
    mat->data[i * mat->ncol + j] = val;

    return;
}

double dblmat_get_entry(DoubleMatrix *mat, int i, int j) {
    assert((i <= mat->nrow) && (j <= mat->ncol));
    double entry = mat->data[i * mat->ncol + j];

    return entry;
} 

// fill by row
// make sure length of entries is rows*cols
void dblmat_fill(DoubleMatrix *mat, double *entries) {
    int n = mat->nrow;
    int p = mat->ncol;

    int i;
    for (i=0; i<n*p; i++) {
        mat->data[i] = entries[i];
    }

    return;
}

int dblmat_equal(DoubleMatrix *mat1, DoubleMatrix *mat2) {
    int n1 = mat1->nrow;
    int p1 = mat1->ncol;
    int n2 = mat2->nrow;
    int p2 = mat2->ncol;
    int b1 = (n1 == n2);
    int b2 = (p1 == p2);
    int b3 = arr_equal(mat1->data, mat2->data, n1 * p1, n2 * p2);

    if (b1 && b2 && b3) {
        return TRUE;
    }
    return FALSE;

}

// make sure length of rows_arr is row_mat->nrow
void dblmat_get_rows(DoubleMatrix *mat, DoubleMatrix *row_mat, int *rows_arr) {
    int rows = row_mat->nrow;
    int cols = mat->ncol;

    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            double entry = dblmat_get_entry(mat, rows_arr[i], j);
            dblmat_set_entry(row_mat, i, j, entry);
        }
    }

    return;
}

// make sure length of cols_arr is col_mat->ncol
void dblmat_get_cols(DoubleMatrix *mat, DoubleMatrix *col_mat, int *cols_arr) {
    int rows = mat->nrow;
    int cols = col_mat->ncol;

    int i, j;
    for (j=0; j<cols; j++) {
        for (i=0; i<rows; i++) {
            double entry = dblmat_get_entry(mat, i, cols_arr[j]);
            dblmat_set_entry(col_mat, i, j, entry);
        }
    }

    return;
}
//--------------------------------------------------------------------------------

// mathematics:

// elementary row operations:

// (type 1) swaps rows i,j
void dblmat_row_op1(DoubleMatrix *mat, int i, int j) {
    int cols = mat->ncol;
    int rows_arr[1] = {i};
    DoubleMatrix *temp_i = dblmat_create(1, cols);
    dblmat_get_rows(mat, temp_i, rows_arr);
    int col;
    for (col=0; col<cols; col=col+1) {
        double entry_j = dblmat_get_entry(mat, j, col);
        dblmat_set_entry(mat, i, col, entry_j);
        double entry_i = dblmat_get_entry(temp_i, 0, col);
        dblmat_set_entry(mat, j, col, entry_i);
    }

    dblmat_delete(temp_i);
    
    return;
}

// (type 2) multiplies row i by a constant k
void dblmat_row_op2(DoubleMatrix *mat, int i, double k) {
    int cols = mat->ncol;
    int j;
    for (j=0; j<cols; j=j+1) {
        double entry = k * dblmat_get_entry(mat, i, j);
        dblmat_set_entry(mat, i, j, entry);
    }

    return;
}

// (type 3) multiplies row j by constant k and adds it to row i
void dblmat_row_op3(DoubleMatrix *mat, int i, int j, double k) {
    int cols = mat->ncol;
    int col;
    for (col=0; col<cols; col=col+1) {
        double entry = dblmat_get_entry(mat, i, col) + k * dblmat_get_entry(mat, j, col);
        dblmat_set_entry(mat, i, col, entry);
    }

    return;
}

// standard matrix product
void dblmat_product(DoubleMatrix *A, DoubleMatrix *B, DoubleMatrix *prod) {
    assert(A->ncol == B->nrow);
    assert(A->nrow == prod->nrow);
    assert(B->ncol == prod->ncol);
    int m, n, p;
    m = A->nrow;
    n = A->ncol;
    p = B->ncol;

    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<p; j=j+1) {

            double kron_prod[n];
            int k;
            for (k=0; k<n; k=k+1) {
                kron_prod[k] = dblmat_get_entry(A, i, k) * dblmat_get_entry(B, k, j);
            }

            double entry = arr_sum(kron_prod, n);
            dblmat_set_entry(prod, i, j, entry);
        }
    }

    return;
}

// Hadamard product
void dblmat_had_product(DoubleMatrix *A, DoubleMatrix *B, DoubleMatrix *prod) {
    assert(A->nrow == B->nrow);
    assert(A->ncol == B->ncol);
    assert(A->nrow == prod->nrow);
    assert(A->ncol == prod->ncol);

    int rows = A->nrow;
    int cols = A->ncol;

    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            double entry = dblmat_get_entry(A, i, j) * dblmat_get_entry(B, i, j);
            dblmat_set_entry(prod, i, j, entry);
        }
    }

    return;
}

void dblmat_scale(double k, DoubleMatrix *mat) {
    int rows = mat->nrow;
    int cols = mat->ncol;

    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            double entry = k * dblmat_get_entry(mat, i, j);
            dblmat_set_entry(mat, i, j, entry);
        }
    }

    return;
}

void dblmat_sum(DoubleMatrix *A, DoubleMatrix *B, DoubleMatrix *sum) {
    assert(A->nrow == B->nrow);
    assert(A->ncol == B->ncol);
    assert(A->nrow == sum->nrow);
    assert(A->ncol == sum->ncol);
    int m = A->nrow;
    int n = A->ncol;

    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<n; j=j+1) {
            double entry = dblmat_get_entry(A, i, j) + dblmat_get_entry(B, i, j);
            dblmat_set_entry(sum, i, j, entry);
        }
    }

    return;
}

void dblmat_transpose(DoubleMatrix *mat) {
    int rows = mat->nrow;
    int cols = mat->ncol;

    int i, j;
    for (i=1; i<rows; i++) {
        for (j=0; j<i; j++) {
            double entry_ij = dblmat_get_entry(mat, i, j);
            double entry_ji = dblmat_get_entry(mat, j, i);
            dblmat_set_entry(mat, j, i, entry_ij);
            dblmat_set_entry(mat, i, j, entry_ji);
        }
    }

    return;
}