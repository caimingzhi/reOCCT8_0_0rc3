

#include "RWStepVisual_RWTessellatedSolid.hpp"
#include <StepVisual_TessellatedSolid.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepVisual_TessellatedStructuredItem.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_ManifoldSolidBrep.hpp>

RWStepVisual_RWTessellatedSolid::RWStepVisual_RWTessellatedSolid() = default;

void RWStepVisual_RWTessellatedSolid::ReadStep(
  const occ::handle<StepData_StepReaderData>&     theData,
  const int                                       theNum,
  occ::handle<Interface_Check>&                   theCheck,
  const occ::handle<StepVisual_TessellatedSolid>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 3, theCheck, "tessellated_solid"))
  {
    return;
  }

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

  occ::handle<NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>> aItems;
  int                                                                                 sub2 = 0;
  if (theData->ReadSubList(theNum, 2, "items", theCheck, sub2))
  {
    int nb0  = theData->NbParams(sub2);
    aItems   = new NCollection_HArray1<occ::handle<StepVisual_TessellatedStructuredItem>>(1, nb0);
    int num2 = sub2;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepVisual_TessellatedStructuredItem> anIt0;
      theData->ReadEntity(num2,
                          i0,
                          "tessellated_structured_item",
                          theCheck,
                          STANDARD_TYPE(StepVisual_TessellatedStructuredItem),
                          anIt0);
      aItems->SetValue(i0, anIt0);
    }
  }

  occ::handle<StepShape_ManifoldSolidBrep> aGeometricLink;
  bool                                     hasGeometricLink = true;
  if (theData->IsParamDefined(theNum, 3))
  {
    theData->ReadEntity(theNum,
                        3,
                        "geometric_link",
                        theCheck,
                        STANDARD_TYPE(StepShape_ManifoldSolidBrep),
                        aGeometricLink);
  }
  else
  {
    hasGeometricLink = false;
    aGeometricLink.Nullify();
  }

  theEnt->Init(aRepresentationItem_Name, aItems, hasGeometricLink, aGeometricLink);
}

void RWStepVisual_RWTessellatedSolid::WriteStep(
  StepData_StepWriter&                            theSW,
  const occ::handle<StepVisual_TessellatedSolid>& theEnt) const
{

  theSW.Send(theEnt->Name());

  theSW.OpenSub();
  for (int i1 = 1; i1 <= theEnt->Items()->Length(); i1++)
  {
    occ::handle<StepVisual_TessellatedStructuredItem> Var0 = theEnt->Items()->Value(i1);
    theSW.Send(Var0);
  }
  theSW.CloseSub();

  if (theEnt->HasGeometricLink())
  {
    theSW.Send(theEnt->GeometricLink());
  }
  else
  {
    theSW.SendUndef();
  }
}

void RWStepVisual_RWTessellatedSolid::Share(const occ::handle<StepVisual_TessellatedSolid>& theEnt,
                                            Interface_EntityIterator& theIter) const
{

  for (int i1 = 1; i1 <= theEnt->Items()->Length(); i1++)
  {
    occ::handle<StepVisual_TessellatedStructuredItem> Var0 = theEnt->Items()->Value(i1);
    theIter.AddItem(Var0);
  }

  if (theEnt->HasGeometricLink())
  {
    theIter.AddItem(theEnt->GeometricLink());
  }
}
