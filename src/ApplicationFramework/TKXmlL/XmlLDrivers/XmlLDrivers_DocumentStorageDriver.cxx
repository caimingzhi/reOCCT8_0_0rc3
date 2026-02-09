#include <CDM_Application.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Message_ProgressScope.hpp>
#include <LDOM_XmlWriter.hpp>
#include <OSD_Environment.hpp>
#include <OSD_File.hpp>
#include <OSD_FileSystem.hpp>
#include <PCDM_ReadWriter.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <Standard_Type.hpp>
#include <Storage_Data.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_Sequence.hpp>
#include <TDocStd_Document.hpp>
#include <XmlLDrivers.hpp>
#include <XmlLDrivers_DocumentStorageDriver.hpp>
#include <XmlLDrivers_NamespaceDef.hpp>
#include <XmlMDF.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Document.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlLDrivers_DocumentStorageDriver, PCDM_StorageDriver)

#define STORAGE_VERSION "STORAGE_VERSION: "
#define REFERENCE_COUNTER "REFERENCE_COUNTER: "
#define MODIFICATION_COUNTER "MODIFICATION_COUNTER: "
#define START_REF "START_REF"
#define END_REF "END_REF"

#define FAILSTR "Failed to write xsi:schemaLocation : "

static void take_time(const int, const char*, const occ::handle<Message_Messenger>&)
#ifdef TAKE_TIMES
  ;
#else
{
}
#endif

XmlLDrivers_DocumentStorageDriver::XmlLDrivers_DocumentStorageDriver(
  const TCollection_ExtendedString& theCopyright)
    : myCopyright(theCopyright)
{
}

void XmlLDrivers_DocumentStorageDriver::AddNamespace(const TCollection_AsciiString& thePrefix,
                                                     const TCollection_AsciiString& theURI)
{
  for (int i = 1; i <= mySeqOfNS.Length(); i++)
    if (thePrefix == mySeqOfNS(i).Prefix())
      return;
  mySeqOfNS.Append(XmlLDrivers_NamespaceDef(thePrefix, theURI));
}

void XmlLDrivers_DocumentStorageDriver::Write(const occ::handle<CDM_Document>&  theDocument,
                                              const TCollection_ExtendedString& theFileName,
                                              const Message_ProgressRange&      theRange)
{
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

    TCollection_ExtendedString aMsg = TCollection_ExtendedString("Error: the file ") + theFileName
                                      + " cannot be opened for writing";

    theDocument->Application()->MessageDriver()->Send(aMsg.ToExtString(), Message_Fail);
    throw Standard_Failure("File cannot be opened for writing");
  }
}

void XmlLDrivers_DocumentStorageDriver::Write(const occ::handle<CDM_Document>& theDocument,
                                              Standard_OStream&                theOStream,
                                              const Message_ProgressRange&     theRange)
{
  occ::handle<Message_Messenger> aMessageDriver = theDocument->Application()->MessageDriver();
  ::take_time(~0, " +++++ Start STORAGE procedures ++++++", aMessageDriver);

  XmlObjMgt_Document aDOMDoc = XmlObjMgt_Document::createDocument("document");

  XmlObjMgt_Element anElement = aDOMDoc.getDocumentElement();

  if (!WriteToDomDocument(theDocument, anElement, theRange))
  {

    LDOM_XmlWriter aWriter;
    aWriter.SetIndentation(1);

    if (theOStream.good())
    {
      aWriter.Write(theOStream, aDOMDoc);
    }
    else
    {
      SetIsError(true);
      SetStoreStatus(PCDM_SS_WriteFailure);

      TCollection_ExtendedString aMsg =
        TCollection_ExtendedString("Error: the stream is bad and") + " cannot be used for writing";
      theDocument->Application()->MessageDriver()->Send(aMsg.ToExtString(), Message_Fail);

      throw Standard_Failure("File cannot be opened for writing");
    }

    ::take_time(0, " +++++ Fin formatting to XML : ", aMessageDriver);
  }
}

bool XmlLDrivers_DocumentStorageDriver::WriteToDomDocument(
  const occ::handle<CDM_Document>& theDocument,
  XmlObjMgt_Element&               theElement,
  const Message_ProgressRange&     theRange)
{
  SetIsError(false);
  occ::handle<Message_Messenger> aMessageDriver = theDocument->Application()->MessageDriver();

  int                i;
  XmlObjMgt_Document aDOMDoc = theElement.getOwnerDocument();

  TCollection_AsciiString aStorageFormat(theDocument->StorageFormat(), '?');
  theElement.setAttribute("format", aStorageFormat.ToCString());

  theElement.setAttribute("xmlns", "http://www.opencascade.org/OCAF/XML");
  for (i = 1; i <= mySeqOfNS.Length(); i++)
  {
    TCollection_AsciiString aPrefix =
      TCollection_AsciiString("xmlns:") + mySeqOfNS(i).Prefix().ToCString();
    theElement.setAttribute(aPrefix.ToCString(), mySeqOfNS(i).URI().ToCString());
  }
  theElement.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");

  TCollection_AsciiString anHTTP            = "http://www.opencascade.org/OCAF/XML";
  bool                    aToSetCSFVariable = false;
  const char*             aCSFVariable[2]   = {"CSF_XmlOcafResource", "CASROOT"};
  OSD_Environment         anEnv(aCSFVariable[0]);
  TCollection_AsciiString aResourceDir = anEnv.Value();
  if (aResourceDir.IsEmpty())
  {

    OSD_Environment anEnv2(aCSFVariable[1]);
    aResourceDir = anEnv2.Value();
    if (!aResourceDir.IsEmpty())
    {
      aResourceDir += "/src/XmlOcafResource";
      aToSetCSFVariable = true;
    }
#ifdef OCCT_DEBUGXML
    else
    {
      TCollection_ExtendedString aWarn = FAILSTR "Neither ";
      aWarn = (aWarn + aCSFVariable[0] + ", nor " + aCSFVariable[1] + " variables have been set");
      aMessageDriver->Send(aWarn.ToExtString(), Message_Warning);
    }
#endif
  }
  if (!aResourceDir.IsEmpty())
  {
    TCollection_AsciiString aResourceFileName = aResourceDir + "/XmlOcaf.xsd";

    OSD_File aResourceFile(aResourceFileName);
    if (aResourceFile.Exists())
    {
      if (aToSetCSFVariable)
      {
        OSD_Environment aCSFVarEnv(aCSFVariable[0], aResourceDir);
        aCSFVarEnv.Build();
#ifdef OCCT_DEBUGXML
        TCollection_ExtendedString aWarn1 = "Variable ";
        aWarn1 =
          (aWarn1 + aCSFVariable[0] + " has not been explicitly defined. Set to " + aResourceDir);
        aMessageDriver->Send(aWarn1.ToExtString(), Message_Warning);
#endif
        if (aCSFVarEnv.Failed())
        {
          TCollection_ExtendedString aWarn = FAILSTR "Failed to initialize ";
          aWarn                            = aWarn + aCSFVariable[0] + " with " + aResourceDir;
          aMessageDriver->Send(aWarn.ToExtString(), Message_Fail);
        }
      }
    }
#ifdef OCCT_DEBUGXML
    else
    {
      TCollection_ExtendedString aWarn = FAILSTR "Schema definition file ";
      aWarn += (aResourceFileName + " was not found");
      aMessageDriver->Send(aWarn.ToExtString(), Message_Warning);
    }
#endif
    anHTTP = anHTTP + ' ' + aResourceFileName;
  }
  theElement.setAttribute("xsi:schemaLocation", anHTTP.ToCString());

  XmlObjMgt_Element anInfoElem = aDOMDoc.createElement("info");
  theElement.appendChild(anInfoElem);

  TCollection_AsciiString aCreationDate = XmlLDrivers::CreationDate();

  anInfoElem.setAttribute("date", aCreationDate.ToCString());
  anInfoElem.setAttribute("schemav", 0);

  occ::handle<TDocStd_Document> aDoc = occ::down_cast<TDocStd_Document>(theDocument);

  TDocStd_FormatVersion aFormatVersion = TDocStd_Document::CurrentStorageFormatVersion();

  if (TDocStd_Document::CurrentStorageFormatVersion() < aDoc->StorageFormatVersion())
  {
    TCollection_ExtendedString anErrorString(
      "Unacceptable storage format version, the last version is used");
    aMessageDriver->Send(anErrorString.ToExtString(), Message_Warning);
  }
  else
  {
    aFormatVersion = aDoc->StorageFormatVersion();
  }
  const TCollection_AsciiString aStringFormatVersion(aFormatVersion);
  anInfoElem.setAttribute("DocVersion", aStringFormatVersion.ToCString());

  NCollection_Sequence<TCollection_AsciiString> aUserInfo;
  if (myCopyright.Length() > 0)
    aUserInfo.Append(TCollection_AsciiString(myCopyright, '?'));

  occ::handle<Storage_Data> theData = new Storage_Data;

  PCDM_ReadWriter::Writer()->WriteReferenceCounter(theData, theDocument);
  PCDM_ReadWriter::Writer()->WriteReferences(theData, theDocument, myFileName);
  PCDM_ReadWriter::Writer()->WriteExtensions(theData, theDocument);
  PCDM_ReadWriter::Writer()->WriteVersion(theData, theDocument);

  const NCollection_Sequence<TCollection_AsciiString>& aRefs = theData->UserInfo();
  for (i = 1; i <= aRefs.Length(); i++)
    aUserInfo.Append(aRefs.Value(i));

  occ::handle<Storage_HeaderData> aHeaderData = theData->HeaderData();
  aHeaderData->SetStorageVersion(aFormatVersion);
  myRelocTable.Clear();
  myRelocTable.SetHeaderData(aHeaderData);

  for (i = 1; i <= aUserInfo.Length(); i++)
  {
    XmlObjMgt_Element aUIItem = aDOMDoc.createElement("iitem");
    anInfoElem.appendChild(aUIItem);
    LDOM_Text aUIText = aDOMDoc.createTextNode(aUserInfo(i).ToCString());
    aUIItem.appendChild(aUIText);
  }

  NCollection_Sequence<TCollection_ExtendedString> aComments;
  theDocument->Comments(aComments);

  XmlObjMgt_Element aCommentsElem = aDOMDoc.createElement("comments");
  theElement.appendChild(aCommentsElem);

  for (i = 1; i <= aComments.Length(); i++)
  {
    XmlObjMgt_Element aCItem = aDOMDoc.createElement("citem");
    aCommentsElem.appendChild(aCItem);
    XmlObjMgt::SetExtendedString(aCItem, aComments(i));
  }
  Message_ProgressScope aPS(theRange, "Writing", 2);

  int anObjNb = 0;
  {
    try
    {
      OCC_CATCH_SIGNALS
      anObjNb = MakeDocument(theDocument, theElement, aPS.Next());
      if (!aPS.More())
      {
        SetIsError(true);
        SetStoreStatus(PCDM_SS_UserBreak);
        return IsError();
      }
    }
    catch (Standard_Failure const& anException)
    {
      SetIsError(true);
      SetStoreStatus(PCDM_SS_Failure);
      TCollection_ExtendedString anErrorString(anException.what());
      aMessageDriver->Send(anErrorString.ToExtString(), Message_Fail);
    }
  }
  if (anObjNb <= 0 && !IsError())
  {
    SetIsError(true);
    SetStoreStatus(PCDM_SS_No_Obj);
    TCollection_ExtendedString anErrorString("error occurred");
    aMessageDriver->Send(anErrorString.ToExtString(), Message_Fail);
  }

  anInfoElem.setAttribute("objnb", anObjNb);
  ::take_time(0, " +++++ Fin DOM data for OCAF : ", aMessageDriver);

  myRelocTable.Clear();

  if (WriteShapeSection(theElement, aFormatVersion, aPS.Next()))
    ::take_time(0, " +++ Fin DOM data for Shapes : ", aMessageDriver);
  if (!aPS.More())
  {
    SetIsError(true);
    SetStoreStatus(PCDM_SS_UserBreak);
    return IsError();
  }
  return IsError();
}

int XmlLDrivers_DocumentStorageDriver::MakeDocument(const occ::handle<CDM_Document>& theTDoc,
                                                    XmlObjMgt_Element&               theElement,
                                                    const Message_ProgressRange&     theRange)
{
  TCollection_ExtendedString    aMessage;
  occ::handle<TDocStd_Document> TDOC = occ::down_cast<TDocStd_Document>(theTDoc);
  if (!TDOC.IsNull())
  {

    occ::handle<TDF_Data> aTDF = TDOC->GetData();

    occ::handle<CDM_Application>   anApplication = theTDoc->Application();
    occ::handle<Message_Messenger> aMessageDriver;
    if (anApplication.IsNull())
    {
      aMessageDriver = Message::DefaultMessenger();
      aMessageDriver->ChangePrinters().Clear();
    }
    else
      aMessageDriver = anApplication->MessageDriver();
    if (myDrivers.IsNull())
      myDrivers = AttributeDrivers(aMessageDriver);

    XmlMDF::FromTo(aTDF, theElement, myRelocTable, myDrivers, theRange);
#ifdef OCCT_DEBUGXML
    aMessage = "First step successful";
    aMessageDriver->Send(aMessage.ToExtString(), Message_Warning);
#endif
    return myRelocTable.Extent();
  }
#ifdef OCCT_DEBUG
  std::cout << "First step failed" << std::endl;
#endif
  return -1;
}

occ::handle<XmlMDF_ADriverTable> XmlLDrivers_DocumentStorageDriver::AttributeDrivers(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  return XmlLDrivers::AttributeDrivers(theMessageDriver);
}

#ifdef TAKE_TIMES
  #include <time.h>
  #include <sys/timeb.h>
  #include <sys/types.h>
  #include <stdio.h>
  #ifndef _WIN32
extern "C" int ftime(struct timeb* tp);
  #endif
struct timeb tmbuf0;

static void take_time(const int                             isReset,
                      const char*                           aHeader,
                      const occ::handle<Message_Messenger>& aMessageDriver)
{
  struct timeb tmbuf;
  ftime(&tmbuf);
  TCollection_ExtendedString aMessage((const char*)aHeader);
  if (isReset)
    tmbuf0 = tmbuf;
  else
  {
    char take_tm_buf[64];
    Sprintf(take_tm_buf,
            "%9.2f s ++++",
            double(tmbuf.time - tmbuf0.time) + double(tmbuf.millitm - tmbuf0.millitm) / 1000.);
    aMessage += take_tm_buf;
  }
  aMessageDriver->Send(aMessage.ToExtString(), Message_Trace);
}
#endif

bool XmlLDrivers_DocumentStorageDriver::WriteShapeSection(XmlObjMgt_Element&,
                                                          const TDocStd_FormatVersion,
                                                          const Message_ProgressRange&)
{

  return false;
}
