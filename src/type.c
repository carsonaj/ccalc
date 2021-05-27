#include <stdio.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/matrix.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

// tvalues must be initialized outside of t_init functions

void t_print(tvalue tval, int newline) {
    dtype t = tval.type;
    
    switch (t) {
        case INT:
            printf("%6.2d", tval.val.intval);
            break;
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

void t_init_int(tvalue *tval) {
    tval->type = INT;
    tval->val.intval = 0;

    return;
}

void t_int(int val, tvalue *tval) {
    assert(tval->type == INT);
    tval->val.intval = val;

    return;
}

void t_init_ints(tvalue *tvals, int len) {
    int i;
    for (i=0; i<len; i++) {
        t_init_int(&tvals[i]);
    }

    return;
}

void t_ints(int *vals, tvalue *tvals, int len) {
    int i;
    for (i=0; i<len; i++) {
        assert(tvals[i].type == INT);
    }
    for (i=0; i<len; i++) {
        tvals[i].val.intval = vals[i];
    }

    return;
}

void t_init_dbl(tvalue *tval) {
    tval->type = DBL;
    tval->val.dblval = 0;

    return;
}

void t_dbl(double val, tvalue *tval) {
    assert(tval->type == DBL);
    tval->val.dblval = val;

    return;
}

void t_init_dbls(tvalue *tvals, int len) {
    int i;
    for (i=0; i<len; i++) {
        t_init_dbl(&tvals[i]);
    }

    return;
}

// copy doubles into tvalues
// tvalues must be initialized
void t_dbls(double *vals, tvalue *tvals, int len) {
    int i;
    for (i=0; i<len; i++) {
        assert(tvals[i].type == DBL);
    }
    for (i=0; i<len; i++) {
        tvals[i].val.dblval = vals[i];
    }

    return;
}

void t_init_ply(dtype coeff_type, tvalue *tval) {
    tval->type = PLY;
    Polynomial *p = ply_create(coeff_type, 0);
    tval->val.plyval = p;

    return;
}

// make sure tval has initialized val.plyval
void t_ply(Polynomial *val, tvalue *tval) {
    assert(tval->type = PLY);
    ply_copy(val, tval->val.plyval);

    return;
}

// make sure tval has initialized val.plyval
void t_delete(tvalue *tval) {
    dtype t = tval->type;
    switch(t) {
        case INT:
            break;
        case DBL:
            break;
        case PLY:
            ply_delete(tval->val.plyval);
    }

    return;
}

// copy tval1 into tval2
// for non-DBL dtypes, value must be initialized
// ex) tval2->val.ply_val must already be initialized, use t_init_ply
void t_copy(tvalue tval1, tvalue *tval2) {
    dtype t = tval1.type;
    assert(t == tval2->type);
    switch(t) {
        case INT:
            tval2->val.intval = tval1.val.intval;
            break;
        case DBL:
            tval2->val.dblval = tval1.val.dblval;
            break;
        case PLY: 
            ply_copy(tval1.val.plyval, tval2->val.plyval);
            break;
    }

    return;
}

int t_equal(tvalue tval1, tvalue tval2) {
    dtype t = tval1.type; 
    if (t != tval2.type) {
        return FALSE;
    }

    switch (t) {
        case INT:
            if (tval1.val.intval == tval2.val.intval)
                return TRUE;
            else 
                return FALSE;
        case DBL: {
            int s1 = ((tval1.val.dblval - tval2.val.dblval) < 0.0001);
            int s2 = (-0.0001 < (tval1.val.dblval - tval2.val.dblval));
            if ((s1 && s2) == TRUE) 
                return TRUE;
            else 
                return FALSE;
        }
        case PLY: {
            int res = ply_equal(tval1.val.plyval, tval2.val.plyval);
            return res;
        }
            
    }
}

// tval must be initialized
int t_is_zero(tvalue tval) {
    dtype t = tval.type;

    switch (t) {
        case INT:
            if (tval.val.intval == 0)
                return TRUE;
            else
                return FALSE;
        case DBL: {
            int s1 = (tval.val.dblval < 0.0001);
            int s2 = (-0.0001 < tval.val.dblval);
            if ((s1 && s2) == TRUE) 
                return TRUE;
            else 
                return FALSE;
            break;
        }
        case PLY: {
            int res = ply_is_zero(tval.val.plyval);
            return res;
        }    
    }
}

// z must be initialized
void t_zero(tvalue *z) {
    dtype t = z->type;
    switch (t) {
        case INT:
            z->val.intval = 0;
            break;
        case DBL: 
            z->val.dblval = 0.0;
            break;
        case PLY:
            ply_zero(z->val.plyval);
            break;
    }

    return;
}

// e must be initialized
void t_identity(tvalue *e) {
    dtype t = e->type;
    switch (t) {
        case INT:
            e->val.intval = 1;
            break;
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
        case INT:
            neg->val.intval = -x.val.intval;
            break;
        case DBL: 
            neg->val.dblval = -x.val.dblval;
            break;
        case PLY:
            ply_neg(x.val.plyval, neg->val.plyval);
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

// if type is not double, values must be initialized
void t_sum(tvalue tval1, tvalue tval2, tvalue *sum) {
    dtype t = tval1.type;
    assert(t == tval2.type);
    assert(t == sum->type);

    switch (t) {
        case INT:
            sum->val.intval = tval1.val.intval + tval2.val.intval;
            break;
        case DBL:
            sum->val.dblval = tval1.val.dblval + tval2.val.dblval;
            break;
        case PLY:
            ply_sum(tval1.val.plyval, tval2.val.plyval, sum->val.plyval);
            break; 
    }

    return;
}

// if type is not double, values must be initialized
void t_product(tvalue tval1, tvalue tval2, tvalue *prod) {
    dtype t = tval1.type;
    dtype s = tval2.type;
    assert(s == t);

    prod->type = t;
    switch (t) {
        case INT:
            prod->val.intval = tval1.val.intval * tval2.val.intval;
            break;
        case DBL:
            prod->val.dblval = tval1.val.dblval * tval2.val.dblval;
            break;
        case PLY:
            ply_product(tval1.val.plyval, tval2.val.plyval, prod->val.plyval);
            break; 
    }

    return;
}