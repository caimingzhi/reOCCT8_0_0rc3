

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCameraModelD2.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CameraModelD2.hpp>
#include <StepVisual_PlanarBox.hpp>

RWStepVisual_RWCameraModelD2::RWStepVisual_RWCameraModelD2() = default;

void RWStepVisual_RWCameraModelD2::ReadStep(const occ::handle<StepData_StepReaderData>&  data,
                                            const int                                    num,
                                            occ::handle<Interface_Check>&                ach,
                                            const occ::handle<StepVisual_CameraModelD2>& ent) const
{

  if (!data->CheckNbParams(num, 3, ach, "camera_model_d2"))
    return;

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<StepVisual_PlanarBox> aViewWindow;

  data->ReadEntity(num, 2, "view_window", ach, STANDARD_TYPE(StepVisual_PlanarBox), aViewWindow);

  bool aViewWindowClipping;

  data->ReadBoolean(num, 3, "view_window_clipping", ach, aViewWindowClipping);

  ent->Init(aName, aViewWindow, aViewWindowClipping);
}

void RWStepVisual_RWCameraModelD2::WriteStep(StepData_StepWriter&                         SW,
                                             const occ::handle<StepVisual_CameraModelD2>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->ViewWindow());

  SW.SendBoolean(ent->ViewWindowClipping());
}

void RWStepVisual_RWCameraModelD2::Share(const occ::handle<StepVisual_CameraModelD2>& ent,
                                         Interface_EntityIterator&                    iter) const
{

  iter.GetOneItem(ent->ViewWindow());
}
