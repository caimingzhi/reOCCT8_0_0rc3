

#include "RWStepVisual_RWTessellatedShapeRepresentation.hpp"
#include <StepVisual_TessellatedShapeRepresentation.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationContext.hpp>

RWStepVisual_RWTessellatedShapeRepresentation::RWStepVisual_RWTessellatedShapeRepresentation() =
  default;

void RWStepVisual_RWTessellatedShapeRepresentation::ReadStep(
  const occ::handle<StepData_StepReaderData>&                   theData,
  const int                                                     theNum,
  occ::handle<Interface_Check>&                                 theCheck,
  const occ::handle<StepVisual_TessellatedShapeRepresentation>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theCheck, "tessellated_shape_representation"))
  {
    return;
  }

  occ::handle<TCollection_HAsciiString> aRepresentation_Name;
  theData->ReadString(theNum, 1, "representation.name", theCheck, aRepresentation_Name);

  occ::handle<NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>> aRepresentation_Items;
  int                                                                        sub2 = 0;
  if (theData->ReadSubList(theNum, 2, "representation.items", theCheck, sub2))
  {
    int nb0 = theData->NbParams(sub2);
    aRepresentation_Items =
      new NCollection_HArray1<occ::handle<StepRepr_RepresentationItem>>(1, nb0);
    int num2 = sub2;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepRepr_RepresentationItem> anIt0;
      theData->ReadEntity(num2,
                          i0,
                          "representation_item",
                          theCheck,
                          STANDARD_TYPE(StepRepr_RepresentationItem),
                          anIt0);
      aRepresentation_Items->SetValue(i0, anIt0);
    }
  }

  occ::handle<StepRepr_RepresentationContext> aRepresentation_ContextOfItems;
  theData->ReadEntity(theNum,
                      3,
                      "representation.context_of_items",
                      theCheck,
                      STANDARD_TYPE(StepRepr_RepresentationContext),
                      aRepresentation_ContextOfItems);

  theEnt->Init(aRepresentation_Name, aRepresentation_Items, aRepresentation_ContextOfItems);
}

void RWStepVisual_RWTessellatedShapeRepresentation::WriteStep(
  StepData_StepWriter&                                          theSW,
  const occ::handle<StepVisual_TessellatedShapeRepresentation>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.OpenSub();
  for (int i1 = 1; i1 <= theEnt->Items()->Length(); i1++)
  {
    occ::handle<StepRepr_RepresentationItem> Var0 = theEnt->Items()->Value(i1);
    theSW.Send(Var0);
  }
  theSW.CloseSub();

  theSW.Send(theEnt->ContextOfItems());
}

void RWStepVisual_RWTessellatedShapeRepresentation::Share(
  const occ::handle<StepVisual_TessellatedShapeRepresentation>& theEnt,
  Interface_EntityIterator&                                     theIter) const
{

  if (!theEnt->StepRepr_Representation::Items().IsNull())
  {
    for (int i1 = 1; i1 <= theEnt->StepRepr_Representation::Items()->Length(); i1++)
    {
      occ::handle<StepRepr_RepresentationItem> Var0 =
        theEnt->StepRepr_Representation::Items()->Value(i1);
      theIter.AddItem(Var0);
    }
  }

  theIter.AddItem(theEnt->StepRepr_Representation::ContextOfItems());
}
