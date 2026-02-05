#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWElementDescriptor.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_ElementDescriptor.hpp>

//=================================================================================================

RWStepElement_RWElementDescriptor::RWStepElement_RWElementDescriptor() = default;

//=================================================================================================

void RWStepElement_RWElementDescriptor::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepElement_ElementDescriptor>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "element_descriptor"))
    return;

  // Own fields of ElementDescriptor

  StepElement_ElementOrder aTopologyOrder = StepElement_Linear;
  if (data->ParamType(num, 1) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 1);
    if (strcmp(text, ".LINEAR.") == 0)
      aTopologyOrder = StepElement_Linear;
    else if (strcmp(text, ".QUADRATIC.") == 0)
      aTopologyOrder = StepElement_Quadratic;
    else if (strcmp(text, ".CUBIC.") == 0)
      aTopologyOrder = StepElement_Cubic;
    else
      ach->AddFail("Parameter #1 (topology_order) has not allowed value");
  }
  else
    ach->AddFail("Parameter #1 (topology_order) is not enumeration");

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  // Initialize entity
  ent->Init(aTopologyOrder, aDescription);
}

//=================================================================================================

void RWStepElement_RWElementDescriptor::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepElement_ElementDescriptor>& ent) const
{

  // Own fields of ElementDescriptor

  switch (ent->TopologyOrder())
  {
    case StepElement_Linear:
      SW.SendEnum(".LINEAR.");
      break;
    case StepElement_Quadratic:
      SW.SendEnum(".QUADRATIC.");
      break;
    case StepElement_Cubic:
      SW.SendEnum(".CUBIC.");
      break;
  }

  SW.Send(ent->Description());
}

//=================================================================================================

void RWStepElement_RWElementDescriptor::Share(const occ::handle<StepElement_ElementDescriptor>&,
                                              Interface_EntityIterator&) const
{
  // Own fields of ElementDescriptor
}
