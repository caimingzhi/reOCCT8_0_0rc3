#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepData_ReadWriteModule;
class StepData_Protocol;
class Standard_Transient;
class StepData_WriterLib;
class StepData_NodeOfWriterLib;

class StepData_GlobalNodeOfWriterLib : public Standard_Transient
{

public:
  Standard_EXPORT StepData_GlobalNodeOfWriterLib();

  Standard_EXPORT void Add(const occ::handle<StepData_ReadWriteModule>& amodule,
                           const occ::handle<StepData_Protocol>&        aprotocol);

  Standard_EXPORT const occ::handle<StepData_ReadWriteModule>& Module() const;

  Standard_EXPORT const occ::handle<StepData_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<StepData_GlobalNodeOfWriterLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(StepData_GlobalNodeOfWriterLib, Standard_Transient)

private:
  occ::handle<StepData_ReadWriteModule>       themod;
  occ::handle<StepData_Protocol>              theprot;
  occ::handle<StepData_GlobalNodeOfWriterLib> thenext;
};
