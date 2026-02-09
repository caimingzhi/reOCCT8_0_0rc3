#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class Law_BSpline;

class Law_Interpolate
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Law_Interpolate(const occ::handle<NCollection_HArray1<double>>& Points,
                                  const bool                                      PeriodicFlag,
                                  const double                                    Tolerance);

  Standard_EXPORT Law_Interpolate(const occ::handle<NCollection_HArray1<double>>& Points,
                                  const occ::handle<NCollection_HArray1<double>>& Parameters,
                                  const bool                                      PeriodicFlag,
                                  const double                                    Tolerance);

  Standard_EXPORT void Load(const double InitialTangent, const double FinalTangent);

  Standard_EXPORT void Load(const NCollection_Array1<double>&             Tangents,
                            const occ::handle<NCollection_HArray1<bool>>& TangentFlags);

  Standard_EXPORT void ClearTangents();

  Standard_EXPORT void Perform();

  Standard_EXPORT const occ::handle<Law_BSpline>& Curve() const;

  Standard_EXPORT bool IsDone() const;

private:
  Standard_EXPORT void PerformNonPeriodic();

  Standard_EXPORT void PerformPeriodic();

  double                                   myTolerance;
  occ::handle<NCollection_HArray1<double>> myPoints;
  bool                                     myIsDone;
  occ::handle<Law_BSpline>                 myCurve;
  occ::handle<NCollection_HArray1<double>> myTangents;
  occ::handle<NCollection_HArray1<bool>>   myTangentFlags;
  occ::handle<NCollection_HArray1<double>> myParameters;
  bool                                     myPeriodic;
  bool                                     myTangentRequest;
};
