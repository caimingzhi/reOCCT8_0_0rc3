#include <Transfer_ActorOfProcessForFinder.hpp>

#include <Standard_DomainError.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_Finder.hpp>
#include <Transfer_FindHasher.hpp>
#include <Transfer_IteratorOfProcessForFinder.hpp>
#include <Transfer_ProcessForFinder.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <NCollection_IndexedDataMap.hpp>

//=================================================================================================

Transfer_ActorOfProcessForFinder::Transfer_ActorOfProcessForFinder() = default;

//=================================================================================================

bool Transfer_ActorOfProcessForFinder::Recognize(const occ::handle<Transfer_Finder>& /*start*/)
{
  return true;
}

//=================================================================================================

occ::handle<Transfer_Binder> Transfer_ActorOfProcessForFinder::Transferring(
  const occ::handle<Transfer_Finder>& /*start*/,
  const occ::handle<Transfer_ProcessForFinder>& /*TP*/,
  const Message_ProgressRange& /*theProgress*/)
{
  return NullResult();
}

//=================================================================================================

occ::handle<Transfer_SimpleBinderOfTransient> Transfer_ActorOfProcessForFinder::TransientResult(
  const occ::handle<Standard_Transient>& res) const
{
  occ::handle<Transfer_SimpleBinderOfTransient> binder;
  if (res.IsNull())
    return binder;
  binder = new Transfer_SimpleBinderOfTransient;
  binder->SetResult(res);
  return binder;
}

//=================================================================================================

occ::handle<Transfer_Binder> Transfer_ActorOfProcessForFinder::NullResult() const
{
  occ::handle<Transfer_Binder> binder;
  return binder;
}

//=================================================================================================

void Transfer_ActorOfProcessForFinder::SetNext(
  const occ::handle<Transfer_ActorOfProcessForFinder>& next)
{
  if (thenext == next)
    return;
  if (thenext.IsNull())
    thenext = next;
  else if (thenext->IsLast())
  {
    next->SetNext(thenext);
    thenext = next;
  }
  else
    thenext->SetNext(next);
}

//=================================================================================================

occ::handle<Transfer_ActorOfProcessForFinder> Transfer_ActorOfProcessForFinder::Next() const
{
  return thenext;
}

//=================================================================================================

void Transfer_ActorOfProcessForFinder::SetLast(const bool mode)
{
  thelast = mode;
}

//=================================================================================================

bool Transfer_ActorOfProcessForFinder::IsLast() const
{
  return thelast;
}
