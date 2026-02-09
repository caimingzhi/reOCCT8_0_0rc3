#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepRepr_ShapeAspect;
class TCollection_HAsciiString;

class StepShape_DimensionalSize : public Standard_Transient
{

public:
  Standard_EXPORT StepShape_DimensionalSize();

  Standard_EXPORT void Init(const occ::handle<StepRepr_ShapeAspect>&     aAppliesTo,
                            const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> AppliesTo() const;

  Standard_EXPORT void SetAppliesTo(const occ::handle<StepRepr_ShapeAspect>& AppliesTo);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  DEFINE_STANDARD_RTTIEXT(StepShape_DimensionalSize, Standard_Transient)

private:
  occ::handle<StepRepr_ShapeAspect>     theAppliesTo;
  occ::handle<TCollection_HAsciiString> theName;
};
