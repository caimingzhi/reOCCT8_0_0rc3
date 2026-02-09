#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCameraModelD3MultiClippingIntersection.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CameraModelD3MultiClippingIntersection.hpp>
#include <StepVisual_CameraModelD3MultiClippingInterectionSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepVisual_RWCameraModelD3MultiClippingIntersection::
  RWStepVisual_RWCameraModelD3MultiClippingIntersection() = default;

void RWStepVisual_RWCameraModelD3MultiClippingIntersection::ReadStep(
  const occ::handle<StepData_StepReaderData>&                           data,
  const int                                                             num,
  occ::handle<Interface_Check>&                                         ach,
  const occ::handle<StepVisual_CameraModelD3MultiClippingIntersection>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "camera_model_d3_multi_clipping_intersection"))
    return;

  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingInterectionSelect>>
                                                         aShapeClipping;
  StepVisual_CameraModelD3MultiClippingInterectionSelect anEnt;
  int                                                    nbSub;
  if (data->ReadSubList(num, 2, "shape_clipping", ach, nbSub))
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

  ent->Init(aName, aShapeClipping);
}

void RWStepVisual_RWCameraModelD3MultiClippingIntersection::WriteStep(
  StepData_StepWriter&                                                  SW,
  const occ::handle<StepVisual_CameraModelD3MultiClippingIntersection>& ent) const
{

  SW.Send(ent->Name());

  SW.OpenSub();
  for (int i = 1; i <= ent->ShapeClipping()->Length(); i++)
  {
    SW.Send(ent->ShapeClipping()->Value(i).Value());
  }
  SW.CloseSub();
}

void RWStepVisual_RWCameraModelD3MultiClippingIntersection::Share(
  const occ::handle<StepVisual_CameraModelD3MultiClippingIntersection>& ent,
  Interface_EntityIterator&                                             iter) const
{

  int i, nb = ent->ShapeClipping()->Length();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->ShapeClipping()->Value(i).Value());
}
