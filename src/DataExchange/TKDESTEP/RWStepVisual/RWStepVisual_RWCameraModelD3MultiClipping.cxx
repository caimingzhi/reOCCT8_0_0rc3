#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCameraModelD3MultiClipping.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepGeom_Axis2Placement3d.hpp>
#include <StepVisual_CameraModelD3MultiClipping.hpp>
#include <StepVisual_CameraModelD3MultiClippingInterectionSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepVisual_ViewVolume.hpp>

RWStepVisual_RWCameraModelD3MultiClipping::RWStepVisual_RWCameraModelD3MultiClipping() = default;

void RWStepVisual_RWCameraModelD3MultiClipping::ReadStep(
  const occ::handle<StepData_StepReaderData>&               data,
  const int                                                 num,
  occ::handle<Interface_Check>&                             ach,
  const occ::handle<StepVisual_CameraModelD3MultiClipping>& ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "camera_model_d3_multi_clipping"))
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

  occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>>
                                                         aShapeClipping;
  StepVisual_CameraModelD3MultiClippingInterectionSelect anEnt;
  int                                                    nbSub;
  if (data->ReadSubList(num, 4, "shape_clipping", ach, nbSub))
  {
    int nbElements = data->NbParams(nbSub);
    aShapeClipping =
      new NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>(1,
                                                                                      nbElements);
    for (int i = 1; i <= nbElements; i++)
    {
      if (data->ReadEntity(nbSub, i, "shape_clipping", ach, anEnt))
        aShapeClipping->SetValue(i, anEnt);
    }
  }

  ent->Init(aName, aViewReferenceSystem, aPerspectiveOfVolume, aShapeClipping);
}

void RWStepVisual_RWCameraModelD3MultiClipping::WriteStep(
  StepData_StepWriter&                                      SW,
  const occ::handle<StepVisual_CameraModelD3MultiClipping>& ent) const
{

  SW.Send(ent->Name());

  SW.Send(ent->ViewReferenceSystem());

  SW.Send(ent->PerspectiveOfVolume());

  SW.OpenSub();
  for (int i = 1; i <= ent->ShapeClipping()->Length(); i++)
  {
    SW.Send(ent->ShapeClipping()->Value(i).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWCameraModelD3MultiClipping::Share(
  const occ::handle<StepVisual_CameraModelD3MultiClipping>& ent,
  Interface_EntityIterator&                                 iter) const
{

  iter.GetOneItem(ent->ViewReferenceSystem());

  iter.GetOneItem(ent->PerspectiveOfVolume());

  int i, nb = ent->ShapeClipping()->Length();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->ShapeClipping()->Value(i).Value());
}
