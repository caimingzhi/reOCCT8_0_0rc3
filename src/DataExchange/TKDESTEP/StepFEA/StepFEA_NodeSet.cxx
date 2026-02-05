#include <StepFEA_NodeSet.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_NodeSet, StepGeom_GeometricRepresentationItem)

//=================================================================================================

StepFEA_NodeSet::StepFEA_NodeSet() = default;

//=================================================================================================

void StepFEA_NodeSet::Init(
  const occ::handle<TCollection_HAsciiString>& aRepresentationItem_Name,
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodes)
{
  StepGeom_GeometricRepresentationItem::Init(aRepresentationItem_Name);

  theNodes = aNodes;
}

//=================================================================================================

occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>> StepFEA_NodeSet::Nodes()
  const
{
  return theNodes;
}

//=================================================================================================

void StepFEA_NodeSet::SetNodes(
  const occ::handle<NCollection_HArray1<occ::handle<StepFEA_NodeRepresentation>>>& aNodes)
{
  theNodes = aNodes;
}
