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

  Standard_EXPORT StepGeom_Axis2Placement();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepGeom_Axis2Placement2d> Axis2Placement2d() const;

  Standard_EXPORT occ::handle<StepGeom_Axis2Placement3d> Axis2Placement3d() const;
};
