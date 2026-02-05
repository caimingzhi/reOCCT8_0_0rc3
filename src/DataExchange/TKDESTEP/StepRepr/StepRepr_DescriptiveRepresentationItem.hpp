#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepRepr_RepresentationItem.hpp>
class TCollection_HAsciiString;

class StepRepr_DescriptiveRepresentationItem : public StepRepr_RepresentationItem
{

public:
  //! Returns a DescriptiveRepresentationItem
  Standard_EXPORT StepRepr_DescriptiveRepresentationItem();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_DescriptiveRepresentationItem, StepRepr_RepresentationItem)

private:
  occ::handle<TCollection_HAsciiString> description;
};
