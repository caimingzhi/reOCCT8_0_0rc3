#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWAnnotationPlane.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_AnnotationPlane.hpp>

//=================================================================================================

RWStepVisual_RWAnnotationPlane::RWStepVisual_RWAnnotationPlane() = default;

//=================================================================================================

void RWStepVisual_RWAnnotationPlane::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepVisual_AnnotationPlane>& ent) const
{
  // Number of Parameter Control
  if (!data->CheckNbParams(num, 4, ach, "annotation_plane"))
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

  // Own field: elements
  occ::handle<NCollection_HArray1<StepVisual_AnnotationPlaneElement>> anElements;
  StepVisual_AnnotationPlaneElement                                   anEnt;
  int                                                                 nbSub;
  if (data->ReadSubList(num, 4, "elements", ach, nbSub))
  {
    int nbElements = data->NbParams(nbSub);
    anElements     = new NCollection_HArray1<StepVisual_AnnotationPlaneElement>(1, nbElements);
    for (int i = 1; i <= nbElements; i++)
    {
      if (data->ReadEntity(nbSub, i, "content", ach, anEnt))
        anElements->SetValue(i, anEnt);
    }
  }

  // Initialisation of the read entity
  ent->Init(aName, aStyles, aItem, anElements);
}

//=================================================================================================

void RWStepVisual_RWAnnotationPlane::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepVisual_AnnotationPlane>& ent) const
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

  // Own field: elements
  SW.OpenSub();
  for (int i = 1; i <= ent->NbElements(); i++)
  {
    SW.Send(ent->ElementsValue(i).Value());
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepVisual_RWAnnotationPlane::Share(const occ::handle<StepVisual_AnnotationPlane>& ent,
                                           Interface_EntityIterator& iter) const
{
  int nbElem1 = ent->NbStyles();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->StylesValue(is1));
  }
  iter.GetOneItem(ent->Item());

  // Own field: contents
  int i, nb = ent->NbElements();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->ElementsValue(i).Value());
}
