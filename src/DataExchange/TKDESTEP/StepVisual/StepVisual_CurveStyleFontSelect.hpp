#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_CurveStyleFont;
class StepVisual_PreDefinedCurveFont;
class StepVisual_ExternallyDefinedCurveFont;

class StepVisual_CurveStyleFontSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepVisual_CurveStyleFontSelect();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_CurveStyleFont> CurveStyleFont() const;

  Standard_EXPORT occ::handle<StepVisual_PreDefinedCurveFont> PreDefinedCurveFont() const;

  Standard_EXPORT occ::handle<StepVisual_ExternallyDefinedCurveFont> ExternallyDefinedCurveFont()
    const;
};
