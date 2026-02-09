#include <BinDrivers.hpp>
#include <BinMDF_ADriverTable.hpp>
#include <BinMXCAFDoc.hpp>
#include <BinXCAFDrivers.hpp>
#include <BinXCAFDrivers_DocumentRetrievalDriver.hpp>
#include <BinXCAFDrivers_DocumentStorageDriver.hpp>
#include <Plugin_Macro.hpp>
#include <Standard_Failure.hpp>
#include <Standard_GUID.hpp>
#include <TDocStd_Application.hpp>

static Standard_GUID BinXCAFStorageDriver("a78ff496-a779-11d5-aab4-0050044b1af1");
static Standard_GUID BinXCAFRetrievalDriver("a78ff497-a779-11d5-aab4-0050044b1af1");

const occ::handle<Standard_Transient>& BinXCAFDrivers::Factory(const Standard_GUID& theGUID)
{

  if (theGUID == BinXCAFStorageDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "BinXCAFDrivers : Storage Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_sd = new BinXCAFDrivers_DocumentStorageDriver;
    return model_sd;
  }

  if (theGUID == BinXCAFRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "BinXCAFDrivers : Retrieval Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_rd = new BinXCAFDrivers_DocumentRetrievalDriver;
    return model_rd;
  }

  throw Standard_Failure("XCAFBinDrivers : unknown GUID");
}

void BinXCAFDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat("BinXCAF",
                       "Binary XCAF Document",
                       "xbf",
                       new BinXCAFDrivers_DocumentRetrievalDriver,
                       new BinXCAFDrivers_DocumentStorageDriver);
}

occ::handle<BinMDF_ADriverTable> BinXCAFDrivers::AttributeDrivers(
  const occ::handle<Message_Messenger>& aMsgDrv)
{

  occ::handle<BinMDF_ADriverTable> aTable = BinDrivers::AttributeDrivers(aMsgDrv);

  BinMXCAFDoc::AddDrivers(aTable, aMsgDrv);

  return aTable;
}

PLUGIN(BinXCAFDrivers)
