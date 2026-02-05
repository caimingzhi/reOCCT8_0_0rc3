#include <Interface_EntityIterator.hpp>
#include "RWStepElement_RWSurfaceElementProperty.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepElement_SurfaceElementProperty.hpp>
#include <StepElement_SurfaceSectionField.hpp>

//=================================================================================================

RWStepElement_RWSurfaceElementProperty::RWStepElement_RWSurfaceElementProperty() = default;

//=================================================================================================

void RWStepElement_RWSurfaceElementProperty::ReadStep(
  const occ::handle<StepData_StepReaderData>&            data,
  const int                                              num,
  occ::handle<Interface_Check>&                          ach,
  const occ::handle<StepElement_SurfaceElementProperty>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "surface_element_property"))
    return;

  // Own fields of SurfaceElementProperty

  occ::handle<TCollection_HAsciiString> aPropertyId;
  data->ReadString(num, 1, "property_id", ach, aPropertyId);

  occ::handle<TCollection_HAsciiString> aDescription;
  data->ReadString(num, 2, "description", ach, aDescription);

  occ::handle<StepElement_SurfaceSectionField> aSection;
  data
    ->ReadEntity(num, 3, "section", ach, STANDARD_TYPE(StepElement_SurfaceSectionField), aSection);

  // Initialize entity
  ent->Init(aPropertyId, aDescription, aSection);
}

//=================================================================================================

void RWStepElement_RWSurfaceElementProperty::WriteStep(
  StepData_StepWriter&                                   SW,
  const occ::handle<StepElement_SurfaceElementProperty>& ent) const
{

  // Own fields of SurfaceElementProperty

  SW.Send(ent->PropertyId());

  SW.Send(ent->Description());

  SW.Send(ent->Section());
}

//=================================================================================================

void RWStepElement_RWSurfaceElementProperty::Share(
  const occ::handle<StepElement_SurfaceElementProperty>& ent,
  Interface_EntityIterator&                              iter) const
{

  // Own fields of SurfaceElementProperty

  iter.AddItem(ent->Section());
}
