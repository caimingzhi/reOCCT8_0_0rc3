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

  Standard_EXPORT StepVisual_TextOrCharacter();

  Standard_EXPORT int CaseNum(const occ::handle<Standard_Transient>& ent) const override;

  Standard_EXPORT occ::handle<StepVisual_AnnotationText> AnnotationText() const;

  Standard_EXPORT occ::handle<StepVisual_CompositeText> CompositeText() const;

  Standard_EXPORT occ::handle<StepVisual_TextLiteral> TextLiteral() const;
};
