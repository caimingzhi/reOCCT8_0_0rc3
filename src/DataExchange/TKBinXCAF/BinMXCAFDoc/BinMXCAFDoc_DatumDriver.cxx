#include <BinMXCAFDoc_DatumDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TDF_Attribute.hpp>
#include <XCAFDoc_Datum.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_DatumDriver, BinMDF_ADriver)

BinMXCAFDoc_DatumDriver::BinMXCAFDoc_DatumDriver(const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_Datum)->Name())
{
}

occ::handle<TDF_Attribute> BinMXCAFDoc_DatumDriver::NewEmpty() const
{
  return new XCAFDoc_Datum();
}

bool BinMXCAFDoc_DatumDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                    const occ::handle<TDF_Attribute>& theTarget,
                                    BinObjMgt_RRelocationTable&) const
{
  occ::handle<XCAFDoc_Datum> anAtt = occ::down_cast<XCAFDoc_Datum>(theTarget);
  TCollection_AsciiString    aName, aDescr, anId;
  if (!(theSource >> aName >> aDescr >> anId))
    return false;

  anAtt->Set(new TCollection_HAsciiString(aName),
             new TCollection_HAsciiString(aDescr),
             new TCollection_HAsciiString(anId));
  return true;
}

void BinMXCAFDoc_DatumDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                    BinObjMgt_Persistent&             theTarget,
                                    NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<XCAFDoc_Datum> anAtt = occ::down_cast<XCAFDoc_Datum>(theSource);
  if (!anAtt->GetName().IsNull())
    theTarget << anAtt->GetName()->String();
  else
    theTarget << TCollection_AsciiString("");

  if (!anAtt->GetDescription().IsNull())
    theTarget << anAtt->GetDescription()->String();
  else
    theTarget << TCollection_AsciiString("");

  if (!anAtt->GetIdentification().IsNull())
    theTarget << anAtt->GetIdentification()->String();
  else
    theTarget << TCollection_AsciiString("");
}
