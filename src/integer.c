#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/matrix.h"

#define TRUE 1
#define FALSE 0

static int abs_val(int x) {
    if (x < 0) 
        return -x;
    else    
        return x;
}

static int max_val(int a, int b) {
    if (a >= b)
        return a;
    else
        return b;
}

static int min_val(int a, int b) {
    if (a >= b)
        return b;
    else
        return a;
}

int int_reduce(int n, int p) {
    if (n < 0) {
        return n % p + p;
    }
    else {
        return n % p;
    }
}

void int_gcd(int n, int p, int *gcd, int *a, int *b) {
    assert((n != 0) || (p != 0));
    assert(n >= 0);
    assert(p >= 0);
    if (n == 0) {
        *gcd = p;
        *a = 0;
        *b = 1;
        
        return;
    }
    else if (p == 0) {
        *gcd = n;
        *a = 1;
        *b = 0;
        
        return;
    }

    else {
        int max = max_val(abs_val(n), abs_val(p));
        int min = min_val(abs_val(n), abs_val(p));
        
        int r0 = max;
        int r1 = min;
        int r2 = r0 % r1;
        int q1 = r0 / r1;
        
        Matrix *prod = mat_create(INT, 2, 2);
        mat_init_int(prod);
        int prod_entries[4] = {0, 1, 1, -q1};
        mat_fill_int(prod, prod_entries);

        Matrix *prod_temp = mat_create(INT, 2, 2);
        mat_init_int(prod_temp);
        mat_fill_int(prod_temp, prod_entries);

        Matrix *next = mat_create(INT, 2, 2);
        mat_init_int(next);
        mat_fill_int(next, prod_entries);

        tvalue next11;
        t_init_int(&next11);

        while(r2 != 0) {
            r0 = r1;
            r1 = r2;
            r2 = r0 % r1;
            q1 = r0 / r1;

            t_int(-q1, &next11);
            mat_set_entry(next, 1, 1, next11);

            mat_product(prod_temp, next, prod);
            mat_copy(prod, prod_temp);

        }

        *gcd = r1;
        if (max == abs_val(n)) {
            *a = mat_get_entry(prod, 0, 0).val.intval;
            *b = mat_get_entry(prod, 1, 0).val.intval;   
        }
        else {
            *b = mat_get_entry(prod, 0, 0).val.intval;
            *a = mat_get_entry(prod, 1, 0).val.intval;
        }

        mat_delete(prod);
        mat_delete(prod_temp);
        mat_delete(next);

        return;

    }

}

