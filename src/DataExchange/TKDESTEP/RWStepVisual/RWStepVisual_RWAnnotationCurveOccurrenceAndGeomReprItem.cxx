#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_AnnotationCurveOccurrenceAndGeomReprItem.hpp>

//=================================================================================================

RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem::
  RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem() = default;

//=================================================================================================

void RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem::ReadStep(
  const occ::handle<StepData_StepReaderData>&                             data,
  const int                                                               num0,
  occ::handle<Interface_Check>&                                           ach,
  const occ::handle<StepVisual_AnnotationCurveOccurrenceAndGeomReprItem>& ent) const
{
  int num = 0;
  data->NamedForComplex("REPRESENTATION_ITEM", "RPRITM", num0, num, ach);
  // Inherited field : name
  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  data->NamedForComplex("STYLED_ITEM", "STYITM", num0, num, ach);
  // Inherited field : styles
  occ::handle<NCollection_HArray1<occ::handle<StepVisual_PresentationStyleAssignment>>> aStyles;
  occ::handle<StepVisual_PresentationStyleAssignment>                                   anEnt;
  int                                                                                   nsub;
  if (data->ReadSubList(num, 1, "styles", ach, nsub))
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
                           anEnt))
        aStyles->SetValue(i, anEnt);
    }
  }

  // Inherited field : item
  occ::handle<Standard_Transient> aItem;
  data->ReadEntity(num, 2, "item", ach, STANDARD_TYPE(Standard_Transient), aItem);

  // Initialization of the read entity
  ent->Init(aName, aStyles, aItem);
}

//=================================================================================================

void RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem::WriteStep(
  StepData_StepWriter&                                                    SW,
  const occ::handle<StepVisual_AnnotationCurveOccurrenceAndGeomReprItem>& ent) const
{
  SW.StartEntity("ANNOTATION_CURVE_OCCURRENCE");
  SW.StartEntity("ANNOTATION_OCCURRENCE");
  SW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");
  SW.StartEntity("REPRESENTATION_ITEM");
  // Inherited field : name
  SW.Send(ent->Name());

  SW.StartEntity("STYLED_ITEM");
  // Inherited field : styles
  SW.OpenSub();
  for (int i = 1; i <= ent->NbStyles(); i++)
  {
    SW.Send(ent->StylesValue(i));
  }
  SW.CloseSub();

  // Inherited field : item
  SW.Send(ent->Item());
}

//=================================================================================================

void RWStepVisual_RWAnnotationCurveOccurrenceAndGeomReprItem::Share(
  const occ::handle<StepVisual_AnnotationCurveOccurrenceAndGeomReprItem>& ent,
  Interface_EntityIterator&                                               iter) const
{

  int nbElem = ent->NbStyles();
  for (int i = 1; i <= nbElem; i++)
  {
    iter.GetOneItem(ent->StylesValue(i));
  }

  iter.GetOneItem(ent->Item());
}
