#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_DerivedUnitElement.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class StepBasic_DerivedUnitElement;

class StepBasic_DerivedUnit : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_DerivedUnit();

  Standard_EXPORT void Init(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>>& elements);

  Standard_EXPORT void SetElements(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>>& elements);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>>
                  Elements() const;

  Standard_EXPORT int NbElements() const;

  Standard_EXPORT occ::handle<StepBasic_DerivedUnitElement> ElementsValue(const int num) const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_DerivedUnit, Standard_Transient)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_DerivedUnitElement>>> theElements;
};
