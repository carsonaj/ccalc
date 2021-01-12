#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
# include "array.h"

// define tests:
void test_arr_equal() {
    double arr1[3] = {2, 4,-1};
    double arr2[2] = {1, 2};
    double arr3[3] = {2, 4, -2};
    double arr4[3] = {2, 4, -1};
    assert(!arr_equal(arr1, arr2, 3, 2));
    assert(!arr_equal(arr1, arr3, 3, 3));
    assert(arr_equal(arr1, arr4, 3, 3));

}

void test_arr_sum() {
    double arr[3] = {2, 1, -1};
    assert(arr_sum(arr, 3) == 2.0);

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