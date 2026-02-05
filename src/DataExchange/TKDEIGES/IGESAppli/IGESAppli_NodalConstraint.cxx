#include <IGESAppli_NodalConstraint.hpp>
#include <IGESAppli_Node.hpp>
#include <IGESDefs_TabularData.hpp>
#include <Standard_DimensionMismatch.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESAppli_NodalConstraint, IGESData_IGESEntity)

IGESAppli_NodalConstraint::IGESAppli_NodalConstraint() = default;

void IGESAppli_NodalConstraint::Init(
  const int                                                                  aType,
  const occ::handle<IGESAppli_Node>&                                         aNode,
  const occ::handle<NCollection_HArray1<occ::handle<IGESDefs_TabularData>>>& allTabData)
{
  if (allTabData->Lower() != 1)
    throw Standard_DimensionMismatch("IGESAppli_NodalConstraint : Init");
  theType             = aType;
  theNode             = aNode;
  theTabularDataProps = allTabData;
  InitTypeAndForm(418, 0);
}

int IGESAppli_NodalConstraint::NbCases() const
{
  return theTabularDataProps->Length();
}

int IGESAppli_NodalConstraint::Type() const
{
  return theType;
}

occ::handle<IGESAppli_Node> IGESAppli_NodalConstraint::NodeEntity() const
{
  return theNode;
}

occ::handle<IGESDefs_TabularData> IGESAppli_NodalConstraint::TabularData(const int Index) const
{
  return theTabularDataProps->Value(Index);
}
