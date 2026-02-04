#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepData_GlobalNodeOfWriterLib;
class Standard_Transient;
class StepData_ReadWriteModule;
class StepData_Protocol;
class StepData_WriterLib;

class StepData_NodeOfWriterLib : public Standard_Transient
{

public:
  //! Creates an empty Node, with no Next
  Standard_EXPORT StepData_NodeOfWriterLib();

  //! Adds a couple (Module,Protocol), that is, stores it into
  //! itself if not yet done, else creates a Next Node to do it
  Standard_EXPORT void AddNode(const occ::handle<StepData_GlobalNodeOfWriterLib>& anode);

  //! Returns the Module designated by a precise Node
  Standard_EXPORT const occ::handle<StepData_ReadWriteModule>& Module() const;

  //! Returns the Protocol designated by a precise Node
  Standard_EXPORT const occ::handle<StepData_Protocol>& Protocol() const;

  //! Returns the Next Node. If none was defined, returned value
  //! is a Null Handle
  Standard_EXPORT const occ::handle<StepData_NodeOfWriterLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(StepData_NodeOfWriterLib, Standard_Transient)

private:
  occ::handle<StepData_GlobalNodeOfWriterLib> thenode;
  occ::handle<StepData_NodeOfWriterLib>       thenext;
};

