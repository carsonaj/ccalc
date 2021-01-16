#ifndef MATRIX_H
#define MATRIX_H

#define MAX_SIZE 50

typedef struct DoubleMatrix DoubleMatrix;

struct DoubleMatrix {
    int nrow;
    int ncol;
    double *data;
};

DoubleMatrix *dblmat_create(int n, int p);
void dblmat_delete(DoubleMatrix *mat);
void dblmat_fill(DoubleMatrix *mat, double *entries);
void dblmat_set_entry(DoubleMatrix *mat, int i, int j, double val);
double dblmat_get_entry(DoubleMatrix *mat, int i, int j);
void dblmat_print(DoubleMatrix *mat);
int dblmat_equal(DoubleMatrix *mat1, DoubleMatrix *mat2);
void dblmat_get_rows(DoubleMatrix *mat, DoubleMatrix *row_mat, int *rows_arr);
void dblmat_get_cols(DoubleMatrix *mat, DoubleMatrix *col_mat, int *cols_arr);
void dblmat_row_op1(DoubleMatrix *mat, int i, int j);
void dblmat_row_op2(DoubleMatrix *mat, int i, double k);
void dblmat_row_op3(DoubleMatrix *mat, int i, int j, double k);
void dblmat_product(DoubleMatrix *A, DoubleMatrix *B, DoubleMatrix *prod);
void dblmat_had_product(DoubleMatrix *A, DoubleMatrix *B, DoubleMatrix *prod);
void dblmat_scale(double k, DoubleMatrix *mat);
void dblmat_sum(DoubleMatrix *A, DoubleMatrix *B, DoubleMatrix *sum);
void dblmat_transpose(DoubleMatrix *mat);

#endif