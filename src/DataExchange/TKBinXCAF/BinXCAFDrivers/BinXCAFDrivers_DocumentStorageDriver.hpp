#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BinDrivers_DocumentStorageDriver.hpp>
class BinMDF_ADriverTable;
namespace System { namespace log {
class Message_Messenger;
}} // namespace System::log


class BinXCAFDrivers_DocumentStorageDriver : public BinDrivers_DocumentStorageDriver
{

public:
  Standard_EXPORT BinXCAFDrivers_DocumentStorageDriver();

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<System::log::Message_Messenger>& theMsgDriver) override;

  DEFINE_STANDARD_RTTIEXT(BinXCAFDrivers_DocumentStorageDriver, BinDrivers_DocumentStorageDriver)
};
