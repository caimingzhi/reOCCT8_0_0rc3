#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Interface_CheckStatus.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedMap.hpp>
class Transfer_Binder;
class Interface_Check;
class Transfer_TransientProcess;

//! This class, in conjunction with ResultFromModel, allows to
//! record the result of a transfer initially stored in a
//! TransientProcess.
//!
//! A ResultFromTransient records a couple (Transient,Binder for
//! the result and checks) plus a list of "sub-results", which
//! have been recorded in the TrabsientProcess, under scope
//! attached to the starting transient.
class Transfer_ResultFromTransient : public Standard_Transient
{

public:
  //! Creates a ResultFromTransient, empty
  Standard_EXPORT Transfer_ResultFromTransient();

  //! Sets starting entity
  Standard_EXPORT void SetStart(const occ::handle<Standard_Transient>& start);

  //! Sets Binder (for result plus individual check)
  Standard_EXPORT void SetBinder(const occ::handle<Transfer_Binder>& binder);

  //! Returns the starting entity
  Standard_EXPORT occ::handle<Standard_Transient> Start() const;

  //! Returns the binder
  Standard_EXPORT occ::handle<Transfer_Binder> Binder() const;

  //! Returns True if a result is recorded
  Standard_EXPORT bool HasResult() const;

  //! Returns the check (or an empty one if no binder)
  Standard_EXPORT const occ::handle<Interface_Check> Check() const;

  //! Returns the check status
  Standard_EXPORT Interface_CheckStatus CheckStatus() const;

  //! Clears the list of (immediate) sub-results
  Standard_EXPORT void ClearSubs();

  //! Adds a sub-result
  Standard_EXPORT void AddSubResult(const occ::handle<Transfer_ResultFromTransient>& sub);

  //! Returns the count of recorded sub-results
  Standard_EXPORT int NbSubResults() const;

  //! Returns a sub-result, given its rank
  Standard_EXPORT occ::handle<Transfer_ResultFromTransient> SubResult(const int num) const;

  //! Returns the ResultFromTransient attached to a given starting
  //! entity (the key). Returns a null handle if not found
  Standard_EXPORT occ::handle<Transfer_ResultFromTransient> ResultFromKey(
    const occ::handle<Standard_Transient>& key) const;

  //! This method is used by ResultFromModel to collate the list of
  //! ResultFromTransient, avoiding duplications with a map
  //! Remark : <me> is already in the map and has not to be bound
  Standard_EXPORT void FillMap(NCollection_IndexedMap<occ::handle<Standard_Transient>>& map) const;

  //! Fills from a TransientProcess, with the starting entity which
  //! must have been set before. It works with scopes, calls Fill
  //! on each of its sub-results
  Standard_EXPORT void Fill(const occ::handle<Transfer_TransientProcess>& TP);

  //! Clears some data attached to binders used by TransientProcess,
  //! which become useless once the transfer has been done :
  //! the list of sub-scoped binders, which is now recorded as
  //! sub-results
  Standard_EXPORT void Strip();

  //! Fills back a TransientProcess with definition of a
  //! ResultFromTransient, respectfully to its structuration in
  //! scopes
  Standard_EXPORT void FillBack(const occ::handle<Transfer_TransientProcess>& TP) const;

  DEFINE_STANDARD_RTTIEXT(Transfer_ResultFromTransient, Standard_Transient)

private:
  occ::handle<Standard_Transient>                                     thestart;
  occ::handle<Transfer_Binder>                                        thebinder;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thesubs;
};
