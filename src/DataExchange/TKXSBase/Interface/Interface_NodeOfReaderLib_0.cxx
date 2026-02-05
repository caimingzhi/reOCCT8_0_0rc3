#include <Interface_NodeOfReaderLib.hpp>

#include <Standard_Type.hpp>

#include <Interface_GlobalNodeOfReaderLib.hpp>
#include <Standard_Transient.hpp>
#include <Interface_ReaderModule.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ReaderLib.hpp>

Interface_NodeOfReaderLib::Interface_NodeOfReaderLib() = default;

void Interface_NodeOfReaderLib::AddNode(const occ::handle<Interface_GlobalNodeOfReaderLib>& anode)
{
  if (thenode == anode)
    return;
  if (thenext.IsNull())
  {
    if (thenode.IsNull())
      thenode = anode;
    else
    {
      thenext = new Interface_NodeOfReaderLib;
      thenext->AddNode(anode);
    }
  }
  else
    thenext->AddNode(anode);
}

const occ::handle<Interface_ReaderModule>& Interface_NodeOfReaderLib::Module() const
{
  return thenode->Module();
}

const occ::handle<Interface_Protocol>& Interface_NodeOfReaderLib::Protocol() const
{
  return thenode->Protocol();
}

const occ::handle<Interface_NodeOfReaderLib>& Interface_NodeOfReaderLib::Next() const
{
  return thenext;
}
