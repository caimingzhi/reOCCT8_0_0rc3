#include <CDM_Application.hpp>
#include <Message_Messenger.hpp>
#include <Message_ProgressScope.hpp>
#include <CDM_MetaData.hpp>
#include <OSD_FileSystem.hpp>
#include <OSD_Path.hpp>
#include <PCDM_DOMHeaderParser.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDF_Data.hpp>
#include <TDocStd_Document.hpp>
#include <TDocStd_Owner.hpp>
#include <UTL.hpp>
#include <XmlLDrivers.hpp>
#include <XmlLDrivers_DocumentRetrievalDriver.hpp>
#include <XmlMDF.hpp>
#include <XmlMDF_ADriver.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_RRelocationTable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlLDrivers_DocumentRetrievalDriver, PCDM_RetrievalDriver)

#ifdef _MSC_VER
  #include <tchar.h>
#endif

#include <Standard_Failure.hpp>
#include <Standard_ErrorHandler.hpp>

#define START_REF "START_REF"
#define END_REF "END_REF"

#define MODIFICATION_COUNTER "MODIFICATION_COUNTER: "
#define REFERENCE_COUNTER "REFERENCE_COUNTER: "

static void take_time(const int, const char*, const occ::handle<Message_Messenger>&)
#ifdef TAKE_TIMES
  ;
#else
{
}
#endif

static int RemoveExtraSeparator(TCollection_AsciiString& aString)
{

  int i, j, len;

  len = aString.Length();
#ifdef _WIN32

  for (i = j = 2; j <= len; i++, j++)
  {
#else
  for (i = j = 1; j <= len; i++, j++)
  {
#endif
    char c = aString.Value(j);
    aString.SetValue(i, c);
    if (c == '/')
      while (j < len && aString.Value(j + 1) == '/')
        j++;
  }
  len = i - 1;
  if (aString.Value(len) == '/')
    len--;
  aString.Trunc(len);
  return len;
}

static TCollection_AsciiString GetDirFromFile(const TCollection_ExtendedString& aFileName)
{
  TCollection_AsciiString theCFile = UTL::CString(aFileName);
  TCollection_AsciiString theDirectory;
  int                     i = theCFile.SearchFromEnd("/");
#ifdef _WIN32

  if (theCFile.SearchFromEnd("\\") > i)
    i = theCFile.SearchFromEnd("\\");
#endif
  if (i != -1)
    theDirectory = theCFile.SubString(1, i);
  return theDirectory;
}

static TCollection_AsciiString AbsolutePath(const TCollection_AsciiString& aDirPath,
                                            const TCollection_AsciiString& aRelFilePath)
{
  TCollection_AsciiString EmptyString = "";
#ifdef _WIN32
  if (aRelFilePath.Search(":") == 2
      || (aRelFilePath.Search("\\") == 1 && aRelFilePath.Value(2) == '\\'))
#else
  if (aRelFilePath.Search("/") == 1)
#endif
    return aRelFilePath;

  TCollection_AsciiString DirPath = aDirPath, RelFilePath = aRelFilePath;
  int                     i, len;

#ifdef _WIN32
  if (DirPath.Search(":") != 2 && (DirPath.Search("\\") != 1 || DirPath.Value(2) != '\\'))
#else
  if (DirPath.Search("/") != 1)
#endif
    return EmptyString;

#ifdef _WIN32
  DirPath.ChangeAll('\\', '/');
  RelFilePath.ChangeAll('\\', '/');
#endif

  RemoveExtraSeparator(DirPath);
  len = RemoveExtraSeparator(RelFilePath);

  while (RelFilePath.Search("../") == 1)
  {
    if (len == 3)
      return EmptyString;
    RelFilePath = RelFilePath.SubString(4, len);
    len -= 3;
    if (DirPath.IsEmpty())
      return EmptyString;
    i = DirPath.SearchFromEnd("/");
    if (i < 0)
      return EmptyString;
    DirPath.Trunc(i - 1);
  }
  TCollection_AsciiString retx;
  retx = DirPath;
  retx += "/";
  retx += RelFilePath;
  return retx;
}

XmlLDrivers_DocumentRetrievalDriver::XmlLDrivers_DocumentRetrievalDriver()
{
  myReaderStatus = PCDM_RS_OK;
}

void XmlLDrivers_DocumentRetrievalDriver::Read(const TCollection_ExtendedString&     theFileName,
                                               const occ::handle<CDM_Document>&      theNewDocument,
                                               const occ::handle<CDM_Application>&   theApplication,
                                               const occ::handle<PCDM_ReaderFilter>& theFilter,
                                               const Message_ProgressRange&          theRange)
{
  myReaderStatus = PCDM_RS_DriverFailure;
  myFileName     = theFileName;

  const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
  std::shared_ptr<std::istream> aFileStream = aFileSystem->OpenIStream(myFileName, std::ios::in);

  if (aFileStream.get() != nullptr && aFileStream->good())
  {
    Read(*aFileStream, nullptr, theNewDocument, theApplication, theFilter, theRange);
  }
  else
  {
    myReaderStatus = PCDM_RS_OpenError;

    TCollection_ExtendedString aMsg = TCollection_ExtendedString("Error: the file ") + theFileName
                                      + " cannot be opened for reading";

    theApplication->MessageDriver()->Send(aMsg.ToExtString(), Message_Fail);
    throw Standard_Failure("File cannot be opened for reading");
  }
}

void XmlLDrivers_DocumentRetrievalDriver::Read(Standard_IStream& theIStream,
                                               const occ::handle<Storage_Data>&,
                                               const occ::handle<CDM_Document>&    theNewDocument,
                                               const occ::handle<CDM_Application>& theApplication,
                                               const occ::handle<PCDM_ReaderFilter>&,
                                               const Message_ProgressRange& theRange)
{
  occ::handle<Message_Messenger> aMessageDriver = theApplication->MessageDriver();
  ::take_time(~0, " +++++ Start RETRIEVE procedures ++++++", aMessageDriver);

  LDOMParser aParser;

  bool aWithoutRoot = myFileName.IsEmpty();

  if (aParser.parse(theIStream, false, aWithoutRoot))
  {
    TCollection_AsciiString aData;
    std::cout << aParser.GetError(aData) << ": " << aData << std::endl;
    myReaderStatus = PCDM_RS_FormatFailure;
    return;
  }
  const XmlObjMgt_Element anElement = aParser.getDocument().getDocumentElement();
  ::take_time(0, " +++++ Fin parsing XML :       ", aMessageDriver);

  ReadFromDomDocument(anElement, theNewDocument, theApplication, theRange);
}

void XmlLDrivers_DocumentRetrievalDriver::ReadFromDomDocument(
  const XmlObjMgt_Element&            theElement,
  const occ::handle<CDM_Document>&    theNewDocument,
  const occ::handle<CDM_Application>& theApplication,
  const Message_ProgressRange&        theRange)
{
  const occ::handle<Message_Messenger> aMsgDriver = theApplication->MessageDriver();

  TCollection_AsciiString    anAbsoluteDirectory = GetDirFromFile(myFileName);
  int                        aCurDocVersion      = TDocStd_FormatVersion_VERSION_2;
  TCollection_ExtendedString anInfo;
  const XmlObjMgt_Element    anInfoElem = theElement.GetChildByTagName("info");
  if (anInfoElem != nullptr)
  {
    XmlObjMgt_DOMString aDocVerStr = anInfoElem.getAttribute("DocVersion");
    if (aDocVerStr != nullptr)
    {
      int anIntegerVersion = 0;
      if (aDocVerStr.GetInteger(anIntegerVersion))
      {
        aCurDocVersion = anIntegerVersion;
      }
      else
      {
        TCollection_ExtendedString aMsg =
          TCollection_ExtendedString("Cannot retrieve the current Document version"
                                     " attribute as \"")
          + aDocVerStr + "\"";
        if (!aMsgDriver.IsNull())
        {
          aMsgDriver->Send(aMsg.ToExtString(), Message_Fail);
        }
      }
    }

    if (aCurDocVersion > TDocStd_Document::CurrentStorageFormatVersion())
    {
      TCollection_ExtendedString aMsg = TCollection_ExtendedString("error: wrong file version: ")
                                        + aDocVerStr + " while current is "
                                        + TDocStd_Document::CurrentStorageFormatVersion();
      myReaderStatus = PCDM_RS_NoVersion;
      if (!aMsgDriver.IsNull())
        aMsgDriver->Send(aMsg.ToExtString(), Message_Fail);
      return;
    }

    bool isRef = false;
    for (LDOM_Node aNode = anInfoElem.getFirstChild(); aNode != nullptr;
         aNode           = aNode.getNextSibling())
    {
      if (aNode.getNodeType() == LDOM_Node::ELEMENT_NODE)
      {
        if (XmlObjMgt::GetExtendedString((LDOM_Element&)aNode, anInfo))
        {

          if (anInfo.Search(REFERENCE_COUNTER) != -1)
          {
            try
            {
              OCC_CATCH_SIGNALS
              TCollection_AsciiString anInf(anInfo, '?');
              int                     aRefCounter = anInf.Token(" ", 2).IntegerValue();
              theNewDocument->SetReferenceCounter(aRefCounter);
            }
            catch (Standard_Failure const&)
            {

              TCollection_ExtendedString aMsg("Warning: ");
              aMsg = aMsg.Cat("could not read the reference counter").Cat("\0");
              if (!aMsgDriver.IsNull())
                aMsgDriver->Send(aMsg.ToExtString(), Message_Warning);
            }
          }
          else if (anInfo.Search(MODIFICATION_COUNTER) != -1)
          {
            try
            {
              OCC_CATCH_SIGNALS

              TCollection_AsciiString anInf(anInfo, '?');
              int                     aModCounter = anInf.Token(" ", 2).IntegerValue();
              theNewDocument->SetModifications(aModCounter);
            }
            catch (Standard_Failure const&)
            {
              TCollection_ExtendedString aMsg("Warning: could not read the modification counter\0");
              if (!aMsgDriver.IsNull())
                aMsgDriver->Send(aMsg.ToExtString(), Message_Warning);
            }
          }

          if (anInfo == END_REF)
            isRef = false;
          if (isRef)
          {

            int pos = anInfo.Search(" ");
            if (pos != -1)
            {

              int                        aRefId;
              TCollection_ExtendedString aFileName;
              int                        aDocumentVersion;

              TCollection_ExtendedString aRest = anInfo.Split(pos);
              aRefId                           = UTL::IntegerValue(anInfo);

              int pos2 = aRest.Search(" ");

              aFileName        = aRest.Split(pos2);
              aDocumentVersion = UTL::IntegerValue(aRest);

              TCollection_AsciiString aPath = UTL::CString(aFileName);
              TCollection_AsciiString anAbsolutePath;
              if (!anAbsoluteDirectory.IsEmpty())
              {
                anAbsolutePath = AbsolutePath(anAbsoluteDirectory, aPath);
                if (!anAbsolutePath.IsEmpty())
                  aPath = anAbsolutePath;
              }
              if (!aMsgDriver.IsNull())
              {

                TCollection_ExtendedString aMsg("Warning: ");
                aMsg = aMsg.Cat("reference found; ReferenceIdentifier:  ")
                         .Cat(aRefId)
                         .Cat("; File:")
                         .Cat(aPath)
                         .Cat(", version:")
                         .Cat(aDocumentVersion)
                         .Cat("\0");
                aMsgDriver->Send(aMsg.ToExtString(), Message_Warning);
              }

              TCollection_ExtendedString theFolder, theName;

              TCollection_ExtendedString f(aPath);
#ifndef _WIN32

              int                        i = f.SearchFromEnd("/");
              TCollection_ExtendedString n = f.Split(i);
              f.Trunc(f.Length() - 1);
              theFolder = f;
              theName   = n;
#else
              OSD_Path                   p = UTL::Path(f);
              char16_t                   chr;
              TCollection_ExtendedString dir, dirRet, name;

              dir = UTL::Disk(p);
              dir += UTL::Trek(p);

              for (int i = 1; i <= dir.Length(); ++i)
              {

                chr = dir.Value(i);

                switch (chr)
                {

                  case '|':
                    dirRet += "/";
                    break;

                  case '^':

                    dirRet += "..";
                    break;

                  default:
                    dirRet += chr;
                }
              }
              theFolder = dirRet;
              theName   = UTL::Name(p);
              theName += UTL::Extension(p);
#endif

              occ::handle<CDM_MetaData> aMetaData =
                CDM_MetaData::LookUp(theApplication->MetaDataLookUpTable(),
                                     theFolder,
                                     theName,
                                     aPath,
                                     aPath,
                                     UTL::IsReadOnly(aFileName));

              theNewDocument->CreateReference(aMetaData,
                                              aRefId,
                                              theApplication,
                                              aDocumentVersion,
                                              false);
            }
          }
          if (anInfo == START_REF)
            isRef = true;
        }
      }
    }
  }

  TCollection_ExtendedString aComment;
  const XmlObjMgt_Element    aCommentsElem = theElement.GetChildByTagName("comments");
  if (aCommentsElem != nullptr)
  {
    for (LDOM_Node aNode = aCommentsElem.getFirstChild(); aNode != nullptr;
         aNode           = aNode.getNextSibling())
    {
      if (aNode.getNodeType() == LDOM_Node::ELEMENT_NODE)
      {
        if (XmlObjMgt::GetExtendedString((LDOM_Element&)aNode, aComment))
        {
          theNewDocument->AddComment(aComment);
        }
      }
    }
  }
  Message_ProgressScope aPS(theRange, "Reading document", 2);

  if (myDrivers.IsNull())
    myDrivers = AttributeDrivers(aMsgDriver);
  const occ::handle<XmlMDF_ADriver> aNSDriver =
    ReadShapeSection(theElement, aMsgDriver, aPS.Next());
  if (!aNSDriver.IsNull())
    ::take_time(0, " +++++ Fin reading Shapes :    ", aMsgDriver);

  if (!aPS.More())
  {
    myReaderStatus = PCDM_RS_UserBreak;
    return;
  }

  occ::handle<Storage_HeaderData> aHeaderData = new Storage_HeaderData();
  aHeaderData->SetStorageVersion(aCurDocVersion);
  myRelocTable.Clear();
  myRelocTable.SetHeaderData(aHeaderData);

  try
  {
    OCC_CATCH_SIGNALS
#ifdef OCCT_DEBUG
    TCollection_ExtendedString aMessage("PasteDocument");
    aMsgDriver->Send(aMessage.ToExtString(), Message_Trace);
#endif
    if (!MakeDocument(theElement, theNewDocument, aPS.Next()))
      myReaderStatus = PCDM_RS_MakeFailure;
    else
      myReaderStatus = PCDM_RS_OK;
  }
  catch (Standard_Failure const& anException)
  {
    TCollection_ExtendedString anErrorString(anException.what());
    aMsgDriver->Send(anErrorString.ToExtString(), Message_Fail);
  }
  if (!aPS.More())
  {
    myReaderStatus = PCDM_RS_UserBreak;
    return;
  }

  ShapeSetCleaning(aNSDriver);

  myRelocTable.Clear();
  ::take_time(0, " +++++ Fin reading data OCAF : ", aMsgDriver);
}

bool XmlLDrivers_DocumentRetrievalDriver::MakeDocument(const XmlObjMgt_Element&         theElement,
                                                       const occ::handle<CDM_Document>& theTDoc,
                                                       const Message_ProgressRange&     theRange)
{
  bool                          aResult = false;
  occ::handle<TDocStd_Document> TDOC    = occ::down_cast<TDocStd_Document>(theTDoc);
  if (!TDOC.IsNull())
  {
    occ::handle<TDF_Data> aTDF = new TDF_Data();
    aResult = XmlMDF::FromTo(theElement, aTDF, myRelocTable, myDrivers, theRange);
    if (aResult)
    {
      TDOC->SetData(aTDF);
      TDocStd_Owner::SetDocument(aTDF, TDOC);
    }
  }
  return aResult;
}

occ::handle<XmlMDF_ADriverTable> XmlLDrivers_DocumentRetrievalDriver::AttributeDrivers(
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
extern struct timeb tmbuf0;

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
  aMessageDriver->Write(aMessage.ToExtString());
}
#endif

occ::handle<XmlMDF_ADriver> XmlLDrivers_DocumentRetrievalDriver::ReadShapeSection(
  const XmlObjMgt_Element&,
  const occ::handle<Message_Messenger>&,
  const Message_ProgressRange&)
{
  occ::handle<XmlMDF_ADriver> aDriver;

  return aDriver;
}

void XmlLDrivers_DocumentRetrievalDriver::ShapeSetCleaning(const occ::handle<XmlMDF_ADriver>&) {}
