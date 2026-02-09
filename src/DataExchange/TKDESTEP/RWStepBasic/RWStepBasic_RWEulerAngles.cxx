#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepBasic_RWEulerAngles.hpp"
#include <Standard_Real.hpp>
#include <StepBasic_EulerAngles.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepBasic_RWEulerAngles::RWStepBasic_RWEulerAngles() = default;

void RWStepBasic_RWEulerAngles::ReadStep(const occ::handle<StepData_StepReaderData>& data,
                                         const int                                   num,
                                         occ::handle<Interface_Check>&               ach,
                                         const occ::handle<StepBasic_EulerAngles>&   ent) const
{

  if (!data->CheckNbParams(num, 1, ach, "euler_angles"))
    return;

  occ::handle<NCollection_HArray1<double>> aAngles;
  int                                      sub1 = 0;
  if (data->ReadSubList(num, 1, "angles", ach, sub1))
  {
    int nb0  = data->NbParams(sub1);
    aAngles  = new NCollection_HArray1<double>(1, nb0);
    int num2 = sub1;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      double anIt0;
      data->ReadReal(num2, i0, "real", ach, anIt0);
      aAngles->SetValue(i0, anIt0);
    }
  }

  ent->Init(aAngles);
}

void RWStepBasic_RWEulerAngles::WriteStep(StepData_StepWriter&                      SW,
                                          const occ::handle<StepBasic_EulerAngles>& ent) const
{

  SW.OpenSub();
  for (int i0 = 1; i0 <= ent->Angles()->Length(); i0++)
  {
    double Var0 = ent->Angles()->Value(i0);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

void RWStepBasic_RWEulerAngles::Share(const occ::handle<StepBasic_EulerAngles>&,
                                      Interface_EntityIterator&) const
{
}
