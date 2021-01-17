#include "../include/type.h"

tvalue tdbl(double val) {
    tvalue tval;
    tval.type = DBL;
    tval.val.dblval = val;

    return tval;
}

tvalues tdbls(double *vals) {
    tvalues tvals;
    tvals.type = DBL;
    tvals.vals.dblvals = vals;

    return tvals;
}