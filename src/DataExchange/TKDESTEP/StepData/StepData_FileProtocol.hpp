#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <StepData_Protocol.hpp>
#include <Standard_Integer.hpp>
class Interface_Protocol;
class Interface_Graph;
class Interface_Check;

class StepData_FileProtocol : public StepData_Protocol
{

public:
  Standard_EXPORT StepData_FileProtocol();

  Standard_EXPORT void Add(const occ::handle<StepData_Protocol>& protocol);

  Standard_EXPORT int NbResources() const override;

  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  Standard_EXPORT bool GlobalCheck(const Interface_Graph&        G,
                                   occ::handle<Interface_Check>& ach) const override;

  Standard_EXPORT const char* SchemaName(
    const occ::handle<Interface_InterfaceModel>& theModel) const override;

  DEFINE_STANDARD_RTTIEXT(StepData_FileProtocol, StepData_Protocol)

private:
  NCollection_Sequence<occ::handle<Standard_Transient>> thecomps;
};
