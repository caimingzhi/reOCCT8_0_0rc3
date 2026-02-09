#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Vec2d.hpp>
class Geom2d_BSplineCurve;
class gp_Vec2d;

class Geom2dAPI_Interpolate
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dAPI_Interpolate(const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Points,
                                        const bool   PeriodicFlag,
                                        const double Tolerance);

  Standard_EXPORT Geom2dAPI_Interpolate(const occ::handle<NCollection_HArray1<gp_Pnt2d>>& Points,
                                        const occ::handle<NCollection_HArray1<double>>& Parameters,
                                        const bool   PeriodicFlag,
                                        const double Tolerance);

  Standard_EXPORT void Load(const gp_Vec2d& InitialTangent,
                            const gp_Vec2d& FinalTangent,
                            const bool      Scale = true);

  Standard_EXPORT void Load(const NCollection_Array1<gp_Vec2d>&           Tangents,
                            const occ::handle<NCollection_HArray1<bool>>& TangentFlags,
                            const bool                                    Scale = true);

  Standard_EXPORT void ClearTangents();

  Standard_EXPORT void Perform();

  Standard_EXPORT const occ::handle<Geom2d_BSplineCurve>& Curve() const;
  Standard_EXPORT operator occ::handle<Geom2d_BSplineCurve>() const;

  Standard_EXPORT bool IsDone() const;

private:
  Standard_EXPORT void PerformNonPeriodic();

  Standard_EXPORT void PerformPeriodic();

  double                                     myTolerance;
  occ::handle<NCollection_HArray1<gp_Pnt2d>> myPoints;
  bool                                       myIsDone;
  occ::handle<Geom2d_BSplineCurve>           myCurve;
  occ::handle<NCollection_HArray1<gp_Vec2d>> myTangents;
  occ::handle<NCollection_HArray1<bool>>     myTangentFlags;
  occ::handle<NCollection_HArray1<double>>   myParameters;
  bool                                       myPeriodic;
  bool                                       myTangentRequest;
};
