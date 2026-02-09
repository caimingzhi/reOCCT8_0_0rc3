#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataStd_ExtStringArray.hpp>
#include <TDF_Attribute.hpp>
#include <TDocStd_FormatVersion.hpp>
#include <XmlMDataStd.hpp>
#include <XmlMDataStd_ExtStringArrayDriver.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Document.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataStd_ExtStringArrayDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(FirstIndexString, "first")
IMPLEMENT_DOMSTRING(LastIndexString, "last")
IMPLEMENT_DOMSTRING(ExtString, "string")
IMPLEMENT_DOMSTRING(IsDeltaOn, "delta")
IMPLEMENT_DOMSTRING(Separator, "separator")
IMPLEMENT_DOMSTRING(AttributeIDString, "extstrarrattguid")

static bool Contains(const occ::handle<TDataStd_ExtStringArray>& arr,
                     const TCollection_ExtendedString&           c)
{
  for (int i = arr->Lower(); i <= arr->Upper(); i++)
  {
    const TCollection_ExtendedString& value = arr->Value(i);
    if (value.Search(c) != -1)
    {
      return true;
    }
  }
  return false;
}

XmlMDataStd_ExtStringArrayDriver::XmlMDataStd_ExtStringArrayDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataStd_ExtStringArrayDriver::NewEmpty() const
{
  return (new TDataStd_ExtStringArray());
}

bool XmlMDataStd_ExtStringArrayDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                             const occ::handle<TDF_Attribute>& theTarget,
                                             XmlObjMgt_RRelocationTable&       theRelocTable) const
{
  int                        aFirstInd, aLastInd, ind;
  TCollection_ExtendedString aValue;
  const XmlObjMgt_Element&   anElement = theSource;

  XmlObjMgt_DOMString aFirstIndex = anElement.getAttribute(::FirstIndexString());
  if (aFirstIndex == nullptr)
    aFirstInd = 1;
  else if (!aFirstIndex.GetInteger(aFirstInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the first index"
                                 " for ExtStringArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  if (!anElement.getAttribute(::LastIndexString()).GetInteger(aLastInd))
  {
    TCollection_ExtendedString aMessageString =
      TCollection_ExtendedString("Cannot retrieve the last index"
                                 " for ExtStringArray attribute as \"")
      + aFirstIndex + "\"";
    myMessageDriver->Send(aMessageString, Message_Fail);
    return false;
  }

  TCollection_ExtendedString separator;
  XmlObjMgt_DOMString        aSeparator = anElement.getAttribute(::Separator());
  if (aSeparator.Type() != XmlObjMgt_DOMString::LDOM_NULL)
    separator = aSeparator.GetString();

  occ::handle<TDataStd_ExtStringArray> aExtStringArray =
    occ::down_cast<TDataStd_ExtStringArray>(theTarget);
  aExtStringArray->Init(aFirstInd, aLastInd);

  Standard_GUID       aGUID;
  XmlObjMgt_DOMString aGUIDStr = anElement.getAttribute(::AttributeIDString());
  if (aGUIDStr.Type() == XmlObjMgt_DOMString::LDOM_NULL)
    aGUID = TDataStd_ExtStringArray::GetID();
  else
    aGUID = Standard_GUID(static_cast<const char*>(aGUIDStr.GetString()));

  aExtStringArray->SetID(aGUID);

  if (!separator.Length() && anElement.hasChildNodes())
  {

    LDOM_Node                  aCurNode    = anElement.getFirstChild();
    LDOM_Element*              aCurElement = (LDOM_Element*)&aCurNode;
    TCollection_ExtendedString aValueStr;
    for (ind = aFirstInd; ind <= aLastInd && *aCurElement != anElement.getLastChild(); ind++)
    {
      XmlObjMgt::GetExtendedString(*aCurElement, aValueStr);
      aExtStringArray->SetValue(ind, aValueStr);
      aCurNode    = aCurElement->getNextSibling();
      aCurElement = (LDOM_Element*)&aCurNode;
    }
    XmlObjMgt::GetExtendedString(*aCurElement, aValueStr);
    aExtStringArray->SetValue(aLastInd, aValueStr);
  }
  else
  {
    TCollection_ExtendedString xstr;
    XmlObjMgt::GetExtendedString(anElement, xstr);
#ifdef _DEBUG
    TCollection_AsciiString cstr(xstr, '?');
#endif

    int      isym(1);
    char16_t xsep = separator.Value(1);
    for (ind = aFirstInd; ind <= aLastInd; ind++)
    {

      int iend = isym;
      while (iend < xstr.Length())
      {
        if (xstr.Value(iend) == xsep)
        {
          break;
        }
        iend++;
      }
      if (iend <= xstr.Length() && xstr.Value(iend) != xsep)
      {
        iend++;
      }

      TCollection_ExtendedString xvalue(iend - isym, '\0');

      for (int i = isym; i < iend; ++i)
      {
        const char16_t x = xstr.Value(i);
        xvalue.SetValue(i - isym + 1, x);
      }
#ifdef _DEBUG
      TCollection_AsciiString cvalue(xvalue, '?');
#endif

      aExtStringArray->SetValue(ind, xvalue);

      isym = iend + 1;
    }
  }

  bool aDelta(false);

  if (theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
      >= TDocStd_FormatVersion_VERSION_3)
  {
    int aDeltaValue;
    if (!anElement.getAttribute(::IsDeltaOn()).GetInteger(aDeltaValue))
    {
      TCollection_ExtendedString aMessageString =
        TCollection_ExtendedString("Cannot retrieve the isDelta value"
                                   " for IntegerArray attribute as \"")
        + aDeltaValue + "\"";
      myMessageDriver->Send(aMessageString, Message_Fail);
      return false;
    }
    else
      aDelta = aDeltaValue != 0;
  }

  aExtStringArray->SetDelta(aDelta);

  return true;
}

void XmlMDataStd_ExtStringArrayDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                             XmlObjMgt_Persistent&             theTarget,
                                             XmlObjMgt_SRelocationTable&       theRelocTable) const
{
  occ::handle<TDataStd_ExtStringArray> aExtStringArray =
    occ::down_cast<TDataStd_ExtStringArray>(theSource);

  int aL = aExtStringArray->Lower(), anU = aExtStringArray->Upper(), i;

  XmlObjMgt_Element& anElement = theTarget;

  if (aL != 1)
    anElement.setAttribute(::FirstIndexString(), aL);
  anElement.setAttribute(::LastIndexString(), anU);
  anElement.setAttribute(::IsDeltaOn(), aExtStringArray->GetDelta() ? 1 : 0);

  bool found(true);

  char c = '-';
  if (theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
      >= TDocStd_FormatVersion_VERSION_8)
  {

    static char aPreferable[] = "-_.:^~";
    for (i = 0; found && aPreferable[i]; i++)
    {
      c     = aPreferable[i];
      found = Contains(aExtStringArray, TCollection_ExtendedString(c));
    }

    if (found)
    {
      c = '!';
      while (found && c < '~')
      {
        found = false;
#ifdef _DEBUG
        TCollection_AsciiString cseparator(c);
#endif
        TCollection_ExtendedString separator(c);
        found = Contains(aExtStringArray, separator);
        if (found)
        {
          c++;

          while (c < '~' && (c == '&' || c == '<'))
          {
            c++;
          }
        }
      }
    }
  }

  if (found)
  {

    XmlObjMgt_Document aDoc(anElement.getOwnerDocument());
    for (i = aL; i <= anU; i++)
    {
      const TCollection_ExtendedString& aValueStr  = aExtStringArray->Value(i);
      XmlObjMgt_Element                 aCurTarget = aDoc.createElement(::ExtString());
      XmlObjMgt::SetExtendedString(aCurTarget, aValueStr);
      anElement.appendChild(aCurTarget);
    }
  }
  else
  {

    TCollection_AsciiString csep(c);
    anElement.setAttribute(::Separator(), csep.ToCString());

    int len(0);
    for (i = aL; i <= anU; i++)
    {
      const TCollection_ExtendedString& aValueStr = aExtStringArray->Value(i);
      len += aValueStr.Length();
      len++;
    }
    if (!len)
      len++;

    int                        isym(1);
    TCollection_ExtendedString xstr(len, c);
    for (i = aL; i <= anU; i++)
    {
      const TCollection_ExtendedString& aValueStr = aExtStringArray->Value(i);
      for (int k = 1; k <= aValueStr.Length(); k++)
      {
        xstr.SetValue(isym++, aValueStr.Value(k));
      }
      xstr.SetValue(isym++, c);
    }
    if (xstr.SearchFromEnd(c) == isym - 1)
      isym--;
    xstr.SetValue(isym, '\0');
#ifdef _DEBUG
    TCollection_AsciiString cstr(xstr, '?');
#endif

    XmlObjMgt::SetExtendedString(theTarget, xstr);
  }
  if (aExtStringArray->ID() != TDataStd_ExtStringArray::GetID())
  {

    char                aGuidStr[Standard_GUID_SIZE_ALLOC];
    Standard_PCharacter pGuidStr = aGuidStr;
    aExtStringArray->ID().ToCString(pGuidStr);
    theTarget.Element().setAttribute(::AttributeIDString(), aGuidStr);
  }
}
