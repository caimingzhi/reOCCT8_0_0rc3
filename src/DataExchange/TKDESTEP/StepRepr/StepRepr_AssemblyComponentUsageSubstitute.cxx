

#include <StepRepr_AssemblyComponentUsage.hpp>
#include <StepRepr_AssemblyComponentUsageSubstitute.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_AssemblyComponentUsageSubstitute, Standard_Transient)

StepRepr_AssemblyComponentUsageSubstitute::StepRepr_AssemblyComponentUsageSubstitute() = default;

void StepRepr_AssemblyComponentUsageSubstitute::Init(
  const occ::handle<TCollection_HAsciiString>&        aName,
  const occ::handle<TCollection_HAsciiString>&        aDef,
  const occ::handle<StepRepr_AssemblyComponentUsage>& aBase,
  const occ::handle<StepRepr_AssemblyComponentUsage>& aSubs)
{
  theName = aName;
  theDef  = aDef;
  theBase = aBase;
  theSubs = aSubs;
}

occ::handle<TCollection_HAsciiString> StepRepr_AssemblyComponentUsageSubstitute::Name() const
{
  return theName;
}

void StepRepr_AssemblyComponentUsageSubstitute::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_AssemblyComponentUsageSubstitute::Definition() const
{
  return theDef;
}

void StepRepr_AssemblyComponentUsageSubstitute::SetDefinition(
  const occ::handle<TCollection_HAsciiString>& aDefinition)
{
  theDef = aDefinition;
}

occ::handle<StepRepr_AssemblyComponentUsage> StepRepr_AssemblyComponentUsageSubstitute::Base() const
{
  return theBase;
}

void StepRepr_AssemblyComponentUsageSubstitute::SetBase(
  const occ::handle<StepRepr_AssemblyComponentUsage>& aBase)
{
  theBase = aBase;
}

occ::handle<StepRepr_AssemblyComponentUsage> StepRepr_AssemblyComponentUsageSubstitute::Substitute()
  const
{
  return theSubs;
}

void StepRepr_AssemblyComponentUsageSubstitute::SetSubstitute(
  const occ::handle<StepRepr_AssemblyComponentUsage>& aSubs)
{
  theSubs = aSubs;
}
