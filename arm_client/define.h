#ifndef DEFINE_H
#define DEFINE_H

#include <iostream>

/*
#include "fixed_point/fixed_class.h"
#include "fpml/fixed_point.h"


typedef fixedpoint::fixed_point<16> fixed_point;
typedef float RealNum;



#define FLOAT

inline float realNumToFloat(RealNum r)
{
#ifdef FLOAT
    return r;
#endif
#ifdef FIXED_POINT
    return fixedpoint::fix2float<16>(r.intValue);
#endif
#ifdef FPML
    return r.operator float();
#endif
}
*/

#endif // DEFINE_H
