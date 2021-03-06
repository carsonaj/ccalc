#ifndef TYPE_H
#define TYPE_H

// defined types

enum dtype;
union value;
struct tvalue;

typedef enum dtype dtype; 
typedef union value value;
typedef struct tvalue tvalue;

struct ModularInt;
struct Matrix;
struct Polynomial;

typedef struct ModularInt ModularInt;
typedef struct Matrix Matrix;
typedef struct Polynomial Polynomial;

enum dtype {
    // int
    INT,

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
    int intval;
    double dblval;
    ModularInt *modval;
    Polynomial *plyval;
    Matrix *matval;
};

struct tvalue {
    dtype type;
    value val;
};

// integer modulo p
struct ModularInt {
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

void t_init_int(tvalue *tval);
void t_int(int val, tvalue *tval);
void t_init_ints(tvalue *tvals, int len);
void t_ints(int *vals, tvalue *tvals, int len);
void t_init_dbl(tvalue *tval);
void t_dbl(double val, tvalue *tval);
void t_init_dbls(tvalue *tvals, int len);
void t_dbls(double *vals, tvalue *tvals, int len);
void t_init_mod(tvalue *tval);
void t_mod(ModularInt *val, tvalue *tval);
void t_init_mods(tvalue *tvals, int len);
void t_mods(int *vals, int modulus, tvalue *tvals, int len);
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
void t_negative(tvalue x, tvalue *neg);
void t_inverse(tvalue x, tvalue *inv);
void t_sum(tvalue tval1, tvalue tval2, tvalue *sum);
void t_product(tvalue tval1, tvalue tval2, tvalue *prod);

#endif