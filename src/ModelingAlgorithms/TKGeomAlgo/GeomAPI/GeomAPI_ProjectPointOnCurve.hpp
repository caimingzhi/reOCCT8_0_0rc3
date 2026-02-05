#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Extrema_ExtPC.hpp>
#include <GeomAdaptor_Curve.hpp>
class gp_Pnt;
class Geom_Curve;

//! This class implements methods for computing all the orthogonal
//! projections of a 3D point onto a 3D curve.
class GeomAPI_ProjectPointOnCurve
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an empty object. Use an
  //! Init function for further initialization.
  Standard_EXPORT GeomAPI_ProjectPointOnCurve();

  //! Create the projection of a point <P> on a curve
  //! <Curve>
  Standard_EXPORT GeomAPI_ProjectPointOnCurve(const gp_Pnt&                  P,
                                              const occ::handle<Geom_Curve>& Curve);

  //! Create the projection of a point <P> on a curve
  //! <Curve> limited by the two points of parameter Umin and Usup.
  Standard_EXPORT GeomAPI_ProjectPointOnCurve(const gp_Pnt&                  P,
                                              const occ::handle<Geom_Curve>& Curve,
                                              const double                   Umin,
                                              const double                   Usup);

  //! Init the projection of a point <P> on a curve
  //! <Curve>
  Standard_EXPORT void Init(const gp_Pnt& P, const occ::handle<Geom_Curve>& Curve);

  //! Init the projection of a point <P> on a curve
  //! <Curve> limited by the two points of parameter Umin and Usup.
  Standard_EXPORT void Init(const gp_Pnt&                  P,
                            const occ::handle<Geom_Curve>& Curve,
                            const double                   Umin,
                            const double                   Usup);

  //! Init the projection of a point <P> on a curve
  //! <Curve> limited by the two points of parameter Umin and Usup.
  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& Curve,
                            const double                   Umin,
                            const double                   Usup);

  //! Performs the projection of a point on the current curve.
  Standard_EXPORT void Perform(const gp_Pnt& P);

  //! Returns the number of computed
  //! orthogonal projection points.
  //! Note: if this algorithm fails, NbPoints returns 0.
  Standard_EXPORT int NbPoints() const;
  Standard_EXPORT     operator int() const;

  //! Returns the orthogonal projection
  //! on the curve. Index is a number of a computed point.
  //! Exceptions
  //! Standard_OutOfRange if Index is not in the range [ 1,NbPoints ], where
  //! NbPoints is the number of solution points.
  Standard_EXPORT gp_Pnt Point(const int Index) const;

  //! Returns the parameter on the curve
  //! of the point, which is the orthogonal projection. Index is a
  //! number of a computed point.
  //! Exceptions
  //! Standard_OutOfRange if Index is not in the range [ 1,NbPoints ], where
  //! NbPoints is the number of solution points.
  Standard_EXPORT double Parameter(const int Index) const;

  //! Returns the parameter on the curve
  //! of the point, which is the orthogonal projection. Index is a
  //! number of a computed point.
  //! Exceptions
  //! Standard_OutOfRange if Index is not in the range [ 1,NbPoints ], where
  //! NbPoints is the number of solution points.-
  Standard_EXPORT void Parameter(const int Index, double& U) const;

  //! Computes the distance between the
  //! point and its orthogonal projection on the curve. Index is a number of a computed point.
  //! Exceptions
  //! Standard_OutOfRange if Index is not in the range [ 1,NbPoints ], where
  //! NbPoints is the number of solution points.
  Standard_EXPORT double Distance(const int Index) const;

  //! Returns the nearest orthogonal
  //! projection of the point on the curve.
  //! Exceptions: StdFail_NotDone if this algorithm fails.
  Standard_EXPORT gp_Pnt NearestPoint() const;
  Standard_EXPORT        operator gp_Pnt() const;

  //! Returns the parameter on the curve
  //! of the nearest orthogonal projection of the point.
  //! Exceptions: StdFail_NotDone if this algorithm fails.
  Standard_EXPORT double LowerDistanceParameter() const;

  //! Computes the distance between the
  //! point and its nearest orthogonal projection on the curve.
  //! Exceptions: StdFail_NotDone if this algorithm fails.
  Standard_EXPORT double LowerDistance() const;
  Standard_EXPORT        operator double() const;

  //! return the algorithmic object from Extrema
  const Extrema_ExtPC& Extrema() const;

private:
  bool              myIsDone;
  int               myIndex;
  Extrema_ExtPC     myExtPC;
  GeomAdaptor_Curve myC;
};

inline const Extrema_ExtPC& GeomAPI_ProjectPointOnCurve::Extrema() const
{
  return myExtPC;
}
