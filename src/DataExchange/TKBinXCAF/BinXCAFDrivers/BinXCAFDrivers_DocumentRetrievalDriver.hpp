#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BinDrivers_DocumentRetrievalDriver.hpp>
class BinMDF_ADriverTable;
class Message_Messenger;

class BinXCAFDrivers_DocumentRetrievalDriver : public BinDrivers_DocumentRetrievalDriver
{

public:
  Standard_EXPORT BinXCAFDrivers_DocumentRetrievalDriver();

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

  DEFINE_STANDARD_RTTIEXT(BinXCAFDrivers_DocumentRetrievalDriver,
                          BinDrivers_DocumentRetrievalDriver)
};
