#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWTessellatedAnnotationOccurrence.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_TessellatedAnnotationOccurrence.hpp>

//=================================================================================================

RWStepVisual_RWTessellatedAnnotationOccurrence::RWStepVisual_RWTessellatedAnnotationOccurrence() =
  default;

//=================================================================================================

void RWStepVisual_RWTessellatedAnnotationOccurrence::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepVisual_TessellatedAnnotationOccurrence>& ent) const
{

  // Number of Parameter Control
  if (!data->CheckNbParams(num, 3, ach, "styled_item"))
    return;

  // Inherited field : name
  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  // Inherited field : styles
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>> aStyles;
  occ::handle<StepVisual_PresentationStyleAssignment>                                   anent2;
  int                                                                                   nsub2;
  if (data->ReadSubList(num, 2, "styles", ach, nsub2))
  {
    int nb2 = data->NbParams(nsub2);
    aStyles = new NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>(1, nb2);
    for (int i2 = 1; i2 <= nb2; i2++)
    {
      if (data->ReadEntity(nsub2,
                           i2,
                           "presentation_style_assignment",
                           ach,
                           STANDARD_TYPE(StepVisual_PresentationStyleAssignment),
                           anent2))
        aStyles->SetValue(i2, anent2);
    }
  }

  // Inherited field : item
  occ::handle<Standard_Transient> aItem;
  data->ReadEntity(num, 3, "item", ach, STANDARD_TYPE(Standard_Transient), aItem);

  // Initialisation of the read entity
  ent->Init(aName, aStyles, aItem);
}

//=================================================================================================

void RWStepVisual_RWTessellatedAnnotationOccurrence::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepVisual_TessellatedAnnotationOccurrence>& ent) const
{
  // Inherited field : name
  SW.Send(ent->Name());

  // Inherited field : styles
  SW.OpenSub();
  for (int i2 = 1; i2 <= ent->NbStyles(); i2++)
  {
    SW.Send(ent->StylesValue(i2));
  }
  SW.CloseSub();

  // Inherited field : item

  SW.Send(ent->Item());
}

//=================================================================================================

void RWStepVisual_RWTessellatedAnnotationOccurrence::Share(
  const occ::handle<StepVisual_TessellatedAnnotationOccurrence>& ent,
  Interface_EntityIterator&                                      iter) const
{

  int nbElem1 = ent->NbStyles();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->StylesValue(is1));
  }

  iter.GetOneItem(ent->Item());
}
