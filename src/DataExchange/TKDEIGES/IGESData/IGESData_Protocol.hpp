#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_Protocol.hpp>
#include <Standard_Integer.hpp>
class Interface_InterfaceModel;
class Standard_Transient;

class IGESData_Protocol : public Interface_Protocol
{

public:
  Standard_EXPORT IGESData_Protocol();

  Standard_EXPORT int NbResources() const override;

  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewModel() const override;

  Standard_EXPORT bool IsSuitableModel(
    const occ::handle<Interface_InterfaceModel>& model) const override;

  Standard_EXPORT occ::handle<Standard_Transient> UnknownEntity() const override;

  Standard_EXPORT bool IsUnknownEntity(const occ::handle<Standard_Transient>& ent) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_Protocol, Interface_Protocol)
};
