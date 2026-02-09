#pragma once

#include <Standard_Type.hpp>

class CDM_MetaData;
class TCollection_ExtendedString;
class CDM_Document;
class PCDM_ReferenceIterator;
class Message_Messenger;

class CDF_MetaDataDriver : public Standard_Transient
{

public:
  Standard_EXPORT virtual bool HasVersionCapability();

  Standard_EXPORT virtual void CreateDependsOn(const occ::handle<CDM_MetaData>& aFirstData,
                                               const occ::handle<CDM_MetaData>& aSecondData);

  Standard_EXPORT virtual void CreateReference(const occ::handle<CDM_MetaData>& aFrom,
                                               const occ::handle<CDM_MetaData>& aTo,
                                               const int aReferenceIdentifier,
                                               const int aToDocumentVersion);

  Standard_EXPORT virtual bool HasVersion(const TCollection_ExtendedString& aFolder,
                                          const TCollection_ExtendedString& aName);

  Standard_EXPORT virtual TCollection_ExtendedString BuildFileName(
    const occ::handle<CDM_Document>& aDocument) = 0;

  Standard_EXPORT virtual TCollection_ExtendedString SetName(
    const occ::handle<CDM_Document>&  aDocument,
    const TCollection_ExtendedString& aName);

  Standard_EXPORT virtual bool Find(const TCollection_ExtendedString& aFolder,
                                    const TCollection_ExtendedString& aName,
                                    const TCollection_ExtendedString& aVersion) = 0;

  Standard_EXPORT virtual bool HasReadPermission(const TCollection_ExtendedString& aFolder,
                                                 const TCollection_ExtendedString& aName,
                                                 const TCollection_ExtendedString& aVersion) = 0;

  Standard_EXPORT virtual occ::handle<CDM_MetaData> MetaData(
    const TCollection_ExtendedString& aFolder,
    const TCollection_ExtendedString& aName,
    const TCollection_ExtendedString& aVersion) = 0;

  Standard_EXPORT virtual occ::handle<CDM_MetaData> LastVersion(
    const occ::handle<CDM_MetaData>& aMetaData);

  Standard_EXPORT virtual occ::handle<CDM_MetaData> CreateMetaData(
    const occ::handle<CDM_Document>&  aDocument,
    const TCollection_ExtendedString& aFileName) = 0;

  Standard_EXPORT virtual bool FindFolder(const TCollection_ExtendedString& aFolder) = 0;

  Standard_EXPORT virtual TCollection_ExtendedString DefaultFolder() = 0;

  Standard_EXPORT virtual occ::handle<PCDM_ReferenceIterator> ReferenceIterator(
    const occ::handle<Message_Messenger>& theMessageDriver);

  Standard_EXPORT bool Find(const TCollection_ExtendedString& aFolder,
                            const TCollection_ExtendedString& aName);

  Standard_EXPORT occ::handle<CDM_MetaData> MetaData(const TCollection_ExtendedString& aFolder,
                                                     const TCollection_ExtendedString& aName);

  DEFINE_STANDARD_RTTIEXT(CDF_MetaDataDriver, Standard_Transient)

protected:
  Standard_EXPORT CDF_MetaDataDriver();
};
