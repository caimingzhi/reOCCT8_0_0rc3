#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_PreDefinedTextFont;
class StepVisual_ExternallyDefinedTextFont;

class StepVisual_FontSelect : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a FontSelect SelectType
  Standard_EXPORT StepVisual_FontSelect();

  //! Recognizes a FontSelect Kind Entity that is :
  //! 1 -> PreDefinedTextFont
  //! 2 -> ExternallyDefinedTextFont
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a PreDefinedTextFont (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_PreDefinedTextFont> PreDefinedTextFont() const;

  //! returns Value as a ExternallyDefinedTextFont (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_ExternallyDefinedTextFont> ExternallyDefinedTextFont()
    const;
};

