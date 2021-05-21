#ifndef TYPE_H
#define TYPE_H

// defined types

enum dtype;
union value;
struct tvalue;
struct Matrix;
struct Polynomial;

typedef enum dtype dtype; 
typedef union value value;
typedef struct tvalue tvalue;
typedef struct Matrix Matrix;
typedef struct Polynomial Polynomial;

enum dtype {
    // double
    DBL,
    // polynomial
    PLY,
    // matrix
    MAT,
    // algebraic number
    ALN
};

union value {
    double dblval;
    Polynomial *plyval;
    Matrix *matval;
};

struct tvalue {
    dtype type;
    value val;
};

// matrix:
struct Matrix {
    dtype type;
    int nrow;
    int ncol;
    tvalue *entries;
};

struct Polynomial {
    dtype type; 
    int deg;
    tvalue *coefs;
};
//==========================================================================================
//==========================================================================================
//==========================================================================================

// data structure:
void t_print(tvalue tval, int newline);
void t_dbl(double val, tvalue *tval);
void t_dbls(double *vals, tvalue *tvals, int len);
void t_copy(tvalue tval1, tvalue *tval2);

// mathematics:
int t_equal(tvalue tval1, tvalue tval2);
int t_is_zero(tvalue tval);
void t_zero(dtype t, tvalue *z);
void t_identity(dtype t, tvalue *e);
void t_neg(tvalue x, tvalue *neg);
void t_inv(tvalue x, tvalue *inv);
void t_sum(tvalue tval1, tvalue tval2, tvalue *sum);
void t_product(tvalue tval1, tvalue tval2, tvalue *prod);

#endif