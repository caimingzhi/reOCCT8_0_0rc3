

#include <TDocStd_Document.hpp>

#include <CDM_Document.hpp>
#include <CDM_MetaData.hpp>
#include <Standard_Dump.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDF_AttributeDelta.hpp>
#include <NCollection_List.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_Delta.hpp>
#include <TDF_Label.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Reference.hpp>
#include <TDocStd.hpp>
#include <TDocStd_Application.hpp>
#include <TDocStd_CompoundDelta.hpp>
#include <TDocStd_Context.hpp>
#include <Standard_GUID.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_DataMap.hpp>
#include <TDocStd_Modified.hpp>
#include <TDocStd_Owner.hpp>
#include <TDocStd_XLink.hpp>
#include <TDocStd_XLinkIterator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDocStd_Document, CDM_Document)

#define TDocStd_List_RemoveLast(theList)                                                           \
  NCollection_List<occ::handle<TDF_Delta>>::Iterator it(theList);                                  \
  int                                                i, n = theList.Extent();                      \
  for (i = 1; i < n; i++)                                                                          \
    it.Next();                                                                                     \
  theList.Remove(it);

#undef DEB_TRANS

#undef DEB_DELTA

#define SRN_DELTA_COMPACT

occ::handle<TDocStd_Document> TDocStd_Document::Get(const TDF_Label& acces)
{

  if (acces.Root().HasAttribute())
  {
    return TDocStd_Owner::GetDocument(acces.Data());
  }
  return occ::handle<TDocStd_Document>();
}

TDocStd_Document::TDocStd_Document(const TCollection_ExtendedString& aStorageFormat)
    : myStorageFormat(aStorageFormat),
      myData(new TDF_Data()),
      myUndoLimit(0),
      myUndoTransaction("UNDO"),
      mySaveTime(0),
      myIsNestedTransactionMode(false),
      mySaveEmptyLabels(false),
      myStorageFormatVersion(TDocStd_FormatVersion_CURRENT)
{
  myUndoTransaction.Initialize(myData);
  TDocStd_Owner::SetDocument(myData, this);

#ifdef SRN_DELTA_COMPACT
  myFromUndo.Nullify();
  myFromRedo.Nullify();
#endif
}

bool TDocStd_Document::IsSaved() const
{
  return CDM_Document::IsStored();
}

TCollection_ExtendedString TDocStd_Document::GetName() const
{
  return CDM_Document::MetaData()->Name();
}

TCollection_ExtendedString TDocStd_Document::GetPath() const
{
  return CDM_Document::MetaData()->Path();
}

void TDocStd_Document::SetData(const occ::handle<TDF_Data>& D)
{
  myData = D;
  myUndoTransaction.Initialize(myData);
}

occ::handle<TDF_Data> TDocStd_Document::GetData() const
{
  return myData;
}

TDF_Label TDocStd_Document::Main() const
{
  return myData->Root().FindChild(1, true);
}

bool TDocStd_Document::IsEmpty() const
{
  TDF_AttributeIterator It(Main());
  return !It.More();
}

bool TDocStd_Document::IsValid() const
{
  return TDocStd_Modified::IsEmpty(Main());
}

void TDocStd_Document::SetModified(const TDF_Label& L)
{
  TDocStd_Modified::Add(L);
}

void TDocStd_Document::PurgeModified()
{
  TDocStd_Modified::Clear(Main());
}

const NCollection_Map<TDF_Label>& TDocStd_Document::GetModified() const
{
  return TDocStd_Modified::Get(Main());
}

void TDocStd_Document::Update(const occ::handle<CDM_Document>&,
                              const int   aReferenceIdentifier,
                              void* const aModifContext)
{
  const TDocStd_Context* CC = static_cast<TDocStd_Context*>(aModifContext);
  if (CC->ModifiedReferences() || !IsUpToDate(aReferenceIdentifier))
  {
    TCollection_AsciiString aDocEntry(aReferenceIdentifier);
    UpdateReferences(aDocEntry);
    SetIsUpToDate(aReferenceIdentifier);
  }
}

void TDocStd_Document::NewCommand()
{
#ifdef OCCT_DEBUG_TRANS
  if (myUndoTransaction.IsOpen() && myData->Transaction() > 1)
  {
    throw Standard_DomainError("NewCommand : many open transactions");
  }
#endif

  CommitTransaction();
  OpenTransaction();

#ifdef OCCT_DEBUG_TRANS
  std::cout << "End NewCommand" << std::endl;
#endif
}

bool TDocStd_Document::HasOpenCommand() const
{
  return myUndoTransaction.IsOpen();
}

void TDocStd_Document::OpenCommand()
{
  if (!myIsNestedTransactionMode && myUndoTransaction.IsOpen())
  {
    throw Standard_DomainError("TDocStd_Document::OpenCommand : already open");
  }
  OpenTransaction();
}

bool TDocStd_Document::CommitCommand()
{
  return CommitTransaction();
}

void TDocStd_Document::AbortCommand()
{
  AbortTransaction();
}

bool TDocStd_Document::CommitTransaction()
{
  myData->AllowModification(true);

  bool isDone = false;

  if (myIsNestedTransactionMode && myUndoTransaction.IsOpen())
  {

    occ::handle<TDF_Delta>             D = myUndoTransaction.Commit(true);
    occ::handle<TDocStd_CompoundDelta> aCompDelta =
      occ::down_cast<TDocStd_CompoundDelta>(myUndoFILO.First());
    AppendDeltaToTheFirst(aCompDelta, D);
    D = aCompDelta;
    myUndoFILO.RemoveFirst();
    if (myUndoFILO.Extent())
    {
      aCompDelta = occ::down_cast<TDocStd_CompoundDelta>(myUndoFILO.First());
      AppendDeltaToTheFirst(aCompDelta, D);
      myUndoTransaction.Open();
    }
    else
    {
      if (!D->IsEmpty())
      {
        myUndos.Append(D);
        myRedos.Clear();
        isDone = true;
      }
    }

    if (myOnlyTransactionModification)
    {
      myData->AllowModification(myUndoTransaction.IsOpen() && myUndoLimit);
    }
  }
  else
  {

    if (myUndoLimit != 0 && myUndoTransaction.IsOpen())
    {

      occ::handle<TDF_Delta> D = myUndoTransaction.Commit(true);
      if (!(D.IsNull() || D->IsEmpty()))
      {
        isDone = true;

        myRedos.Clear();
        myUndos.Append(D);

        if (myUndos.Extent() > myUndoLimit)
        {
#ifdef SRN_DELTA_COMPACT
          occ::handle<TDF_Delta> aDelta = myUndos.First();
#endif
          myUndos.RemoveFirst();
#ifdef SRN_DELTA_COMPACT
          if (myFromUndo == aDelta)
          {

            if (myUndos.Extent() == 1)
            {
              myFromUndo.Nullify();
              myFromRedo.Nullify();
            }
            else
              myFromUndo = myUndos.First();
          }
#endif
        }
      }
    }

    if (myOnlyTransactionModification)
    {
      myData->AllowModification(myUndoTransaction.IsOpen() && myUndoLimit);
    }
  }

  if (isDone && IsOpened())
  {
    const occ::handle<TDocStd_Application> anAppli =
      occ::down_cast<TDocStd_Application>(Application());
    if (!anAppli.IsNull())
      anAppli->OnCommitTransaction(this);
  }
  return isDone;
}

void TDocStd_Document::AbortTransaction()
{
  myData->AllowModification(true);

  if (myUndoTransaction.IsOpen())
    if (myUndoLimit != 0)
      myUndoTransaction.Abort();

  if (myIsNestedTransactionMode && myUndoFILO.Extent())
  {
    if (!myUndoFILO.First()->IsEmpty())
      myData->Undo(myUndoFILO.First(), true);
    myUndoFILO.RemoveFirst();
    if (myUndoFILO.Extent())
      myUndoTransaction.Open();
  }

  if (myOnlyTransactionModification)
  {
    myData->AllowModification(myUndoTransaction.IsOpen() && myUndoLimit);
  }

  if (IsOpened())
  {
    const occ::handle<TDocStd_Application> anAppli =
      occ::down_cast<TDocStd_Application>(Application());
    if (!anAppli.IsNull())
      anAppli->OnAbortTransaction(this);
  }
}

void TDocStd_Document::OpenTransaction()
{
  myData->AllowModification(true);

  if (myIsNestedTransactionMode)
  {

    if (myUndoTransaction.IsOpen())
    {
      occ::handle<TDF_Delta>             D = myUndoTransaction.Commit(true);
      occ::handle<TDocStd_CompoundDelta> aCompDelta =
        occ::down_cast<TDocStd_CompoundDelta>(myUndoFILO.First());
      AppendDeltaToTheFirst(aCompDelta, D);
    }
    int aLastTime = myData->Time();
    if (myUndoFILO.Extent())
      aLastTime = myUndoFILO.First()->EndTime();
    occ::handle<TDocStd_CompoundDelta> aCompoundDelta = new TDocStd_CompoundDelta;
    aCompoundDelta->Validity(aLastTime, aLastTime);
    myUndoFILO.Prepend(aCompoundDelta);
  }

  if (myUndoLimit != 0)
    myUndoTransaction.Open();

  if (myOnlyTransactionModification)
  {
    myData->AllowModification(myUndoTransaction.IsOpen() && myUndoLimit);
  }

  if (IsOpened())
  {
    const occ::handle<TDocStd_Application> anAppli =
      occ::down_cast<TDocStd_Application>(Application());
    if (!anAppli.IsNull())
      anAppli->OnOpenTransaction(this);
  }
}

void TDocStd_Document::SetUndoLimit(const int L)
{
#ifdef SRN_DELTA_COMPACT
  myFromUndo.Nullify();
  myFromRedo.Nullify();
#endif

  CommitTransaction();
  myUndoLimit = (L > 0) ? L : 0;
  int n       = myUndos.Extent() - myUndoLimit;
  while (n > 0)
  {
    myUndos.RemoveFirst();
    --n;
  }

  if (myOnlyTransactionModification)
  {
    myData->AllowModification(myUndoTransaction.IsOpen() && myUndoLimit);
  }
}

int TDocStd_Document::GetUndoLimit() const
{
  return myUndoLimit;
}

int TDocStd_Document::GetAvailableUndos() const
{
  return myUndos.Extent();
}

void TDocStd_Document::ClearUndos()
{
  myUndos.Clear();
  myRedos.Clear();
#ifdef SRN_DELTA_COMPACT
  myFromRedo.Nullify();
  myFromUndo.Nullify();
#endif
}

void TDocStd_Document::ClearRedos()
{
  myRedos.Clear();
#ifdef SRN_DELTA_COMPACT
  myFromRedo.Nullify();
#endif
}

bool TDocStd_Document::Undo()
{

  bool isOpened = myUndoTransaction.IsOpen();
  bool undoDone = false;

  if (!myUndos.IsEmpty())
  {

    AbortTransaction();

    while (myIsNestedTransactionMode && myUndoFILO.Extent())
      AbortTransaction();

    myData->AllowModification(true);

#ifdef OCCT_DEBUG_DELTA
    std::cout << "DF before Undo ==================================" << std::endl;
    TDF_Tool::DeepDump(std::cout, myData);
#endif
    occ::handle<TDF_Delta> D = myData->Undo(myUndos.Last(), true);
    D->SetName(myUndos.Last()->Name());
#ifdef OCCT_DEBUG_DELTA
    std::cout << "DF after Undo ==================================" << std::endl;
    TDF_Tool::DeepDump(std::cout, myData);
#endif

    myRedos.Prepend(D);

    TDocStd_List_RemoveLast(myUndos);
    undoDone = true;
  }

  if (isOpened && undoDone)
    OpenTransaction();

  if (myOnlyTransactionModification)
  {
    myData->AllowModification(myUndoTransaction.IsOpen() && myUndoLimit);
  }

  return undoDone;
}

int TDocStd_Document::GetAvailableRedos() const
{

  return myRedos.Extent();
}

bool TDocStd_Document::Redo()
{
  bool isOpened = myUndoTransaction.IsOpen();
  bool undoDone = false;
  if (!myRedos.IsEmpty())
  {

    AbortTransaction();

    while (myIsNestedTransactionMode && myUndoFILO.Extent())
      AbortTransaction();

    myData->AllowModification(true);

#ifdef OCCT_DEBUG_DELTA
    std::cout << "DF before Redo ==================================" << std::endl;
    TDF_Tool::DeepDump(std::cout, myData);
#endif
    occ::handle<TDF_Delta> D = myData->Undo(myRedos.First(), true);
    D->SetName(myRedos.First()->Name());
#ifdef OCCT_DEBUG_DELTA
    std::cout << "DF after Redo ==================================" << std::endl;
    TDF_Tool::DeepDump(std::cout, myData);
#endif

    myUndos.Append(D);

    myRedos.RemoveFirst();
    undoDone = true;
  }

  if (isOpened && undoDone)
    OpenTransaction();

  if (myOnlyTransactionModification)
  {
    myData->AllowModification(myUndoTransaction.IsOpen() && myUndoLimit);
  }

  return undoDone;
}

void TDocStd_Document::UpdateReferences(const TCollection_AsciiString& aDocEntry)
{

  NCollection_List<occ::handle<TDF_Attribute>> aRefList;
  TDocStd_XLink*                               xRefPtr;
  for (TDocStd_XLinkIterator xItr(this); xItr.More(); xItr.Next())
  {
    xRefPtr = xItr.Value();
    if (xRefPtr->DocumentEntry() == aDocEntry)
    {
      aRefList.Append(xRefPtr->Update());
    }
  }
  NCollection_List<occ::handle<TDF_Attribute>>::Iterator It(aRefList);
  for (; It.More(); It.Next())
  {

    SetModified(It.Value()->Label());
  }
}

const NCollection_List<occ::handle<TDF_Delta>>& TDocStd_Document::GetUndos() const
{
  return myUndos;
}

const NCollection_List<occ::handle<TDF_Delta>>& TDocStd_Document::GetRedos() const
{
  return myRedos;
}

bool TDocStd_Document::InitDeltaCompaction()
{
#ifdef SRN_DELTA_COMPACT
  if (myUndoLimit == 0 || myUndos.Extent() == 0)
  {
    myFromRedo.Nullify();
    myFromUndo.Nullify();
    return false;
  }

  myFromRedo.Nullify();

  myFromUndo = myUndos.Last();
  if (myRedos.Extent() > 0)
    myFromRedo = myRedos.First();
#endif
  return true;
}

bool TDocStd_Document::PerformDeltaCompaction()
{
#ifdef SRN_DELTA_COMPACT
  if (myFromUndo.IsNull())
    return false;

  NCollection_List<occ::handle<TDF_Delta>>           aList;
  occ::handle<TDocStd_CompoundDelta>                 aCompoundDelta = new TDocStd_CompoundDelta;
  NCollection_List<occ::handle<TDF_Delta>>::Iterator anIterator(myUndos);
  NCollection_List<occ::handle<TDF_AttributeDelta>>::Iterator    aDeltasIterator;
  NCollection_DataMap<TDF_Label, NCollection_Map<Standard_GUID>> aMap;
  bool                                                           isFound = false, isTimeSet = false;

  for (; anIterator.More(); anIterator.Next())
  {
    if (!isFound)
    {
      if (myFromUndo == anIterator.Value())
        isFound = true;
      aList.Append(anIterator.Value());
      continue;
    }

    if (!isTimeSet)
    {
      aCompoundDelta->Validity(anIterator.Value()->BeginTime(), myUndos.Last()->EndTime());
      isTimeSet = true;
    }

    aDeltasIterator.Initialize(anIterator.Value()->AttributeDeltas());
    for (; aDeltasIterator.More(); aDeltasIterator.Next())
    {
      if (!aMap.IsBound(aDeltasIterator.Value()->Label()))
      {
        NCollection_Map<Standard_GUID>* pIDMap = new NCollection_Map<Standard_GUID>();
        aMap.Bind(aDeltasIterator.Value()->Label(), *pIDMap);
        delete pIDMap;
      }
      if (aMap(aDeltasIterator.Value()->Label()).Add(aDeltasIterator.Value()->ID()))

        aCompoundDelta->AddAttributeDelta(aDeltasIterator.Value());
    }
  }

  myUndos.Clear();
  myUndos.Assign(aList);
  myUndos.Append(aCompoundDelta);

  if (myFromRedo.IsNull())
  {
    myRedos.Clear();
    return true;
  }

  aList.Clear();

  for (anIterator.Initialize(myRedos); anIterator.More(); anIterator.Next())
  {
    aList.Append(anIterator.Value());
    if (anIterator.Value() == myFromRedo)
      break;
  }

  myRedos.Clear();
  myRedos.Assign(aList);
#endif
  return true;
}

TCollection_ExtendedString TDocStd_Document::StorageFormat() const
{
  return myStorageFormat;
}

void TDocStd_Document::ChangeStorageFormat(const TCollection_ExtendedString& newStorageFormat)
{
  if (newStorageFormat != myStorageFormat)
  {
    myStorageFormat      = newStorageFormat;
    myResourcesAreLoaded = false;
    CDM_Document::LoadResources();
  }
}

void TDocStd_Document::Recompute()
{
  if (IsValid())
    return;

  PurgeModified();
}

void TDocStd_Document::AppendDeltaToTheFirst(const occ::handle<TDocStd_CompoundDelta>& theDelta1,
                                             const occ::handle<TDF_Delta>&             theDelta2)
{
  if (theDelta2->IsEmpty())
    return;
  NCollection_DataMap<TDF_Label, NCollection_Map<Standard_GUID>> aMap;

  NCollection_List<occ::handle<TDF_AttributeDelta>>::Iterator aDeltasIterator1(
    theDelta1->AttributeDeltas());
  for (; aDeltasIterator1.More(); aDeltasIterator1.Next())
  {
    TDF_Label aLabel = aDeltasIterator1.Value()->Label();
    if (!aMap.IsBound(aLabel))
    {
      NCollection_Map<Standard_GUID> aTmpIDMap;
      aMap.Bind(aLabel, aTmpIDMap);
    }
    Standard_GUID                   anID    = aDeltasIterator1.Value()->ID();
    NCollection_Map<Standard_GUID>& anIDMap = aMap.ChangeFind(aLabel);
    anIDMap.Add(anID);
  }

  theDelta1->Validity(theDelta1->BeginTime(), theDelta2->EndTime());
  NCollection_List<occ::handle<TDF_AttributeDelta>>::Iterator aDeltasIterator2(
    theDelta2->AttributeDeltas());
  for (; aDeltasIterator2.More(); aDeltasIterator2.Next())
  {
    TDF_Label     aLabel = aDeltasIterator2.Value()->Label();
    Standard_GUID anID   = aDeltasIterator2.Value()->ID();
    if (aMap.IsBound(aLabel))
    {
      const NCollection_Map<Standard_GUID>& anIDMap = aMap.Find(aLabel);
      if (anIDMap.Contains(anID))
        continue;
    }
    theDelta1->AddAttributeDelta(aDeltasIterator2.Value());
  }
}

void TDocStd_Document::RemoveFirstUndo()
{
  if (myUndos.IsEmpty())
    return;
  myUndos.RemoveFirst();
}

void TDocStd_Document::BeforeClose()
{
  SetModificationMode(false);
  AbortTransaction();
  if (myIsNestedTransactionMode)
    myUndoFILO.Clear();
  ClearUndos();
}

TDocStd_FormatVersion TDocStd_Document::StorageFormatVersion() const
{
  return myStorageFormatVersion;
}

void TDocStd_Document::ChangeStorageFormatVersion(const TDocStd_FormatVersion theVersion)
{
  myStorageFormatVersion = theVersion;
}

TDocStd_FormatVersion TDocStd_Document::CurrentStorageFormatVersion()
{
  return TDocStd_FormatVersion_CURRENT;
}

void TDocStd_Document::DumpJson(Standard_OStream& theOStream, int theDepth) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_BASE_CLASS(theOStream, theDepth, CDM_Document)

  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myStorageFormat)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsSaved())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsChanged())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsEmpty())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, IsValid())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, GetAvailableUndos())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, GetAvailableRedos())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, HasOpenCommand())

  for (NCollection_List<occ::handle<TDF_Delta>>::Iterator anUndoIt(myUndos); anUndoIt.More();
       anUndoIt.Next())
  {
    const occ::handle<TDF_Delta>& anUndo = anUndoIt.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, anUndo.get())
  }

  for (NCollection_List<occ::handle<TDF_Delta>>::Iterator aRedoIt(myRedos); aRedoIt.More();
       aRedoIt.Next())
  {
    const occ::handle<TDF_Delta>& aRedo = aRedoIt.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, aRedo.get())
  }

  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myData.get())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myUndoLimit)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myUndoTransaction)
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myFromUndo.get())
  OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myFromRedo.get())
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySaveTime)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsNestedTransactionMode)

  for (NCollection_List<occ::handle<TDF_Delta>>::Iterator anUndoFILOIt(myUndoFILO);
       anUndoFILOIt.More();
       anUndoFILOIt.Next())
  {
    const occ::handle<TDF_Delta>& anUndoFILO = anUndoFILOIt.Value();
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, anUndoFILO.get())
  }

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myOnlyTransactionModification)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, mySaveEmptyLabels)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myStorageFormatVersion)
}
