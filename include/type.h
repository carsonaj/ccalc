#ifndef TYPE_H
#define TYPE_H

typedef enum dtype dtype; 
typedef union value value;
typedef union values values;
typedef struct tvalue tvalue;
typedef struct tvalues tvalues;

enum dtype {
    DBL,
    PLY,
    ALN
};

union value {
    double dblval;
};

struct tvalue {
    dtype type;
    value val;
};

// data structure:
tvalue t_dbl(double val);
void t_dbls(double *vals, tvalue *tvals, int len);

// mathematics:
tvalue zero(dtype type);
int t_equal(tvalue tval1, tvalue tval2);
tvalue t_sum(tvalue tval1, tvalue tval2);
tvalue t_product(tvalue tval1, tvalue tval2);

#endif