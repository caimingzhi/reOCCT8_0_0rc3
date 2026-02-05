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

  //! Returns a SurfaceStyleElementSelect SelectType
  Standard_EXPORT StepVisual_SurfaceStyleElementSelect();

  //! Recognizes a SurfaceStyleElementSelect Kind Entity that is :
  //! 1 -> SurfaceStyleFillArea
  //! 2 -> SurfaceStyleBoundary
  //! 3 -> SurfaceStyleParameterLine
  //! 4 -> SurfaceStyleSilhouette
  //! 5 -> SurfaceStyleSegmentationCurve
  //! 6 -> SurfaceStyleControlGrid
  //! 7 -> SurfaceStyleRendering
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a SurfaceStyleFillArea (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleFillArea> SurfaceStyleFillArea() const;

  //! returns Value as a SurfaceStyleBoundary (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleBoundary> SurfaceStyleBoundary() const;

  //! returns Value as a SurfaceStyleParameterLine (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleParameterLine> SurfaceStyleParameterLine()
    const;

  //! returns Value as a SurfaceStyleRendering (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleRendering> SurfaceStyleRendering() const;
};
