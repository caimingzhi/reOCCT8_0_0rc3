#include <BinLDrivers.hpp>
#include <BinLDrivers_DocumentRetrievalDriver.hpp>
#include <BinLDrivers_DocumentSection.hpp>
#include <BinLDrivers_Marker.hpp>
#include <BinMDataStd.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <CDM_Application.hpp>
#include <Message_Messenger.hpp>
#include <FSD_BinaryFile.hpp>
#include <FSD_FileHeader.hpp>
#include <OSD_FileSystem.hpp>
#include <PCDM_ReadWriter.hpp>
#include <Standard_Macro.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Standard_Type.hpp>
#include <Storage_HeaderData.hpp>
#include <Storage_Schema.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDataStd_TreeNode.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDocStd_Document.hpp>
#include <TDocStd_FormatVersion.hpp>
#include <TDocStd_Owner.hpp>
#include <Message_ProgressScope.hpp>
#include <PCDM_ReaderFilter.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinLDrivers_DocumentRetrievalDriver, PCDM_RetrievalDriver)

#define SHAPESECTION_POS "SHAPE_SECTION_POS:"
#define ENDSECTION_POS ":"
#define SIZEOFSHAPELABEL 18

#define DATATYPE_MIGRATION

BinLDrivers_DocumentRetrievalDriver::BinLDrivers_DocumentRetrievalDriver()
{
  myReaderStatus = PCDM_RS_OK;
}

void BinLDrivers_DocumentRetrievalDriver::Read(const TCollection_ExtendedString&     theFileName,
                                               const occ::handle<CDM_Document>&      theNewDocument,
                                               const occ::handle<CDM_Application>&   theApplication,
                                               const occ::handle<PCDM_ReaderFilter>& theFilter,
                                               const Message_ProgressRange&          theRange)
{
  const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
  std::shared_ptr<std::istream>      aFileStream =
    aFileSystem->OpenIStream(theFileName, std::ios::in | std::ios::binary);

  if (aFileStream.get() != nullptr && aFileStream->good())
  {
    occ::handle<Storage_Data>  dData;
    TCollection_ExtendedString aFormat = PCDM_ReadWriter::FileFormat(*aFileStream, dData);

    Read(*aFileStream, dData, theNewDocument, theApplication, theFilter, theRange);
    if (!theRange.More())
    {
      myReaderStatus = PCDM_RS_UserBreak;
      return;
    }
  }
  else
  {
    myReaderStatus = PCDM_RS_OpenError;
  }
}

#define MODIFICATION_COUNTER "MODIFICATION_COUNTER: "
#define REFERENCE_COUNTER "REFERENCE_COUNTER: "

#define START_TYPES "START_TYPES"
#define END_TYPES "END_TYPES"

void BinLDrivers_DocumentRetrievalDriver::Read(Standard_IStream&                     theIStream,
                                               const occ::handle<Storage_Data>&      theStorageData,
                                               const occ::handle<CDM_Document>&      theDoc,
                                               const occ::handle<CDM_Application>&   theApplication,
                                               const occ::handle<PCDM_ReaderFilter>& theFilter,
                                               const Message_ProgressRange&          theRange)
{
  myReaderStatus = PCDM_RS_DriverFailure;
  myMsgDriver    = theApplication->MessageDriver();

  const TCollection_ExtendedString aMethStr("BinLDrivers_DocumentRetrievalDriver: ");

  occ::handle<TDocStd_Document> aDoc = occ::down_cast<TDocStd_Document>(theDoc);
  if (aDoc.IsNull())
  {
#ifdef OCCT_DEBUG
    myMsgDriver->Send(aMethStr + "error: null document", Message_Fail);
#endif
    myReaderStatus = PCDM_RS_NoDocument;
    return;
  }

  occ::handle<Storage_HeaderData> aHeaderData;

  if (!theStorageData.IsNull())
  {
    aHeaderData = theStorageData->HeaderData();
  }

  if (!aHeaderData.IsNull())
  {
    for (int i = 1; i <= aHeaderData->UserInfo().Length(); i++)
    {
      const TCollection_AsciiString& aLine = aHeaderData->UserInfo().Value(i);

      if (aLine.Search(REFERENCE_COUNTER) != -1)
      {
        theDoc->SetReferenceCounter(aLine.Token(" ", 2).IntegerValue());
      }
      else if (aLine.Search(MODIFICATION_COUNTER) != -1)
      {
        theDoc->SetModifications(aLine.Token(" ", 2).IntegerValue());
      }
    }
  }

  if (!aHeaderData->StorageVersion().IsIntegerValue())
  {

    myMsgDriver->Send(aMethStr + "error: file has no format version", Message_Fail);
    myReaderStatus = PCDM_RS_FormatFailure;
    return;
  }
  TDocStd_FormatVersion aFileVer =
    static_cast<TDocStd_FormatVersion>(aHeaderData->StorageVersion().IntegerValue());
  TDocStd_FormatVersion aCurrVer = TDocStd_Document::CurrentStorageFormatVersion();

  if (!CheckDocumentVersion(aFileVer, aCurrVer))
  {
    myReaderStatus = PCDM_RS_NoVersion;

    myMsgDriver->Send(aMethStr + "error: wrong file version: " + aHeaderData->StorageVersion()
                        + " while current is " + TDocStd_Document::CurrentStorageFormatVersion(),
                      Message_Fail);
    return;
  }

  NCollection_Sequence<TCollection_AsciiString>        aTypeNames;
  const NCollection_Sequence<TCollection_AsciiString>& aUserInfo = aHeaderData->UserInfo();
  bool                                                 begin     = false;
  int                                                  i;
  for (i = 1; i <= aUserInfo.Length(); i++)
  {
    TCollection_AsciiString aStr = aUserInfo(i);
    if (aStr == START_TYPES)
      begin = true;
    else if (aStr == END_TYPES)
      break;
    else if (begin)
    {
      if (aFileVer < TDocStd_FormatVersion_VERSION_8)
      {
#ifdef DATATYPE_MIGRATION
        TCollection_AsciiString newName;
        if (Storage_Schema::CheckTypeMigration(aStr, newName))
        {
  #ifdef OCCT_DEBUG
          std::cout << "CheckTypeMigration:OldType = " << aStr << " Len = " << aStr.Length()
                    << std::endl;
          std::cout << "CheckTypeMigration:NewType = " << newName << " Len = " << newName.Length()
                    << std::endl;
  #endif
          aStr = newName;
        }
#endif
      }
      aTypeNames.Append(aStr);
    }
  }
  if (myDrivers.IsNull())
    myDrivers = AttributeDrivers(myMsgDriver);
  myDrivers->AssignIds(aTypeNames);

  myMapUnsupported.Clear();
  for (i = 1; i <= aTypeNames.Length(); i++)
    if (myDrivers->GetDriver(i).IsNull())
      myMapUnsupported.Add(i);
  if (!myMapUnsupported.IsEmpty())
  {
    myMsgDriver->Send(aMethStr
                        + "warning: "
                          "the following attributes have no driver:",
                      Message_Warning);
    for (i = 1; i <= aTypeNames.Length(); i++)
      if (myMapUnsupported.Contains(i))
        myMsgDriver->Send(aTypeNames(i), Message_Warning);
  }

  myRelocTable.Clear();
  myRelocTable.SetHeaderData(aHeaderData);
  mySections.Clear();
  myPAtt.Init();
  occ::handle<TDF_Data> aData =
    (!theFilter.IsNull() && theFilter->IsAppendMode()) ? aDoc->GetData() : new TDF_Data();

  Message_ProgressScope aPS(theRange, "Reading data", 3);
  bool                  aQuickPart = IsQuickPart(aFileVer);

  if (aFileVer >= TDocStd_FormatVersion_VERSION_3)
  {
    BinLDrivers_DocumentSection aSection;
    do
    {
      if (!BinLDrivers_DocumentSection::ReadTOC(aSection, theIStream, aFileVer))
        break;
      mySections.Append(aSection);
    } while (!aSection.Name().IsEqual(aQuickPart ? ENDSECTION_POS : SHAPESECTION_POS)
             && !theIStream.eof());

    if (mySections.IsEmpty() || theIStream.eof())
    {

      myMsgDriver->Send(aMethStr + "error: shape section is not found", Message_Fail);
      myReaderStatus = PCDM_RS_ReaderException;
      return;
    }

    NCollection_Vector<BinLDrivers_DocumentSection>::Iterator anIterS(mySections);

    if (!mySections.IsEmpty()
        && (mySections.Size() > 1 || !anIterS.Value().Name().IsEqual(ENDSECTION_POS)))
    {
      std::streampos aDocumentPos = theIStream.tellg();
      for (; anIterS.More(); anIterS.Next())
      {
        BinLDrivers_DocumentSection& aCurSection = anIterS.ChangeValue();
        if (!aCurSection.IsPostRead())
        {
          theIStream.seekg((std::streampos)aCurSection.Offset());
          if (aCurSection.Name().IsEqual(SHAPESECTION_POS))
          {
            ReadShapeSection(aCurSection, theIStream, false, aPS.Next());
            if (!aPS.More())
            {
              myReaderStatus = PCDM_RS_UserBreak;
              return;
            }
          }
          else if (!aCurSection.Name().IsEqual(ENDSECTION_POS))
            ReadSection(aCurSection, theDoc, theIStream);
        }
      }
      theIStream.seekg(aDocumentPos);
    }
  }
  else
  {
    std::streampos aDocumentPos = theIStream.tellg();

    char aShapeSecLabel[SIZEOFSHAPELABEL + 1];
    aShapeSecLabel[SIZEOFSHAPELABEL] = 0x00;
    theIStream.read((char*)&aShapeSecLabel, SIZEOFSHAPELABEL);
    TCollection_AsciiString aShapeLabel(aShapeSecLabel);

    if (aShapeLabel.Length() > 0)
    {

      if (aShapeLabel.Length() <= 0 || aShapeLabel != SHAPESECTION_POS)
      {
        myMsgDriver->Send(aMethStr + "error: Format failure", Message_Fail);
        myReaderStatus = PCDM_RS_FormatFailure;
        return;
      }

      int aShapeSectionPos;
      theIStream.read((char*)&aShapeSectionPos, sizeof(int));

#ifdef DO_INVERSE
      aShapeSectionPos = InverseInt(aShapeSectionPos);
#endif
#ifdef OCCT_DEBUG
      std::cout << "aShapeSectionPos = " << aShapeSectionPos << std::endl;
#endif
      if (aShapeSectionPos)
      {
        aDocumentPos = theIStream.tellg();
        theIStream.seekg((std::streampos)aShapeSectionPos);

        CheckShapeSection(aShapeSectionPos, theIStream);

        BinLDrivers_DocumentSection aCurSection;
        ReadShapeSection(aCurSection, theIStream, false, aPS.Next());
        if (!aPS.More())
        {
          myReaderStatus = PCDM_RS_UserBreak;
          return;
        }
      }
    }
    theIStream.seekg(aDocumentPos);
  }

  int aTag;
  theIStream.read((char*)&aTag, sizeof(int));

  if (aQuickPart)
    myPAtt.SetIStream(theIStream);
  EnableQuickPartReading(myMsgDriver, aQuickPart);

  if (!theFilter.IsNull())
    theFilter->StartIteration();
  const auto aStreamStartPosition = theIStream.tellg();
  int nbRead = ReadSubTree(theIStream, aData->Root(), theFilter, aQuickPart, false, aPS.Next());
  if (!myUnresolvedLinks.IsEmpty())
  {

    theFilter->StartIteration();
    theIStream.seekg(aStreamStartPosition, std::ios_base::beg);
    nbRead += ReadSubTree(theIStream, aData->Root(), theFilter, aQuickPart, true, aPS.Next());
  }
  if (!aPS.More())
  {
    myReaderStatus = PCDM_RS_UserBreak;
    return;
  }

  Clear();
  if (!aPS.More())
  {
    myReaderStatus = PCDM_RS_UserBreak;
    return;
  }
  aPS.Next();

  if (nbRead > 0)
  {

    if (theFilter.IsNull() || !theFilter->IsAppendMode())
    {
      aDoc->SetData(aData);
      TDocStd_Owner::SetDocument(aData, aDoc);
      aDoc->SetComments(aHeaderData->Comments());
    }
    myReaderStatus = PCDM_RS_OK;
  }

  if (aFileVer >= TDocStd_FormatVersion_VERSION_3)
  {
    NCollection_Vector<BinLDrivers_DocumentSection>::Iterator aSectIter(mySections);
    for (; aSectIter.More(); aSectIter.Next())
    {
      BinLDrivers_DocumentSection& aCurSection = aSectIter.ChangeValue();
      if (aCurSection.IsPostRead())
      {
        theIStream.seekg((std::streampos)aCurSection.Offset());
        ReadSection(aCurSection, theDoc, theIStream);
      }
    }
  }
}

int BinLDrivers_DocumentRetrievalDriver::ReadSubTree(
  Standard_IStream&                     theIS,
  const TDF_Label&                      theLabel,
  const occ::handle<PCDM_ReaderFilter>& theFilter,
  const bool&                           theQuickPart,
  const bool                            theReadMissing,
  const Message_ProgressRange&          theRange)
{
  int                        nbRead = 0;
  TCollection_ExtendedString aMethStr("BinLDrivers_DocumentRetrievalDriver: ");

  Message_ProgressScope aPS(theRange, "Reading sub tree", 2, true);

  bool aSkipAttrs = false;
  if (!theFilter.IsNull() && theFilter->IsPartTree())
    aSkipAttrs = !theFilter->IsPassed();

  if (theQuickPart)
  {
    uint64_t aLabelSize = 0;
    theIS.read((char*)&aLabelSize, sizeof(uint64_t));
#if DO_INVERSE
    aLabelSize = InverseUint64(aLabelSize);
#endif

    if (aSkipAttrs && !theFilter->IsSubPassed() && myUnresolvedLinks.IsEmpty())
    {
      aLabelSize -= sizeof(uint64_t);
      theIS.seekg(aLabelSize, std::ios_base::cur);
      if (!theFilter.IsNull())
        theFilter->Up();
      return 0;
    }
  }

  if (theReadMissing)
  {
    aSkipAttrs = true;
  }
  const auto anAttStartPosition = theIS.tellg();

  for (theIS >> myPAtt; theIS && myPAtt.TypeId() > 0 && myPAtt.Id() > 0 && !theIS.eof();
       theIS >> myPAtt)
  {
    if (!aPS.More())
    {
      myReaderStatus = PCDM_RS_UserBreak;
      return -1;
    }
    if (myUnresolvedLinks.Remove(myPAtt.Id()) && aSkipAttrs)
    {
      aSkipAttrs = false;
      theIS.seekg(anAttStartPosition, std::ios_base::beg);
      continue;
    }
    if (aSkipAttrs)
    {
      if (myPAtt.IsDirect())
      {
        uint64_t aStreamSize = 0;
        theIS.read((char*)&aStreamSize, sizeof(uint64_t));
        aStreamSize -= sizeof(uint64_t);
        theIS.seekg(aStreamSize, std::ios_base::cur);
      }
      continue;
    }

    occ::handle<BinMDF_ADriver> aDriver = myDrivers->GetDriver(myPAtt.TypeId());
    if (!aDriver.IsNull())
    {

      int                        anID = myPAtt.Id();
      occ::handle<TDF_Attribute> tAtt;
      bool                       isBound = myRelocTable.IsBound(anID);
      if (isBound)
        tAtt = occ::down_cast<TDF_Attribute>(myRelocTable.Find(anID));
      else
        tAtt = aDriver->NewEmpty();

      if (!theFilter.IsNull() && !theFilter->IsPassed(tAtt->DynamicType()))
      {
        if (myPAtt.IsDirect())
        {
          uint64_t aStreamSize = 0;
          theIS.read((char*)&aStreamSize, sizeof(uint64_t));
          aStreamSize -= sizeof(uint64_t);
          theIS.seekg(aStreamSize, std::ios_base::cur);
        }
        continue;
      }
      nbRead++;

      if (tAtt->Label().IsNull())
      {
        if (!theFilter.IsNull() && theFilter->Mode() != PCDM_ReaderFilter::AppendMode_Forbid
            && theLabel.IsAttribute(tAtt->ID()))
        {
          if (theFilter->Mode() == PCDM_ReaderFilter::AppendMode_Protect)
            continue;
          if (theFilter->Mode() == PCDM_ReaderFilter::AppendMode_Overwrite)
            theLabel.ForgetAttribute(tAtt->ID());
        }
        try
        {
          theLabel.AddAttribute(tAtt);
        }
        catch (const Standard_DomainError&)
        {

          static const Standard_GUID fbidGuid;
          tAtt->SetID(fbidGuid);
          theLabel.AddAttribute(tAtt);
        }
      }
      else
        myMsgDriver->Send(aMethStr + "warning: attempt to attach attribute " + aDriver->TypeName()
                            + " to a second label",
                          Message_Warning);

      bool ok = aDriver->Paste(myPAtt, tAtt, myRelocTable);
      if (!ok)
      {

        myMsgDriver->Send(aMethStr + "warning: failure reading attribute " + aDriver->TypeName(),
                          Message_Warning);
      }
      else if (!isBound)
      {
        myRelocTable.Bind(anID, tAtt);
        occ::handle<TDataStd_TreeNode> aNode = occ::down_cast<TDataStd_TreeNode>(tAtt);
        if (!theFilter.IsNull() && !aNode.IsNull() && !aNode->Father().IsNull()
            && aNode->Father()->IsNew())
        {
          int anUnresolvedLink;
          myPAtt.SetPosition(BP_HEADSIZE);
          myPAtt >> anUnresolvedLink;
          myUnresolvedLinks.Add(anUnresolvedLink);
        }
      }
    }
    else if (!myMapUnsupported.Contains(myPAtt.TypeId()))
      myMsgDriver->Send(aMethStr + "warning: type ID not registered in header: " + myPAtt.TypeId(),
                        Message_Warning);
  }
  if (!theIS || myPAtt.TypeId() != BinLDrivers_ENDATTRLIST)
  {

    myMsgDriver->Send(aMethStr + "error: unexpected EOF or garbage data", Message_Fail);
    myReaderStatus = PCDM_RS_UnrecognizedFileFormat;
    return -1;
  }

  int aTag = BinLDrivers_ENDLABEL;
  theIS.read((char*)&aTag, sizeof(int));
#ifdef DO_INVERSE
  aTag = InverseInt(aTag);
#endif

  while (theIS && aTag >= 0 && !theIS.eof())
  {

    TDF_Label aLab = theLabel.FindChild(aTag, true);
    if (!aPS.More())
    {
      myReaderStatus = PCDM_RS_UserBreak;
      return -1;
    }

    if (!theFilter.IsNull())
      theFilter->Down(aTag);
    int nbSubRead = ReadSubTree(theIS, aLab, theFilter, theQuickPart, theReadMissing, aPS.Next());

    if (nbSubRead == -1)
      return -1;
    nbRead += nbSubRead;

    theIS.read((char*)&aTag, sizeof(int));
#ifdef DO_INVERSE
    aTag = InverseInt(aTag);
#endif
  }

  if (aTag != BinLDrivers_ENDLABEL)
  {

    myMsgDriver->Send(aMethStr + "error: invalid end label marker", Message_Fail);
    myReaderStatus = PCDM_RS_UnrecognizedFileFormat;
    return -1;
  }
  if (!theFilter.IsNull())
    theFilter->Up();

  return nbRead;
}

occ::handle<BinMDF_ADriverTable> BinLDrivers_DocumentRetrievalDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  return BinLDrivers::AttributeDrivers(theMessageDriver);
}

void BinLDrivers_DocumentRetrievalDriver::ReadSection(BinLDrivers_DocumentSection&,
                                                      const occ::handle<CDM_Document>&,
                                                      Standard_IStream&)
{
}

void BinLDrivers_DocumentRetrievalDriver::ReadShapeSection(BinLDrivers_DocumentSection& theSection,
                                                           Standard_IStream&,
                                                           const bool isMess,
                                                           const Message_ProgressRange&)

{
  if (isMess && theSection.Length())
  {
    const TCollection_ExtendedString aMethStr("BinLDrivers_DocumentRetrievalDriver: ");
    myMsgDriver->Send(aMethStr + "warning: Geometry is not supported by Lite schema. ",
                      Message_Warning);
  }
}

void BinLDrivers_DocumentRetrievalDriver::CheckShapeSection(const Storage_Position& ShapeSectionPos,
                                                            Standard_IStream&       IS)
{
  if (!IS.eof())
  {
    const std::streamoff endPos = IS.rdbuf()->pubseekoff(0L, std::ios_base::end, std::ios_base::in);
#ifdef OCCT_DEBUG
    std::cout << "endPos = " << endPos << std::endl;
#endif
    if (ShapeSectionPos != endPos)
    {
      const TCollection_ExtendedString aMethStr("BinLDrivers_DocumentRetrievalDriver: ");
      myMsgDriver->Send(aMethStr + "warning: Geometry is not supported by Lite schema. ",
                        Message_Warning);
    }
  }
}

void BinLDrivers_DocumentRetrievalDriver::Clear()
{
  myPAtt.Destroy();
  myRelocTable.Clear();
  myMapUnsupported.Clear();
}

bool BinLDrivers_DocumentRetrievalDriver::CheckDocumentVersion(const int theFileVersion,
                                                               const int theCurVersion)
{

  return theFileVersion >= TDocStd_FormatVersion_LOWER && theFileVersion <= theCurVersion;
}

bool BinLDrivers_DocumentRetrievalDriver::IsQuickPart(const int theFileVer)
{
  return theFileVer >= TDocStd_FormatVersion_VERSION_12;
}
