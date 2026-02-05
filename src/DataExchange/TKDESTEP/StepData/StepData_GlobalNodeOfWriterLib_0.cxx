#include <StepData_GlobalNodeOfWriterLib.hpp>

#include <Standard_Type.hpp>

#include <StepData_ReadWriteModule.hpp>
#include <StepData_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <StepData_WriterLib.hpp>
#include <StepData_NodeOfWriterLib.hpp>

StepData_GlobalNodeOfWriterLib::StepData_GlobalNodeOfWriterLib() = default;

void StepData_GlobalNodeOfWriterLib::Add(const occ::handle<StepData_ReadWriteModule>& amodule,
                                         const occ::handle<StepData_Protocol>&        aprotocol)
{
  if (themod == amodule)
    return;
  if (theprot == aprotocol)
    themod = amodule;
  else if (thenext.IsNull())
  {
    if (themod.IsNull())
    {
      themod  = amodule;
      theprot = aprotocol;
    }
    else
    {
      thenext = new StepData_GlobalNodeOfWriterLib;
      thenext->Add(amodule, aprotocol);
    }
  }
  else
    thenext->Add(amodule, aprotocol);
}

const occ::handle<StepData_ReadWriteModule>& StepData_GlobalNodeOfWriterLib::Module() const
{
  return themod;
}

const occ::handle<StepData_Protocol>& StepData_GlobalNodeOfWriterLib::Protocol() const
{
  return theprot;
}

const occ::handle<StepData_GlobalNodeOfWriterLib>& StepData_GlobalNodeOfWriterLib::Next() const
{
  return thenext;
}
