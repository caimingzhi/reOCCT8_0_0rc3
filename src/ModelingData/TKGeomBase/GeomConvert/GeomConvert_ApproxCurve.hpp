#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_OStream.hpp>

class Geom_BSplineCurve;
class Geom_Curve;

//! A framework to convert a 3D curve to a 3D BSpline.
//! This is done by approximation to a BSpline curve within a given tolerance.
class GeomConvert_ApproxCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs a curve approximation framework defined by -
  //! -      the conic Curve,
  //! -      the tolerance value Tol3d,
  //! -      the degree of continuity Order,
  //! -      the maximum number of segments
  //! MaxSegments allowed in the resulting BSpline curve, and
  //! -      the highest degree MaxDeg which the
  //! polynomial defining the BSpline curve may have.
  Standard_EXPORT GeomConvert_ApproxCurve(const occ::handle<Geom_Curve>& Curve,
                                          const double                   Tol3d,
                                          const GeomAbs_Shape            Order,
                                          const int                      MaxSegments,
                                          const int                      MaxDegree);

  //! Constructs a curve approximation framework defined by -
  //! -      the Curve,
  //! -      the tolerance value Tol3d,
  //! -      the degree of continuity Order,
  //! -      the maximum number of segments
  //! MaxSegments allowed in the resulting BSpline curve, and
  //! -      the highest degree MaxDeg which the
  //! polynomial defining the BSpline curve may have.
  Standard_EXPORT GeomConvert_ApproxCurve(const occ::handle<Adaptor3d_Curve>& Curve,
                                          const double                        Tol3d,
                                          const GeomAbs_Shape                 Order,
                                          const int                           MaxSegments,
                                          const int                           MaxDegree);

  //! Returns the BSpline curve resulting from the approximation algorithm.
  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve() const;

  //! returns true if the approximation has
  //! been done within required tolerance
  Standard_EXPORT bool IsDone() const;

  //! Returns true if the approximation did come out
  //! with a result that is not NECESSARELY within the required tolerance
  Standard_EXPORT bool HasResult() const;

  //! Returns the greatest distance between a point on the
  //! source conic and the BSpline curve resulting from the
  //! approximation. (>0 when an approximation
  //! has been done, 0 if no approximation)
  Standard_EXPORT double MaxError() const;

  //! Print on the stream o information about the object
  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  //! Converts a curve to B-spline
  Standard_EXPORT void Approximate(const occ::handle<Adaptor3d_Curve>& theCurve,
                                   const double                        theTol3d,
                                   const GeomAbs_Shape                 theOrder,
                                   const int                           theMaxSegments,
                                   const int                           theMaxDegree);

  bool                           myIsDone;
  bool                           myHasResult;
  occ::handle<Geom_BSplineCurve> myBSplCurve;
  double                         myMaxError;
};
