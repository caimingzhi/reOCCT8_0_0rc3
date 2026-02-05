// Created on : Thu Mar 24 18:30:12 2022

#include "RWStepVisual_RWTessellatedConnectingEdge.hpp"
#include <StepVisual_TessellatedConnectingEdge.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <StepVisual_EdgeOrCurve.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepData_Logical.hpp>
#include <StepVisual_TessellatedFace.hpp>

//=================================================================================================

RWStepVisual_RWTessellatedConnectingEdge::RWStepVisual_RWTessellatedConnectingEdge() = default;

//=================================================================================================

void RWStepVisual_RWTessellatedConnectingEdge::ReadStep(
  const occ::handle<StepData_StepReaderData>&              theData,
  const int                                                theNum,
  occ::handle<Interface_Check>&                            theCheck,
  const occ::handle<StepVisual_TessellatedConnectingEdge>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 9, theCheck, "tessellated_connecting_edge"))
  {
    return;
  }

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

  // Inherited fields of TessellatedEdge

  occ::handle<StepVisual_CoordinatesList> aTessellatedEdge_Coordinates;
  theData->ReadEntity(theNum,
                      2,
                      "tessellated_edge.coordinates",
                      theCheck,
                      STANDARD_TYPE(StepVisual_CoordinatesList),
                      aTessellatedEdge_Coordinates);

  StepVisual_EdgeOrCurve aTessellatedEdge_GeometricLink;
  bool                   hasTessellatedEdge_GeometricLink = true;
  if (theData->IsParamDefined(theNum, 3))
  {
    theData->ReadEntity(theNum,
                        3,
                        "tessellated_edge.geometric_link",
                        theCheck,
                        aTessellatedEdge_GeometricLink);
  }
  else
  {
    hasTessellatedEdge_GeometricLink = false;
    aTessellatedEdge_GeometricLink   = StepVisual_EdgeOrCurve();
  }

  occ::handle<NCollection_HArray1<int>> aTessellatedEdge_LineStrip;
  int                                   sub4 = 0;
  if (theData->ReadSubList(theNum, 4, "tessellated_edge.line_strip", theCheck, sub4))
  {
    int nb0                    = theData->NbParams(sub4);
    aTessellatedEdge_LineStrip = new NCollection_HArray1<int>(1, nb0);
    int num2                   = sub4;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      int anIt0;
      theData->ReadInteger(num2, i0, "integer", theCheck, anIt0);
      aTessellatedEdge_LineStrip->SetValue(i0, anIt0);
    }
  }

  // Own fields of TessellatedConnectingEdge

  StepData_Logical aSmooth;
  theData->ReadLogical(theNum, 5, "smooth", theCheck, aSmooth);

  occ::handle<StepVisual_TessellatedFace> aFace1;
  theData
    ->ReadEntity(theNum, 6, "face1", theCheck, STANDARD_TYPE(StepVisual_TessellatedFace), aFace1);

  occ::handle<StepVisual_TessellatedFace> aFace2;
  theData
    ->ReadEntity(theNum, 7, "face2", theCheck, STANDARD_TYPE(StepVisual_TessellatedFace), aFace2);

  occ::handle<NCollection_HArray1<int>> aLineStripFace1;
  int                                   sub8 = 0;
  if (theData->ReadSubList(theNum, 8, "line_strip_face1", theCheck, sub8))
  {
    int nb0         = theData->NbParams(sub8);
    aLineStripFace1 = new NCollection_HArray1<int>(1, nb0);
    int num2        = sub8;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      int anIt0;
      theData->ReadInteger(num2, i0, "integer", theCheck, anIt0);
      aLineStripFace1->SetValue(i0, anIt0);
    }
  }

  occ::handle<NCollection_HArray1<int>> aLineStripFace2;
  int                                   sub9 = 0;
  if (theData->ReadSubList(theNum, 9, "line_strip_face2", theCheck, sub9))
  {
    int nb0         = theData->NbParams(sub9);
    aLineStripFace2 = new NCollection_HArray1<int>(1, nb0);
    int num2        = sub9;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      int anIt0;
      theData->ReadInteger(num2, i0, "integer", theCheck, anIt0);
      aLineStripFace2->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name,
               aTessellatedEdge_Coordinates,
               hasTessellatedEdge_GeometricLink,
               aTessellatedEdge_GeometricLink,
               aTessellatedEdge_LineStrip,
               aSmooth,
               aFace1,
               aFace2,
               aLineStripFace1,
               aLineStripFace2);
}

//=================================================================================================

void RWStepVisual_RWTessellatedConnectingEdge::WriteStep(
  StepData_StepWriter&                                     theSW,
  const occ::handle<StepVisual_TessellatedConnectingEdge>& theEnt) const
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

  // Own fields of TessellatedConnectingEdge

  theSW.SendLogical(theEnt->Smooth());

  theSW.Send(theEnt->Face1());

  theSW.Send(theEnt->Face2());

  theSW.OpenSub();
  for (int i7 = 1; i7 <= theEnt->LineStripFace1()->Length(); i7++)
  {
    int Var0 = theEnt->LineStripFace1()->Value(i7);
    theSW.Send(Var0);
  }
  theSW.CloseSub();

  theSW.OpenSub();
  for (int i8 = 1; i8 <= theEnt->LineStripFace2()->Length(); i8++)
  {
    int Var0 = theEnt->LineStripFace2()->Value(i8);
    theSW.Send(Var0);
  }
  theSW.CloseSub();
}

//=================================================================================================

void RWStepVisual_RWTessellatedConnectingEdge::Share(
  const occ::handle<StepVisual_TessellatedConnectingEdge>& theEnt,
  Interface_EntityIterator&                                theIter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of TessellatedEdge

  theIter.AddItem(theEnt->StepVisual_TessellatedEdge::Coordinates());

  if (theEnt->StepVisual_TessellatedEdge::HasGeometricLink())
  {
    theIter.AddItem(theEnt->StepVisual_TessellatedEdge::GeometricLink().Value());
  }

  // Own fields of TessellatedConnectingEdge

  theIter.AddItem(theEnt->Face1());

  theIter.AddItem(theEnt->Face2());
}
