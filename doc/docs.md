# Documentation:

## type:
Everything in `ccalc` revolves around the notion of the typed value or "tvalue". A tvalue is simply a structure containing a datatype and a value where the datatype is represented by an `enum` and the value is represented by a `union`. 

Currently the supported datatypes include `double`, `Polynomial *`, `NumFld *`, `FinFld *`.

Specifically, we have the following: 

```
typedef enum dtype dtype; 
typedef union value value;
typedef struct tvalue tvalue;

enum dtype {
    DBL, // double
    PLY, // polynomial
    NF   // number field element
    FF   // finite field element
};

union value {
    double dblval;
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

Depending on `t`, we know to which to access among `v.dbl`, ...