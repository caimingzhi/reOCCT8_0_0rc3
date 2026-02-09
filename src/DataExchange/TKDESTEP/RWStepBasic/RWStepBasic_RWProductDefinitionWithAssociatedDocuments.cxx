

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProductDefinitionWithAssociatedDocuments.hpp"
#include <StepBasic_ProductDefinitionContext.hpp>
#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionWithAssociatedDocuments.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProductDefinitionWithAssociatedDocuments::
  RWStepBasic_RWProductDefinitionWithAssociatedDocuments() = default;

void RWStepBasic_RWProductDefinitionWithAssociatedDocuments::ReadStep(
  const occ::handle<StepData_StepReaderData>&                            data,
  const int                                                              num,
  occ::handle<Interface_Check>&                                          ach,
  const occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments>& ent) const
{

  if (!data->CheckNbParams(num, 5, ach, "product_definition"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aDescription;

  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<StepBasic_ProductDefinitionFormation> aFormation;

  data->ReadEntity(num,
                   3,
                   "formation",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionFormation),
                   aFormation);

  occ::handle<StepBasic_ProductDefinitionContext> aFrameOfReference;

  data->ReadEntity(num,
                   4,
                   "frame_of_reference",
                   ach,
                   STANDARD_TYPE(StepBasic_ProductDefinitionContext),
                   aFrameOfReference);

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_Document>>> aDocIds;
  occ::handle<StepBasic_Document>                                   anent5;
  int                                                               nsub5;
  if (data->ReadSubList(num, 5, "frame_of_reference", ach, nsub5))
  {
    int nb5 = data->NbParams(nsub5);
    if (nb5 > 0)
      aDocIds = new NCollection_HArray1<occ::handle<StepBasic_Document>>(1, nb5);
    for (int i5 = 1; i5 <= nb5; i5++)
    {

      if (data->ReadEntity(nsub5,
                           i5,
                           "product_context",
                           ach,
                           STANDARD_TYPE(StepBasic_Document),
                           anent5))
        aDocIds->SetValue(i5, anent5);
    }
  }

  ent->Init(aId, aDescription, aFormation, aFrameOfReference, aDocIds);
}

void RWStepBasic_RWProductDefinitionWithAssociatedDocuments::WriteStep(
  StepData_StepWriter&                                                   SW,
  const occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments>& ent) const
{

  SW.Send(ent->Id());

  SW.Send(ent->Description());

  SW.Send(ent->Formation());

  SW.Send(ent->FrameOfReference());

  SW.OpenSub();
  int i, nb = ent->NbDocIds();
  for (i = 1; i <= nb; i++)
    SW.Send(ent->DocIdsValue(i));
  SW.CloseSub();
}

void RWStepBasic_RWProductDefinitionWithAssociatedDocuments::Share(
  const occ::handle<StepBasic_ProductDefinitionWithAssociatedDocuments>& ent,
  Interface_EntityIterator&                                              iter) const
{

  iter.GetOneItem(ent->Formation());

  iter.GetOneItem(ent->FrameOfReference());

  int i, nb = ent->NbDocIds();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->DocIdsValue(i));
}
