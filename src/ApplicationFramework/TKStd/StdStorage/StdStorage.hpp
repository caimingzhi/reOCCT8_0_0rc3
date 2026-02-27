#pragma once

#include <Standard_Macro.hpp>
#include <Storage_Error.hpp>
class StdStorage_Data;
namespace app { namespace storage {
class Storage_BaseDriver;
}} // namespace app::storage

class TCollection_AsciiString;

class StdStorage
{

public:
  Standard_EXPORT static TCollection_AsciiString Version();

  Standard_EXPORT static Storage_Error Read(const TCollection_AsciiString& theFileName,
                                            occ::handle<StdStorage_Data>&  theData);

  Standard_EXPORT static Storage_Error Read(const occ::handle<app::storage::Storage_BaseDriver>& theDriver,
                                            occ::handle<StdStorage_Data>&          theData);

  Standard_EXPORT static Storage_Error Write(const occ::handle<app::storage::Storage_BaseDriver>& theDriver,
                                             const occ::handle<StdStorage_Data>&    theData);
};
