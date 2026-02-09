#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
class StepData_NodeOfWriterLib;
class Standard_NoSuchObject;
class Standard_Transient;
class StepData_ReadWriteModule;
class StepData_Protocol;
class StepData_GlobalNodeOfWriterLib;

class StepData_WriterLib
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void SetGlobal(const occ::handle<StepData_ReadWriteModule>& amodule,
                                        const occ::handle<StepData_Protocol>&        aprotocol);

  Standard_EXPORT StepData_WriterLib(const occ::handle<StepData_Protocol>& aprotocol);

  Standard_EXPORT StepData_WriterLib();

  Standard_EXPORT void AddProtocol(const occ::handle<Standard_Transient>& aprotocol);

  Standard_EXPORT void Clear();

  Standard_EXPORT void SetComplete();

  Standard_EXPORT bool Select(const occ::handle<Standard_Transient>& obj,
                              occ::handle<StepData_ReadWriteModule>& module,
                              int&                                   CN) const;

  Standard_EXPORT void Start();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const occ::handle<StepData_ReadWriteModule>& Module() const;

  Standard_EXPORT const occ::handle<StepData_Protocol>& Protocol() const;

private:
  occ::handle<StepData_NodeOfWriterLib> thelist;
  occ::handle<StepData_NodeOfWriterLib> thecurr;
};
