#pragma once


#include <StdLDrivers_DocumentRetrievalDriver.hpp>

//! retrieval driver of a Part document
class StdDrivers_DocumentRetrievalDriver : public StdLDrivers_DocumentRetrievalDriver
{
public:
  DEFINE_STANDARD_RTTIEXT(StdDrivers_DocumentRetrievalDriver, StdLDrivers_DocumentRetrievalDriver)

protected:
  //! Register types.
  Standard_EXPORT void bindTypes(StdObjMgt_MapOfInstantiators& theMap) override;
};

