#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Geom_BSplineCurve.hpp>

class gp_Vec;

class GeomAPI_Interpolate
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomAPI_Interpolate(const occ::handle<NCollection_HArray1<gp_Pnt>>& Points,
                                      const bool                                      PeriodicFlag,
                                      const double                                    Tolerance);

  Standard_EXPORT GeomAPI_Interpolate(const occ::handle<NCollection_HArray1<gp_Pnt>>& Points,
                                      const occ::handle<NCollection_HArray1<double>>& Parameters,
                                      const bool                                      PeriodicFlag,
                                      const double                                    Tolerance);

  Standard_EXPORT void Load(const gp_Vec& InitialTangent,
                            const gp_Vec& FinalTangent,
                            const bool    Scale = true);

  Standard_EXPORT void Load(const NCollection_Array1<gp_Vec>&             Tangents,
                            const occ::handle<NCollection_HArray1<bool>>& TangentFlags,
                            const bool                                    Scale = true);

  Standard_EXPORT void ClearTangents();

  Standard_EXPORT void Perform();

  Standard_EXPORT const occ::handle<Geom_BSplineCurve>& Curve() const;
  Standard_EXPORT operator occ::handle<Geom_BSplineCurve>() const;

  Standard_EXPORT bool IsDone() const;

private:
  Standard_EXPORT void PerformNonPeriodic();

  Standard_EXPORT void PerformPeriodic();

  double                                   myTolerance;
  occ::handle<NCollection_HArray1<gp_Pnt>> myPoints;
  bool                                     myIsDone;
  occ::handle<Geom_BSplineCurve>           myCurve;
  occ::handle<NCollection_HArray1<gp_Vec>> myTangents;
  occ::handle<NCollection_HArray1<bool>>   myTangentFlags;
  occ::handle<NCollection_HArray1<double>> myParameters;
  bool                                     myPeriodic;
  bool                                     myTangentRequest;
};
