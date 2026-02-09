#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>
#include <Interface_CheckStatus.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Interface_InterfaceModel;
class Transfer_ResultFromTransient;
class Transfer_TransientProcess;
class Interface_CheckIterator;

class Transfer_ResultFromModel : public Standard_Transient
{

public:
  Standard_EXPORT Transfer_ResultFromModel();

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT void SetFileName(const char* filename);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT const char* FileName() const;

  Standard_EXPORT bool Fill(const occ::handle<Transfer_TransientProcess>& TP,
                            const occ::handle<Standard_Transient>&        ent);

  Standard_EXPORT void Strip(const int mode);

  Standard_EXPORT void FillBack(const occ::handle<Transfer_TransientProcess>& TP) const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT occ::handle<Transfer_ResultFromTransient> MainResult() const;

  Standard_EXPORT void SetMainResult(const occ::handle<Transfer_ResultFromTransient>& amain);

  Standard_EXPORT const char* MainLabel() const;

  Standard_EXPORT int MainNumber() const;

  Standard_EXPORT occ::handle<Transfer_ResultFromTransient> ResultFromKey(
    const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Results(
    const int level) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
                  TransferredList(const int level = 2) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> CheckedList(
    const Interface_CheckStatus check,
    const bool                  result) const;

  Standard_EXPORT Interface_CheckIterator CheckList(const bool erronly, const int level = 2) const;

  Standard_EXPORT Interface_CheckStatus CheckStatus() const;

  Standard_EXPORT Interface_CheckStatus ComputeCheckStatus(const bool enforce);

  DEFINE_STANDARD_RTTIEXT(Transfer_ResultFromModel, Standard_Transient)

private:
  occ::handle<Interface_InterfaceModel>     themodel;
  TCollection_AsciiString                   thename;
  occ::handle<Transfer_ResultFromTransient> themain;
  TCollection_AsciiString                   themlab;
  int                                       themnum;
  Interface_CheckStatus                     themchk;
};
