#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWExternallyDefinedCurveFont.hpp"
#include <StepBasic_ExternalSource.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_ExternallyDefinedCurveFont.hpp>

//=================================================================================================

RWStepVisual_RWExternallyDefinedCurveFont::RWStepVisual_RWExternallyDefinedCurveFont() = default;

//=================================================================================================

void RWStepVisual_RWExternallyDefinedCurveFont::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepVisual_ExternallyDefinedCurveFont>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "externally_defined_curve_font"))
    return;

  // Inherited fields of ExternallyDefinedItem

  StepBasic_SourceItem aExternallyDefinedItem_ItemId;
  data->ReadEntity(num, 1, "externally_defined_item.item_id", ach, aExternallyDefinedItem_ItemId);

  occ::handle<StepBasic_ExternalSource> aExternallyDefinedItem_Source;
  data->ReadEntity(num,
                   2,
                   "externally_defined_item.source",
                   ach,
                   STANDARD_TYPE(StepBasic_ExternalSource),
                   aExternallyDefinedItem_Source);

  // Initialize entity
  ent->Init(aExternallyDefinedItem_ItemId, aExternallyDefinedItem_Source);
}

//=================================================================================================

void RWStepVisual_RWExternallyDefinedCurveFont::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepVisual_ExternallyDefinedCurveFont>& ent) const
{

  // Inherited fields of ExternallyDefinedItem

  SW.Send(ent->StepBasic_ExternallyDefinedItem::ItemId().Value());

  SW.Send(ent->StepBasic_ExternallyDefinedItem::Source());
}

//=================================================================================================

void RWStepVisual_RWExternallyDefinedCurveFont::Share(
  const occ::handle<StepVisual_ExternallyDefinedCurveFont>& ent,
  Interface_EntityIterator&                                 iter) const
{

  // Inherited fields of ExternallyDefinedItem

  iter.AddItem(ent->StepBasic_ExternallyDefinedItem::ItemId().Value());

  iter.AddItem(ent->StepBasic_ExternallyDefinedItem::Source());
}
