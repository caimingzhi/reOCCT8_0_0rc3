#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_ShapeAspect;

class StepRepr_ShapeAspectRelationship : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_ShapeAspectRelationship();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<StepRepr_ShapeAspect>&     aRelatingShapeAspect,
                            const occ::handle<StepRepr_ShapeAspect>&     aRelatedShapeAspect);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> RelatingShapeAspect() const;

  Standard_EXPORT void SetRelatingShapeAspect(
    const occ::handle<StepRepr_ShapeAspect>& RelatingShapeAspect);

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> RelatedShapeAspect() const;

  Standard_EXPORT void SetRelatedShapeAspect(
    const occ::handle<StepRepr_ShapeAspect>& RelatedShapeAspect);

  DEFINE_STANDARD_RTTIEXT(StepRepr_ShapeAspectRelationship, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<StepRepr_ShapeAspect>     theRelatingShapeAspect;
  occ::handle<StepRepr_ShapeAspect>     theRelatedShapeAspect;
  bool                                  defDescription;
};
