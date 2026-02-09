#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <BinMXCAFDoc_AssemblyItemRefDriver.hpp>
#include <XCAFDoc_AssemblyItemRef.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMXCAFDoc_AssemblyItemRefDriver, BinMDF_ADriver)

BinMXCAFDoc_AssemblyItemRefDriver::BinMXCAFDoc_AssemblyItemRefDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(XCAFDoc_AssemblyItemRef)->Name())
{
}

occ::handle<TDF_Attribute> BinMXCAFDoc_AssemblyItemRefDriver::NewEmpty() const
{
  return new XCAFDoc_AssemblyItemRef();
}

bool BinMXCAFDoc_AssemblyItemRefDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                              const occ::handle<TDF_Attribute>& theTarget,
                                              BinObjMgt_RRelocationTable&) const
{
  occ::handle<XCAFDoc_AssemblyItemRef> aThis = occ::down_cast<XCAFDoc_AssemblyItemRef>(theTarget);
  if (aThis.IsNull())
    return false;

  TCollection_AsciiString aPathStr;
  if (!(theSource >> aPathStr))
    return false;

  aThis->SetItem(aPathStr);

  int anExtraRef = 0;
  if (!(theSource >> anExtraRef))
    return false;

  if (anExtraRef == 1)
  {
    Standard_GUID aGUID;
    if (!(theSource >> aGUID))
      return false;

    aThis->SetGUID(aGUID);
  }
  else if (anExtraRef == 2)
  {
    int aSubshapeIndex;
    if (!(theSource >> aSubshapeIndex))
      return false;

    aThis->SetSubshapeIndex(aSubshapeIndex);
  }

  return true;
}

void BinMXCAFDoc_AssemblyItemRefDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  occ::handle<XCAFDoc_AssemblyItemRef> aThis = occ::down_cast<XCAFDoc_AssemblyItemRef>(theSource);
  if (!aThis.IsNull())
  {
    theTarget << aThis->GetItem().ToString();
    if (aThis->IsGUID())
    {
      theTarget << int(1);
      theTarget << aThis->GetGUID();
    }
    else if (aThis->IsSubshapeIndex())
    {
      theTarget << int(2);
      theTarget << aThis->GetSubshapeIndex();
    }
    else
      theTarget << int(0);
  }
}
