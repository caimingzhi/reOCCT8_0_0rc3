#pragma once

#include <Standard.hpp>

#include <BinObjMgt_Persistent.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Vector.hpp>
#include <BinLDrivers_DocumentSection.hpp>
#include <PCDM_StorageDriver.hpp>
#include <Standard_OStream.hpp>
#include <Standard_Type.hpp>
#include <TDocStd_FormatVersion.hpp>
class BinMDF_ADriverTable;
class Message_Messenger;
class CDM_Document;
class TDF_Label;
class TCollection_AsciiString;
class BinLDrivers_DocumentSection;
class BinObjMgt_Position;

class BinLDrivers_DocumentStorageDriver : public PCDM_StorageDriver
{

public:
  Standard_EXPORT BinLDrivers_DocumentStorageDriver();

  Standard_EXPORT void Write(
    const occ::handle<CDM_Document>&  theDocument,
    const TCollection_ExtendedString& theFileName,
    const Message_ProgressRange&      theRange = Message_ProgressRange()) override;

  Standard_EXPORT void Write(
    const occ::handle<CDM_Document>& theDocument,
    Standard_OStream&                theOStream,
    const Message_ProgressRange&     theRange = Message_ProgressRange()) override;

  Standard_EXPORT virtual occ::handle<BinMDF_ADriverTable> AttributeDrivers(
    const occ::handle<Message_Messenger>& theMsgDriver);

  Standard_EXPORT void AddSection(const TCollection_AsciiString& theName,
                                  const bool                     isPostRead = true);

  Standard_EXPORT bool IsQuickPart(const int theVersion) const;

  DEFINE_STANDARD_RTTIEXT(BinLDrivers_DocumentStorageDriver, PCDM_StorageDriver)

protected:
  Standard_EXPORT void WriteSubTree(
    const TDF_Label&             theData,
    Standard_OStream&            theOS,
    const bool&                  theQuickPart,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT virtual void WriteSection(const TCollection_AsciiString&,
                                            const occ::handle<CDM_Document>&,
                                            Standard_OStream&);

  Standard_EXPORT virtual void WriteShapeSection(
    BinLDrivers_DocumentSection& theDocSection,
    Standard_OStream&            theOS,
    const TDocStd_FormatVersion  theDocVer,
    const Message_ProgressRange& theRange = Message_ProgressRange());

  Standard_EXPORT virtual void EnableQuickPartWriting(const occ::handle<Message_Messenger>&,
                                                      const bool)
  {
  }

  Standard_EXPORT virtual void Clear();

  occ::handle<BinMDF_ADriverTable>                        myDrivers;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myRelocTable;
  occ::handle<Message_Messenger>                          myMsgDriver;

private:
  Standard_EXPORT void FirstPass(const TDF_Label& theRoot);

  Standard_EXPORT bool FirstPassSubTree(const TDF_Label&             L,
                                        NCollection_List<TDF_Label>& ListOfEmptyL);

  Standard_EXPORT void WriteInfoSection(const occ::handle<CDM_Document>& theDocument,
                                        Standard_OStream&                theOStream);

  Standard_EXPORT void UnsupportedAttrMsg(const occ::handle<Standard_Type>& theType);

  Standard_EXPORT void WriteSizes(Standard_OStream& theOS);

  BinObjMgt_Persistent                                    myPAtt;
  NCollection_List<TDF_Label>                             myEmptyLabels;
  NCollection_Map<occ::handle<Standard_Transient>>        myMapUnsupported;
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myTypesMap;
  NCollection_Vector<BinLDrivers_DocumentSection>         mySections;
  TCollection_ExtendedString                              myFileName;

  NCollection_List<occ::handle<BinObjMgt_Position>> mySizesToWrite;
};
