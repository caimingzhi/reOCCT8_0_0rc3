#pragma once

#include <Standard.hpp>

#include <TCollection_ExtendedString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_GUID.hpp>

class TDF_Label;
class TCollection_ExtendedString;
class TDF_RelocationTable;
class TDF_DeltaOnModification;

//! ExtStringArray Attribute. Handles an array of UNICODE strings (represented by the
//! TCollection_ExtendedString class).
class TDataStd_ExtStringArray : public TDF_Attribute
{
  friend class TDataStd_DeltaOnModificationOfExtStringArray;
  DEFINE_STANDARD_RTTIEXT(TDataStd_ExtStringArray, TDF_Attribute)
public:
  //! class methods
  //! =============
  //! Returns the GUID for the attribute.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Finds, or creates, an ExtStringArray attribute with <lower>
  //! and <upper> bounds on the specified label.
  //! If <isDelta> == False, DefaultDeltaOnModification is used.
  //! If <isDelta> == True, DeltaOnModification of the current attribute is used.
  //! If attribute is already set, all input parameters are refused and the found
  //! attribute is returned.
  Standard_EXPORT static occ::handle<TDataStd_ExtStringArray> Set(const TDF_Label& label,
                                                                  const int        lower,
                                                                  const int        upper,
                                                                  const bool       isDelta = false);

  //! Finds, or creates, an ExtStringArray attribute with explicit user defined <guid>.
  //! The ExtStringArray attribute is returned.
  Standard_EXPORT static occ::handle<TDataStd_ExtStringArray> Set(const TDF_Label&     label,
                                                                  const Standard_GUID& theGuid,
                                                                  const int            lower,
                                                                  const int            upper,
                                                                  const bool isDelta = false);

  //! Initializes the inner array with bounds from <lower> to <upper>
  Standard_EXPORT void Init(const int lower, const int upper);

  //! Sets the <Index>th element of the array to <Value>
  //! OutOfRange exception is raised if <Index> doesn't respect Lower and Upper bounds of the
  //! internal array.
  Standard_EXPORT void SetValue(const int Index, const TCollection_ExtendedString& Value);

  //! Sets the explicit GUID (user defined) for the attribute.
  Standard_EXPORT void SetID(const Standard_GUID& theGuid) override;

  //! Sets default GUID for the attribute.
  Standard_EXPORT void SetID() override;

  //! Returns the value of the <Index>th element of the array
  Standard_EXPORT const TCollection_ExtendedString& Value(const int Index) const;

  const TCollection_ExtendedString& operator()(const int Index) const { return Value(Index); }

  //! Return the lower bound.
  Standard_EXPORT int Lower() const;

  //! Return the upper bound
  Standard_EXPORT int Upper() const;

  //! Return the number of elements of <me>.
  Standard_EXPORT int Length() const;

  //! Sets the inner array <myValue> of the ExtStringArray attribute to <newArray>.
  //! If value of <newArray> differs from <myValue>, Backup performed and myValue
  //! refers to new instance of HArray1OfExtendedString that holds <newArray> values
  //! If <isCheckItems> equal True each item of <newArray> will be checked with each
  //! item of <myValue> for coincidence (to avoid backup).
  Standard_EXPORT void ChangeArray(
    const occ::handle<NCollection_HArray1<TCollection_ExtendedString>>& newArray,
    const bool                                                          isCheckItems = true);

  //! Return the inner array of the ExtStringArray attribute
  const occ::handle<NCollection_HArray1<TCollection_ExtendedString>>& Array() const
  {
    return myValue;
  }

  bool GetDelta() const { return myIsDelta; }

  //! for internal use only!
  void SetDelta(const bool isDelta) { myIsDelta = isDelta; }

  Standard_EXPORT TDataStd_ExtStringArray();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Makes a DeltaOnModification between <me> and
  //! <anOldAttribute>.
  Standard_EXPORT occ::handle<TDF_DeltaOnModification> DeltaOnModification(
    const occ::handle<TDF_Attribute>& anOldAttribute) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  void RemoveArray() { myValue.Nullify(); }

private:
  occ::handle<NCollection_HArray1<TCollection_ExtendedString>> myValue;
  bool                                                         myIsDelta;
  Standard_GUID                                                myID;
};
