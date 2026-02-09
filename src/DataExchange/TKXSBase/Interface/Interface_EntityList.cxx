

#include <Interface_EntityCluster.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_EntityList.hpp>
#include <Interface_InterfaceError.hpp>
#include <Standard_NullObject.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_Transient.hpp>

Interface_EntityList::Interface_EntityList() = default;

void Interface_EntityList::Clear()
{
  theval.Nullify();
}

void Interface_EntityList::Append(const occ::handle<Standard_Transient>& ent)
{
  if (ent.IsNull())
    throw Standard_NullObject("Interface_EntityList Append");
  if (theval.IsNull())
  {
    theval = ent;
    return;
  }
  occ::handle<Interface_EntityCluster> aValEC = occ::down_cast<Interface_EntityCluster>(theval);
  if (!aValEC.IsNull())
    aValEC->Append(ent);
  else
  {
    occ::handle<Interface_EntityCluster> ec = new Interface_EntityCluster(theval);
    ec->Append(ent);
    theval = ec;
  }
}

void Interface_EntityList::Add(const occ::handle<Standard_Transient>& ent)
{
  if (ent.IsNull())
    throw Standard_NullObject("Interface_EntityList Add");
  if (theval.IsNull())
  {
    theval = ent;
    return;
  }
  occ::handle<Interface_EntityCluster> aValEC = occ::down_cast<Interface_EntityCluster>(theval);
  if (!aValEC.IsNull())
  {
    if (aValEC->IsLocalFull())
      theval = new Interface_EntityCluster(ent, aValEC);
    else
      aValEC->Append(ent);
  }
  else
  {
    occ::handle<Interface_EntityCluster> ec = new Interface_EntityCluster(theval);
    ec->Append(ent);
    theval = ec;
  }
}

void Interface_EntityList::Remove(const occ::handle<Standard_Transient>& ent)
{
  if (ent.IsNull())
    throw Standard_NullObject("Interface_EntityList Remove");
  if (theval.IsNull())
    return;
  if (theval == ent)
  {
    theval.Nullify();
    return;
  }
  occ::handle<Interface_EntityCluster> ec = occ::down_cast<Interface_EntityCluster>(theval);
  if (ec.IsNull())
    return;
  bool res = ec->Remove(ent);
  if (res)
    theval.Nullify();
}

void Interface_EntityList::Remove(const int num)
{
  if (theval.IsNull())
    throw Standard_OutOfRange("EntityList : Remove");
  occ::handle<Interface_EntityCluster> ec = occ::down_cast<Interface_EntityCluster>(theval);
  if (ec.IsNull())
  {
    if (num != 1)
      throw Standard_OutOfRange("EntityList : Remove");
    theval.Nullify();
    return;
  }
  bool res = ec->Remove(num);
  if (res)
    theval.Nullify();
}

bool Interface_EntityList::IsEmpty() const
{
  return (theval.IsNull());
}

int Interface_EntityList::NbEntities() const
{
  if (theval.IsNull())
    return 0;
  occ::handle<Interface_EntityCluster> ec = occ::down_cast<Interface_EntityCluster>(theval);
  if (ec.IsNull())
    return 1;
  return ec->NbEntities();
}

const occ::handle<Standard_Transient>& Interface_EntityList::Value(const int num) const
{
  if (theval.IsNull())
    throw Standard_OutOfRange("Interface EntityList : Value");
  occ::handle<Interface_EntityCluster> ec = occ::down_cast<Interface_EntityCluster>(theval);
  if (!ec.IsNull())
    return ec->Value(num);
  else if (num != 1)
    throw Standard_OutOfRange("Interface EntityList : Value");
  return theval;
}

void Interface_EntityList::SetValue(const int num, const occ::handle<Standard_Transient>& ent)
{
  if (ent.IsNull())
    throw Standard_NullObject("Interface_EntityList SetValue");
  if (theval.IsNull())
    throw Standard_OutOfRange("Interface EntityList : SetValue");
  occ::handle<Interface_EntityCluster> ec = occ::down_cast<Interface_EntityCluster>(theval);
  if (!ec.IsNull())
    ec->SetValue(num, ent);
  else if (num != 1)
    throw Standard_OutOfRange("Interface EntityList : SetValue");
  else
    theval = ent;
}

void Interface_EntityList::FillIterator(Interface_EntityIterator& iter) const
{
  if (theval.IsNull())
    return;
  occ::handle<Interface_EntityCluster> ec = occ::down_cast<Interface_EntityCluster>(theval);
  if (!ec.IsNull())
    ec->FillIterator(iter);
  else
    iter.GetOneItem(theval);
}

int Interface_EntityList::NbTypedEntities(const occ::handle<Standard_Type>& atype) const
{
  int res = 0;
  if (theval.IsNull())
    return 0;
  occ::handle<Interface_EntityCluster> ec = occ::down_cast<Interface_EntityCluster>(theval);
  if (!ec.IsNull())
  {
    while (!ec.IsNull())
    {
      for (int i = ec->NbLocal(); i > 0; i--)
      {
        if (ec->Value(i)->IsKind(atype))
          res++;
      }
      if (!ec->HasNext())
        break;
      ec = ec->Next();
    }
  }
  else
  {
    if (theval->IsKind(atype))
      res = 1;
  }
  return res;
}

occ::handle<Standard_Transient> Interface_EntityList::TypedEntity(
  const occ::handle<Standard_Type>& atype,
  const int                         num) const
{
  int                             res = 0;
  occ::handle<Standard_Transient> entres;
  if (theval.IsNull())
    throw Interface_InterfaceError("Interface EntityList : TypedEntity , none found");
  occ::handle<Interface_EntityCluster> ec = occ::down_cast<Interface_EntityCluster>(theval);
  if (!ec.IsNull())
  {
    while (!ec.IsNull())
    {
      for (int i = ec->NbLocal(); i > 0; i--)
      {
        if (ec->Value(i)->IsKind(atype))
        {
          res++;
          if (num == 0 && res > 1)
            throw Interface_InterfaceError("Interface EntityList : TypedEntity , several found");
          entres = ec->Value(i);
          if (res == num)
            return entres;
        }
      }
      if (!ec->HasNext())
        break;
      ec = ec->Next();
    }
  }
  else if (num > 1)
  {
    throw Interface_InterfaceError("Interface EntityList : TypedEntity ,out of range");
  }
  else
  {
    if (!theval->IsKind(atype))
      throw Interface_InterfaceError("Interface EntityList : TypedEntity , none found");
    entres = theval;
  }
  return entres;
}
