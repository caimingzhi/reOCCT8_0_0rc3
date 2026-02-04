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

  //! Creates an empty Iterator
  //! if withstarts is True, each Binder to be iterated will
  //! be associated to its corresponding Starting Object
  Standard_EXPORT Transfer_IteratorOfProcessForTransient(const bool withstarts);

  //! Adds a Binder to the iteration list (construction)
  //! with no corresponding Starting Object
  //! (note that Result is brought by Binder)
  Standard_EXPORT void Add(const occ::handle<Transfer_Binder>& binder);

  //! Adds a Binder to the iteration list, associated with
  //! its corresponding Starting Object "start"
  //! Starting Object is ignored if not required at
  //! Creation time
  Standard_EXPORT void Add(const occ::handle<Transfer_Binder>&    binder,
                           const occ::handle<Standard_Transient>& start);

  //! After having added all items, keeps or rejects items
  //! which are attached to starting data given by <only>
  //! <keep> = True (D) : keeps. <keep> = False : rejects
  //! Does nothing if <withstarts> was False
  Standard_EXPORT void Filter(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& list,
    const bool                                                                 keep = true);

  //! Returns True if Starting Object is available
  //! (defined at Creation Time)
  Standard_EXPORT bool HasStarting() const;

  //! Returns corresponding Starting Object
  Standard_EXPORT const occ::handle<Standard_Transient>& Starting() const;

private:
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thestarts;
};

