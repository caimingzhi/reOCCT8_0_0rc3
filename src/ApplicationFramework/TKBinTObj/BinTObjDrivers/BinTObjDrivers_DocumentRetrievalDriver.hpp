#pragma once

#include <BinLDrivers_DocumentRetrievalDriver.hpp>
#include <BinMDF_ADriverTable.hpp>

// Retrieval driver of a TObj Bin document
//

class BinTObjDrivers_DocumentRetrievalDriver : public BinLDrivers_DocumentRetrievalDriver
{
public:
  // ---------- PUBLIC METHODS ----------

  Standard_EXPORT BinTObjDrivers_DocumentRetrievalDriver();
  // Constructor

  Standard_EXPORT occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver) override;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(BinTObjDrivers_DocumentRetrievalDriver,
                          BinLDrivers_DocumentRetrievalDriver)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp

#ifdef _MSC_VER
  #pragma once
#endif
