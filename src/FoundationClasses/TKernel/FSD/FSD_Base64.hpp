#pragma once

#include <NCollection_Buffer.hpp>
#include <TCollection_AsciiString.hpp>

class FSD_Base64
{
public:
  Standard_EXPORT static size_t Encode(char*          theEncodedStr,
                                       const size_t   theStrLen,
                                       const uint8_t* theData,
                                       const size_t   theDataLen);

  Standard_EXPORT static TCollection_AsciiString Encode(const uint8_t* theData,
                                                        const size_t   theDataLen);

  Standard_EXPORT static size_t Decode(uint8_t*     theDecodedData,
                                       const size_t theDataLen,
                                       const char*  theEncodedStr,
                                       const size_t theStrLen);

  Standard_EXPORT static occ::handle<NCollection_Buffer> Decode(const char*  theStr,
                                                                const size_t theLen);
};
