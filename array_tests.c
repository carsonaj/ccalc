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
//===========================================================================================
//===========================================================================================

// run tests:
int main() {
    test_arr_equal;
    
    return 0;
}