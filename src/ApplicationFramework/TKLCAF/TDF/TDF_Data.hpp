#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDF_LabelNodePtr.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TDF_HAllocator.hpp>
#include <Standard_Transient.hpp>
#include <TDF_Label.hpp>
#include <Standard_OStream.hpp>
#include <NCollection_DataMap.hpp>
class TDF_Delta;
class TDF_Label;

class TDF_Data : public Standard_Transient
{

public:
  Standard_EXPORT TDF_Data();

  const TDF_Label Root() const;

  int Transaction() const;

  int Time() const;

  Standard_EXPORT bool IsApplicable(const occ::handle<TDF_Delta>& aDelta) const;

  Standard_EXPORT occ::handle<TDF_Delta> Undo(const occ::handle<TDF_Delta>& aDelta,
                                              const bool                    withDelta = false);

  Standard_EXPORT void Destroy();

  ~TDF_Data() override { Destroy(); }

  bool NotUndoMode() const;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const;

  Standard_OStream& operator<<(Standard_OStream& anOS) const { return Dump(anOS); }

  void AllowModification(const bool isAllowed);

  bool IsModificationAllowed() const;

  Standard_EXPORT void SetAccessByEntries(const bool aSet);

  bool IsAccessByEntries() const { return myAccessByEntries; }

  bool GetLabel(const TCollection_AsciiString& anEntry, TDF_Label& aLabel)
  {
    return myAccessByEntriesTable.Find(anEntry, aLabel);
  }

  Standard_EXPORT void RegisterLabel(const TDF_Label& aLabel);

  const TDF_HAllocator& LabelNodeAllocator() const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class TDF_Transaction;
  friend class TDF_LabelNode;

  DEFINE_STANDARD_RTTIEXT(TDF_Data, Standard_Transient)

private:
  void FixOrder(const occ::handle<TDF_Delta>& theDelta);

  Standard_EXPORT int OpenTransaction();

  Standard_EXPORT occ::handle<TDF_Delta> CommitTransaction(const bool withDelta = false);

  Standard_EXPORT occ::handle<TDF_Delta> CommitUntilTransaction(const int  untilTransaction,
                                                                const bool withDelta = false);

  Standard_EXPORT void AbortTransaction();

  Standard_EXPORT void AbortUntilTransaction(const int untilTransaction);

  Standard_EXPORT int CommitTransaction(const TDF_Label&              aLabel,
                                        const occ::handle<TDF_Delta>& aDelta,
                                        const bool                    withDelta);

  TDF_LabelNodePtr                                        myRoot;
  int                                                     myTransaction;
  int                                                     myNbTouchedAtt;
  bool                                                    myNotUndoMode;
  int                                                     myTime;
  NCollection_List<int>                                   myTimes;
  TDF_HAllocator                                          myLabelNodeAllocator;
  bool                                                    myAllowModification;
  bool                                                    myAccessByEntries;
  NCollection_DataMap<TCollection_AsciiString, TDF_Label> myAccessByEntriesTable;
};

inline int TDF_Data::Transaction() const
{
  return myTransaction;
}

inline const TDF_Label TDF_Data::Root() const
{
  return TDF_Label(myRoot);
}

inline int TDF_Data::Time() const
{
  return myTime;
}

inline bool TDF_Data::NotUndoMode() const
{
  return myNotUndoMode;
}

inline Standard_OStream& operator<<(Standard_OStream& anOS, const occ::handle<TDF_Data>& aDF)
{
  return aDF->Dump(anOS);
}

inline void TDF_Data::AllowModification(const bool theAllowModification)
{
  myAllowModification = theAllowModification;
}

inline bool TDF_Data::IsModificationAllowed() const
{
  return myAllowModification;
}

inline const occ::handle<NCollection_BaseAllocator>& TDF_Data::LabelNodeAllocator() const
{
  return myLabelNodeAllocator;
}
