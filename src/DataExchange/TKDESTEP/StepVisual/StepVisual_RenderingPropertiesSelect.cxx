// Created on : Thu May 14 15:13:19 2020

#include <StepVisual_RenderingPropertiesSelect.hpp>
#include <StepVisual_SurfaceStyleReflectanceAmbient.hpp>
#include <StepVisual_SurfaceStyleTransparent.hpp>

//=================================================================================================

StepVisual_RenderingPropertiesSelect::StepVisual_RenderingPropertiesSelect() = default;

//=================================================================================================

int StepVisual_RenderingPropertiesSelect::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_SurfaceStyleReflectanceAmbient)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_SurfaceStyleTransparent)))
    return 2;
  return 0;
}

//=================================================================================================

occ::handle<StepVisual_SurfaceStyleReflectanceAmbient> StepVisual_RenderingPropertiesSelect::
  SurfaceStyleReflectanceAmbient() const
{
  return occ::down_cast<StepVisual_SurfaceStyleReflectanceAmbient>(Value());
}

//=================================================================================================

occ::handle<StepVisual_SurfaceStyleTransparent> StepVisual_RenderingPropertiesSelect::
  SurfaceStyleTransparent() const
{
  return occ::down_cast<StepVisual_SurfaceStyleTransparent>(Value());
}
