// Created on : Thu Mar 24 18:30:12 2022

#include "RWStepVisual_RWTessellatedEdge.hpp"
#include <StepVisual_TessellatedEdge.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <StepVisual_EdgeOrCurve.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=================================================================================================

RWStepVisual_RWTessellatedEdge::RWStepVisual_RWTessellatedEdge() = default;

//=================================================================================================

void RWStepVisual_RWTessellatedEdge::ReadStep(
  const occ::handle<StepData_StepReaderData>&    theData,
  const int                                      theNum,
  occ::handle<Interface_Check>&                  theCheck,
  const occ::handle<StepVisual_TessellatedEdge>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 4, theCheck, "tessellated_edge"))
  {
    return;
  }

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

  // Own fields of TessellatedEdge

  occ::handle<StepVisual_CoordinatesList> aCoordinates;
  theData->ReadEntity(theNum,
                      2,
                      "coordinates",
                      theCheck,
                      STANDARD_TYPE(StepVisual_CoordinatesList),
                      aCoordinates);

  StepVisual_EdgeOrCurve aGeometricLink;
  bool                   hasGeometricLink = true;
  if (theData->IsParamDefined(theNum, 3))
  {
    theData->ReadEntity(theNum, 3, "geometric_link", theCheck, aGeometricLink);
  }
  else
  {
    hasGeometricLink = false;
    aGeometricLink   = StepVisual_EdgeOrCurve();
  }

  occ::handle<NCollection_HArray1<int>> aLineStrip;
  int                                   sub4 = 0;
  if (theData->ReadSubList(theNum, 4, "line_strip", theCheck, sub4))
  {
    int nb0    = theData->NbParams(sub4);
    aLineStrip = new NCollection_HArray1<int>(1, nb0);
    int num2   = sub4;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      int anIt0;
      theData->ReadInteger(num2, i0, "integer", theCheck, anIt0);
      aLineStrip->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name,
               aCoordinates,
               hasGeometricLink,
               aGeometricLink,
               aLineStrip);
}

//=================================================================================================

void RWStepVisual_RWTessellatedEdge::WriteStep(
  StepData_StepWriter&                           theSW,
  const occ::handle<StepVisual_TessellatedEdge>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Own fields of TessellatedEdge

  theSW.Send(theEnt->Coordinates());

  if (theEnt->HasGeometricLink())
  {
    theSW.Send(theEnt->GeometricLink().Value());
  }
  else
  {
    theSW.SendUndef();
  }

  theSW.OpenSub();
  for (int i3 = 1; i3 <= theEnt->LineStrip()->Length(); i3++)
  {
    int Var0 = theEnt->LineStrip()->Value(i3);
    theSW.Send(Var0);
  }
  theSW.CloseSub();
}

//=================================================================================================

void RWStepVisual_RWTessellatedEdge::Share(const occ::handle<StepVisual_TessellatedEdge>& theEnt,
                                           Interface_EntityIterator& theIter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of TessellatedEdge

  theIter.AddItem(theEnt->Coordinates());

  if (theEnt->HasGeometricLink())
  {
    theIter.AddItem(theEnt->GeometricLink().Value());
  }
}
