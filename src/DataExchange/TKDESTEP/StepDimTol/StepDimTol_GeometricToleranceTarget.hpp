#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepShape_DimensionalLocation;
class StepShape_DimensionalSize;
class StepRepr_ProductDefinitionShape;
class StepRepr_ShapeAspect;

class StepDimTol_GeometricToleranceTarget : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a GeometricToleranceTarget select type
  Standard_EXPORT StepDimTol_GeometricToleranceTarget();

  //! Recognizes a GeometricToleranceTarget Kind Entity that is :
  //! 1 -> DimensionalLocation
  //! 2 -> DimensionalSize
  //! 3 -> ProductDefinitionShape
  //! 4 -> ShapeAspect
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a DimensionalLocation (Null if another type)
  Standard_EXPORT occ::handle<StepShape_DimensionalLocation> DimensionalLocation() const;

  //! returns Value as a DimensionalSize (Null if another type)
  Standard_EXPORT occ::handle<StepShape_DimensionalSize> DimensionalSize() const;

  //! returns Value as a ProductDefinitionShape (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ProductDefinitionShape> ProductDefinitionShape() const;

  //! returns Value as a ShapeAspect (Null if another type)
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> ShapeAspect() const;
};
