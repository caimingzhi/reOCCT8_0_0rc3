#include <Standard_Transient.hpp>
#include <StepData_SelectArrReal.hpp>
#include <StepFEA_SymmetricTensor22d.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

//=================================================================================================

StepFEA_SymmetricTensor22d::StepFEA_SymmetricTensor22d() = default;

//=================================================================================================

int StepFEA_SymmetricTensor22d::CaseNum(const occ::handle<Standard_Transient>& ent) const
{
  if (ent.IsNull())
    return 0;
  if (ent->IsKind(STANDARD_TYPE(StepData_SelectArrReal)))
    return 1;
  return 0;
}

//=================================================================================================

occ::handle<NCollection_HArray1<double>> StepFEA_SymmetricTensor22d::AnisotropicSymmetricTensor22d()
  const
{
  // return occ::down_cast<NCollection_HArray1<double>>(Value());
  occ::handle<StepData_SelectArrReal> SSR = occ::down_cast<StepData_SelectArrReal>(Value());
  if (SSR.IsNull())
    return new NCollection_HArray1<double>(1, 3);
  return SSR->ArrReal();
}
