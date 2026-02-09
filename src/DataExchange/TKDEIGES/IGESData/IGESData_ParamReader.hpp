#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_ReadStage.hpp>
#include <Interface_ParamType.hpp>
#include <Standard_CString.hpp>
#include <IGESData_Status.hpp>
#include <IGESData_ParamCursor.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_HAsciiString.hpp>
#include <IGESData_IGESEntity.hpp>

class Interface_ParamList;
class Interface_Check;
class IGESData_IGESEntity;
class IGESData_IGESReaderData;
class Message_Msg;
class gp_XY;
class gp_XYZ;
class TCollection_HAsciiString;
class Interface_EntityList;

class IGESData_ParamReader
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_ParamReader(const occ::handle<Interface_ParamList>& list,
                                       const occ::handle<Interface_Check>&     ach,
                                       const int                               base  = 1,
                                       const int                               nbpar = 0,
                                       const int                               num   = 0);

  Standard_EXPORT int EntityNumber() const;

  Standard_EXPORT void Clear();

  Standard_EXPORT int CurrentNumber() const;

  Standard_EXPORT void SetCurrentNumber(const int num);

  Standard_EXPORT IGESData_ReadStage Stage() const;

  Standard_EXPORT void NextStage();

  Standard_EXPORT void EndAll();

  Standard_EXPORT int NbParams() const;

  Standard_EXPORT Interface_ParamType ParamType(const int num) const;

  Standard_EXPORT const char* ParamValue(const int num) const;

  Standard_EXPORT bool IsParamDefined(const int num) const;

  Standard_EXPORT bool IsParamEntity(const int num) const;

  Standard_EXPORT int ParamNumber(const int num) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> ParamEntity(
    const occ::handle<IGESData_IGESReaderData>& IR,
    const int                                   num);

  Standard_EXPORT IGESData_ParamCursor Current() const;

  Standard_EXPORT IGESData_ParamCursor CurrentList(const int nb, const int size = 1) const;

  Standard_EXPORT bool DefinedElseSkip();

  Standard_EXPORT bool ReadInteger(const IGESData_ParamCursor& PC, int& val);

  Standard_EXPORT bool ReadInteger(const IGESData_ParamCursor& PC, const char* mess, int& val);

  Standard_EXPORT bool ReadBoolean(const IGESData_ParamCursor& PC,
                                   const Message_Msg&          amsg,
                                   bool&                       val,
                                   const bool                  exact = true);

  Standard_EXPORT bool ReadBoolean(const IGESData_ParamCursor& PC,
                                   const char*                 mess,
                                   bool&                       val,
                                   const bool                  exact = true);

  Standard_EXPORT bool ReadReal(const IGESData_ParamCursor& PC, double& val);

  Standard_EXPORT bool ReadReal(const IGESData_ParamCursor& PC, const char* mess, double& val);

  Standard_EXPORT bool ReadXY(const IGESData_ParamCursor& PC, Message_Msg& amsg, gp_XY& val);

  Standard_EXPORT bool ReadXY(const IGESData_ParamCursor& PC, const char* mess, gp_XY& val);

  Standard_EXPORT bool ReadXYZ(const IGESData_ParamCursor& PC, Message_Msg& amsg, gp_XYZ& val);

  Standard_EXPORT bool ReadXYZ(const IGESData_ParamCursor& PC, const char* mess, gp_XYZ& val);

  Standard_EXPORT bool ReadText(const IGESData_ParamCursor&            thePC,
                                const Message_Msg&                     theMsg,
                                occ::handle<TCollection_HAsciiString>& theVal);

  Standard_EXPORT bool ReadText(const IGESData_ParamCursor&            PC,
                                const char*                            mess,
                                occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT bool ReadEntity(const occ::handle<IGESData_IGESReaderData>& IR,
                                  const IGESData_ParamCursor&                 PC,
                                  IGESData_Status&                            aStatus,
                                  occ::handle<IGESData_IGESEntity>&           val,
                                  const bool                                  canbenul = false);

  Standard_EXPORT bool ReadEntity(const occ::handle<IGESData_IGESReaderData>& IR,
                                  const IGESData_ParamCursor&                 PC,
                                  const char*                                 mess,
                                  occ::handle<IGESData_IGESEntity>&           val,
                                  const bool                                  canbenul = false);

  Standard_EXPORT bool ReadEntity(const occ::handle<IGESData_IGESReaderData>& IR,
                                  const IGESData_ParamCursor&                 PC,
                                  IGESData_Status&                            aStatus,
                                  const occ::handle<Standard_Type>&           type,
                                  occ::handle<IGESData_IGESEntity>&           val,
                                  const bool                                  canbenul = false);

  template <class T>
  bool ReadEntity(const occ::handle<IGESData_IGESReaderData>& IR,
                  const IGESData_ParamCursor&                 PC,
                  IGESData_Status&                            aStatus,
                  const occ::handle<Standard_Type>&           type,
                  occ::handle<T>&                             val,
                  const bool                                  canbenul = false)
  {
    occ::handle<IGESData_IGESEntity> aVal = val;
    bool                             aRes = ReadEntity(IR, PC, aStatus, type, aVal, canbenul);
    val                                   = occ::down_cast<T>(aVal);
    return aRes && (canbenul || !val.IsNull());
  }

  Standard_EXPORT bool ReadEntity(const occ::handle<IGESData_IGESReaderData>& IR,
                                  const IGESData_ParamCursor&                 PC,
                                  const char*                                 mess,
                                  const occ::handle<Standard_Type>&           type,
                                  occ::handle<IGESData_IGESEntity>&           val,
                                  const bool                                  canbenul = false);

  template <class T>
  bool ReadEntity(const occ::handle<IGESData_IGESReaderData>& IR,
                  const IGESData_ParamCursor&                 PC,
                  const char*                                 mess,
                  const occ::handle<Standard_Type>&           type,
                  occ::handle<T>&                             val,
                  const bool                                  canbenul = false)
  {
    occ::handle<IGESData_IGESEntity> aVal = val;
    bool                             aRes = ReadEntity(IR, PC, mess, type, aVal, canbenul);
    val                                   = occ::down_cast<T>(aVal);
    return aRes && (canbenul || !val.IsNull());
  }

  Standard_EXPORT bool ReadInts(const IGESData_ParamCursor&            PC,
                                const Message_Msg&                     amsg,
                                occ::handle<NCollection_HArray1<int>>& val,
                                const int                              index = 1);

  Standard_EXPORT bool ReadInts(const IGESData_ParamCursor&            PC,
                                const char*                            mess,
                                occ::handle<NCollection_HArray1<int>>& val,
                                const int                              index = 1);

  Standard_EXPORT bool ReadReals(const IGESData_ParamCursor&               PC,
                                 Message_Msg&                              amsg,
                                 occ::handle<NCollection_HArray1<double>>& val,
                                 const int                                 index = 1);

  Standard_EXPORT bool ReadReals(const IGESData_ParamCursor&               PC,
                                 const char*                               mess,
                                 occ::handle<NCollection_HArray1<double>>& val,
                                 const int                                 index = 1);

  Standard_EXPORT bool ReadTexts(
    const IGESData_ParamCursor&                                              PC,
    const Message_Msg&                                                       amsg,
    occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& val,
    const int                                                                index = 1);

  Standard_EXPORT bool ReadTexts(
    const IGESData_ParamCursor&                                              PC,
    const char*                                                              mess,
    occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>>& val,
    const int                                                                index = 1);

  Standard_EXPORT bool ReadEnts(
    const occ::handle<IGESData_IGESReaderData>&                         IR,
    const IGESData_ParamCursor&                                         PC,
    const Message_Msg&                                                  amsg,
    occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& val,
    const int                                                           index = 1);

  Standard_EXPORT bool ReadEnts(
    const occ::handle<IGESData_IGESReaderData>&                         IR,
    const IGESData_ParamCursor&                                         PC,
    const char*                                                         mess,
    occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>>& val,
    const int                                                           index = 1);

  Standard_EXPORT bool ReadEntList(const occ::handle<IGESData_IGESReaderData>& IR,
                                   const IGESData_ParamCursor&                 PC,
                                   Message_Msg&                                amsg,
                                   Interface_EntityList&                       val,
                                   const bool                                  ord = true);

  Standard_EXPORT bool ReadEntList(const occ::handle<IGESData_IGESReaderData>& IR,
                                   const IGESData_ParamCursor&                 PC,
                                   const char*                                 mess,
                                   Interface_EntityList&                       val,
                                   const bool                                  ord = true);

  Standard_EXPORT bool ReadingReal(const int num, double& val);

  Standard_EXPORT bool ReadingReal(const int num, const char* mess, double& val);

  Standard_EXPORT bool ReadingEntityNumber(const int num, int& val);

  Standard_EXPORT bool ReadingEntityNumber(const int num, const char* mess, int& val);

  Standard_EXPORT void SendFail(const Message_Msg& amsg);

  Standard_EXPORT void SendWarning(const Message_Msg& amsg);

  Standard_EXPORT void AddFail(const char* afail, const char* bfail = "");

  Standard_EXPORT void AddFail(const occ::handle<TCollection_HAsciiString>& af,
                               const occ::handle<TCollection_HAsciiString>& bf);

  Standard_EXPORT void AddWarning(const char* awarn, const char* bwarn = "");

  Standard_EXPORT void AddWarning(const occ::handle<TCollection_HAsciiString>& aw,
                                  const occ::handle<TCollection_HAsciiString>& bw);

  Standard_EXPORT void Mend(const char* pref = "");

  Standard_EXPORT bool HasFailed() const;

  Standard_EXPORT const occ::handle<Interface_Check>& Check() const;

  Standard_EXPORT occ::handle<Interface_Check>& CCheck();

  Standard_EXPORT bool IsCheckEmpty() const;

private:
  Standard_EXPORT bool PrepareRead(const IGESData_ParamCursor& PC,
                                   const bool                  several,
                                   const int                   size = 1);

  Standard_EXPORT bool PrepareRead(const IGESData_ParamCursor& PC,
                                   const char*                 mess,
                                   const bool                  several,
                                   const int                   size = 1);

  Standard_EXPORT int FirstRead(const int nb = 1);

  Standard_EXPORT int NextRead(const int nb = 1);

  Standard_EXPORT void AddFail(const char*                                  idm,
                               const occ::handle<TCollection_HAsciiString>& af,
                               const occ::handle<TCollection_HAsciiString>& bf);

  Standard_EXPORT void AddFail(const char* idm, const char* afail, const char* bfail);

  Standard_EXPORT void AddWarning(const char*                                  idm,
                                  const occ::handle<TCollection_HAsciiString>& aw,
                                  const occ::handle<TCollection_HAsciiString>& bw);

  Standard_EXPORT void AddWarning(const char* idm, const char* aw, const char* bw);

  occ::handle<Interface_ParamList> theparams;
  occ::handle<Interface_Check>     thecheck;
  int                              thebase;
  int                              thenbpar;
  int                              thecurr;
  IGESData_ReadStage               thestage;
  bool                             thelast;
  int                              theindex;
  int                              thenbitem;
  int                              theitemsz;
  int                              theoffset;
  int                              thetermsz;
  int                              themaxind;
  int                              thenbterm;
  int                              pbrealint;
  int                              pbrealform;
  int                              thenum;
};
