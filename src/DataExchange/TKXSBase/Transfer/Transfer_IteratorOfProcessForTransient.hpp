#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_TransferIterator.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Transfer_Binder.hpp>

class Standard_NoSuchObject;
class Standard_Transient;
class Transfer_ProcessForTransient;
class Transfer_ActorOfProcessForTransient;
class Transfer_Binder;

class Transfer_IteratorOfProcessForTransient : public Transfer_TransferIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Transfer_IteratorOfProcessForTransient(const bool withstarts);

  Standard_EXPORT void Add(const occ::handle<Transfer_Binder>& binder);

  Standard_EXPORT void Add(const occ::handle<Transfer_Binder>&    binder,
                           const occ::handle<Standard_Transient>& start);

  Standard_EXPORT void Filter(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const bool                                                                 keep = true);

  Standard_EXPORT bool HasStarting() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Starting() const;

private:
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thestarts;
};
