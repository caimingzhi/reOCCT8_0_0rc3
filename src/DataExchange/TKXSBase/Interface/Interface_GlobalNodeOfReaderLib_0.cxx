#include <Interface_GlobalNodeOfReaderLib.hpp>

#include <Standard_Type.hpp>

#include <Interface_ReaderModule.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Interface_ReaderLib.hpp>
#include <Interface_NodeOfReaderLib.hpp>

Interface_GlobalNodeOfReaderLib::Interface_GlobalNodeOfReaderLib() = default;

void Interface_GlobalNodeOfReaderLib::Add(const occ::handle<Interface_ReaderModule>& amodule,
                                          const occ::handle<Interface_Protocol>&     aprotocol)
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
      thenext = new Interface_GlobalNodeOfReaderLib;
      thenext->Add(amodule, aprotocol);
    }
  }
  else
    thenext->Add(amodule, aprotocol);
}

const occ::handle<Interface_ReaderModule>& Interface_GlobalNodeOfReaderLib::Module() const
{
  return themod;
}

const occ::handle<Interface_Protocol>& Interface_GlobalNodeOfReaderLib::Protocol() const
{
  return theprot;
}

const occ::handle<Interface_GlobalNodeOfReaderLib>& Interface_GlobalNodeOfReaderLib::Next() const
{
  return thenext;
}
