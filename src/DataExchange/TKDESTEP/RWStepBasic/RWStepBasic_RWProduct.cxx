

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWProduct.hpp"
#include <StepBasic_Product.hpp>
#include <StepBasic_ProductContext.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWProduct::RWStepBasic_RWProduct() = default;

void RWStepBasic_RWProduct::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                     const int                                   num,
                                     occ::handle<Interface_Check>&               ach,
                                     const occ::handle<StepBasic_Product>&       ent) const
{

  if (!data->CheckNbParams(num, 4, ach, "product"))
    return;

  occ::handle<TCollection_HAsciiString> aId;

  data->ReadString(num, 1, "id", ach, aId);

  occ::handle<TCollection_HAsciiString> aName;

  data->ReadString(num, 2, "name", ach, aName);

  occ::handle<TCollection_HAsciiString> aDescription;
  if (data->IsParamDefined(num, 3))
  {

    data->ReadString(num, 3, "description", ach, aDescription);
  }

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_ProductContext>>> aFrameOfReference;
  occ::handle<StepBasic_ProductContext>                                   anent4;
  int                                                                     nsub4;
  if (data->ReadSubList(num, 4, "frame_of_reference", ach, nsub4))
  {
    int nb4           = data->NbParams(nsub4);
    aFrameOfReference = new NCollection_HArray1<occ::handle<StepBasic_ProductContext>>(1, nb4);
    for (int i4 = 1; i4 <= nb4; i4++)
    {

      if (data->ReadEntity(nsub4,
                           i4,
                           "product_context",
                           ach,
                           STANDARD_TYPE(StepBasic_ProductContext),
                           anent4))
        aFrameOfReference->SetValue(i4, anent4);
    }
  }

  ent->Init(aId, aName, aDescription, aFrameOfReference);
}

void RWStepBasic_RWProduct::WriteStep(StepData_StepWriter&                  SW,
                                      const occ::handle<StepBasic_Product>& ent) const
{

  SW.Send(ent->Id());

  SW.Send(ent->Name());

  if (!ent->Description().IsNull())
  {
    SW.Send(ent->Description());
  }
  else
  {
    SW.SendUndef();
  }

  SW.OpenSub();
  for (int i4 = 1; i4 <= ent->NbFrameOfReference(); i4++)
  {
    SW.Send(ent->FrameOfReferenceValue(i4));
  }
  SW.CloseSub();
}

void RWStepBasic_RWProduct::Share(const occ::handle<StepBasic_Product>& ent,
                                  Interface_EntityIterator&             iter) const
{

  int nbElem1 = ent->NbFrameOfReference();
  for (int is1 = 1; is1 <= nbElem1; is1++)
  {
    iter.GetOneItem(ent->FrameOfReferenceValue(is1));
  }
}
