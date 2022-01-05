#ifndef __CVALUE_H__
#define __CVALUE_H__

typedef union {
    long double c_ldouble;
    long long   c_llong;
    double      c_double;
    long        c_long;
    float       c_float;
    int         c_int;
    short       c_short;
    char        c_char;
} Value;



#endif // __CVALUE_H__
