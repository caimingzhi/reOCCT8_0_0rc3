

#include <StepBasic_ApplicationContext.hpp>
#include <StepBasic_ApplicationProtocolDefinition.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ApplicationProtocolDefinition, Standard_Transient)

StepBasic_ApplicationProtocolDefinition::StepBasic_ApplicationProtocolDefinition() = default;

void StepBasic_ApplicationProtocolDefinition::Init(
  const occ::handle<TCollection_HAsciiString>&     aStatus,
  const occ::handle<TCollection_HAsciiString>&     aApplicationInterpretedModelSchemaName,
  const int                                        aApplicationProtocolYear,
  const occ::handle<StepBasic_ApplicationContext>& aApplication)
{

  status                                = aStatus;
  applicationInterpretedModelSchemaName = aApplicationInterpretedModelSchemaName;
  applicationProtocolYear               = aApplicationProtocolYear;
  application                           = aApplication;
}

void StepBasic_ApplicationProtocolDefinition::SetStatus(
  const occ::handle<TCollection_HAsciiString>& aStatus)
{
  status = aStatus;
}

occ::handle<TCollection_HAsciiString> StepBasic_ApplicationProtocolDefinition::Status() const
{
  return status;
}

void StepBasic_ApplicationProtocolDefinition::SetApplicationInterpretedModelSchemaName(
  const occ::handle<TCollection_HAsciiString>& aApplicationInterpretedModelSchemaName)
{
  applicationInterpretedModelSchemaName = aApplicationInterpretedModelSchemaName;
}

occ::handle<TCollection_HAsciiString> StepBasic_ApplicationProtocolDefinition::
  ApplicationInterpretedModelSchemaName() const
{
  return applicationInterpretedModelSchemaName;
}

void StepBasic_ApplicationProtocolDefinition::SetApplicationProtocolYear(
  const int aApplicationProtocolYear)
{
  applicationProtocolYear = aApplicationProtocolYear;
}

int StepBasic_ApplicationProtocolDefinition::ApplicationProtocolYear() const
{
  return applicationProtocolYear;
}

void StepBasic_ApplicationProtocolDefinition::SetApplication(
  const occ::handle<StepBasic_ApplicationContext>& aApplication)
{
  application = aApplication;
}

occ::handle<StepBasic_ApplicationContext> StepBasic_ApplicationProtocolDefinition::Application()
  const
{
  return application;
}
