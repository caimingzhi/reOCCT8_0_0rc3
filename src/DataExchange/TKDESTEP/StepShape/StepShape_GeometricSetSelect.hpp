#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Point;
class StepGeom_Curve;
class StepGeom_Surface;

class StepShape_GeometricSetSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_GeometricSetSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepGeom_Point> Point() const;

  Standard_EXPORT occ::handle<StepGeom_Curve> Curve() const;

  Standard_EXPORT occ::handle<StepGeom_Surface> Surface() const;
};
