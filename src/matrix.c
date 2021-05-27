#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/array.h"
#include "../include/matrix.h"
#include "../include/polynomial.h"

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

void mat_init_int(Matrix *mat) {
    assert(mat->type == INT);
    int n = mat->nrow;
    int p = mat->ncol;
    int i;
    for (i=0; i<n*p; i++) {
        mat->entries[i].type = INT;
        mat->entries[i].val.dblval = 0;
    }

    return;
}

void mat_init_dbl(Matrix *mat) {
    assert(mat->type == DBL);
    int n = mat->nrow;
    int p = mat->ncol;
    int i;
    for (i=0; i<n*p; i++) {
        mat->entries[i].type = DBL;
        mat->entries[i].val.dblval = 0.0;
    }

    return;
}

void mat_init_ply(Matrix *mat, dtype coeff_type) {
    assert(mat->type == PLY);
    int n = mat->nrow;
    int p = mat->ncol;
    int i;
    for (i=0; i<n*p; i++) {
                tvalue tval;
                t_init_ply(coeff_type, &tval);
                Polynomial *p = tval.val.plyval;
                ply_zero(p);
                mat->entries[i] = tval;
    }

    return;
}

void mat_delete(Matrix *mat) {
    assert(mat != NULL);
    dtype t = mat->type;
    int n = mat->nrow;
    int p = mat->ncol;
    int i;
    switch (t) {
        case INT:
            break;
        case DBL:
            break;
        case PLY: {
            for(i=0; i<n*p; i++) {
                Polynomial *p = mat->entries[i].val.plyval;
                if (p != NULL) {
                    ply_delete(p);
                }
            }

            break;
        }
    }
    free(mat->entries);
    free(mat);

    mat = NULL;

    return;
}

void mat_print(Matrix *mat) {
    assert(mat != NULL);
    dtype t = mat->type;
    int rows = mat->nrow;
    int cols = mat->ncol;
    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            tvalue entry = mat_get_entry(mat, i, j);
            t_print(entry, FALSE);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

void mat_set_entry(Matrix *mat, int i, int j, tvalue tval){
    assert(mat != NULL);
    dtype t = mat->type;
    dtype s = tval.type;
    assert(t == s);
    assert((i <= mat->nrow) && (j <= mat->ncol));
    t_copy(tval, &mat->entries[i * mat->ncol + j]);
    
    return;
}

tvalue mat_get_entry(Matrix *mat, int i, int j) {
    assert((i <= mat->nrow) && (j <= mat->ncol));
    tvalue entry = mat->entries[i * mat->ncol + j];

    return entry;
} 

// copy mat1 into mat2
void mat_copy(Matrix *mat1, Matrix *mat2) {
    assert(mat1->type == mat2->type);
    int n = mat1->nrow;
    int p = mat1->ncol;
    assert(n == mat2->nrow);
    assert(p == mat2->ncol);

    int i, j;
    for (i=0; i<n; i++) {
        for (j=0; j<p; j++) {
            tvalue entryij = mat_get_entry(mat1, i, j);
            mat_set_entry(mat2, i, j, entryij);
        }
    }

    return;
}

// fill by row
// make sure length of entries is rows * cols
// entries must be initialized
void mat_fill(Matrix *mat, tvalue *entries) {

    dtype t = mat->type;
    int n = mat->nrow;
    int p = mat->ncol;
    int j;
    for (j=0; j<n*p; j++) {
        assert(entries[j].type == t);
    }

    int i;
    for (i=0; i<n*p; i++) {
        t_copy(entries[i], &mat->entries[i]);
    }

    return;
}

// fill by row
void mat_fill_int(Matrix *mat, int *entries) {
    assert(mat->type == INT);
    int len = mat->nrow * mat->ncol;
    tvalue t_entries[len];
    t_init_ints(t_entries, len);
    t_ints(entries, t_entries, len);

    mat_fill(mat, t_entries);

    return;
}

// mat_fill directly with doubles by row
// make sure len(entries) == nrow * ncol
void mat_fill_dbl(Matrix *mat, double *entries) {
    assert(mat->type == DBL);
    int len = mat->nrow * mat->ncol;
    tvalue t_entries[len];
    t_init_dbls(t_entries, len);
    t_dbls(entries, t_entries, len);

    mat_fill(mat, t_entries);

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

void mat_join(Matrix *A, Matrix *B, int axis, Matrix *join) {
    dtype t = A->type;
    assert(t == B->type);
    assert(t == join->type);

    // axis = 0 means vertical join, i.e. a row join
    // axis = 1 means horizontal join, i.e. a column join
    int m = A->nrow;
    int n = A->ncol;
    int r = B->nrow;
    int s = B->ncol;

    if (axis==0) {
        assert(n == s);
        assert(join->nrow == m+r);
        assert(join->ncol == n);

        int i, j;
        for (j=0; j<n; j++) {
            for (i=0; i<m; i++) {
                tvalue entryA = mat_get_entry(A, i, j);
                mat_set_entry(join, i, j, entryA);
            }

            for (i=0; i<r; i++) {
                tvalue entryB = mat_get_entry(B, i, j);
                mat_set_entry(join, i+m, j, entryB);
            }
        }
    }

    else if (axis == 1) {
        assert(m == r);
        assert(join->nrow == m);
        assert(join->ncol == n+s);

        int i, j;
        for (i=0; i<m; i++) {
            for (j=0; j<n; j++) {
                tvalue entryA = mat_get_entry(A, i, j);
                mat_set_entry(join, i, j, entryA);
            }

            for (j=0; j<s; j++) {
                tvalue entryB = mat_get_entry(B, i, j);
                mat_set_entry(join, i, j+n, entryB);
            }
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
    switch(t) {
        case INT:
            mat_init_int(temp_i);
            break;
        case DBL:
            mat_init_dbl(temp_i);
            break;
        case PLY: {
            // poly entries must be initialized
            dtype coef_type = mat_get_entry(mat, 0, 0).val.plyval->type;
            mat_init_ply(temp_i, coef_type);
            break;
        }
    }
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

    tvalue entry;
    switch(t) {
        case INT:
            t_init_int(&entry);
            break;
        case DBL:
            t_init_dbl(&entry);
            break;
        case PLY: {
            // poly entries must be initialized
            dtype coef_type = mat_get_entry(mat, 0, 0).val.plyval->type;
            t_init_ply(coef_type, &entry);
            break;
        }
    }

    int j;
    for (j=0; j<ncol; j=j+1) {
        tvalue temp_entry = mat_get_entry(mat, i, j);
        t_product(k, temp_entry, &entry);
        mat_set_entry(mat, i, j, entry);
    }

    t_delete(&entry);

    return;
}

// (type 3) multiplies row j by constant k and adds it to row i
void mat_row_op3(Matrix *mat, int i, int j, tvalue k) {
    dtype t = mat->type;
    dtype s = k.type;
    assert(t == s);
    int cols = mat->ncol;
    int col;

    tvalue entry; 
    tvalue temp_entry;
    switch(t) {
        case INT:
            t_init_int(&entry);
            t_init_int(&temp_entry);
            break;
        case DBL:
            t_init_dbl(&entry);
            t_init_dbl(&temp_entry);
            break;
        case PLY: {
            // poly entries must be initialized
            dtype coef_type = mat_get_entry(mat, 0, 0).val.plyval->type;
            t_init_ply(coef_type, &entry);
            t_init_ply(coef_type, &temp_entry);
            break;
        }
    }

    for (col=0; col<cols; col=col+1) {
        t_product(mat_get_entry(mat, j, col), k, &temp_entry);
        t_sum(mat_get_entry(mat, i, col), temp_entry, &entry);
        mat_set_entry(mat, i, col, entry);
    }

    t_delete(&entry);
    t_delete(&temp_entry);

    return;
}

// standard matrix product
void mat_product(Matrix *A, Matrix *B, Matrix *prod) {
    dtype t = A->type;
    assert(t == B->type);
    assert(t == prod->type);
    assert(A->ncol == B->nrow);
    assert(A->nrow == prod->nrow);
    assert(B->ncol == prod->ncol);
    int m, n, p;
    m = A->nrow;
    n = A->ncol;
    p = B->ncol;

    tvalue kron_prod[n];
    tvalue entry;
    switch(t) {
        case INT: {
            t_init_int(&entry);
            int k;
            for (k=0; k<n; k++) {
                 t_init_int(&kron_prod[k]);
            }
            break;
        }
        case DBL: {
            t_init_dbl(&entry);
            int k;
            for (k=0; k<n; k++) {
                 t_init_dbl(&kron_prod[k]);
            }
            break;
        }
        case PLY: {
            // poly entries must be initialized
            dtype coef_type = mat_get_entry(A, 0, 0).val.plyval->type;
            t_init_ply(coef_type, &entry);
            int k;
            for (k=0; k<n; k++) {
                 t_init_ply(coef_type, &kron_prod[k]);
            }
            break;
        }
    }


    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<p; j=j+1) {
            int k;
            for (k=0; k<n; k++) {
                tvalue aik = mat_get_entry(A, i, k);
                tvalue bkj = mat_get_entry(B, k, j);
                t_product(aik, bkj, &kron_prod[k]);
            }
            
            arr_sum(kron_prod, n, &entry);
            mat_set_entry(prod, i, j, entry);
        }
    }

    t_delete(&entry);
    int k;
    for (k=0; k<n; k++) {
        t_delete(&kron_prod[k]);
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
            tvalue aij = mat_get_entry(A, i, j);
            tvalue bij = mat_get_entry(B, i, j);
            tvalue entry;
            t_product(aij, bij, &entry);
            mat_set_entry(prod, i, j, entry);
        }
    }

    return;
}

void mat_scale(tvalue k, Matrix *mat) {
    assert(k.type == mat->type);
    int nrow = mat->nrow;
    int ncol = mat->ncol;

    int i, j;
    for (i=0; i<nrow; i++) {
        for (j=0; j<ncol; j++) {
            tvalue entry = mat_get_entry(mat, i, j); 
            t_product(k, entry, &entry);
            mat_set_entry(mat, i, j, entry);
        }
    }

    return;
}

void mat_sum(Matrix *A, Matrix *B, Matrix *sum) {
    dtype t = A->type;
    assert(t == B->type);
    assert(A->nrow == B->nrow);
    assert(A->ncol == B->ncol);
    assert(A->nrow == sum->nrow);
    assert(A->ncol == sum->ncol);
    int m = A->nrow;
    int n = A->ncol;

    tvalue entry;
    switch(t) {
        case INT: 
            t_init_int(&entry);
            break;
        case DBL: 
            t_init_dbl(&entry);
            break;
        case PLY: {
            // poly entries must be initialized
            dtype coef_type = mat_get_entry(A, 0, 0).val.plyval->type;
            t_init_ply(coef_type, &entry);
        }
    }

    int i,j;
    for (i=0; i<m; i=i+1) {
        for (j=0; j<n; j=j+1) {
            tvalue aij = mat_get_entry(A, i, j);
            tvalue bij = mat_get_entry(B, i, j);
            t_sum(aij, bij, &entry);
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
//--------------------------------------------------------

// algorithms

// row echelon form
static void sub_ref(Matrix *mat, int start_row, int start_col) {
    dtype t = mat->type;

    // check if mat is zero matrix
    int nrow = mat->nrow;
    int ncol = mat->ncol;
    int val = TRUE;
    tvalue entry;
    int row = start_row;
    int col = start_col;
    while (col < ncol) {
        row = start_row;
        while (row < nrow) {
            entry = mat_get_entry(mat, row, col);
            if (t_is_zero(entry) == FALSE) {
                val = FALSE;
                break;
            }
            row = row+1;
        }
        if (val == FALSE)
            break;
        col = col + 1;
    }
    if (val == TRUE)
        return;

    // (row, col) is now pivot;
    // row operations to create a pivot of 1 and zeros below pivot
    tvalue inv; 
    switch(t) {
        case DBL: 
            t_init_dbl(&inv);
            break;
        case MOD: {
        }
    }
    t_inverse(entry, &inv);
    mat_row_op2(mat, row, inv);

    if (start_row != row) {
        mat_row_op1(mat, start_row, row);
    }

    row = row + 1;
    while (row < nrow) {
        tvalue k; 
        switch(t) {
            case DBL: 
                t_init_dbl(&k);
                break;
            case MOD: {
        }
    }
        t_negative(mat_get_entry(mat, row, col), &k);
        if (t_is_zero(k) == FALSE) {
            mat_row_op3(mat, row, start_row, k);
        }
        row = row + 1;
    }
    // recursive call on submatrix down-right from pivot
    sub_ref(mat, start_row+1, col+1);
}

void mat_ref(Matrix *mat) {
    sub_ref(mat, 0, 0);
}

// reduced row echelon form
static void sub_rref(Matrix *mat, int start_row, int start_col) {
    // assume matrix is in row echelon form
    // check if mat is zero matrix
    dtype t = mat->type;
    int m = mat->nrow;
    int n = mat->ncol;
    int val = TRUE;
    tvalue entry;
    int row = start_row;
    int col = start_col;
    while (col < n) {
        row = start_row;
        while (row < m) {
            entry = mat_get_entry(mat, row, col);
            if (t_is_zero(entry) == FALSE) {
                val = FALSE;
                break;
            } 
            row = row + 1;
        }
        if (val == FALSE)
            break;
        col = col + 1;
    }
    if (val == TRUE)
        return;

    // now (row, col) is the pivot
    int prev_row = row-1;
    while (0 <= prev_row) {
        t_negative(mat_get_entry(mat, prev_row, col), &entry);
        if (t_is_zero(entry) == FALSE)
            mat_row_op3(mat, prev_row, row, entry);
        prev_row = prev_row - 1;
    }

    row = row + 1;
    col = col + 1;
    sub_rref(mat, row, col);
}

void mat_rref(Matrix *mat) {
    mat_ref(mat);
    sub_rref(mat, 0, 0);
}

// solve system Ax=b
// A is square
void mat_solve(Matrix *A, Matrix *b, Matrix *xsol) {
    dtype t = A->type;
    assert(t == b->type);
    assert(t == xsol->type);
    int m = A->nrow;
    assert(m == A->ncol);
    assert(m == b->nrow);
    assert(b->ncol = 1);
    assert(xsol->nrow == m);
    assert(xsol->ncol == 1);

    Matrix *join = mat_create(t, m, m+1);
    switch(t) {
        case DBL: 
            mat_init_dbl(join);
            break;
        case MOD: {
            break;
        }
    }
    mat_join(A, b, 1, join);
    mat_rref(join);
    int cols_arr[1] = {m};
    mat_get_cols(join, xsol, cols_arr);
    
    mat_delete(join);

    return;
}

//-------------------------------------------------------------------