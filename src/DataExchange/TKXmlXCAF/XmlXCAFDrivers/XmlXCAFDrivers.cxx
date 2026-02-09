#include <Plugin_Macro.hpp>
#include <Standard_Failure.hpp>
#include <Standard_GUID.hpp>
#include <TDocStd_Application.hpp>
#include <XmlDrivers.hpp>
#include <XmlXCAFDrivers.hpp>
#include <XmlXCAFDrivers_DocumentRetrievalDriver.hpp>
#include <XmlXCAFDrivers_DocumentStorageDriver.hpp>

static Standard_GUID XSStorageDriver("f78ff496-a779-11d5-aab4-0050044b1af1");
static Standard_GUID XSRetrievalDriver("f78ff497-a779-11d5-aab4-0050044b1af1");

const occ::handle<Standard_Transient>& XmlXCAFDrivers::Factory(const Standard_GUID& aGUID)
{
  if (aGUID == XSStorageDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "XmlXCAFDrivers : Storage Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_sd =
      new XmlXCAFDrivers_DocumentStorageDriver("Copyright: Open Cascade, 2001-2002");
    return model_sd;
  }
  if (aGUID == XSRetrievalDriver)
  {
#ifdef OCCT_DEBUG
    std::cout << "XmlXCAFDrivers : Retrieval Plugin" << std::endl;
#endif
    static occ::handle<Standard_Transient> model_rd = new XmlXCAFDrivers_DocumentRetrievalDriver;
    return model_rd;
  }

  return XmlDrivers::Factory(aGUID);
}

void XmlXCAFDrivers::DefineFormat(const occ::handle<TDocStd_Application>& theApp)
{
  theApp->DefineFormat(
    "XmlXCAF",
    "Xml XCAF Document",
    "xml",
    new XmlXCAFDrivers_DocumentRetrievalDriver,
    new XmlXCAFDrivers_DocumentStorageDriver("Copyright: Open Cascade, 2001-2002"));
}

PLUGIN(XmlXCAFDrivers)
