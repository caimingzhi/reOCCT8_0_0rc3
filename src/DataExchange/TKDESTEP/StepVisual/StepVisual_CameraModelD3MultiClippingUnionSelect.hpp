#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Plane;
class StepVisual_CameraModelD3MultiClippingIntersection;

class StepVisual_CameraModelD3MultiClippingUnionSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a CameraModelD3MultiClippingUnionSelect select type
  Standard_EXPORT StepVisual_CameraModelD3MultiClippingUnionSelect();

  //! Recognizes a IdAttributeSelect Kind Entity that is :
  //! 1 -> Plane
  //! 2 -> CameraModelD3MultiClippingIntersection
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a Plane (Null if another type)
  Standard_EXPORT occ::handle<StepGeom_Plane> Plane() const;

  //! returns Value as a CameraModelD3MultiClippingIntersection (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_CameraModelD3MultiClippingIntersection>
                  CameraModelD3MultiClippingIntersection() const;
};
