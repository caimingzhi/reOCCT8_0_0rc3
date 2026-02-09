

#include "RWStepVisual_RWRepositionedTessellatedGeometricSet.hpp"

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepVisual_PresentationStyleAssignment.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_RepositionedTessellatedGeometricSet.hpp>
#include <StepGeom_Axis2Placement3d.hpp>

void RWStepVisual_RWRepositionedTessellatedGeometricSet::ReadStep(
  const occ::handle<StepData_StepReaderData>&                        theData,
  const int                                                          theNum,
  occ::handle<Interface_Check>&                                      theAch,
  const occ::handle<StepVisual_RepositionedTessellatedGeometricSet>& theEnt) const
{
  int aNum = 0;
  theData->NamedForComplex("REPOSITIONED_TESSELLATED_ITEM", theNum, aNum, theAch);
  if (!theData->CheckNbParams(aNum, 1, theAch, "location"))
    return;
  occ::handle<StepGeom_Axis2Placement3d> aLocation;
  theData
    ->ReadEntity(aNum, 1, "location", theAch, STANDARD_TYPE(StepGeom_Axis2Placement3d), aLocation);

  theData->NamedForComplex("REPRESENTATION_ITEM", theNum, aNum, theAch);
  if (!theData->CheckNbParams(aNum, 1, theAch, "name"))
    return;
  occ::handle<TCollection_HAsciiString> aName;
  theData->ReadString(aNum, 1, "name", theAch, aName);

  theData->NamedForComplex("TESSELLATED_GEOMETRIC_SET", theNum, aNum, theAch);
  NCollection_Handle<NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>> anItems;
  int                                                                             aNSub2;
  if (theData->ReadSubList(aNum, 1, "items", theAch, aNSub2))
  {
    int aNb2 = theData->NbParams(aNSub2);
    anItems  = new NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>(1, aNb2);
    for (int i2 = 1; i2 <= aNb2; i2++)
    {
      occ::handle<StepVisual_TessellatedItem> anItem;
      if (theData->ReadEntity(aNSub2,
                              i2,
                              "item",
                              theAch,
                              STANDARD_TYPE(StepVisual_TessellatedItem),
                              anItem))
        anItems->SetValue(i2, anItem);
    }
  }
  theEnt->Init(aName, anItems, aLocation);
}

void RWStepVisual_RWRepositionedTessellatedGeometricSet::WriteStep(
  StepData_StepWriter&                                               theSW,
  const occ::handle<StepVisual_RepositionedTessellatedGeometricSet>& theEnt) const
{
  theSW.StartEntity("GEOMETRIC_REPRESENTATION_ITEM");
  theSW.StartEntity("REPOSITIONED_TESSELLATED_ITEM");
  theSW.Send(theEnt->Location());
  theSW.StartEntity("REPRESENTATION_ITEM");
  theSW.Send(theEnt->Name());
  theSW.StartEntity("TESSELLATED_GEOMETRIC_SET");
  theSW.OpenSub();
  for (NCollection_Array1<occ::handle<StepVisual_TessellatedItem>>::Iterator anIter(
         *theEnt->Items());
       anIter.More();
       anIter.Next())
  {
    theSW.Send(anIter.Value());
  }
  theSW.CloseSub();
  theSW.StartEntity("TESSELLATED_ITEM");
}

void RWStepVisual_RWRepositionedTessellatedGeometricSet::Share(
  const occ::handle<StepVisual_RepositionedTessellatedGeometricSet>& theEnt,
  Interface_EntityIterator&                                          theIter) const
{

  for (int i = 1; i <= theEnt->Items()->Length(); i++)
    theIter.AddItem(theEnt->Items()->Value(i));
  theIter.AddItem(theEnt->Location());
}
