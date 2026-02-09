

#include "RWStepVisual_RWCameraModel.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CameraModel.hpp>

RWStepVisual_RWCameraModel::RWStepVisual_RWCameraModel() = default;

void RWStepVisual_RWCameraModel::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                          const int                                   num,
                                          occ::handle<Interface_Check>&               ach,
                                          const occ::handle<StepVisual_CameraModel>&  ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "camera_model has not 1 parameter(s)"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  ent->Init(aName);
}

void RWStepVisual_RWCameraModel::WriteStep(StepData_StepWriter&                       SW,
                                           const occ::handle<StepVisual_CameraModel>& ent) const
{

  SW.Send(ent->Name());
}
