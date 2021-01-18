#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"

#define TRUE 1
#define FALSE 0

// define tests:
void test_t_dbl() {
    tvalue tval = t_dbl(3.2);

    assert(tval.type == DBL);
    assert(tval.val.dblval == 3.2);

    return;
}

void test_t_dbls() {
    double vals[3] = {1, 2, 3};
    tvalue *tvals = malloc(3 * sizeof(tvalue));
    t_dbls(vals, tvals, 3);

    assert(tvals[0].type == DBL);
    assert(tvals[0].val.dblval == 1);
     assert(tvals[1].type == DBL);
    assert(tvals[1].val.dblval == 2);
     assert(tvals[2].type == DBL);
    assert(tvals[2].val.dblval == 3);
    free(tvals);

    return;
}

void test_t_zero() {
    tvalue z = t_zero(DBL);
    assert(z.val.dblval == 0.0);

    return;
}

void test_t_equal() {
    tvalue tval1 = t_dbl(1.0);
    tvalue tval2 = t_dbl(2.1);
    tvalue tval3; 
    tval3.type = DBL;
    tval3.val.dblval = 1.0;

    assert(t_equal(tval1, tval2) == FALSE);
    assert(t_equal(tval1, tval3) == TRUE);

    return;
}

void test_t_sum() {
    tvalue tval1 = t_dbl(2.0);
    tvalue tval2 = t_dbl(-3.0);
    tvalue sum = t_sum(tval1, tval2); 
    
    assert(t_equal(sum, t_dbl(-1.0)) == TRUE);

    return;
}

void test_t_product() {
    tvalue tval1 = t_dbl(2.0);
    tvalue tval2 = t_dbl(-3.0);
    tvalue sum = t_product(tval1, tval2); 
    
    assert(t_equal(sum, t_dbl(-6.0)) == TRUE);

    return;
}
//===========================================================================================
//===========================================================================================

// run tests:
int main() {
    test_t_dbl();
    test_t_dbls();
    test_t_zero();
    test_t_equal();
    test_t_sum();
    test_t_product();

    return 0;
}