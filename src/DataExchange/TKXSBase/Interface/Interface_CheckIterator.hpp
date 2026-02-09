#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Interface_Check.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_CString.hpp>
#include <Interface_CheckStatus.hpp>
#include <Standard_Transient.hpp>
class Interface_InterfaceModel;
class Interface_IntVal;
class Interface_Check;
class Standard_Transient;

#ifdef Status
  #undef Status
#endif

class Interface_CheckIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Interface_CheckIterator();

  Standard_EXPORT Interface_CheckIterator(const char* name);

  Standard_EXPORT void SetName(const char* name);

  Standard_EXPORT const char* Name() const;

  Standard_EXPORT void SetModel(const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT occ::handle<Interface_InterfaceModel> Model() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT void Merge(Interface_CheckIterator& other);

  Standard_EXPORT void Add(const occ::handle<Interface_Check>& ach, const int num = 0);

  Standard_EXPORT const occ::handle<Interface_Check>& Check(const int num) const;

  Standard_EXPORT const occ::handle<Interface_Check>& Check(
    const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT occ::handle<Interface_Check>& CCheck(const int num);

  Standard_EXPORT occ::handle<Interface_Check>& CCheck(const occ::handle<Standard_Transient>& ent);

  Standard_EXPORT bool IsEmpty(const bool failsonly) const;

  Standard_EXPORT Interface_CheckStatus Status() const;

  Standard_EXPORT bool Complies(const Interface_CheckStatus status) const;

  Standard_EXPORT Interface_CheckIterator Extract(const Interface_CheckStatus status) const;

  Standard_EXPORT Interface_CheckIterator Extract(const char*                 mess,
                                                  const int                   incl,
                                                  const Interface_CheckStatus status) const;

  Standard_EXPORT bool Remove(const char* mess, const int incl, const Interface_CheckStatus status);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Checkeds(
    const bool failsonly,
    const bool global) const;

  Standard_EXPORT void Start() const;

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next() const;

  Standard_EXPORT const occ::handle<Interface_Check>& Value() const;

  Standard_EXPORT int Number() const;

  Standard_EXPORT void Print(Standard_OStream& S, const bool failsonly, const int final = 0) const;

  Standard_EXPORT void Print(Standard_OStream&                            S,
                             const occ::handle<Interface_InterfaceModel>& model,
                             const bool                                   failsonly,
                             const int                                    final = 0) const;

  Standard_EXPORT void Destroy();

  ~Interface_CheckIterator() { Destroy(); }

private:
  occ::handle<NCollection_HSequence<occ::handle<Interface_Check>>> thelist;
  occ::handle<NCollection_HSequence<int>>                          thenums;
  occ::handle<Interface_InterfaceModel>                            themod;
  TCollection_AsciiString                                          thename;
  occ::handle<Interface_IntVal>                                    thecurr;
};
