#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TFunction_Scope.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TFunction_Scope, TDF_Attribute)

const Standard_GUID& TFunction_Scope::GetID()
{
  static Standard_GUID TFunction_ScopeID("F2DE4EFF-7FE8-40a3-AAD5-5B6DDEA83469");
  return TFunction_ScopeID;
}

occ::handle<TFunction_Scope> TFunction_Scope::Set(const TDF_Label& Access)
{
  occ::handle<TFunction_Scope> S;
  if (!Access.Root().FindAttribute(TFunction_Scope::GetID(), S))
  {
    S = new TFunction_Scope();
    Access.Root().AddAttribute(S);
  }
  return S;
}

const Standard_GUID& TFunction_Scope::ID() const
{
  return GetID();
}

TFunction_Scope::TFunction_Scope()
    : myFreeID(1)
{
}

bool TFunction_Scope::AddFunction(const TDF_Label& L)
{
  if (myFunctions.IsBound2(L))
    return false;

  Backup();

  myFunctions.Bind(myFreeID++, L);
  return true;
}

bool TFunction_Scope::RemoveFunction(const TDF_Label& L)
{
  if (!myFunctions.IsBound2(L))
    return false;

  Backup();

  return myFunctions.UnBind2(L);
}

bool TFunction_Scope::RemoveFunction(const int ID)
{
  if (!myFunctions.IsBound1(ID))
    return false;

  Backup();

  return myFunctions.UnBind1(ID);
}

void TFunction_Scope::RemoveAllFunctions()
{
  if (myFunctions.IsEmpty())
    return;

  Backup();

  myFunctions.Clear();
}

bool TFunction_Scope::HasFunction(const int ID) const
{
  return myFunctions.IsBound1(ID);
}

bool TFunction_Scope::HasFunction(const TDF_Label& L) const
{
  return myFunctions.IsBound2(L);
}

int TFunction_Scope::GetFunction(const TDF_Label& L) const
{
  return myFunctions.Find2(L);
}

const TDF_Label& TFunction_Scope::GetFunction(const int ID) const
{
  return myFunctions.Find1(ID);
}

occ::handle<TFunction_Logbook> TFunction_Scope::GetLogbook() const
{
  occ::handle<TFunction_Logbook> logbook;
  FindAttribute(TFunction_Logbook::GetID(), logbook);
  return logbook;
}

void TFunction_Scope::Restore(const occ::handle<TDF_Attribute>& other)
{
  occ::handle<TFunction_Scope> S = occ::down_cast<TFunction_Scope>(other);

  myFunctions = S->myFunctions;
  myFreeID    = S->myFreeID;
}

void TFunction_Scope::Paste(const occ::handle<TDF_Attribute>&,
                            const occ::handle<TDF_RelocationTable>&) const
{
}

occ::handle<TDF_Attribute> TFunction_Scope::NewEmpty() const
{
  return new TFunction_Scope();
}

Standard_OStream& TFunction_Scope::Dump(Standard_OStream& anOS) const
{
  TDF_Attribute::Dump(anOS);
  return anOS;
}

const NCollection_DoubleMap<int, TDF_Label>& TFunction_Scope::GetFunctions() const
{
  return myFunctions;
}

NCollection_DoubleMap<int, TDF_Label>& TFunction_Scope::ChangeFunctions()
{
  return myFunctions;
}

void TFunction_Scope::SetFreeID(const int ID)
{
  if (myFreeID == ID)
    return;

  Backup();

  myFreeID = ID;
}

int TFunction_Scope::GetFreeID() const
{
  return myFreeID;
}
