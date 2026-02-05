#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_AssemblyComponentUsage;

class StepRepr_AssemblyComponentUsageSubstitute : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_AssemblyComponentUsageSubstitute();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&        aName,
                            const occ::handle<TCollection_HAsciiString>&        aDef,
                            const occ::handle<StepRepr_AssemblyComponentUsage>& aBase,
                            const occ::handle<StepRepr_AssemblyComponentUsage>& aSubs);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Definition() const;

  Standard_EXPORT void SetDefinition(const occ::handle<TCollection_HAsciiString>& aDef);

  Standard_EXPORT occ::handle<StepRepr_AssemblyComponentUsage> Base() const;

  Standard_EXPORT void SetBase(const occ::handle<StepRepr_AssemblyComponentUsage>& aBase);

  Standard_EXPORT occ::handle<StepRepr_AssemblyComponentUsage> Substitute() const;

  Standard_EXPORT void SetSubstitute(
    const occ::handle<StepRepr_AssemblyComponentUsage>& aSubstitute);

  DEFINE_STANDARD_RTTIEXT(StepRepr_AssemblyComponentUsageSubstitute, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>        theName;
  occ::handle<TCollection_HAsciiString>        theDef;
  occ::handle<StepRepr_AssemblyComponentUsage> theBase;
  occ::handle<StepRepr_AssemblyComponentUsage> theSubs;
};
