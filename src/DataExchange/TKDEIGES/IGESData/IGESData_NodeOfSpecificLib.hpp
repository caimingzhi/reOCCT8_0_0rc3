#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IGESData_GlobalNodeOfSpecificLib;
class IGESData_IGESEntity;
class IGESData_SpecificModule;
class IGESData_Protocol;
class IGESData_SpecificLib;

class IGESData_NodeOfSpecificLib : public Standard_Transient
{

public:
  //! Creates an empty Node, with no Next
  Standard_EXPORT IGESData_NodeOfSpecificLib();

  //! Adds a couple (Module,Protocol), that is, stores it into
  //! itself if not yet done, else creates a Next Node to do it
  Standard_EXPORT void AddNode(const occ::handle<IGESData_GlobalNodeOfSpecificLib>& anode);

  //! Returns the Module designated by a precise Node
  Standard_EXPORT const occ::handle<IGESData_SpecificModule>& Module() const;

  //! Returns the Protocol designated by a precise Node
  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

  //! Returns the Next Node. If none was defined, returned value
  //! is a Null Handle
  Standard_EXPORT const occ::handle<IGESData_NodeOfSpecificLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(IGESData_NodeOfSpecificLib, Standard_Transient)

private:
  occ::handle<IGESData_GlobalNodeOfSpecificLib> thenode;
  occ::handle<IGESData_NodeOfSpecificLib>       thenext;
};
