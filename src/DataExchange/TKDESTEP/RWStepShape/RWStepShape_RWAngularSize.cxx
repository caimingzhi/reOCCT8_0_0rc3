#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWAngularSize.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_ShapeAspect.hpp>
#include <StepShape_AngularSize.hpp>

RWStepShape_RWAngularSize::RWStepShape_RWAngularSize() = default;

void RWStepShape_RWAngularSize::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepShape_AngularSize>&   ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "angular_size"))
    return;

  occ::handle<StepRepr_ShapeAspect> aDimensionalSize_AppliesTo;
  data->ReadEntity(num,
                   1,
                   "dimensional_size.applies_to",
                   ach,
                   STANDARD_TYPE(StepRepr_ShapeAspect),
                   aDimensionalSize_AppliesTo);

  occ::handle<TCollection_HAsciiString> aDimensionalSize_Name;
  data->ReadString(num, 2, "dimensional_size.name", ach, aDimensionalSize_Name);

  StepShape_AngleRelator aAngleSelection = StepShape_Small;
  if (data->ParamType(num, 3) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 3);
    if (strcmp(text, ".EQUAL.") == 0)
      aAngleSelection = StepShape_Equal;
    else if (strcmp(text, ".LARGE.") == 0)
      aAngleSelection = StepShape_Large;
    else if (strcmp(text, ".SMALL.") == 0)
      aAngleSelection = StepShape_Small;
    else
      ach->AddFail("Parameter #3 (angle_selection) has not allowed value");
  }
  else
    ach->AddFail("Parameter #3 (angle_selection) is not enumeration");

  ent->Init(aDimensionalSize_AppliesTo, aDimensionalSize_Name, aAngleSelection);
}

void RWStepShape_RWAngularSize::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepShape_AngularSize>& ent) const
{

  SW.Send(ent->StepShape_DimensionalSize::AppliesTo());

  SW.Send(ent->StepShape_DimensionalSize::Name());

  switch (ent->AngleSelection())
  {
    case StepShape_Equal:
      SW.SendEnum(".EQUAL.");
      break;
    case StepShape_Large:
      SW.SendEnum(".LARGE.");
      break;
    case StepShape_Small:
      SW.SendEnum(".SMALL.");
      break;
  }
}

void RWStepShape_RWAngularSize::Share(const occ::handle<StepShape_AngularSize>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.AddItem(ent->StepShape_DimensionalSize::AppliesTo());
}
