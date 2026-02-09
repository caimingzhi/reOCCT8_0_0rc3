#pragma once

#include <XCAFDoc_Note.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>

class OSD_File;

class XCAFDoc_NoteBinData : public XCAFDoc_Note
{
public:
  DEFINE_STANDARD_RTTIEXT(XCAFDoc_NoteBinData, XCAFDoc_Note)

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_NoteBinData> Get(const TDF_Label& theLabel);

  Standard_EXPORT static occ::handle<XCAFDoc_NoteBinData> Set(
    const TDF_Label&                  theLabel,
    const TCollection_ExtendedString& theUserName,
    const TCollection_ExtendedString& theTimeStamp,
    const TCollection_ExtendedString& theTitle,
    const TCollection_AsciiString&    theMIMEtype,
    OSD_File&                         theFile);

  Standard_EXPORT static occ::handle<XCAFDoc_NoteBinData> Set(
    const TDF_Label&                                 theLabel,
    const TCollection_ExtendedString&                theUserName,
    const TCollection_ExtendedString&                theTimeStamp,
    const TCollection_ExtendedString&                theTitle,
    const TCollection_AsciiString&                   theMIMEtype,
    const occ::handle<NCollection_HArray1<uint8_t>>& theData);

  Standard_EXPORT XCAFDoc_NoteBinData();

  Standard_EXPORT bool Set(const TCollection_ExtendedString& theTitle,
                           const TCollection_AsciiString&    theMIMEtype,
                           OSD_File&                         theFile);

  Standard_EXPORT void Set(const TCollection_ExtendedString&                theTitle,
                           const TCollection_AsciiString&                   theMIMEtype,
                           const occ::handle<NCollection_HArray1<uint8_t>>& theData);

  const TCollection_ExtendedString& Title() const { return myTitle; }

  const TCollection_AsciiString& MIMEtype() const { return myMIMEtype; }

  int Size() const { return (!myData.IsNull() ? myData->Length() : 0); }

  const occ::handle<NCollection_HArray1<uint8_t>>& Data() const { return myData; }

public:
  Standard_EXPORT const Standard_GUID& ID() const override;
  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;
  Standard_EXPORT void              Restore(const occ::handle<TDF_Attribute>& theAttrFrom) override;
  Standard_EXPORT void              Paste(const occ::handle<TDF_Attribute>&       theAttrInto,
                                          const occ::handle<TDF_RelocationTable>& theRT) const override;
  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theOS) const override;

protected:
  TCollection_ExtendedString                myTitle;
  TCollection_AsciiString                   myMIMEtype;
  occ::handle<NCollection_HArray1<uint8_t>> myData;
};
