#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <XmlMNaming_Shape1.hpp>
#include <XmlObjMgt.hpp>

#include <cstdio>
IMPLEMENT_DOMSTRING(TShapeString, "tshape")
IMPLEMENT_DOMSTRING(LocationString, "location")

IMPLEMENT_DOMSTRING(XCoordString, "x")
IMPLEMENT_DOMSTRING(YCoordString, "y")
IMPLEMENT_DOMSTRING(ZCoordString, "z")

//=================================================================================================

XmlMNaming_Shape1::XmlMNaming_Shape1(XmlObjMgt_Document& theDoc)
    : myTShapeID(0),
      myLocID(0),
      myOrientation(TopAbs_FORWARD)
{
  myElement = theDoc.createElement(XmlObjMgt_DOMString("shape"));
}

//=================================================================================================

XmlMNaming_Shape1::XmlMNaming_Shape1(const XmlObjMgt_Element& theEl)
    : myElement(theEl),
      myTShapeID(0),
      myLocID(0),
      myOrientation(TopAbs_FORWARD)
{
  if (myElement != nullptr)
  {
    myElement.getAttribute(::LocationString()).GetInteger(myLocID);
    XmlObjMgt_DOMString aString = myElement.getAttribute(::TShapeString());
    const char*         aPtr    = aString.GetString();
    switch (*aPtr)
    {
      case '+':
        myOrientation = TopAbs_FORWARD;
        break;
      case '-':
        myOrientation = TopAbs_REVERSED;
        break;
      case 'i':
        myOrientation = TopAbs_INTERNAL;
        break;
      case 'e':
        myOrientation = TopAbs_EXTERNAL;
        break;
      default:
        throw Standard_DomainError(
          "XmlMNaming_Shape1; orientation value without enum term equivalence");
    }
    const char* anIntPtr = (const char*)&aPtr[1];
    if (!XmlObjMgt::GetInteger(anIntPtr, myTShapeID))
      throw Standard_DomainError(
        "XmlMNaming_Shape1; tshape value cannot be initialised by integer");
  }
}

//=================================================================================================

const XmlObjMgt_Element& XmlMNaming_Shape1::Element() const
{
  return myElement;
}

//=================================================================================================

XmlObjMgt_Element& XmlMNaming_Shape1::Element()
{
  return myElement;
}

//=================================================================================================

int XmlMNaming_Shape1::TShapeId() const
{
  return myTShapeID;
}

//=================================================================================================

int XmlMNaming_Shape1::LocId() const
{
  return myLocID;
}

//=================================================================================================

TopAbs_Orientation XmlMNaming_Shape1::Orientation() const
{
  return myOrientation;
}

//=================================================================================================

void XmlMNaming_Shape1::SetShape(const int                theID,
                                 const int                theLocID,
                                 const TopAbs_Orientation theOrient)
{
  myTShapeID    = theID;
  myLocID       = theLocID;
  myOrientation = theOrient;

  char aBuffer[16], anOr;

  switch (theOrient)
  {
    case TopAbs_FORWARD:
      anOr = '+';
      break;
    case TopAbs_REVERSED:
      anOr = '-';
      break;
    case TopAbs_INTERNAL:
      anOr = 'i';
      break;
    case TopAbs_EXTERNAL:
      anOr = 'e';
      break;
    default:
      anOr = '\0';
  }
  Sprintf(aBuffer, "%c%i", anOr, theID);
  Element().setAttribute(::TShapeString(), aBuffer);
  if (theLocID > 0)
    Element().setAttribute(::LocationString(), theLocID);
}

//=================================================================================================

void XmlMNaming_Shape1::SetVertex(const TopoDS_Shape& theVertex)
{
  TopoDS_Vertex aV   = TopoDS::Vertex(theVertex);
  gp_Pnt        aPos = BRep_Tool::Pnt(aV);

  char buf[16];
  Sprintf(buf, "%.8g", aPos.X());
  Element().setAttribute(::XCoordString(), buf);

  Sprintf(buf, "%.8g", aPos.Y());
  Element().setAttribute(::YCoordString(), buf);

  Sprintf(buf, "%.8g", aPos.Z());
  Element().setAttribute(::ZCoordString(), buf);
}
