

#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <StepVisual_AnnotationText.hpp>
#include <StepVisual_CompositeText.hpp>
#include <StepVisual_TextLiteral.hpp>
#include <StepVisual_TextOrCharacter.hpp>

StepVisual_TextOrCharacter::StepVisual_TextOrCharacter() = default;

int StepVisual_TextOrCharacter::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_AnnotationText)))
    return 1;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_CompositeText)))
    return 2;
  if (ent->IsKind(STANDARD_TYPE(StepVisual_TextLiteral)))
    return 3;
  return 0;
}

occ::handle<StepVisual_AnnotationText> StepVisual_TextOrCharacter::AnnotationText() const
{
  return GetCasted(StepVisual_AnnotationText, Value());
}

occ::handle<StepVisual_CompositeText> StepVisual_TextOrCharacter::CompositeText() const
{
  return GetCasted(StepVisual_CompositeText, Value());
}

occ::handle<StepVisual_TextLiteral> StepVisual_TextOrCharacter::TextLiteral() const
{
  return GetCasted(StepVisual_TextLiteral, Value());
}
