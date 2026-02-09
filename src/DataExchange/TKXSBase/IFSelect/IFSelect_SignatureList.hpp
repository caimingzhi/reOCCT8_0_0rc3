#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <IFSelect_PrintCount.hpp>
#include <NCollection_IndexedDataMap.hpp>
class TCollection_HAsciiString;
class Interface_InterfaceModel;

class IFSelect_SignatureList : public Standard_Transient
{

public:
  Standard_EXPORT IFSelect_SignatureList(const bool withlist = false);

  Standard_EXPORT void SetList(const bool withlist);

  Standard_EXPORT bool& ModeSignOnly();

  Standard_EXPORT virtual void Clear();

  Standard_EXPORT void Add(const occ::handle<Standard_Transient>& ent, const char* sign);

  Standard_EXPORT const char* LastValue() const;

  Standard_EXPORT void Init(const char*                                                     name,
                            const NCollection_IndexedDataMap<TCollection_AsciiString, int>& count,
                            const NCollection_IndexedDataMap<TCollection_AsciiString,
                                                             occ::handle<Standard_Transient>>& list,
                            const int nbnuls);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> List(
    const char* root = "") const;

  Standard_EXPORT bool HasEntities() const;

  Standard_EXPORT int NbNulls() const;

  Standard_EXPORT int NbTimes(const char* sign) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> Entities(
    const char* sign) const;

  Standard_EXPORT void SetName(const char* name);

  Standard_EXPORT virtual const char* Name() const;

  Standard_EXPORT virtual void PrintCount(Standard_OStream& S) const;

  Standard_EXPORT virtual void PrintList(Standard_OStream&                            S,
                                         const occ::handle<Interface_InterfaceModel>& model,
                                         const IFSelect_PrintCount mod = IFSelect_ListByItem) const;

  Standard_EXPORT virtual void PrintSum(Standard_OStream& S) const;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignatureList, Standard_Transient)

private:
  bool                                                                                 thesignonly;
  bool                                                                                 thelistat;
  int                                                                                  thenbnuls;
  occ::handle<TCollection_HAsciiString>                                                thename;
  TCollection_AsciiString                                                              thelastval;
  NCollection_IndexedDataMap<TCollection_AsciiString, int>                             thedicount;
  NCollection_IndexedDataMap<TCollection_AsciiString, occ::handle<Standard_Transient>> thediclist;
};
