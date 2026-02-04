#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepDimTol_GeometricTolerance;
class StepShape_PlusMinusTolerance;

//! Representation of STEP SELECT type ShapeToleranceSelect
class StepDimTol_ShapeToleranceSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepDimTol_ShapeToleranceSelect();

  //! Recognizes a kind of ShapeToleranceSelect select type
  //! 1 -> GeometricTolerance from StepDimTol
  //! 2 -> PlusMinusTolerance from StepShape
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as GeometricTolerance (or Null if another type)
  Standard_EXPORT occ::handle<StepDimTol_GeometricTolerance> GeometricTolerance() const;

  //! Returns Value as PlusMinusTolerance (or Null if another type)
  Standard_EXPORT occ::handle<StepShape_PlusMinusTolerance> PlusMinusTolerance() const;
};

