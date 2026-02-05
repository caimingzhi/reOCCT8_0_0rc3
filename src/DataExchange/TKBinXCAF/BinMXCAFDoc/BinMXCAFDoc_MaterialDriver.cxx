#include <BinMXCAFDoc_MaterialDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <XCAFDoc_Material.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_MaterialDriver, BinMDF_ADriver)

//=================================================================================================

BinMXCAFDoc_MaterialDriver::BinMXCAFDoc_MaterialDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_Material)->Name())
{
}

//=================================================================================================

occ::handle<TDF_Attribute> BinMXCAFDoc_MaterialDriver::NewEmpty() const
{
  return new XCAFDoc_Material();
}

//=================================================================================================

bool BinMXCAFDoc_MaterialDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       BinObjMgt_RRelocationTable& /*theRelocTable*/) const
{
  occ::handle<XCAFDoc_Material> anAtt = occ::down_cast<XCAFDoc_Material>(theTarget);
  double                        aDensity;
  TCollection_AsciiString       aName, aDescr, aDensName, aDensValType;
  if (!(theSource >> aName >> aDescr >> aDensity >> aDensName >> aDensValType))
    return false;

  anAtt->Set(new TCollection_HAsciiString(aName),
             new TCollection_HAsciiString(aDescr),
             aDensity,
             new TCollection_HAsciiString(aDensName),
             new TCollection_HAsciiString(aDensValType));
  return true;
}

static void pasteString(BinObjMgt_Persistent&                        theTarget,
                        const occ::handle<TCollection_HAsciiString>& theStr)
{
  if (!theStr.IsNull())
    theTarget << theStr->String();
  else
    theTarget << TCollection_AsciiString("");
}

//=================================================================================================

void BinMXCAFDoc_MaterialDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>& /*theRelocTable*/) const
{
  occ::handle<XCAFDoc_Material> anAtt = occ::down_cast<XCAFDoc_Material>(theSource);
  pasteString(theTarget, anAtt->GetName());
  pasteString(theTarget, anAtt->GetDescription());
  theTarget << anAtt->GetDensity();
  pasteString(theTarget, anAtt->GetDensName());
  pasteString(theTarget, anAtt->GetDensValType());
}
