#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWConnectedFaceSubSet.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_ConnectedFaceSubSet.hpp>
#include <StepShape_Face.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=================================================================================================

RWStepShape_RWConnectedFaceSubSet::RWStepShape_RWConnectedFaceSubSet() = default;

//=================================================================================================

void RWStepShape_RWConnectedFaceSubSet::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepShape_ConnectedFaceSubSet>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "connected_face_sub_set"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Inherited fields of ConnectedFaceSet

  occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> aConnectedFaceSet_CfsFaces;
  int                                                           sub2 = 0;
  if (data->ReadSubList(num, 2, "connected_face_set.cfs_faces", ach, sub2))
  {
    int num2                   = sub2;
    int nb0                    = data->NbParams(num2);
    aConnectedFaceSet_CfsFaces = new NCollection_HArray1<occ::handle<StepShape_Face>>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepShape_Face> anIt0;
      data->ReadEntity(num2,
                       i0,
                       "connected_face_set.cfs_faces",
                       ach,
                       STANDARD_TYPE(StepShape_Face),
                       anIt0);
      aConnectedFaceSet_CfsFaces->SetValue(i0, anIt0);
    }
  }

  // Own fields of ConnectedFaceSubSet

  occ::handle<StepShape_ConnectedFaceSet> aParentFaceSet;
  data->ReadEntity(num,
                   3,
                   "parent_face_set",
                   ach,
                   STANDARD_TYPE(StepShape_ConnectedFaceSet),
                   aParentFaceSet);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aConnectedFaceSet_CfsFaces, aParentFaceSet);
}

//=================================================================================================

void RWStepShape_RWConnectedFaceSubSet::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepShape_ConnectedFaceSubSet>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Inherited fields of ConnectedFaceSet

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->StepShape_ConnectedFaceSet::CfsFaces()->Length(); i1++)
  {
    occ::handle<StepShape_Face> Var0 = ent->StepShape_ConnectedFaceSet::CfsFaces()->Value(i1);
    SW.Send(Var0);
  }
  SW.CloseSub();

  // Own fields of ConnectedFaceSubSet

  SW.Send(ent->ParentFaceSet());
}

//=================================================================================================

void RWStepShape_RWConnectedFaceSubSet::Share(const occ::handle<StepShape_ConnectedFaceSubSet>& ent,
                                              Interface_EntityIterator& iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of ConnectedFaceSet

  for (int i1 = 1; i1 <= ent->StepShape_ConnectedFaceSet::CfsFaces()->Length(); i1++)
  {
    occ::handle<StepShape_Face> Var0 = ent->StepShape_ConnectedFaceSet::CfsFaces()->Value(i1);
    iter.AddItem(Var0);
  }

  // Own fields of ConnectedFaceSubSet

  iter.AddItem(ent->ParentFaceSet());
}
