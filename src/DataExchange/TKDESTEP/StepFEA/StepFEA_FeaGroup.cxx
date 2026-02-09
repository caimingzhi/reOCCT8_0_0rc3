#include <StepFEA_FeaGroup.hpp>
#include <StepFEA_FeaModel.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FeaGroup, StepBasic_Group)

StepFEA_FeaGroup::StepFEA_FeaGroup() = default;

void StepFEA_FeaGroup::Init(const occ::handle<TCollection_HAsciiString>& aGroup_Name,
                            const occ::handle<TCollection_HAsciiString>& aGroup_Description,
                            const occ::handle<StepFEA_FeaModel>&         aModelRef)
{
  StepBasic_Group::Init(aGroup_Name, true, aGroup_Description);

  theModelRef = aModelRef;
}

occ::handle<StepFEA_FeaModel> StepFEA_FeaGroup::ModelRef() const
{
  return theModelRef;
}

void StepFEA_FeaGroup::SetModelRef(const occ::handle<StepFEA_FeaModel>& aModelRef)
{
  theModelRef = aModelRef;
}
