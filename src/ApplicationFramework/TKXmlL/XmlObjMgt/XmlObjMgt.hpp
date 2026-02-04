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

//! This package defines services to manage the storage
//! grain of data produced by applications and those classes
//! to manage persistent extern reference.
class XmlObjMgt
{
public:
  DEFINE_STANDARD_ALLOC

  //! Define the name of XMLattribute 'ID' (to be used everywhere)
  Standard_EXPORT static const XmlObjMgt_DOMString& IdString();

  //! Add attribute <theElement extstring="theString" ...>
  Standard_EXPORT static bool SetExtendedString(XmlObjMgt_Element&                theElement,
                                                const TCollection_ExtendedString& theString);

  //! Get attribute <theElement extstring="theString" ...>
  Standard_EXPORT static bool GetExtendedString(const XmlObjMgt_Element&    theElement,
                                                TCollection_ExtendedString& theString);

  //! Returns the first child text node
  Standard_EXPORT static XmlObjMgt_DOMString GetStringValue(const XmlObjMgt_Element& theElement);

  //! Add theData as the last child text node to theElement
  //! isClearText(True) avoids analysis of the string and replacement
  //! of characters like '<' and '&' during XML file storage.
  //! Do NEVER set isClearText unless you have a hell of a reason
  Standard_EXPORT static void SetStringValue(XmlObjMgt_Element&         theElement,
                                             const XmlObjMgt_DOMString& theData,
                                             const bool                 isClearText = false);

  //! Convert XPath expression (DOMString) into TagEntry string
  //! returns False on Error
  Standard_EXPORT static bool GetTagEntryString(const XmlObjMgt_DOMString& theTarget,
                                                TCollection_AsciiString&   theTagEntry);

  //! Convert XPath expression (DOMString) into TagEntry string
  //! returns False on Error
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

