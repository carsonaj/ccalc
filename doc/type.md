# type.h:

## tvalue structure:
Everything in `ccalc` revolves around the notion of the typed value or "tvalue". A tvalue is simply a structure containing a datatype and a value as fields where the datatype is represented by an `enum` and the value is represented by a `union`. 

The supported datatypes include `double`, `Polynomial *`, `NumFldElm *`, and `FinFldElm *`. For more on these datatypes, see the following links:

`Polynomial`: 
`NumFldElm`:
`FinFldElm`:

Specifically, we have the following: 

```
typedef enum dtype dtype; 
typedef union value value;
typedef struct tvalue tvalue;

enum dtype {
    DBL, // double
    PLY, // polynomial
    NFE  // number field element
    FFE  // finite field element
};

union value {
    double dblval;
    Polynomial *plyval;
    NumFldElm *nfeval;
    FinFldElm *ffeval;
};

struct tvalue {
    dtype type;
    value val;
};
```

We may access the datatype and value of a given tvalue `tval` like so:

```
tvalue tval;

dtype t = tval.type;
value v = tval.val;
```

Depending on `t`, we know to which to access among `v.dblval`, `v.plyval`, `v.nfeval` and `v.ffeval`.

## tvalue functions:
`void t_print(tvalue tval)`: prints a tvalue <br>
**input**: <br>
        `tvalue` <br>
**output**:<br>
        `NULL` <br>


`tvalue t_dbl(double val)`: transform a double to its corresponding tvalue <br>
**input**: <br>
        `double`<br>
**output**:<br>
        `tvalue`<br>

`void t_dbls(double *vals, tvalue *tvals, int len)`: transform an array of doubles to an array of corresponding tvalues
**input**: <br>
        `double *, tvalue *, int` <br>
**output**: <br>
        `NULL` <br>


tvalue t_zero(dtype type);
tvalue t_neg(tvalue x);
tvalue t_inv(tvalue x);
int t_equal(tvalue tval1, tvalue tval2);
tvalue t_sum(tvalue tval1, tvalue tval2);
tvalue t_product(tvalue tval1, tvalue tval2);


