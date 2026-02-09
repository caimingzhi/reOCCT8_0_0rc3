#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <XmlObjMgt_DOMString.hpp>
class gp_Trsf;
class gp_Mat;
class gp_XYZ;

class XmlObjMgt_GP
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static XmlObjMgt_DOMString Translate(const gp_Trsf& aTrsf);

  Standard_EXPORT static XmlObjMgt_DOMString Translate(const gp_Mat& aMat);

  Standard_EXPORT static XmlObjMgt_DOMString Translate(const gp_XYZ& anXYZ);

  Standard_EXPORT static bool Translate(const XmlObjMgt_DOMString& aStr, gp_Trsf& T);

  Standard_EXPORT static bool Translate(const XmlObjMgt_DOMString& aStr, gp_Mat& T);

  Standard_EXPORT static bool Translate(const XmlObjMgt_DOMString& aStr, gp_XYZ& T);
};
