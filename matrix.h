#ifndef MATRIX_H
#define MATRIX_H

#define MAX_SIZE 50

typedef struct Matrix Matrix;

struct Matrix {
    int rows;
    int cols;
    double *data;
};

Matrix *mat_create(int n, int p);
void mat_delete(Matrix *mat);
void mat_fill(Matrix *mat, double *entries, int len);
void mat_set_entry(Matrix *mat, int i, int j, double val);
double mat_get_entry(Matrix *mat, int i, int j);
void mat_print(Matrix *mat);
int mat_equal(Matrix *mat1, Matrix *mat2);


#endif