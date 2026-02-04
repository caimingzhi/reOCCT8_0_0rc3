#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepRepr_RepresentationItem;

//! Added from StepRepr Rev2 to Rev4
class StepRepr_ItemDefinedTransformation : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_ItemDefinedTransformation();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    aName,
                            const occ::handle<TCollection_HAsciiString>&    aDescription,
                            const occ::handle<StepRepr_RepresentationItem>& aTransformItem1,
                            const occ::handle<StepRepr_RepresentationItem>& aTransformItem2);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  bool HasDescription() const { return !theDescription.IsNull(); }

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetTransformItem1(const occ::handle<StepRepr_RepresentationItem>& aItem);

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> TransformItem1() const;

  Standard_EXPORT void SetTransformItem2(const occ::handle<StepRepr_RepresentationItem>& aItem);

  Standard_EXPORT occ::handle<StepRepr_RepresentationItem> TransformItem2() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_ItemDefinedTransformation, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>    theName;
  occ::handle<TCollection_HAsciiString>    theDescription;
  occ::handle<StepRepr_RepresentationItem> theTransformItem1;
  occ::handle<StepRepr_RepresentationItem> theTransformItem2;
};

