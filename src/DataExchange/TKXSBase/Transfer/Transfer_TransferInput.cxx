

#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_Protocol.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_IteratorOfProcessForFinder.hpp>
#include <Transfer_IteratorOfProcessForTransient.hpp>
#include <Transfer_MultipleBinder.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <Transfer_TransferFailure.hpp>
#include <Transfer_TransferInput.hpp>
#include <Transfer_TransferIterator.hpp>
#include <Transfer_TransientProcess.hpp>
#include <Transfer_VoidBinder.hpp>

Transfer_TransferInput::Transfer_TransferInput() = default;

Interface_EntityIterator Transfer_TransferInput::Entities(Transfer_TransferIterator& list) const
{
  Interface_EntityIterator iter;
  for (list.Start(); list.More(); list.Next())
  {
    const occ::handle<Transfer_Binder>& binder = list.Value();
    if (binder.IsNull())
      continue;
    if (binder->IsKind(STANDARD_TYPE(Transfer_VoidBinder)))
      continue;

    DeclareAndCast(Transfer_SimpleBinderOfTransient, transb, binder);
    DeclareAndCast(Transfer_MultipleBinder, multi, binder);
    if (!transb.IsNull())
    {
      if (transb->HasResult())
        iter.AddItem(transb->Result());
    }
    else if (!multi.IsNull())
    {
      occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> mulres =
        multi->MultipleResult();
      int nbres = 0;
      if (!mulres.IsNull())
        nbres = mulres->Length();
      for (int i = 1; i <= nbres; i++)
        iter.AddItem(mulres->Value(i));
    }
    else
      throw Transfer_TransferFailure(
        "TransferInput : Entities, one of the Results is not Transient Handle");
  }
  return iter;
}

void Transfer_TransferInput::FillModel(const occ::handle<Transfer_TransientProcess>& proc,
                                       const occ::handle<Interface_InterfaceModel>&  amodel) const
{
  Transfer_TransferIterator list = proc->CompleteResult();
  Interface_EntityIterator  iter = Entities(list);
  amodel->GetFromTransfer(iter);
}

void Transfer_TransferInput::FillModel(const occ::handle<Transfer_TransientProcess>& proc,
                                       const occ::handle<Interface_InterfaceModel>&  amodel,
                                       const occ::handle<Interface_Protocol>&        proto,
                                       const bool                                    roots) const
{
  Transfer_TransferIterator list;
  if (roots)
    list = proc->RootResult();
  else
    list = proc->CompleteResult();
  Interface_EntityIterator iter = Entities(list);
  for (iter.Start(); iter.More(); iter.Next())
    amodel->AddWithRefs(iter.Value(), proto);
}

void Transfer_TransferInput::FillModel(const occ::handle<Transfer_FinderProcess>&   proc,
                                       const occ::handle<Interface_InterfaceModel>& amodel) const
{
  Transfer_TransferIterator list = proc->CompleteResult();
  Interface_EntityIterator  iter = Entities(list);
  amodel->GetFromTransfer(iter);
}

void Transfer_TransferInput::FillModel(const occ::handle<Transfer_FinderProcess>&   proc,
                                       const occ::handle<Interface_InterfaceModel>& amodel,
                                       const occ::handle<Interface_Protocol>&       proto,
                                       const bool                                   roots) const
{
  Transfer_TransferIterator list;
  if (roots)
    list = proc->RootResult();
  else
    list = proc->CompleteResult();
  Interface_EntityIterator iter = Entities(list);
  for (iter.Start(); iter.More(); iter.Next())
    amodel->AddWithRefs(iter.Value(), proto);
}
