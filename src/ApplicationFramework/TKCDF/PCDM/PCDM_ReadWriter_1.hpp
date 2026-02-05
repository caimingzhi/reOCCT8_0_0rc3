#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <PCDM_ReadWriter.hpp>
#include <Standard_Integer.hpp>
#include <PCDM_Reference.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
class TCollection_AsciiString;
class Storage_Data;
class CDM_Document;
class TCollection_ExtendedString;
class Message_Messenger;

class PCDM_ReadWriter_1 : public PCDM_ReadWriter
{

public:
  Standard_EXPORT PCDM_ReadWriter_1();

  //! returns PCDM_ReadWriter_1.
  Standard_EXPORT TCollection_AsciiString Version() const override;

  Standard_EXPORT void WriteReferenceCounter(
    const occ::handle<Storage_Data>& aData,
    const occ::handle<CDM_Document>& aDocument) const override;

  Standard_EXPORT void WriteReferences(
    const occ::handle<Storage_Data>&  aData,
    const occ::handle<CDM_Document>&  aDocument,
    const TCollection_ExtendedString& theReferencerFileName) const override;

  Standard_EXPORT void WriteExtensions(const occ::handle<Storage_Data>& aData,
                                       const occ::handle<CDM_Document>& aDocument) const override;

  Standard_EXPORT void WriteVersion(const occ::handle<Storage_Data>& aData,
                                    const occ::handle<CDM_Document>& aDocument) const override;

  Standard_EXPORT int ReadReferenceCounter(
    const TCollection_ExtendedString&     aFileName,
    const occ::handle<Message_Messenger>& theMsgDriver) const override;

  Standard_EXPORT void ReadReferences(
    const TCollection_ExtendedString&     aFileName,
    NCollection_Sequence<PCDM_Reference>& theReferences,
    const occ::handle<Message_Messenger>& theMsgDriver) const override;

  Standard_EXPORT void ReadExtensions(
    const TCollection_ExtendedString&                 aFileName,
    NCollection_Sequence<TCollection_ExtendedString>& theExtensions,
    const occ::handle<Message_Messenger>&             theMsgDriver) const override;

  Standard_EXPORT int ReadDocumentVersion(
    const TCollection_ExtendedString&     aFileName,
    const occ::handle<Message_Messenger>& theMsgDriver) const override;

  DEFINE_STANDARD_RTTIEXT(PCDM_ReadWriter_1, PCDM_ReadWriter)

private:
  Standard_EXPORT static void ReadUserInfo(
    const TCollection_ExtendedString&                 aFileName,
    const TCollection_AsciiString&                    Start,
    const TCollection_AsciiString&                    End,
    NCollection_Sequence<TCollection_ExtendedString>& theUserInfo,
    const occ::handle<Message_Messenger>&             theMsgDriver);
};
