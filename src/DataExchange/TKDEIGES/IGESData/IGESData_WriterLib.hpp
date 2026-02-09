#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class IGESData_NodeOfWriterLib;
class Standard_NoSuchObject;
class IGESData_IGESEntity;
class IGESData_ReadWriteModule;
class IGESData_Protocol;
class IGESData_GlobalNodeOfWriterLib;
class Standard_Transient;

class IGESData_WriterLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void SetGlobal(const occ::handle<IGESData_ReadWriteModule>& amodule,
                                        const occ::handle<IGESData_Protocol>&        aprotocol);

  Standard_EXPORT IGESData_WriterLib(const occ::handle<IGESData_Protocol>& aprotocol);

  Standard_EXPORT IGESData_WriterLib();

  Standard_EXPORT void AddProtocol(const occ::handle<Standard_Transient>& aprotocol);

  Standard_EXPORT void Clear();

  Standard_EXPORT void SetComplete();

  Standard_EXPORT bool Select(const occ::handle<IGESData_IGESEntity>& obj,
                              occ::handle<IGESData_ReadWriteModule>&  module,
                              int&                                    CN) const;

  Standard_EXPORT void Start();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const occ::handle<IGESData_ReadWriteModule>& Module() const;

  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

private:
  occ::handle<IGESData_NodeOfWriterLib> thelist;
  occ::handle<IGESData_NodeOfWriterLib> thecurr;
};
