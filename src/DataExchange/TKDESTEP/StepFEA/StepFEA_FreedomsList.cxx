#include <StepFEA_FreedomsList.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepFEA_FreedomsList, Standard_Transient)

StepFEA_FreedomsList::StepFEA_FreedomsList() = default;

void StepFEA_FreedomsList::Init(
  const occ::handle<NCollection_HArray1<StepFEA_DegreeOfFreedom>>& aFreedoms)
{

  theFreedoms = aFreedoms;
}

occ::handle<NCollection_HArray1<StepFEA_DegreeOfFreedom>> StepFEA_FreedomsList::Freedoms() const
{
  return theFreedoms;
}

void StepFEA_FreedomsList::SetFreedoms(
  const occ::handle<NCollection_HArray1<StepFEA_DegreeOfFreedom>>& aFreedoms)
{
  theFreedoms = aFreedoms;
}
