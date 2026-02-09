#include <IGESSolid_BooleanTree.hpp>
#include <Standard_DimensionError.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSolid_BooleanTree, IGESData_IGESEntity)

IGESSolid_BooleanTree::IGESSolid_BooleanTree() = default;

void IGESSolid_BooleanTree::Init(
  const occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& operands,
  const occ::handle<NCollection_HArray1<int>>&                              operations)
{
  if (operands->Lower() != 1 || operations->Lower() != 1
      || operands->Length() != operations->Length())
    throw Standard_DimensionError("IGESSolid_BooleanTree : Init");

  theOperations = operations;
  theOperands   = operands;
  InitTypeAndForm(180, 0);
}

int IGESSolid_BooleanTree::Length() const
{
  return theOperands->Length();
}

bool IGESSolid_BooleanTree::IsOperand(const int Index) const
{
  return (!theOperands->Value(Index).IsNull());
}

occ::handle<IGESData_IGESEntity> IGESSolid_BooleanTree::Operand(const int Index) const
{
  return theOperands->Value(Index);
}

int IGESSolid_BooleanTree::Operation(const int Index) const
{
  if (theOperands->Value(Index).IsNull())
    return theOperations->Value(Index);
  else
    return 0;
}
