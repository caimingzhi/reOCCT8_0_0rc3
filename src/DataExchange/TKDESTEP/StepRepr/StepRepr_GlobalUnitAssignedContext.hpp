#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationContext.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepBasic_NamedUnit;

class StepRepr_GlobalUnitAssignedContext : public StepRepr_RepresentationContext
{

public:
  //! Returns a GlobalUnitAssignedContext
  Standard_EXPORT StepRepr_GlobalUnitAssignedContext();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                              aContextIdentifier,
    const occ::handle<TCollection_HAsciiString>&                              aContextType,
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits);

  Standard_EXPORT void SetUnits(
    const occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>>& aUnits);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>> Units() const;

  Standard_EXPORT occ::handle<StepBasic_NamedUnit> UnitsValue(const int num) const;

  Standard_EXPORT int NbUnits() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_GlobalUnitAssignedContext, StepRepr_RepresentationContext)

private:
  occ::handle<NCollection_HArray1<occ::handle<StepBasic_NamedUnit>>> units;
};

