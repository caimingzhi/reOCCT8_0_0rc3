#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>

class Standard_Transient;
class StepVisual_SurfaceStyleReflectanceAmbient;
class StepVisual_SurfaceStyleTransparent;

//! Representation of STEP SELECT type RenderingPropertiesSelect
class StepVisual_RenderingPropertiesSelect : public StepData_SelectType
{

public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT StepVisual_RenderingPropertiesSelect();

  //! Recognizes a kind of RenderingPropertiesSelect select type
  //! -- 1 -> SurfaceStyleReflectanceAmbient
  //! -- 2 -> SurfaceStyleTransparent
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! Returns Value as SurfaceStyleReflectanceAmbient (or Null if another type)
  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleReflectanceAmbient>
                  SurfaceStyleReflectanceAmbient() const;

  //! Returns Value as SurfaceStyleTransparent (or Null if another type)
  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleTransparent> SurfaceStyleTransparent() const;
};
