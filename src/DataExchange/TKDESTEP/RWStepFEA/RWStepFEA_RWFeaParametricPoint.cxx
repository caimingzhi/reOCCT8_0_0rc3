#include <Interface_Check.hpp>
#include <Interface_EntityIterator.hpp>
#include "RWStepFEA_RWFeaParametricPoint.hpp"
#include <Standard_Real.hpp>
#include <StepData_StepReaderData.hpp>
#include <StepData_StepWriter.hpp>
#include <StepFEA_FeaParametricPoint.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

RWStepFEA_RWFeaParametricPoint::RWStepFEA_RWFeaParametricPoint() = default;

void RWStepFEA_RWFeaParametricPoint::ReadStep(
  const occ::handle<StepData_StepReaderData>&    data,
  const int                                      num,
  occ::handle<Interface_Check>&                  ach,
  const occ::handle<StepFEA_FeaParametricPoint>& ent) const
{

  if (!data->CheckNbParams(num, 2, ach, "fea_parametric_point"))
    return;

  occ::handle<TCollection_HAsciiString> aRepresentationItem_Name;
  data->ReadString(num, 1, "representation_item.name", ach, aRepresentationItem_Name);

  occ::handle<NCollection_HArray1<double>> aCoordinates;
  int                                      sub2 = 0;
  if (data->ReadSubList(num, 2, "coordinates", ach, sub2))
  {
    int nb0      = data->NbParams(sub2);
    aCoordinates = new NCollection_HArray1<double>(1, nb0);
    int num2     = sub2;
    for (int i0 = 1; i0 <= nb0; i0++)
    {
      double anIt0;
      data->ReadReal(num2, i0, "real", ach, anIt0);
      aCoordinates->SetValue(i0, anIt0);
    }
  }

  ent->Init(aRepresentationItem_Name, aCoordinates);
}

void RWStepFEA_RWFeaParametricPoint::WriteStep(
  StepData_StepWriter&                           SW,
  const occ::handle<StepFEA_FeaParametricPoint>& ent) const
{

  SW.Send(ent->StepRepr_RepresentationItem::Name());

  SW.OpenSub();
  for (int i1 = 1; i1 <= ent->Coordinates()->Length(); i1++)
  {
    double Var0 = ent->Coordinates()->Value(i1);
    SW.Send(Var0);
  }
  SW.CloseSub();
}

void RWStepFEA_RWFeaParametricPoint::Share(const occ::handle<StepFEA_FeaParametricPoint>&,
                                           Interface_EntityIterator&) const
{
}
