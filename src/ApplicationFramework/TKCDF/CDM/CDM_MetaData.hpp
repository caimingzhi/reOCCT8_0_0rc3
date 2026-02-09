#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <CDM_DocumentPointer.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <CDM_Document.hpp>
#include <CDM_Application.hpp>
#include <Standard_OStream.hpp>
#include <NCollection_DataMap.hpp>
class CDM_MetaData;

class CDM_MetaData : public Standard_Transient
{

public:
  Standard_EXPORT static occ::handle<CDM_MetaData> LookUp(
    NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>& theLookUpTable,
    const TCollection_ExtendedString&                                           aFolder,
    const TCollection_ExtendedString&                                           aName,
    const TCollection_ExtendedString&                                           aPath,
    const TCollection_ExtendedString&                                           aFileName,
    const bool                                                                  ReadOnly);

  Standard_EXPORT static occ::handle<CDM_MetaData> LookUp(
    NCollection_DataMap<TCollection_ExtendedString, occ::handle<CDM_MetaData>>& theLookUpTable,
    const TCollection_ExtendedString&                                           aFolder,
    const TCollection_ExtendedString&                                           aName,
    const TCollection_ExtendedString&                                           aPath,
    const TCollection_ExtendedString&                                           aVersion,
    const TCollection_ExtendedString&                                           aFileName,
    const bool                                                                  ReadOnly);

  Standard_EXPORT bool IsRetrieved() const;

  Standard_EXPORT occ::handle<CDM_Document> Document() const;

  Standard_EXPORT TCollection_ExtendedString Folder() const;

  Standard_EXPORT TCollection_ExtendedString Name() const;

  Standard_EXPORT TCollection_ExtendedString Version() const;

  Standard_EXPORT bool HasVersion() const;

  Standard_EXPORT TCollection_ExtendedString FileName() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;
  Standard_OStream&                 operator<<(Standard_OStream& anOStream);

  Standard_EXPORT TCollection_ExtendedString Path() const;

  Standard_EXPORT void UnsetDocument();

  Standard_EXPORT bool IsReadOnly() const;

  Standard_EXPORT void SetIsReadOnly();

  Standard_EXPORT void UnsetIsReadOnly();

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  friend class CDM_Reference;
  friend

    Standard_EXPORT void
                              CDM_Document::SetMetaData(const occ::handle<CDM_MetaData>& aMetaData);
  friend Standard_EXPORT void CDM_Application::SetDocumentVersion(
    const occ::handle<CDM_Document>& aDocument,
    const occ::handle<CDM_MetaData>& aMetaData) const;

  DEFINE_STANDARD_RTTIEXT(CDM_MetaData, Standard_Transient)

private:
  CDM_MetaData(const TCollection_ExtendedString& aFolder,
               const TCollection_ExtendedString& aName,
               const TCollection_ExtendedString& aPath,
               const TCollection_ExtendedString& aFileName,
               const bool                        ReadOnly);

  CDM_MetaData(const TCollection_ExtendedString& aFolder,
               const TCollection_ExtendedString& aName,
               const TCollection_ExtendedString& aPath,
               const TCollection_ExtendedString& aVersion,
               const TCollection_ExtendedString& aFileName,
               const bool                        ReadOnly);

  void SetDocument(const occ::handle<CDM_Document>& aDocument);

  int DocumentVersion(const occ::handle<CDM_Application>& anApplication);

private:
  bool                       myIsRetrieved;
  CDM_DocumentPointer        myDocument;
  TCollection_ExtendedString myFolder;
  TCollection_ExtendedString myName;
  TCollection_ExtendedString myVersion;
  bool                       myHasVersion;
  TCollection_ExtendedString myFileName;
  TCollection_ExtendedString myPath;
  int                        myDocumentVersion;
  bool                       myIsReadOnly;
};
