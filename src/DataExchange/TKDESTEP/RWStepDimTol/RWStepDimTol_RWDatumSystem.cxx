#include "RWStepDimTol_RWDatumSystem.hpp"

#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepDimTol_DatumSystem.hpp>
#include <StepRepr_ProductDefinitionShape.hpp>

RWStepDimTol_RWDatumSystem::RWStepDimTol_RWDatumSystem() = default;

void RWStepDimTol_RWDatumSystem::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepDimTol_DatumSystem>&  ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "datum_system"))
    return;

  occ::handle<TCollection_HAsciiString> aShapeAspect_Name;
  data->ReadString(num, 1, "shape_aspect.name", ach, aShapeAspect_Name);

  occ::handle<TCollection_HAsciiString> aShapeAspect_Description;
  if (data->IsParamDefined(num, 2))
  {
    data->ReadString(num, 2, "shape_aspect.description", ach, aShapeAspect_Description);
  }

  occ::handle<StepRepr_ProductDefinitionShape> aShapeAspect_OfShape;
  data->ReadEntity(num,
                   3,
                   "shape_aspect.of_shape",
                   ach,
                   STANDARD_TYPE(StepRepr_ProductDefinitionShape),
                   aShapeAspect_OfShape);

  StepData_Logical aShapeAspect_ProductDefinitional;
  data->ReadLogical(num,
                    4,
                    "shape_aspect.product_definitional",
                    ach,
                    aShapeAspect_ProductDefinitional);

  occ::handle<NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>> aConstituents;
  occ::handle<StepDimTol_DatumReferenceCompartment>                                   anEnt;
  int                                                                                 nbSub;
  if (data->ReadSubList(num, 5, "base", ach, nbSub))
  {
    int nbElements = data->NbParams(nbSub);
    aConstituents =
      new NCollection_HArray1<occ::handle<StepDimTol_DatumReferenceCompartment>>(1, nbElements);
    for (int i = 1; i <= nbElements; i++)
    {
      if (data->ReadEntity(nbSub,
                           i,
                           "datum_reference_compartment",
                           ach,
                           STANDARD_TYPE(StepDimTol_DatumReferenceCompartment),
                           anEnt))
        aConstituents->SetValue(i, anEnt);
    }
  }

  ent->Init(aShapeAspect_Name,
            aShapeAspect_Description,
            aShapeAspect_OfShape,
            aShapeAspect_ProductDefinitional,
            aConstituents);
}

void RWStepDimTol_RWDatumSystem::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepDimTol_DatumSystem>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Description());

  SW.Send(ent->OfShape());

  SW.SendLogical(ent->ProductDefinitional());

  int i, nb = ent->NbConstituents();
  SW.OpenSub();
  for (i = 1; i <= nb; i++)
    SW.Send(ent->ConstituentsValue(i));
  SW.CloseSub();
}

void RWStepDimTol_RWDatumSystem::Share(const occ::handle<StepDimTol_DatumSystem>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.AddItem(ent->OfShape());

  int i, nb = ent->NbConstituents();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->ConstituentsValue(i));
}
