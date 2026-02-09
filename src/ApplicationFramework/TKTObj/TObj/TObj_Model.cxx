#include <TObj_Model.hpp>

#include <OSD_File.hpp>
#include <TDataStd_Integer.hpp>
#include <TDF_Tool.hpp>
#include <TDocStd_Owner.hpp>

#include <TObj_Assistant.hpp>
#include <TObj_Application.hpp>
#include <TObj_CheckModel.hpp>
#include <TObj_HiddenPartition.hpp>
#include <TObj_LabelIterator.hpp>
#include <TObj_ModelIterator.hpp>
#include <TObj_Object.hpp>
#include <TObj_Partition.hpp>
#include <TObj_TObject.hpp>
#include <TObj_TModel.hpp>
#include <TObj_TNameContainer.hpp>
#include <Message_Msg.hpp>
#include <OSD_OpenFile.hpp>
#include <utility>

IMPLEMENT_STANDARD_RTTIEXT(TObj_Model, Standard_Transient)

#ifdef _MSC_VER
  #include <io.h>
#else
  #include <unistd.h>
#endif

TObj_Model::TObj_Model()
{
  myMessenger = GetApplication()->Messenger();
}

const occ::handle<TObj_Application> TObj_Model::GetApplication()
{
  return TObj_Application::GetInstance();
}

TObj_Model::~TObj_Model()
{
  Close();
}

void TObj_Model::CloseDocument(const occ::handle<TDocStd_Document>& theDoc)
{

  if (theDoc->HasOpenCommand())
    theDoc->AbortCommand();

  const occ::handle<TObj_Application> anApplication = GetApplication();

  theDoc->Main().Root().ForgetAllAttributes(true);
  anApplication->Close(theDoc);
}

bool TObj_Model::Load(const TCollection_ExtendedString& theFile)
{

  bool aStatus = true;

  occ::handle<TDocStd_Document> aDoc;

  const occ::handle<TObj_Application> anApplication = GetApplication();

  const occ::handle<TObj_Model> me = this;
  TObj_Assistant::SetCurrentModel(me);
  TObj_Assistant::ClearTypeMap();

  bool isFileEmpty = checkDocumentEmpty(theFile);
  if (isFileEmpty)
  {

    aStatus = anApplication->CreateNewDocument(aDoc, GetFormat());

    if (aStatus)
    {

      TDF_Label                aLabel = aDoc->Main();
      occ::handle<TObj_TModel> anAtr  = new TObj_TModel;
      aLabel.AddAttribute(anAtr);
      anAtr->Set(me);

      SetLabel(aLabel);
    }
  }
  else
  {

    Messenger()->Send(Message_Msg("TObj_M_LoadDocument") << theFile, Message_Info);
    aStatus = anApplication->LoadDocument(theFile, aDoc);

    if (aStatus)
    {

      TDF_Label aLabel  = GetLabel();
      bool      isValid = !aLabel.IsNull() && !aDoc.IsNull();
      {
        try
        {
          isValid = isValid && aLabel.Data() == aDoc->GetData();
        }
        catch (Standard_Failure const&)
        {
          isValid = false;
        }
      }
      if (!isValid)
      {
        if (!aDoc.IsNull())
          CloseDocument(aDoc);
        myLabel.Nullify();
        Messenger()->Send(Message_Msg("TObj_M_WrongFile") << theFile, Message_Alarm);
        aStatus = false;
      }
    }
    else
    {

      if (!aDoc.IsNull())
        CloseDocument(aDoc);
      myLabel.Nullify();
    }
  }

  if (aStatus)
  {
    bool isInitOk = false;
    {
      try
      {
        isInitOk = initNewModel(isFileEmpty);
      }
      catch (Standard_Failure const& anException)
      {
#ifdef OCCT_DEBUG
        TCollection_ExtendedString aString(anException.ExceptionType());
        aString = aString + ": " + anException.GetMessageString();
        Messenger()->Send(Message_Msg("TObj_Appl_Exception") << aString);
#endif
        (void)anException;
        Messenger()->Send(Message_Msg("TObj_M_WrongFile") << theFile, Message_Alarm);
      }
    }
    if (!isInitOk)
    {
      if (!aDoc.IsNull())
        CloseDocument(aDoc);
      myLabel.Nullify();
      aStatus = false;
    }
  }
  TObj_Assistant::UnSetCurrentModel();
  TObj_Assistant::ClearTypeMap();
  return aStatus;
}

bool TObj_Model::Load(Standard_IStream& theIStream)
{
  occ::handle<TDocStd_Document>       aDoc;
  bool                                aStatus = true, isFileLoaded = false;
  const occ::handle<TObj_Application> anApplication = GetApplication();

  const occ::handle<TObj_Model> me = this;
  TObj_Assistant::SetCurrentModel(me);
  TObj_Assistant::ClearTypeMap();

  Messenger()->Send(Message_Msg("TObj_M_LoadDocument"), Message_Info);
  aStatus = anApplication->LoadDocument(theIStream, aDoc);
  if (aStatus)
  {

    TDF_Label aLabel  = GetLabel();
    bool      isValid = (!aLabel.IsNull() && !aDoc.IsNull());
    try
    {
      isValid = (isValid && aLabel.Data() == aDoc->GetData());
    }
    catch (Standard_Failure const&)
    {
      isValid = false;
    }
    if (!isValid)
    {
      if (!aDoc.IsNull())
        CloseDocument(aDoc);
      myLabel.Nullify();
      Messenger()->Send(Message_Msg("TObj_M_WrongFile"), Message_Alarm);
      aStatus = false;
    }
    isFileLoaded = isValid;
  }
  else
  {

    if (!aDoc.IsNull())
      CloseDocument(aDoc);
    myLabel.Nullify();

    aStatus = anApplication->CreateNewDocument(aDoc, GetFormat());
    if (aStatus)
    {

      TDF_Label                aLabel = aDoc->Main();
      occ::handle<TObj_TModel> anAtr  = new TObj_TModel;
      aLabel.AddAttribute(anAtr);
      anAtr->Set(me);

      SetLabel(aLabel);
    }
  }

  if (aStatus)
  {
    bool isInitOk = false;
    try
    {
      isInitOk = initNewModel(!isFileLoaded);
    }
    catch (Standard_Failure const& anException)
    {
#ifdef OCCT_DEBUG
      TCollection_ExtendedString aString(anException.what());
      Messenger()->Send(Message_Msg("TObj_Appl_Exception") << aString);
#endif
      (void)anException;
      Messenger()->Send(Message_Msg("TObj_M_WrongFile"), Message_Alarm);
    }
    if (!isInitOk)
    {
      if (!aDoc.IsNull())
        CloseDocument(aDoc);
      myLabel.Nullify();
      aStatus = false;
    }
  }

  TObj_Assistant::UnSetCurrentModel();
  TObj_Assistant::ClearTypeMap();
  return aStatus;
}

occ::handle<TCollection_HExtendedString> TObj_Model::GetFile() const
{
  occ::handle<TDocStd_Document> aDoc = GetDocument();
  if (aDoc.IsNull() || !aDoc->IsStored())
  {
    return occ::handle<TCollection_HExtendedString>();
  }

  TCollection_ExtendedString aPath(aDoc->GetPath());
  return !aPath.IsEmpty() ? new TCollection_HExtendedString(aPath)
                          : occ::handle<TCollection_HExtendedString>();
}

bool TObj_Model::Save()
{
  occ::handle<TDocStd_Document> aDoc = TDocStd_Document::Get(GetLabel());
  if (aDoc.IsNull())
    return false;

  if (!aDoc->GetPath().IsEmpty())
    return SaveAs(aDoc->GetPath());
  return true;
}

bool TObj_Model::SaveAs(const TCollection_ExtendedString& theFile)
{
  TObj_Assistant::ClearTypeMap();

  occ::handle<TDocStd_Document> aDoc = TDocStd_Document::Get(GetLabel());
  if (aDoc.IsNull())
    return false;

  FILE* aF = OSD_OpenFile(theFile, "w");
  if (aF == nullptr)
  {
    Messenger()->Send(Message_Msg("TObj_M_NoWriteAccess") << theFile, Message_Alarm);
    return false;
  }
  else
    fclose(aF);

  bool aTrMode = aDoc->ModificationMode();
  aDoc->SetModificationMode(false);

  occ::handle<TObj_ObjectIterator> anIterator;
  for (anIterator = GetObjects(); anIterator->More(); anIterator->Next())
  {
    occ::handle<TObj_Object> anOCAFObj = anIterator->Value();
    if (anOCAFObj.IsNull())
      continue;
    anOCAFObj->BeforeStoring();
  }

  aDoc->SetModificationMode(aTrMode);

  const occ::handle<TObj_Application> anApplication = GetApplication();

  bool aStatus = anApplication->SaveDocument(aDoc, theFile);

  TObj_Assistant::ClearTypeMap();
  return aStatus;
}

bool TObj_Model::SaveAs(Standard_OStream& theOStream)
{
  TObj_Assistant::ClearTypeMap();

  occ::handle<TDocStd_Document> aDoc = TDocStd_Document::Get(GetLabel());
  if (aDoc.IsNull())
    return false;

  bool aTrMode = aDoc->ModificationMode();
  aDoc->SetModificationMode(false);

  occ::handle<TObj_ObjectIterator> anIterator;
  for (anIterator = GetObjects(); anIterator->More(); anIterator->Next())
  {
    occ::handle<TObj_Object> anOCAFObj = anIterator->Value();
    if (anOCAFObj.IsNull())
      continue;
    anOCAFObj->BeforeStoring();
  }

  aDoc->SetModificationMode(aTrMode);

  bool aStatus = GetApplication()->SaveDocument(aDoc, theOStream);
  TObj_Assistant::ClearTypeMap();
  return aStatus;
}

bool TObj_Model::Close()
{

  TDF_Label aLabel = GetLabel();
  if (aLabel.IsNull())
    return false;
  occ::handle<TDocStd_Document> aDoc = TDocStd_Document::Get(aLabel);
  if (aDoc.IsNull())
    return false;

  CloseDocument(aDoc);

  myLabel.Nullify();
  return true;
}

occ::handle<TObj_Model> TObj_Model::GetDocumentModel(const TDF_Label& theLabel)
{
  occ::handle<TObj_Model> aModel;
  if (theLabel.IsNull())
    return aModel;

  occ::handle<TDocStd_Document> aDoc;
  occ::handle<TDF_Data>         aData  = theLabel.Data();
  TDF_Label                     aRootL = aData->Root();
  if (aRootL.IsNull())
    return aModel;
  occ::handle<TDocStd_Owner> aDocOwnerAtt;
  if (aRootL.FindAttribute(TDocStd_Owner::GetID(), aDocOwnerAtt))
    aDoc = aDocOwnerAtt->GetDocument();

  if (aDoc.IsNull())
    return aModel;

  TDF_Label                aLabel = aDoc->Main();
  occ::handle<TObj_TModel> anAttr;
  if (aLabel.FindAttribute(TObj_TModel::GetID(), anAttr))
    aModel = anAttr->Model();

  return aModel;
}

occ::handle<TObj_ObjectIterator> TObj_Model::GetObjects() const
{
  occ::handle<TObj_Model> me = this;
  return new TObj_ModelIterator(me);
}

occ::handle<TObj_ObjectIterator> TObj_Model::GetChildren() const
{
  occ::handle<TObj_Partition> aMainPartition = GetMainPartition();
  if (aMainPartition.IsNull())
    return nullptr;
  return aMainPartition->GetChildren();
}

occ::handle<TObj_Object> TObj_Model::FindObject(
  const occ::handle<TCollection_HExtendedString>& theName,
  const occ::handle<TObj_TNameContainer>&         theDictionary) const
{
  occ::handle<TObj_TNameContainer> aDictionary = theDictionary;
  if (aDictionary.IsNull())
    aDictionary = GetDictionary();
  occ::handle<TObj_Object> aResult;

  if (IsRegisteredName(theName, aDictionary))
  {
    TDF_Label aLabel = aDictionary->Get().Find(theName);
    TObj_Object::GetObj(aLabel, aResult);
  }

  return aResult;
}

occ::handle<TObj_Object> TObj_Model::GetRoot() const
{
  return getPartition(GetLabel());
}

occ::handle<TObj_Partition> TObj_Model::GetMainPartition() const
{
  return getPartition(GetLabel());
}

void TObj_Model::SetNewName(const occ::handle<TObj_Object>& theObject)
{
  occ::handle<TObj_Partition> aPartition = TObj_Partition::GetPartition(theObject);

  if (aPartition.IsNull())
    return;

  occ::handle<TCollection_HExtendedString> name = aPartition->GetNewName();
  if (!name.IsNull())
    theObject->SetName(name);
}

bool TObj_Model::IsRegisteredName(const occ::handle<TCollection_HExtendedString>& theName,
                                  const occ::handle<TObj_TNameContainer>& theDictionary) const
{
  occ::handle<TObj_TNameContainer> aDictionary = theDictionary;
  if (aDictionary.IsNull())
    aDictionary = GetDictionary();

  if (aDictionary.IsNull())
    return false;
  return aDictionary->IsRegistered(theName);
}

void TObj_Model::RegisterName(const occ::handle<TCollection_HExtendedString>& theName,
                              const TDF_Label&                                theLabel,
                              const occ::handle<TObj_TNameContainer>&         theDictionary) const
{
  occ::handle<TObj_TNameContainer> aDictionary = theDictionary;
  if (aDictionary.IsNull())
    aDictionary = GetDictionary();

  if (!aDictionary.IsNull())
    aDictionary->RecordName(theName, theLabel);
}

void TObj_Model::UnRegisterName(const occ::handle<TCollection_HExtendedString>& theName,
                                const occ::handle<TObj_TNameContainer>&         theDictionary) const
{
  occ::handle<TObj_TNameContainer> aDictionary = theDictionary;
  if (aDictionary.IsNull())
    aDictionary = GetDictionary();

  if (!aDictionary.IsNull())
    aDictionary->RemoveName(theName);
}

occ::handle<TObj_TNameContainer> TObj_Model::GetDictionary() const
{
  occ::handle<TObj_TNameContainer> A;
  TDF_Label                        aLabel = GetLabel();
  if (!aLabel.IsNull())
    aLabel.FindAttribute(TObj_TNameContainer::GetID(), A);
  return A;
}

occ::handle<TObj_Partition> TObj_Model::getPartition(const TDF_Label& theLabel,
                                                     const bool       theHidden) const
{
  occ::handle<TObj_Partition> aPartition;
  if (theLabel.IsNull())
    return aPartition;
  occ::handle<TObj_TObject> A;

  if (!theLabel.FindAttribute(TObj_TObject::GetID(), A))
  {
    if (theHidden)
      aPartition = new TObj_HiddenPartition(theLabel);
    else
      aPartition = TObj_Partition::Create(theLabel);
  }
  else
    aPartition = occ::down_cast<TObj_Partition>(A->Get());

  return aPartition;
}

occ::handle<TObj_Partition> TObj_Model::getPartition(const TDF_Label&                  theLabel,
                                                     const int                         theIndex,
                                                     const TCollection_ExtendedString& theName,
                                                     const bool theHidden) const
{
  occ::handle<TObj_Partition> aPartition;
  if (theLabel.IsNull())
    return aPartition;

  TDF_Label aLabel = theLabel.FindChild(theIndex, false);
  bool      isNew  = false;

  if (aLabel.IsNull())
  {
    aLabel = theLabel.FindChild(theIndex, true);
    isNew  = true;
  }

  aPartition = getPartition(aLabel, theHidden);

  if (isNew)
    aPartition->SetName(new TCollection_HExtendedString(theName));
  return aPartition;
}

occ::handle<TObj_Partition> TObj_Model::getPartition(const int                         theIndex,
                                                     const TCollection_ExtendedString& theName,
                                                     const bool theHidden) const
{
  return getPartition(GetMainPartition()->GetChildLabel(), theIndex, theName, theHidden);
}

bool TObj_Model::initNewModel(const bool IsNew)
{

  TObj_TNameContainer::Set(GetLabel());

  if (!IsNew)
  {

    occ::handle<TObj_ObjectIterator> anIterator;
    for (anIterator = GetObjects(); anIterator->More(); anIterator->Next())
    {
      occ::handle<TObj_Object> anOCAFObj = anIterator->Value();
      if (anOCAFObj.IsNull())
        continue;
      anOCAFObj->AfterRetrieval();
    }

    updateBackReferences(GetMainPartition());

    if (isToCheck())
    {

      occ::handle<TObj_CheckModel> aCheck = GetChecker();
      aCheck->Perform();
      aCheck->SendMessages();

      SetModified(true);
    }
  }
  return true;
}

void TObj_Model::updateBackReferences(const occ::handle<TObj_Object>& theObject)
{

  if (theObject.IsNull())
    return;
  occ::handle<TObj_ObjectIterator> aChildren = theObject->GetChildren();
  for (; aChildren->More(); aChildren->Next())
  {
    occ::handle<TObj_Object> aChild = aChildren->Value();
    updateBackReferences(aChild);
  }

  occ::handle<TObj_LabelIterator> anIter =
    occ::down_cast<TObj_LabelIterator>(theObject->GetReferences());

  if (anIter.IsNull())
    return;

  for (; anIter->More(); anIter->Next())
  {
    occ::handle<TObj_Object> anObject = anIter->Value();
    if (!anObject.IsNull())
      anObject->RemoveBackReference(theObject, false);
  }

  anIter = occ::down_cast<TObj_LabelIterator>(theObject->GetReferences());
  if (!anIter.IsNull())
    for (; anIter->More(); anIter->Next())
    {
      occ::handle<TObj_Object> anObject = anIter->Value();
      if (!anObject.IsNull())
        anObject->AddBackReference(theObject);
    }
}

occ::handle<TDocStd_Document> TObj_Model::GetDocument() const
{
  occ::handle<TDocStd_Document> D;
  TDF_Label                     aLabel = GetLabel();
  if (!aLabel.IsNull())
    D = TDocStd_Document::Get(aLabel);
  return D;
}

bool TObj_Model::HasOpenCommand() const
{
  return GetDocument()->HasOpenCommand();
}

void TObj_Model::OpenCommand() const
{
  GetDocument()->OpenCommand();
}

void TObj_Model::CommitCommand() const
{
  GetDocument()->CommitCommand();
}

void TObj_Model::AbortCommand() const
{
  GetDocument()->AbortCommand();
}

bool TObj_Model::IsModified() const
{
  occ::handle<TDocStd_Document> aDoc = GetDocument();
  return aDoc.IsNull() ? false : aDoc->IsChanged();
}

void TObj_Model::SetModified(const bool theModified)
{
  occ::handle<TDocStd_Document> aDoc = GetDocument();
  if (!aDoc.IsNull())
  {
    int aSavedTime = aDoc->GetData()->Time();
    if (theModified)
      --aSavedTime;
    aDoc->SetSavedTime(aSavedTime);
  }
}

bool TObj_Model::checkDocumentEmpty(const TCollection_ExtendedString& theFile)
{
  if (theFile.IsEmpty())
    return true;

  OSD_Path aPath(theFile);
  OSD_File osdfile(aPath);
  if (!osdfile.Exists())
    return true;

  FILE* f = OSD_OpenFile(theFile, "r");
  if (f)
  {
    bool isZeroLengh = false;
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0)
      isZeroLengh = true;

    fclose(f);
    return isZeroLengh;
  }
  return false;
}

Standard_GUID TObj_Model::GetGUID() const
{
  Standard_GUID aGUID("3bbefb49-e618-11d4-ba38-0060b0ee18ea");
  return aGUID;
}

TCollection_ExtendedString TObj_Model::GetFormat() const
{
  return TCollection_ExtendedString("TObjBin");
}

int TObj_Model::GetFormatVersion() const
{
  TDF_Label aLabel = GetDataLabel().FindChild(DataTag_FormatVersion, false);
  if (aLabel.IsNull())
    return -1;

  occ::handle<TDataStd_Integer> aNum;
  if (!aLabel.FindAttribute(TDataStd_Integer::GetID(), aNum))
    return -1;
  else
    return aNum->Get();
}

void TObj_Model::SetFormatVersion(const int theVersion)
{
  TDF_Label aLabel = GetDataLabel().FindChild(DataTag_FormatVersion, true);
  TDataStd_Integer::Set(aLabel, theVersion);
}

TDF_Label TObj_Model::GetDataLabel() const
{
  return GetMainPartition()->GetDataLabel();
}

bool TObj_Model::Paste(occ::handle<TObj_Model>          theModel,
                       occ::handle<TDF_RelocationTable> theRelocTable)
{
  if (theModel.IsNull())
    return false;

  TObj_TNameContainer::Set(theModel->GetLabel());
  GetMainPartition()->Clone(theModel->GetLabel(), std::move(theRelocTable));
  return true;
}

void TObj_Model::CopyReferences(const occ::handle<TObj_Model>&          theTarget,
                                const occ::handle<TDF_RelocationTable>& theRelocTable)
{
  occ::handle<TObj_Object> aMyRoot     = GetMainPartition();
  occ::handle<TObj_Object> aTargetRoot = theTarget->GetMainPartition();
  aMyRoot->CopyReferences(aTargetRoot, theRelocTable);
}

occ::handle<TCollection_HExtendedString> TObj_Model::GetModelName() const
{
  occ::handle<TCollection_HExtendedString> aName = new TCollection_HExtendedString("TObj");
  return aName;
}

bool TObj_Model::Update()
{
  return true;
}

occ::handle<TObj_CheckModel> TObj_Model::GetChecker() const
{
  return new TObj_CheckModel(this);
}
