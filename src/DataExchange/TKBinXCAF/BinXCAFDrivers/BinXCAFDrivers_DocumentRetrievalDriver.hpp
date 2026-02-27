#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BinDrivers_DocumentRetrievalDriver.hpp>
class BinMDF_ADriverTable;
namespace System { namespace log {
class Message_Messenger;
}} // namespace System::log


class BinXCAFDrivers_DocumentRetrievalDriver : public BinDrivers_DocumentRetrievalDriver
{

public:
  Standard_EXPORT BinXCAFDrivers_DocumentRetrievalDriver();

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<System::log::Message_Messenger>& theMsgDriver) override;

  DEFINE_STANDARD_RTTIEXT(BinXCAFDrivers_DocumentRetrievalDriver,
                          BinDrivers_DocumentRetrievalDriver)
};
