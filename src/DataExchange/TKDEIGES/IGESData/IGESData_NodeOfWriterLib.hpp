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
  //! Creates an empty Node, with no Next
  Standard_EXPORT IGESData_NodeOfWriterLib();

  //! Adds a couple (Module,Protocol), that is, stores it into
  //! itself if not yet done, else creates a Next Node to do it
  Standard_EXPORT void AddNode(const occ::handle<IGESData_GlobalNodeOfWriterLib>& anode);

  //! Returns the Module designated by a precise Node
  Standard_EXPORT const occ::handle<IGESData_ReadWriteModule>& Module() const;

  //! Returns the Protocol designated by a precise Node
  Standard_EXPORT const occ::handle<IGESData_Protocol>& Protocol() const;

  //! Returns the Next Node. If none was defined, returned value
  //! is a Null Handle
  Standard_EXPORT const occ::handle<IGESData_NodeOfWriterLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(IGESData_NodeOfWriterLib, Standard_Transient)

private:
  occ::handle<IGESData_GlobalNodeOfWriterLib> thenode;
  occ::handle<IGESData_NodeOfWriterLib>       thenext;
};

