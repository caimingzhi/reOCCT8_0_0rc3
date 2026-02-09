#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_LabelNodePtr.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <Standard_OStream.hpp>
#include <NCollection_IndexedMap.hpp>
class TDF_Label;
class TDF_DeltaOnForget;
class Standard_GUID;
class TDF_AttributeDelta;
class TDF_DeltaOnAddition;
class TDF_DeltaOnResume;
class TDF_DeltaOnModification;
class TDF_DeltaOnRemoval;
class TDF_RelocationTable;
class TDF_DataSet;
class TDF_IDFilter;

class TDF_Attribute : public Standard_Transient
{

public:
  Standard_EXPORT virtual const Standard_GUID& ID() const = 0;

  virtual void SetID(const Standard_GUID&) {}

  virtual void SetID() {}

  Standard_EXPORT const TDF_Label Label() const;

  int Transaction() const;

  Standard_EXPORT int UntilTransaction() const;

  bool IsValid() const;

  bool IsNew() const;

  bool IsForgotten() const;

  Standard_EXPORT bool IsAttribute(const Standard_GUID& anID) const;

  Standard_EXPORT bool FindAttribute(const Standard_GUID&        anID,
                                     occ::handle<TDF_Attribute>& anAttribute) const;

  template <class T>
  bool FindAttribute(const Standard_GUID& theID, occ::handle<T>& theAttr) const
  {
    occ::handle<TDF_Attribute> anAttr = theAttr;
    return FindAttribute(theID, anAttr) && !(theAttr = occ::down_cast<T>(anAttr)).IsNull();
  }

  Standard_EXPORT void AddAttribute(const occ::handle<TDF_Attribute>& other) const;

  Standard_EXPORT bool ForgetAttribute(const Standard_GUID& aguid) const;

  Standard_EXPORT void ForgetAllAttributes(const bool clearChildren = true) const;

  Standard_EXPORT virtual void AfterAddition();

  Standard_EXPORT virtual void BeforeRemoval();

  Standard_EXPORT virtual void BeforeForget();

  Standard_EXPORT virtual void AfterResume();

  Standard_EXPORT virtual bool AfterRetrieval(const bool forceIt = false);

  Standard_EXPORT virtual bool BeforeUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                          const bool                             forceIt = false);

  Standard_EXPORT virtual bool AfterUndo(const occ::handle<TDF_AttributeDelta>& anAttDelta,
                                         const bool                             forceIt = false);

  Standard_EXPORT virtual void BeforeCommitTransaction();

  Standard_EXPORT void Backup();

  bool IsBackuped() const;

  Standard_EXPORT virtual occ::handle<TDF_Attribute> BackupCopy() const;

  Standard_EXPORT virtual void Restore(const occ::handle<TDF_Attribute>& anAttribute) = 0;

  Standard_EXPORT virtual occ::handle<TDF_DeltaOnAddition> DeltaOnAddition() const;

  Standard_EXPORT virtual occ::handle<TDF_DeltaOnForget> DeltaOnForget() const;

  Standard_EXPORT virtual occ::handle<TDF_DeltaOnResume> DeltaOnResume() const;

  Standard_EXPORT virtual occ::handle<TDF_DeltaOnModification> DeltaOnModification(
    const occ::handle<TDF_Attribute>& anOldAttribute) const;

  Standard_EXPORT virtual void DeltaOnModification(
    const occ::handle<TDF_DeltaOnModification>& aDelta);

  Standard_EXPORT virtual occ::handle<TDF_DeltaOnRemoval> DeltaOnRemoval() const;

  Standard_EXPORT virtual occ::handle<TDF_Attribute> NewEmpty() const = 0;

  Standard_EXPORT virtual void Paste(
    const occ::handle<TDF_Attribute>&       intoAttribute,
    const occ::handle<TDF_RelocationTable>& aRelocationTable) const = 0;

  Standard_EXPORT virtual void References(const occ::handle<TDF_DataSet>& aDataSet) const;

  Standard_EXPORT virtual Standard_OStream& Dump(Standard_OStream& anOS) const;

  Standard_OStream& operator<<(Standard_OStream& anOS) const { return Dump(anOS); }

  Standard_EXPORT virtual void ExtendedDump(
    Standard_OStream&                                   anOS,
    const TDF_IDFilter&                                 aFilter,
    NCollection_IndexedMap<occ::handle<TDF_Attribute>>& aMap) const;

  Standard_EXPORT void Forget(const int aTransaction);

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class TDF_Data;
  friend class TDF_Label;
  friend class TDF_LabelNode;
  friend class TDF_AttributeIterator;
  friend class TDF_DeltaOnForget;

  DEFINE_STANDARD_RTTIEXT(TDF_Attribute, Standard_Transient)

protected:
  Standard_EXPORT TDF_Attribute();

private:
  void Validate(const bool aStatus);

  Standard_EXPORT void Resume();

  void Backup(const bool aStatus);

  Standard_EXPORT void RemoveBackup();

  TDF_LabelNodePtr           myLabelNode;
  int                        myTransaction;
  int                        mySavedTransaction;
  int                        myFlags;
  occ::handle<TDF_Attribute> myNext;
  occ::handle<TDF_Attribute> myBackup;
};

enum
{
  TDF_AttributeValidMsk     = 1,
  TDF_AttributeBackupMsk    = 2,
  TDF_AttributeForgottenMsk = 4
};

inline int TDF_Attribute::Transaction() const
{
  return myTransaction;
}

inline void TDF_Attribute::Validate(const bool aStatus)
{
  myFlags = (aStatus) ? (myFlags | TDF_AttributeValidMsk) : (myFlags & ~TDF_AttributeValidMsk);
}

inline bool TDF_Attribute::IsValid() const
{
  return (myFlags & TDF_AttributeValidMsk) != 0;
}

inline void TDF_Attribute::Backup(const bool aStatus)
{
  myFlags = (aStatus) ? (myFlags | TDF_AttributeBackupMsk) : (myFlags & ~TDF_AttributeBackupMsk);
  Validate(!aStatus);
}

inline bool TDF_Attribute::IsBackuped() const
{
  return (myFlags & TDF_AttributeBackupMsk) != 0;
}

inline bool TDF_Attribute::IsNew() const
{
  return IsValid() && myBackup.IsNull();
}

inline bool TDF_Attribute::IsForgotten() const
{
  return (myFlags & TDF_AttributeForgottenMsk) != 0;
}

inline Standard_OStream& operator<<(Standard_OStream& anOS, const occ::handle<TDF_Attribute>& anAtt)
{
  return anAtt->Dump(anOS);
}
