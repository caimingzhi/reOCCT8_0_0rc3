#pragma once


#include <Standard.hpp>

#include <StepShape_ValueQualifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_ValueQualifier;

//! Added for Dimensional Tolerances
class StepShape_QualifiedRepresentationItem : public StepRepr_RepresentationItem
{

public:
  Standard_EXPORT StepShape_QualifiedRepresentationItem();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                      aName,
    const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> Qualifiers() const;

  Standard_EXPORT int NbQualifiers() const;

  Standard_EXPORT void SetQualifiers(
    const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers);

  Standard_EXPORT StepShape_ValueQualifier QualifiersValue(const int num) const;

  Standard_EXPORT void SetQualifiersValue(const int                       num,
                                          const StepShape_ValueQualifier& aqualifier);

  DEFINE_STANDARD_RTTIEXT(StepShape_QualifiedRepresentationItem, StepRepr_RepresentationItem)

private:
  occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> theQualifiers;
};

