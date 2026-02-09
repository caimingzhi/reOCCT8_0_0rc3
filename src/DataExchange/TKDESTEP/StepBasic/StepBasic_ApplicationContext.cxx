

#include <StepBasic_ApplicationContext.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApplicationContext, Standard_Transient)

StepBasic_ApplicationContext::StepBasic_ApplicationContext() = default;

void StepBasic_ApplicationContext::Init(const occ::handle<TCollection_HAsciiString>& aApplication)
{

  application = aApplication;
}

void StepBasic_ApplicationContext::SetApplication(
  const occ::handle<TCollection_HAsciiString>& aApplication)
{
  application = aApplication;
}

occ::handle<TCollection_HAsciiString> StepBasic_ApplicationContext::Application() const
{
  return application;
}
