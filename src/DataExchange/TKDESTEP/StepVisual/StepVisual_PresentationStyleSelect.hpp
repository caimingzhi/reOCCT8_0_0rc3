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

  Standard_EXPORT StepVisual_PresentationStyleSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_PointStyle> PointStyle() const;

  Standard_EXPORT occ::handle<StepVisual_CurveStyle> CurveStyle() const;

  Standard_EXPORT occ::handle<StepVisual_NullStyleMember> NullStyle() const;

  Standard_EXPORT occ::handle<StepVisual_SurfaceStyleUsage> SurfaceStyleUsage() const;
};
