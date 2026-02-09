#pragma once

#include <Standard.hpp>

#include <StepShape_BooleanOperator.hpp>
#include <StepShape_BooleanOperand.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
class TCollection_HAsciiString;

class StepShape_BooleanResult : public StepGeom_GeometricRepresentationItem
{

public:
  Standard_EXPORT StepShape_BooleanResult();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const StepShape_BooleanOperator              aOperator,
                            const StepShape_BooleanOperand&              aFirstOperand,
                            const StepShape_BooleanOperand&              aSecondOperand);

  Standard_EXPORT void SetOperator(const StepShape_BooleanOperator aOperator);

  Standard_EXPORT StepShape_BooleanOperator Operator() const;

  Standard_EXPORT void SetFirstOperand(const StepShape_BooleanOperand& aFirstOperand);

  Standard_EXPORT StepShape_BooleanOperand FirstOperand() const;

  Standard_EXPORT void SetSecondOperand(const StepShape_BooleanOperand& aSecondOperand);

  Standard_EXPORT StepShape_BooleanOperand SecondOperand() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_BooleanResult, StepGeom_GeometricRepresentationItem)

private:
  StepShape_BooleanOperator anOperator;
  StepShape_BooleanOperand  firstOperand;
  StepShape_BooleanOperand  secondOperand;
};
