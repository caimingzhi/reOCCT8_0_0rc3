#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Interface_GeneralModule;
class Interface_Protocol;
class Standard_Transient;
class Interface_GeneralLib;
class Interface_NodeOfGeneralLib;

class Interface_GlobalNodeOfGeneralLib : public Standard_Transient
{

public:
  Standard_EXPORT Interface_GlobalNodeOfGeneralLib();

  Standard_EXPORT void Add(const occ::handle<Interface_GeneralModule>& amodule,
                           const occ::handle<Interface_Protocol>&      aprotocol);

  Standard_EXPORT const occ::handle<Interface_GeneralModule>& Module() const;

  Standard_EXPORT const occ::handle<Interface_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<Interface_GlobalNodeOfGeneralLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(Interface_GlobalNodeOfGeneralLib, Standard_Transient)

private:
  occ::handle<Interface_GeneralModule>          themod;
  occ::handle<Interface_Protocol>               theprot;
  occ::handle<Interface_GlobalNodeOfGeneralLib> thenext;
};
