#include <StdDrivers.hpp>
#include <StdDrivers_DocumentRetrievalDriver.hpp>

#include <StdLPersistent.hpp>
#include <StdPersistent.hpp>
#include <ShapePersistent.hpp>

#include <Standard_Failure.hpp>
#include <Standard_GUID.hpp>
#include <Plugin_Macro.hpp>

#include <PCDM_StorageDriver.hpp>
#include <TDocStd_Application.hpp>

static Standard_GUID StdRetrievalDriver("ad696001-5b34-11d1-b5ba-00a0c9064368");

occ::handle<Standard_Transient> StdDrivers::Factory(const Standard_GUID& aGUID)
{
  if (aGUID == StdRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "StdDrivers : Retrieval Plugin" << std::endl;
#endif

    static occ::handle<StdDrivers_DocumentRetrievalDriver> model_rd =
      new StdDrivers_DocumentRetrievalDriver;
    return model_rd;
  }

  throw Standard_Failure("StdDrivers : unknown GUID");
}

void StdDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat("MDTV-Standard",
                       "Standard OCAF Document",
                       "std",
                       new StdDrivers_DocumentRetrievalDriver,
                       nullptr);
}

void StdDrivers::BindTypes(StdObjMgt_MapOfInstantiators& theMap)
{
  StdLPersistent ::BindTypes(theMap);
  StdPersistent ::BindTypes(theMap);
  ShapePersistent::BindTypes(theMap);
}

PLUGIN(StdDrivers)
