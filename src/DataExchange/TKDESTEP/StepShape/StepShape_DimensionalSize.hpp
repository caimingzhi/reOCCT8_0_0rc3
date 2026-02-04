#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepRepr_ShapeAspect;
class TCollection_HAsciiString;

//! Representation of STEP entity DimensionalSize
class StepShape_DimensionalSize : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepShape_DimensionalSize();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepRepr_ShapeAspect>&     aAppliesTo,
                            const occ::handle<TCollection_HAsciiString>& aName);

  //! Returns field AppliesTo
  Standard_EXPORT occ::handle<StepRepr_ShapeAspect> AppliesTo() const;

  //! Set field AppliesTo
  Standard_EXPORT void SetAppliesTo(const occ::handle<StepRepr_ShapeAspect>& AppliesTo);

  //! Returns field Name
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  //! Set field Name
  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  DEFINE_STANDARD_RTTIEXT(StepShape_DimensionalSize, Standard_Transient)

private:
  occ::handle<StepRepr_ShapeAspect>     theAppliesTo;
  occ::handle<TCollection_HAsciiString> theName;
};

