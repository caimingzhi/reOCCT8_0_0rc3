#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Interface_ReaderModule;
class Interface_Protocol;
class Standard_Transient;
class Interface_ReaderLib;
class Interface_NodeOfReaderLib;

class Interface_GlobalNodeOfReaderLib : public Standard_Transient
{

public:
  Standard_EXPORT Interface_GlobalNodeOfReaderLib();

  Standard_EXPORT void Add(const occ::handle<Interface_ReaderModule>& amodule,
                           const occ::handle<Interface_Protocol>&     aprotocol);

  Standard_EXPORT const occ::handle<Interface_ReaderModule>& Module() const;

  Standard_EXPORT const occ::handle<Interface_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<Interface_GlobalNodeOfReaderLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(Interface_GlobalNodeOfReaderLib, Standard_Transient)

private:
  occ::handle<Interface_ReaderModule>          themod;
  occ::handle<Interface_Protocol>              theprot;
  occ::handle<Interface_GlobalNodeOfReaderLib> thenext;
};
