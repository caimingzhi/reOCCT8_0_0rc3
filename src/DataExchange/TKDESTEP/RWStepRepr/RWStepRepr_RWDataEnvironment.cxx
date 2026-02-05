#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepRepr_RWDataEnvironment.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_DataEnvironment.hpp>
#include <StepRepr_PropertyDefinitionRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=================================================================================================

RWStepRepr_RWDataEnvironment::RWStepRepr_RWDataEnvironment() = default;

//=================================================================================================

void RWStepRepr_RWDataEnvironment::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepRepr_DataEnvironment>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "data_environment"))
    return;

  // Own fields of DataEnvironment

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>>
      aElements;
  int sub3 = 0;
  if (data->ReadSubList(num, 3, "elements", ach, sub3))
  {
    int nb0 = data->NbParams(sub3);
    aElements =
      new NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>(1, nb0);
    int num2 = sub3;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepRepr_PropertyDefinitionRepresentation> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "property_definition_representation",
                       ach,
                       STANDARD_TYPE(StepRepr_PropertyDefinitionRepresentation),
                       anIt0);
      aElements->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aName, aDescription, aElements);
}

//=================================================================================================

void RWStepRepr_RWDataEnvironment::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepRepr_DataEnvironment>& ent) const
{

  // Own fields of DataEnvironment

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->Elements()->Length(); i2++)
  {
    occ::handle<StepRepr_PropertyDefinitionRepresentation> Var0 = ent->Elements()->Value(i2);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepRepr_RWDataEnvironment::Share(const occ::handle<StepRepr_DataEnvironment>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  // Own fields of DataEnvironment

  for (int i1 = 1; i1 <= ent->Elements()->Length(); i1++)
  {
    occ::handle<StepRepr_PropertyDefinitionRepresentation> Var0 = ent->Elements()->Value(i1);
    iter.AddItem(Var0);
  }
}
