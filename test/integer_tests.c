#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/integer.h"
#include "../include/matrix.h"
#include "../include/polynomial.h"

#define TRUE 1
#define FALSE 0


// define tests:

void test_int_reduce() {
    int n1 = -7;
    int n2 = 7;
    int p = 3;

    assert(int_reduce(n1, p) == 2);
    assert(int_reduce(n2, p) == 1);

    return;
}

void test_int_gcd() {
    int n = 60;
    int p = 84;
    int gcd;
    int a;
    int b;
    int_gcd(n, p, &gcd, &a, &b);

    assert(gcd == 12);
    assert(a == 3);
    assert(b == -2);

    return;
}

//===========================================================================================
//===========================================================================================

// run tests:

int main() {
    test_int_reduce();
    test_int_gcd();

    return 0;
}