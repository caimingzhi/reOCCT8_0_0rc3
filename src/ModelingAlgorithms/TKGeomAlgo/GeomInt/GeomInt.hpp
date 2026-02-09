#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

class GeomInt
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool AdjustPeriodic(const double thePar,
                                             const double theParMin,
                                             const double theParMax,
                                             const double thePeriod,
                                             double&      theNewPar,
                                             double&      theOffset,
                                             const double theEps = 0.0);
};
