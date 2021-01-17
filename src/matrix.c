#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/array.h"
#include "../include/matrix.h"

#define TRUE 1
#define FALSE 0


// data structure:

Matrix *mat_create(dtype t, int n, int p) {
    assert(n * p <= MAX_SIZE);
    assert((n > 0) && (p > 0));


    Matrix *mat = malloc(sizeof(Matrix));
    assert(mat != NULL);
    mat->type = t;
    mat->nrow = n;
    mat->ncol = p;
    mat->entries = malloc((n * p) * sizeof(tvalue));

    assert(mat->entries != NULL);

    return mat;
}

void mat_delete(Matrix *mat) {
    assert(mat != NULL);
    free(mat->entries);
    free(mat);

    return;
}

void mat_print(Matrix *mat) {
    dtype t = mat->type;
    int rows = mat->nrow;
    int cols = mat->ncol;
    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            tvalue entry = mat_get_entry(mat, i, j);
            switch(t) {
                case DBL: 
                    printf("%6.2f ", entry.val.dblval);
                    break;
                case PLY:
                    break;
            }
        }
        printf("\n");
    }
}

void mat_set_entry(Matrix *mat, int i, int j, tvalue tval){
    dtype t = mat->type;
    dtype s = tval.type;
    assert(t == s);
    assert((i <= mat->nrow) && (j <= mat->ncol));
    mat->entries[i * mat->ncol + j] = tval;
    
    return;
}

tvalue mat_get_entry(Matrix *mat, int i, int j) {
    assert((i <= mat->nrow) && (j <= mat->ncol));
    tvalue entry = mat->entries[i * mat->ncol + j];

    return entry;
} 

// fill by row
// make sure length of entries is rows*cols
void mat_fill(Matrix *mat, tvalue *entries) {
    dtype t = mat->type;
    int n = mat->nrow;
    int p = mat->ncol;

    int i;
    for (i=0; i<n*p; i++) {
        dtype s = entries[i].type;
        assert(t == s);
        mat->entries[i] = entries[i];
    }

    return;
}

int mat_equal(Matrix *mat1, Matrix *mat2) {
    dtype t1 = mat1->type;
    dtype t2 = mat2->type;
    int b1 = (t1 == t2);
    if (b1 == FALSE) {
        return FALSE;
    }

    int n1 = mat1->nrow;
    int p1 = mat1->ncol;
    int n2 = mat2->nrow;
    int p2 = mat2->ncol;
    int b2 = (n1 == n2);
    int b3 = (p1 == p2);
    if ((b2 && b3) == FALSE) {
        return FALSE;
    }

    int b4 = arr_equal(mat1->entries, mat2->entries, n1 * p1, n2 * p2);
    if (b4 == FALSE) {
        return FALSE;
    }

    return TRUE;

}

// make sure length of rows_arr is row_mat->nrow
void mat_get_rows(Matrix *mat, Matrix *row_mat, int *rows_arr) {
    dtype s = mat->type;
    dtype t = row_mat->type;
    assert(s == t);
    int rows = row_mat->nrow;
    int cols = mat->ncol;

    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            tvalue entry = mat_get_entry(mat, rows_arr[i], j);
            mat_set_entry(row_mat, i, j, entry);
        }
    }

    return;
}

// make sure length of cols_arr is col_mat->ncol
void mat_get_cols(Matrix *mat, Matrix *col_mat, int *cols_arr) {
    dtype s = mat->type;
    dtype t = col_mat->type;
    assert(s == t);
    int rows = mat->nrow;
    int cols = col_mat->ncol;

    int i, j;
    for (j=0; j<cols; j++) {
        for (i=0; i<rows; i++) {
            tvalue entry = mat_get_entry(mat, i, cols_arr[j]);
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
    dtype t = mat->type;
    int ncol = mat->ncol;
    int rows_arr[1] = {i};
    Matrix *temp_i = mat_create(t, 1, ncol);
    mat_get_rows(mat, temp_i, rows_arr);
    int col;
    for (col=0; col<ncol; col=col+1) {
        tvalue entry_j = mat_get_entry(mat, j, col);
        mat_set_entry(mat, i, col, entry_j);
        tvalue entry_i = mat_get_entry(temp_i, 0, col);
        mat_set_entry(mat, j, col, entry_i);
    }

    mat_delete(temp_i);
    
    return;
}

// (type 2) multiplies row i by a constant k
void mat_row_op2(Matrix *mat, int i, tvalue k) {
    dtype t = mat->type;
    dtype s = k.type;
    assert(t == s);
    int ncol = mat->ncol;
    int j;
    for (j=0; j<ncol; j=j+1) {
        tvalue entry = t_product(k, mat_get_entry(mat, i, j));
        mat_set_entry(mat, i, j, entry);
    }

    return;
}

// (type 3) multiplies row j by constant k and adds it to row i
void mat_row_op3(Matrix *mat, int i, int j, tvalue k) {
    dtype t = mat->type;
    dtype s = k.type;
    assert(t == s);
    int cols = mat->ncol;
    int col;
    for (col=0; col<cols; col=col+1) {
        tvalue entry = t_product(k, mat_get_entry(mat, j, col));
        entry = t_sum(mat_get_entry(mat, i, col), entry);
        mat_set_entry(mat, i, col, entry);
    }

    return;
}

// standard matrix product
void mat_product(Matrix *A, Matrix *B, Matrix *prod) {
    assert(A->type == B->type);
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

            tvalue kron_prod[n];
            int k;
            for (k=0; k<n; k=k+1) {
                kron_prod[k] = t_product(mat_get_entry(A, i, k), mat_get_entry(B, k, j));
            }

            tvalue entry = arr_sum(kron_prod, n);
            mat_set_entry(prod, i, j, entry);
        }
    }

    return;
}

// Hadamard product
void mat_had_product(Matrix *A, Matrix *B, Matrix *prod) {
    assert(A->type == B->type);
    assert(A->nrow == B->nrow);
    assert(A->ncol == B->ncol);
    assert(A->nrow == prod->nrow);
    assert(A->ncol == prod->ncol);

    int nrow = A->nrow;
    int ncol = A->ncol;

    int i, j;
    for (i=0; i<nrow; i++) {
        for (j=0; j<ncol; j++) {
            tvalue entry = t_product(mat_get_entry(A, i, j), mat_get_entry(B, i, j));
            mat_set_entry(prod, i, j, entry);
        }
    }

    return;
}

void mat_scale(tvalue k, Matrix *mat) {
    int nrow = mat->nrow;
    int ncol = mat->ncol;

    int i, j;
    for (i=0; i<nrow; i++) {
        for (j=0; j<ncol; j++) {
            tvalue entry = t_product(k, mat_get_entry(mat, i, j));
            mat_set_entry(mat, i, j, entry);
        }
    }

    return;
}

void mat_sum(Matrix *A, Matrix *B, Matrix *sum) {
    assert(A->nrow == B->nrow);
    assert(A->ncol == B->ncol);
    assert(A->nrow == sum->nrow);
    assert(A->ncol == sum->ncol);
    int m = A->nrow;
    int n = A->ncol;

    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<n; j=j+1) {
            tvalue entry = t_sum(mat_get_entry(A, i, j), mat_get_entry(B, i, j));
            mat_set_entry(sum, i, j, entry);
        }
    }

    return;
}

void mat_transpose(Matrix *mat) {
    int rows = mat->nrow;
    int cols = mat->ncol;

    int i, j;
    for (i=1; i<rows; i++) {
        for (j=0; j<i; j++) {
            tvalue entry_ij = mat_get_entry(mat, i, j);
            tvalue entry_ji = mat_get_entry(mat, j, i);
            mat_set_entry(mat, j, i, entry_ij);
            mat_set_entry(mat, i, j, entry_ji);
        }
    }

    return;
}