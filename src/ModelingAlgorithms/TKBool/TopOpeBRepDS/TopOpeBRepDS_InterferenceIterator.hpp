#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_Interference.hpp>

#include <NCollection_List.hpp>
#include <Standard_Boolean.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
class TopOpeBRepDS_Interference;

class TopOpeBRepDS_InterferenceIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_InterferenceIterator();

  Standard_EXPORT TopOpeBRepDS_InterferenceIterator(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  Standard_EXPORT void Init(const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  Standard_EXPORT void GeometryKind(const TopOpeBRepDS_Kind GK);

  Standard_EXPORT void Geometry(const int G);

  Standard_EXPORT void SupportKind(const TopOpeBRepDS_Kind ST);

  Standard_EXPORT void Support(const int S);

  Standard_EXPORT void Match();

  Standard_EXPORT virtual bool MatchInterference(
    const occ::handle<TopOpeBRepDS_Interference>& I) const;

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const occ::handle<TopOpeBRepDS_Interference>& Value() const;

  Standard_EXPORT NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator&
                  ChangeIterator();

private:
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator myIterator;
  bool                                                               myGKDef;
  TopOpeBRepDS_Kind                                                  myGK;
  bool                                                               myGDef;
  int                                                                myG;
  bool                                                               mySKDef;
  TopOpeBRepDS_Kind                                                  mySK;
  bool                                                               mySDef;
  int                                                                myS;
};
