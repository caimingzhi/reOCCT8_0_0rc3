#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFreedomsList.hpp"
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FreedomsList.hpp>
#include <StepFEA_DegreeOfFreedom.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=================================================================================================

RWStepFEA_RWFreedomsList::RWStepFEA_RWFreedomsList() = default;

//=================================================================================================

void RWStepFEA_RWFreedomsList::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                        const int                                   num,
                                        occ::handle<Interface_Check>&               ach,
                                        const occ::handle<StepFEA_FreedomsList>&    ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 1, ach, "freedoms_list"))
    return;

  // Own fields of FreedomsList

  occ::handle<NCollection_HArray1<StepFEA_DegreeOfFreedom>> aFreedoms;
  int                                                       sub1 = 0;
  if (data->ReadSubList(num, 1, "freedoms", ach, sub1))
  {
    int nb0   = data->NbParams(sub1);
    aFreedoms = new NCollection_HArray1<StepFEA_DegreeOfFreedom>(1, nb0);
    int num2  = sub1;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      StepFEA_DegreeOfFreedom anIt0;
      data->ReadEntity(num2, i0, "degree_of_freedom", ach, anIt0);
      aFreedoms->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aFreedoms);
}

//=================================================================================================

void RWStepFEA_RWFreedomsList::WriteStep(StepData_StepWriter&                     SW,
                                         const occ::handle<StepFEA_FreedomsList>& ent) const
{

  // Own fields of FreedomsList

  SW.OpenSub();
  for (int i0 = 1; i0 <= ent->Freedoms()->Length(); i0++)
  {
    StepFEA_DegreeOfFreedom Var0 = ent->Freedoms()->Value(i0);
    SW.Send(Var0.Value());
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepFEA_RWFreedomsList::Share(const occ::handle<StepFEA_FreedomsList>& ent,
                                     Interface_EntityIterator&                iter) const
{

  // Own fields of FreedomsList

  for (int i1 = 1; i1 <= ent->Freedoms()->Length(); i1++)
  {
    StepFEA_DegreeOfFreedom Var0 = ent->Freedoms()->Value(i1);
    iter.AddItem(Var0.Value());
  }
}
