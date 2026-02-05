#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class TCollection_HAsciiString;

class StepRepr_RealRepresentationItem : public StepRepr_RepresentationItem
{

public:
  //! Returns a RealRepresentationItem
  Standard_EXPORT StepRepr_RealRepresentationItem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theName,
                            const double                                 theValue);

  inline void SetValue(const double theValue) { value = theValue; }

  inline double Value() const { return value; }

  DEFINE_STANDARD_RTTIEXT(StepRepr_RealRepresentationItem, StepRepr_RepresentationItem)

private:
  double value;
};
