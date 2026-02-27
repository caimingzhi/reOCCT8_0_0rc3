

#include <Storage_BaseDriver.hpp>
#include <Storage_StreamExtCharParityError.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(app::storage::Storage_BaseDriver, Standard_Transient)

app::storage::Storage_BaseDriver::Storage_BaseDriver()
    : myOpenMode(Storage_VSNone)
{
}

app::storage::Storage_BaseDriver::~Storage_BaseDriver() = default;

TCollection_AsciiString app::storage::Storage_BaseDriver::ReadMagicNumber(Standard_IStream& theIStream)
{

  size_t aMagicNumberLen = 7;

  TCollection_AsciiString aReadMagicNumber;

  char   aChar;
  size_t aReadCharNb = 0;

  while (theIStream.good() && (aReadCharNb < aMagicNumberLen))
  {
    theIStream.get(aChar);
    aReadCharNb += (size_t)theIStream.gcount();
    aReadMagicNumber += aChar;
  }

  return aReadMagicNumber;
}
