#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <IntRes2d_Domain.hpp>
#include <IntRes2d_Intersection.hpp>
#include <Standard_Integer.hpp>
class HLRBRep_CurveTool;
class HLRBRep_TheProjPCurOfCInter;
class HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter;
class HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter;
class HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter;
class IntRes2d_Domain;

class HLRBRep_TheIntPCurvePCurveOfCInter : public IntRes2d_Intersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_TheIntPCurvePCurveOfCInter();

  Standard_EXPORT void Perform(const HLRBRep_CurvePtr& Curve1,
                               const IntRes2d_Domain&  Domain1,
                               const HLRBRep_CurvePtr& Curve2,
                               const IntRes2d_Domain&  Domain2,
                               const double            TolConf,
                               const double            Tol);

  Standard_EXPORT void Perform(const HLRBRep_CurvePtr& Curve1,
                               const IntRes2d_Domain&  Domain1,
                               const double            TolConf,
                               const double            Tol);

  //! Set / get minimum number of points in polygon for intersection.
  Standard_EXPORT void SetMinNbSamples(const int theMinNbSamples);
  Standard_EXPORT int  GetMinNbSamples() const;

protected:
  Standard_EXPORT void Perform(const HLRBRep_CurvePtr& Curve1,
                               const IntRes2d_Domain&  Domain1,
                               const HLRBRep_CurvePtr& Curve2,
                               const IntRes2d_Domain&  Domain2,
                               const double            TolConf,
                               const double            Tol,
                               const int               NbIter,
                               const double            DeltaU,
                               const double            DeltaV);

  Standard_EXPORT void Perform(const HLRBRep_CurvePtr& Curve1,
                               const IntRes2d_Domain&  Domain1,
                               const double            TolConf,
                               const double            Tol,
                               const int               NbIter,
                               const double            DeltaU,
                               const double            DeltaV);

private:
  //! Method to find intersection between two curves
  //! : returns false for case when some points of polygon
  //! : were replaced on line and exact point of intersection was not found
  //! : for case when point of intersection was found
  //! : during prelimanary search for line (case of bad parameterization of Bspline for example).
  Standard_EXPORT bool findIntersect(
    const HLRBRep_CurvePtr&                                 Curve1,
    const IntRes2d_Domain&                                  Domain1,
    const HLRBRep_CurvePtr&                                 Curve2,
    const IntRes2d_Domain&                                  Domain2,
    const double                                            TolConf,
    const double                                            Tol,
    const int                                               NbIter,
    const double                                            DeltaU,
    const double                                            DeltaV,
    const HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter& thePoly1,
    const HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter& thePoly2,
    const bool                                              isFullRepresentation);

  IntRes2d_Domain DomainOnCurve1;
  IntRes2d_Domain DomainOnCurve2;

  //! Minimal number of sample points
  int myMinPntNb;
};
