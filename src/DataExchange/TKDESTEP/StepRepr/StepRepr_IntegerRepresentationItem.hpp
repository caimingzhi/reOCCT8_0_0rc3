#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class TCollection_HAsciiString;

class StepRepr_IntegerRepresentationItem : public StepRepr_RepresentationItem
{

public:
  Standard_EXPORT StepRepr_IntegerRepresentationItem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const int                                    theValue);

  inline void SetValue(const int theValue) { value = theValue; }

  inline int Value() const { return value; }

  DEFINE_STANDARD_RTTIEXT(StepRepr_IntegerRepresentationItem, StepRepr_RepresentationItem)

private:
  int value;
};
