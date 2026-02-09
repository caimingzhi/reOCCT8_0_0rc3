

#include <Interface_EntityIterator.hpp>
#include <Interface_IntVal.hpp>
#include <Standard_NoMoreObject.hpp>
#include <Standard_NoSuchObject.hpp>
#include <Standard_Transient.hpp>

Interface_EntityIterator::Interface_EntityIterator() {}

Interface_EntityIterator::Interface_EntityIterator(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list)
{
  thecurr           = new Interface_IntVal;
  thecurr->CValue() = 0;
  thelist           = list;
}

void Interface_EntityIterator::AddList(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list)
{
  if (thelist.IsNull())
    thelist = new NCollection_HSequence<occ::handle<Standard_Transient>>();
  if (thecurr.IsNull())
    thecurr = new Interface_IntVal;
  thecurr->CValue() = 0;
  thelist->Append(list);
}

void Interface_EntityIterator::AddItem(const occ::handle<Standard_Transient>& anentity)
{
  if (anentity.IsNull())
    return;
  if (thecurr.IsNull())
    thecurr = new Interface_IntVal;
  if (thelist.IsNull())
    thelist = new NCollection_HSequence<occ::handle<Standard_Transient>>();
  thecurr->CValue() = 0;
  thelist->Append(anentity);
}

void Interface_EntityIterator::GetOneItem(const occ::handle<Standard_Transient>& anentity)
{
  AddItem(anentity);
}

void Interface_EntityIterator::Reset()
{
  if (thecurr.IsNull())
    thecurr = new Interface_IntVal;
  thecurr->CValue() = 0;
  thelist           = new NCollection_HSequence<occ::handle<Standard_Transient>>();
}

void Interface_EntityIterator::SelectType(const occ::handle<Standard_Type>& atype, const bool keep)
{
  if (thelist.IsNull())
    return;
  int                                                                 i, n = thelist->Length();
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> nlist =
    new NCollection_HSequence<occ::handle<Standard_Transient>>();
  for (i = 1; i <= n; i++)
  {
    if (thelist->Value(i)->IsKind(atype) == keep)
      nlist->Append(thelist->Value(i));
  }
  thelist = nlist;
}

int Interface_EntityIterator::NbEntities() const
{
  if (thelist.IsNull())
    return 0;
  if (!thecurr.IsNull() && thecurr->Value() == 0)
    Start();
  return thelist->Length();
}

int Interface_EntityIterator::NbTyped(const occ::handle<Standard_Type>& atype) const
{
  int res = 0;
  if (thelist.IsNull())
    return res;
  int i, n = thelist->Length();
  for (i = 1; i <= n; i++)
  {
    if (thelist->Value(i)->IsKind(atype))
      res++;
  }
  return res;
}

Interface_EntityIterator Interface_EntityIterator::Typed(
  const occ::handle<Standard_Type>& atype) const
{
  Interface_EntityIterator res;
  if (thelist.IsNull())
    return res;
  int i, n = thelist->Length();
  for (i = 1; i <= n; i++)
  {
    if (thelist->Value(i)->IsKind(atype))
      res.AddItem(thelist->Value(i));
  }
  return res;
}

void Interface_EntityIterator::Start() const
{
  if (!thecurr.IsNull())
    thecurr->CValue() = 1;
}

bool Interface_EntityIterator::More() const
{
  if (thecurr.IsNull())
    return false;
  if (thecurr->Value() == 0)
    Start();
  if (thelist.IsNull())
    return false;
  return (thecurr->Value() <= thelist->Length());
}

void Interface_EntityIterator::Next() const
{
  thecurr->CValue()++;
}

const occ::handle<Standard_Transient>& Interface_EntityIterator::Value() const
{

  if (thelist.IsNull())
    throw Standard_NoSuchObject("Interface_EntityIterator");
  if (thecurr->Value() < 1 || thecurr->Value() > thelist->Length())
    throw Standard_NoSuchObject("Interface_EntityIterator");
  return thelist->Value(thecurr->Value());
}

occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Interface_EntityIterator::
  Content() const
{
  if (!thecurr.IsNull() && thecurr->Value() == 0)
    Start();
  if (thelist.IsNull())
    return new NCollection_HSequence<occ::handle<Standard_Transient>>();
  return thelist;
}

void Interface_EntityIterator::Destroy()
{
  thecurr.Nullify();
}

Interface_EntityIterator::~Interface_EntityIterator()
{
  Destroy();
}
