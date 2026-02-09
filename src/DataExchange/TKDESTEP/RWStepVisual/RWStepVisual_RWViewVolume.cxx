

#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWViewVolume.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_CartesianPoint.hpp>
#include <StepVisual_PlanarBox.hpp>
#include <StepVisual_ViewVolume.hpp>
#include <TCollection_AsciiString.hpp>

#include "RWStepVisual_RWCentralOrParallel.hpp"

RWStepVisual_RWViewVolume::RWStepVisual_RWViewVolume() = default;

void RWStepVisual_RWViewVolume::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepVisual_ViewVolume>&   ent) const
{

  if (!data->CheckNbParams(num, 9, ach, "view_volume"))
    return;

  StepVisual_CentralOrParallel aProjectionType = StepVisual_copCentral;
  if (data->ParamType(num, 1) == Interface_ParamEnum)
  {
    const char* text = data->ParamCValue(num, 1);
    if (!RWStepVisual_RWCentralOrParallel::ConvertToEnum(text, aProjectionType))
    {
      ach->AddFail("Enumeration central_or_parallel has not an allowed value");
    }
  }
  else
    ach->AddFail("Parameter #1 (projection_type) is not an enumeration");

  occ::handle<StepGeom_CartesianPoint> aProjectionPoint;

  data->ReadEntity(num,
                   2,
                   "projection_point",
                   ach,
                   STANDARD_TYPE(StepGeom_CartesianPoint),
                   aProjectionPoint);

  double aViewPlaneDistance;

  data->ReadReal(num, 3, "view_plane_distance", ach, aViewPlaneDistance);

  double aFrontPlaneDistance;

  data->ReadReal(num, 4, "front_plane_distance", ach, aFrontPlaneDistance);

  bool aFrontPlaneClipping;

  data->ReadBoolean(num, 5, "front_plane_clipping", ach, aFrontPlaneClipping);

  double aBackPlaneDistance;

  data->ReadReal(num, 6, "back_plane_distance", ach, aBackPlaneDistance);

  bool aBackPlaneClipping;

  data->ReadBoolean(num, 7, "back_plane_clipping", ach, aBackPlaneClipping);

  bool aViewVolumeSidesClipping;

  data->ReadBoolean(num, 8, "view_volume_sides_clipping", ach, aViewVolumeSidesClipping);

  occ::handle<StepVisual_PlanarBox> aViewWindow;

  data->ReadEntity(num, 9, "view_window", ach, STANDARD_TYPE(StepVisual_PlanarBox), aViewWindow);

  ent->Init(aProjectionType,
            aProjectionPoint,
            aViewPlaneDistance,
            aFrontPlaneDistance,
            aFrontPlaneClipping,
            aBackPlaneDistance,
            aBackPlaneClipping,
            aViewVolumeSidesClipping,
            aViewWindow);
}

void RWStepVisual_RWViewVolume::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepVisual_ViewVolume>& ent) const
{

  SW.SendEnum(RWStepVisual_RWCentralOrParallel::ConvertToString(ent->ProjectionType()));

  SW.Send(ent->ProjectionPoint());

  SW.Send(ent->ViewPlaneDistance());

  SW.Send(ent->FrontPlaneDistance());

  SW.SendBoolean(ent->FrontPlaneClipping());

  SW.Send(ent->BackPlaneDistance());

  SW.SendBoolean(ent->BackPlaneClipping());

  SW.SendBoolean(ent->ViewVolumeSidesClipping());

  SW.Send(ent->ViewWindow());
}

void RWStepVisual_RWViewVolume::Share(const occ::handle<StepVisual_ViewVolume>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  iter.GetOneItem(ent->ProjectionPoint());

  iter.GetOneItem(ent->ViewWindow());
}
