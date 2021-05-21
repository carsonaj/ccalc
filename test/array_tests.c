#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/type.h"
#include "../include/array.h"

#define TRUE 1
#define FALSE 0

// define tests:
void test_arr_equal() {
    double arr1[3] = {2, 4,-1};
    tvalue tarr1[3];
    t_dbls(arr1, tarr1, 3);

    double arr2[2] = {1, 2};
    tvalue tarr2[2];
    t_dbls(arr2, tarr2, 2);

    double arr3[3] = {2, 4, -2};
    tvalue tarr3[3];
    t_dbls(arr3, tarr3, 3);

    double arr4[3] = {2, 4, -1};
    tvalue tarr4[3];
    t_dbls(arr4, tarr4, 3);

    assert(arr_equal(tarr1, tarr2, 3, 2) == FALSE);
    assert(arr_equal(tarr1, tarr3, 3, 3) == FALSE);
    assert(arr_equal(tarr1, tarr4, 3, 3) == TRUE);

}

void test_arr_sum() {
    double arr[3] = {2, 1, -1};
    tvalue tarr[3];
    t_dbls(arr, tarr, 3);
    tvalue sum;
    arr_sum(tarr, 3, &sum);
    assert(sum.val.dblval == 2.0);

    return;
}
//===========================================================================================
//===========================================================================================

// run tests:
int main() {
    test_arr_equal();
    test_arr_sum(); 
    
    return 0;
}