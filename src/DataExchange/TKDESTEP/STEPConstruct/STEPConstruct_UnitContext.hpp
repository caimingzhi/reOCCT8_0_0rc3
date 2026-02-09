#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_CString.hpp>
#include <StepData_Factors.hpp>
#include <StepBasic_SiPrefix.hpp>
class StepData_StepModel;
class StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx;
class StepRepr_GlobalUnitAssignedContext;
class StepBasic_NamedUnit;
class StepRepr_GlobalUncertaintyAssignedContext;
class StepBasic_SiUnit;

class STEPConstruct_UnitContext
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT STEPConstruct_UnitContext();

  Standard_EXPORT void Init(const double                           Tol3d,
                            const occ::handle<StepData_StepModel>& theModel,
                            const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx>
                  Value() const;

  Standard_EXPORT int ComputeFactors(
    const occ::handle<StepRepr_GlobalUnitAssignedContext>& aContext,
    const StepData_Factors&                                theLocalFactors = StepData_Factors());

  Standard_EXPORT int ComputeFactors(const occ::handle<StepBasic_NamedUnit>& aUnit,
                                     const StepData_Factors& theLocalFactors = StepData_Factors());

  Standard_EXPORT int ComputeTolerance(
    const occ::handle<StepRepr_GlobalUncertaintyAssignedContext>& aContext);

  Standard_EXPORT double LengthFactor() const;

  Standard_EXPORT double PlaneAngleFactor() const;

  Standard_EXPORT double SolidAngleFactor() const;

  Standard_EXPORT double Uncertainty() const;

  Standard_EXPORT double AreaFactor() const;

  Standard_EXPORT double VolumeFactor() const;

  Standard_EXPORT bool HasUncertainty() const;

  Standard_EXPORT bool LengthDone() const;

  Standard_EXPORT bool PlaneAngleDone() const;

  Standard_EXPORT bool SolidAngleDone() const;

  Standard_EXPORT bool AreaDone() const;

  Standard_EXPORT bool VolumeDone() const;

  Standard_EXPORT const char* StatusMessage(const int status) const;

  Standard_EXPORT static double ConvertSiPrefix(const StepBasic_SiPrefix aPrefix);

private:
  Standard_EXPORT bool SiUnitNameFactor(const occ::handle<StepBasic_SiUnit>& aSiUnit,
                                        double&                              val) const;

  bool                                                                          done;
  occ::handle<StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx> GRC;
  double                                                                        lengthFactor;
  double                                                                        planeAngleFactor;
  double                                                                        solidAngleFactor;
  double                                                                        theUncertainty;
  double                                                                        areaFactor;
  double                                                                        volumeFactor;
  bool                                                                          areaDone;
  bool                                                                          volumeDone;
  bool                                                                          lengthDone;
  bool                                                                          planeAngleDone;
  bool                                                                          solidAngleDone;
  bool                                                                          hasUncertainty;
};
