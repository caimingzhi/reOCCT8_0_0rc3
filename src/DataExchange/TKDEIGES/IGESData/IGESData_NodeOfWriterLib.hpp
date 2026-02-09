#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IGESData_GlobalNodeOfWriterLib;
class IGESData_IGESEntity;
class IGESData_ReadWriteModule;
class IGESData_Protocol;
class IGESData_WriterLib;

class IGESData_NodeOfWriterLib : public Standard_Transient
{

public:
  Standard_EXPORT IGESData_NodeOfWriterLib();

  Standard_EXPORT void AddNode(const occ::handle<IGESData_GlobalNodeOfWriterLib>& anode);

  Standard_EXPORT const occ::handle<IGESData_ReadWriteModule>& Module() const;

  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

  Standard_EXPORT const occ::handle<IGESData_NodeOfWriterLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(IGESData_NodeOfWriterLib, Standard_Transient)

private:
  occ::handle<IGESData_GlobalNodeOfWriterLib> thenode;
  occ::handle<IGESData_NodeOfWriterLib>       thenext;
};
