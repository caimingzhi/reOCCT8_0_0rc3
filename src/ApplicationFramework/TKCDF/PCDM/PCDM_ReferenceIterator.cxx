#include <Message_Messenger.hpp>
#include <CDM_MetaData.hpp>
#include <OSD_Path.hpp>
#include <PCDM_ReferenceIterator.hpp>
#include <PCDM_RetrievalDriver.hpp>
#include <Standard_Type.hpp>
#include <UTL.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PCDM_ReferenceIterator, Standard_Transient)

#ifdef _MSC_VER
  #include <tchar.h>
#endif

PCDM_ReferenceIterator::PCDM_ReferenceIterator(const occ::handle<Message_Messenger>& theMsgDriver)
    : myIterator(0)
{
  myMessageDriver = theMsgDriver;
}

void PCDM_ReferenceIterator::LoadReferences(const occ::handle<CDM_Document>&    aDocument,
                                            const occ::handle<CDM_MetaData>&    aMetaData,
                                            const occ::handle<CDM_Application>& anApplication,
                                            const bool UseStorageConfiguration)
{
  for (Init(aMetaData); More(); Next())
  {
    aDocument->CreateReference(
      MetaData(anApplication->MetaDataLookUpTable(), UseStorageConfiguration),
      ReferenceIdentifier(),
      anApplication,
      DocumentVersion(),
      UseStorageConfiguration);
  }
}

void PCDM_ReferenceIterator::Init(const occ::handle<CDM_MetaData>& theMetaData)
{

  myReferences.Clear();

  PCDM_RetrievalDriver::References(theMetaData->FileName(), myReferences, myMessageDriver);
  myIterator = 1;
}

bool PCDM_ReferenceIterator::More() const
{
  return myIterator <= myReferences.Length();
}

void PCDM_ReferenceIterator::Next()
{
  myIterator++;
}

occ::handle<CDM_MetaData> PCDM_ReferenceIterator::MetaData(
  NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>& theLookUpTable,
  const bool) const
{

  TCollection_ExtendedString theFolder, theName;
  TCollection_ExtendedString theFile = myReferences(myIterator).FileName();
  TCollection_ExtendedString f(theFile);
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

  return CDM_MetaData::LookUp(theLookUpTable,
                              theFolder,
                              theName,
                              theFile,
                              theFile,
                              UTL::IsReadOnly(theFile));
}

int PCDM_ReferenceIterator::ReferenceIdentifier() const
{
  return myReferences(myIterator).ReferenceIdentifier();
}

int PCDM_ReferenceIterator::DocumentVersion() const
{
  return myReferences(myIterator).DocumentVersion();
}
