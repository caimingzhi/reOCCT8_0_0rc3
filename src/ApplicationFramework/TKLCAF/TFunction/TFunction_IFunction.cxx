#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <TFunction_DriverTable.hpp>
#include <TFunction_Function.hpp>
#include <TFunction_GraphNode.hpp>
#include <TFunction_IFunction.hpp>
#include <TFunction_Scope.hpp>

bool TFunction_IFunction::NewFunction(const TDF_Label& L, const Standard_GUID& ID)
{

  TFunction_Function::Set(L, ID)->SetFailure(0);

  occ::handle<TFunction_GraphNode> graphNode = TFunction_GraphNode::Set(L);
  graphNode->RemoveAllPrevious();
  graphNode->RemoveAllNext();
  graphNode->SetStatus(TFunction_ES_WrongDefinition);

  TFunction_Scope::Set(L)->AddFunction(L);

  return TFunction_DriverTable::Get()->HasDriver(ID);
}

bool TFunction_IFunction::DeleteFunction(const TDF_Label& L)
{

  occ::handle<TFunction_Function> func;
  if (L.FindAttribute(TFunction_Function::GetID(), func))
    L.ForgetAttribute(func);

  occ::handle<TFunction_Scope> scope  = TFunction_Scope::Set(L);
  const int                    funcID = scope->GetFunctions().Find2(L);

  occ::handle<TFunction_GraphNode> graphNode;
  if (L.FindAttribute(TFunction_GraphNode::GetID(), graphNode))
  {
    const NCollection_Map<int>& prev = graphNode->GetPrevious();
    const NCollection_Map<int>& next = graphNode->GetNext();

    NCollection_Map<int>::Iterator itrm(prev);
    for (; itrm.More(); itrm.Next())
    {
      const int                        ID = itrm.Key();
      const TDF_Label&                 La = scope->GetFunctions().Find1(ID);
      occ::handle<TFunction_GraphNode> G;
      if (La.FindAttribute(TFunction_GraphNode::GetID(), G))
      {
        G->RemoveNext(funcID);
      }
    }

    for (itrm.Initialize(next); itrm.More(); itrm.Next())
    {
      const int                        ID = itrm.Key();
      const TDF_Label&                 La = scope->GetFunctions().Find1(ID);
      occ::handle<TFunction_GraphNode> G;
      if (La.FindAttribute(TFunction_GraphNode::GetID(), G))
      {
        G->RemovePrevious(funcID);
      }
    }

    L.ForgetAttribute(graphNode);
  }

  scope->RemoveFunction(L);

  return true;
}

bool TFunction_IFunction::UpdateDependencies(const TDF_Label& Access)
{

  occ::handle<TFunction_Scope> scope = TFunction_Scope::Set(Access);

  NCollection_DataMap<TDF_Label, NCollection_List<TDF_Label>> table;
  NCollection_DoubleMap<int, TDF_Label>::Iterator             itrm(scope->GetFunctions());
  for (; itrm.More(); itrm.Next())
  {

    const TDF_Label&    L = itrm.Key2();
    TFunction_IFunction iFunction(L);

    occ::handle<TFunction_Driver> driver = iFunction.GetDriver();

    NCollection_List<TDF_Label> res;
    driver->Results(res);

    table.Bind(L, res);

    occ::handle<TFunction_GraphNode> graphNode = iFunction.GetGraphNode();
    graphNode->RemoveAllPrevious();
    graphNode->RemoveAllNext();
  }

  NCollection_DataMap<TDF_Label, NCollection_List<TDF_Label>>::Iterator itrd;
  for (itrm.Initialize(scope->GetFunctions()); itrm.More(); itrm.Next())
  {

    const TDF_Label&    L = itrm.Key2();
    TFunction_IFunction iFunction(L);

    occ::handle<TFunction_Driver> driver = iFunction.GetDriver();

    NCollection_List<TDF_Label> args;
    driver->Arguments(args);

    NCollection_Map<TDF_Label>            argsMap;
    NCollection_List<TDF_Label>::Iterator itrl(args);
    for (; itrl.More(); itrl.Next())
      argsMap.Add(itrl.Value());

    const int funcID = itrm.Key1();

    for (itrd.Initialize(table); itrd.More(); itrd.Next())
    {
      const TDF_Label& anotherL = itrd.Key();
      if (L == anotherL)
        continue;
      const NCollection_List<TDF_Label>& anotherRes = itrd.Value();

      for (itrl.Initialize(anotherRes); itrl.More(); itrl.Next())
      {
        if (argsMap.Contains(itrl.Value()))
        {
          iFunction.GetGraphNode()->AddPrevious(anotherL);

          TFunction_IFunction iAnotherFunction(anotherL);
          iAnotherFunction.GetGraphNode()->AddNext(funcID);
        }
      }
    }
  }

  return true;
}

TFunction_IFunction::TFunction_IFunction() = default;

TFunction_IFunction::TFunction_IFunction(const TDF_Label& L)
{
  Init(L);
}

void TFunction_IFunction::Init(const TDF_Label& L)
{
  myLabel = L;
}

const TDF_Label& TFunction_IFunction::Label() const
{
  return myLabel;
}

bool TFunction_IFunction::UpdateDependencies() const
{

  NCollection_List<TDF_Label>   args, res;
  occ::handle<TFunction_Driver> D = GetDriver();
  D->Arguments(args);
  D->Results(res);

  NCollection_Map<TDF_Label>            argsMap, resMap;
  NCollection_List<TDF_Label>::Iterator itrl(args);
  for (; itrl.More(); itrl.Next())
  {
    argsMap.Add(itrl.Value());
  }
  for (itrl.Initialize(res); itrl.More(); itrl.Next())
  {
    resMap.Add(itrl.Value());
  }

  occ::handle<TFunction_Scope>                    scope = TFunction_Scope::Set(myLabel);
  NCollection_DoubleMap<int, TDF_Label>::Iterator itrm(scope->GetFunctions());
  for (; itrm.More(); itrm.Next())
  {
    const TDF_Label& L = itrm.Key2();
    if (L == myLabel)
      continue;
    TFunction_IFunction iFunc(L);
    D = iFunc.GetDriver();

    args.Clear();
    D->Arguments(args);

    for (itrl.Initialize(args); itrl.More(); itrl.Next())
    {
      if (resMap.Contains(itrl.Value()))
      {

        GetGraphNode()->AddNext(scope->GetFunctions().Find2(L));
        iFunc.GetGraphNode()->AddPrevious(scope->GetFunctions().Find2(myLabel));
      }
    }

    res.Clear();
    D->Results(res);

    for (itrl.Initialize(res); itrl.More(); itrl.Next())
    {
      if (argsMap.Contains(itrl.Value()))
      {

        GetGraphNode()->AddPrevious(scope->GetFunctions().Find2(L));
        iFunc.GetGraphNode()->AddNext(scope->GetFunctions().Find2(myLabel));
      }
    }
  }

  return true;
}

void TFunction_IFunction::Arguments(NCollection_List<TDF_Label>& args) const
{
  occ::handle<TFunction_Driver> driver = GetDriver();
  driver->Arguments(args);
}

void TFunction_IFunction::Results(NCollection_List<TDF_Label>& res) const
{
  occ::handle<TFunction_Driver> driver = GetDriver();
  driver->Results(res);
}

void TFunction_IFunction::GetPrevious(NCollection_List<TDF_Label>& prev) const
{
  occ::handle<TFunction_GraphNode> graph = GetGraphNode();
  const NCollection_Map<int>&      map   = graph->GetPrevious();
  occ::handle<TFunction_Scope>     scope = TFunction_Scope::Set(myLabel);

  NCollection_Map<int>::Iterator itrm(map);
  for (; itrm.More(); itrm.Next())
  {
    const int funcID = itrm.Key();
    if (scope->GetFunctions().IsBound1(funcID))
    {
      prev.Append(scope->GetFunctions().Find1(funcID));
    }
  }
}

void TFunction_IFunction::GetNext(NCollection_List<TDF_Label>& next) const
{
  occ::handle<TFunction_GraphNode> graph = GetGraphNode();
  const NCollection_Map<int>&      map   = graph->GetNext();
  occ::handle<TFunction_Scope>     scope = TFunction_Scope::Set(myLabel);

  NCollection_Map<int>::Iterator itrm(map);
  for (; itrm.More(); itrm.Next())
  {
    const int funcID = itrm.Key();
    if (scope->GetFunctions().IsBound1(funcID))
    {
      next.Append(scope->GetFunctions().Find1(funcID));
    }
  }
}

TFunction_ExecutionStatus TFunction_IFunction::GetStatus() const
{
  occ::handle<TFunction_GraphNode> graph = GetGraphNode();
  return graph->GetStatus();
}

void TFunction_IFunction::SetStatus(const TFunction_ExecutionStatus status) const
{
  occ::handle<TFunction_GraphNode> graph = GetGraphNode();
  graph->SetStatus(status);
}

const NCollection_DoubleMap<int, TDF_Label>& TFunction_IFunction::GetAllFunctions() const
{
  return TFunction_Scope::Set(myLabel)->GetFunctions();
}

occ::handle<TFunction_Logbook> TFunction_IFunction::GetLogbook() const
{
  return TFunction_Scope::Set(myLabel)->GetLogbook();
}

occ::handle<TFunction_Driver> TFunction_IFunction::GetDriver(const int thread) const
{
  occ::handle<TFunction_Driver>   driver;
  occ::handle<TFunction_Function> func;
  if (!myLabel.FindAttribute(TFunction_Function::GetID(), func))
    throw Standard_NoSuchObject(
      "TFunction_IFunction::GetDriver(): A Function is not found attached to this label");
  if (!TFunction_DriverTable::Get()->FindDriver(func->GetDriverGUID(), driver, thread))
    throw Standard_NoSuchObject(
      "TFunction_IFunction::GetDriver(): A driver is not found for this ID");
  driver->Init(myLabel);
  return driver;
}

occ::handle<TFunction_GraphNode> TFunction_IFunction::GetGraphNode() const
{
  occ::handle<TFunction_GraphNode> graphNode;
  if (!myLabel.FindAttribute(TFunction_GraphNode::GetID(), graphNode))
    throw Standard_NoSuchObject(
      "TFunction_IFunction::GetStatus(): A graph node is not found attached to this label");
  return graphNode;
}
