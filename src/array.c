#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/array.h"

#define TRUE 1
#define FALSE 0

int arr_equal(tvalue *arr1, tvalue *arr2, int len1, int len2) {
    if (len1 != len2) {
        return FALSE;
    }
    int i;
    for (i=0; i<len1; i++) {
        if (t_equal(arr1[i], arr2[i]) == FALSE) {
            return FALSE;
        }
    }
    return TRUE;
}

void arr_sum(tvalue *arr, int len, tvalue *sum) {
    dtype t = arr[0].type;
    t_zero(t, sum);
    int i;
    for (i=0; i<len; i++) {
        t_sum(*sum, arr[i], sum);
    }

    return;
}