#include <CDM_Application.hpp>
#include <CDM_Document.hpp>
#include <FSD_BinaryFile.hpp>
#include <FSD_CmpFile.hpp>
#include <FSD_File.hpp>
#include <PCDM.hpp>
#include <PCDM_StorageDriver.hpp>
#include <Plugin.hpp>
#include <Resource_Manager.hpp>
#include <TCollection_AsciiString.hpp>

PCDM_TypeOfFileDriver PCDM::FileDriverType(const TCollection_AsciiString&   aFileName,
                                           occ::handle<app::storage::Storage_BaseDriver>& aBaseDriver)
{
  if (app::file::stream::FSD_CmpFile::IsGoodFileType(aFileName) == Storage_VSOk)
  {
    aBaseDriver = new app::file::stream::FSD_CmpFile;
    return PCDM_TOFD_CmpFile;
  }
  else if (app::file::stream::FSD_File::IsGoodFileType(aFileName) == Storage_VSOk)
  {
    aBaseDriver = new app::file::stream::FSD_File;
    return PCDM_TOFD_File;
  }
  else if (app::file::stream::FSD_BinaryFile::IsGoodFileType(aFileName) == Storage_VSOk)
  {
    aBaseDriver = new app::file::stream::FSD_BinaryFile;
    return PCDM_TOFD_File;
  }
  else
  {
    aBaseDriver = nullptr;
    return PCDM_TOFD_Unknown;
  }
}

PCDM_TypeOfFileDriver PCDM::FileDriverType(Standard_IStream&                theIStream,
                                           occ::handle<app::storage::Storage_BaseDriver>& theBaseDriver)
{
  TCollection_AsciiString aReadMagicNumber;

  if (theIStream.good())
  {
    aReadMagicNumber = app::storage::Storage_BaseDriver::ReadMagicNumber(theIStream);
  }

  if (aReadMagicNumber == app::file::stream::FSD_CmpFile::MagicNumber())
  {
    theBaseDriver = new app::file::stream::FSD_CmpFile;
    return PCDM_TOFD_CmpFile;
  }
  else if (aReadMagicNumber == app::file::stream::FSD_File::MagicNumber())
  {
    theBaseDriver = new app::file::stream::FSD_File;
    return PCDM_TOFD_File;
  }
  else if (aReadMagicNumber == app::file::stream::FSD_BinaryFile::MagicNumber())
  {
    theBaseDriver = new app::file::stream::FSD_BinaryFile;
    return PCDM_TOFD_File;
  }
  else if (aReadMagicNumber.Search("<?xml") != -1)
  {

    char aChar = ' ';
    while (theIStream.good() && !theIStream.eof() && aChar != '>')
    {
      theIStream.get(aChar);
    }

    return PCDM_TOFD_XmlFile;
  }

  theBaseDriver = nullptr;
  return PCDM_TOFD_Unknown;
}
