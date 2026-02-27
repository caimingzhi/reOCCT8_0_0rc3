#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class BinMDF_ADriverTable;
namespace System { namespace log {
class Message_Messenger;
}} // namespace System::log


class BinMDF
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void AddDrivers(const occ::handle<BinMDF_ADriverTable>& aDriverTable,
                                         const occ::handle<System::log::Message_Messenger>&   aMsgDrv);
};
