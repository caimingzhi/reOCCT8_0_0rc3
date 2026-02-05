#include <IGESData_GlobalNodeOfWriterLib.hpp>

#include <Standard_Type.hpp>

#include <IGESData_ReadWriteModule.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_WriterLib.hpp>
#include <IGESData_NodeOfWriterLib.hpp>

IGESData_GlobalNodeOfWriterLib::IGESData_GlobalNodeOfWriterLib() = default;

void IGESData_GlobalNodeOfWriterLib::Add(const occ::handle<IGESData_ReadWriteModule>& amodule,
                                         const occ::handle<IGESData_Protocol>&        aprotocol)
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
      thenext = new IGESData_GlobalNodeOfWriterLib;
      thenext->Add(amodule, aprotocol);
    }
  }
  else
    thenext->Add(amodule, aprotocol);
}

const occ::handle<IGESData_ReadWriteModule>& IGESData_GlobalNodeOfWriterLib::Module() const
{
  return themod;
}

const occ::handle<IGESData_Protocol>& IGESData_GlobalNodeOfWriterLib::Protocol() const
{
  return theprot;
}

const occ::handle<IGESData_GlobalNodeOfWriterLib>& IGESData_GlobalNodeOfWriterLib::Next() const
{
  return thenext;
}
