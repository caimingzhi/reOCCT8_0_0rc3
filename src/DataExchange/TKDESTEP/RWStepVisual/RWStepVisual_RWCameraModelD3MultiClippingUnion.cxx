#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepVisual_RWCameraModelD3MultiClippingUnion.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepVisual_CameraModelD3MultiClippingUnion.hpp>
#include <StepVisual_CameraModelD3MultiClippingUnionSelect.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=================================================================================================

RWStepVisual_RWCameraModelD3MultiClippingUnion::RWStepVisual_RWCameraModelD3MultiClippingUnion() =
  default;

//=================================================================================================

void RWStepVisual_RWCameraModelD3MultiClippingUnion::ReadStep(
  const occ::handle<StepData_StepReaderData>&                    data,
  const int                                                      num,
  occ::handle<Interface_Check>&                                  ach,
  const occ::handle<StepVisual_CameraModelD3MultiClippingUnion>& ent) const
{
  // Number of Parameter Control
  if (!data->CheckNbParams(num, 2, ach, "camera_model_d3_multi_clipping_union"))
    return;

  // Inherited field : name
  occ::handle<TCollection_HAsciiString> aName;
  data->ReadString(num, 1, "name", ach, aName);

  // Own field : shape_clipping
  occ::handle<NCollection_HArray1<StepVisual_CameraModelD3MultiClippingUnionSelect>> aShapeClipping;
  StepVisual_CameraModelD3MultiClippingUnionSelect                                   anEnt;
  int                                                                                nbSub;
  if (data->ReadSubList(num, 2, "shape_clipping", ach, nbSub))
  {
    int nbElements = data->NbParams(nbSub);
    aShapeClipping =
      new NCollection_HArray1<StepVisual_CameraModelD3MultiClippingUnionSelect>(1, nbElements);
    for (int i = 1; i <= nbElements; i++)
    {
      if (data->ReadEntity(nbSub, i, "shape_clipping", ach, anEnt))
        aShapeClipping->SetValue(i, anEnt);
    }
  }

  // Initialization of the read entity
  ent->Init(aName, aShapeClipping);
}

//=================================================================================================

void RWStepVisual_RWCameraModelD3MultiClippingUnion::WriteStep(
  StepData_StepWriter&                                           SW,
  const occ::handle<StepVisual_CameraModelD3MultiClippingUnion>& ent) const
{
  // Inherited field name
  SW.Send(ent->Name());

  // Own field: shape_clipping
  SW.OpenSub();
  for (int i = 1; i <= ent->ShapeClipping()->Length(); i++)
  {
    SW.Send(ent->ShapeClipping()->Value(i).Value());
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepVisual_RWCameraModelD3MultiClippingUnion::Share(
  const occ::handle<StepVisual_CameraModelD3MultiClippingUnion>& ent,
  Interface_EntityIterator&                                      iter) const
{
  // Own field: shape_clipping
  int i, nb = ent->ShapeClipping()->Length();
  for (i = 1; i <= nb; i++)
    iter.AddItem(ent->ShapeClipping()->Value(i).Value());
}
