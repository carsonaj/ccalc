#include <stdio.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/matrix.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

void t_print(tvalue tval, int newline) {
    dtype t = tval.type;
    
    switch (t) {
        case DBL:
            printf("%6.2f", tval.val.dblval);
            break;
        case PLY:
            ply_print(tval.val.plyval, FALSE);
            break;
    }

    if (newline == TRUE) {
        printf("\n");
    }

    return;
}

void t_dbl(double val, tvalue *tval) {
    tval->type = DBL;
    tval->val.dblval = val;

    return;
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

// copy tval1 into tval2
void t_copy(tvalue tval1, tvalue *tval2) {
    tval2->type = tval1.type;
    tval2->val = tval1.val;

    return;

}

int t_equal(tvalue tval1, tvalue tval2) {
    dtype t = tval1.type; 
    if (t != tval2.type) {
        return FALSE;
    }

    switch (t) {
        case DBL: {
            int s1 = ((tval1.val.dblval - tval2.val.dblval) < 0.0001);
            int s2 = (-0.0001 < (tval1.val.dblval - tval2.val.dblval));
            if ((s1 && s2) == TRUE) 
                return TRUE;
            else 
                return FALSE;
            break;
        }
        case PLY:
            break;
    }
}

int t_is_zero(tvalue tval) {
    dtype t = tval.type;

    switch (t) {
        case DBL: {
            int s1 = (tval.val.dblval < 0.0001);
            int s2 = (-0.0001 < tval.val.dblval);
            if ((s1 && s2) == TRUE) 
                return TRUE;
            else 
                return FALSE;
            break;
        }
        //case PLY:
        //    if (ply_is_zero(tval.val.plyval) == TRUE)
        //        return TRUE;
        //    else 
        //        return FALSE;
        //    break;
    }
}

void t_zero(dtype t, tvalue *z) {
    z->type = t;
    switch (t) {
        case DBL: 
            z->val.dblval = 0.0;
            break;
        case PLY:
            break;
    }

    return;
}

void t_identity(dtype t, tvalue *e) {
    e->type = t;
    switch (t) {
        case DBL: 
            e->val.dblval = 1.0;
            break;
        case PLY:
            break;
    }

    return;
}

void t_neg(tvalue x, tvalue *neg) {
    dtype t = x.type;
    neg->type = t;
    switch (t) {
        case DBL: 
            neg->val.dblval = -x.val.dblval;
            break;
        case PLY:
            break;
    }

    return;
}

void t_inv(tvalue x, tvalue *inv) {
    assert(t_is_zero(x) == FALSE);
    dtype t = x.type;
    inv->type = t;
    switch (t) {
        case DBL:
            inv->val.dblval = 1 / x.val.dblval;
            break;
        case PLY:
            break;
    }

    return;
}

void t_sum(tvalue tval1, tvalue tval2, tvalue *sum) {
    dtype t = tval1.type;
    dtype s = tval2.type;
    assert(s == t);

    sum->type = t;
    switch (t) {
        case DBL:
            sum->val.dblval = tval1.val.dblval + tval2.val.dblval;
            break;
        case PLY:
            break; 
    }

    return;
}

void t_product(tvalue tval1, tvalue tval2, tvalue *prod) {
    dtype t = tval1.type;
    dtype s = tval2.type;
    assert(s == t);

    prod->type = t;
    switch (t) {
        case DBL:
            prod->val.dblval = tval1.val.dblval * tval2.val.dblval;
            break;
        case PLY:
            break; 
    }

    return;
}