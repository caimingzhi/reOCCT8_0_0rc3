#include <BinLDrivers.hpp>
#include <BinTObjDrivers.hpp>
#include <BinTObjDrivers_DocumentStorageDriver.hpp>
#include <BinTObjDrivers_DocumentRetrievalDriver.hpp>
#include <BinTObjDrivers_IntSparseArrayDriver.hpp>
#include <BinTObjDrivers_ModelDriver.hpp>
#include <BinTObjDrivers_ObjectDriver.hpp>
#include <BinTObjDrivers_ReferenceDriver.hpp>
#include <BinTObjDrivers_XYZDriver.hpp>
#include <Plugin_Macro.hpp>
#include <TDocStd_Application.hpp>

static Standard_GUID BinStorageDriver("f78ff4a2-a779-11d5-aab4-0050044b1af1");
static Standard_GUID BinRetrievalDriver("f78ff4a3-a779-11d5-aab4-0050044b1af1");

const occ::handle<Standard_Transient>& BinTObjDrivers::Factory(const Standard_GUID& aGUID)
{
  if (aGUID == BinStorageDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "BinTObjDrivers : Storage Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_sd = new BinTObjDrivers_DocumentStorageDriver;
    return model_sd;
  }

  if (aGUID == BinRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "BinTObjDrivers : Retrieval Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_rd = new BinTObjDrivers_DocumentRetrievalDriver;
    return model_rd;
  }

  return BinLDrivers::Factory(aGUID);
}

//=================================================================================================

void BinTObjDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat("TObjBin",
                       "Binary TObj OCAF Document",
                       "cbf",
                       new BinTObjDrivers_DocumentRetrievalDriver,
                       new BinTObjDrivers_DocumentStorageDriver);
}

//=================================================================================================

void BinTObjDrivers::AddDrivers(const occ::handle<BinMDF_ADriverTable>& aDriverTable,
                                const occ::handle<Message_Messenger>&   aMsgDrv)
{
  aDriverTable->AddDriver(new BinTObjDrivers_ModelDriver(aMsgDrv));
  aDriverTable->AddDriver(new BinTObjDrivers_ObjectDriver(aMsgDrv));
  aDriverTable->AddDriver(new BinTObjDrivers_ReferenceDriver(aMsgDrv));
  aDriverTable->AddDriver(new BinTObjDrivers_XYZDriver(aMsgDrv));
  aDriverTable->AddDriver(new BinTObjDrivers_IntSparseArrayDriver(aMsgDrv));
}

PLUGIN(BinTObjDrivers)
