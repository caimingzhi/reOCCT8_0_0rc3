

#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ProductContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductContext, StepBasic_ApplicationContextElement)

StepBasic_ProductContext::StepBasic_ProductContext() = default;

void StepBasic_ProductContext::Init(
  const occ::handle<TCollection_HAsciiString>&     aName,
  const occ::handle<StepBasic_ApplicationContext>& aFrameOfReference,
  const occ::handle<TCollection_HAsciiString>&     aDisciplineType)
{

  disciplineType = aDisciplineType;

  StepBasic_ApplicationContextElement::Init(aName, aFrameOfReference);
}

void StepBasic_ProductContext::SetDisciplineType(
  const occ::handle<TCollection_HAsciiString>& aDisciplineType)
{
  disciplineType = aDisciplineType;
}

occ::handle<TCollection_HAsciiString> StepBasic_ProductContext::DisciplineType() const
{
  return disciplineType;
}
