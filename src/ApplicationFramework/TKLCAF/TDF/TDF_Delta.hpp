#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TDF_AttributeDelta.hpp>
#include <NCollection_List.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Standard_Transient.hpp>
#include <TDF_Label.hpp>
#include <Standard_OStream.hpp>
class TDF_AttributeDelta;

//! A set of AttributeDelta for a given transaction
//! number and reference time number.
//! A delta set is available at <aSourceTime>. If
//! applied, it restores the TDF_Data in the state it
//! was at <aTargetTime>.
class TDF_Delta : public Standard_Transient
{

public:
  //! Creates a delta.
  Standard_EXPORT TDF_Delta();

  //! Returns true if there is nothing to undo.
  bool IsEmpty() const;

  //! Returns true if the Undo action of <me> is
  //! applicable at <aCurrentTime>.
  bool IsApplicable(const int aCurrentTime) const;

  //! Returns the field <myBeginTime>.
  int BeginTime() const;

  //! Returns the field <myEndTime>.
  int EndTime() const;

  //! Adds in <aLabelList> the labels of the attribute deltas.
  //! Caution: <aLabelList> is not cleared before use.
  Standard_EXPORT void Labels(NCollection_List<TDF_Label>& aLabelList) const;

  //! Returns the field <myAttDeltaList>.
  const NCollection_List<occ::handle<TDF_AttributeDelta>>& AttributeDeltas() const;

  //! Returns a name associated with this delta.
  TCollection_ExtendedString Name() const;

  //! Associates a name <theName> with this delta
  void SetName(const TCollection_ExtendedString& theName);

  Standard_EXPORT void Dump(Standard_OStream& OS) const;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class TDF_Data;

  DEFINE_STANDARD_RTTIEXT(TDF_Delta, Standard_Transient)

protected:
  //! Validates <me> at <aBeginTime>. If applied, it
  //! restores the TDF_Data in the state it was at
  //! <anEndTime>. Reserved to TDF_Data.
  Standard_EXPORT void Validity(const int aBeginTime, const int anEndTime);

  //! Adds an AttributeDelta to the list. Reserved to
  //! TDF_Data.
  Standard_EXPORT void AddAttributeDelta(const occ::handle<TDF_AttributeDelta>& anAttributeDelta);

private:
  //! Replaces Attribute Delta List
  void ReplaceDeltaList(const NCollection_List<occ::handle<TDF_AttributeDelta>>& theList);

  void BeforeOrAfterApply(const bool before) const;

  void Apply();

  int                                               myBeginTime;
  int                                               myEndTime;
  NCollection_List<occ::handle<TDF_AttributeDelta>> myAttDeltaList;
  TCollection_ExtendedString                        myName;
};

inline bool TDF_Delta::IsEmpty() const
{
  return myAttDeltaList.IsEmpty();
}

inline bool TDF_Delta::IsApplicable(const int aCurrentTime) const
{
  return (myEndTime == aCurrentTime);
}

inline int TDF_Delta::BeginTime() const
{
  return myBeginTime;
}

inline int TDF_Delta::EndTime() const
{
  return myEndTime;
}

inline const NCollection_List<occ::handle<TDF_AttributeDelta>>& TDF_Delta::AttributeDeltas() const
{
  return myAttDeltaList;
}

inline void TDF_Delta::SetName(const TCollection_ExtendedString& theName)
{
  myName = theName;
}

inline TCollection_ExtendedString TDF_Delta::Name() const
{
  return myName;
}

inline void TDF_Delta::ReplaceDeltaList(
  const NCollection_List<occ::handle<TDF_AttributeDelta>>& theList)
{
  myAttDeltaList = theList;
}
