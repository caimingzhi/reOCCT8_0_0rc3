#include <CDF_Application.hpp>
#include <CDF_MetaDataDriver.hpp>
#include <CDM_MetaData.hpp>
#include <PCDM_ReferenceIterator.hpp>
#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>
#include <OSD_Thread.hpp>

IMPLEMENT_STANDARD_RTTIEXT(CDF_MetaDataDriver, Standard_Transient)

CDF_MetaDataDriver::CDF_MetaDataDriver() = default;

bool CDF_MetaDataDriver::HasVersion(const TCollection_ExtendedString&,
                                    const TCollection_ExtendedString&)
{
  return true;
}

bool CDF_MetaDataDriver::HasVersionCapability()
{
  return false;
}

void CDF_MetaDataDriver::CreateDependsOn(const occ::handle<CDM_MetaData>&,
                                         const occ::handle<CDM_MetaData>&)
{
}

void CDF_MetaDataDriver::CreateReference(const occ::handle<CDM_MetaData>&,
                                         const occ::handle<CDM_MetaData>&,
                                         const int,
                                         const int)
{
}

occ::handle<PCDM_ReferenceIterator> CDF_MetaDataDriver::ReferenceIterator(
  const occ::handle<Message_Messenger>& theMessageDriver)
{
  return new PCDM_ReferenceIterator(theMessageDriver);
}

bool CDF_MetaDataDriver::Find(const TCollection_ExtendedString& aFolder,
                              const TCollection_ExtendedString& aName)
{
  TCollection_ExtendedString aVersion;
  return Find(aFolder, aName, aVersion);
}

occ::handle<CDM_MetaData> CDF_MetaDataDriver::MetaData(const TCollection_ExtendedString& aFolder,
                                                       const TCollection_ExtendedString& aName)
{
  TCollection_ExtendedString aVersion;
  return MetaData(aFolder, aName, aVersion);
}

occ::handle<CDM_MetaData> CDF_MetaDataDriver::LastVersion(
  const occ::handle<CDM_MetaData>& aMetaData)
{
  return aMetaData;
}

TCollection_ExtendedString CDF_MetaDataDriver::SetName(const occ::handle<CDM_Document>&,
                                                       const TCollection_ExtendedString& aName)
{
  return aName;
}
