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

class Transfer_ResultFromTransient : public Standard_Transient
{

public:
  Standard_EXPORT Transfer_ResultFromTransient();

  Standard_EXPORT void SetStart(const occ::handle<Standard_Transient>& start);

  Standard_EXPORT void SetBinder(const occ::handle<Transfer_Binder>& binder);

  Standard_EXPORT occ::handle<Standard_Transient> Start() const;

  Standard_EXPORT occ::handle<Transfer_Binder> Binder() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT const occ::handle<Interface_Check> Check() const;

  Standard_EXPORT Interface_CheckStatus CheckStatus() const;

  Standard_EXPORT void ClearSubs();

  Standard_EXPORT void AddSubResult(const occ::handle<Transfer_ResultFromTransient>& sub);

  Standard_EXPORT int NbSubResults() const;

  Standard_EXPORT occ::handle<Transfer_ResultFromTransient> SubResult(const int num) const;

  Standard_EXPORT occ::handle<Transfer_ResultFromTransient> ResultFromKey(
    const occ::handle<Standard_Transient>& key) const;

  Standard_EXPORT void FillMap(NCollection_IndexedMap<occ::handle<Standard_Transient>>& map) const;

  Standard_EXPORT void Fill(const occ::handle<Transfer_TransientProcess>& TP);

  Standard_EXPORT void Strip();

  Standard_EXPORT void FillBack(const occ::handle<Transfer_TransientProcess>& TP) const;

  DEFINE_STANDARD_RTTIEXT(Transfer_ResultFromTransient, Standard_Transient)

private:
  occ::handle<Standard_Transient>                                     thestart;
  occ::handle<Transfer_Binder>                                        thebinder;
  occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> thesubs;
};
