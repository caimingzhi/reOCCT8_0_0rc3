

#include <Interface_EntityIterator.hpp>
#include <Interface_GTool.hpp>
#include <Interface_HGraph.hpp>
#include <Interface_InterfaceError.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ShareTool.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

Interface_ShareTool::Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                         const Interface_GeneralLib&                  lib)
{
  theHGraph = new Interface_HGraph(amodel, lib);
}

Interface_ShareTool::Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                         const occ::handle<Interface_GTool>&          gtool)
{
  theHGraph = new Interface_HGraph(amodel, gtool);
}

Interface_ShareTool::Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel,
                                         const occ::handle<Interface_Protocol>&       protocol)
{
  theHGraph = new Interface_HGraph(amodel, protocol);
}

Interface_ShareTool::Interface_ShareTool(const occ::handle<Interface_InterfaceModel>& amodel)
{
  theHGraph = new Interface_HGraph(amodel);
}

Interface_ShareTool::Interface_ShareTool(const Interface_Graph& agraph)
{
  theHGraph = new Interface_HGraph(agraph.Model());
}

Interface_ShareTool::Interface_ShareTool(const occ::handle<Interface_HGraph>& ahgraph)
{
  theHGraph = ahgraph;
}

occ::handle<Interface_InterfaceModel> Interface_ShareTool::Model() const
{
  return theHGraph->Graph().Model();
}

const Interface_Graph& Interface_ShareTool::Graph() const
{
  return theHGraph->Graph();
}

Interface_EntityIterator Interface_ShareTool::RootEntities() const
{
  return theHGraph->Graph().RootEntities();
}

bool Interface_ShareTool::IsShared(const occ::handle<Standard_Transient>& ent) const
{
  const Interface_Graph&                                              thegraph = theHGraph->Graph();
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> list =
    thegraph.GetShareds(ent);
  return (!list.IsNull() && list->Length() > 0);
}

Interface_EntityIterator Interface_ShareTool::Shareds(
  const occ::handle<Standard_Transient>& ent) const
{
  return theHGraph->Graph().Shareds(ent);
}

Interface_EntityIterator Interface_ShareTool::Sharings(
  const occ::handle<Standard_Transient>& ent) const
{
  return theHGraph->Graph().Sharings(ent);
}

int Interface_ShareTool::NbTypedSharings(const occ::handle<Standard_Transient>& ent,
                                         const occ::handle<Standard_Type>&      atype) const
{
  Interface_Graph& thegraph = theHGraph->CGraph();
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> list =
    thegraph.GetSharings(ent);
  if (list.IsNull())
    return 0;

  int result = 0;
  int n      = list->Length();
  for (int i = 1; i <= n; i++)
  {
    occ::handle<Standard_Transient> entsh = list->Value(i);
    if (entsh.IsNull())
      continue;
    if (entsh->IsKind(atype))
      result++;
  }
  return result;
}

occ::handle<Standard_Transient> Interface_ShareTool::TypedSharing(
  const occ::handle<Standard_Transient>& ent,
  const occ::handle<Standard_Type>&      atype) const
{
  Interface_Graph& thegraph = theHGraph->CGraph();
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> list =
    thegraph.GetSharings(ent);
  if (list.IsNull())
    return nullptr;
  occ::handle<Standard_Transient> entresult;
  int                             result = 0;
  int                             n      = list->Length();
  for (int i = 1; i <= n; i++)
  {
    occ::handle<Standard_Transient> entsh = list->Value(i);
    if (entsh.IsNull())
      continue;
    if (entsh->IsKind(atype))
    {
      entresult = entsh;
      result++;
      if (result > 1)
        throw Interface_InterfaceError("Interface ShareTool : TypedSharing, more than one found");
    }
  }
  if (result == 0)
    throw Interface_InterfaceError("Interface ShareTool : TypedSharing, not found");
  return entresult;
}

Interface_EntityIterator Interface_ShareTool::All(const occ::handle<Standard_Transient>& ent,
                                                  const bool rootlast) const
{
  occ::handle<Interface_InterfaceModel> model = Model();
  Interface_EntityIterator              list;
  int                                   i, n0 = 0, nb = model->NbEntities();
  occ::handle<NCollection_HArray1<int>> fl = new NCollection_HArray1<int>(0, nb);
  fl->Init(0);
  if (ent == model)
  {

    Interface_EntityIterator roots = RootEntities();
    for (roots.Start(); roots.More(); roots.Next())
    {
      Interface_EntityIterator subl = All(roots.Value(), rootlast);
      for (subl.Start(); subl.More(); subl.Next())
      {
        int nm = model->Number(subl.Value());
        if (fl->Value(nm) > 0)
          continue;
        n0++;
        fl->SetValue(nm, n0);
      }
    }

    for (i = 1; i <= nb; i++)
      if (fl->Value(i) == 0)
      {
        n0++;
        fl->SetValue(i, n0);
      }
  }
  else
  {
    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> sq =
      new NCollection_HSequence<occ::handle<Standard_Transient>>();
    sq->Append(ent);

    for (i = 1; i <= sq->Length(); i++)
    {
      occ::handle<Standard_Transient> en  = sq->Value(i);
      int                             num = model->Number(en);
      if (fl->Value(num) != 0)
        continue;
      n0++;
      fl->SetValue(num, n0);
      Interface_EntityIterator sh = Shareds(en);
      sq->Append(sh.Content());
    }
  }

  occ::handle<NCollection_HArray1<int>> ord = new NCollection_HArray1<int>(0, nb);
  ord->Init(0);
  for (i = 1; i <= nb; i++)
  {
    n0 = fl->Value(i);
    ord->SetValue(n0, i);
  }
  if (rootlast && ent != model)
    for (i = 1; i <= nb; i++)
    {
      if (ord->Value(i) != 0)
        list.AddItem(model->Value(ord->Value(i)));
    }
  else
    for (i = nb; i > 0; i--)
    {
      if (ord->Value(i) != 0)
        list.AddItem(model->Value(ord->Value(i)));
    }

  return list;
}

void Interface_ShareTool::Print(const Interface_EntityIterator& iter, Standard_OStream& S) const
{
  S << " Nb.Entities : " << iter.NbEntities() << " : ";
  for (iter.Start(); iter.More(); iter.Next())
  {
    const occ::handle<Standard_Transient>& ent = iter.Value();
    S << " n0/id:";
    Model()->Print(ent, S);
  }
  S << std::endl;
}
