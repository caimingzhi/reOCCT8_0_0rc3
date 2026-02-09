#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESData_NodeOfSpecificLib;
class Standard_NoSuchObject;
class IGESData_IGESEntity;
class IGESData_SpecificModule;
class IGESData_Protocol;
class IGESData_GlobalNodeOfSpecificLib;
class Standard_Transient;

class IGESData_SpecificLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void SetGlobal(const occ::handle<IGESData_SpecificModule>& amodule,
                                        const occ::handle<IGESData_Protocol>&       aprotocol);

  Standard_EXPORT IGESData_SpecificLib(const occ::handle<IGESData_Protocol>& aprotocol);

  Standard_EXPORT IGESData_SpecificLib();

  Standard_EXPORT void AddProtocol(const occ::handle<Standard_Transient>& aprotocol);

  Standard_EXPORT void Clear();

  Standard_EXPORT void SetComplete();

  Standard_EXPORT bool Select(const occ::handle<IGESData_IGESEntity>& obj,
                              occ::handle<IGESData_SpecificModule>&   module,
                              int&                                    CN) const;

  Standard_EXPORT void Start();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const occ::handle<IGESData_SpecificModule>& Module() const;

  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

private:
  occ::handle<IGESData_NodeOfSpecificLib> thelist;
  occ::handle<IGESData_NodeOfSpecificLib> thecurr;
};
