

#include "RWStepVisual_RWTessellatedWire.hpp"
#include <StepVisual_TessellatedWire.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepVisual_TessellatedEdgeOrVertex.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_PathOrCompositeCurve.hpp>

RWStepVisual_RWTessellatedWire::RWStepVisual_RWTessellatedWire() = default;

void RWStepVisual_RWTessellatedWire::ReadStep(
  const occ::handle<StepData_StepReaderData>&    theData,
  const int                                      theNum,
  occ::handle<Interface_Check>&                  theCheck,
  const occ::handle<StepVisual_TessellatedWire>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theCheck, "tessellated_wire"))
  {
    return;
  }

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

  occ::handle<NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>> aItems;
  int                                                                  sub2 = 0;
  if (theData->ReadSubList(theNum, 2, "items", theCheck, sub2))
  {
    int nb0  = theData->NbParams(sub2);
    aItems   = new NCollection_HArray1<StepVisual_TessellatedEdgeOrVertex>(1, nb0);
    int num2 = sub2;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepVisual_TessellatedEdgeOrVertex anIt0;
      theData->ReadEntity(num2, i0, "tessellated_edge_or_vertex", theCheck, anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  StepVisual_PathOrCompositeCurve aGeometricModelLink;
  bool                            hasGeometricModelLink = true;
  if (theData->IsParamDefined(theNum, 3))
  {
    theData->ReadEntity(theNum, 3, "geometric_model_link", theCheck, aGeometricModelLink);
  }
  else
  {
    hasGeometricModelLink = false;
    aGeometricModelLink   = StepVisual_PathOrCompositeCurve();
  }

  theEnt->Init(aRepresentationItem_Name, aItems, hasGeometricModelLink, aGeometricModelLink);
}

void RWStepVisual_RWTessellatedWire::WriteStep(
  StepData_StepWriter&                           theSW,
  const occ::handle<StepVisual_TessellatedWire>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.OpenSub();
  for (int i1 = 1; i1 <= theEnt->Items()->Length(); i1++)
  {
    StepVisual_TessellatedEdgeOrVertex Var0 = theEnt->Items()->Value(i1);
    theSW.Send(Var0.Value());
  }
  theSW.CloseSub();

  if (theEnt->HasGeometricModelLink())
  {
    theSW.Send(theEnt->GeometricModelLink().Value());
  }
  else
  {
    theSW.SendUndef();
  }
}

void RWStepVisual_RWTessellatedWire::Share(const occ::handle<StepVisual_TessellatedWire>& theEnt,
                                           Interface_EntityIterator& theIter) const
{

  for (int i1 = 1; i1 <= theEnt->Items()->Length(); i1++)
  {
    StepVisual_TessellatedEdgeOrVertex Var0 = theEnt->Items()->Value(i1);
    theIter.AddItem(Var0.Value());
  }

  if (theEnt->HasGeometricModelLink())
  {
    theIter.AddItem(theEnt->GeometricModelLink().Value());
  }
}
