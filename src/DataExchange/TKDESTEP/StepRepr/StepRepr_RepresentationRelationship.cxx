

#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentationRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_RepresentationRelationship, Standard_Transient)

StepRepr_RepresentationRelationship::StepRepr_RepresentationRelationship() = default;

void StepRepr_RepresentationRelationship::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const occ::handle<StepRepr_Representation>&  aRep1,
  const occ::handle<StepRepr_Representation>&  aRep2)
{

  name        = aName;
  description = aDescription;
  rep1        = aRep1;
  rep2        = aRep2;
}

void StepRepr_RepresentationRelationship::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_RepresentationRelationship::Name() const
{
  return name;
}

void StepRepr_RepresentationRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepRepr_RepresentationRelationship::Description() const
{
  return description;
}

void StepRepr_RepresentationRelationship::SetRep1(const occ::handle<StepRepr_Representation>& aRep1)
{
  rep1 = aRep1;
}

occ::handle<StepRepr_Representation> StepRepr_RepresentationRelationship::Rep1() const
{
  return rep1;
}

void StepRepr_RepresentationRelationship::SetRep2(const occ::handle<StepRepr_Representation>& aRep2)
{
  rep2 = aRep2;
}

occ::handle<StepRepr_Representation> StepRepr_RepresentationRelationship::Rep2() const
{
  return rep2;
}
