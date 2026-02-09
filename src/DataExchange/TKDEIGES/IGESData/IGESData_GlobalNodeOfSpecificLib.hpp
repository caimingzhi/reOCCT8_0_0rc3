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
  Standard_EXPORT IGESData_GlobalNodeOfSpecificLib();

  Standard_EXPORT void Add(const occ::handle<IGESData_SpecificModule>& amodule,
                           const occ::handle<IGESData_Protocol>&       aprotocol);

  Standard_EXPORT const occ::handle<IGESData_SpecificModule>& Module() const;

  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<IGESData_GlobalNodeOfSpecificLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(IGESData_GlobalNodeOfSpecificLib, Standard_Transient)

private:
  occ::handle<IGESData_SpecificModule>          themod;
  occ::handle<IGESData_Protocol>                theprot;
  occ::handle<IGESData_GlobalNodeOfSpecificLib> thenext;
};
