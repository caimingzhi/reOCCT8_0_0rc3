#include <Interface_NodeOfGeneralLib.hpp>

#include <Standard_Type.hpp>

#include <Interface_GlobalNodeOfGeneralLib.hpp>
#include <Standard_Transient.hpp>
#include <Interface_GeneralModule.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_GeneralLib.hpp>

Interface_NodeOfGeneralLib::Interface_NodeOfGeneralLib() = default;

void Interface_NodeOfGeneralLib::AddNode(const occ::handle<Interface_GlobalNodeOfGeneralLib>& anode)
{
  if (thenode == anode)
    return;
  if (thenext.IsNull())
  {
    if (thenode.IsNull())
      thenode = anode;
    else
    {
      thenext = new Interface_NodeOfGeneralLib;
      thenext->AddNode(anode);
    }
  }
  else
    thenext->AddNode(anode);
}

const occ::handle<Interface_GeneralModule>& Interface_NodeOfGeneralLib::Module() const
{
  return thenode->Module();
}

const occ::handle<Interface_Protocol>& Interface_NodeOfGeneralLib::Protocol() const
{
  return thenode->Protocol();
}

const occ::handle<Interface_NodeOfGeneralLib>& Interface_NodeOfGeneralLib::Next() const
{
  return thenext;
}
