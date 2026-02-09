#pragma once

#include <StdLDrivers_DocumentRetrievalDriver.hpp>

class StdDrivers_DocumentRetrievalDriver : public StdLDrivers_DocumentRetrievalDriver
{
public:
  DEFINE_STANDARD_RTTIEXT(StdDrivers_DocumentRetrievalDriver, StdLDrivers_DocumentRetrievalDriver)

protected:
  Standard_EXPORT void bindTypes(StdObjMgt_MapOfInstantiators& theMap) override;
};
