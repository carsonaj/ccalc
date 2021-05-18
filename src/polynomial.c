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

    return poly;
}

void ply_delete(Polynomial *poly) {
    assert(poly != NULL);
    dtype t = poly->type;
    switch (t) {
        case DBL:
            break;
        case ALN: // must free each value as well
            break;
    }

    free(poly->coefs);
    free(poly);

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
        poly->coefs[i] = coefs[i];
    }

    return;
}

// make sure coefs has length deg + 1
void ply_fill_dbl(Polynomial *poly, double *coefs) {
    assert(poly->type == DBL);
    int deg = poly->deg;
    tvalue t_coefs[deg + 1];
    t_dbls(coefs, t_coefs, deg + 1);
    ply_fill(poly, t_coefs);

    return;
}

tvalue ply_get_coef(Polynomial *poly, int i) {
    return poly->coefs[i];
}

void ply_set_coef(Polynomial *poly, int i, tvalue tval) {
    poly->coefs[i] = tval;
}

// copy coefs of poly p into poly q
void ply_copy(Polynomial *p, Polynomial *q) {
    assert(p->type == q->type);
    assert(p->deg == q->deg);
    int d = p->deg;
    int i;
    for (i=0; i <= d; i++) {
        tvalue coef = ply_get_coef(p, i);
        ply_set_coef(q, i, coef);
    }

    return;
}

void ply_print(Polynomial *poly) {
    dtype t = poly->type;
    switch (t) {
        case DBL:
            ply_print_dbl(poly);
            break;
    }
}

void ply_print_dbl(Polynomial *poly) {
    assert(poly->type == DBL);
    int deg = poly->deg;
    tvalue coef0 = ply_get_coef(poly, 0);
    tvalue coefn = ply_get_coef(poly, deg); //PROBLEM
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

void ply_sum(Polynomial *poly1, Polynomial *poly2, Polynomial *sum_poly) {
    assert(poly1->type == poly2->type);

    Polynomial *p1 = max_deg(poly1, poly2);
    Polynomial *p2 = min_deg(poly1, poly2);
    int deg1 = p1->deg;
    int deg2 = p2->deg;

    tvalue sum_coefs[deg1+1];
    int i;
    for (i=0; i<=deg2; i++) {
        sum_coefs[i] = t_sum(ply_get_coef(poly1, i), ply_get_coef(poly2, i));
    }
    for (i=deg2+1; i<=deg1; i++) {
        sum_coefs[i] = ply_get_coef(p1, i);
    }
    int deg = deg1;
    while (deg >= 0) {
        if (t_is_zero(sum_coefs[deg]) == FALSE)
            break;
        if (deg == 0)
            break;
        deg = deg-1;
    }

    sum_poly->deg = deg;
    for (i=0; i<=deg; i++) {
        tvalue coef = sum_coefs[i];
        ply_set_coef(sum_poly, i, coef);
    }

    return;
}

void ply_product(Polynomial *poly1, Polynomial *poly2, Polynomial *prod_poly) {
    assert(poly1->type == poly2->type);
    dtype t = poly1->type;

    if (ply_is_zero(poly1) == TRUE) {
        prod_poly->deg = 0;
        ply_set_coef(prod_poly, 0, t_zero(prod_poly->type));
        return;
    }
    else if (ply_is_zero(poly2) == TRUE) {
        prod_poly->deg = 0;
        ply_set_coef(prod_poly, 0, t_zero(prod_poly->type));
        return;
    }
    else {
        Polynomial *p1 = max_deg(poly1, poly2);
        Polynomial *p2 = min_deg(poly1, poly2);
        int deg1 = p1->deg;
        int deg2 = p2->deg;
        int deg = deg1+deg2;

//      *******************************
//      *******************************
//      *******************************
//      *******************************
//      Warning: might need to delete lots of coeficient values to 
//               avoid memory leak in the case of algebraic numbers
        int k;
        prod_poly->deg = deg;
        for (k=0; k<=deg; k++) {
            tvalue sum_k = t_zero(t);
                int l;
                for (l=0; l<=k; l++) {
                    if ((l<=deg1)&&(k-l<=deg2)) {
                        tvalue s = t_product(ply_get_coef(p1, l), ply_get_coef(p2, k-l));
                        sum_k = t_sum(sum_k, s);
                    }
                }
            ply_set_coef(prod_poly, k, sum_k);
        }

        return;
    }
}

void ply_scale(tvalue s, Polynomial *p, Polynomial *sp) {
    assert(s.type = p->type);
    dtype t = p->type;

    if (t_is_zero(s) == TRUE) {
        p->deg = 0;
        ply_set_coef(p, 0, t_zero(t));
        return;
    }
    else {
        int n = p->deg;

        int i;
        for(i=0; i<=n; i++) {
            tvalue coef = ply_get_coef(p, i);
            ply_set_coef(sp, i, t_prod(s , coef));
        }

        return sp;
    }
}

Polynomial ply_neg(Polynomial p) {
    Polynomial neg = ply_scale(-1.0, p);
    return neg;
}




/* 
**********************************
**********************************
**********************************
**********************************




//---------------------------------------------------------------
static PolyMatrix sub_division(Polynomial f, Polynomial g) {
    Polynomial q;
    Polynomial r;

    int deg_q = f.deg - g.deg;
    q = ply_monomial(deg_q);

    double coef = ply_get_coef(f, f.deg)/ply_get_coef(g, g.deg);
    ply_set_coef(&q, deg_q, coef);

    Polynomial prod = ply_product(g, q);
    Polynomial scaled = ply_scale(-1.0, prod);
    r = ply_sum(f, scaled);

    PolyMatrix pair = pymat_create(1, 2);
    pymat_set_element(&pair, 0, 0, q);
    pymat_set_element(&pair, 0, 1, r);

    return pair;
}

// division algorithm: divides f by g and
// returns struct containing quotient, remainder

// remember to free pair and the polys it contains after use
PolyMatrix ply_division(Polynomial f, Polynomial g) {
    assert(ply_is_zero(g)==FALSE);
    Polynomial q0 = ply_zero();
    Polynomial r0 = ply_copy(f);

    Polynomial q = q0;
    Polynomial r = r0;
    PolyMatrix pair;

    if (f.deg < g.deg || ply_is_zero(f)==TRUE) {
        pair = pymat_create(1,2);
        pymat_set_element(&pair, 0, 0, q);
        pymat_set_element(&pair, 0, 1, r);

        return pair;
    }
    else {
        while (r.deg >= g.deg && ply_is_zero(r)==FALSE) {
            pair = sub_division(r, g);
            Polynomial temp_q = pymat_get_element(pair, 0, 0);
            Polynomial temp_r = pymat_get_element(pair, 0, 1);

            q = ply_sum(q, temp_q);
            r = ply_copy(temp_r);

        }

        pair = pymat_create(1,2);
        pymat_set_element(&pair, 0, 0, q);
        pymat_set_element(&pair, 0, 1, r);

        return pair;
    }
}

// return gcd and Bezout coefficients for f,g
PolyMatrix ply_gcd(Polynomial f, Polynomial g) {
    assert((ply_is_zero(f)==TRUE && ply_is_zero(f)==TRUE)==FALSE);
    PolyMatrix result = pymat_create(1, 3);

    if (ply_is_zero(f)==TRUE) {
        pymat_set_element(&result, 0, 0, g);
        pymat_set_element(&result, 0, 1, ply_zero());
        pymat_set_element(&result, 0, 2, ply_monomial(0));

        return result;
    }

    else if (ply_is_zero(g)==TRUE) {
        pymat_set_element(&result, 0, 0, f);
        pymat_set_element(&result, 0, 1, ply_monomial(0));
        pymat_set_element(&result, 0, 2, ply_zero());

        return result;
    }

    else {
        int flip = FALSE;
        Polynomial p1;
        Polynomial p2;
        if (f.deg > g.deg) {
            p1 = f;
            p2 = g;
        }
        else {
            p1 = g;
            p2 = f;
            flip = TRUE;
        }

        PolyMatrix a = pymat_create(1, 2);
        PolyMatrix b = pymat_create(1, 2);
        PolyMatrix c = pymat_create(1, 2);

        pymat_set_element(&a, 0, 0, ply_monomial(0));
        pymat_set_element(&a, 0, 1, ply_zero());
        pymat_set_element(&b, 0, 0, ply_zero());
        pymat_set_element(&b, 0, 1, ply_monomial(0));
        pymat_set_element(&c, 0, 0, ply_zero());
        pymat_set_element(&c, 0, 1, ply_monomial(0));

        while(1) {
            PolyMatrix qr = ply_division(p1, p2);
            Polynomial q = pymat_get_element(qr, 0, 0);
            Polynomial r = pymat_get_element(qr, 0, 1);

            if (ply_is_zero(r))
                break;

            PolyMatrix scaled = pymat_poly_scale(q, b);
            PolyMatrix neg_qb = pymat_scale(-1.0, scaled);
            c = pymat_sum(a, neg_qb);

            p1 = ply_copy(p2);
            p2 = ply_copy(r);

            a = b;
            b = c;

        }
        double coef = ply_get_coef(p2, p2.deg);
        if (coef != 1.0) {
            Polynomial t_p2 = p2;
            PolyMatrix t_c = c;

            p2 = ply_scale(1.0/coef, t_p2);
            c = pymat_scale(1.0/coef, t_c);

        }

        Polynomial c00 = pymat_get_element(c, 0, 0);
        Polynomial c01 = pymat_get_element(c, 0, 1);

        pymat_set_element(&result, 0, 0 ,p2);
        if (flip == TRUE) {
            pymat_set_element(&result, 0, 1, c01);
            pymat_set_element(&result, 0, 2, c00);
        }
        else {
            pymat_set_element(&result, 0, 1, c00);
            pymat_set_element(&result, 0, 2, c01);
        }


        return result;
    }
}

//polynomial arithmetic modulo m(x)
//--------------------------------------------------
Polynomial pymod_reduce(Polynomial p, Polynomial m) {
    assert(ply_is_zero(m)==FALSE);
    PolyMatrix pair = ply_division(p, m);
    Polynomial pmodm = pymat_get_element(pair, 0, 1);
    return pmodm;
}

Polynomial pymod_inv(Polynomial p, Polynomial m) {
    PolyMatrix res = ply_gcd(p,m);
    Polynomial pinv_modm = pymat_get_element(res, 0, 1);
    if (pinv_modm.deg >= m.deg) {
        pinv_modm = pymod_reduce(p, m);
    }

    return pinv_modm;
}

Polynomial pymod_sum(Polynomial p, Polynomial q, Polynomial m) {
    Polynomial sum = ply_sum(p, q);
    sum = pymod_reduce(sum, m);

    return sum;
}

Polynomial pymod_product(Polynomial p, Polynomial q, Polynomial m) {
    Polynomial prod = ply_product(p, q);
    prod = pymod_reduce(prod, m);

    return prod;
}






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