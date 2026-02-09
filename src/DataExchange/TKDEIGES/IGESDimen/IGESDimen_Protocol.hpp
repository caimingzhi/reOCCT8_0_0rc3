#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_Protocol.hpp>
#include <Standard_Integer.hpp>
class Interface_Protocol;

class IGESDimen_Protocol : public IGESData_Protocol
{

public:
  Standard_EXPORT IGESDimen_Protocol();

  Standard_EXPORT int NbResources() const override;

  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_Protocol, IGESData_Protocol)
};
