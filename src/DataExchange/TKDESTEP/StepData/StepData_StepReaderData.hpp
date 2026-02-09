#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <Resource_FormatType.hpp>

#include <TCollection_AsciiString.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <Interface_FileReaderData.hpp>
#include <Standard_CString.hpp>
#include <Interface_ParamType.hpp>
#include <NCollection_Sequence.hpp>
#include <StepData_Logical.hpp>
class Interface_Check;
class TCollection_AsciiString;
class StepData_PDescr;
class Standard_Transient;
class StepData_SelectMember;
class StepData_Field;
class StepData_ESDescr;
class StepData_FieldList;
class StepData_SelectType;
class TCollection_HAsciiString;
class StepData_EnumTool;

class StepData_StepReaderData : public Interface_FileReaderData
{

public:
  Standard_EXPORT StepData_StepReaderData(
    const int                 nbheader,
    const int                 nbtotal,
    const int                 nbpar,
    const Resource_FormatType theSourceCodePage = Resource_FormatType_UTF8);

  Standard_EXPORT void SetRecord(const int   num,
                                 const char* ident,
                                 const char* type,
                                 const int   nbpar);

  Standard_EXPORT void AddStepParam(const int                 num,
                                    const char*               aval,
                                    const Interface_ParamType atype,
                                    const int                 nument = 0);

  Standard_EXPORT const TCollection_AsciiString& RecordType(const int num) const;

  Standard_EXPORT const char* CType(const int num) const;

  Standard_EXPORT int RecordIdent(const int num) const;

  Standard_EXPORT int SubListNumber(const int num, const int nump, const bool aslast) const;

  Standard_EXPORT bool IsComplex(const int num) const;

  Standard_EXPORT void ComplexType(const int                                      num,
                                   NCollection_Sequence<TCollection_AsciiString>& types) const;

  Standard_EXPORT int NextForComplex(const int num) const;

  Standard_EXPORT bool NamedForComplex(const char*                   name,
                                       const int                     num0,
                                       int&                          num,
                                       occ::handle<Interface_Check>& ach) const;

  Standard_EXPORT bool NamedForComplex(const char*                   theName,
                                       const char*                   theShortName,
                                       const int                     num0,
                                       int&                          num,
                                       occ::handle<Interface_Check>& ach) const;

  Standard_EXPORT bool CheckNbParams(const int                     num,
                                     const int                     nbreq,
                                     occ::handle<Interface_Check>& ach,
                                     const char*                   mess = "") const;

  Standard_EXPORT bool ReadSubList(const int                     num,
                                   const int                     nump,
                                   const char*                   mess,
                                   occ::handle<Interface_Check>& ach,
                                   int&                          numsub,
                                   const bool                    optional = false,
                                   const int                     lenmin   = 0,
                                   const int                     lenmax   = 0) const;

  Standard_EXPORT int ReadSub(const int                           numsub,
                              const char*                         mess,
                              occ::handle<Interface_Check>&       ach,
                              const occ::handle<StepData_PDescr>& descr,
                              occ::handle<Standard_Transient>&    val) const;

  Standard_EXPORT bool ReadMember(const int                           num,
                                  const int                           nump,
                                  const char*                         mess,
                                  occ::handle<Interface_Check>&       ach,
                                  occ::handle<StepData_SelectMember>& val) const;

  template <class T>
  bool ReadMember(const int                     num,
                  const int                     nump,
                  const char*                   mess,
                  occ::handle<Interface_Check>& ach,
                  occ::handle<T>&               val) const
  {
    occ::handle<StepData_SelectMember> aVal = val;
    return ReadMember(num, nump, mess, ach, aVal) && !(val = occ::down_cast<T>(aVal)).IsNull();
  }

  Standard_EXPORT bool ReadField(const int                           num,
                                 const int                           nump,
                                 const char*                         mess,
                                 occ::handle<Interface_Check>&       ach,
                                 const occ::handle<StepData_PDescr>& descr,
                                 StepData_Field&                     fild) const;

  Standard_EXPORT bool ReadList(const int                            num,
                                occ::handle<Interface_Check>&        ach,
                                const occ::handle<StepData_ESDescr>& descr,
                                StepData_FieldList&                  list) const;

  Standard_EXPORT bool ReadAny(const int                           num,
                               const int                           nump,
                               const char*                         mess,
                               occ::handle<Interface_Check>&       ach,
                               const occ::handle<StepData_PDescr>& descr,
                               occ::handle<Standard_Transient>&    val) const;

  Standard_EXPORT bool ReadXY(const int                     num,
                              const int                     nump,
                              const char*                   mess,
                              occ::handle<Interface_Check>& ach,
                              double&                       X,
                              double&                       Y) const;

  Standard_EXPORT bool ReadXYZ(const int                     num,
                               const int                     nump,
                               const char*                   mess,
                               occ::handle<Interface_Check>& ach,
                               double&                       X,
                               double&                       Y,
                               double&                       Z) const;

  Standard_EXPORT bool ReadReal(const int                     num,
                                const int                     nump,
                                const char*                   mess,
                                occ::handle<Interface_Check>& ach,
                                double&                       val) const;

  Standard_EXPORT bool ReadEntity(const int                         num,
                                  const int                         nump,
                                  const char*                       mess,
                                  occ::handle<Interface_Check>&     ach,
                                  const occ::handle<Standard_Type>& atype,
                                  occ::handle<Standard_Transient>&  ent) const;

  template <class T>
  bool ReadEntity(const int                         num,
                  const int                         nump,
                  const char*                       mess,
                  occ::handle<Interface_Check>&     ach,
                  const occ::handle<Standard_Type>& atype,
                  occ::handle<T>&                   ent) const
  {
    occ::handle<Standard_Transient> anEnt = ent;
    return ReadEntity(num, nump, mess, ach, atype, anEnt)
           && !(ent = occ::down_cast<T>(anEnt)).IsNull();
  }

  Standard_EXPORT bool ReadEntity(const int                     num,
                                  const int                     nump,
                                  const char*                   mess,
                                  occ::handle<Interface_Check>& ach,
                                  StepData_SelectType&          sel) const;

  Standard_EXPORT bool ReadInteger(const int                     num,
                                   const int                     nump,
                                   const char*                   mess,
                                   occ::handle<Interface_Check>& ach,
                                   int&                          val) const;

  Standard_EXPORT bool ReadBoolean(const int                     num,
                                   const int                     nump,
                                   const char*                   mess,
                                   occ::handle<Interface_Check>& ach,
                                   bool&                         flag) const;

  Standard_EXPORT bool ReadLogical(const int                     num,
                                   const int                     nump,
                                   const char*                   mess,
                                   occ::handle<Interface_Check>& ach,
                                   StepData_Logical&             flag) const;

  Standard_EXPORT bool ReadString(const int                              num,
                                  const int                              nump,
                                  const char*                            mess,
                                  occ::handle<Interface_Check>&          ach,
                                  occ::handle<TCollection_HAsciiString>& val) const;

  Standard_EXPORT bool ReadEnumParam(const int                     num,
                                     const int                     nump,
                                     const char*                   mess,
                                     occ::handle<Interface_Check>& ach,
                                     const char*&                  text) const;

  Standard_EXPORT void FailEnumValue(const int                     num,
                                     const int                     nump,
                                     const char*                   mess,
                                     occ::handle<Interface_Check>& ach) const;

  Standard_EXPORT bool ReadEnum(const int                     num,
                                const int                     nump,
                                const char*                   mess,
                                occ::handle<Interface_Check>& ach,
                                const StepData_EnumTool&      enumtool,
                                int&                          val) const;

  Standard_EXPORT bool ReadTypedParam(const int                     num,
                                      const int                     nump,
                                      const bool                    mustbetyped,
                                      const char*                   mess,
                                      occ::handle<Interface_Check>& ach,
                                      int&                          numr,
                                      int&                          numrp,
                                      TCollection_AsciiString&      typ) const;

  Standard_EXPORT bool CheckDerived(const int                     num,
                                    const int                     nump,
                                    const char*                   mess,
                                    occ::handle<Interface_Check>& ach,
                                    const bool                    errstat = false) const;

  Standard_EXPORT int NbEntities() const override;

  Standard_EXPORT int FindNextRecord(const int num) const override;

  Standard_EXPORT void SetEntityNumbers(const bool withmap = true);

  Standard_EXPORT int FindNextHeaderRecord(const int num) const;

  Standard_EXPORT void PrepareHeader();

  Standard_EXPORT const occ::handle<Interface_Check> GlobalCheck() const;

  DEFINE_STANDARD_RTTIEXT(StepData_StepReaderData, Interface_FileReaderData)

private:
  Standard_EXPORT int FindEntityNumber(const int num, const int id) const;

  Standard_EXPORT void cleanText(const occ::handle<TCollection_HAsciiString>& theVal) const;

private:
  NCollection_Array1<int>                         theidents;
  NCollection_Array1<int>                         thetypes;
  NCollection_IndexedMap<TCollection_AsciiString> thenametypes;
  NCollection_DataMap<int, int>                   themults;
  int                                             thenbents;
  int                                             thelastn;
  int                                             thenbhead;
  int                                             thenbscop;
  occ::handle<Interface_Check>                    thecheck;
  Resource_FormatType                             mySourceCodePage;
};
