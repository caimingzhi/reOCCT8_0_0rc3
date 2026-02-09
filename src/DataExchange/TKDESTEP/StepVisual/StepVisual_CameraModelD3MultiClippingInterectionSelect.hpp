#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepGeom_Plane;
class StepVisual_CameraModelD3MultiClippingUnion;

class StepVisual_CameraModelD3MultiClippingInterectionSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_CameraModelD3MultiClippingInterectionSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepGeom_Plane> Plane() const;

  Standard_EXPORT occ::handle<StepVisual_CameraModelD3MultiClippingUnion>
                  CameraModelD3MultiClippingUnion() const;
};
