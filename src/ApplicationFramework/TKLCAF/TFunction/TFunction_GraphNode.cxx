#include <Standard_GUID.hpp>
#include <Standard_Type.hpp>
#include <TDF_DataSet.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TFunction_GraphNode.hpp>
#include <TFunction_Scope.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TFunction_GraphNode, TDF_Attribute)

const Standard_GUID& TFunction_GraphNode::GetID()
{
  static Standard_GUID TFunction_GraphNodeID("DD51FA86-E171-41a4-A2C1-3A0FBF286798");
  return TFunction_GraphNodeID;
}

occ::handle<TFunction_GraphNode> TFunction_GraphNode::Set(const TDF_Label& L)
{
  occ::handle<TFunction_GraphNode> G;
  if (!L.FindAttribute(TFunction_GraphNode::GetID(), G))
  {
    G = new TFunction_GraphNode();
    L.AddAttribute(G);
  }
  return G;
}

const Standard_GUID& TFunction_GraphNode::ID() const
{
  return GetID();
}

TFunction_GraphNode::TFunction_GraphNode()
    : myStatus(TFunction_ES_WrongDefinition)
{
}

bool TFunction_GraphNode::AddPrevious(const int funcID)
{
  if (myPrevious.Contains(funcID))
    return false;

  Backup();

  return myPrevious.Add(funcID);
}

bool TFunction_GraphNode::AddPrevious(const TDF_Label& func)
{
  occ::handle<TFunction_Scope> scope = TFunction_Scope::Set(func);
  if (!scope->GetFunctions().IsBound2(func))
    return false;
  int funcID = scope->GetFunctions().Find2(func);
  return AddPrevious(funcID);
}

bool TFunction_GraphNode::RemovePrevious(const int funcID)
{
  if (!myPrevious.Contains(funcID))
    return false;

  Backup();

  return myPrevious.Remove(funcID);
}

bool TFunction_GraphNode::RemovePrevious(const TDF_Label& func)
{
  occ::handle<TFunction_Scope> scope = TFunction_Scope::Set(func);
  if (!scope->GetFunctions().IsBound2(func))
    return false;
  int funcID = scope->GetFunctions().Find2(func);
  return RemovePrevious(funcID);
}

const NCollection_Map<int>& TFunction_GraphNode::GetPrevious() const
{
  return myPrevious;
}

void TFunction_GraphNode::RemoveAllPrevious()
{
  if (myPrevious.IsEmpty())
    return;

  Backup();

  myPrevious.Clear();
}

bool TFunction_GraphNode::AddNext(const int funcID)
{
  if (myNext.Contains(funcID))
    return false;

  Backup();

  return myNext.Add(funcID);
}

bool TFunction_GraphNode::AddNext(const TDF_Label& func)
{
  occ::handle<TFunction_Scope> scope = TFunction_Scope::Set(func);
  if (!scope->GetFunctions().IsBound2(func))
    return false;
  int funcID = scope->GetFunctions().Find2(func);
  return AddNext(funcID);
}

bool TFunction_GraphNode::RemoveNext(const int funcID)
{
  if (!myNext.Contains(funcID))
    return false;

  Backup();

  return myNext.Remove(funcID);
}

bool TFunction_GraphNode::RemoveNext(const TDF_Label& func)
{
  occ::handle<TFunction_Scope> scope = TFunction_Scope::Set(func);
  if (!scope->GetFunctions().IsBound2(func))
    return false;
  int funcID = scope->GetFunctions().Find2(func);
  return RemoveNext(funcID);
}

const NCollection_Map<int>& TFunction_GraphNode::GetNext() const
{
  return myNext;
}

void TFunction_GraphNode::RemoveAllNext()
{
  if (myNext.IsEmpty())
    return;

  Backup();

  myNext.Clear();
}

TFunction_ExecutionStatus TFunction_GraphNode::GetStatus() const
{
  return myStatus;
}

void TFunction_GraphNode::SetStatus(const TFunction_ExecutionStatus status)
{
  if (myStatus == status)
    return;

  Backup();

  myStatus = status;
}

void TFunction_GraphNode::Restore(const occ::handle<TDF_Attribute>& other)
{
  occ::handle<TFunction_GraphNode> G = occ::down_cast<TFunction_GraphNode>(other);

  myPrevious = G->myPrevious;

  myNext = G->myNext;

  myStatus = G->myStatus;
}

void TFunction_GraphNode::Paste(const occ::handle<TDF_Attribute>& into,
                                const occ::handle<TDF_RelocationTable>&) const
{
  occ::handle<TFunction_GraphNode> G = occ::down_cast<TFunction_GraphNode>(into);

  G->myPrevious = myPrevious;

  G->myNext = myNext;

  G->myStatus = myStatus;
}

occ::handle<TDF_Attribute> TFunction_GraphNode::NewEmpty() const
{
  return new TFunction_GraphNode();
}

void TFunction_GraphNode::References(const occ::handle<TDF_DataSet>&) const {}

Standard_OStream& TFunction_GraphNode::Dump(Standard_OStream& anOS) const
{
  TDF_Attribute::Dump(anOS);
  return anOS;
}
