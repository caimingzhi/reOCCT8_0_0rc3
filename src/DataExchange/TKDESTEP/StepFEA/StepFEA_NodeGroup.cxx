#include <StepFEA_FeaModel.hpp>
#include <StepFEA_NodeGroup.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_NodeGroup, StepFEA_FeaGroup)

//=================================================================================================

StepFEA_NodeGroup::StepFEA_NodeGroup() = default;

//=================================================================================================

void StepFEA_NodeGroup::Init(
  const occ::handle<TCollection_HAsciiString>& aGroup_Name,
  const occ::handle<TCollection_HAsciiString>& aGroup_Description,
  const occ::handle<StepFEA_FeaModel>&         aFeaGroup_ModelRef,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodes)
{
  StepFEA_FeaGroup::Init(aGroup_Name, aGroup_Description, aFeaGroup_ModelRef);

  theNodes = aNodes;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> StepFEA_NodeGroup::Nodes()
  const
{
  return theNodes;
}

//=================================================================================================

void StepFEA_NodeGroup::SetNodes(
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodes)
{
  theNodes = aNodes;
}
