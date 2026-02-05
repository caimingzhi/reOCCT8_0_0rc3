#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IGESData_SpecificModule;
class IGESData_Protocol;
class IGESData_IGESEntity;
class IGESData_SpecificLib;
class IGESData_NodeOfSpecificLib;

class IGESData_GlobalNodeOfSpecificLib : public Standard_Transient
{

public:
  //! Creates an empty GlobalNode, with no Next
  Standard_EXPORT IGESData_GlobalNodeOfSpecificLib();

  //! Adds a Module bound with a Protocol to the list : does
  //! nothing if already in the list, THAT IS, Same Type (exact
  //! match) and Same State (that is, IsEqual is not required)
  //! Once added, stores its attached Protocol in correspondence
  Standard_EXPORT void Add(const occ::handle<IGESData_SpecificModule>& amodule,
                           const occ::handle<IGESData_Protocol>&       aprotocol);

  //! Returns the Module stored in a given GlobalNode
  Standard_EXPORT const occ::handle<IGESData_SpecificModule>& Module() const;

  //! Returns the attached Protocol stored in a given GlobalNode
  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

  //! Returns the Next GlobalNode. If none is defined, returned
  //! value is a Null Handle
  Standard_EXPORT const occ::handle<IGESData_GlobalNodeOfSpecificLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(IGESData_GlobalNodeOfSpecificLib, Standard_Transient)

private:
  occ::handle<IGESData_SpecificModule>          themod;
  occ::handle<IGESData_Protocol>                theprot;
  occ::handle<IGESData_GlobalNodeOfSpecificLib> thenext;
};
