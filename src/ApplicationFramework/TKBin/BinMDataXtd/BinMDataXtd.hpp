#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Integer.hpp>
class BinMDF_ADriverTable;
class Message_Messenger;

class BinMDataXtd
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AddDrivers(const occ::handle<BinMDF_ADriverTable>& theDriverTable,
                                         const occ::handle<Message_Messenger>&   aMsgDrv);

  Standard_EXPORT static void SetDocumentVersion(const int DocVersion);

  Standard_EXPORT static int DocumentVersion();
};
