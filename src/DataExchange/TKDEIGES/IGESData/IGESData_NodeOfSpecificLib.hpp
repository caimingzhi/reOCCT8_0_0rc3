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
  Standard_EXPORT IGESData_NodeOfSpecificLib();

  Standard_EXPORT void AddNode(const occ::handle<IGESData_GlobalNodeOfSpecificLib>& anode);

  Standard_EXPORT const occ::handle<IGESData_SpecificModule>& Module() const;

  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<IGESData_NodeOfSpecificLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(IGESData_NodeOfSpecificLib, Standard_Transient)

private:
  occ::handle<IGESData_GlobalNodeOfSpecificLib> thenode;
  occ::handle<IGESData_NodeOfSpecificLib>       thenext;
};
