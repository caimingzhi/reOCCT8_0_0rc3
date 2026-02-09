#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepShape_Sphere;
class StepShape_Block;
class StepShape_RightAngularWedge;
class StepShape_Torus;
class StepShape_RightCircularCone;
class StepShape_RightCircularCylinder;

class StepShape_CsgPrimitive : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepShape_CsgPrimitive();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepShape_Sphere> Sphere() const;

  Standard_EXPORT occ::handle<StepShape_Block> Block() const;

  Standard_EXPORT occ::handle<StepShape_RightAngularWedge> RightAngularWedge() const;

  Standard_EXPORT occ::handle<StepShape_Torus> Torus() const;

  Standard_EXPORT occ::handle<StepShape_RightCircularCone> RightCircularCone() const;

  Standard_EXPORT occ::handle<StepShape_RightCircularCylinder> RightCircularCylinder() const;
};
