#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Geometry.hpp>
#include <TDF_Attribute.hpp>
#include <XmlMDataXtd_GeometryDriver.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataXtd_GeometryDriver, XmlMDF_ADriver)

static const XmlObjMgt_DOMString& GeometryTypeString(const TDataXtd_GeometryEnum);
static bool                       GeometryTypeEnum(const XmlObjMgt_DOMString& theString,
                                                   TDataXtd_GeometryEnum&     theResult);

IMPLEMENT_DOMSTRING(TypeString, "geomtype")

IMPLEMENT_DOMSTRING(GeomAnyString, "any")
IMPLEMENT_DOMSTRING(GeomPointString, "point")
IMPLEMENT_DOMSTRING(GeomLineString, "line")
IMPLEMENT_DOMSTRING(GeomCircleString, "circle")
IMPLEMENT_DOMSTRING(GeomEllipseString, "ellipse")
IMPLEMENT_DOMSTRING(GeomSplineString, "slpine")
IMPLEMENT_DOMSTRING(GeomPlaneString, "plane")
IMPLEMENT_DOMSTRING(GeomCylinderString, "cylinder")

XmlMDataXtd_GeometryDriver::XmlMDataXtd_GeometryDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataXtd_GeometryDriver::NewEmpty() const
{
  return (new TDataXtd_Geometry());
}

bool XmlMDataXtd_GeometryDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                       const occ::handle<TDF_Attribute>& theTarget,
                                       XmlObjMgt_RRelocationTable&) const
{
  occ::handle<TDataXtd_Geometry> aT = occ::down_cast<TDataXtd_Geometry>(theTarget);

  XmlObjMgt_DOMString   aType = theSource.Element().getAttribute(::TypeString());
  TDataXtd_GeometryEnum aTypeEnum;
  if (!GeometryTypeEnum(aType, aTypeEnum))
  {
    myMessageDriver->Send("TDataXtd_GeometryEnum; "
                          "string value without enum term equivalence",
                          Message_Fail);
    return false;
  }

  aT->SetType(aTypeEnum);
  return true;
}

void XmlMDataXtd_GeometryDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                       XmlObjMgt_Persistent&             theTarget,
                                       XmlObjMgt_SRelocationTable&) const
{
  occ::handle<TDataXtd_Geometry> aG = occ::down_cast<TDataXtd_Geometry>(theSource);
  theTarget.Element().setAttribute(::TypeString(), GeometryTypeString(aG->GetType()));
}

static bool GeometryTypeEnum(const XmlObjMgt_DOMString& theString, TDataXtd_GeometryEnum& theResult)
{
  TDataXtd_GeometryEnum aResult = TDataXtd_ANY_GEOM;
  if (!theString.equals(::GeomAnyString()))
  {
    if (theString.equals(::GeomPointString()))
      aResult = TDataXtd_POINT;
    else if (theString.equals(::GeomLineString()))
      aResult = TDataXtd_LINE;
    else if (theString.equals(::GeomCircleString()))
      aResult = TDataXtd_CIRCLE;
    else if (theString.equals(::GeomEllipseString()))
      aResult = TDataXtd_ELLIPSE;
    else if (theString.equals(::GeomSplineString()))
      aResult = TDataXtd_SPLINE;
    else if (theString.equals(::GeomPlaneString()))
      aResult = TDataXtd_PLANE;
    else if (theString.equals(::GeomCylinderString()))
      aResult = TDataXtd_CYLINDER;
    else
      return false;
  }
  theResult = aResult;
  return true;
}

static const XmlObjMgt_DOMString& GeometryTypeString(const TDataXtd_GeometryEnum theE)
{
  switch (theE)
  {
    case TDataXtd_ANY_GEOM:
      return ::GeomAnyString();
    case TDataXtd_POINT:
      return ::GeomPointString();
    case TDataXtd_LINE:
      return ::GeomLineString();
    case TDataXtd_CIRCLE:
      return ::GeomCircleString();
    case TDataXtd_ELLIPSE:
      return ::GeomEllipseString();
    case TDataXtd_SPLINE:
      return ::GeomSplineString();
    case TDataXtd_PLANE:
      return ::GeomPlaneString();
    case TDataXtd_CYLINDER:
      return ::GeomCylinderString();

    default:
      throw Standard_DomainError("TDataXtd_GeometryEnum; enum term unknown");
  }
}
