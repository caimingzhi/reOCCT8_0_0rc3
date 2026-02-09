

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWBooleanResult.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_BooleanResult.hpp>
#include <StepShape_SolidModel.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepShape_RWBooleanOperator.hpp"

RWStepShape_RWBooleanResult::RWStepShape_RWBooleanResult() = default;

void RWStepShape_RWBooleanResult::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                           const int                                   num,
                                           occ::handle<Interface_Check>&               ach,
                                           const occ::handle<StepShape_BooleanResult>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "boolean_result"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepShape_BooleanOperator aOperator = StepShape_boDifference;
  if (data->ParamType(num, 2) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 2);
    if (!RWStepShape_RWBooleanOperator::ConvertToEnum(text, aOperator))
    {
      ach->AddFail("Enumeration boolean_operator has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #2 (operator) is not an enumeration");

  occ::handle<StepShape_SolidModel> aSolidModel1;

  data->ReadEntity(num, 3, "first_operand", ach, STANDARD_TYPE(StepShape_SolidModel), aSolidModel1);
  StepShape_BooleanOperand aFirstOperand;
  aFirstOperand.SetSolidModel(aSolidModel1);

  occ::handle<StepShape_SolidModel> aSolidModel2;

  data
    ->ReadEntity(num, 4, "second_operand", ach, STANDARD_TYPE(StepShape_SolidModel), aSolidModel2);

  StepShape_BooleanOperand aSecondOperand;
  aSecondOperand.SetSolidModel(aSolidModel2);

  ent->Init(aName, aOperator, aFirstOperand, aSecondOperand);
}

void RWStepShape_RWBooleanResult::WriteStep(StepData_StepWriter&                        SW,
                                            const occ::handle<StepShape_BooleanResult>& ent) const
{

  SW.Send(ent->Name());

  SW.SendEnum(RWStepShape_RWBooleanOperator::ConvertToString(ent->Operator()));

  SW.Send(ent->FirstOperand().SolidModel());

  SW.Send(ent->SecondOperand().SolidModel());
}

void RWStepShape_RWBooleanResult::Share(const occ::handle<StepShape_BooleanResult>& ent,
                                        Interface_EntityIterator&                   iter) const
{

  iter.GetOneItem(ent->FirstOperand().SolidModel());

  iter.GetOneItem(ent->SecondOperand().SolidModel());
}
