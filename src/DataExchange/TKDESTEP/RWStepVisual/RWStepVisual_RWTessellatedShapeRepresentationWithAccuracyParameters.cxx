

#include "RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters.hpp"
#include <StepVisual_TessellatedShapeRepresentationWithAccuracyParameters.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationContext.hpp>

RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters::
  RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters() = default;

void RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters::ReadStep(
  const occ::handle<StepData_StepReaderData>&                                         theData,
  const int                                                                           theNum,
  occ::handle<Interface_Check>&                                                       theCheck,
  const occ::handle<StepVisual_TessellatedShapeRepresentationWithAccuracyParameters>& theEnt) const
{

  if (!theData->CheckNbParams(theNum,
                              4,
                              theCheck,
                              "tessellated_shape_representation_with_accuracy_parameters"))
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

  occ::handle<NCollection_HArray1<double>> aTessellationAccuracyParameters;
  int                                      sub4 = 0;
  if (theData->ReadSubList(theNum, 4, "tessellation_accuracy_parameters", theCheck, sub4))
  {
    int nb0                         = theData->NbParams(sub4);
    aTessellationAccuracyParameters = new NCollection_HArray1<double>(1, nb0);
    int num2                        = sub4;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      double anIt0;
      theData->ReadReal(num2, i0, "tessellation_accuracy_parameter_item", theCheck, anIt0);
      aTessellationAccuracyParameters->SetValue(i0, anIt0);
    }
  }

  theEnt->Init(aRepresentation_Name,
               aRepresentation_Items,
               aRepresentation_ContextOfItems,
               aTessellationAccuracyParameters);
}

void RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters::WriteStep(
  StepData_StepWriter&                                                                theSW,
  const occ::handle<StepVisual_TessellatedShapeRepresentationWithAccuracyParameters>& theEnt) const
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

  theSW.OpenSub();
  for (int i3 = 1; i3 <= theEnt->TessellationAccuracyParameters()->Length(); i3++)
  {
    double Var0 = theEnt->TessellationAccuracyParameters()->Value(i3);
    theSW.Send(Var0);
  }
  theSW.CloseSub();
}

void RWStepVisual_RWTessellatedShapeRepresentationWithAccuracyParameters::Share(
  const occ::handle<StepVisual_TessellatedShapeRepresentationWithAccuracyParameters>& theEnt,
  Interface_EntityIterator&                                                           theIter) const
{

  for (int i1 = 1; i1 <= theEnt->StepRepr_Representation::Items()->Length(); i1++)
  {
    occ::handle<StepRepr_RepresentationItem> Var0 =
      theEnt->StepRepr_Representation::Items()->Value(i1);
    theIter.AddItem(Var0);
  }

  theIter.AddItem(theEnt->StepRepr_Representation::ContextOfItems());
}
