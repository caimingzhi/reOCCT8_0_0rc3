#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_SurfaceStyleFillArea;
class StepVisual_SurfaceStyleBoundary;
class StepVisual_SurfaceStyleParameterLine;
class StepVisual_SurfaceStyleRendering;

class StepVisual_SurfaceStyleElementSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_SurfaceStyleElementSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleFillArea> SurfaceStyleFillArea() const;

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleBoundary> SurfaceStyleBoundary() const;

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleParameterLine> SurfaceStyleParameterLine()
    const;

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleRendering> SurfaceStyleRendering() const;
};
