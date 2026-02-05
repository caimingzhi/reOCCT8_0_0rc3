#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_ApplicationContext : public Standard_Transient
{

public:
  //! Returns a ApplicationContext
  Standard_EXPORT StepBasic_ApplicationContext();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aApplication);

  Standard_EXPORT void SetApplication(const occ::handle<TCollection_HAsciiString>& aApplication);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Application() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ApplicationContext, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> application;
};
