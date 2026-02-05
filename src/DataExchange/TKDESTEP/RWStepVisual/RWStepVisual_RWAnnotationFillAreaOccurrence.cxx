#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWAnnotationFillAreaOccurrence.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_GeometricRepresentationItem.hpp>
#include <StepVisual_AnnotationFillAreaOccurrence.hpp>

//=================================================================================================

RWStepVisual_RWAnnotationFillAreaOccurrence::RWStepVisual_RWAnnotationFillAreaOccurrence() =
  default;

//=================================================================================================

void RWStepVisual_RWAnnotationFillAreaOccurrence::ReadStep(
  const occ::handle<StepData_StepReaderData>&                 data,
  const int                                                   num,
  occ::handle<Interface_Check>&                               ach,
  const occ::handle<StepVisual_AnnotationFillAreaOccurrence>& ent) const
{
  // Number of Parameter Control
  if (!data->CheckNbParams(num, 4, ach, "annotation_fill_area_occurrence"))
    return;

  // Inherited field : name
  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  // Inherited field : styles
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>> aStyles;
  occ::handle<StepVisual_PresentationStyleAssignment>                                   anent;
  int                                                                                   nsub;
  if (data->ReadSubList(num, 2, "styles", ach, nsub))
  {
    int nb  = data->NbParams(nsub);
    aStyles = new NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>(1, nb);
    for (int i = 1; i <= nb; i++)
    {
      if (data->ReadEntity(nsub,
                           i,
                           "presentation_style_assignment",
                           ach,
                           STANDARD_TYPE(StepVisual_PresentationStyleAssignment),
                           anent))
        aStyles->SetValue(i, anent);
    }
  }

  // Inherited field : item
  occ::handle<Standard_Transient> aItem;
  data->ReadEntity(num, 3, "item", ach, STANDARD_TYPE(Standard_Transient), aItem);

  // Own field : fill_style_target
  occ::handle<StepGeom_GeometricRepresentationItem> aFillStyleTarget;
  data->ReadEntity(num,
                   4,
                   "item",
                   ach,
                   STANDARD_TYPE(StepGeom_GeometricRepresentationItem),
                   aFillStyleTarget);

  // Initialisation of the read entity
  ent->Init(aName, aStyles, aItem, aFillStyleTarget);
}

//=================================================================================================

void RWStepVisual_RWAnnotationFillAreaOccurrence::WriteStep(
  StepData_StepWriter&                                        SW,
  const occ::handle<StepVisual_AnnotationFillAreaOccurrence>& ent) const
{
  // Inherited field : name
  SW.Send(ent->Name());

  // Inherited field : styles
  SW.OpenSub();
  for (int i = 1; i <= ent->NbStyles(); i++)
  {
    SW.Send(ent->StylesValue(i));
  }
  SW.CloseSub();

  // Inherited field : item
  SW.Send(ent->Item());

  // Own field: fill_area_target
  SW.Send(ent->FillStyleTarget());
}

//=================================================================================================

void RWStepVisual_RWAnnotationFillAreaOccurrence::Share(
  const occ::handle<StepVisual_AnnotationFillAreaOccurrence>& ent,
  Interface_EntityIterator&                                   iter) const
{
  int nbElem1 = ent->NbStyles();
  for (int i = 1; i <= nbElem1; i++)
  {
    iter.GetOneItem(ent->StylesValue(i));
  }
  iter.GetOneItem(ent->Item());
  iter.GetOneItem(ent->FillStyleTarget());
}
