#include <Transfer_ActorOfProcessForTransient.hpp>

#include <Standard_DomainError.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_IteratorOfProcessForTransient.hpp>
#include <Transfer_ProcessForTransient.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <NCollection_IndexedDataMap.hpp>

Transfer_ActorOfProcessForTransient::Transfer_ActorOfProcessForTransient() = default;

bool Transfer_ActorOfProcessForTransient::Recognize(const occ::handle<Standard_Transient>&)
{
  return true;
}

occ::handle<Transfer_Binder> Transfer_ActorOfProcessForTransient::Transferring(
  const occ::handle<Standard_Transient>&,
  const occ::handle<Transfer_ProcessForTransient>&,
  const Message_ProgressRange&)
{
  return NullResult();
}

occ::handle<Transfer_SimpleBinderOfTransient> Transfer_ActorOfProcessForTransient::TransientResult(
  const occ::handle<Standard_Transient>& res) const
{
  occ::handle<Transfer_SimpleBinderOfTransient> binder;
  if (res.IsNull())
    return binder;
  binder = new Transfer_SimpleBinderOfTransient;
  binder->SetResult(res);
  return binder;
}

occ::handle<Transfer_Binder> Transfer_ActorOfProcessForTransient::NullResult() const
{
  occ::handle<Transfer_Binder> binder;
  return binder;
}

void Transfer_ActorOfProcessForTransient::SetNext(
  const occ::handle<Transfer_ActorOfProcessForTransient>& next)
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

occ::handle<Transfer_ActorOfProcessForTransient> Transfer_ActorOfProcessForTransient::Next() const
{
  return thenext;
}

void Transfer_ActorOfProcessForTransient::SetLast(const bool mode)
{
  thelast = mode;
}

bool Transfer_ActorOfProcessForTransient::IsLast() const
{
  return thelast;
}
