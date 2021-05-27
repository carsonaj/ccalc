#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/array.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0

// helpful functions
static Polynomial *max_deg(Polynomial *p1, Polynomial *p2) {
    int deg1 = p1->deg;
    int deg2 = p2->deg;
    if (deg1>deg2)
        return p1;
    else if (deg2>deg1)
        return p2;
    else {
        if (ply_is_zero(p1))
            return p2;
        else
            return p1;
    }
}

static Polynomial *min_deg(Polynomial *p1, Polynomial *p2) {
    int deg1 = p1->deg;
    int deg2 = p2->deg;
    if (deg1>deg2)
        return p2;
    else if (deg2>deg1)
        return p1;
    else {
        if (ply_is_zero(p1))
            return p1;
        else
            return p2;
    }
}

// data structure
Polynomial *ply_create(dtype t, int deg) {
    assert(deg >= 0 && deg <= MAX_DEG);
    Polynomial *poly = malloc(sizeof(Polynomial));
    assert(poly != NULL);
    poly->type = t;
    poly->deg = deg;
    poly->coefs = malloc((MAX_DEG + 1) * sizeof(tvalue));

    int i;
    for(i=0; i<=MAX_DEG; i++) {
        poly->coefs[i].type = t;
    }
    
    return poly;
}

void ply_delete(Polynomial *poly) {
    assert(poly != NULL);
    dtype t = poly->type;
    switch (t) {
        case DBL:
            break;
        case FFE: // must free each value as well
            break;
    }

    free(poly->coefs);
    free(poly);

    poly = NULL;

    return;
}

// make sure entries has length deg + 1
void ply_fill(Polynomial *poly, tvalue *coefs) {
    dtype t = poly->type;
    int deg = poly->deg;
    if (deg > 0)
        assert(t_is_zero(coefs[deg]) == FALSE);
    
    int i;
    for (i = 0; i <= deg; i++) {
        dtype s = coefs[i].type;
        assert(t == s);
        t_copy(coefs[i], &poly->coefs[i]);
    }

    return;
}

// make sure coefs has length deg + 1
void ply_fill_dbl(Polynomial *poly, double *coefs) {
    assert(poly->type == DBL);
    int deg = poly->deg;
    tvalue t_coefs[deg + 1];
    t_init_dbls(t_coefs, deg+1);
    t_dbls(coefs, t_coefs, deg+1);

    if (poly->deg > 0) {
        assert(t_is_zero(t_coefs[deg]) == FALSE);
    }
    
    ply_fill(poly, t_coefs);

    int i;
    for (i=0; i<=deg; i++) {
        t_delete(&t_coefs[i]);
    }

    return;
}

tvalue ply_get_coef(Polynomial *poly, int i) {
    return poly->coefs[i];
}

void ply_set_coef(Polynomial *poly, int i, tvalue tval) {
    t_copy(tval, &poly->coefs[i]);

    return;
}

// copy coefs of poly p into poly q
void ply_copy(Polynomial *p, Polynomial *q) {
    dtype t = p->type;
    assert(t == q->type);
    int d = p->deg;

    //for(i=q->deg+1; i<d; i++) {
    //    q->coefs[i].type = t;
    //    switch(t) {
    //        case DBL:   
    //            q->coefs[i].val.dblval = 0;
    //            break;
    //        case MOD:
    //            break;
    //    }
    //}
    q->deg = d;
    int i;
    for (i=0; i <= d; i++) {
        tvalue coef = ply_get_coef(p, i);
        ply_set_coef(q, i, coef);
    }

    return;
}

// newline either TRUE or FALSE, i.e. 1 or 0
void ply_print(Polynomial *poly, int newline) {
    dtype t = poly->type;
    switch (t) {
        case DBL:
            ply_print_dbl(poly, newline);
            break;
    }
}

// newline either TRUE or FALSE, i.e. 1 or 0
void ply_print_dbl(Polynomial *poly, int newline) {
    assert(poly->type == DBL);
    int deg = poly->deg;
    tvalue coef0 = ply_get_coef(poly, 0);
    tvalue coefn = ply_get_coef(poly, deg); 
    
    switch (newline) {
        case TRUE: {
            if (deg!=0) {
                assert(coefn.val.dblval !=0);
                int k;
                int i;
                tvalue coef;
                for (i=0; i<=deg; i++) {
                    coef = ply_get_coef(poly, i);
                    if (coef.val.dblval != 0) {
                        k = i;
                        break;
                    }
                }
                if (k<deg) {
                    printf("%.2fx^%d ", coef.val.dblval, k);
                    for (i=k+1; i<=deg-1; i++) {
                        coef = ply_get_coef(poly, i);
                        if (coef.val.dblval > 0) {
                            printf("+ %.2fx^%d ", coef.val.dblval, i);
                        }
                        else if (coef.val.dblval < 0)
                            printf("- %.2fx^%d ", -coef.val.dblval, i);
                        }
                    if (coefn.val.dblval > 0)
                        printf("+ %.2fx^%d\n", coefn.val.dblval, deg);
                    else
                        printf("- %.2fx^%d\n", -coefn.val.dblval, deg);
                }

                else if (k==deg) {
                    printf("%.3fx^%d\n", coefn.val.dblval, deg);
                }
            }   

            else if (deg == 0) {
                printf("%.2f\n", coef0.val.dblval);
            }

            break;
        }

        case FALSE: {
            if (deg!=0) {
                assert(coefn.val.dblval !=0);
                int k;
                int i;
                tvalue coef;
                for (i=0; i<=deg; i++) {
                    coef = ply_get_coef(poly, i);
                    if (coef.val.dblval != 0) {
                        k = i;
                        break;
                    }
                }
                if (k<deg) {
                    printf("%.2fx^%d ", coef.val.dblval, k);
                    for (i=k+1; i<=deg-1; i++) {
                        coef = ply_get_coef(poly, i);
                        if (coef.val.dblval > 0) {
                            printf("+ %.2fx^%d ", coef.val.dblval, i);
                        }
                        else if (coef.val.dblval < 0)
                            printf("- %.2fx^%d ", -coef.val.dblval, i);
                        }
                    if (coefn.val.dblval > 0)
                        printf("+ %.2fx^%d", coefn.val.dblval, deg);
                    else
                        printf("- %.2fx^%d", -coefn.val.dblval, deg);
                }

                else if (k==deg) {
                    printf("%.3fx^%d", coefn.val.dblval, deg);
                }
            }   

            else if (deg == 0) {
                printf("%.2f", coef0.val.dblval);
            }

            break;
        }
            
    }
    
}
//----------------------------------------------------------------------------


//mathematics

// algebra

int ply_equal(Polynomial *p, Polynomial *q) {
    if (p->type != q->type) 
        return FALSE;
    else {
        int m = p->deg;
        int n = q->deg;

        if (m != n)
            return FALSE;
        else {
            int i;
            for (i=0; i<=m; i++){
                tvalue co_p = ply_get_coef(p, i);
                tvalue co_q = ply_get_coef(q, i);
                if (t_equal(co_p, co_q) == FALSE)
                    return FALSE;
            }
        }

        return TRUE;
    }
}

int ply_is_zero(Polynomial *p) {
    if (p->deg != 0)
        return FALSE;
    else {
        tvalue coef0 = ply_get_coef(p, 0);
        if (t_is_zero(coef0) == TRUE)
            return TRUE;
        else
            return FALSE;
    }

}

void ply_zero(Polynomial *z) {
    dtype t = z->type;
    z->deg = 0;

    tvalue tz;
    switch(t) {
        case DBL: 
            t_init_dbl(&tz);
            break;
        case MOD:
            break;
    }

    t_zero(&tz);

    ply_set_coef(z, 0, tz);

    t_delete(&tz);

    return;
}

void ply_monomial(int deg, Polynomial *m) {
    dtype t = m->type;
    m->deg = deg;
    int i;
    tvalue t_z;
    tvalue t_e;
    switch(t) {
        case DBL: 
            t_init_dbl(&t_z);
            t_init_dbl(&t_e);
            break;
        case MOD:
            break;
    }

    t_zero(&t_z);
    t_identity(&t_e);

    for (i=0; i<deg; i++) {
        ply_set_coef(m, i, t_z);
    }

    ply_set_coef(m, deg, t_e);

    t_delete(&t_z);
    t_delete(&t_e);

    return;
}

void ply_sum(Polynomial *poly1, Polynomial *poly2, Polynomial *sum_poly) {
    dtype t = poly1->type;
    assert(t == poly2->type);
    assert(t == sum_poly->type);

    Polynomial *p1 = max_deg(poly1, poly2);
    Polynomial *p2 = min_deg(poly1, poly2);
    int deg1 = p1->deg;
    int deg2 = p2->deg;

    tvalue sum_coefs[deg1+1];
    tvalue sum;

    switch(t) {
        case DBL: {
            t_init_dbl(&sum);
            int i;
            for (i=0; i<=deg1; i++) {
                t_init_dbl(&sum_coefs[i]);
            }
        }
        
    }

    int i;
    for (i=0; i<=deg2; i++) {
        t_sum(ply_get_coef(poly1, i), ply_get_coef(poly2, i), &sum);
        t_copy(sum, &sum_coefs[i]);
    }
    
    t_delete(&sum);

    for (i=deg2+1; i<=deg1; i++) {
        t_copy(ply_get_coef(p1, i), &sum_coefs[i]);
    }
    int deg = deg1;
    while (deg >= 0) {
        if (t_is_zero(sum_coefs[deg]) == FALSE)
            break;
        if (deg == 0)
            break;
        deg = deg - 1;
    }

    sum_poly->deg = deg;
    ply_fill(sum_poly, sum_coefs);

    for (i=0; i<=deg; i++) {
        t_delete(&sum_coefs[i]);
    }



    return;
}

void ply_product(Polynomial *poly1, Polynomial *poly2, Polynomial *prod_poly) {
    dtype t = poly1->type;
    assert(t == poly2->type);
    assert(t == prod_poly->type);

    if (ply_is_zero(poly1) == TRUE) {
        ply_zero(prod_poly);
        return;
    }
    else if (ply_is_zero(poly2) == TRUE) {
        ply_zero(prod_poly);
        return;
    }
    else {
        Polynomial *p1 = max_deg(poly1, poly2);
        Polynomial *p2 = min_deg(poly1, poly2);
        int deg1 = p1->deg;
        int deg2 = p2->deg;
        int deg = deg1+deg2;
        prod_poly->deg = deg;

        tvalue sum_k;
        tvalue s;

        switch(t) {
            case DBL:
                t_init_dbl(&sum_k);
                t_init_dbl(&s);
                break;
            case MOD:
                break;
        }

        int k;
        for (k=0; k<=deg; k++) {
            t_zero(&sum_k);
                int l;
                for (l=0; l<=k; l++) {
                    if ((l<=deg1)&&(k-l<=deg2)) {
                        t_product(ply_get_coef(p1, l), ply_get_coef(p2, k-l), &s);
                        t_sum(sum_k, s, &sum_k);
                    }
                }
            ply_set_coef(prod_poly, k, sum_k);
        }

        t_delete(&sum_k);
        t_delete(&s);

        return;
    }
}

void ply_scale(tvalue s, Polynomial *p, Polynomial *sp) {
    dtype t = p->type;
    assert(t == s.type);
    assert(t == sp->type);

    if (t_is_zero(s) == TRUE) {
        ply_zero(sp);
        return;
    }
    else {
        int n = p->deg;
        sp->deg = n;

        int i;
        for(i=0; i<=n; i++) {
            tvalue coef = ply_get_coef(p, i);
            t_product(coef, s, &coef);
            ply_set_coef(sp, i, coef);
        }

        return;
    }
}

void ply_neg(Polynomial *p, Polynomial *neg) {
    dtype t = p->type;
    assert(t == neg->type);

    tvalue t_e;
    tvalue t_neg_e;

    switch(t) {
        case DBL:
            t_init_dbl(&t_e);
            t_init_dbl(&t_neg_e);
            break;
        case MOD:
            break;
    }

    t_identity(&t_e);
    t_neg(t_e, &t_neg_e);
 
    ply_scale(t_neg_e, p, neg);

    t_delete(&t_e);
    t_delete(&t_neg_e);
    return;
}

// f = a_nx^n + ... + a_0
// g = b_mx^m _ ... + b_0
// put q = a/bx^(n-m)
// put r = f - gq which kills the leading term in f
static void sub_division(Polynomial *f, Polynomial *g, Polynomial *q, Polynomial *r) {
    dtype t = f->type;
    assert(t == g->type);
    assert(t == q->type);
    assert(t == r->type);

    assert(g->deg <= f->deg);
    int deg_q = f->deg - g->deg;
    ply_monomial(deg_q, q);

    tvalue f_coef = ply_get_coef(f, f->deg);
    tvalue g_coef_inv;
    t_inv(ply_get_coef(g, g->deg), &g_coef_inv);
    tvalue coef;
    t_product(f_coef, g_coef_inv, &coef);
    ply_set_coef(q, deg_q, coef);

    Polynomial *prod = ply_create(t, 0);
    Polynomial *neg = ply_create(t, 0);
    ply_product(g, q, prod);
    ply_neg(prod, neg);
    ply_sum(f, neg, r);

    ply_delete(prod);
    ply_delete(neg);

    return;
}

// Division algorithm: divides f by g and returns struct containing quotient, remainder.
// Remember to free pair and the polys it contains after use.
void ply_division(Polynomial *f, Polynomial *g, Polynomial *q, Polynomial *r) {
    dtype t = f->type;
    assert(t == g->type);
    assert(t == q->type);
    assert(t == r->type);
    assert(ply_is_zero(g) == FALSE);

    ply_zero(q);
    ply_copy(f, r);

    if ((f->deg < g->deg) || (ply_is_zero(f) == TRUE)) {

        return;
    }
    else {
        Polynomial *q_temp = ply_create(t, 0);
        Polynomial *r_temp = ply_create(t, 0);

        while ((r->deg >= g->deg) && (ply_is_zero(r)==FALSE)) {
            sub_division(r, g, q_temp, r_temp);
            ply_sum(q, q_temp, q);
            ply_copy(r_temp, r);
        }

        ply_delete(q_temp);
        ply_delete(r_temp);

        return;
    }
}

// return gcd and Bezout coefficients for f,g, i.e. gcd = af+bg
void ply_gcd(Polynomial *f, Polynomial *g, Polynomial *gcd, Polynomial *a, Polynomial *b) {
    dtype t = f->type;
    assert(t == g->type);
    assert(t == gcd->type);
    assert(t == a->type);
    assert(t == b->type);
    assert(((ply_is_zero(f) == TRUE) && (ply_is_zero(g) == TRUE)) == FALSE);

    if (ply_is_zero(f)==TRUE) {
        ply_copy(g, gcd);
        ply_zero(a);
        ply_monomial(0, b);
    
        return;
    }
    else if (ply_is_zero(g)==TRUE) {
        ply_copy(f, gcd);
        ply_monomial(0, a);
        ply_zero(b);

        return;
    }
    else {
        Polynomial *max = max_deg(f, g);
        Polynomial *min = min_deg(f,g);
        // use division alg to get r0 = q1*r1 + r2
        // then gcd(r0, r1) = gcd(r1, r2)
        // and (r1, r2) = (r0, r1) |0   1|
        //                         |1 -q1|
        // repeat this to get (r_{k-1}, r_k) = (r0, r1) * product from i = 1 to k-1 |0    1|
        //                                                                          |1 -q_i|
        // repeat until r_k = 0, then r_{k-1} = gcd(r0, r1)

        Polynomial *q1 = ply_create(t, 0);
        Polynomial *r0 = ply_create(t, 0); 
        Polynomial *r1 = ply_create(t, 0);
        Polynomial *r2 = ply_create(t, 0);

        ply_copy(max, r0);
        ply_copy(min, r1);
        ply_division(r0, r1, q1, r2);

        Matrix *prod = mat_create(PLY, 2, 2);
        Matrix *prod_temp = mat_create(PLY, 2, 2);
        Matrix *next = mat_create(PLY, 2, 2);

        mat_init_ply(prod, t);
        mat_init_ply(prod_temp, t);
        mat_init_ply(next, t);

        Polynomial *z = ply_create(t, 0);
        Polynomial *e = ply_create(t, 0);
        Polynomial *neg_q1 = ply_create(t, 0);

        ply_zero(z);
        ply_monomial(0, e);
        ply_neg(q1, neg_q1);

        ply_copy(z, mat_get_entry(prod, 0, 0).val.plyval);
        ply_copy(e, mat_get_entry(prod, 0, 1).val.plyval);
        ply_copy(e, mat_get_entry(prod, 1, 0).val.plyval);
        ply_copy(neg_q1, mat_get_entry(prod, 1, 1).val.plyval);

        mat_copy(prod, next);

        while(ply_is_zero(r2) == FALSE) {
            ply_copy(r1, r0);
            ply_copy(r2, r1);
            ply_division(r0, r1, q1, r2);

            ply_neg(q1, neg_q1); // -q1
            ply_copy(neg_q1, mat_get_entry(next, 1, 1).val.plyval);
            mat_product(prod, next, prod_temp);

            mat_copy(prod_temp, prod);
        }

        int deg = r1->deg;
        tvalue lead_coef = ply_get_coef(r1, deg);
        tvalue lead_coef_inv; 
        switch (t) {
            case DBL:
                t_init_dbl(&lead_coef_inv);
                break;
            //case FFE:
            //    t_init_ffe(t, lead_coef_inv);

        }

        t_inv(lead_coef, &lead_coef_inv);
        ply_scale(lead_coef_inv, r1, gcd);

        if (ply_equal(max, f) == TRUE) {
            ply_scale(lead_coef_inv, mat_get_entry(prod, 0, 0).val.plyval, a);
            ply_scale(lead_coef_inv, mat_get_entry(prod, 1, 0).val.plyval, b);
        }
        else {
            ply_scale(lead_coef_inv, mat_get_entry(prod, 0, 0).val.plyval, b);
            ply_scale(lead_coef_inv, mat_get_entry(prod, 1, 0).val.plyval, a);
        }

        t_delete(&lead_coef_inv);
        ply_delete(q1);
        ply_delete(r0);
        ply_delete(r1);
        ply_delete(r2);
        ply_delete(z);
        ply_delete(e);
        ply_delete(neg_q1);

        mat_delete(prod);
        mat_delete(prod_temp);
        mat_delete(next);

        return;
    }
}

//polynomial arithmetic modulo m(x)
//--------------------------------------------------
void ply_mod_reduce(Polynomial *p, Polynomial *m) {
    dtype t = p->type;
    assert(t == m->type);
    assert(ply_is_zero(m)==FALSE);

    Polynomial *q = ply_create(t, 0);
    Polynomial *r = ply_create(t, 0);
    ply_division(p, m, q, r);
    
    ply_copy(r, p);
    ply_delete(q);
    ply_delete(r);
    
    return;
}

void ply_mod_inv(Polynomial *p, Polynomial *inv, Polynomial *m) {
    dtype t = p->type;
    assert(t == m->type);
    assert(t == inv->type);
    assert(ply_is_zero(m)==FALSE);

    Polynomial *gcd = ply_create(t, 0);
    Polynomial *a = ply_create(t, 0);
    Polynomial *b = ply_create(t, 0);
    ply_gcd(p, m, gcd, a, b);

    ply_copy(a, inv);
    ply_mod_reduce(inv, m);

    ply_delete(gcd);
    ply_delete(a);
    ply_delete(b);

    return;
}

void ply_mod_sum(Polynomial *p, Polynomial *q, Polynomial *sum, Polynomial *m) {
    ply_sum(p, q, sum);
    ply_mod_reduce(sum, m);

    return;
}

void ply_mod_product(Polynomial *p, Polynomial *q, Polynomial *prod, Polynomial *m)  {
    ply_product(p, q, prod);
    ply_mod_reduce(prod, m);

    return;
}

/*


// analysis

// Horner's method
double ply_evaluate(Polynomial poly, double x) {
    int deg = poly.deg;
    double coefn = ply_get_coef(poly, deg);
    assert(coefn!=0);

    double val = coefn;
    if (deg==0) {
        return val;
    }
    else if (deg>0) {
        while (deg>0) {
            val = val*x + ply_get_coef(poly, deg-1);
            deg = deg-1;
        }
    }

    return val;
}

Polynomial ply_differentiate(Polynomial poly, int n) {
    int deg = poly.deg;
    if (deg<n) {
        Polynomial deriv = ply_create(0);
        ply_set_coef(&deriv, 0, 0.0);
        return deriv;
    }
    else {
        int dn_deg = deg-n;
        double dn_coefs[dn_deg+1];
        int i;
        for (i=0; i<=dn_deg; i++) {
            dn_coefs[i] = cnt_factorial(n+i, i+1)*ply_get_coef(poly, n+i);
        }

        while (dn_deg>=0) {
            if (dn_coefs[dn_deg]!=0)
                break;
            if (dn_deg==0)
                break;
            dn_deg = dn_deg-1;
        }

        Polynomial deriv = ply_create(dn_deg);
        for (i=0; i<=dn_deg; i++) {
            double coef = dn_coefs[i];
            ply_set_coef(&deriv, i, coef);
        }

        return deriv;
    }
}

*/