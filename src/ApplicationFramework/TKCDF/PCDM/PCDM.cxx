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
                                           occ::handle<Storage_BaseDriver>& aBaseDriver)
{
  if (FSD_CmpFile::IsGoodFileType(aFileName) == Storage_VSOk)
  {
    aBaseDriver = new FSD_CmpFile;
    return PCDM_TOFD_CmpFile;
  }
  else if (FSD_File::IsGoodFileType(aFileName) == Storage_VSOk)
  {
    aBaseDriver = new FSD_File;
    return PCDM_TOFD_File;
  }
  else if (FSD_BinaryFile::IsGoodFileType(aFileName) == Storage_VSOk)
  {
    aBaseDriver = new FSD_BinaryFile;
    return PCDM_TOFD_File;
  }
  else
  {
    aBaseDriver = nullptr;
    return PCDM_TOFD_Unknown;
  }
}

PCDM_TypeOfFileDriver PCDM::FileDriverType(Standard_IStream&                theIStream,
                                           occ::handle<Storage_BaseDriver>& theBaseDriver)
{
  TCollection_AsciiString aReadMagicNumber;

  if (theIStream.good())
  {
    aReadMagicNumber = Storage_BaseDriver::ReadMagicNumber(theIStream);
  }

  if (aReadMagicNumber == FSD_CmpFile::MagicNumber())
  {
    theBaseDriver = new FSD_CmpFile;
    return PCDM_TOFD_CmpFile;
  }
  else if (aReadMagicNumber == FSD_File::MagicNumber())
  {
    theBaseDriver = new FSD_File;
    return PCDM_TOFD_File;
  }
  else if (aReadMagicNumber == FSD_BinaryFile::MagicNumber())
  {
    theBaseDriver = new FSD_BinaryFile;
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
