#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepRepr_RepresentationContext : public Standard_Transient
{

public:
  //! Returns a RepresentationContext
  Standard_EXPORT StepRepr_RepresentationContext();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aContextIdentifier,
                            const occ::handle<TCollection_HAsciiString>& aContextType);

  Standard_EXPORT void SetContextIdentifier(
    const occ::handle<TCollection_HAsciiString>& aContextIdentifier);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ContextIdentifier() const;

  Standard_EXPORT void SetContextType(const occ::handle<TCollection_HAsciiString>& aContextType);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ContextType() const;

  DEFINE_STANDARD_RTTIEXT(StepRepr_RepresentationContext, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> contextIdentifier;
  occ::handle<TCollection_HAsciiString> contextType;
};
