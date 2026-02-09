#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class BinMDF_ADriverTable;
class Message_Messenger;

class BinMXCAFDoc
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AddDrivers(const occ::handle<BinMDF_ADriverTable>& theDriverTable,
                                         const occ::handle<Message_Messenger>&   theMsgDrv);
};
