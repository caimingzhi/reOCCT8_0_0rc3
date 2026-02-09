

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCameraUsage.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <StepVisual_CameraUsage.hpp>

RWStepVisual_RWCameraUsage::RWStepVisual_RWCameraUsage() = default;

void RWStepVisual_RWCameraUsage::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepVisual_CameraUsage>&  ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "camera_usage"))
    return;

  occ::handle<StepRepr_RepresentationItem> aMappingOrigin;

  data->ReadEntity(num,
                   1,
                   "mapping_origin",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationItem),
                   aMappingOrigin);

  occ::handle<StepRepr_Representation> aMappedRepresentation;

  data->ReadEntity(num,
                   2,
                   "mapped_representation",
                   ach,
                   STANDARD_TYPE(StepRepr_Representation),
                   aMappedRepresentation);

  ent->Init(aMappingOrigin, aMappedRepresentation);
}

void RWStepVisual_RWCameraUsage::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepVisual_CameraUsage>& ent) const
{

  SW.Send(ent->MappingOrigin());

  SW.Send(ent->MappedRepresentation());
}

void RWStepVisual_RWCameraUsage::Share(const occ::handle<StepVisual_CameraUsage>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->MappingOrigin());

  iter.GetOneItem(ent->MappedRepresentation());
}
