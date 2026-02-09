#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IGESData_ReadWriteModule;
class IGESData_Protocol;
class IGESData_IGESEntity;
class IGESData_WriterLib;
class IGESData_NodeOfWriterLib;

class IGESData_GlobalNodeOfWriterLib : public Standard_Transient
{

public:
  Standard_EXPORT IGESData_GlobalNodeOfWriterLib();

  Standard_EXPORT void Add(const occ::handle<IGESData_ReadWriteModule>& amodule,
                           const occ::handle<IGESData_Protocol>&        aprotocol);

  Standard_EXPORT const occ::handle<IGESData_ReadWriteModule>& Module() const;

  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<IGESData_GlobalNodeOfWriterLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(IGESData_GlobalNodeOfWriterLib, Standard_Transient)

private:
  occ::handle<IGESData_ReadWriteModule>       themod;
  occ::handle<IGESData_Protocol>              theprot;
  occ::handle<IGESData_GlobalNodeOfWriterLib> thenext;
};
