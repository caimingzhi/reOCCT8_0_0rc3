#include <IGESData_NodeOfSpecificLib.hpp>

#include <Standard_Type.hpp>

#include <IGESData_GlobalNodeOfSpecificLib.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_SpecificModule.hpp>
#include <IGESData_Protocol.hpp>
#include <IGESData_SpecificLib.hpp>

IGESData_NodeOfSpecificLib::IGESData_NodeOfSpecificLib() = default;

void IGESData_NodeOfSpecificLib::AddNode(const occ::handle<IGESData_GlobalNodeOfSpecificLib>& anode)
{
  if (thenode == anode)
    return;
  if (thenext.IsNull())
  {
    if (thenode.IsNull())
      thenode = anode;
    else
    {
      thenext = new IGESData_NodeOfSpecificLib;
      thenext->AddNode(anode);
    }
  }
  else
    thenext->AddNode(anode);
}

const occ::handle<IGESData_SpecificModule>& IGESData_NodeOfSpecificLib::Module() const
{
  return thenode->Module();
}

const occ::handle<IGESData_Protocol>& IGESData_NodeOfSpecificLib::Protocol() const
{
  return thenode->Protocol();
}

const occ::handle<IGESData_NodeOfSpecificLib>& IGESData_NodeOfSpecificLib::Next() const
{
  return thenext;
}
