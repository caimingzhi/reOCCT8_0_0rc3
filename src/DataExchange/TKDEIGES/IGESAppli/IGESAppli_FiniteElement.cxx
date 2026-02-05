#include <IGESAppli.hpp>
#include <IGESAppli_FiniteElement.hpp>
#include <IGESAppli_Node.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_FiniteElement, IGESData_IGESEntity)

IGESAppli_FiniteElement::IGESAppli_FiniteElement() = default;

void IGESAppli_FiniteElement::Init(
  const int                                                            aType,
  const occ::handle<NCollection_HArray1<occ::handle<IGESAppli_Node>>>& allNodes,
  const occ::handle<TCollection_HAsciiString>&                         aName)
{
  if (allNodes->Lower() != 1)
    throw Standard_DimensionMismatch("IGESAppli_FiniteElement : Init");
  theTopology = aType;
  theNodes    = allNodes;
  theName     = aName;
  InitTypeAndForm(136, 0);
}

int IGESAppli_FiniteElement::Topology() const
{
  return theTopology;
}

occ::handle<IGESAppli_Node> IGESAppli_FiniteElement::Node(const int Index) const
{
  return theNodes->Value(Index);
}

occ::handle<TCollection_HAsciiString> IGESAppli_FiniteElement::Name() const
{
  return theName;
}

int IGESAppli_FiniteElement::NbNodes() const
{
  return theNodes->Length();
}
