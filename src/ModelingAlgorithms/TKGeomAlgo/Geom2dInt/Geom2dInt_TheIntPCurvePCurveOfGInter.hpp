#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntRes2d_Domain.hpp>
#include <IntRes2d_Intersection.hpp>
#include <Standard_Integer.hpp>
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class Geom2dInt_TheProjPCurOfGInter;
class Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter;
class Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter;
class Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter;
class IntRes2d_Domain;

class Geom2dInt_TheIntPCurvePCurveOfGInter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dInt_TheIntPCurvePCurveOfGInter();

  Standard_EXPORT void Perform(const Adaptor2d_Curve2d& Curve1,
                               const IntRes2d_Domain&   Domain1,
                               const Adaptor2d_Curve2d& Curve2,
                               const IntRes2d_Domain&   Domain2,
                               const double             TolConf,
                               const double             Tol);

  Standard_EXPORT void Perform(const Adaptor2d_Curve2d& Curve1,
                               const IntRes2d_Domain&   Domain1,
                               const double             TolConf,
                               const double             Tol);

  //! Set / get minimum number of points in polygon for intersection.
  Standard_EXPORT void SetMinNbSamples(const int theMinNbSamples);
  Standard_EXPORT int  GetMinNbSamples() const;

protected:
  Standard_EXPORT void Perform(const Adaptor2d_Curve2d& Curve1,
                               const IntRes2d_Domain&   Domain1,
                               const Adaptor2d_Curve2d& Curve2,
                               const IntRes2d_Domain&   Domain2,
                               const double             TolConf,
                               const double             Tol,
                               const int                NbIter,
                               const double             DeltaU,
                               const double             DeltaV);

  Standard_EXPORT void Perform(const Adaptor2d_Curve2d& Curve1,
                               const IntRes2d_Domain&   Domain1,
                               const double             TolConf,
                               const double             Tol,
                               const int                NbIter,
                               const double             DeltaU,
                               const double             DeltaV);

private:
  //! Method to find intersection between two curves
  //! : returns false for case when some points of polygon
  //! : were replaced on line and exact point of intersection was not found
  //! : for case when point of intersection was found
  //! : during prelimanary search for line (case of bad parameterization of Bspline for example).
  Standard_EXPORT bool findIntersect(
    const Adaptor2d_Curve2d&                                  Curve1,
    const IntRes2d_Domain&                                    Domain1,
    const Adaptor2d_Curve2d&                                  Curve2,
    const IntRes2d_Domain&                                    Domain2,
    const double                                              TolConf,
    const double                                              Tol,
    const int                                                 NbIter,
    const double                                              DeltaU,
    const double                                              DeltaV,
    const Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter& thePoly1,
    const Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter& thePoly2,
    const bool                                                isFullRepresentation);

  IntRes2d_Domain DomainOnCurve1;
  IntRes2d_Domain DomainOnCurve2;

  //! Minimal number of sample points
  int myMinPntNb;
};
