

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWPointStyle.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_Colour.hpp>
#include <StepVisual_PointStyle.hpp>

RWStepVisual_RWPointStyle::RWStepVisual_RWPointStyle() = default;

void RWStepVisual_RWPointStyle::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepVisual_PointStyle>&   ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "point_style"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  StepVisual_MarkerSelect aMarker;

  data->ReadEntity(num, 2, "marker", ach, aMarker);

  StepBasic_SizeSelect aMarkerSize;

  data->ReadEntity(num, 3, "marker_size", ach, aMarkerSize);

  occ::handle<StepVisual_Colour> aMarkerColour;

  data->ReadEntity(num, 4, "marker_colour", ach, STANDARD_TYPE(StepVisual_Colour), aMarkerColour);

  ent->Init(aName, aMarker, aMarkerSize, aMarkerColour);
}

void RWStepVisual_RWPointStyle::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepVisual_PointStyle>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->Marker().Value());

  SW.Send(ent->MarkerSize().Value());

  SW.Send(ent->MarkerColour());
}

void RWStepVisual_RWPointStyle::Share(const occ::handle<StepVisual_PointStyle>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  if (ent->Marker().CaseNumber() > 0)
    iter.GetOneItem(ent->Marker().Value());
  iter.GetOneItem(ent->MarkerColour());
}
