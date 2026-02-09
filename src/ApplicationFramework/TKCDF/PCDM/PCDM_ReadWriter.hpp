#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <PCDM_Reference.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
#include <Storage_OpenMode.hpp>
class TCollection_AsciiString;
class Storage_Data;
class CDM_Document;
class TCollection_ExtendedString;
class Message_Messenger;
class Storage_BaseDriver;

class PCDM_ReadWriter : public Standard_Transient
{

public:
  Standard_EXPORT virtual TCollection_AsciiString Version() const = 0;

  Standard_EXPORT virtual void WriteReferenceCounter(
    const occ::handle<Storage_Data>& aData,
    const occ::handle<CDM_Document>& aDocument) const = 0;

  Standard_EXPORT virtual void WriteReferences(
    const occ::handle<Storage_Data>&  aData,
    const occ::handle<CDM_Document>&  aDocument,
    const TCollection_ExtendedString& theReferencerFileName) const = 0;

  Standard_EXPORT virtual void WriteExtensions(
    const occ::handle<Storage_Data>& aData,
    const occ::handle<CDM_Document>& aDocument) const = 0;

  Standard_EXPORT virtual void WriteVersion(const occ::handle<Storage_Data>& aData,
                                            const occ::handle<CDM_Document>& aDocument) const = 0;

  Standard_EXPORT virtual int ReadReferenceCounter(
    const TCollection_ExtendedString&     theFileName,
    const occ::handle<Message_Messenger>& theMsgDriver) const = 0;

  Standard_EXPORT virtual void ReadReferences(
    const TCollection_ExtendedString&     aFileName,
    NCollection_Sequence<PCDM_Reference>& theReferences,
    const occ::handle<Message_Messenger>& theMsgDriver) const = 0;

  Standard_EXPORT virtual void ReadExtensions(
    const TCollection_ExtendedString&                 aFileName,
    NCollection_Sequence<TCollection_ExtendedString>& theExtensions,
    const occ::handle<Message_Messenger>&             theMsgDriver) const = 0;

  Standard_EXPORT virtual int ReadDocumentVersion(
    const TCollection_ExtendedString&     aFileName,
    const occ::handle<Message_Messenger>& theMsgDriver) const = 0;

  Standard_EXPORT static void Open(const occ::handle<Storage_BaseDriver>& aDriver,
                                   const TCollection_ExtendedString&      aFileName,
                                   const Storage_OpenMode                 anOpenMode);

  Standard_EXPORT static occ::handle<PCDM_ReadWriter> Reader(
    const TCollection_ExtendedString& aFileName);

  Standard_EXPORT static occ::handle<PCDM_ReadWriter> Writer();

  Standard_EXPORT static void WriteFileFormat(const occ::handle<Storage_Data>& aData,
                                              const occ::handle<CDM_Document>& aDocument);

  Standard_EXPORT static TCollection_ExtendedString FileFormat(
    const TCollection_ExtendedString& aFileName);

  Standard_EXPORT static TCollection_ExtendedString FileFormat(Standard_IStream& theIStream,
                                                               occ::handle<Storage_Data>& theData);

  DEFINE_STANDARD_RTTIEXT(PCDM_ReadWriter, Standard_Transient)
};
