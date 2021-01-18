#include <stdio.h>
#include <assert.h>
#include "../include/type.h"

#define TRUE 1
#define FALSE 0

void t_print(tvalue tval) {
    dtype t = tval.type;
    
    switch(t) {
        case DBL:
            printf("%6.2f ", tval.val.dblval);
            break;
        case PLY:
            break;
    }

    return;
}

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

tvalue t_zero(dtype t) {
    tvalue z;
    z.type = t;
    switch(t) {
        case DBL: 
            z.val.dblval = 0.0;
            break;
        case PLY:
            break;
    }

    return z;
}

tvalue t_neg(tvalue x) {
    dtype t = x.type;
    tvalue neg;
    neg.type = t;
    switch(t) {
        case DBL: 
            neg.val.dblval = -x.val.dblval;
            break;
        case PLY:
            break;
    }

    return neg;
}

tvalue t_inv(tvalue x) {
    dtype t = x.type;
    assert(t_equal(x, t_zero(t)) == FALSE);
    tvalue inv;
    inv.type = t;
    switch(t) {
        case DBL:
            inv.val.dblval = 1/x.val.dblval;
            break;
        case PLY:
            break;
    }

    return inv;
}

int t_equal(tvalue tval1, tvalue tval2) {
    dtype t = tval1.type; 
    if (t != tval2.type) {
        return FALSE;
    }

    switch(t) {
        case DBL: {
            int s1 = ((tval1.val.dblval - tval2.val.dblval) < 0.0001);
            int s2 = (-0.0001 < (tval1.val.dblval - tval2.val.dblval));
            if ((s1 && s2) == TRUE) {
                return TRUE;
            }
            break;
        }
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