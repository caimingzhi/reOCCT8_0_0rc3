#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <TCollection_AsciiString.hpp>
class TopOpeBRepDS_Interference;

class TopOpeBRepDS_TKI
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_TKI();

  Standard_EXPORT void Clear();

  Standard_EXPORT void FillOnGeometry(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  Standard_EXPORT void FillOnSupport(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  Standard_EXPORT bool IsBound(const TopOpeBRepDS_Kind K, const int G) const;

  Standard_EXPORT const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& Interferences(
    const TopOpeBRepDS_Kind K,
    const int               G) const;

  Standard_EXPORT NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& ChangeInterferences(
    const TopOpeBRepDS_Kind K,
    const int               G);

  Standard_EXPORT bool HasInterferences(const TopOpeBRepDS_Kind K, const int G) const;

  Standard_EXPORT void Add(const TopOpeBRepDS_Kind K, const int G);

  Standard_EXPORT void Add(const TopOpeBRepDS_Kind                       K,
                           const int                                     G,
                           const occ::handle<TopOpeBRepDS_Interference>& HI);

  Standard_EXPORT void DumpTKIIterator(const TCollection_AsciiString& s1 = "",
                                       const TCollection_AsciiString& s2 = "");

  Standard_EXPORT void Init();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& Value(
    TopOpeBRepDS_Kind& K,
    int&               G) const;

  Standard_EXPORT NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& ChangeValue(
    TopOpeBRepDS_Kind& K,
    int&               G);

private:
  Standard_EXPORT void Reset();

  Standard_EXPORT bool MoreTI() const;

  Standard_EXPORT void NextTI();

  Standard_EXPORT bool MoreITM() const;

  Standard_EXPORT void FindITM();

  Standard_EXPORT void NextITM();

  Standard_EXPORT void Find();

  Standard_EXPORT int KindToTableIndex(const TopOpeBRepDS_Kind K) const;

  Standard_EXPORT TopOpeBRepDS_Kind TableIndexToKind(const int TI) const;

  Standard_EXPORT bool IsValidTI(const int TI) const;

  Standard_EXPORT bool IsValidK(const TopOpeBRepDS_Kind K) const;

  Standard_EXPORT bool IsValidG(const int G) const;

  Standard_EXPORT bool IsValidKG(const TopOpeBRepDS_Kind K, const int G) const;

  int mydelta;
  occ::handle<NCollection_HArray1<
    NCollection_DataMap<int, NCollection_List<occ::handle<TopOpeBRepDS_Interference>>>>>
      myT;
  int myTI;
  int myG;
  NCollection_DataMap<int, NCollection_List<occ::handle<TopOpeBRepDS_Interference>>>::Iterator
                                                           myITM;
  TopOpeBRepDS_Kind                                        myK;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> myEmptyLOI;
  TCollection_AsciiString                                  myDummyAsciiString;
};

