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

//! Iterate on interferences of a list, matching
//! conditions on interferences.
//! Nota:
//! inheritance of ListIteratorOfListOfInterference from
//! TopOpeBRepDS has not been done because of the
//! impossibility of naming the classical More, Next
//! methods which are declared as static in
//! TCollection_ListIteratorOfList ... . ListIteratorOfList
//! has benn placed as a field of InterferenceIterator.
class TopOpeBRepDS_InterferenceIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_InterferenceIterator();

  //! Creates an iterator on the Interference of list <L>.
  Standard_EXPORT TopOpeBRepDS_InterferenceIterator(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  //! re-initialize interference iteration process on
  //! the list of interference <L>.
  //! Conditions are not modified.
  Standard_EXPORT void Init(const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L);

  //! define a condition on interference iteration process.
  //! Interference must match the Geometry Kind <ST>
  Standard_EXPORT void GeometryKind(const TopOpeBRepDS_Kind GK);

  //! define a condition on interference iteration process.
  //! Interference must match the Geometry <G>
  Standard_EXPORT void Geometry(const int G);

  //! define a condition on interference iteration process.
  //! Interference must match the Support Kind <ST>
  Standard_EXPORT void SupportKind(const TopOpeBRepDS_Kind ST);

  //! define a condition on interference iteration process.
  //! Interference must match the Support <S>
  Standard_EXPORT void Support(const int S);

  //! reach for an interference matching the conditions
  //! (if defined).
  Standard_EXPORT void Match();

  //! Returns True if the Interference <I> matches the
  //! conditions (if defined).
  //! If no conditions defined, returns True.
  Standard_EXPORT virtual bool MatchInterference(
    const occ::handle<TopOpeBRepDS_Interference>& I) const;

  //! Returns True if there is a current Interference in
  //! the iteration.
  Standard_EXPORT bool More() const;

  //! Move to the next Interference.
  Standard_EXPORT void Next();

  //! Returns the current Interference, matching the
  //! conditions (if defined).
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
