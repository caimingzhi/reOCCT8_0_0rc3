

#include <StepBasic_Document.hpp>
#include <StepBasic_DocumentUsageConstraint.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_DocumentUsageConstraint, Standard_Transient)

StepBasic_DocumentUsageConstraint::StepBasic_DocumentUsageConstraint() = default;

void StepBasic_DocumentUsageConstraint::Init(const occ::handle<StepBasic_Document>&       aSource,
                                             const occ::handle<TCollection_HAsciiString>& ase,
                                             const occ::handle<TCollection_HAsciiString>& asev)
{
  theSource = aSource;
  theSE     = ase;
  theSEV    = asev;
}

occ::handle<StepBasic_Document> StepBasic_DocumentUsageConstraint::Source() const
{
  return theSource;
}

void StepBasic_DocumentUsageConstraint::SetSource(const occ::handle<StepBasic_Document>& aSource)
{
  theSource = aSource;
}

occ::handle<TCollection_HAsciiString> StepBasic_DocumentUsageConstraint::SubjectElement() const
{
  return theSE;
}

void StepBasic_DocumentUsageConstraint::SetSubjectElement(
  const occ::handle<TCollection_HAsciiString>& ase)
{
  theSE = ase;
}

occ::handle<TCollection_HAsciiString> StepBasic_DocumentUsageConstraint::SubjectElementValue() const
{
  return theSEV;
}

void StepBasic_DocumentUsageConstraint::SetSubjectElementValue(
  const occ::handle<TCollection_HAsciiString>& asev)
{
  theSEV = asev;
}
