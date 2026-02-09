

#include <StepRepr_ItemDefinedTransformation.hpp>
#include <StepRepr_RepresentationItem.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ItemDefinedTransformation, Standard_Transient)

StepRepr_ItemDefinedTransformation::StepRepr_ItemDefinedTransformation() = default;

void StepRepr_ItemDefinedTransformation::Init(
  const occ::handle<TCollection_HAsciiString>&    aName,
  const occ::handle<TCollection_HAsciiString>&    aDescription,
  const occ::handle<StepRepr_RepresentationItem>& aTransformItem1,
  const occ::handle<StepRepr_RepresentationItem>& aTransformItem2)
{
  theName           = aName;
  theDescription    = aDescription;
  theTransformItem1 = aTransformItem1;
  theTransformItem2 = aTransformItem2;
}

void StepRepr_ItemDefinedTransformation::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_ItemDefinedTransformation::Name() const
{
  return theName;
}

void StepRepr_ItemDefinedTransformation::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

occ::handle<TCollection_HAsciiString> StepRepr_ItemDefinedTransformation::Description() const
{
  return theDescription;
}

void StepRepr_ItemDefinedTransformation::SetTransformItem1(
  const occ::handle<StepRepr_RepresentationItem>& aTransformItem1)
{
  theTransformItem1 = aTransformItem1;
}

occ::handle<StepRepr_RepresentationItem> StepRepr_ItemDefinedTransformation::TransformItem1() const
{
  return theTransformItem1;
}

void StepRepr_ItemDefinedTransformation::SetTransformItem2(
  const occ::handle<StepRepr_RepresentationItem>& aTransformItem2)
{
  theTransformItem2 = aTransformItem2;
}

occ::handle<StepRepr_RepresentationItem> StepRepr_ItemDefinedTransformation::TransformItem2() const
{
  return theTransformItem2;
}
