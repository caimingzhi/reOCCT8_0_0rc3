#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Interface_Graph;
class Interface_Check;
class Interface_InterfaceModel;

class Interface_Protocol : public Standard_Transient
{

public:
  Standard_EXPORT static occ::handle<Interface_Protocol> Active();

  Standard_EXPORT static void SetActive(const occ::handle<Interface_Protocol>& aprotocol);

  Standard_EXPORT static void ClearActive();

  Standard_EXPORT virtual int NbResources() const = 0;

  Standard_EXPORT virtual occ::handle<Interface_Protocol> Resource(const int num) const = 0;

  Standard_EXPORT virtual int CaseNumber(const occ::handle<Standard_Transient>& obj) const;

  Standard_EXPORT virtual bool IsDynamicType(const occ::handle<Standard_Transient>& obj) const;

  Standard_EXPORT virtual int NbTypes(const occ::handle<Standard_Transient>& obj) const;

  Standard_EXPORT occ::handle<Standard_Type> Type(const occ::handle<Standard_Transient>& obj,
                                                  const int nt = 1) const;

  Standard_EXPORT virtual int TypeNumber(const occ::handle<Standard_Type>& atype) const = 0;

  Standard_EXPORT virtual bool GlobalCheck(const Interface_Graph&        G,
                                           occ::handle<Interface_Check>& ach) const;

  Standard_EXPORT virtual occ::handle<Interface_InterfaceModel> NewModel() const = 0;

  Standard_EXPORT virtual bool IsSuitableModel(
    const occ::handle<Interface_InterfaceModel>& model) const = 0;

  Standard_EXPORT virtual occ::handle<Standard_Transient> UnknownEntity() const = 0;

  Standard_EXPORT virtual bool IsUnknownEntity(
    const occ::handle<Standard_Transient>& ent) const = 0;

  DEFINE_STANDARD_RTTIEXT(Interface_Protocol, Standard_Transient)
};
