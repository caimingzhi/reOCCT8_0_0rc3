#include <StepRepr_ShapeAspect.hpp>
#include <StepRepr_ShapeAspectRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_ShapeAspectRelationship, Standard_Transient)

//=================================================================================================

StepRepr_ShapeAspectRelationship::StepRepr_ShapeAspectRelationship()
{
  defDescription = false;
}

//=================================================================================================

void StepRepr_ShapeAspectRelationship::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const bool                                   hasDescription,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const occ::handle<StepRepr_ShapeAspect>&     aRelatingShapeAspect,
  const occ::handle<StepRepr_ShapeAspect>&     aRelatedShapeAspect)
{

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theRelatingShapeAspect = aRelatingShapeAspect;

  theRelatedShapeAspect = aRelatedShapeAspect;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_ShapeAspectRelationship::Name() const
{
  return theName;
}

//=================================================================================================

void StepRepr_ShapeAspectRelationship::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_ShapeAspectRelationship::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepRepr_ShapeAspectRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepRepr_ShapeAspectRelationship::HasDescription() const
{
  return defDescription;
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspect> StepRepr_ShapeAspectRelationship::RelatingShapeAspect() const
{
  return theRelatingShapeAspect;
}

//=================================================================================================

void StepRepr_ShapeAspectRelationship::SetRelatingShapeAspect(
  const occ::handle<StepRepr_ShapeAspect>& aRelatingShapeAspect)
{
  theRelatingShapeAspect = aRelatingShapeAspect;
}

//=================================================================================================

occ::handle<StepRepr_ShapeAspect> StepRepr_ShapeAspectRelationship::RelatedShapeAspect() const
{
  return theRelatedShapeAspect;
}

//=================================================================================================

void StepRepr_ShapeAspectRelationship::SetRelatedShapeAspect(
  const occ::handle<StepRepr_ShapeAspect>& aRelatedShapeAspect)
{
  theRelatedShapeAspect = aRelatedShapeAspect;
}
