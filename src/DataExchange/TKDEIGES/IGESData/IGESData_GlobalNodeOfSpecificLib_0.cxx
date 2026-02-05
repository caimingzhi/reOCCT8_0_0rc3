#include <IGESData_GlobalNodeOfSpecificLib.hpp>

#include <Standard_Type.hpp>

#include <IGESData_SpecificModule.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_SpecificLib.hpp>
#include <IGESData_NodeOfSpecificLib.hpp>

IGESData_GlobalNodeOfSpecificLib::IGESData_GlobalNodeOfSpecificLib() = default;

void IGESData_GlobalNodeOfSpecificLib::Add(const occ::handle<IGESData_SpecificModule>& amodule,
                                           const occ::handle<IGESData_Protocol>&       aprotocol)
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
      thenext = new IGESData_GlobalNodeOfSpecificLib;
      thenext->Add(amodule, aprotocol);
    }
  }
  else
    thenext->Add(amodule, aprotocol);
}

const occ::handle<IGESData_SpecificModule>& IGESData_GlobalNodeOfSpecificLib::Module() const
{
  return themod;
}

const occ::handle<IGESData_Protocol>& IGESData_GlobalNodeOfSpecificLib::Protocol() const
{
  return theprot;
}

const occ::handle<IGESData_GlobalNodeOfSpecificLib>& IGESData_GlobalNodeOfSpecificLib::Next() const
{
  return thenext;
}
