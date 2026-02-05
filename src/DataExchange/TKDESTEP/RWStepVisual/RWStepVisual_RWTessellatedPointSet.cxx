// Created on : Thu Mar 24 18:30:12 2022

#include "RWStepVisual_RWTessellatedPointSet.hpp"
#include <StepVisual_TessellatedPointSet.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=================================================================================================

RWStepVisual_RWTessellatedPointSet::RWStepVisual_RWTessellatedPointSet() = default;

//=================================================================================================

void RWStepVisual_RWTessellatedPointSet::ReadStep(
  const occ::handle<StepData_StepReaderData>&        theData,
  const int                                          theNum,
  occ::handle<Interface_Check>&                      theCheck,
  const occ::handle<StepVisual_TessellatedPointSet>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 3, theCheck, "tessellated_point_set"))
  {
    return;
  }

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

  // Own fields of TessellatedPointSet

  occ::handle<StepVisual_CoordinatesList> aCoordinates;
  theData->ReadEntity(theNum,
                      2,
                      "coordinates",
                      theCheck,
                      STANDARD_TYPE(StepVisual_CoordinatesList),
                      aCoordinates);

  occ::handle<NCollection_HArray1<int>> aPointList;
  int                                   sub3 = 0;
  if (theData->ReadSubList(theNum, 3, "point_list", theCheck, sub3))
  {
    int nb0    = theData->NbParams(sub3);
    aPointList = new NCollection_HArray1<int>(1, nb0);
    int num2   = sub3;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      int anIt0;
      theData->ReadInteger(num2, i0, "integer", theCheck, anIt0);
      aPointList->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name, aCoordinates, aPointList);
}

//=================================================================================================

void RWStepVisual_RWTessellatedPointSet::WriteStep(
  StepData_StepWriter&                               theSW,
  const occ::handle<StepVisual_TessellatedPointSet>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Own fields of TessellatedPointSet

  theSW.Send(theEnt->Coordinates());

  theSW.OpenSub();
  for (int i2 = 1; i2 <= theEnt->PointList()->Length(); i2++)
  {
    int Var0 = theEnt->PointList()->Value(i2);
    theSW.Send(Var0);
  }
  theSW.CloseSub();
}

//=================================================================================================

void RWStepVisual_RWTessellatedPointSet::Share(
  const occ::handle<StepVisual_TessellatedPointSet>& theEnt,
  Interface_EntityIterator&                          theIter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of TessellatedPointSet

  theIter.AddItem(theEnt->Coordinates());
}
