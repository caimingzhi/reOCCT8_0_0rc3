#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_Protocol.hpp>
#include <Standard_Integer.hpp>
class Interface_Protocol;

class IGESData_FileProtocol : public IGESData_Protocol
{

public:
  Standard_EXPORT IGESData_FileProtocol();

  Standard_EXPORT void Add(const occ::handle<IGESData_Protocol>& protocol);

  Standard_EXPORT int NbResources() const override;

  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_FileProtocol, IGESData_Protocol)

private:
  occ::handle<IGESData_Protocol>     theresource;
  occ::handle<IGESData_FileProtocol> thenext;
};
