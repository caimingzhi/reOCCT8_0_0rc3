#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <XmlObjMgt_RRelocationTable.hpp>
#include <TCollection_ExtendedString.hpp>
#include <PCDM_RetrievalDriver.hpp>
#include <XmlObjMgt_Element.hpp>
#include <Standard_Integer.hpp>
#include <Storage_Data.hpp>
class XmlMDF_ADriverTable;
class CDM_Document;
class CDM_Application;
class Message_Messenger;
class XmlMDF_ADriver;

class XmlLDrivers_DocumentRetrievalDriver : public PCDM_RetrievalDriver
{

public:
  Standard_EXPORT XmlLDrivers_DocumentRetrievalDriver();

  Standard_EXPORT void Read(
    const TCollection_ExtendedString&     theFileName,
    const occ::handle<CDM_Document>&      theNewDocument,
    const occ::handle<CDM_Application>&   theApplication,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange()) override;

  Standard_EXPORT void Read(
    Standard_IStream&                     theIStream,
    const occ::handle<Storage_Data>&      theStorageData,
    const occ::handle<CDM_Document>&      theDoc,
    const occ::handle<CDM_Application>&   theApplication,
    const occ::handle<PCDM_ReaderFilter>& theFilter = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theRange  = Message_ProgressRange()) override;

  Standard_EXPORT virtual occ::handle<XmlMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver);

  DEFINE_STANDARD_RTTIEXT(XmlLDrivers_DocumentRetrievalDriver, PCDM_RetrievalDriver)

protected:
  Standard_EXPORT virtual void ReadFromDomDocument(
    const XmlObjMgt_Element&            theDomElement,
    const occ::handle<CDM_Document>&    theNewDocument,
    const occ::handle<CDM_Application>& theApplication,
    const Message_ProgressRange&        theRange = Message_ProgressRange());

  Standard_EXPORT virtual bool MakeDocument(
    const XmlObjMgt_Element&         thePDoc,
    const occ::handle<CDM_Document>& theTDoc,
    const Message_ProgressRange&     theRange = Message_ProgressRange());

  Standard_EXPORT virtual occ::handle<XmlMDF_ADriver> ReadShapeSection(
    const XmlObjMgt_Element&              thePDoc,
    const occ::handle<Message_Messenger>& theMsgDriver,
    const Message_ProgressRange&          theRange = Message_ProgressRange());

  Standard_EXPORT virtual void ShapeSetCleaning(const occ::handle<XmlMDF_ADriver>& theDriver);

  occ::handle<XmlMDF_ADriverTable> myDrivers;
  XmlObjMgt_RRelocationTable       myRelocTable;
  TCollection_ExtendedString       myFileName;
};
