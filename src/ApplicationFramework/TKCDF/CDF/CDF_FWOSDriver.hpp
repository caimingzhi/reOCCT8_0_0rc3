#pragma once


#include <Standard.hpp>

#include <CDF_MetaDataDriver.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_DataMap.hpp>

class TCollection_ExtendedString;
class CDM_MetaData;
class CDM_Document;

class CDF_FWOSDriver : public CDF_MetaDataDriver
{

public:
  //! Initializes the MetaDatadriver connected to specified look-up table.
  //! Note that the created driver will keep reference to the table,
  //! thus it must have life time longer than this object.
  Standard_EXPORT CDF_FWOSDriver(
    NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>& theLookUpTable);

  //! indicate whether a file exists corresponding to the folder and the name
  Standard_EXPORT bool Find(const TCollection_ExtendedString& aFolder,
                            const TCollection_ExtendedString& aName,
                            const TCollection_ExtendedString& aVersion) override;

  Standard_EXPORT bool HasReadPermission(const TCollection_ExtendedString& aFolder,
                                         const TCollection_ExtendedString& aName,
                                         const TCollection_ExtendedString& aVersion) override;

  Standard_EXPORT bool FindFolder(const TCollection_ExtendedString& aFolder) override;

  Standard_EXPORT TCollection_ExtendedString DefaultFolder() override;

  Standard_EXPORT TCollection_ExtendedString
    BuildFileName(const occ::handle<CDM_Document>& aDocument) override;

  Standard_EXPORT TCollection_ExtendedString
    SetName(const occ::handle<CDM_Document>&  aDocument,
            const TCollection_ExtendedString& aName) override;

  DEFINE_STANDARD_RTTIEXT(CDF_FWOSDriver, CDF_MetaDataDriver)

private:
  Standard_EXPORT occ::handle<CDM_MetaData> MetaData(
    const TCollection_ExtendedString& aFolder,
    const TCollection_ExtendedString& aName,
    const TCollection_ExtendedString& aVersion) override;

  Standard_EXPORT occ::handle<CDM_MetaData> CreateMetaData(
    const occ::handle<CDM_Document>&  aDocument,
    const TCollection_ExtendedString& aFileName) override;

  Standard_EXPORT static TCollection_ExtendedString Concatenate(
    const TCollection_ExtendedString& aFolder,
    const TCollection_ExtendedString& aName);

private:
  NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>* myLookUpTable;
};

