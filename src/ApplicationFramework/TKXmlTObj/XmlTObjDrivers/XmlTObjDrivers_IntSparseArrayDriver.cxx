#include <XmlTObjDrivers_IntSparseArrayDriver.hpp>
#include <Message_Messenger.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <TObj_TIntSparseArray.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDF_Tool.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlTObjDrivers_IntSparseArrayDriver, XmlMDF_ADriver)

#define ITEM_ID "itemId_"
#define ITEM_VALUE "itemValue_"

XmlTObjDrivers_IntSparseArrayDriver::XmlTObjDrivers_IntSparseArrayDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : XmlMDF_ADriver(theMessageDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlTObjDrivers_IntSparseArrayDriver::NewEmpty() const
{
  return new TObj_TIntSparseArray;
}

bool XmlTObjDrivers_IntSparseArrayDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                                const occ::handle<TDF_Attribute>& theTarget,
                                                XmlObjMgt_RRelocationTable&) const
{
  const XmlObjMgt_Element&          anElement = theSource;
  occ::handle<TObj_TIntSparseArray> aTarget   = occ::down_cast<TObj_TIntSparseArray>(theTarget);

  int                     i = 1;
  TCollection_AsciiString anItemID;
  TCollection_AsciiString anIdStr = TCollection_AsciiString(ITEM_ID) + TCollection_AsciiString(i);
  anItemID                        = anElement.getAttribute(anIdStr.ToCString());
  while (anItemID.IsIntegerValue() && anItemID.IntegerValue() != 0)
  {
    TCollection_AsciiString aStrIndex =
      TCollection_AsciiString(ITEM_VALUE) + TCollection_AsciiString(i);
    TCollection_AsciiString anItemValue = anElement.getAttribute(aStrIndex.ToCString());
    if (anItemValue.IsIntegerValue())
    {

      aTarget->SetDoBackup(false);
      aTarget->SetValue(anItemID.IntegerValue(), anItemValue.IntegerValue());
      aTarget->SetDoBackup(true);
    }
    i++;
  }
  return true;
}

void XmlTObjDrivers_IntSparseArrayDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                                XmlObjMgt_Persistent&             theTarget,
                                                XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TObj_TIntSparseArray> aSource = occ::down_cast<TObj_TIntSparseArray>(theSource);

  TObj_TIntSparseArray::Iterator anIt = aSource->GetIterator();
  int                            i    = 1;
  for (; anIt.More(); anIt.Next())
  {
    int aValue = anIt.Value();
    if (aValue == 0)
      continue;
    TCollection_AsciiString anIdStr = TCollection_AsciiString(ITEM_ID) + TCollection_AsciiString(i);
    TCollection_AsciiString aStrIndex =
      TCollection_AsciiString(ITEM_VALUE) + TCollection_AsciiString(i);
    theTarget.Element().setAttribute(anIdStr.ToCString(), (int)anIt.Index());
    theTarget.Element().setAttribute(aStrIndex.ToCString(), anIt.Value());
    i++;
  }

  TCollection_AsciiString anIdStr = TCollection_AsciiString(ITEM_ID) + TCollection_AsciiString(i);
  TCollection_AsciiString aStrIndex =
    TCollection_AsciiString(ITEM_VALUE) + TCollection_AsciiString(i);
  theTarget.Element().setAttribute(anIdStr.ToCString(), 0);
  theTarget.Element().setAttribute(aStrIndex.ToCString(), 0);
}
