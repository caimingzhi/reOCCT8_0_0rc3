

#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <Interface_InterfaceModel.hpp>
#include <Interface_Protocol.hpp>
#include <Interface_ShareFlags.hpp>
#include <Standard_Transient.hpp>
#include <Transfer_ActorOfTransientProcess.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_TransferFailure.hpp>
#include <Transfer_TransferOutput.hpp>
#include <Transfer_TransientProcess.hpp>
#include <Message_ProgressScope.hpp>

Transfer_TransferOutput::Transfer_TransferOutput(
  const occ::handle<Transfer_ActorOfTransientProcess>& actor,
  const occ::handle<Interface_InterfaceModel>&         amodel)
{
  theproc = new Transfer_TransientProcess(amodel->NbEntities());
  theproc->SetActor(actor);
  themodel = amodel;
}

Transfer_TransferOutput::Transfer_TransferOutput(
  const occ::handle<Transfer_TransientProcess>& proc,
  const occ::handle<Interface_InterfaceModel>&  amodel)
{
  theproc  = proc;
  themodel = amodel;
}

occ::handle<Interface_InterfaceModel> Transfer_TransferOutput::Model() const
{
  return themodel;
}

occ::handle<Transfer_TransientProcess> Transfer_TransferOutput::TransientProcess() const
{
  return theproc;
}

void Transfer_TransferOutput::Transfer(const occ::handle<Standard_Transient>& obj,
                                       const Message_ProgressRange&           theProgress)
{
  if (themodel->Number(obj) == 0)
    throw Transfer_TransferFailure(
      "TransferOutput : Transfer, entities do not come from same initial model");

  theproc->Transfer(obj, theProgress);
}

void Transfer_TransferOutput::TransferRoots(const Message_ProgressRange& theProgress)
{
  TransferRoots(Interface_Protocol::Active(), theProgress);
}

void Transfer_TransferOutput::TransferRoots(const occ::handle<Interface_Protocol>& protocol,
                                            const Message_ProgressRange&           theProgress)
{
  theproc->SetRootManagement(false);
  Interface_ShareFlags     tool(themodel, protocol);
  Interface_EntityIterator list = tool.RootEntities();
  Message_ProgressScope    aPS(theProgress, nullptr, list.NbEntities());
  for (list.Start(); list.More() && aPS.More(); list.Next())
  {
    const occ::handle<Standard_Transient>& ent = list.Value();

    if (theproc->Transfer(ent, aPS.Next()))
      theproc->SetRoot(ent);
  }
}

void Transfer_TransferOutput::TransferRoots(const Interface_Graph&       G,
                                            const Message_ProgressRange& theProgress)
{
  theproc->SetRootManagement(false);
  Interface_ShareFlags tool(G);
  theproc->SetModel(G.Model());
  Interface_EntityIterator list = tool.RootEntities();
  Message_ProgressScope    aPS(theProgress, nullptr, list.NbEntities());
  for (list.Start(); list.More() && aPS.More(); list.Next())
  {
    const occ::handle<Standard_Transient>& ent = list.Value();

    if (theproc->Transfer(ent, aPS.Next()))
      theproc->SetRoot(ent);
  }
}

Interface_EntityIterator Transfer_TransferOutput::ListForStatus(const bool normal,
                                                                const bool roots) const
{
  Interface_EntityIterator list;
  int                      max = (roots ? theproc->NbRoots() : theproc->NbMapped());
  for (int i = 1; i <= max; i++)
  {
    const occ::handle<Transfer_Binder>& binder =
      (roots ? theproc->RootItem(i) : theproc->MapItem(i));
    if (binder.IsNull())
      continue;
    Transfer_StatusExec statex = binder->StatusExec();
    bool                ok = (statex == Transfer_StatusInitial || statex == Transfer_StatusDone);
    if (ok == normal)
      list.AddItem((roots ? theproc->Root(i) : theproc->Mapped(i)));
  }
  return list;
}

occ::handle<Interface_InterfaceModel> Transfer_TransferOutput::ModelForStatus(
  const occ::handle<Interface_Protocol>& protocol,
  const bool                             normal,
  const bool                             roots) const
{
  occ::handle<Interface_InterfaceModel> newmod;
  if (themodel.IsNull())
    return newmod;
  newmod                        = themodel->NewEmptyModel();
  Interface_EntityIterator list = ListForStatus(normal, roots);
  for (list.Start(); list.More(); list.Next())
    newmod->AddWithRefs(list.Value(), protocol);
  return newmod;
}
