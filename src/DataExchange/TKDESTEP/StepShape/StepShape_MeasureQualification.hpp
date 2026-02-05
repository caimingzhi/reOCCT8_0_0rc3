#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ValueQualifier.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_ValueQualifier;

//! Added for Dimensional Tolerances
class StepShape_MeasureQualification : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_MeasureQualification();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                      name,
    const occ::handle<TCollection_HAsciiString>&                      description,
    const occ::handle<Standard_Transient>&                            qualified_measure,
    const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& description);

  Standard_EXPORT occ::handle<Standard_Transient> QualifiedMeasure() const;

  Standard_EXPORT void SetQualifiedMeasure(
    const occ::handle<Standard_Transient>& qualified_measure);

  Standard_EXPORT occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> Qualifiers() const;

  Standard_EXPORT int NbQualifiers() const;

  Standard_EXPORT void SetQualifiers(
    const occ::handle<NCollection_HArray1<StepShape_ValueQualifier>>& qualifiers);

  Standard_EXPORT StepShape_ValueQualifier QualifiersValue(const int num) const;

  Standard_EXPORT void SetQualifiersValue(const int                       num,
                                          const StepShape_ValueQualifier& aqualifier);

  DEFINE_STANDARD_RTTIEXT(StepShape_MeasureQualification, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                      theName;
  occ::handle<TCollection_HAsciiString>                      theDescription;
  occ::handle<Standard_Transient>                            theQualifiedMeasure;
  occ::handle<NCollection_HArray1<StepShape_ValueQualifier>> theQualifiers;
};
