#pragma once


#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_BSplineCurve.hpp>

class Approx_Curve3d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Approximation of a curve with respect of the
  //! required tolerance Tol3D.
  Standard_EXPORT Approx_Curve3d(const occ::handle<Adaptor3d_Curve>& Curve,
                                 const double                        Tol3d,
                                 const GeomAbs_Shape                 Order,
                                 const int                           MaxSegments,
                                 const int                           MaxDegree);

  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve() const;

  //! returns true if the approximation has
  //! been done within required tolerance
  Standard_EXPORT bool IsDone() const;

  //! returns true if the approximation did come out
  //! with a result that is not NECESSARILY within the required
  //! tolerance
  Standard_EXPORT bool HasResult() const;

  //! returns the Maximum Error (>0 when an approximation
  //! has been done, 0 if no approximation)
  Standard_EXPORT double MaxError() const;

  //! Print on the stream 'o' information about the object
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool                           myIsDone;
  bool                           myHasResult;
  occ::handle<Geom_BSplineCurve> myBSplCurve;
  double                         myMaxError;
};

