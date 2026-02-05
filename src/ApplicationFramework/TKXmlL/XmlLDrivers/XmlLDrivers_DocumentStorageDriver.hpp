#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XmlLDrivers_NamespaceDef.hpp>
#include <NCollection_Sequence.hpp>
#include <TCollection_ExtendedString.hpp>
#include <XmlObjMgt_SRelocationTable.hpp>
#include <PCDM_StorageDriver.hpp>
#include <XmlObjMgt_Element.hpp>
#include <Standard_Integer.hpp>
#include <TDocStd_FormatVersion.hpp>

class XmlMDF_ADriverTable;
class CDM_Document;
class TCollection_AsciiString;
class Message_Messenger;

class XmlLDrivers_DocumentStorageDriver : public PCDM_StorageDriver
{

public:
  Standard_EXPORT XmlLDrivers_DocumentStorageDriver(const TCollection_ExtendedString& theCopyright);

  Standard_EXPORT void Write(
    const occ::handle<CDM_Document>&  theDocument,
    const TCollection_ExtendedString& theFileName,
    const Message_ProgressRange&      theRange = Message_ProgressRange()) override;

  Standard_EXPORT void Write(
    const occ::handle<CDM_Document>& theDocument,
    Standard_OStream&                theOStream,
    const Message_ProgressRange&     theRange = Message_ProgressRange()) override;

  Standard_EXPORT virtual occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver);

  DEFINE_STANDARD_RTTIEXT(XmlLDrivers_DocumentStorageDriver, PCDM_StorageDriver)

protected:
  Standard_EXPORT virtual bool WriteToDomDocument(
    const occ::handle<CDM_Document>& theDocument,
    XmlObjMgt_Element&               thePDoc,
    const Message_ProgressRange&     theRange = Message_ProgressRange());

  Standard_EXPORT virtual int MakeDocument(
    const occ::handle<CDM_Document>& theDocument,
    XmlObjMgt_Element&               thePDoc,
    const Message_ProgressRange&     theRange = Message_ProgressRange());

  Standard_EXPORT void AddNamespace(const TCollection_AsciiString& thePrefix,
                                    const TCollection_AsciiString& theURI);

  Standard_EXPORT virtual bool WriteShapeSection(
    XmlObjMgt_Element&           thePDoc,
    const TDocStd_FormatVersion  theStorageFormatVersion,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  occ::handle<XmlMDF_ADriverTable> myDrivers;
  XmlObjMgt_SRelocationTable       myRelocTable;

private:
  NCollection_Sequence<XmlLDrivers_NamespaceDef> mySeqOfNS;
  TCollection_ExtendedString                     myCopyright;
  TCollection_ExtendedString                     myFileName;
};
