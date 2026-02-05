#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_PointStyle;
class StepVisual_CurveStyle;
class StepVisual_NullStyleMember;
class StepVisual_SurfaceStyleUsage;

class StepVisual_PresentationStyleSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a PresentationStyleSelect SelectType
  Standard_EXPORT StepVisual_PresentationStyleSelect();

  //! Recognizes a PresentationStyleSelect Kind Entity that is :
  //! 1 -> PointStyle
  //! 2 -> CurveStyle
  //! 3 -> SurfaceStyleUsage
  //! 4 -> SymbolStyle
  //! 5 -> FillAreaStyle
  //! 6 -> TextStyle
  //! 7 -> NullStyle
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a PointStyle (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PointStyle> PointStyle() const;

  //! returns Value as a CurveStyle (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_CurveStyle> CurveStyle() const;

  //! returns Value as a NullStyleMember (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_NullStyleMember> NullStyle() const;

  //! returns Value as a SurfaceStyleUsage (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleUsage> SurfaceStyleUsage() const;
};
