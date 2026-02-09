#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepVisual_SurfaceStyleReflectanceAmbient;
class StepVisual_SurfaceStyleTransparent;

class StepVisual_RenderingPropertiesSelect : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_RenderingPropertiesSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleReflectanceAmbient>
                  SurfaceStyleReflectanceAmbient() const;

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleTransparent> SurfaceStyleTransparent() const;
};
