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

union values {
    double *dblvals;
};

struct tvalue {
    dtype type;
    value val;
};

struct tvalues {
    dtype type;
    values vals;
};

tvalue tdbl(double val);
tvalues tdbls(double *vals);

#endif