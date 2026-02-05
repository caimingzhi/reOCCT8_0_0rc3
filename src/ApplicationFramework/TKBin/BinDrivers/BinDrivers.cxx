#include <BinDrivers.hpp>
#include <BinDrivers_DocumentRetrievalDriver.hpp>
#include <BinDrivers_DocumentStorageDriver.hpp>
#include <BinLDrivers.hpp>
#include <BinMDataStd.hpp>
#include <BinMDataXtd.hpp>
#include <BinMDF.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinMDocStd.hpp>
#include <BinMFunction.hpp>
#include <BinMNaming.hpp>
#include <Plugin_Macro.hpp>
#include <Standard_Failure.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Transient.hpp>
#include <TDocStd_Application.hpp>

static Standard_GUID BinStorageDriver("03a56835-8269-11d5-aab2-0050044b1af1");
static Standard_GUID BinRetrievalDriver("03a56836-8269-11d5-aab2-0050044b1af1");

//=================================================================================================

const occ::handle<Standard_Transient>& BinDrivers::Factory(const Standard_GUID& theGUID)
{
  if (theGUID == BinStorageDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "BinDrivers : Storage Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_sd = new BinDrivers_DocumentStorageDriver;
    return model_sd;
  }

  if (theGUID == BinRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "BinDrivers : Retrieval Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_rd = new BinDrivers_DocumentRetrievalDriver;
    return model_rd;
  }

  throw Standard_Failure("BinDrivers : unknown GUID");
}

//=================================================================================================

void BinDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat("BinOcaf",
                       "Binary OCAF Document",
                       "cbf",
                       new BinDrivers_DocumentRetrievalDriver,
                       new BinDrivers_DocumentStorageDriver);
}

//=================================================================================================

occ::handle<BinMDF_ADriverTable> BinDrivers::AttributeDrivers(
  const occ::handle<Message_Messenger>& aMsgDrv)
{
  occ::handle<BinMDF_ADriverTable> aTable = new BinMDF_ADriverTable;

  BinMDF ::AddDrivers(aTable, aMsgDrv);
  BinMDataStd ::AddDrivers(aTable, aMsgDrv);
  BinMDataXtd ::AddDrivers(aTable, aMsgDrv);
  BinMNaming ::AddDrivers(aTable, aMsgDrv);
  BinMDocStd ::AddDrivers(aTable, aMsgDrv);
  BinMFunction ::AddDrivers(aTable, aMsgDrv);
  return aTable;
}

PLUGIN(BinDrivers)
