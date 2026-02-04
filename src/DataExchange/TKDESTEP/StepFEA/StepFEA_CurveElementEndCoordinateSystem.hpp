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

//! Representation of STEP SELECT type CurveElementEndCoordinateSystem
class StepFEA_CurveElementEndCoordinateSystem : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepFEA_CurveElementEndCoordinateSystem();

  //! Recognizes a kind of CurveElementEndCoordinateSystem select type
  //! 1 -> FeaAxis2Placement3d from StepFEA
  //! 2 -> AlignedCurve3dElementCoordinateSystem from StepFEA
  //! 3 -> ParametricCurve3dElementCoordinateSystem from StepFEA
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as FeaAxis2Placement3d (or Null if another type)
  Standard_EXPORT occ::handle<StepFEA_FeaAxis2Placement3d> FeaAxis2Placement3d() const;

  //! Returns Value as AlignedCurve3dElementCoordinateSystem (or Null if another type)
  Standard_EXPORT occ::handle<StepFEA_AlignedCurve3dElementCoordinateSystem>
                  AlignedCurve3dElementCoordinateSystem() const;

  //! Returns Value as ParametricCurve3dElementCoordinateSystem (or Null if another type)
  Standard_EXPORT occ::handle<StepFEA_ParametricCurve3dElementCoordinateSystem>
                  ParametricCurve3dElementCoordinateSystem() const;
};

