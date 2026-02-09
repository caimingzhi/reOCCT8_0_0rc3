#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <XmlObjMgt_DOMString.hpp>
#include <Standard_Boolean.hpp>
#include <XmlObjMgt_Element.hpp>
#include <Standard_CString.hpp>
#include <Standard_Real.hpp>
class TCollection_ExtendedString;
class TCollection_AsciiString;

class XmlObjMgt
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static const XmlObjMgt_DOMString& IdString();

  Standard_EXPORT static bool SetExtendedString(XmlObjMgt_Element&                theElement,
                                                const TCollection_ExtendedString& theString);

  Standard_EXPORT static bool GetExtendedString(const XmlObjMgt_Element&    theElement,
                                                TCollection_ExtendedString& theString);

  Standard_EXPORT static XmlObjMgt_DOMString GetStringValue(const XmlObjMgt_Element& theElement);

  Standard_EXPORT static void SetStringValue(XmlObjMgt_Element&         theElement,
                                             const XmlObjMgt_DOMString& theData,
                                             const bool                 isClearText = false);

  Standard_EXPORT static bool GetTagEntryString(const XmlObjMgt_DOMString& theTarget,
                                                TCollection_AsciiString&   theTagEntry);

  Standard_EXPORT static void SetTagEntryString(XmlObjMgt_DOMString&           theSource,
                                                const TCollection_AsciiString& theTagEntry);

  Standard_EXPORT static XmlObjMgt_Element FindChildElement(const XmlObjMgt_Element& theSource,
                                                            const int                theObjId);

  Standard_EXPORT static XmlObjMgt_Element FindChildByRef(const XmlObjMgt_Element&   theSource,
                                                          const XmlObjMgt_DOMString& theRefName);

  Standard_EXPORT static XmlObjMgt_Element FindChildByName(const XmlObjMgt_Element&   theSource,
                                                           const XmlObjMgt_DOMString& theName);

  Standard_EXPORT static bool GetInteger(const char*& theString, int& theValue);

  Standard_EXPORT static bool GetReal(const char*& theString, double& theValue);

  Standard_EXPORT static bool GetReal(const XmlObjMgt_DOMString& theString, double& theValue);
};
