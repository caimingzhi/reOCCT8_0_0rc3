

#include <Interface_CopyMap.hpp>
#include <Interface_InterfaceError.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Interface_CopyMap, Interface_CopyControl)

Interface_CopyMap::Interface_CopyMap(const occ::handle<Interface_InterfaceModel>& amodel)
    : theres(0, amodel->NbEntities())
{
  themod = amodel;
}

void Interface_CopyMap::Clear()
{
  int                             nb = theres.Upper();
  occ::handle<Standard_Transient> bid;
  for (int i = 1; i <= nb; i++)
    theres.SetValue(i, bid);
}

occ::handle<Interface_InterfaceModel> Interface_CopyMap::Model() const
{
  return themod;
}

void Interface_CopyMap::Bind(const occ::handle<Standard_Transient>& ent,
                             const occ::handle<Standard_Transient>& res)
{
  int num = themod->Number(ent);
  if (num == 0 || num > theres.Upper())
    throw Interface_InterfaceError(
      "CopyMap : Bind, Starting Entity not issued from Starting Model");
  if (!theres.Value(num).IsNull())
    throw Interface_InterfaceError("CopyMap : Bind, Starting Entity already bound");
  theres.SetValue(num, res);
}

bool Interface_CopyMap::Search(const occ::handle<Standard_Transient>& ent,
                               occ::handle<Standard_Transient>&       res) const
{
  int num = themod->Number(ent);
  if (num == 0)
    return false;
  res = theres.Value(num);
  return (!res.IsNull());
}
