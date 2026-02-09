#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class Interface_GlobalNodeOfReaderLib;
class Standard_Transient;
class Interface_ReaderModule;
class Interface_Protocol;
class Interface_ReaderLib;

class Interface_NodeOfReaderLib : public Standard_Transient
{

public:
  Standard_EXPORT Interface_NodeOfReaderLib();

  Standard_EXPORT void AddNode(const occ::handle<Interface_GlobalNodeOfReaderLib>& anode);

  Standard_EXPORT const occ::handle<Interface_ReaderModule>& Module() const;

  Standard_EXPORT const occ::handle<Interface_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<Interface_NodeOfReaderLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(Interface_NodeOfReaderLib, Standard_Transient)

private:
  occ::handle<Interface_GlobalNodeOfReaderLib> thenode;
  occ::handle<Interface_NodeOfReaderLib>       thenext;
};
