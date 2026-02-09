#include <Standard_Transient.hpp>
#include <StepData_SelectArrReal.hpp>
#include <StepFEA_SymmetricTensor42d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

StepFEA_SymmetricTensor42d::StepFEA_SymmetricTensor42d() = default;

int StepFEA_SymmetricTensor42d::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepData_SelectArrReal)))
    return 1;
  return 0;
}

occ::handle<NCollection_HArray1<double>> StepFEA_SymmetricTensor42d::AnisotropicSymmetricTensor42d()
  const
{

  occ::handle<StepData_SelectArrReal> SSR = occ::down_cast<StepData_SelectArrReal>(Value());
  if (SSR.IsNull())
    return new NCollection_HArray1<double>(1, 6);
  return SSR->ArrReal();
}
