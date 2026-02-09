#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <IFSelect_Activator.hpp>
#include <IFSelect_ReturnStatus.hpp>
#include <IFSelect_PrintCount.hpp>
class IFSelect_WorkSession;
class IFSelect_WorkLibrary;
class IFSelect_SignCounter;

class IFSelect_SessionPilot : public IFSelect_Activator
{

public:
  Standard_EXPORT IFSelect_SessionPilot(const char* prompt = "");

  Standard_EXPORT occ::handle<IFSelect_WorkSession> Session() const;

  Standard_EXPORT occ::handle<IFSelect_WorkLibrary> Library() const;

  Standard_EXPORT bool RecordMode() const;

  Standard_EXPORT void SetSession(const occ::handle<IFSelect_WorkSession>& WS);

  Standard_EXPORT void SetLibrary(const occ::handle<IFSelect_WorkLibrary>& WL);

  Standard_EXPORT void SetRecordMode(const bool mode);

  Standard_EXPORT void SetCommandLine(const TCollection_AsciiString& command);

  Standard_EXPORT const TCollection_AsciiString& CommandLine() const;

  Standard_EXPORT const char* CommandPart(const int numarg = 0) const;

  Standard_EXPORT int NbWords() const;

  Standard_EXPORT const TCollection_AsciiString& Word(const int num) const;

  Standard_EXPORT const char* Arg(const int num) const;

  Standard_EXPORT bool RemoveWord(const int num);

  Standard_EXPORT int NbCommands() const;

  Standard_EXPORT const TCollection_AsciiString& Command(const int num) const;

  Standard_EXPORT IFSelect_ReturnStatus RecordItem(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT occ::handle<Standard_Transient> RecordedItem() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT IFSelect_ReturnStatus ReadScript(const char* file = "");

  Standard_EXPORT IFSelect_ReturnStatus Perform();

  Standard_EXPORT IFSelect_ReturnStatus ExecuteAlias(const TCollection_AsciiString& aliasname);

  Standard_EXPORT IFSelect_ReturnStatus Execute(const TCollection_AsciiString& command);

  Standard_EXPORT IFSelect_ReturnStatus
    ExecuteCounter(const occ::handle<IFSelect_SignCounter>& counter,
                   const int                                numword,
                   const IFSelect_PrintCount                mode = IFSelect_CountByItem);

  Standard_EXPORT int Number(const char* val) const;

  Standard_EXPORT IFSelect_ReturnStatus
    Do(const int number, const occ::handle<IFSelect_SessionPilot>& session) override;

  Standard_EXPORT const char* Help(const int number) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SessionPilot, IFSelect_Activator)

private:
  occ::handle<IFSelect_WorkSession>             thesession;
  TCollection_AsciiString                       theprompt;
  TCollection_AsciiString                       thecommand;
  int                                           thenbwords;
  NCollection_Array1<TCollection_AsciiString>   thewords;
  NCollection_Array1<int>                       thewordeb;
  bool                                          therecord;
  int                                           thenumrec;
  occ::handle<Standard_Transient>               theobjrec;
  NCollection_Sequence<TCollection_AsciiString> thecomlist;
};
