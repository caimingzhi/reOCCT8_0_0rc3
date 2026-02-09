

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCameraModelD3.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepVisual_CameraModelD3.hpp>
#include <StepVisual_ViewVolume.hpp>

RWStepVisual_RWCameraModelD3::RWStepVisual_RWCameraModelD3() = default;

void RWStepVisual_RWCameraModelD3::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepVisual_CameraModelD3>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "camera_model_d3"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepGeom_Axis2Placement3d> aViewReferenceSystem;

  data->ReadEntity(num,
                   2,
                   "view_reference_system",
                   ach,
                   STANDARD_TYPE(StepGeom_Axis2Placement3d),
                   aViewReferenceSystem);

  occ::handle<StepVisual_ViewVolume> aPerspectiveOfVolume;

  data->ReadEntity(num,
                   3,
                   "perspective_of_volume",
                   ach,
                   STANDARD_TYPE(StepVisual_ViewVolume),
                   aPerspectiveOfVolume);

  ent->Init(aName, aViewReferenceSystem, aPerspectiveOfVolume);
}

void RWStepVisual_RWCameraModelD3::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepVisual_CameraModelD3>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->ViewReferenceSystem());

  SW.Send(ent->PerspectiveOfVolume());
}

void RWStepVisual_RWCameraModelD3::Share(const occ::handle<StepVisual_CameraModelD3>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->ViewReferenceSystem());

  iter.GetOneItem(ent->PerspectiveOfVolume());
}
