#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

enum GeomLib_InterpolationErrors
{
  GeomLib_NoError,
  GeomLib_NotEnoughtPoints,
  GeomLib_DegreeSmallerThan3,
  GeomLib_InversionProblem
};

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>
class Geom_BSplineCurve;

class GeomLib_Interpolate
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_Interpolate(const int                         Degree,
                                      const int                         NumPoints,
                                      const NCollection_Array1<gp_Pnt>& Points,
                                      const NCollection_Array1<double>& Parameters);

  bool IsDone() const;

  GeomLib_InterpolationErrors Error() const;

  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve() const;

private:
  occ::handle<Geom_BSplineCurve> myCurve;
  bool                           myIsDone;
  GeomLib_InterpolationErrors    myError;
};

inline bool GeomLib_Interpolate::IsDone() const
{
  return myIsDone;
}

inline GeomLib_InterpolationErrors GeomLib_Interpolate::Error() const
{
  return myError;
}
