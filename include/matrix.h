#ifndef MATRIX_H
#define MATRIX_H
#include "type.h"

#define MAX_SIZE 50

// data structure:
Matrix *mat_create(dtype t, int n, int p);
void mat_init_dbl(Matrix *mat);
void mat_init_ply(Matrix *mat, dtype coeff_type);
void mat_delete(Matrix *mat);
void mat_fill(Matrix *mat, tvalue *entries);
void mat_fill_dbl(Matrix *mat, double *entries);
void mat_set_entry(Matrix *mat, int i, int j, tvalue tval);
tvalue mat_get_entry(Matrix *mat, int i, int j);
void mat_copy(Matrix *mat1, Matrix *mat2);
void mat_print(Matrix *mat);
int mat_equal(Matrix *mat1, Matrix *mat2);
void mat_get_rows(Matrix *mat, Matrix *row_mat, int *rows_arr);
void mat_get_cols(Matrix *mat, Matrix *col_mat, int *cols_arr);
void mat_join(Matrix *A, Matrix *B, int axis, Matrix *join);

// mathematics:
void mat_row_op1(Matrix *mat, int i, int j);
void mat_row_op2(Matrix *mat, int i, tvalue k);
void mat_row_op3(Matrix *mat, int i, int j, tvalue k);
void mat_product(Matrix *A, Matrix *B, Matrix *prod);
void mat_had_product(Matrix *A, Matrix *B, Matrix *prod);
void mat_scale(tvalue k, Matrix *mat);
void mat_sum(Matrix *A, Matrix *B, Matrix *sum);
void mat_transpose(Matrix *mat);

// algorithms:
void mat_ref(Matrix *mat);
void mat_rref(Matrix *mat);
void mat_solve(Matrix *A, Matrix *b, Matrix *xsol);

#endif