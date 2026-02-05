#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepData_SelectType.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class StepVisual_AnnotationText;
class StepVisual_CompositeText;
class StepVisual_TextLiteral;

class StepVisual_TextOrCharacter : public StepData_SelectType
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns a TextOrCharacter SelectType
  Standard_EXPORT StepVisual_TextOrCharacter();

  //! Recognizes a TextOrCharacter Kind Entity that is :
  //! 1 -> AnnotationText
  //! 2 -> CompositeText
  //! 3 -> TextLiteral
  //! 0 else
  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  //! returns Value as a AnnotationText (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_AnnotationText> AnnotationText() const;

  //! returns Value as a CompositeText (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_CompositeText> CompositeText() const;

  //! returns Value as a TextLiteral (Null if another type)
  Standard_EXPORT occ::handle<StepVisual_TextLiteral> TextLiteral() const;
};
