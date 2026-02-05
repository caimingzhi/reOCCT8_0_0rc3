#pragma once

#include <LDOMString.hpp>

typedef LDOMString XmlObjMgt_DOMString;

#define IMPLEMENT_DOMSTRING(FnName, String)                                                        \
  static const XmlObjMgt_DOMString& FnName()                                                       \
  {                                                                                                \
    static const XmlObjMgt_DOMString aString(String);                                              \
    return aString;                                                                                \
  }
