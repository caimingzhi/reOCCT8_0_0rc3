#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Axis2Placement2d;
class StepGeom_Axis2Placement3d;

class StepGeom_Axis2Placement : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a Axis2Placement SelectType
  Standard_EXPORT StepGeom_Axis2Placement();

  //! Recognizes a Axis2Placement Kind Entity that is :
  //! 1 -> Axis2Placement2d
  //! 2 -> Axis2Placement3d
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Axis2Placement2d (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Axis2Placement2d> Axis2Placement2d() const;

  //! returns Value as a Axis2Placement3d (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> Axis2Placement3d() const;
};

