// Created on : Thu Mar 24 18:30:12 2022

#include "RWStepVisual_RWTessellatedVertex.hpp"
#include <StepVisual_TessellatedVertex.hpp>
#include <Interface_EntityIterator.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <TCollection_HAsciiString.hpp>
#include <StepVisual_CoordinatesList.hpp>
#include <StepShape_VertexPoint.hpp>
#include <Standard_Integer.hpp>

//=================================================================================================

RWStepVisual_RWTessellatedVertex::RWStepVisual_RWTessellatedVertex() = default;

//=================================================================================================

void RWStepVisual_RWTessellatedVertex::ReadStep(
  const occ::handle<StepData_StepReaderData>&      theData,
  const int                                        theNum,
  occ::handle<Interface_Check>&                    theCheck,
  const occ::handle<StepVisual_TessellatedVertex>& theEnt) const
{
  // Check number of parameters
  if (!theData->CheckNbParams(theNum, 4, theCheck, "tessellated_vertex"))
  {
    return;
  }

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  theData->ReadString(theNum, 1, "representation_item.name", theCheck, aRepresentationItem_Name);

  // Own fields of TessellatedVertex

  occ::handle<StepVisual_CoordinatesList> aCoordinates;
  theData->ReadEntity(theNum,
                      2,
                      "coordinates",
                      theCheck,
                      STANDARD_TYPE(StepVisual_CoordinatesList),
                      aCoordinates);

  occ::handle<StepShape_VertexPoint> aTopologicalLink;
  bool                               hasTopologicalLink = true;
  if (theData->IsParamDefined(theNum, 3))
  {
    theData->ReadEntity(theNum,
                        3,
                        "topological_link",
                        theCheck,
                        STANDARD_TYPE(StepShape_VertexPoint),
                        aTopologicalLink);
  }
  else
  {
    hasTopologicalLink = false;
    aTopologicalLink.Nullify();
  }

  int aPointIndex;
  theData->ReadInteger(theNum, 4, "point_index", theCheck, aPointIndex);

  // Initialize entity
  theEnt->Init(aRepresentationItem_Name,
               aCoordinates,
               hasTopologicalLink,
               aTopologicalLink,
               aPointIndex);
}

//=================================================================================================

void RWStepVisual_RWTessellatedVertex::WriteStep(
  StepData_StepWriter&                             theSW,
  const occ::handle<StepVisual_TessellatedVertex>& theEnt) const
{

  // Own fields of RepresentationItem

  theSW.Send(theEnt->Name());

  // Own fields of TessellatedVertex

  theSW.Send(theEnt->Coordinates());

  if (theEnt->HasTopologicalLink())
  {
    theSW.Send(theEnt->TopologicalLink());
  }
  else
  {
    theSW.SendUndef();
  }

  theSW.Send(theEnt->PointIndex());
}

//=================================================================================================

void RWStepVisual_RWTessellatedVertex::Share(
  const occ::handle<StepVisual_TessellatedVertex>& theEnt,
  Interface_EntityIterator&                        theIter) const
{

  // Inherited fields of RepresentationItem

  // Own fields of TessellatedVertex

  theIter.AddItem(theEnt->Coordinates());

  if (theEnt->HasTopologicalLink())
  {
    theIter.AddItem(theEnt->TopologicalLink());
  }
}
