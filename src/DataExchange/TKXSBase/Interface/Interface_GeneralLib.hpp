#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class Interface_NodeOfGeneralLib;
class Standard_NoSuchObject;
class Standard_Transient;
class Interface_GeneralModule;
class Interface_Protocol;
class Interface_GlobalNodeOfGeneralLib;

class Interface_GeneralLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void SetGlobal(const occ::handle<Interface_GeneralModule>& amodule,
                                        const occ::handle<Interface_Protocol>&      aprotocol);

  Standard_EXPORT Interface_GeneralLib(const occ::handle<Interface_Protocol>& aprotocol);

  Standard_EXPORT Interface_GeneralLib();

  Standard_EXPORT void AddProtocol(const occ::handle<Standard_Transient>& aprotocol);

  Standard_EXPORT void Clear();

  Standard_EXPORT void SetComplete();

  Standard_EXPORT bool Select(const occ::handle<Standard_Transient>& obj,
                              occ::handle<Interface_GeneralModule>&  module,
                              int&                                   CN) const;

  Standard_EXPORT void Start();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const occ::handle<Interface_GeneralModule>& Module() const;

  Standard_EXPORT const occ::handle<Interface_Protocol>& Protocol() const;

private:
  occ::handle<Interface_NodeOfGeneralLib> thelist;
  occ::handle<Interface_NodeOfGeneralLib> thecurr;
};
