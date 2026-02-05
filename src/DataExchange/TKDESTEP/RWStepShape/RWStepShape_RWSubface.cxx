#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepShape_RWSubface.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepShape_FaceBound.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepShape_Subface.hpp>

//=================================================================================================

RWStepShape_RWSubface::RWStepShape_RWSubface() = default;

//=================================================================================================

void RWStepShape_RWSubface::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepShape_Subface>&       ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 3, ach, "subface"))
    return;

  // Inherited fields of RepresentationItem

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  // Inherited fields of Face

  occ::handle<NCollection_HArray1<occ::handle<StepShape_FaceBound>>> aFace_Bounds;
  int                                                                sub2 = 0;
  if (data->ReadSubList(num, 2, "face.bounds", ach, sub2))
  {
    int num2     = sub2;
    int nb0      = data->NbParams(num2);
    aFace_Bounds = new NCollection_HArray1<occ::handle<StepShape_FaceBound>>(1, nb0);
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      occ::handle<StepShape_FaceBound> anIt0;
      data->ReadEntity(num2, i0, "face.bounds", ach, STANDARD_TYPE(StepShape_FaceBound), anIt0);
      aFace_Bounds->SetValue(i0, anIt0);
    }
  }

  // Own fields of Subface

  occ::handle<StepShape_Face> aParentFace;
  data->ReadEntity(num, 3, "parent_face", ach, STANDARD_TYPE(StepShape_Face), aParentFace);

  // Initialize entity
  ent->Init(aRepresentationItem_Name, aFace_Bounds, aParentFace);
}

//=================================================================================================

void RWStepShape_RWSubface::WriteStep(StepData_StepWriter&                  SW,
                                      const occ::handle<StepShape_Subface>& ent) const
{

  // Inherited fields of RepresentationItem

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  // Inherited fields of Face

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->StepShape_Face::Bounds()->Length(); i1++)
  {
    occ::handle<StepShape_FaceBound> Var0 = ent->StepShape_Face::Bounds()->Value(i1);
    SW.Send(Var0);
  }
  SW.CloseSub();

  // Own fields of Subface

  SW.Send(ent->ParentFace());
}

//=================================================================================================

void RWStepShape_RWSubface::Share(const occ::handle<StepShape_Subface>& ent,
                                  Interface_EntityIterator&             iter) const
{

  // Inherited fields of RepresentationItem

  // Inherited fields of Face

  for (int i1 = 1; i1 <= ent->StepShape_Face::Bounds()->Length(); i1++)
  {
    occ::handle<StepShape_FaceBound> Var0 = ent->StepShape_Face::Bounds()->Value(i1);
    iter.AddItem(Var0);
  }

  // Own fields of Subface

  iter.AddItem(ent->ParentFace());
}
