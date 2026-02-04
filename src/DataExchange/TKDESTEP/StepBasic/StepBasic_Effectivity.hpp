#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_Effectivity : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_Effectivity();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aid);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& aid);

  DEFINE_STANDARD_RTTIEXT(StepBasic_Effectivity, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theid;
};

