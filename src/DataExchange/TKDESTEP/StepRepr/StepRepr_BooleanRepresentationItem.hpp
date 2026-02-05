#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class TCollection_HAsciiString;

class StepRepr_BooleanRepresentationItem : public StepRepr_RepresentationItem
{
public:
  //! Returns a BooleanRepresentationItem
  Standard_EXPORT StepRepr_BooleanRepresentationItem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const bool                                   theValue);

  inline void SetValue(const bool theValue) { value = theValue; }

  inline bool Value() const { return value; }

  DEFINE_STANDARD_RTTIEXT(StepRepr_BooleanRepresentationItem, StepRepr_RepresentationItem)

private:
  bool value;
};
