#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Interface_GlobalNodeOfGeneralLib;
class Standard_Transient;
class Interface_GeneralModule;
class Interface_Protocol;
class Interface_GeneralLib;

class Interface_NodeOfGeneralLib : public Standard_Transient
{

public:
  Standard_EXPORT Interface_NodeOfGeneralLib();

  Standard_EXPORT void AddNode(const occ::handle<Interface_GlobalNodeOfGeneralLib>& anode);

  Standard_EXPORT const occ::handle<Interface_GeneralModule>& Module() const;

  Standard_EXPORT const occ::handle<Interface_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<Interface_NodeOfGeneralLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(Interface_NodeOfGeneralLib, Standard_Transient)

private:
  occ::handle<Interface_GlobalNodeOfGeneralLib> thenode;
  occ::handle<Interface_NodeOfGeneralLib>       thenext;
};
