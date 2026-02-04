#pragma once


#include <Adaptor2d_Curve2d.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_OStream.hpp>

class Geom2d_BSplineCurve;
class Geom2d_Curve;

//! A framework to convert a 2D curve to a BSpline.
//! This is done by approximation within a given tolerance.
class Geom2dConvert_ApproxCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructs an approximation framework defined by
  //! -   the 2D conic Curve
  //! -   the tolerance value Tol2d
  //! -   the degree of continuity Order
  //! -   the maximum number of segments allowed MaxSegments
  //! -   the highest degree MaxDegree which the
  //! polynomial defining the BSpline is allowed to have.
  Standard_EXPORT Geom2dConvert_ApproxCurve(const occ::handle<Geom2d_Curve>& Curve,
                                            const double                     Tol2d,
                                            const GeomAbs_Shape              Order,
                                            const int                        MaxSegments,
                                            const int                        MaxDegree);

  //! Constructs an approximation framework defined by
  //! -   the 2D conic Curve
  //! -   the tolerance value Tol2d
  //! -   the degree of continuity Order
  //! -   the maximum number of segments allowed MaxSegments
  //! -   the highest degree MaxDegree which the
  //! polynomial defining the BSpline is allowed to have.
  Standard_EXPORT Geom2dConvert_ApproxCurve(const occ::handle<Adaptor2d_Curve2d>& Curve,
                                            const double                          Tol2d,
                                            const GeomAbs_Shape                   Order,
                                            const int                             MaxSegments,
                                            const int                             MaxDegree);

  //! Returns the 2D BSpline curve resulting from the
  //! approximation algorithm.
  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve() const;

  //! returns true if the approximation has
  //! been done with within required tolerance
  Standard_EXPORT bool IsDone() const;

  //! returns true if the approximation did come out
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
  Standard_EXPORT void Approximate(const occ::handle<Adaptor2d_Curve2d>& theCurve,
                                   const double                          theTol3d,
                                   const GeomAbs_Shape                   theOrder,
                                   const int                             theMaxSegments,
                                   const int                             theMaxDegree);

  bool                             myIsDone;
  bool                             myHasResult;
  occ::handle<Geom2d_BSplineCurve> myBSplCurve;
  double                           myMaxError;
};

