#pragma once

#include <NCollection_DataMap.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_CString.hpp>

class IFSelect_WorkSession;
class Standard_Transient;

class IFSelect_SessionFile
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IFSelect_SessionFile(const occ::handle<IFSelect_WorkSession>& WS);

  Standard_EXPORT IFSelect_SessionFile(const occ::handle<IFSelect_WorkSession>& WS,
                                       const char*                              filename);

  Standard_EXPORT void ClearLines();

  Standard_EXPORT int NbLines() const;

  Standard_EXPORT const TCollection_AsciiString& Line(const int num) const;

  Standard_EXPORT void AddLine(const char* line);

  Standard_EXPORT void RemoveLastLine();

  Standard_EXPORT bool WriteFile(const char* name);

  Standard_EXPORT bool ReadFile(const char* name);

  Standard_EXPORT bool RecognizeFile(const char* headerline);

  Standard_EXPORT int Write(const char* filename);

  Standard_EXPORT int Read(const char* filename);

  Standard_EXPORT int WriteSession();

  Standard_EXPORT int WriteEnd();

  Standard_EXPORT void WriteLine(const char* line, const char follow = 0);

  Standard_EXPORT bool WriteOwn(const occ::handle<Standard_Transient>& item);

  Standard_EXPORT int ReadSession();

  Standard_EXPORT int ReadEnd();

  Standard_EXPORT bool ReadLine();

  Standard_EXPORT void SplitLine(const char* line);

  Standard_EXPORT bool ReadOwn(occ::handle<Standard_Transient>& item);

  Standard_EXPORT void AddItem(const occ::handle<Standard_Transient>& item,
                               const bool                             active = true);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<IFSelect_WorkSession> WorkSession() const;

  Standard_EXPORT void NewItem(const int ident, const occ::handle<Standard_Transient>& par);

  Standard_EXPORT void SetOwn(const bool mode);

  Standard_EXPORT void SendVoid();

  Standard_EXPORT void SendItem(const occ::handle<Standard_Transient>& par);

  Standard_EXPORT void SendText(const char* text);

  Standard_EXPORT void SetLastGeneral(const int lastgen);

  Standard_EXPORT int NbParams() const;

  Standard_EXPORT bool IsVoid(const int num) const;

  Standard_EXPORT bool IsText(const int num) const;

  Standard_EXPORT const TCollection_AsciiString& ParamValue(const int num) const;

  Standard_EXPORT TCollection_AsciiString TextValue(const int num) const;

  Standard_EXPORT occ::handle<Standard_Transient> ItemValue(const int num) const;

  Standard_EXPORT void Destroy();

  ~IFSelect_SessionFile() { Destroy(); }

protected:
  occ::handle<IFSelect_WorkSession>                 thesess;
  occ::handle<NCollection_HArray1<int>>             thenums;
  NCollection_DataMap<TCollection_AsciiString, int> thenames;
  int                                               thenl;
  NCollection_Sequence<TCollection_AsciiString>     theline;

private:
  bool                                          themode;
  NCollection_Sequence<TCollection_AsciiString> thelist;
  TCollection_AsciiString                       thebuff;
  int                                           thelastgen;
  bool                                          thedone;
  bool                                          theownflag;
  int                                           thenewnum;
};
