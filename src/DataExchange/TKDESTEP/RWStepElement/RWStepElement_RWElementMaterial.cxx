#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWElementMaterial.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_ElementMaterial.hpp>
#include <StepRepr_MaterialPropertyRepresentation.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepElement_RWElementMaterial::RWStepElement_RWElementMaterial() = default;

void RWStepElement_RWElementMaterial::ReadStep(
  const occ::handle<StepData_StepReaderData>&     data,
  const int                                       num,
  occ::handle<Interface_Check>&                   ach,
  const occ::handle<StepElement_ElementMaterial>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "element_material"))
    return;

  occ::handle<TCollection_HAsciiString> aMaterialId;
  data->ReadString(num, 1, "material_id", ach, aMaterialId);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>>
      aProperties;
  int sub3 = 0;
  if (data->ReadSubList(num, 3, "properties", ach, sub3))
  {
    int nb0 = data->NbParams(sub3);
    aProperties =
      new NCollection_HArray1<occ::handle<StepRepr_MaterialPropertyRepresentation>>(1, nb0);
    int num2 = sub3;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepRepr_MaterialPropertyRepresentation> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "material_property_representation",
                       ach,
                       STANDARD_TYPE(StepRepr_MaterialPropertyRepresentation),
                       anIt0);
      aProperties->SetValue(i0, anIt0);
    }
  }

  ent->Init(aMaterialId, aDescription, aProperties);
}

void RWStepElement_RWElementMaterial::WriteStep(
  StepData_StepWriter&                            SW,
  const occ::handle<StepElement_ElementMaterial>& ent) const
{

  SW.Send(ent->MaterialId());

  SW.Send(ent->Description());

  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->Properties()->Length(); i2++)
  {
    occ::handle<StepRepr_MaterialPropertyRepresentation> Var0 = ent->Properties()->Value(i2);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

void RWStepElement_RWElementMaterial::Share(const occ::handle<StepElement_ElementMaterial>& ent,
                                            Interface_EntityIterator& iter) const
{

  for (int i1 = 1; i1 <= ent->Properties()->Length(); i1++)
  {
    occ::handle<StepRepr_MaterialPropertyRepresentation> Var0 = ent->Properties()->Value(i1);
    iter.AddItem(Var0);
  }
}
