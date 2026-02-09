#include <XmlMDataXtd_TriangulationDriver.hpp>
#include <Message_Messenger.hpp>
#include <NCollection_LocalArray.hpp>
#include <Standard_Type.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <TDataXtd_Triangulation.hpp>
#include <LDOM_OSStream.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMDataXtd_TriangulationDriver, XmlMDF_ADriver)
IMPLEMENT_DOMSTRING(TriangString, "triangulation")
IMPLEMENT_DOMSTRING(NullString, "null")
IMPLEMENT_DOMSTRING(ExistString, "exists")

XmlMDataXtd_TriangulationDriver::XmlMDataXtd_TriangulationDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : XmlMDF_ADriver(theMsgDriver, nullptr)
{
}

occ::handle<TDF_Attribute> XmlMDataXtd_TriangulationDriver::NewEmpty() const
{
  return new TDataXtd_Triangulation();
}

bool XmlMDataXtd_TriangulationDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                            const occ::handle<TDF_Attribute>& theTarget,
                                            XmlObjMgt_RRelocationTable&) const
{
  const XmlObjMgt_Element&            element   = theSource;
  occ::handle<TDataXtd_Triangulation> attribute = occ::down_cast<TDataXtd_Triangulation>(theTarget);

  XmlObjMgt_DOMString triangStatus = element.getAttribute(::TriangString());
  if (triangStatus == nullptr || triangStatus.Type() != LDOMBasicString::LDOM_AsciiDoc
      || strcmp(triangStatus.GetString(), ::ExistString().GetString()))
  {

    return true;
  }

  const XmlObjMgt_DOMString& data = XmlObjMgt::GetStringValue(element);
  std::stringstream          stream(std::string(data.GetString()));

  int    i, n1, n2, n3;
  int    nbNodes, nbTriangles, hasUV;
  double deflection, x, y, z;

  stream >> nbNodes >> nbTriangles >> hasUV;
  GetReal(stream, deflection);

  NCollection_Array1<gp_Pnt>   Nodes(1, nbNodes);
  NCollection_Array1<gp_Pnt2d> UVNodes(1, nbNodes);

  for (i = 1; i <= nbNodes; i++)
  {
    GetReal(stream, x);
    GetReal(stream, y);
    GetReal(stream, z);
    Nodes(i).SetCoord(x, y, z);
  }

  if (hasUV)
  {
    for (i = 1; i <= nbNodes; i++)
    {
      GetReal(stream, x);
      GetReal(stream, y);
      UVNodes(i).SetCoord(x, y);
    }
  }

  NCollection_Array1<Poly_Triangle> Triangles(1, nbTriangles);
  for (i = 1; i <= nbTriangles; i++)
  {
    stream >> n1 >> n2 >> n3;
    Triangles(i).Set(n1, n2, n3);
  }

  occ::handle<Poly_Triangulation> PT;
  if (hasUV)
    PT = new Poly_Triangulation(Nodes, UVNodes, Triangles);
  else
    PT = new Poly_Triangulation(Nodes, Triangles);
  PT->Deflection(deflection);

  attribute->Set(PT);

  return true;
}

void XmlMDataXtd_TriangulationDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                            XmlObjMgt_Persistent&             theTarget,
                                            XmlObjMgt_SRelocationTable&) const
{
  const occ::handle<TDataXtd_Triangulation> attribute =
    occ::down_cast<TDataXtd_Triangulation>(theSource);
  if (attribute->Get().IsNull())
    theTarget.Element().setAttribute(::TriangString(), ::NullString());
  else
  {
    theTarget.Element().setAttribute(::TriangString(), ::ExistString());

    int i, n1, n2, n3;

    const occ::handle<Poly_Triangulation>& PT          = attribute->Get();
    int                                    nbNodes     = PT->NbNodes();
    int                                    nbTriangles = PT->NbTriangles();
    int                                    size        = PT->NbNodes();

    size *= 3 * 25;
    if (PT->HasUVNodes())
      size += 2 * 25 * nbNodes;

    size += 3 * 10 * nbTriangles;
    size *= 2;
    if (!size)
      size = 1;

    LDOM_OSStream stream(size);
    stream.precision(17);

    stream << nbNodes << " " << nbTriangles << " ";
    stream << ((PT->HasUVNodes()) ? "1" : "0") << " ";

    stream << PT->Deflection() << "\n";

    for (i = 1; i <= nbNodes; i++)
    {
      const gp_Pnt aNode = PT->Node(i);
      stream << aNode.X() << " " << aNode.Y() << " " << aNode.Z() << " ";
    }

    if (PT->HasUVNodes())
    {
      for (i = 1; i <= nbNodes; i++)
      {
        const gp_Pnt2d aNode2d = PT->UVNode(i);
        stream << aNode2d.X() << " " << aNode2d.Y() << " ";
      }
    }

    for (i = 1; i <= nbTriangles; i++)
    {
      PT->Triangle(i).Get(n1, n2, n3);
      stream << n1 << " " << n2 << " " << n3 << " ";
    }

    stream << std::ends;

    char* dump = (char*)stream.str();

    XmlObjMgt::SetStringValue(theTarget, dump, true);
    delete[] dump;
  }
}

void XmlMDataXtd_TriangulationDriver::GetReal(Standard_IStream& IS, double& theValue) const
{
  theValue = 0.;
  if (IS.eof())
    return;

  char buffer[256];
  buffer[0]                 = '\0';
  std::streamsize anOldWide = IS.width(256);
  IS >> buffer;
  IS.width(anOldWide);
  theValue = Strtod(buffer, nullptr);
}
