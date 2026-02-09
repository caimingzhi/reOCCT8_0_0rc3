#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Transfer_Binder.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Type.hpp>
#include <Transfer_StatusExec.hpp>
class Transfer_Binder;
class Standard_Transient;
class Interface_Check;

#ifdef Status
  #undef Status
#endif

class Transfer_TransferIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Transfer_TransferIterator();

  Standard_EXPORT void AddItem(const occ::handle<Transfer_Binder>& atr);

  Standard_EXPORT void SelectBinder(const occ::handle<Standard_Type>& atype, const bool keep);

  Standard_EXPORT void SelectResult(const occ::handle<Standard_Type>& atype, const bool keep);

  Standard_EXPORT void SelectUnique(const bool keep);

  Standard_EXPORT void SelectItem(const int num, const bool keep);

  Standard_EXPORT int Number() const;

  Standard_EXPORT void Start();

  Standard_EXPORT bool More();

  Standard_EXPORT void Next();

  Standard_EXPORT const occ::handle<Transfer_Binder>& Value() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT bool HasUniqueResult() const;

  Standard_EXPORT occ::handle<Standard_Type> ResultType() const;

  Standard_EXPORT bool HasTransientResult() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& TransientResult() const;

  Standard_EXPORT Transfer_StatusExec Status() const;

  Standard_EXPORT bool HasFails() const;

  Standard_EXPORT bool HasWarnings() const;

  Standard_EXPORT const occ::handle<Interface_Check> Check() const;

protected:
  int thecurr;

private:
  occ::handle<NCollection_HSequence<occ::handle<Transfer_Binder>>> theitems;
  occ::handle<NCollection_HSequence<int>>                          theselect;
  int                                                              themaxi;
};
