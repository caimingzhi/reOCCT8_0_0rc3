

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCameraImage.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepRepr_RepresentationMap.hpp>
#include <StepVisual_CameraImage.hpp>

RWStepVisual_RWCameraImage::RWStepVisual_RWCameraImage() = default;

void RWStepVisual_RWCameraImage::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepVisual_CameraImage>&  ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "camera_image"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepRepr_RepresentationMap> aMappingSource;

  data->ReadEntity(num,
                   2,
                   "mapping_source",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationMap),
                   aMappingSource);

  occ::handle<StepRepr_RepresentationItem> aMappingTarget;

  data->ReadEntity(num,
                   3,
                   "mapping_target",
                   ach,
                   STANDARD_TYPE(StepRepr_RepresentationItem),
                   aMappingTarget);

  ent->Init(aName, aMappingSource, aMappingTarget);
}

void RWStepVisual_RWCameraImage::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepVisual_CameraImage>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->MappingSource());

  SW.Send(ent->MappingTarget());
}

void RWStepVisual_RWCameraImage::Share(const occ::handle<StepVisual_CameraImage>& ent,
                                       Interface_EntityIterator&                  iter) const
{

  iter.GetOneItem(ent->MappingSource());

  iter.GetOneItem(ent->MappingTarget());
}
