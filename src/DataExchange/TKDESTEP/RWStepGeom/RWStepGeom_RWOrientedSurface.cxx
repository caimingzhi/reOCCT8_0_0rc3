#include <Interface_EntityIterator.hpp>
#include "RWStepGeom_RWOrientedSurface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_OrientedSurface.hpp>

//=================================================================================================

RWStepGeom_RWOrientedSurface::RWStepGeom_RWOrientedSurface() = default;

//=================================================================================================

void RWStepGeom_RWOrientedSurface::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepGeom_OrientedSurface>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "oriented_surface"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Own fields of OrientedSurface

  bool aOrientation;
  data->ReadBoolean(num, 2, "orientation", ach, aOrientation);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aOrientation);
}

//=================================================================================================

void RWStepGeom_RWOrientedSurface::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepGeom_OrientedSurface>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Own fields of OrientedSurface

  SW.SendBoolean(ent->Orientation());
}

//=================================================================================================

void RWStepGeom_RWOrientedSurface::Share(const occ::handle<StepGeom_OrientedSurface>& /*ent*/,
                                         Interface_EntityIterator& /*iter*/) const
{

  // Inherited fields of RepresentationItem

  // Own fields of OrientedSurface
}
