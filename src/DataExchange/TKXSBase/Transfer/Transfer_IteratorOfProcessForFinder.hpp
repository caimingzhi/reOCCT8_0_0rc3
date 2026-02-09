#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Transfer_Finder.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Transfer_TransferIterator.hpp>

class Standard_NoSuchObject;
class Transfer_Finder;
class Transfer_FindHasher;
class Transfer_ProcessForFinder;
class Transfer_ActorOfProcessForFinder;
class Transfer_Binder;

class Transfer_IteratorOfProcessForFinder : public Transfer_TransferIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Transfer_IteratorOfProcessForFinder(const bool withstarts);

  Standard_EXPORT void Add(const occ::handle<Transfer_Binder>& binder);

  Standard_EXPORT void Add(const occ::handle<Transfer_Binder>& binder,
                           const occ::handle<Transfer_Finder>& start);

  Standard_EXPORT void Filter(
    const occ::handle<NCollection_HSequence<occ::handle<Transfer_Finder>>>& list,
    const bool                                                              keep = true);

  Standard_EXPORT bool HasStarting() const;

  Standard_EXPORT const occ::handle<Transfer_Finder>& Starting() const;

private:
  occ::handle<NCollection_HSequence<occ::handle<Transfer_Finder>>> thestarts;
};
