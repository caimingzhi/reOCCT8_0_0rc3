#pragma once

#include <BinLDrivers_DocumentRetrievalDriver.hpp>
#include <BinMDF_ADriverTable.hpp>

class BinTObjDrivers_DocumentRetrievalDriver : public BinLDrivers_DocumentRetrievalDriver
{
public:
  Standard_EXPORT BinTObjDrivers_DocumentRetrievalDriver();

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

public:
  DEFINE_STANDARD_RTTIEXT(BinTObjDrivers_DocumentRetrievalDriver,
                          BinLDrivers_DocumentRetrievalDriver)
};

#ifdef _MSC_VER
  #pragma once
#endif
