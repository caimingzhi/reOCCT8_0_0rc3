#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>

enum Interface_DataState
{
  Interface_StateOK,
  Interface_LoadWarning,
  Interface_LoadFail,
  Interface_DataWarning,
  Interface_DataFail,
  Interface_StateUnloaded,
  Interface_StateUnknown
};

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
class Interface_Check;
class TCollection_HAsciiString;
class Interface_GTool;
class Interface_Protocol;
class Interface_ReportEntity;
class Interface_CheckIterator;
class Interface_GeneralLib;
class Interface_EntityIterator;

class Interface_InterfaceModel : public Standard_Transient
{

public:
  Standard_EXPORT void Destroy();

  ~Interface_InterfaceModel() override { Destroy(); }

  Standard_EXPORT void SetProtocol(const occ::handle<Interface_Protocol>& proto);

  Standard_EXPORT virtual occ::handle<Interface_Protocol> Protocol() const;

  Standard_EXPORT void SetGTool(const occ::handle<Interface_GTool>& gtool);

  Standard_EXPORT occ::handle<Interface_GTool> GTool() const;

  Standard_EXPORT bool& DispatchStatus();

  Standard_EXPORT virtual void Clear();

  Standard_EXPORT virtual void ClearEntities();

  Standard_EXPORT virtual void ClearLabels() = 0;

  Standard_EXPORT virtual void ClearHeader() = 0;

  Standard_EXPORT int NbEntities() const;

  Standard_EXPORT bool Contains(const occ::handle<Standard_Transient>& anentity) const;

  Standard_EXPORT int Number(const occ::handle<Standard_Transient>& anentity) const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Value(const int num) const;

  Standard_EXPORT int NbTypes(const occ::handle<Standard_Transient>& ent) const;

  Standard_EXPORT occ::handle<Standard_Type> Type(const occ::handle<Standard_Transient>& ent,
                                                  const int num = 1) const;

  Standard_EXPORT const char* TypeName(const occ::handle<Standard_Transient>& ent,
                                       const bool complete = true) const;

  Standard_EXPORT static const char* ClassName(const char* typnam);

  Standard_EXPORT Interface_DataState EntityState(const int num) const;

  Standard_EXPORT bool IsReportEntity(const int num, const bool semantic = false) const;

  Standard_EXPORT occ::handle<Interface_ReportEntity> ReportEntity(
    const int  num,
    const bool semantic = false) const;

  Standard_EXPORT bool IsErrorEntity(const int num) const;

  Standard_EXPORT bool IsRedefinedContent(const int num) const;

  Standard_EXPORT bool ClearReportEntity(const int num);

  Standard_EXPORT bool SetReportEntity(const int                                  num,
                                       const occ::handle<Interface_ReportEntity>& rep);

  Standard_EXPORT bool AddReportEntity(const occ::handle<Interface_ReportEntity>& rep,
                                       const bool                                 semantic = false);

  Standard_EXPORT bool IsUnknownEntity(const int num) const;

  Standard_EXPORT void FillSemanticChecks(const Interface_CheckIterator& checks,
                                          const bool                     clear = true);

  Standard_EXPORT bool HasSemanticChecks() const;

  Standard_EXPORT const occ::handle<Interface_Check>& Check(const int  num,
                                                            const bool syntactic) const;

  Standard_EXPORT virtual void Reservate(const int nbent);

  Standard_EXPORT virtual void AddEntity(const occ::handle<Standard_Transient>& anentity);

  Standard_EXPORT void AddWithRefs(const occ::handle<Standard_Transient>& anent,
                                   const occ::handle<Interface_Protocol>& proto,
                                   const int                              level   = 0,
                                   const bool                             listall = false);

  Standard_EXPORT void AddWithRefs(const occ::handle<Standard_Transient>& anent,
                                   const int                              level   = 0,
                                   const bool                             listall = false);

  Standard_EXPORT void AddWithRefs(const occ::handle<Standard_Transient>& anent,
                                   const Interface_GeneralLib&            lib,
                                   const int                              level   = 0,
                                   const bool                             listall = false);

  Standard_EXPORT void ReplaceEntity(const int                              nument,
                                     const occ::handle<Standard_Transient>& anent);

  Standard_EXPORT void ReverseOrders(const int after = 0);

  Standard_EXPORT void ChangeOrder(const int oldnum, const int newnum, const int count = 1);

  Standard_EXPORT void GetFromTransfer(const Interface_EntityIterator& aniter);

  Standard_EXPORT virtual void GetFromAnother(
    const occ::handle<Interface_InterfaceModel>& other) = 0;

  Standard_EXPORT virtual occ::handle<Interface_InterfaceModel> NewEmptyModel() const = 0;

  Standard_EXPORT bool SetCategoryNumber(const int num, const int val);

  Standard_EXPORT int CategoryNumber(const int num) const;

  Standard_EXPORT void FillIterator(Interface_EntityIterator& iter) const;

  Standard_EXPORT Interface_EntityIterator Entities() const;

  Standard_EXPORT Interface_EntityIterator Reports(const bool semantic = false) const;

  Standard_EXPORT Interface_EntityIterator Redefineds() const;

  Standard_EXPORT const occ::handle<Interface_Check>& GlobalCheck(
    const bool syntactic = true) const;

  Standard_EXPORT void SetGlobalCheck(const occ::handle<Interface_Check>& ach);

  Standard_EXPORT virtual void VerifyCheck(occ::handle<Interface_Check>& ach) const;

  Standard_EXPORT virtual void DumpHeader(Standard_OStream& S, const int level = 0) const = 0;

  Standard_EXPORT void Print(const occ::handle<Standard_Transient>& ent,
                             Standard_OStream&                      s,
                             const int                              mode = 0) const;

  Standard_EXPORT virtual void PrintLabel(const occ::handle<Standard_Transient>& ent,
                                          Standard_OStream&                      S) const = 0;

  Standard_EXPORT virtual void PrintToLog(const occ::handle<Standard_Transient>& ent,
                                          Standard_OStream&                      S) const;

  Standard_EXPORT virtual occ::handle<TCollection_HAsciiString> StringLabel(
    const occ::handle<Standard_Transient>& ent) const = 0;

  Standard_EXPORT virtual int NextNumberForLabel(const char* label,
                                                 const int   lastnum = 0,
                                                 const bool  exact   = true) const;

  Standard_EXPORT static bool HasTemplate(const char* name);

  Standard_EXPORT static occ::handle<Interface_InterfaceModel> Template(const char* name);

  Standard_EXPORT static bool SetTemplate(const char*                                  name,
                                          const occ::handle<Interface_InterfaceModel>& model);

  Standard_EXPORT static occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
    ListTemplates();

  DEFINE_STANDARD_RTTIEXT(Interface_InterfaceModel, Standard_Transient)

protected:
  Standard_EXPORT Interface_InterfaceModel();

private:
  NCollection_IndexedMap<occ::handle<Standard_Transient>>   theentities;
  NCollection_DataMap<int, occ::handle<Standard_Transient>> thereports;
  NCollection_DataMap<int, occ::handle<Standard_Transient>> therepch;
  occ::handle<Interface_Check>                              thecheckstx;
  occ::handle<Interface_Check>                              thechecksem;
  bool                                                      haschecksem;
  bool                                                      isdispatch;
  occ::handle<TCollection_HAsciiString>                     thecategory;
  occ::handle<Interface_GTool>                              thegtool;
};
