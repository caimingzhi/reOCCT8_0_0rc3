#include <StepFEA_ElementGroup.hpp>
#include <StepFEA_FeaModel.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_ElementGroup, StepFEA_FeaGroup)

StepFEA_ElementGroup::StepFEA_ElementGroup() = default;

void StepFEA_ElementGroup::Init(
  const occ::handle<TCollection_HAsciiString>& aGroup_Name,
  const occ::handle<TCollection_HAsciiString>& aGroup_Description,
  const occ::handle<StepFEA_FeaModel>&         aFeaGroup_ModelRef,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>>& aElements)
{
  StepFEA_FeaGroup::Init(aGroup_Name, aGroup_Description, aFeaGroup_ModelRef);

  theElements = aElements;
}

occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>> StepFEA_ElementGroup::
  Elements() const
{
  return theElements;
}

void StepFEA_ElementGroup::SetElements(
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_ElementRepresentation>>>& aElements)
{
  theElements = aElements;
}
