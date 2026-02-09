#pragma once

typedef enum
{
  TObj_FreeOnly = 0,
  TObj_KeepDepending,
  TObj_Forced
} TObj_DeletingMode;

#ifdef _MSC_VER
  #pragma once
#endif

#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>

#include <TDF_Label.hpp>
#include <gp_XYZ.hpp>

class TObj_Model;
class TObj_Persistence;
class TObj_ObjectIterator;
class TObj_TNameContainer;
class TCollection_HExtendedString;
class TCollection_HAsciiString;

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_ExtendedString.hpp>
class TObj_Object;

class TObj_Object : public Standard_Transient
{
public:
  enum TypeFlags
  {
    Visible = 0x0001
  };

  enum ObjectState
  {
    ObjectState_Hidden = 0x0001,
    ObjectState_Saved  = 0x0002,

    ObjectState_Imported       = 0x0004,
    ObjectState_ImportedByFile = 0x0008,

    ObjectState_Ordered = 0x0010
  };

protected:
  enum DataTag
  {
    DataTag_First = 0,
    DataTag_Flags,
    DataTag_Order,
    DataTag_Last = DataTag_First + 100
  };

  enum ChildTag
  {
    ChildTag_First = 0,
    ChildTag_Last  = ChildTag_First
  };

  enum RefTag
  {
    RefTag_First = 0,
    RefTag_Last  = RefTag_First
  };

protected:
  Standard_EXPORT TObj_Object(const TDF_Label& theLabel, const bool theSetName = true);

  TObj_Object(const TObj_Persistence*, const TDF_Label& theLabel)
      : myLabel(theLabel)
  {
  }

  void initFields() {}

public:
  virtual Standard_EXPORT occ::handle<TObj_Model> GetModel() const;

  virtual Standard_EXPORT occ::handle<TObj_ObjectIterator> GetChildren(
    const occ::handle<Standard_Type>& theType = nullptr) const;

  Standard_EXPORT TDF_Label GetChildLabel() const;

  Standard_EXPORT TDF_Label getChildLabel(const int theRank) const;

public:
  Standard_EXPORT TDF_Label GetLabel() const;

  Standard_EXPORT TDF_Label GetDataLabel() const;

  Standard_EXPORT TDF_Label GetReferenceLabel() const;

public:
  virtual Standard_EXPORT occ::handle<TObj_TNameContainer> GetDictionary() const;

  virtual Standard_EXPORT occ::handle<TCollection_HExtendedString> GetName() const;

  Standard_EXPORT bool GetName(TCollection_ExtendedString& theName) const;

  Standard_EXPORT bool GetName(TCollection_AsciiString& theName) const;

  virtual Standard_EXPORT bool SetName(
    const occ::handle<TCollection_HExtendedString>& theName) const;

  Standard_EXPORT bool SetName(const occ::handle<TCollection_HAsciiString>& theName) const;

  Standard_EXPORT bool SetName(const char* name) const;

  virtual occ::handle<TCollection_HExtendedString> GetNameForClone(
    const occ::handle<TObj_Object>&) const
  {
    return GetName();
  }

public:
  virtual Standard_EXPORT bool HasReference(const occ::handle<TObj_Object>& theObject) const;

  virtual Standard_EXPORT occ::handle<TObj_ObjectIterator> GetReferences(
    const occ::handle<Standard_Type>& theType = nullptr) const;

  virtual Standard_EXPORT void RemoveAllReferences();

  virtual Standard_EXPORT occ::handle<TObj_ObjectIterator> GetBackReferences(
    const occ::handle<Standard_Type>& theType = nullptr) const;

  virtual Standard_EXPORT void AddBackReference(const occ::handle<TObj_Object>& theObject);

  virtual Standard_EXPORT void RemoveBackReference(const occ::handle<TObj_Object>& theObject,
                                                   const bool theSingleOnly = true);

  virtual Standard_EXPORT bool RemoveBackReferences(
    const TObj_DeletingMode theMode = TObj_FreeOnly);

  virtual Standard_EXPORT void ClearBackReferences();

  Standard_EXPORT bool HasBackReferences() const;

  virtual Standard_EXPORT void ReplaceReference(const occ::handle<TObj_Object>& theOldObject,
                                                const occ::handle<TObj_Object>& theNewObject);

  virtual Standard_EXPORT bool GetBadReference(const TDF_Label& theRoot,
                                               TDF_Label&       theBadReference) const;

  virtual Standard_EXPORT bool RelocateReferences(const TDF_Label& theFromRoot,
                                                  const TDF_Label& theToRoot,
                                                  const bool       theUpdateBackRefs = true);

  virtual Standard_EXPORT bool CanRemoveReference(const occ::handle<TObj_Object>& theObject) const;

  virtual Standard_EXPORT void RemoveReference(const occ::handle<TObj_Object>& theObject);

  virtual void BeforeForgetReference(const TDF_Label&) {}

public:
  virtual Standard_EXPORT bool CanDetach(const TObj_DeletingMode theMode = TObj_FreeOnly);

  virtual Standard_EXPORT bool Detach(const TObj_DeletingMode theMode = TObj_FreeOnly);

  static Standard_EXPORT bool Detach(const TDF_Label&        theLabel,
                                     const TObj_DeletingMode theMode = TObj_FreeOnly);

public:
  static Standard_EXPORT bool GetObj(const TDF_Label&          theLabel,
                                     occ::handle<TObj_Object>& theResult,
                                     const bool                isSuper = false);

  Standard_EXPORT occ::handle<TObj_Object> GetFatherObject(
    const occ::handle<Standard_Type>& theType = nullptr) const;

public:
  virtual Standard_EXPORT bool IsAlive() const;

public:
  virtual Standard_EXPORT occ::handle<TObj_Object> Clone(
    const TDF_Label&                 theTargetLabel,
    occ::handle<TDF_RelocationTable> theRelocTable = nullptr);

  virtual Standard_EXPORT void CopyReferences(
    const occ::handle<TObj_Object>&         theTargetObject,
    const occ::handle<TDF_RelocationTable>& theRelocTable);

  virtual Standard_EXPORT void CopyChildren(TDF_Label&                              theTargetLabel,
                                            const occ::handle<TDF_RelocationTable>& theRelocTable);

public:
  virtual Standard_EXPORT int GetOrder() const;

  virtual Standard_EXPORT bool SetOrder(const int& theIndx);

public:
  Standard_EXPORT bool HasModifications() const;

protected:
  virtual Standard_EXPORT bool copyData(const occ::handle<TObj_Object>& theTargetObject);

  Standard_EXPORT void copyReferences(const TDF_Label&                        theSourceLabel,
                                      TDF_Label&                              theTargetLabel,
                                      const occ::handle<TDF_RelocationTable>& theRelocTable);

public:
  virtual Standard_EXPORT int GetTypeFlags() const;

  Standard_EXPORT int GetFlags() const;

  Standard_EXPORT void SetFlags(const int theMask);

  Standard_EXPORT bool TestFlags(const int theMask) const;

  Standard_EXPORT void ClearFlags(const int theMask = ~0);

public:
  virtual Standard_EXPORT void AfterRetrieval();

  virtual Standard_EXPORT void BeforeStoring();

protected:
  Standard_EXPORT TDF_Label getDataLabel(const int theRank1, const int theRank2 = 0) const;

  Standard_EXPORT TDF_Label getReferenceLabel(const int theRank1, const int theRank2 = 0) const;

  Standard_EXPORT bool isDataAttribute(const Standard_GUID& theGUID,
                                       const int            theRank1,
                                       const int            theRank2 = 0) const;

  Standard_EXPORT double getReal(const int theRank1, const int theRank2 = 0) const;

  Standard_EXPORT bool setReal(const double theValue,
                               const int    theRank1,
                               const int    theRank2     = 0,
                               const double theTolerance = 0.) const;

  Standard_EXPORT int getInteger(const int theRank1, const int theRank2 = 0) const;

  Standard_EXPORT bool setInteger(const int theValue,
                                  const int theRank1,
                                  const int theRank2 = 0) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<double>> getRealArray(
    const int    theLength,
    const int    theRank1,
    const int    theRank2        = 0,
    const double theInitialValue = 0.0) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<int>> getIntegerArray(
    const int theLength,
    const int theRank1,
    const int theRank2        = 0,
    const int theInitialValue = 0) const;

  Standard_EXPORT occ::handle<NCollection_HArray1<TCollection_ExtendedString>> getExtStringArray(
    const int theLength,
    const int theRank1,
    const int theRank2 = 0) const;

  Standard_EXPORT void setArray(const occ::handle<NCollection_HArray1<double>>& theArray,
                                const int                                       theRank1,
                                const int                                       theRank2 = 0);

  Standard_EXPORT void setArray(const occ::handle<NCollection_HArray1<int>>& theArray,
                                const int                                    theRank1,
                                const int                                    theRank2 = 0);

  Standard_EXPORT void setArray(
    const occ::handle<NCollection_HArray1<TCollection_ExtendedString>>& theArray,
    const int                                                           theRank1,
    const int                                                           theRank2 = 0);

  Standard_EXPORT void setExtString(const occ::handle<TCollection_HExtendedString>& theValue,
                                    const int                                       theRank1,
                                    const int theRank2 = 0) const;

  Standard_EXPORT occ::handle<TCollection_HExtendedString> getExtString(
    const int theRank1,
    const int theRank2 = 0) const;

  Standard_EXPORT void setAsciiString(const occ::handle<TCollection_HAsciiString>& theValue,
                                      const int                                    theRank1,
                                      const int theRank2 = 0) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> getAsciiString(
    const int theRank1,
    const int theRank2 = 0) const;

  Standard_EXPORT occ::handle<TObj_Object> getReference(const int theRank1,
                                                        const int theRank2 = 0) const;

  Standard_EXPORT bool setReference(const occ::handle<TObj_Object>& theObject,
                                    const int                       theRank1,
                                    const int                       theRank2 = 0);

  Standard_EXPORT TDF_Label addReference(const int                       theRank1,
                                         const occ::handle<TObj_Object>& theObject);

private:
  TDF_Label myLabel;

  occ::handle<NCollection_HSequence<occ::handle<TObj_Object>>> myHSeqBackRef;

  friend class TObj_TObject;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_Object, Standard_Transient)
};

#ifdef _MSC_VER
  #pragma once
#endif
