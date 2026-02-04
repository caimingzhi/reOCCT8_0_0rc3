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
  //! Creates an empty GlobalNode, with no Next
  Standard_EXPORT StepData_GlobalNodeOfWriterLib();

  //! Adds a Module bound with a Protocol to the list : does
  //! nothing if already in the list, THAT IS, Same Type (exact
  //! match) and Same State (that is, IsEqual is not required)
  //! Once added, stores its attached Protocol in correspondence
  Standard_EXPORT void Add(const occ::handle<StepData_ReadWriteModule>& amodule,
                           const occ::handle<StepData_Protocol>&        aprotocol);

  //! Returns the Module stored in a given GlobalNode
  Standard_EXPORT const occ::handle<StepData_ReadWriteModule>& Module() const;

  //! Returns the attached Protocol stored in a given GlobalNode
  Standard_EXPORT const occ::handle<StepData_Protocol>& Protocol() const;

  //! Returns the Next GlobalNode. If none is defined, returned
  //! value is a Null Handle
  Standard_EXPORT const occ::handle<StepData_GlobalNodeOfWriterLib>& Next() const;

  DEFINE_STANDARD_RTTI_INLINE(StepData_GlobalNodeOfWriterLib, Standard_Transient)

private:
  occ::handle<StepData_ReadWriteModule>       themod;
  occ::handle<StepData_Protocol>              theprot;
  occ::handle<StepData_GlobalNodeOfWriterLib> thenext;
};

