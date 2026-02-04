#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <GeomAbs_CurveType.hpp>
class LProp_CurAndInf;

//! Computes the locals extremas of curvature of a gp curve
//! Remark : a gp curve has not inflection.
class LProp_AnalyticCurInf
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT LProp_AnalyticCurInf();

  Standard_EXPORT void Perform(const GeomAbs_CurveType T,
                               const double            UFirst,
                               const double            ULast,
                               LProp_CurAndInf&        Result);
};

