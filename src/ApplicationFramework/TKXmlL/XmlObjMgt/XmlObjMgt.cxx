#include <XmlObjMgt.hpp>

#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <XmlObjMgt_Document.hpp>

#include <cerrno>
#include <cstdio>
#include <limits>

static const char aRefPrefix[] = "/document/label";
static const char aRefElem1[]  = "/label[@tag=";
static const char aRefElem2[]  = "]";

const XmlObjMgt_DOMString& XmlObjMgt::IdString()
{
  static const LDOMString aString("id");
  return aString;
}

void XmlObjMgt::SetStringValue(XmlObjMgt_Element&         theElement,
                               const XmlObjMgt_DOMString& theData,
                               const bool                 isClearText)
{
  XmlObjMgt_Document aDocument = theElement.getOwnerDocument();
  LDOM_Text          aText     = aDocument.createTextNode(theData);
  if (isClearText)
    aText.SetValueClear();
  theElement.appendChild(aText);
}

XmlObjMgt_DOMString XmlObjMgt::GetStringValue(const XmlObjMgt_Element& theElement)
{
  XmlObjMgt_DOMString aString;
  for (LDOM_Node aNode = theElement.getFirstChild(); aNode != nullptr;
       aNode           = aNode.getNextSibling())
  {
    if (aNode.getNodeType() == LDOM_Node::TEXT_NODE)
    {
      aString = ((const LDOM_Text&)aNode).getData();
      break;
    }
  }
  return aString;
}

void SprintfExtStr(char* out, const TCollection_ExtendedString& theString)
{
  unsigned short* p       = (unsigned short*)theString.ToExtString();
  int             len     = theString.Length();
  int             i       = 0;
  unsigned short  mask[4] = {0xf000, 0x0f00, 0x00f0, 0x000f};
  while (len)
  {
    for (int j = 0, k = 3; j < 4; j++, k--)
    {
      unsigned short v = *(p + i) & mask[j];
      v                = (unsigned short)(v >> (4 * k));
      if (v < 10)
        v |= 0x30;
      else
        v += 87;
      out[4 * i + j] = (char)v;
    }
    i++;
    len--;
  }
  out[4 * theString.Length()] = 0x00;
}

bool XmlObjMgt::SetExtendedString(XmlObjMgt_Element&                theElement,
                                  const TCollection_ExtendedString& theString)
{
  TCollection_AsciiString anAString;
  if (theString.IsAscii())
  {
    anAString = TCollection_AsciiString(theString, '?');
    SetStringValue(theElement, anAString.ToCString());
  }
  else
  {
    const int aLen = theString.Length();

    char* buf0 = new char[4 * (aLen + 1) + 3];
    Sprintf(&buf0[0], "##%04x", 0xfeff);
    char* buf = &buf0[6];

    SprintfExtStr(buf, theString);
    SetStringValue(theElement, buf0);
    delete[] buf0;
  }
  return true;
}

bool XmlObjMgt::GetExtendedString(const XmlObjMgt_Element&    theElement,
                                  TCollection_ExtendedString& theString)
{
  theString = GetStringValue(theElement);
  return true;
}

bool XmlObjMgt::GetTagEntryString(const XmlObjMgt_DOMString& theSource,
                                  TCollection_AsciiString&   theTagEntry)
{

  const size_t aPrefixSize = sizeof(aRefPrefix) - 1;
  const char*  aSource     = theSource.GetString();
  if (strncmp(aSource, aRefPrefix, aPrefixSize))
    return false;

  char* aTagEntry    = (char*)Standard::Allocate(strlen(aSource) / 2);
  char* aTagEntryPtr = aTagEntry + 1;
  *aTagEntry         = '0';
  aSource += aPrefixSize;

  const size_t anElem1Size = sizeof(aRefElem1) - 1;
  const size_t anElem2Size = sizeof(aRefElem2) - 1;
  while (aSource[0] != '\0')
  {

    if (strncmp(aSource, aRefElem1, anElem1Size))
      return false;
    aSource += anElem1Size;
    const char aQuote = aSource[0];
    if (aQuote != '\'' && aQuote != '\"')
      return false;

    errno = 0;
    char* aPtr;
    long  aTagValue = strtol(&aSource[1], &aPtr, 10);
    int   aLen      = (int)(aPtr - &aSource[1]);
    if (aTagValue < 0 || aLen == 0 || aPtr[0] != aQuote || errno == ERANGE || errno == EINVAL)
      return false;
    aTagEntryPtr[0] = ':';
    memcpy(&aTagEntryPtr[1], &aSource[1], aLen);
    aTagEntryPtr += (aLen + 1);

    if (strncmp(aPtr + 1, aRefElem2, anElem2Size))
      return false;
    aSource = aPtr + 1 + anElem2Size;
  }
  aTagEntryPtr[0] = '\0';
  theTagEntry     = aTagEntry;
  Standard::Free(aTagEntry);
  return true;
}

void XmlObjMgt::SetTagEntryString(XmlObjMgt_DOMString&           theTarget,
                                  const TCollection_AsciiString& theTagEntry)
{

  const char* aTagEntry = (const char*)theTagEntry.ToCString() + 1;
  if (aTagEntry[-1] != '0')
    return;

  const char* aPtr      = aTagEntry;
  int         aTagCount = 0;
  while (*aPtr)
    if (*aPtr++ == ':')
      aTagCount++;

  const size_t anElem1Size = sizeof(aRefElem1) - 1;
  const size_t anElem2Size = sizeof(aRefElem2) - 1;
  char*        aTarget =
    (char*)Standard::Allocate(sizeof(aRefPrefix) + aTagCount * (anElem1Size + anElem2Size + 12));
  memcpy(aTarget, aRefPrefix, sizeof(aRefPrefix) - 1);
  char* aTargetPtr = aTarget + (sizeof(aRefPrefix) - 1);

  for (;;)
  {

    aPtr = strchr(aTagEntry, ':');
    if (aPtr == nullptr)
      break;
    aTagEntry = aPtr + 1;

    errno = 0;
    char* ptr;
    long  aTagValue = strtol(aTagEntry, &ptr, 10);
    int   aTagSize  = (int)(ptr - aTagEntry);
    if (aTagValue < 0 || aTagSize == 0 || errno == ERANGE || errno == EINVAL)
      return;

    memcpy(&aTargetPtr[0], aRefElem1, anElem1Size);
    aTargetPtr[anElem1Size] = '\"';
    memcpy(&aTargetPtr[anElem1Size + 1], aTagEntry, aTagSize);
    aTargetPtr[anElem1Size + aTagSize + 1] = '\"';
    memcpy(&aTargetPtr[anElem1Size + aTagSize + 2], aRefElem2, anElem2Size);
    aTargetPtr += (anElem1Size + aTagSize + anElem2Size + 2);
  }
  *aTargetPtr = '\0';
  theTarget   = aTarget;
  Standard::Free(aTarget);
}

XmlObjMgt_Element XmlObjMgt::FindChildElement(const XmlObjMgt_Element& theSource, const int theId)
{
  LDOM_Node aNode = theSource.getFirstChild();
  int       anId;
  while (!aNode.isNull())
  {
    if (aNode.getNodeType() == LDOM_Node::ELEMENT_NODE)
    {
      LDOM_Element anElem = (LDOM_Element&)aNode;
      if (anElem.getAttribute(IdString()).GetInteger(anId))
        if (anId == theId)
          return anElem;
    }
    aNode = aNode.getNextSibling();
  }

  return LDOM_Element();
}

XmlObjMgt_Element XmlObjMgt::FindChildByRef(const XmlObjMgt_Element&   theSource,
                                            const XmlObjMgt_DOMString& theRefName)
{
  int anID;
  if (theSource.getAttribute(theRefName).GetInteger(anID))
    return FindChildElement(theSource, anID);
  return LDOM_Element();
}

XmlObjMgt_Element XmlObjMgt::FindChildByName(const XmlObjMgt_Element&   theSource,
                                             const XmlObjMgt_DOMString& theName)
{
  return theSource.GetChildByTagName(theName);
}

bool XmlObjMgt::GetInteger(const char*& theString, int& theValue)
{
  char* ptr;
  errno       = 0;
  long aValue = strtol(theString, &ptr, 10);
  if (ptr == theString || errno == ERANGE || errno == EINVAL)
    return false;
  theValue  = int(aValue);
  theString = ptr;
  return true;
}

bool XmlObjMgt::GetReal(const char*& theString, double& theValue)
{
  char* ptr;
  errno    = 0;
  theValue = Strtod(theString, &ptr);
  if (ptr == theString || errno == ERANGE || errno == EINVAL)
    return false;

  theString = ptr;

  if (*ptr == '#')
  {
    if (!strncmp(ptr, "#QNAN", 5) || !strncmp(ptr, "#SNAN", 5))
    {
      theString = ptr + 5;
      theValue  = std::numeric_limits<double>::quiet_NaN();
      return true;
    }
    else if (!strncmp(ptr, "#INF", 4))
    {
      theString = ptr + 4;
      theValue  = (theValue < 0 ? -std::numeric_limits<double>::infinity()
                                : std::numeric_limits<double>::infinity());
      return true;
    }
    else
      return false;
  }
  else if (*ptr && !IsSpace(*ptr))
  {

    return false;
  }

  return true;
}

bool XmlObjMgt::GetReal(const XmlObjMgt_DOMString& theString, double& theValue)
{
  switch (theString.Type())
  {
    case LDOMBasicString::LDOM_NULL:
      return false;
    case LDOMBasicString::LDOM_Integer:
    {
      int anIntValue;
      theString.GetInteger(anIntValue);
      theValue = double(anIntValue);
      break;
    }
    default:
    {
      const char* aString = theString.GetString();
      return GetReal(aString, theValue);
    }
  }
  return true;
}
