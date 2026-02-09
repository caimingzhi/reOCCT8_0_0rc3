#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_Finder.hpp>
#include <Transfer_FindHasher.hpp>
#include <Message_ProgressRange.hpp>

class Standard_DomainError;
class Transfer_Finder;
class Transfer_FindHasher;
class Transfer_ProcessForFinder;
class Transfer_IteratorOfProcessForFinder;
class Transfer_Binder;
class Transfer_SimpleBinderOfTransient;
class Standard_Transient;

class Transfer_ActorOfProcessForFinder : public Standard_Transient
{

public:
  Standard_EXPORT Transfer_ActorOfProcessForFinder();

  Standard_EXPORT virtual bool Recognize(const occ::handle<Transfer_Finder>& start);

  Standard_EXPORT virtual occ::handle<Transfer_Binder> Transferring(
    const occ::handle<Transfer_Finder>&           start,
    const occ::handle<Transfer_ProcessForFinder>& TP,
    const Message_ProgressRange&                  theProgress = Message_ProgressRange());

  Standard_EXPORT occ::handle<Transfer_SimpleBinderOfTransient> TransientResult(
    const occ::handle<Standard_Transient>& res) const;

  Standard_EXPORT occ::handle<Transfer_Binder> NullResult() const;

  Standard_EXPORT void SetLast(const bool mode = true);

  Standard_EXPORT bool IsLast() const;

  Standard_EXPORT void SetNext(const occ::handle<Transfer_ActorOfProcessForFinder>& next);

  Standard_EXPORT occ::handle<Transfer_ActorOfProcessForFinder> Next() const;

  DEFINE_STANDARD_RTTI_INLINE(Transfer_ActorOfProcessForFinder, Standard_Transient)

private:
  occ::handle<Transfer_ActorOfProcessForFinder> thenext;
  bool                                          thelast;
};
