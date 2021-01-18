#include <assert.h>
#include "../include/type.h"

#define TRUE 1
#define FALSE 0

tvalue t_dbl(double val) {
    tvalue tval;
    tval.type = DBL;
    tval.val.dblval = val;

    return tval;
}

// copy doubles into tvalues
void t_dbls(double *vals, tvalue *tvals, int len) {
    int i;
    for (i=0; i<len; i++) {
        tvals[i].type = DBL;
        tvals[i].val.dblval = vals[i];
    }

    return;
}

tvalue t_zero(dtype type) {
    tvalue z;
    z.type = type;
    switch(type) {
        case DBL: 
            z.val.dblval = 0.0;
            break;
        case PLY:
            break;
    }

    return z;

}

int t_equal(tvalue tval1, tvalue tval2) {
    dtype t = tval1.type; 
    if (t != tval2.type) {
        return FALSE;
    }

    switch(t) {
        case DBL: 
            if (tval1.val.dblval == tval2.val.dblval) {
                return TRUE;
            }
            break;
        case PLY:
            break;
    }
}

tvalue t_sum(tvalue tval1, tvalue tval2) {
    dtype t = tval1.type;
    dtype s = tval2.type;
    assert(s == t);

    tvalue sum;
    sum.type = t;
    switch(t) {
        case DBL:
            sum.val.dblval = tval1.val.dblval + tval2.val.dblval;
            break;
        case PLY:
            break; 
    }

    return sum;
}

tvalue t_product(tvalue tval1, tvalue tval2) {
    dtype t = tval1.type;
    dtype s = tval2.type;
    assert(s == t);

    tvalue prod;
    prod.type = t;
    switch(t) {
        case DBL:
            prod.val.dblval = tval1.val.dblval * tval2.val.dblval;
            break;
        case PLY:
            break; 
    }

    return prod;
}