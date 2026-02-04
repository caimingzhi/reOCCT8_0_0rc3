#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Interface_Protocol.hpp>
#include <Standard_Integer.hpp>
class Interface_InterfaceModel;
class Standard_Transient;

//! Description of basic Protocol for IGES
//! This comprises treatment of IGESModel and Recognition of
//! Undefined-FreeFormat-Entity
class IGESData_Protocol : public Interface_Protocol
{

public:
  Standard_EXPORT IGESData_Protocol();

  //! Gives the count of Resource Protocol. Here, none
  Standard_EXPORT int NbResources() const override;

  //! Returns a Resource, given a rank. Here, none
  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  //! Returns a Case Number, specific of each recognized Type
  //! Here, Undefined and Free Format Entities have the Number 1.
  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  //! Creates an empty Model for IGES Norm
  Standard_EXPORT occ::handle<Interface_InterfaceModel> NewModel() const override;

  //! Returns True if <model> is a Model of IGES Norm
  Standard_EXPORT bool IsSuitableModel(
    const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Creates a new Unknown Entity for IGES (UndefinedEntity)
  Standard_EXPORT occ::handle<Standard_Transient> UnknownEntity() const override;

  //! Returns True if <ent> is an Unknown Entity for the Norm, i.e.
  //! Type UndefinedEntity, status Unknown
  Standard_EXPORT bool IsUnknownEntity(const occ::handle<Standard_Transient>& ent) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_Protocol, Interface_Protocol)
};

