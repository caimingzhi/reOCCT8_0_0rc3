

#include <StepShape_CsgSolid.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_CsgSolid, StepShape_SolidModel)

StepShape_CsgSolid::StepShape_CsgSolid() = default;

void StepShape_CsgSolid::Init(const occ::handle<TCollection_HAsciiString>& aName,
                              const StepShape_CsgSelect&                   aTreeRootExpression)
{

  treeRootExpression = aTreeRootExpression;

  StepRepr_RepresentationItem::Init(aName);
}

void StepShape_CsgSolid::SetTreeRootExpression(const StepShape_CsgSelect& aTreeRootExpression)
{
  treeRootExpression = aTreeRootExpression;
}

StepShape_CsgSelect StepShape_CsgSolid::TreeRootExpression() const
{
  return treeRootExpression;
}
