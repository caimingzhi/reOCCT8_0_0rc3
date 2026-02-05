#include <StepData_NodeOfWriterLib.hpp>

#include <Standard_Type.hpp>

#include <StepData_GlobalNodeOfWriterLib.hpp>
#include <Standard_Transient.hpp>
#include <StepData_ReadWriteModule.hpp>
#include <StepData_Protocol.hpp>
#include <StepData_WriterLib.hpp>

StepData_NodeOfWriterLib::StepData_NodeOfWriterLib() = default;

void StepData_NodeOfWriterLib::AddNode(const occ::handle<StepData_GlobalNodeOfWriterLib>& anode)
{
  if (thenode == anode)
    return;
  if (thenext.IsNull())
  {
    if (thenode.IsNull())
      thenode = anode;
    else
    {
      thenext = new StepData_NodeOfWriterLib;
      thenext->AddNode(anode);
    }
  }
  else
    thenext->AddNode(anode);
}

const occ::handle<StepData_ReadWriteModule>& StepData_NodeOfWriterLib::Module() const
{
  return thenode->Module();
}

const occ::handle<StepData_Protocol>& StepData_NodeOfWriterLib::Protocol() const
{
  return thenode->Protocol();
}

const occ::handle<StepData_NodeOfWriterLib>& StepData_NodeOfWriterLib::Next() const
{
  return thenext;
}
