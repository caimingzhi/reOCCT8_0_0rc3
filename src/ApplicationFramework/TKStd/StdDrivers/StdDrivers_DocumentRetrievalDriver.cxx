

#include <StdDrivers_DocumentRetrievalDriver.hpp>
#include <StdDrivers.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StdDrivers_DocumentRetrievalDriver, StdLDrivers_DocumentRetrievalDriver)

void StdDrivers_DocumentRetrievalDriver::bindTypes(StdObjMgt_MapOfInstantiators& theMap)
{
  StdDrivers::BindTypes(theMap);
}
