#pragma once

#include <Standard.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <Interface_CheckStatus.hpp>
class Message_Msg;
class TCollection_HAsciiString;

#ifdef Status
  #undef Status
#endif

class Interface_Check : public Standard_Transient
{

public:
  Standard_EXPORT Interface_Check();

  Standard_EXPORT Interface_Check(const occ::handle<Standard_Transient>& anentity);

  Standard_EXPORT void SendFail(const Message_Msg& amsg);

  Standard_EXPORT void AddFail(const occ::handle<TCollection_HAsciiString>& amess);

  Standard_EXPORT void AddFail(const occ::handle<TCollection_HAsciiString>& amess,
                               const occ::handle<TCollection_HAsciiString>& orig);

  Standard_EXPORT void AddFail(const char* amess, const char* orig = "");

  Standard_EXPORT void AddFail(const Message_Msg& amsg);

  Standard_EXPORT bool HasFailed() const;

  Standard_EXPORT int NbFails() const;

  Standard_EXPORT const occ::handle<TCollection_HAsciiString>& Fail(const int  num,
                                                                    const bool final = true) const;

  Standard_EXPORT const char* CFail(const int num, const bool final = true) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> Fails(
    const bool final = true) const;

  Standard_EXPORT void SendWarning(const Message_Msg& amsg);

  Standard_EXPORT void AddWarning(const occ::handle<TCollection_HAsciiString>& amess);

  Standard_EXPORT void AddWarning(const occ::handle<TCollection_HAsciiString>& amess,
                                  const occ::handle<TCollection_HAsciiString>& orig);

  Standard_EXPORT void AddWarning(const char* amess, const char* orig = "");

  Standard_EXPORT void AddWarning(const Message_Msg& amsg);

  Standard_EXPORT bool HasWarnings() const;

  Standard_EXPORT int NbWarnings() const;

  Standard_EXPORT const occ::handle<TCollection_HAsciiString>& Warning(
    const int  num,
    const bool final = true) const;

  Standard_EXPORT const char* CWarning(const int num, const bool final = true) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  Warnings(const bool final = true) const;

  Standard_EXPORT void SendMsg(const Message_Msg& amsg);

  Standard_EXPORT int NbInfoMsgs() const;

  Standard_EXPORT const occ::handle<TCollection_HAsciiString>& InfoMsg(
    const int  num,
    const bool final = true) const;

  Standard_EXPORT const char* CInfoMsg(const int num, const bool final = true) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  InfoMsgs(const bool final = true) const;

  Standard_EXPORT Interface_CheckStatus Status() const;

  Standard_EXPORT bool Complies(const Interface_CheckStatus status) const;

  Standard_EXPORT bool Complies(const occ::handle<TCollection_HAsciiString>& mess,
                                const int                                    incl,
                                const Interface_CheckStatus                  status) const;

  Standard_EXPORT bool HasEntity() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Entity() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT void ClearFails();

  Standard_EXPORT void ClearWarnings();

  Standard_EXPORT void ClearInfoMsgs();

  Standard_EXPORT bool Remove(const occ::handle<TCollection_HAsciiString>& mess,
                              const int                                    incl,
                              const Interface_CheckStatus                  status);

  Standard_EXPORT bool Mend(const char* pref, const int num = 0);

  Standard_EXPORT void SetEntity(const occ::handle<Standard_Transient>& anentity);

  Standard_EXPORT void GetEntity(const occ::handle<Standard_Transient>& anentity);

  Standard_EXPORT void GetMessages(const occ::handle<Interface_Check>& other);

  Standard_EXPORT void GetAsWarning(const occ::handle<Interface_Check>& other,
                                    const bool                          failsonly);

  Standard_EXPORT void Print(Standard_OStream& S, const int level, const int final = 1) const;

  Standard_EXPORT void Trace(const int level = -1, const int final = 1) const;

  DEFINE_STANDARD_RTTIEXT(Interface_Check, Standard_Transient)

private:
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thefails;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thefailo;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thewarns;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thewarno;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> theinfos;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> theinfoo;
  occ::handle<Standard_Transient>                                           theent;
};
