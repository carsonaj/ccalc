#ifndef MATRIX_H
#define MATRIX_H
#include "type.h"

#define MAX_SIZE 50

typedef struct Matrix Matrix;

struct Matrix {
    dtype type;
    int nrow;
    int ncol;
    tvalues data;
};

Matrix *mat_create(dtype t, int n, int p);
void mat_delete(Matrix *mat);
void mat_fill(Matrix *mat, tvalues entries);
void mat_set_entry(Matrix *mat, int i, int j, tvalue tval);
tvalue mat_get_entry(Matrix *mat, int i, int j);
void mat_print(Matrix *mat);
int mat_equal(Matrix *mat1, Matrix *mat2);
void mat_get_rows(Matrix *mat, Matrix *row_mat, int *rows_arr);
void mat_get_cols(Matrix *mat, Matrix *col_mat, int *cols_arr);
void mat_row_op1(Matrix *mat, int i, int j);
void mat_row_op2(Matrix *mat, int i, double k);
void mat_row_op3(Matrix *mat, int i, int j, double k);
void mat_product(Matrix *A, Matrix *B, Matrix *prod);
void mat_had_product(Matrix *A, Matrix *B, Matrix *prod);
void mat_scale(double k, Matrix *mat);
void mat_sum(Matrix *A, Matrix *B, Matrix *sum);
void mat_transpose(Matrix *mat);

#endif