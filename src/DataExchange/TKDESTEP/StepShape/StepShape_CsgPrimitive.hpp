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

  //! Returns a CsgPrimitive SelectType
  Standard_EXPORT StepShape_CsgPrimitive();

  //! Recognizes a CsgPrimitive Kind Entity that is :
  //! 1 -> Sphere
  //! 2 -> Block
  //! 3 -> RightAngularWedge
  //! 4 -> Torus
  //! 5 -> RightCircularCone
  //! 6 -> RightCircularCylinder
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Sphere (Null if another type)
  Standard_EXPORT occ::handle<StepShape_Sphere> Sphere() const;

  //! returns Value as a Block (Null if another type)
  Standard_EXPORT occ::handle<StepShape_Block> Block() const;

  //! returns Value as a RightAngularWedge (Null if another type)
  Standard_EXPORT occ::handle<StepShape_RightAngularWedge> RightAngularWedge() const;

  //! returns Value as a Torus (Null if another type)
  Standard_EXPORT occ::handle<StepShape_Torus> Torus() const;

  //! returns Value as a RightCircularCone (Null if another type)
  Standard_EXPORT occ::handle<StepShape_RightCircularCone> RightCircularCone() const;

  //! returns Value as a RightCircularCylinder (Null if another type)
  Standard_EXPORT occ::handle<StepShape_RightCircularCylinder> RightCircularCylinder() const;
};

