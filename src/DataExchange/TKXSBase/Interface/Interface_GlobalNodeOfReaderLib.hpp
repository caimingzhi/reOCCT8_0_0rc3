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
  //! Creates an empty GlobalNode, with no Next
  Standard_EXPORT Interface_GlobalNodeOfReaderLib();

  //! Adds a Module bound with a Protocol to the list : does
  //! nothing if already in the list, THAT IS, Same Type (exact
  //! match) and Same State (that is, IsEqual is not required)
  //! Once added, stores its attached Protocol in correspondence
  Standard_EXPORT void Add(const occ::handle<Interface_ReaderModule>& amodule,
                           const occ::handle<Interface_Protocol>&     aprotocol);

  //! Returns the Module stored in a given GlobalNode
  Standard_EXPORT const occ::handle<Interface_ReaderModule>& Module() const;

  //! Returns the attached Protocol stored in a given GlobalNode
  Standard_EXPORT const occ::handle<Interface_Protocol>& Protocol() const;

  //! Returns the Next GlobalNode. If none is defined, returned
  //! value is a Null Handle
  Standard_EXPORT const occ::handle<Interface_GlobalNodeOfReaderLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(Interface_GlobalNodeOfReaderLib, Standard_Transient)

private:
  occ::handle<Interface_ReaderModule>          themod;
  occ::handle<Interface_Protocol>              theprot;
  occ::handle<Interface_GlobalNodeOfReaderLib> thenext;
};
