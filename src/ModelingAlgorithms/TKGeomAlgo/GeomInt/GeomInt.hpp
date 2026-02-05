#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Real.hpp>

//! Provides intersections on between two surfaces of Geom.
//! The result are curves from Geom.
class GeomInt
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adjusts the parameter <thePar> to the range [theParMin, theParMax]
  Standard_EXPORT static bool AdjustPeriodic(const double thePar,
                                             const double theParMin,
                                             const double theParMax,
                                             const double thePeriod,
                                             double&      theNewPar,
                                             double&      theOffset,
                                             const double theEps = 0.0);
};
