#pragma once

#include <Standard.hpp>

#include <BinObjMgt_Persistent.hpp>
#include <BinObjMgt_RRelocationTable.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Vector.hpp>
#include <BinLDrivers_DocumentSection.hpp>
#include <PCDM_RetrievalDriver.hpp>
#include <Standard_IStream.hpp>
#include <Storage_Position.hpp>
#include <Storage_Data.hpp>

class BinMDF_ADriverTable;
class Message_Messenger;
class TCollection_ExtendedString;
class CDM_Document;
class CDM_Application;
class TDF_Label;
class BinLDrivers_DocumentSection;

class BinLDrivers_DocumentRetrievalDriver : public PCDM_RetrievalDriver
{

public:
  Standard_EXPORT BinLDrivers_DocumentRetrievalDriver();

  Standard_EXPORT void Read(
    const TCollection_ExtendedString&     theFileName,
    const occ::handle<CDM_Document>&      theNewDocument,
    const occ::handle<CDM_Application>&   theApplication,
    const occ::handle<PCDM_ReaderFilter>& theFilter   = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theProgress = Message_ProgressRange()) override;

  Standard_EXPORT void Read(
    Standard_IStream&                     theIStream,
    const occ::handle<Storage_Data>&      theStorageData,
    const occ::handle<CDM_Document>&      theDoc,
    const occ::handle<CDM_Application>&   theApplication,
    const occ::handle<PCDM_ReaderFilter>& theFilter   = occ::handle<PCDM_ReaderFilter>(),
    const Message_ProgressRange&          theProgress = Message_ProgressRange()) override;

  Standard_EXPORT virtual occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver);

  DEFINE_STANDARD_RTTIEXT(BinLDrivers_DocumentRetrievalDriver, PCDM_RetrievalDriver)

protected:
  Standard_EXPORT virtual int ReadSubTree(
    Standard_IStream&                     theIS,
    const TDF_Label&                      theData,
    const occ::handle<PCDM_ReaderFilter>& theFilter,
    const bool&                           theQuickPart,
    const bool                            theReadMissing,
    const Message_ProgressRange&          theRanges = Message_ProgressRange());

  Standard_EXPORT virtual void ReadSection(BinLDrivers_DocumentSection&     theSection,
                                           const occ::handle<CDM_Document>& theDoc,
                                           Standard_IStream&                theIS);

  Standard_EXPORT virtual void ReadShapeSection(
    BinLDrivers_DocumentSection& theSection,
    Standard_IStream&            theIS,
    const bool                   isMess   = false,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT virtual void CheckShapeSection(const Storage_Position& thePos,
                                                 Standard_IStream&       theIS);

  Standard_EXPORT virtual void Clear();

  Standard_EXPORT virtual bool CheckDocumentVersion(const int theFileVersion,
                                                    const int theCurVersion);

  static bool IsQuickPart(const int theFileVer);

  Standard_EXPORT virtual void EnableQuickPartReading(const occ::handle<Message_Messenger>&, bool)
  {
  }

  occ::handle<BinMDF_ADriverTable> myDrivers;
  BinObjMgt_RRelocationTable       myRelocTable;
  occ::handle<Message_Messenger>   myMsgDriver;

private:
  BinObjMgt_Persistent                            myPAtt;
  NCollection_Map<int>                            myMapUnsupported;
  NCollection_Vector<BinLDrivers_DocumentSection> mySections;
  NCollection_Map<int>                            myUnresolvedLinks;
};
