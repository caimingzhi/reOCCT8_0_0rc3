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

  //! Returns a CurveStyleFontSelect SelectType
  Standard_EXPORT StepVisual_CurveStyleFontSelect();

  //! Recognizes a CurveStyleFontSelect Kind Entity that is :
  //! 1 -> CurveStyleFont
  //! 2 -> PreDefinedCurveFont
  //! 3 -> ExternallyDefinedCurveFont
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a CurveStyleFont (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_CurveStyleFont> CurveStyleFont() const;

  //! returns Value as a PreDefinedCurveFont (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PreDefinedCurveFont> PreDefinedCurveFont() const;

  //! returns Value as a ExternallyDefinedCurveFont (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_ExternallyDefinedCurveFont> ExternallyDefinedCurveFont()
    const;
};
