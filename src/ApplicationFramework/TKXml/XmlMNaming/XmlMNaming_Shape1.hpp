#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <XmlObjMgt_Element.hpp>
#include <TopAbs_Orientation.hpp>
#include <XmlObjMgt_Document.hpp>
class TopoDS_Shape;

class XmlMNaming_Shape1
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XmlMNaming_Shape1(XmlObjMgt_Document& Doc);

  Standard_EXPORT XmlMNaming_Shape1(const XmlObjMgt_Element& E);

  Standard_EXPORT const XmlObjMgt_Element& Element() const;

  Standard_EXPORT XmlObjMgt_Element& Element();

  Standard_EXPORT int TShapeId() const;

  Standard_EXPORT int LocId() const;

  Standard_EXPORT TopAbs_Orientation Orientation() const;

  Standard_EXPORT void SetShape(const int ID, const int LocID, const TopAbs_Orientation Orient);

  Standard_EXPORT void SetVertex(const TopoDS_Shape& theVertex);

private:
  XmlObjMgt_Element  myElement;
  int                myTShapeID;
  int                myLocID;
  TopAbs_Orientation myOrientation;
};
