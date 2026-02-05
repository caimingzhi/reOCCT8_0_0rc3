#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWCurveElementEndOffset.hpp"
#include <Standard_Real.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_CurveElementEndOffset.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

//=================================================================================================

RWStepFEA_RWCurveElementEndOffset::RWStepFEA_RWCurveElementEndOffset() = default;

//=================================================================================================

void RWStepFEA_RWCurveElementEndOffset::ReadStep(
  const occ::handle<StepData_StepReaderData>&       data,
  const int                                         num,
  occ::handle<Interface_Check>&                     ach,
  const occ::handle<StepFEA_CurveElementEndOffset>& ent) const
{
  // Check number of parameters
  if (!data->CheckNbParams(num, 2, ach, "curve_element_end_offset"))
    return;

  // Own fields of CurveElementEndOffset

  StepFEA_CurveElementEndCoordinateSystem aCoordinateSystem;
  data->ReadEntity(num, 1, "coordinate_system", ach, aCoordinateSystem);

  occ::handle<NCollection_HArray1<double>> aOffsetVector;
  int                                      sub2 = 0;
  if (data->ReadSubList(num, 2, "offset_vector", ach, sub2))
  {
    int nb0       = data->NbParams(sub2);
    aOffsetVector = new NCollection_HArray1<double>(1, nb0);
    int num2      = sub2;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      double anIt0;
      data->ReadReal(num2, i0, "real", ach, anIt0);
      aOffsetVector->SetValue(i0, anIt0);
    }
  }

  // Initialize entity
  ent->Init(aCoordinateSystem, aOffsetVector);
}

//=================================================================================================

void RWStepFEA_RWCurveElementEndOffset::WriteStep(
  StepData_StepWriter&                              SW,
  const occ::handle<StepFEA_CurveElementEndOffset>& ent) const
{

  // Own fields of CurveElementEndOffset

  SW.Send(ent->CoordinateSystem().Value());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->OffsetVector()->Length(); i1++)
  {
    double Var0 = ent->OffsetVector()->Value(i1);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

//=================================================================================================

void RWStepFEA_RWCurveElementEndOffset::Share(const occ::handle<StepFEA_CurveElementEndOffset>& ent,
                                              Interface_EntityIterator& iter) const
{

  // Own fields of CurveElementEndOffset

  iter.AddItem(ent->CoordinateSystem().Value());
}
