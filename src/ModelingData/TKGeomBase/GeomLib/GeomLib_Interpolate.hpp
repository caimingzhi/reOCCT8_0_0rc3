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

//! This class is used to construct a BSpline curve by
//! interpolation of points at given parameters. The
//! continuity of the curve is degree - 1 and the
//! method used when boundary conditions are not given
//! is to use odd degrees and null the derivatives on
//! both sides from degree -1 down to (degree+1) / 2
//! When even degree is given the returned curve is of
//! degree - 1 so that the degree of the curve is odd
class GeomLib_Interpolate
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_Interpolate(const int                         Degree,
                                      const int                         NumPoints,
                                      const NCollection_Array1<gp_Pnt>& Points,
                                      const NCollection_Array1<double>& Parameters);

  //! returns if everything went OK
  bool IsDone() const;

  //! returns the error type if any
  GeomLib_InterpolationErrors Error() const;

  //! returns the interpolated curve of the requested degree
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

//=================================================================================================

inline GeomLib_InterpolationErrors GeomLib_Interpolate::Error() const
{
  return myError;
}
