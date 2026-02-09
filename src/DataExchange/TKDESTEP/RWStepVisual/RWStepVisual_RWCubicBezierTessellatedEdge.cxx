

#include "RWStepVisual_RWCubicBezierTessellatedEdge.hpp"
#include <StepVisual_CubicBezierTessellatedEdge.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <StepVisual_EdgeOrCurve.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepVisual_RWCubicBezierTessellatedEdge::RWStepVisual_RWCubicBezierTessellatedEdge() = default;

void RWStepVisual_RWCubicBezierTessellatedEdge::ReadStep(
  const occ::handle<StepData_StepReaderData>&               theData,
  const int                                                 theNum,
  occ::handle<Interface_Check>&                             theCheck,
  const occ::handle<StepVisual_CubicBezierTessellatedEdge>& theEnt) const
{

  if (!theData->CheckNbParams(theNum, 4, theCheck, "cubic_bezier_tessellated_edge"))
  {
    return;
  }

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

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

  theEnt->Init(aRepresentationItem_Name,
               aTessellatedEdge_Coordinates,
               hasTessellatedEdge_GeometricLink,
               aTessellatedEdge_GeometricLink,
               aTessellatedEdge_LineStrip);
}

void RWStepVisual_RWCubicBezierTessellatedEdge::WriteStep(
  StepData_StepWriter&                                      theSW,
  const occ::handle<StepVisual_CubicBezierTessellatedEdge>& theEnt) const
{

  theSW.Send(theEnt->Name());

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

void RWStepVisual_RWCubicBezierTessellatedEdge::Share(
  const occ::handle<StepVisual_CubicBezierTessellatedEdge>& theEnt,
  Interface_EntityIterator&                                 theIter) const
{

  theIter.AddItem(theEnt->StepVisual_TessellatedEdge::Coordinates());

  if (theEnt->StepVisual_TessellatedEdge::HasGeometricLink())
  {
    theIter.AddItem(theEnt->StepVisual_TessellatedEdge::GeometricLink().Value());
  }
}
