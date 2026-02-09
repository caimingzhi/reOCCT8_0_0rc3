#include <BinMDataXtd_TriangulationDriver.hpp>
#include <BinObjMgt_Persistent.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd_Triangulation.hpp>
#include <TDF_Attribute.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BinMDataXtd_TriangulationDriver, BinMDF_ADriver)

BinMDataXtd_TriangulationDriver::BinMDataXtd_TriangulationDriver(
  const occ::handle<Message_Messenger>& theMsgDriver)
    : BinMDF_ADriver(theMsgDriver, STANDARD_TYPE(TDataXtd_Triangulation)->Name())
{
}

occ::handle<TDF_Attribute> BinMDataXtd_TriangulationDriver::NewEmpty() const
{
  return new TDataXtd_Triangulation();
}

bool BinMDataXtd_TriangulationDriver::Paste(const BinObjMgt_Persistent&       theSource,
                                            const occ::handle<TDF_Attribute>& theTarget,
                                            BinObjMgt_RRelocationTable&) const
{
  occ::handle<TDataXtd_Triangulation> attrubute = occ::down_cast<TDataXtd_Triangulation>(theTarget);

  int    i;
  double deflection, x, y, z;
  int    n1, n2, n3;
  int    nbNodes(0), nbTriangles(0);
  bool   hasUV(false);

  theSource >> nbNodes;
  theSource >> nbTriangles;
  theSource >> hasUV;
  theSource >> deflection;

  if (!nbNodes || !nbTriangles)
  {
    return false;
  }

  occ::handle<Poly_Triangulation> PT = new Poly_Triangulation(nbNodes, nbTriangles, hasUV);

  PT->Deflection(deflection);

  for (i = 1; i <= nbNodes; i++)
  {
    theSource >> x;
    theSource >> y;
    theSource >> z;
    PT->SetNode(i, gp_Pnt(x, y, z));
  }

  if (hasUV)
  {
    for (i = 1; i <= nbNodes; i++)
    {
      theSource >> x;
      theSource >> y;
      PT->SetUVNode(i, gp_Pnt2d(x, y));
    }
  }

  for (i = 1; i <= nbTriangles; i++)
  {
    theSource >> n1;
    theSource >> n2;
    theSource >> n3;
    PT->SetTriangle(i, Poly_Triangle(n1, n2, n3));
  }

  attrubute->Set(PT);
  return !PT.IsNull();
}

void BinMDataXtd_TriangulationDriver::Paste(
  const occ::handle<TDF_Attribute>& theSource,
  BinObjMgt_Persistent&             theTarget,
  NCollection_IndexedMap<occ::handle<Standard_Transient>>&) const
{
  const occ::handle<TDataXtd_Triangulation> attribute =
    occ::down_cast<TDataXtd_Triangulation>(theSource);
  const occ::handle<Poly_Triangulation>& PT = attribute->Get();
  if (!PT.IsNull())
  {
    int nbNodes     = PT->NbNodes();
    int nbTriangles = PT->NbTriangles();
    int n1, n2, n3;

    theTarget << nbNodes;
    theTarget << nbTriangles;
    theTarget << (PT->HasUVNodes() ? 1 : 0);

    theTarget << PT->Deflection();

    for (int i = 1; i <= nbNodes; i++)
    {
      const gp_Pnt aNode = PT->Node(i);
      theTarget << aNode.X();
      theTarget << aNode.Y();
      theTarget << aNode.Z();
    }

    if (PT->HasUVNodes())
    {
      for (int i = 1; i <= nbNodes; i++)
      {
        const gp_Pnt2d aNode2d = PT->UVNode(i);
        theTarget << aNode2d.X();
        theTarget << aNode2d.Y();
      }
    }

    for (int i = 1; i <= nbTriangles; i++)
    {
      PT->Triangle(i).Get(n1, n2, n3);
      theTarget << n1;
      theTarget << n2;
      theTarget << n3;
    }
  }
}
