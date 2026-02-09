

#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWOrientedPath.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_EdgeLoop.hpp>
#include <StepShape_OrientedPath.hpp>

RWStepShape_RWOrientedPath::RWStepShape_RWOrientedPath() = default;

void RWStepShape_RWOrientedPath::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepShape_OrientedPath>&  ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "oriented_path"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  data->CheckDerived(num, 2, "edge_list", ach, false);

  occ::handle<StepShape_EdgeLoop> aPathElement;

  data->ReadEntity(num, 3, "path_element", ach, STANDARD_TYPE(StepShape_EdgeLoop), aPathElement);

  bool aOrientation;

  data->ReadBoolean(num, 4, "orientation", ach, aOrientation);

  ent->Init(aName, aPathElement, aOrientation);
}

void RWStepShape_RWOrientedPath::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepShape_OrientedPath>& ent) const
{

  SW.Send(ent->Name());

  SW.SendDerived();

  SW.Send(ent->PathElement());

  SW.SendBoolean(ent->Orientation());
}

void RWStepShape_RWOrientedPath::Share(const occ::handle<StepShape_OrientedPath>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->PathElement());
}
