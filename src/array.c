#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/array.h"

#define TRUE 1
#define FALSE 0

int arr_equal(double *arr1, double *arr2, int len1, int len2) {
    if (len1 != len2) {
        return FALSE;
    }
    int i;
    for (i=0; i<len1; i++) {
        if (arr1[i] != arr2[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

double arr_sum(double *arr, int len) {
    int i;
    double sum = 0;
    for (i=0; i<len; i++) {
        sum = sum + arr[i];
    }

    return sum;
}