# type.h:

## tvalue:
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

## functions:
* `void t_print`: prints a tvalue <br>
**input**: <br>
  `tvalue` <br>
**output**:<br>
  `NULL` <br> 
<br>

- **example**: <br>
    ```
    tvalue tval = t_dbl(2.3);
    t_print(tval);
    ```
    `2.30`






* `tvalue t_dbl`: transform a double to its corresponding tvalue <br>
**input**: <br>
  `double`<br>
**output**:<br>
  `tvalue`<br>

* `void t_dbls`: transform an array of doubles to an array of corresponding tvalues <br>
**input**: <br>
  `double *, tvalue *, int` <br>
**output**: <br>
  `NULL` <br>

* `int t_equal`: decides whether two tvalues are equal or not <br>
**input**: <br>
  `tvalue`, `tvalue`  <br>
**output**: <br>
  `int`: `0` - FALSE, `1` - TRUE <br>

* `tvalue t_zero`: generates the additive identity of a given dtype <br>
**input**: <br>
  `dtype`  <br>
**output**: <br>
  `tvalue` <br>

* `tvalue t_neg`: generates the additive inverse of a given tvalue <br>
**input**: <br>
  `tvalue`  <br>
**output**: <br>
  `tvalue` <br>

* `tvalue t_inv`: if applicable, generates the multiplicative inverse of a given tvalue <br>
**input**: <br>
  `tvalue`: a nonzero tvalue that is invertible  <br>
**output**: <br>
  `tvalue` <br>

* `tvalue t_sum`: computes the sum of two tvalues<br>
**input**: <br>
  `tvalue`, `tvalue`  <br>
**output**: <br>
  `tvalue` <br>

* `tvalue t_product`: computes the product of two tvalues <br>
**input**: <br>
  `tvalue` `tvalue` <br>
**output**: <br>
  `tvalue` <br>


