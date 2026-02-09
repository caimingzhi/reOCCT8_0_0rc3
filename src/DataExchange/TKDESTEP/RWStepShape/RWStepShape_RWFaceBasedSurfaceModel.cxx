#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWFaceBasedSurfaceModel.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_FaceBasedSurfaceModel.hpp>
#include <StepShape_ConnectedFaceSet.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepShape_RWFaceBasedSurfaceModel::RWStepShape_RWFaceBasedSurfaceModel() = default;

void RWStepShape_RWFaceBasedSurfaceModel::ReadStep(
  const occ::handle<StepData_StepReaderData>&         data,
  const int                                           num,
  occ::handle<Interface_Check>&                       ach,
  const occ::handle<StepShape_FaceBasedSurfaceModel>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "face_based_surface_model"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>> aFbsmFaces;
  int                                                                       sub2 = 0;
  if (data->ReadSubList(num, 2, "fbsm_faces", ach, sub2))
  {
    int num2   = sub2;
    int nb0    = data->NbParams(num2);
    aFbsmFaces = new NCollection_HArray1<occ::handle<StepShape_ConnectedFaceSet>>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepShape_ConnectedFaceSet> anIt0;
      data
        ->ReadEntity(num2, i0, "fbsm_faces", ach, STANDARD_TYPE(StepShape_ConnectedFaceSet), anIt0);
      aFbsmFaces->SetValue(i0, anIt0);
    }
  }

  ent->Init(aRepresentationItem_Name, aFbsmFaces);
}

void RWStepShape_RWFaceBasedSurfaceModel::WriteStep(
  StepData_StepWriter&                                SW,
  const occ::handle<StepShape_FaceBasedSurfaceModel>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->FbsmFaces()->Length(); i1++)
  {
    occ::handle<StepShape_ConnectedFaceSet> Var0 = ent->FbsmFaces()->Value(i1);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

void RWStepShape_RWFaceBasedSurfaceModel::Share(
  const occ::handle<StepShape_FaceBasedSurfaceModel>& ent,
  Interface_EntityIterator&                           iter) const
{

  for (int i1 = 1; i1 <= ent->FbsmFaces()->Length(); i1++)
  {
    occ::handle<StepShape_ConnectedFaceSet> Var0 = ent->FbsmFaces()->Value(i1);
    iter.AddItem(Var0);
  }
}
