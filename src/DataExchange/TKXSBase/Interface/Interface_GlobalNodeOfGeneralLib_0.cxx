#include <Interface_GlobalNodeOfGeneralLib.hpp>

#include <Standard_Type.hpp>

#include <Interface_GeneralModule.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <Interface_GeneralLib.hpp>
#include <Interface_NodeOfGeneralLib.hpp>

Interface_GlobalNodeOfGeneralLib::Interface_GlobalNodeOfGeneralLib() = default;

void Interface_GlobalNodeOfGeneralLib::Add(const occ::handle<Interface_GeneralModule>& amodule,
                                           const occ::handle<Interface_Protocol>&      aprotocol)
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
      thenext = new Interface_GlobalNodeOfGeneralLib;
      thenext->Add(amodule, aprotocol);
    }
  }
  else
    thenext->Add(amodule, aprotocol);
}

const occ::handle<Interface_GeneralModule>& Interface_GlobalNodeOfGeneralLib::Module() const
{
  return themod;
}

const occ::handle<Interface_Protocol>& Interface_GlobalNodeOfGeneralLib::Protocol() const
{
  return theprot;
}

const occ::handle<Interface_GlobalNodeOfGeneralLib>& Interface_GlobalNodeOfGeneralLib::Next() const
{
  return thenext;
}
