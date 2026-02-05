#pragma once

#include <Standard.hpp>

#include <StepShape_CsgSelect.hpp>
#include <StepShape_SolidModel.hpp>
class TCollection_HAsciiString;

class StepShape_CsgSolid : public StepShape_SolidModel
{

public:
  //! Returns a CsgSolid
  Standard_EXPORT StepShape_CsgSolid();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepShape_CsgSelect&                   aTreeRootExpression);

  Standard_EXPORT void SetTreeRootExpression(const StepShape_CsgSelect& aTreeRootExpression);

  Standard_EXPORT StepShape_CsgSelect TreeRootExpression() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_CsgSolid, StepShape_SolidModel)

private:
  StepShape_CsgSelect treeRootExpression;
};
