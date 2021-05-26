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
    t_zero(sum);
    int i;
    tvalue sum_temp;
    switch(t) {
        case DBL:
            break;
        case PLY: {
            dtype coef_type = arr[0].val.plyval->type;
            t_init_ply(coef_type, &sum_temp);
        }

    }
    for (i=0; i<len; i++) {
        t_sum(*sum, arr[i], &sum_temp);
        t_copy(sum_temp, sum);
    }

    t_delete(&sum_temp);

    return;
}