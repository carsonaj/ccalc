#ifndef TYPE_H
#define TYPE_H

// defined types

enum dtype;
union value;
struct tvalue;

typedef enum dtype dtype; 
typedef union value value;
typedef struct tvalue tvalue;

struct Modulo;
struct Matrix;
struct Polynomial;

typedef struct Modulo Modulo;
typedef struct Matrix Matrix;
typedef struct Polynomial Polynomial;

enum dtype {
    // double
    DBL,
    // integer modulo p
    MOD,
    // polynomial
    PLY,
    // matrix
    MAT,
    // finite field element
    FFE,
    // number field element
    NFE
};

union value {
    double dblval;
    Modulo *modval;
    Polynomial *plyval;
    Matrix *matval;
};

struct tvalue {
    dtype type;
    value val;
};

// integer modulo p
struct Modulo{
    dtype type;
    int modulus;
    int residue;
};

// matrix:
struct Matrix {
    dtype type;
    int nrow;
    int ncol;
    tvalue *entries;
};

// polynomial
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

void t_init_dbl(tvalue *tval);
void t_dbl(double val, tvalue *tval);
void t_init_dbls(tvalue *tvals, int len);
void t_dbls(double *vals, tvalue *tvals, int len);
void t_init_ply(dtype coeff_type, tvalue *tval);
void t_ply(Polynomial *val, tvalue *tval);
void t_init_zp(int p, tvalue *tval);

void t_delete(tvalue *tval);
void t_copy(tvalue tval1, tvalue *tval2);

// mathematics:
int t_equal(tvalue tval1, tvalue tval2);
int t_is_zero(tvalue tval);
void t_zero(tvalue *z);
void t_identity(tvalue *e);
void t_neg(tvalue x, tvalue *neg);
void t_inv(tvalue x, tvalue *inv);
void t_sum(tvalue tval1, tvalue tval2, tvalue *sum);
void t_product(tvalue tval1, tvalue tval2, tvalue *prod);

#endif