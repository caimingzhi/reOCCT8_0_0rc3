

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWFacetedBrepAndBrepWithVoids.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_FacetedBrep.hpp>
#include <StepShape_FacetedBrepAndBrepWithVoids.hpp>
#include <StepShape_OrientedClosedShell.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWFacetedBrepAndBrepWithVoids::RWStepShape_RWFacetedBrepAndBrepWithVoids() = default;

void RWStepShape_RWFacetedBrepAndBrepWithVoids::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num0,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepShape_FacetedBrepAndBrepWithVoids>& ent) const
{

  int num = num0;

  if (!data->CheckNbParams(num, 1, ach, "brep_with_voids"))
    return;

  occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>> aVoids;
  occ::handle<StepShape_OrientedClosedShell>                                   anent;
  int                                                                          nsub1;
  if (data->ReadSubList(num, 1, "voids", ach, nsub1))
  {
    int nb1 = data->NbParams(nsub1);
    aVoids  = new NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {

      if (data->ReadEntity(nsub1,
                           i1,
                           "oriented_closed_shell",
                           ach,
                           STANDARD_TYPE(StepShape_OrientedClosedShell),
                           anent))
        aVoids->SetValue(i1, anent);
    }
  }

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "faceted_brep"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "geometric_representation_item"))
    return;

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "manifold_solid_brep"))
    return;

  occ::handle<StepShape_ClosedShell> aOuter;

  data->ReadEntity(num, 1, "outer", ach, STANDARD_TYPE(StepShape_ClosedShell), aOuter);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 1, ach, "representation_item"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  num = data->NextForComplex(num);

  if (!data->CheckNbParams(num, 0, ach, "solid_model"))
    return;

  ent->Init(aName, aOuter, aVoids);
}

void RWStepShape_RWFacetedBrepAndBrepWithVoids::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepShape_FacetedBrepAndBrepWithVoids>& ent) const
{

  SW.StartEntity("BREP_WITH_VOIDS");

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->NbVoids(); i1++)
  {
    SW.Send(ent->VoidsValue(i1));
  }
  SW.CloseSub();

  SW.StartEntity("FACETED_BREP");

  SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");

  SW.StartEntity("MANIFOLD_SOLID_BREP");

  SW.Send(ent->Outer());

  SW.StartEntity("REPRESENTATION_ITEM");

  SW.Send(ent->Name());

  SW.StartEntity("SOLID_MODEL");
}

void RWStepShape_RWFacetedBrepAndBrepWithVoids::Share(
  const occ::handle<StepShape_FacetedBrepAndBrepWithVoids>& ent,
  Interface_EntityIterator&                                 iter) const
{

  iter.GetOneItem(ent->Outer());

  int nbElem2 = ent->NbVoids();
  for (int is2 = 1; is2 <= nbElem2; is2++)
  {
    iter.GetOneItem(ent->VoidsValue(is2));
  }
}
