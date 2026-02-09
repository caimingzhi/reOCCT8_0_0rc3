

#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWDerivedUnit.hpp"
#include <StepBasic_DerivedUnit.hpp>
#include <StepBasic_DerivedUnitElement.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>

RWStepBasic_RWDerivedUnit::RWStepBasic_RWDerivedUnit() = default;

void RWStepBasic_RWDerivedUnit::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepBasic_DerivedUnit>&   ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "derived_unit"))
    return;

  occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>> elts;
  occ::handle<StepBasic_DerivedUnitElement>                                   anelt;
  int                                                                         nsub1;
  if (data->ReadSubList(num, 1, "elements", ach, nsub1))
  {
    int nb1 = data->NbParams(nsub1);
    elts    = new NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>(1, nb1);
    for (int i1 = 1; i1 <= nb1; i1++)
    {

      if (data->ReadEntity(nsub1,
                           i1,
                           "element",
                           ach,
                           STANDARD_TYPE(StepBasic_DerivedUnitElement),
                           anelt))
        elts->SetValue(i1, anelt);
    }
  }

  ent->Init(elts);
}

void RWStepBasic_RWDerivedUnit::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepBasic_DerivedUnit>& ent) const
{

  int i, nb = ent->NbElements();
  SW.OpenSub();
  for (i = 1; i <= nb; i++)
  {
    SW.Send(ent->ElementsValue(i));
  }
  SW.CloseSub();
}

void RWStepBasic_RWDerivedUnit::Share(const occ::handle<StepBasic_DerivedUnit>& ent,
                                      Interface_EntityIterator&                 iter) const
{

  int i, nb = ent->NbElements();
  for (i = 1; i <= nb; i++)
  {
    iter.GetOneItem(ent->ElementsValue(i));
  }
}
