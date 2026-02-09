#include <TDF_ChildIterator.hpp>
#include <TDF_Label.hpp>
#include <TNaming_Scope.hpp>
#include <TNaming_Tool.hpp>
#include <TopoDS_Shape.hpp>

TNaming_Scope::TNaming_Scope()
    : myWithValid(false)
{
}

TNaming_Scope::TNaming_Scope(NCollection_Map<TDF_Label>& map)
{
  myWithValid = true;
  myValid     = map;
}

TNaming_Scope::TNaming_Scope(const bool with)
    : myWithValid(with)
{
}

bool TNaming_Scope::WithValid() const
{
  return myWithValid;
}

void TNaming_Scope::WithValid(const bool mode)
{
  myWithValid = mode;
}

void TNaming_Scope::ClearValid()
{
  myValid.Clear();
}

void TNaming_Scope::Valid(const TDF_Label& L)
{
  myValid.Add(L);
}

void TNaming_Scope::ValidChildren(const TDF_Label& L, const bool withroot)
{
  if (L.HasChild())
  {
    TDF_ChildIterator itc(L, true);
    for (; itc.More(); itc.Next())
      myValid.Add(itc.Value());
  }
  if (withroot)
    myValid.Add(L);
}

void TNaming_Scope::Unvalid(const TDF_Label& L)
{
  myValid.Remove(L);
}

void TNaming_Scope::UnvalidChildren(const TDF_Label& L, const bool withroot)
{
  if (L.HasChild())
  {
    TDF_ChildIterator itc(L, true);
    for (; itc.More(); itc.Next())
      myValid.Remove(itc.Value());
  }
  if (withroot)
    myValid.Remove(L);
}

bool TNaming_Scope::IsValid(const TDF_Label& L) const
{
  if (myWithValid)
    return myValid.Contains(L);
  return true;
}

const NCollection_Map<TDF_Label>& TNaming_Scope::GetValid() const
{
  return myValid;
}

NCollection_Map<TDF_Label>& TNaming_Scope::ChangeValid()
{
  return myValid;
}

TopoDS_Shape TNaming_Scope::CurrentShape(const occ::handle<TNaming_NamedShape>& NS) const
{
  if (myWithValid)
    return TNaming_Tool::CurrentShape(NS, myValid);
  return TNaming_Tool::CurrentShape(NS);
}
