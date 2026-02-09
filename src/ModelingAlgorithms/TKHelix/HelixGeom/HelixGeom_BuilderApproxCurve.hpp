#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Real.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_Curve.hpp>
#include <NCollection_Sequence.hpp>

class HelixGeom_BuilderApproxCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT void SetApproxParameters(const GeomAbs_Shape aCont,
                                           const int           aMaxDegree,
                                           const int           aMaxSeg);

  Standard_EXPORT void ApproxParameters(GeomAbs_Shape& aCont, int& aMaxDegree, int& aMaxSeg) const;

  Standard_EXPORT void SetTolerance(const double aTolerance);

  Standard_EXPORT double Tolerance() const;

  Standard_EXPORT double ToleranceReached() const;

  Standard_EXPORT const NCollection_Sequence<occ::handle<Geom_Curve>>& Curves() const;

  Standard_EXPORT int ErrorStatus() const;

  Standard_EXPORT int WarningStatus() const;

  Standard_EXPORT virtual void Perform() = 0;

protected:
  Standard_EXPORT HelixGeom_BuilderApproxCurve();
  Standard_EXPORT virtual ~HelixGeom_BuilderApproxCurve();

  int                                           myErrorStatus;
  int                                           myWarningStatus;
  double                                        myTolerance;
  GeomAbs_Shape                                 myCont;
  int                                           myMaxDegree;
  int                                           myMaxSeg;
  double                                        myTolReached;
  NCollection_Sequence<occ::handle<Geom_Curve>> myCurves;
};
