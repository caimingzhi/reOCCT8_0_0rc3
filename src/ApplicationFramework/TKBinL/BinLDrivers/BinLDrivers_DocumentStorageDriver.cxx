#include <BinLDrivers.hpp>
#include <BinLDrivers_DocumentStorageDriver.hpp>
#include <BinLDrivers_Marker.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_Position.hpp>
#include <CDM_Application.hpp>
#include <Message_Messenger.hpp>
#include <FSD_BinaryFile.hpp>
#include <FSD_FileHeader.hpp>
#include <OSD_FileSystem.hpp>
#include <PCDM_ReadWriter.hpp>
#include <Standard_Type.hpp>
#include <Storage_Schema.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <TDocStd_Document.hpp>
#include <Message_ProgressScope.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinLDrivers_DocumentStorageDriver, PCDM_StorageDriver)

#define SHAPESECTION_POS (const char*)"SHAPE_SECTION_POS:"
#define ENDSECTION_POS (const char*)":"

//=================================================================================================

BinLDrivers_DocumentStorageDriver::BinLDrivers_DocumentStorageDriver() = default;

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::Write(const occ::handle<CDM_Document>&  theDocument,
                                              const TCollection_ExtendedString& theFileName,
                                              const Message_ProgressRange&      theRange)
{
  SetIsError(false);
  SetStoreStatus(PCDM_SS_OK);

  myFileName = theFileName;

  const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
  std::shared_ptr<std::ostream>      aFileStream =
    aFileSystem->OpenOStream(theFileName, std::ios::out | std::ios::binary);

  if (aFileStream.get() != nullptr && aFileStream->good())
  {
    Write(theDocument, *aFileStream, theRange);
  }
  else
  {
    SetIsError(true);
    SetStoreStatus(PCDM_SS_WriteFailure);
  }
}

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::Write(const occ::handle<CDM_Document>& theDoc,
                                              Standard_OStream&                theOStream,
                                              const Message_ProgressRange&     theRange)
{
  myMsgDriver = theDoc->Application()->MessageDriver();
  myMapUnsupported.Clear();
  mySizesToWrite.Clear();

  occ::handle<TDocStd_Document> aDoc = occ::down_cast<TDocStd_Document>(theDoc);
  if (aDoc.IsNull())
  {
    SetIsError(true);
    SetStoreStatus(PCDM_SS_Doc_IsNull);
  }
  else
  {
    // First pass: collect empty labels, assign IDs to the types
    if (myDrivers.IsNull())
      myDrivers = AttributeDrivers(myMsgDriver);
    occ::handle<TDF_Data> aData = aDoc->GetData();
    FirstPass(aData->Root());
    if (aDoc->EmptyLabelsSavingMode())
      myEmptyLabels.Clear(); //

    //  1. Write info section (including types table)
    WriteInfoSection(aDoc, theOStream);

    myTypesMap.Clear();
    if (IsError())
    {
      SetStoreStatus(PCDM_SS_Info_Section_Error);
      return;
    }

    //  2. Write the Table of Contents of Sections
    const TDocStd_FormatVersion aDocVer = aDoc->StorageFormatVersion();
    NCollection_Vector<BinLDrivers_DocumentSection>::Iterator anIterS(mySections);
    for (; anIterS.More(); anIterS.Next())
      anIterS.ChangeValue().WriteTOC(theOStream, aDocVer);

    EnableQuickPartWriting(myMsgDriver, IsQuickPart(aDocVer));
    BinLDrivers_DocumentSection* aShapesSection = nullptr;
    bool                         aQuickPart     = IsQuickPart(aDocVer);
    if (!aQuickPart)
    {
      // Shapes Section is the last one, it indicates the end of the table.
      aShapesSection = new BinLDrivers_DocumentSection(SHAPESECTION_POS, false);
      aShapesSection->WriteTOC(theOStream, aDocVer);
    }
    else
    {
      // End Section is the last one, it indicates the end of the table.
      BinLDrivers_DocumentSection anEndSection(ENDSECTION_POS, false);
      anEndSection.WriteTOC(theOStream, aDocVer);
    }

    //  3. Write document contents
    // (Storage data to the stream)
    myRelocTable.Clear();
    myPAtt.Init();
    if (aQuickPart)
      myPAtt.SetOStream(theOStream); // for writing shapes data into the stream directly

    Message_ProgressScope aPS(theRange, "Writing document", 3);

    //  Write Doc structure
    WriteSubTree(aData->Root(), theOStream, aQuickPart, aPS.Next()); // Doc is written
    if (!aPS.More())
    {
      SetIsError(true);
      SetStoreStatus(PCDM_SS_UserBreak);
      return;
    }

    //  4. Write Shapes section
    if (!aQuickPart)
    {
      WriteShapeSection(*aShapesSection, theOStream, aDocVer, aPS.Next());
      delete aShapesSection;
    }
    else
      Clear();

    if (!aPS.More())
    {
      SetIsError(true);
      SetStoreStatus(PCDM_SS_UserBreak);
      return;
    }

    // Write application-defined sections
    for (anIterS.Init(mySections); anIterS.More(); anIterS.Next())
    {
      BinLDrivers_DocumentSection& aSection       = anIterS.ChangeValue();
      const size_t                 aSectionOffset = (size_t)theOStream.tellp();
      WriteSection(aSection.Name(), aDoc, theOStream);
      aSection.Write(theOStream, aSectionOffset, aDocVer);
    }

    //  5. Write sizes along the file where it is needed for quick part mode
    if (aQuickPart)
      WriteSizes(theOStream);

    // End of processing: close structures and check the status
    myPAtt.Destroy(); // free buffer
    myEmptyLabels.Clear();
    myMapUnsupported.Clear();

    if (!myRelocTable.Extent())
    {
      // No objects written
#ifdef OCCT_DEBUG
      myMsgDriver->Send("BinLDrivers_DocumentStorageDriver, no objects written", Message_Info);
#endif
      SetIsError(true);
      SetStoreStatus(PCDM_SS_No_Obj);
    }
    myRelocTable.Clear();
    if (!aPS.More())
    {
      SetIsError(true);
      SetStoreStatus(PCDM_SS_UserBreak);
      return;
    }
    aPS.Next();
    if (!theOStream)
    {
      // A problem with the stream
#ifdef OCCT_DEBUG
      TCollection_ExtendedString anErrorStr(
        "BinLDrivers_DocumentStorageDriver, Problem with the file stream, rdstate = ");
      myMsgDriver->Send(anErrorStr + (int)theOStream.rdstate(), Message_Info);
#endif
      SetIsError(true);
      SetStoreStatus(PCDM_SS_WriteFailure);
    }
  }
}

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::UnsupportedAttrMsg(
  const occ::handle<Standard_Type>& theType)
{
#ifdef OCCT_DEBUG
  TCollection_ExtendedString aMsg(
    "BinLDrivers_DocumentStorageDriver: warning: attribute driver for type ");
#endif
  if (!myMapUnsupported.Contains(theType))
  {
    myMapUnsupported.Add(theType);
#ifdef OCCT_DEBUG
    myMsgDriver->Send(aMsg + theType->Name() + " not found", Message_Info);
#endif
  }
}

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::WriteSubTree(const TDF_Label&             theLabel,
                                                     Standard_OStream&            theOS,
                                                     const bool&                  theQuickPart,
                                                     const Message_ProgressRange& theRange)
{
  // Skip empty labels
  if (!myEmptyLabels.IsEmpty() && myEmptyLabels.First() == theLabel)
  {
    myEmptyLabels.RemoveFirst();
    return;
  }
  Message_ProgressScope aPS(theRange, "Writing sub tree", 2, true);
  // Write label header: tag
  int aTag = theLabel.Tag();
#ifdef DO_INVERSE
  aTag = InverseInt(aTag);
#endif
  theOS.write((char*)&aTag, sizeof(int));

  occ::handle<BinObjMgt_Position> aPosition;
  if (theQuickPart)
  {
    aPosition = mySizesToWrite.Append(new BinObjMgt_Position(theOS));
    aPosition->WriteSize(theOS, true);
  }

  // Write attributes
  TDF_AttributeIterator itAtt(theLabel);
  for (; itAtt.More() && theOS && aPS.More(); itAtt.Next())
  {
    const occ::handle<TDF_Attribute>  tAtt  = itAtt.Value();
    const occ::handle<Standard_Type>& aType = tAtt->DynamicType();
    // Get type ID and driver
    occ::handle<BinMDF_ADriver> aDriver;
    const int                   aTypeId = myDrivers->GetDriver(aType, aDriver);
    if (aTypeId > 0)
    {
      // Add source to relocation table
      const int anId = myRelocTable.Add(tAtt);

      // Create and fill data item
      myPAtt.SetTypeId(aTypeId);
      myPAtt.SetId(anId);
      aDriver->Paste(tAtt, myPAtt, myRelocTable);
      if (!myPAtt.StreamStart().IsNull())
      {
        occ::handle<BinObjMgt_Position> anAttrPosition = myPAtt.StreamStart();
        anAttrPosition->StoreSize(theOS);
        mySizesToWrite.Append(anAttrPosition);
      }

      // Write data to the stream -->!!!
      theOS << myPAtt;
    }
#ifdef OCCT_DEBUG
    else
      UnsupportedAttrMsg(aType);
#endif
  }
  if (!theOS)
  {
    // Problem with the stream
    return;
  }
  if (!aPS.More())
  {
    SetIsError(true);
    SetStoreStatus(PCDM_SS_UserBreak);
    return;
  }
  // Write the end attributes list marker
  BinLDrivers_Marker anEndAttr = BinLDrivers_ENDATTRLIST;
#ifdef DO_INVERSE
  anEndAttr = (BinLDrivers_Marker)InverseInt(anEndAttr);
#endif
  theOS.write((char*)&anEndAttr, sizeof(anEndAttr));

  // Process sub-labels
  TDF_ChildIterator itChld(theLabel);
  for (; itChld.More(); itChld.Next())
  {
    const TDF_Label& aChildLab = itChld.Value();
    if (!aPS.More())
    {
      SetIsError(true);
      SetStoreStatus(PCDM_SS_UserBreak);
      return;
    }
    WriteSubTree(aChildLab, theOS, theQuickPart, aPS.Next());
  }
  // Write the end label marker
  BinLDrivers_Marker anEndLabel = BinLDrivers_ENDLABEL;
#ifdef DO_INVERSE
  anEndLabel = (BinLDrivers_Marker)InverseInt(anEndLabel);
#endif
  theOS.write((char*)&anEndLabel, sizeof(anEndLabel));
  if (theQuickPart)
    aPosition->StoreSize(theOS);
}

//=================================================================================================

occ::handle<BinMDF_ADriverTable> BinLDrivers_DocumentStorageDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  return BinLDrivers::AttributeDrivers(theMessageDriver);
}

//=================================================================================================

bool BinLDrivers_DocumentStorageDriver::FirstPassSubTree(const TDF_Label&             L,
                                                         NCollection_List<TDF_Label>& ListOfEmptyL)
{
  // are there writable attributes on L ?
  bool                  hasAttr = false;
  TDF_AttributeIterator itAtt(L);
  for (; itAtt.More(); itAtt.Next())
  {
    const occ::handle<Standard_Type>& aType = itAtt.Value()->DynamicType();
    occ::handle<BinMDF_ADriver>       aDriver;
    // do not rely on a value returned by GetDriver here, because
    // the IDs have not yet been assigned to the types
    myDrivers->GetDriver(aType, aDriver);
    if (!aDriver.IsNull())
    {
      hasAttr = true;
      myTypesMap.Add(aType);
    }
#ifdef OCCT_DEBUG
    else
      UnsupportedAttrMsg(aType);
#endif
  }

  // are there writable attributes on sub-labels ?
  bool                        hasChildAttr = false;
  NCollection_List<TDF_Label> emptyChildrenList;
  TDF_ChildIterator           itChld(L);
  for (; itChld.More(); itChld.Next())
  {
    if (FirstPassSubTree(itChld.Value(), emptyChildrenList))
      emptyChildrenList.Append(itChld.Value());
    else
      hasChildAttr = true;
  }

  bool isEmpty = !(hasAttr || hasChildAttr);

  if (!isEmpty)
    ListOfEmptyL.Append(emptyChildrenList);

  return isEmpty;
}

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::FirstPass(const TDF_Label& theRoot)
{
  myTypesMap.Clear();
  myEmptyLabels.Clear();

  if (FirstPassSubTree(theRoot, myEmptyLabels))
    myEmptyLabels.Append(theRoot);

  myDrivers->AssignIds(myTypesMap);
}

//=======================================================================
// function : WriteInfoSection
// purpose  : Write info section using FSD_BinaryFile driver
//=======================================================================

#define START_TYPES "START_TYPES"
#define END_TYPES "END_TYPES"

void BinLDrivers_DocumentStorageDriver::WriteInfoSection(const occ::handle<CDM_Document>& theDoc,
                                                         Standard_OStream& theOStream)
{
  // Magic number
  theOStream.write(FSD_BinaryFile::MagicNumber(), strlen(FSD_BinaryFile::MagicNumber()));

  FSD_FileHeader aHeader;

  {
    aHeader.testindian = -1;
    aHeader.binfo      = -1;
    aHeader.einfo      = -1;
    aHeader.bcomment   = -1;
    aHeader.ecomment   = -1;
    aHeader.btype      = -1;
    aHeader.etype      = -1;
    aHeader.broot      = -1;
    aHeader.eroot      = -1;
    aHeader.bref       = -1;
    aHeader.eref       = -1;
    aHeader.bdata      = -1;
    aHeader.edata      = -1;
  }

  // aHeader.testindian
  {
    union
    {
      char ti2[4];
      int  aResult;
    } aWrapUnion;

    aWrapUnion.ti2[0] = 1;
    aWrapUnion.ti2[1] = 2;
    aWrapUnion.ti2[2] = 3;
    aWrapUnion.ti2[3] = 4;

    aHeader.testindian = aWrapUnion.aResult;
  }

  // info section
  aHeader.binfo = (int)theOStream.tellp();

  // header section
  aHeader.einfo = aHeader.binfo + FSD_BinaryFile::WriteHeader(theOStream, aHeader, true);

  // add format
  occ::handle<Storage_Data> theData = new Storage_Data;
  PCDM_ReadWriter::WriteFileFormat(theData, theDoc);
  PCDM_ReadWriter::Writer()->WriteReferenceCounter(theData, theDoc);
  PCDM_ReadWriter::Writer()->WriteReferences(theData, theDoc, myFileName);
  PCDM_ReadWriter::Writer()->WriteExtensions(theData, theDoc);
  PCDM_ReadWriter::Writer()->WriteVersion(theData, theDoc);

  // add the types table
  theData->AddToUserInfo(START_TYPES);
  for (int i = 1; i <= myTypesMap.Extent(); i++)
  {
    occ::handle<BinMDF_ADriver> aDriver = myDrivers->GetDriver(i);
    if (!aDriver.IsNull())
    {
      const TCollection_AsciiString& aTypeName = aDriver->TypeName();
      theData->AddToUserInfo(aTypeName);
    }
  }
  theData->AddToUserInfo(END_TYPES);

  int aObjNb    = 1;
  int aShemaVer = 1;

  // Store the name and version of the application that has created the
  // document.
  theData->SetApplicationVersion(theDoc->Application()->Version());
  theData->SetApplicationName(theDoc->Application()->Name());

  occ::handle<TDocStd_Document> aDoc    = occ::down_cast<TDocStd_Document>(theDoc);
  const int                     aDocVer = aDoc->StorageFormatVersion();
  aHeader.einfo += FSD_BinaryFile::WriteInfo(theOStream,
                                             aObjNb,
                                             aDocVer,
                                             Storage_Schema::ICreationDate(),
                                             "", // schema name
                                             aShemaVer,
                                             theData->ApplicationName(),
                                             theData->ApplicationVersion(),
                                             theData->DataType(),
                                             theData->UserInfo(),
                                             // clang-format off
                                              true); // only count the size of the section
  // clang-format on

  // calculate comment section
  NCollection_Sequence<TCollection_ExtendedString> aComments;
  theDoc->Comments(aComments);
  for (int i = 1; i <= aComments.Length(); i++)
  {
    theData->AddToComments(aComments(i));
  }

  aHeader.bcomment = aHeader.einfo;
  aHeader.ecomment =
    aHeader.bcomment + FSD_BinaryFile::WriteComment(theOStream, theData->Comments(), true);

  aHeader.edata = aHeader.ecomment;

  // write header information
  FSD_BinaryFile::WriteHeader(theOStream, aHeader);

  // write info section
  FSD_BinaryFile::WriteInfo(theOStream,
                            aObjNb,
                            aDocVer,
                            Storage_Schema::ICreationDate(),
                            "", // schema name
                            aShemaVer,
                            theData->ApplicationName(),
                            theData->ApplicationVersion(),
                            theData->DataType(),
                            theData->UserInfo());

  // write the comments
  FSD_BinaryFile::WriteComment(theOStream, theData->Comments());
}

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::AddSection(const TCollection_AsciiString& theName,
                                                   const bool                     isPostRead)
{
  mySections.Append(BinLDrivers_DocumentSection(theName, isPostRead));
}

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::WriteSection(
  const TCollection_AsciiString& /*theName*/,
  const occ::handle<CDM_Document>& /*theDocument*/,
  Standard_OStream& /*theOS*/)
{
  // empty; should be redefined in subclasses
}

//=======================================================================
// function : WriteShapeSection
// purpose  : defines WriteShapeSection
//=======================================================================
void BinLDrivers_DocumentStorageDriver::WriteShapeSection(BinLDrivers_DocumentSection& theSection,
                                                          Standard_OStream&            theOS,
                                                          const TDocStd_FormatVersion  theDocVer,
                                                          const Message_ProgressRange& /*theRange*/)
{
  const size_t aShapesSectionOffset = (size_t)theOS.tellp();
  theSection.Write(theOS, aShapesSectionOffset, theDocVer);
}

//=======================================================================
// function : IsQuickPart
// purpose  : Return true if document should be stored in quick mode for partial reading
//=======================================================================
bool BinLDrivers_DocumentStorageDriver::IsQuickPart(const int theVersion) const
{
  return theVersion >= TDocStd_FormatVersion_VERSION_12;
}

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::Clear()
{
  // empty; should be redefined in subclasses
}

//=================================================================================================

void BinLDrivers_DocumentStorageDriver::WriteSizes(Standard_OStream& theOS)
{
  NCollection_List<occ::handle<BinObjMgt_Position>>::Iterator anIter(mySizesToWrite);
  for (; anIter.More() && theOS; anIter.Next())
    anIter.Value()->WriteSize(theOS);
  mySizesToWrite.Clear();
}
