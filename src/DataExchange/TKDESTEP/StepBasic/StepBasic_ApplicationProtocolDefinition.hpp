#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_ApplicationContext;

#ifdef Status
  #undef Status
#endif

class StepBasic_ApplicationProtocolDefinition : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ApplicationProtocolDefinition();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&     aStatus,
    const occ::handle<TCollection_HAsciiString>&     aApplicationInterpretedModelSchemaName,
    const int                                        aApplicationProtocolYear,
    const occ::handle<StepBasic_ApplicationContext>& aApplication);

  Standard_EXPORT void SetStatus(const occ::handle<TCollection_HAsciiString>& aStatus);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Status() const;

  Standard_EXPORT void SetApplicationInterpretedModelSchemaName(
    const occ::handle<TCollection_HAsciiString>& aApplicationInterpretedModelSchemaName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ApplicationInterpretedModelSchemaName()
    const;

  Standard_EXPORT void SetApplicationProtocolYear(const int aApplicationProtocolYear);

  Standard_EXPORT int ApplicationProtocolYear() const;

  Standard_EXPORT void SetApplication(
    const occ::handle<StepBasic_ApplicationContext>& aApplication);

  Standard_EXPORT occ::handle<StepBasic_ApplicationContext> Application() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_ApplicationProtocolDefinition, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>     status;
  occ::handle<TCollection_HAsciiString>     applicationInterpretedModelSchemaName;
  int                                       applicationProtocolYear;
  occ::handle<StepBasic_ApplicationContext> application;
};
