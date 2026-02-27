#pragma once

#include <Storage_BaseDriver.hpp>
#include <PCDM_TypeOfFileDriver.hpp>

class TCollection_AsciiString;

class PCDM
{
public:
  Standard_EXPORT static PCDM_TypeOfFileDriver FileDriverType(
    const TCollection_AsciiString&   aFileName,
    occ::handle<app::storage::Storage_BaseDriver>& aBaseDriver);

  Standard_EXPORT static PCDM_TypeOfFileDriver FileDriverType(
    Standard_IStream&                theIStream,
    occ::handle<app::storage::Storage_BaseDriver>& theBaseDriver);

  DEFINE_STANDARD_ALLOC
};
