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
void t_print(tvalue tval);
tvalue t_dbl(double val);
void t_dbls(double *vals, tvalue *tvals, int len);

// mathematics:
tvalue t_zero(dtype type);
tvalue t_neg(tvalue x);
tvalue t_inv(tvalue x);
int t_equal(tvalue tval1, tvalue tval2);
int t_is_zero(tvalue tval);
tvalue t_sum(tvalue tval1, tvalue tval2);
tvalue t_product(tvalue tval1, tvalue tval2);

#endif