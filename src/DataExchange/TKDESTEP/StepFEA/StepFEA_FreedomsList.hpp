#pragma once

#include <Standard.hpp>

#include <StepFEA_DegreeOfFreedom.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>

class StepFEA_FreedomsList : public Standard_Transient
{

public:
  Standard_EXPORT StepFEA_FreedomsList();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<StepFEA_DegreeOfFreedom>>& aFreedoms);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepFEA_DegreeOfFreedom>> Freedoms() const;

  Standard_EXPORT void SetFreedoms(
    const occ::handle<NCollection_HArray1<StepFEA_DegreeOfFreedom>>& Freedoms);

  DEFINE_STANDARD_RTTIEXT(StepFEA_FreedomsList, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<StepFEA_DegreeOfFreedom>> theFreedoms;
};
