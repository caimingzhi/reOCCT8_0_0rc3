#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepFEA_FeaAxis2Placement3d;
class StepFEA_AlignedCurve3dElementCoordinateSystem;
class StepFEA_ParametricCurve3dElementCoordinateSystem;

class StepFEA_CurveElementEndCoordinateSystem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepFEA_CurveElementEndCoordinateSystem();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepFEA_FeaAxis2Placement3d> FeaAxis2Placement3d() const;

  Standard_EXPORT occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem>
                  AlignedCurve3dElementCoordinateSystem() const;

  Standard_EXPORT occ::handle<StepFEA_ParametricCurve3dElementCoordinateSystem>
                  ParametricCurve3dElementCoordinateSystem() const;
};
