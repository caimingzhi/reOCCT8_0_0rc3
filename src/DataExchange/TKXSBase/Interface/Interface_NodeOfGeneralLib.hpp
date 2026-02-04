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
  //! Creates an empty Node, with no Next
  Standard_EXPORT Interface_NodeOfGeneralLib();

  //! Adds a couple (Module,Protocol), that is, stores it into
  //! itself if not yet done, else creates a Next Node to do it
  Standard_EXPORT void AddNode(const occ::handle<Interface_GlobalNodeOfGeneralLib>& anode);

  //! Returns the Module designated by a precise Node
  Standard_EXPORT const occ::handle<Interface_GeneralModule>& Module() const;

  //! Returns the Protocol designated by a precise Node
  Standard_EXPORT const occ::handle<Interface_Protocol>& Protocol() const;

  //! Returns the Next Node. If none was defined, returned value
  //! is a Null Handle
  Standard_EXPORT const occ::handle<Interface_NodeOfGeneralLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(Interface_NodeOfGeneralLib, Standard_Transient)

private:
  occ::handle<Interface_GlobalNodeOfGeneralLib> thenode;
  occ::handle<Interface_NodeOfGeneralLib>       thenext;
};

