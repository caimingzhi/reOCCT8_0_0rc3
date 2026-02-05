#include <IGESData_NodeOfWriterLib.hpp>

#include <Standard_Type.hpp>

#include <IGESData_GlobalNodeOfWriterLib.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_ReadWriteModule.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_WriterLib.hpp>

IGESData_NodeOfWriterLib::IGESData_NodeOfWriterLib() = default;

void IGESData_NodeOfWriterLib::AddNode(const occ::handle<IGESData_GlobalNodeOfWriterLib>& anode)
{
  if (thenode == anode)
    return;
  if (thenext.IsNull())
  {
    if (thenode.IsNull())
      thenode = anode;
    else
    {
      thenext = new IGESData_NodeOfWriterLib;
      thenext->AddNode(anode);
    }
  }
  else
    thenext->AddNode(anode);
}

const occ::handle<IGESData_ReadWriteModule>& IGESData_NodeOfWriterLib::Module() const
{
  return thenode->Module();
}

const occ::handle<IGESData_Protocol>& IGESData_NodeOfWriterLib::Protocol() const
{
  return thenode->Protocol();
}

const occ::handle<IGESData_NodeOfWriterLib>& IGESData_NodeOfWriterLib::Next() const
{
  return thenext;
}
