#include <CDM_Application.hpp>
#include <CDM_Document.hpp>
#include <CDM_MetaData.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Dump.hpp>
#include <CDF_Application.hpp>
#include <Standard_NullObject.hpp>
#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>
#include <OSD_Thread.hpp>
class CDM_MetaData;

IMPLEMENT_STANDARD_RTTIEXT(CDM_MetaData, Standard_Transient)

CDM_MetaData::CDM_MetaData(const TCollection_ExtendedString& aFolder,
                           const TCollection_ExtendedString& aName,
                           const TCollection_ExtendedString& aPath,
                           const TCollection_ExtendedString& aFileName,
                           const bool                        ReadOnly)
    : myIsRetrieved(false),
      myDocument(nullptr),
      myFolder(aFolder),
      myName(aName),
      myHasVersion(false),
      myFileName(aFileName),
      myPath(aPath),
      myDocumentVersion(0),
      myIsReadOnly(ReadOnly)
{
}

CDM_MetaData::CDM_MetaData(const TCollection_ExtendedString& aFolder,
                           const TCollection_ExtendedString& aName,
                           const TCollection_ExtendedString& aPath,
                           const TCollection_ExtendedString& aVersion,
                           const TCollection_ExtendedString& aFileName,
                           const bool                        ReadOnly)
    : myIsRetrieved(false),
      myDocument(nullptr),
      myFolder(aFolder),
      myName(aName),
      myVersion(aVersion),
      myHasVersion(true),
      myFileName(aFileName),
      myPath(aPath),
      myDocumentVersion(0),
      myIsReadOnly(ReadOnly)
{
}

bool CDM_MetaData::IsRetrieved() const
{
  return myIsRetrieved;
}

occ::handle<CDM_Document> CDM_MetaData::Document() const
{
  return myDocument;
}

void CDM_MetaData::SetDocument(const occ::handle<CDM_Document>& aDocument)
{
  myIsRetrieved = true;
  myDocument    = aDocument.operator->();
}

void CDM_MetaData::UnsetDocument()
{
  myIsRetrieved = false;
}

occ::handle<CDM_MetaData> CDM_MetaData::LookUp(
  NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>& theLookUpTable,
  const TCollection_ExtendedString&                                           aFolder,
  const TCollection_ExtendedString&                                           aName,
  const TCollection_ExtendedString&                                           aPath,
  const TCollection_ExtendedString&                                           aFileName,
  const bool                                                                  ReadOnly)
{
  occ::handle<CDM_MetaData>  theMetaData;
  TCollection_ExtendedString aConventionalPath = aPath;
  aConventionalPath.ChangeAll('\\', '/');
  if (!theLookUpTable.IsBound(aConventionalPath))
  {
    theMetaData = new CDM_MetaData(aFolder, aName, aPath, aFileName, ReadOnly);
    theLookUpTable.Bind(aConventionalPath, theMetaData);
  }
  else
  {
    theMetaData = theLookUpTable.Find(aConventionalPath);
  }

  return theMetaData;
}

occ::handle<CDM_MetaData> CDM_MetaData::LookUp(
  NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>& theLookUpTable,
  const TCollection_ExtendedString&                                           aFolder,
  const TCollection_ExtendedString&                                           aName,
  const TCollection_ExtendedString&                                           aPath,
  const TCollection_ExtendedString&                                           aVersion,
  const TCollection_ExtendedString&                                           aFileName,
  const bool                                                                  ReadOnly)
{
  occ::handle<CDM_MetaData>  theMetaData;
  TCollection_ExtendedString aConventionalPath = aPath;
  aConventionalPath.ChangeAll('\\', '/');
  if (!theLookUpTable.IsBound(aConventionalPath))
  {
    theMetaData = new CDM_MetaData(aFolder, aName, aPath, aVersion, aFileName, ReadOnly);
    theLookUpTable.Bind(aConventionalPath, theMetaData);
  }
  else
  {
    theMetaData = theLookUpTable.Find(aConventionalPath);
  }

  return theMetaData;
}

TCollection_ExtendedString CDM_MetaData::Folder() const
{
  return myFolder;
}

TCollection_ExtendedString CDM_MetaData::Name() const
{
  return myName;
}

TCollection_ExtendedString CDM_MetaData::Version() const
{
  Standard_NoSuchObject_Raise_if(!myHasVersion, "Document has no version");
  return myVersion;
}

bool CDM_MetaData::HasVersion() const
{
  return myHasVersion;
}

TCollection_ExtendedString CDM_MetaData::FileName() const
{
  return myFileName;
}

TCollection_ExtendedString CDM_MetaData::Path() const
{
  return myPath;
}

Standard_OStream& CDM_MetaData::Print(Standard_OStream& anOStream) const
{
  anOStream << "*CDM_MetaData*";
  anOStream << myFolder << "," << myName;
  if (HasVersion())
    anOStream << "," << myVersion;
  anOStream << "; Physical situation: ";
  anOStream << myFileName;
  anOStream << std::endl;
  return anOStream;
}

Standard_OStream& CDM_MetaData::operator<<(Standard_OStream& anOStream)
{
  return Print(anOStream);
}

int CDM_MetaData::DocumentVersion(const occ::handle<CDM_Application>& anApplication)
{
  if (myDocumentVersion == 0)
    myDocumentVersion = anApplication->DocumentVersion(this);
  return myDocumentVersion;
}

bool CDM_MetaData::IsReadOnly() const
{
  return myIsReadOnly;
}

void CDM_MetaData::SetIsReadOnly()
{
  myIsReadOnly = true;
}

void CDM_MetaData::UnsetIsReadOnly()
{
  myIsReadOnly = false;
}

void CDM_MetaData::DumpJson(Standard_OStream& theOStream, int) const
{
  OCCT_DUMP_TRANSIENT_CLASS_BEGIN(theOStream)

  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsRetrieved)
  OCCT_DUMP_FIELD_VALUE_POINTER(theOStream, myDocument)

  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myFolder)
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myName)
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myVersion)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myHasVersion)
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myFileName)
  OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myPath)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myDocumentVersion)
  OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsReadOnly)
}
