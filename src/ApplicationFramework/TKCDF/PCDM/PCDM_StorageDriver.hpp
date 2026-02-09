#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_ExtendedString.hpp>
#include <PCDM_StoreStatus.hpp>
#include <PCDM_Writer.hpp>
#include <PCDM_Document.hpp>
#include <NCollection_Sequence.hpp>
class PCDM_Document;
class CDM_Document;

class PCDM_StorageDriver : public PCDM_Writer
{

public:
  Standard_EXPORT virtual occ::handle<PCDM_Document> Make(
    const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT virtual void Make(const occ::handle<CDM_Document>&                  aDocument,
                                    NCollection_Sequence<occ::handle<PCDM_Document>>& Documents);

  Standard_EXPORT void Write(
    const occ::handle<CDM_Document>&  aDocument,
    const TCollection_ExtendedString& aFileName,
    const Message_ProgressRange&      theRange = Message_ProgressRange()) override;

  Standard_EXPORT void Write(
    const occ::handle<CDM_Document>& theDocument,
    Standard_OStream&                theOStream,
    const Message_ProgressRange&     theRange = Message_ProgressRange()) override;

  Standard_EXPORT void SetFormat(const TCollection_ExtendedString& aformat);

  Standard_EXPORT TCollection_ExtendedString GetFormat() const;

  Standard_EXPORT bool IsError() const;

  Standard_EXPORT void SetIsError(const bool theIsError);

  Standard_EXPORT PCDM_StoreStatus GetStoreStatus() const;

  Standard_EXPORT void SetStoreStatus(const PCDM_StoreStatus theStoreStatus);

  DEFINE_STANDARD_RTTIEXT(PCDM_StorageDriver, PCDM_Writer)

private:
  TCollection_ExtendedString myFormat;
  bool                       myIsError;
  PCDM_StoreStatus           myStoreStatus;
};
