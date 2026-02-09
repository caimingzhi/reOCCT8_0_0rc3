#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Interface_LineBuffer.hpp>
#include <Standard_Integer.hpp>
#include <Interface_FloatWriter.hpp>
#include <Interface_CheckIterator.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_CString.hpp>
#include <StepData_Logical.hpp>
#include <Standard_OStream.hpp>
class StepData_StepModel;
class StepData_Protocol;
class StepData_WriterLib;
class TCollection_AsciiString;
class TCollection_HAsciiString;
class StepData_Field;
class StepData_PDescr;
class StepData_SelectMember;
class StepData_FieldList;
class StepData_ESDescr;
class Standard_Transient;

class StepData_StepWriter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepData_StepWriter(const occ::handle<StepData_StepModel>& amodel);

  Standard_EXPORT int& LabelMode();

  Standard_EXPORT int& TypeMode();

  Standard_EXPORT Interface_FloatWriter& FloatWriter();

  Standard_EXPORT void SetScope(const int numscope, const int numin);

  Standard_EXPORT bool IsInScope(const int num) const;

  Standard_EXPORT void SendModel(const occ::handle<StepData_Protocol>& protocol,
                                 const bool                            headeronly = false);

  Standard_EXPORT void SendHeader();

  Standard_EXPORT void SendData();

  Standard_EXPORT void SendEntity(const int nument, const StepData_WriterLib& lib);

  Standard_EXPORT void EndSec();

  Standard_EXPORT void EndFile();

  Standard_EXPORT void NewLine(const bool evenempty);

  Standard_EXPORT void JoinLast(const bool newline);

  Standard_EXPORT void Indent(const bool onent);

  Standard_EXPORT void SendIdent(const int ident);

  Standard_EXPORT void SendScope();

  Standard_EXPORT void SendEndscope();

  Standard_EXPORT void Comment(const bool mode);

  Standard_EXPORT void SendComment(const occ::handle<TCollection_HAsciiString>& text);

  Standard_EXPORT void SendComment(const char* text);

  Standard_EXPORT void StartEntity(const TCollection_AsciiString& atype);

  Standard_EXPORT void StartComplex();

  Standard_EXPORT void EndComplex();

  Standard_EXPORT void SendField(const StepData_Field&               fild,
                                 const occ::handle<StepData_PDescr>& descr);

  Standard_EXPORT void SendSelect(const occ::handle<StepData_SelectMember>& sm,
                                  const occ::handle<StepData_PDescr>&       descr);

  Standard_EXPORT void SendList(const StepData_FieldList&            list,
                                const occ::handle<StepData_ESDescr>& descr);

  Standard_EXPORT void OpenSub();

  Standard_EXPORT void OpenTypedSub(const char* subtype);

  Standard_EXPORT void CloseSub();

  Standard_EXPORT void AddParam();

  Standard_EXPORT void Send(const int val);

  Standard_EXPORT void Send(const double val);

  Standard_EXPORT void Send(const TCollection_AsciiString& val);

  Standard_EXPORT void Send(const occ::handle<Standard_Transient>& val);

  Standard_EXPORT void SendBoolean(const bool val);

  Standard_EXPORT void SendLogical(const StepData_Logical val);

  Standard_EXPORT void SendString(const TCollection_AsciiString& val);

  Standard_EXPORT void SendString(const char* val);

  Standard_EXPORT void SendEnum(const TCollection_AsciiString& val);

  Standard_EXPORT void SendEnum(const char* val);

  Standard_EXPORT void SendArrReal(const occ::handle<NCollection_HArray1<double>>& anArr);

  Standard_EXPORT void SendUndef();

  Standard_EXPORT void SendDerived();

  Standard_EXPORT void EndEntity();

  Standard_EXPORT Interface_CheckIterator CheckList() const;

  Standard_EXPORT int NbLines() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Line(const int num) const;

  Standard_EXPORT bool Print(Standard_OStream& S);

  Standard_EXPORT static TCollection_AsciiString CleanTextForSend(
    const TCollection_AsciiString& theText);

private:
  Standard_EXPORT void AddString(const TCollection_AsciiString& str, const int more = 0);

  Standard_EXPORT void AddString(const char* str, const int lnstr, const int more = 0);

  occ::handle<StepData_StepModel>                                           themodel;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thefile;
  Interface_LineBuffer                                                      thecurr;
  bool                                                                      thesect;
  bool                                                                      thecomm;
  bool                                                                      thefirst;
  bool                                                                      themult;
  int                                                                       thelevel;
  bool                                                                      theindent;
  int                                                                       theindval;
  int                                                                       thetypmode;
  Interface_FloatWriter                                                     thefloatw;
  Interface_CheckIterator                                                   thechecks;
  int                                                                       thenum;
  int                                                                       thelabmode;
  occ::handle<NCollection_HArray1<int>>                                     thescopebeg;
  occ::handle<NCollection_HArray1<int>>                                     thescopeend;
  occ::handle<NCollection_HArray1<int>>                                     thescopenext;
};
