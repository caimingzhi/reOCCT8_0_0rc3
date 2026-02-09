#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Transfer_Binder.hpp>
#include <Message_ProgressRange.hpp>

class Standard_DomainError;
class Standard_Transient;
class Transfer_ProcessForTransient;
class Transfer_IteratorOfProcessForTransient;
class Transfer_Binder;
class Transfer_SimpleBinderOfTransient;

class Transfer_ActorOfProcessForTransient : public Standard_Transient
{

public:
  Standard_EXPORT Transfer_ActorOfProcessForTransient();

  Standard_EXPORT virtual bool Recognize(const occ::handle<Standard_Transient>& start);

  Standard_EXPORT virtual occ::handle<Transfer_Binder> Transferring(
    const occ::handle<Standard_Transient>&           start,
    const occ::handle<Transfer_ProcessForTransient>& TP,
    const Message_ProgressRange&                     theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<Transfer_SimpleBinderOfTransient> TransientResult(
    const occ::handle<Standard_Transient>& res) const;

  Standard_EXPORT occ::handle<Transfer_Binder> NullResult() const;

  Standard_EXPORT void SetLast(const bool mode = true);

  Standard_EXPORT bool IsLast() const;

  Standard_EXPORT void SetNext(const occ::handle<Transfer_ActorOfProcessForTransient>& next);

  Standard_EXPORT occ::handle<Transfer_ActorOfProcessForTransient> Next() const;

  DEFINE_STANDARD_RTTI_INLINE(Transfer_ActorOfProcessForTransient, Standard_Transient)

private:
  occ::handle<Transfer_ActorOfProcessForTransient> thenext;
  bool                                             thelast;
};
