

#include <BRep_Builder.hpp>
#include <gp_Pnt.hpp>
#include <ShapeAnalysis_Edge.hpp>
#include <ShapeExtend_WireData.hpp>
#include <ShapeFix_WireVertex.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>

ShapeFix_WireVertex::ShapeFix_WireVertex() = default;

void ShapeFix_WireVertex::Init(const TopoDS_Wire& wire, const double preci)
{
  occ::handle<ShapeExtend_WireData> sbwd = new ShapeExtend_WireData(wire);
  Init(sbwd, preci);
}

void ShapeFix_WireVertex::Init(const occ::handle<ShapeExtend_WireData>& sbwd, const double preci)
{
  myAnalyzer.Load(sbwd);
  myAnalyzer.SetPrecision(preci);
  myAnalyzer.Analyze();
}

void ShapeFix_WireVertex::Init(const ShapeAnalysis_WireVertex& sawv)
{
  myAnalyzer = sawv;
}

const ShapeAnalysis_WireVertex& ShapeFix_WireVertex::Analyzer() const
{
  return myAnalyzer;
}

const occ::handle<ShapeExtend_WireData>& ShapeFix_WireVertex::WireData() const
{
  return myAnalyzer.WireData();
}

TopoDS_Wire ShapeFix_WireVertex::Wire() const
{
  return myAnalyzer.WireData()->Wire();
}

int ShapeFix_WireVertex::FixSame()
{

  if (!myAnalyzer.IsDone())
    return 0;

  int          nbfix = 0;
  BRep_Builder B;

  occ::handle<ShapeExtend_WireData> sbwd = myAnalyzer.WireData();
  int                               i, nb = sbwd->NbEdges();

  for (i = 1; i <= nb; i++)
  {
    int j    = (i == nb ? 1 : i + 1);
    int stat = myAnalyzer.Status(i);
    if (stat != 1 && stat != 2)
      continue;

    TopoDS_Edge E1 = sbwd->Edge(i);
    TopoDS_Edge E2 = sbwd->Edge(j);

    ShapeAnalysis_Edge sae;
    TopoDS_Vertex      V1 = sae.LastVertex(E1);
    TopoDS_Vertex      V2 = sae.FirstVertex(E2);
    if (V1 == V2)
    {
      myAnalyzer.SetSameVertex(i);
      continue;
    }
    if (stat == 2)
    {

      occ::handle<Geom_Curve> crv;
      double                  cf, cl;
      sae.Curve3d(sbwd->Edge(i), crv, cf, cl);
      B.UpdateVertex(V1, cl, E1, myAnalyzer.Precision());
      sae.Curve3d(sbwd->Edge(j), crv, cf, cl);
      B.UpdateVertex(V1, cf, E2, myAnalyzer.Precision());
    }

    V1.Orientation(E2.Orientation());
    B.Add(E2, V1);
    V1.Orientation(E1.Orientation());
    V1.Reverse();
    B.Add(E1, V1);
    myAnalyzer.SetSameVertex(i);
    nbfix++;
  }
  return nbfix;
}

int ShapeFix_WireVertex::Fix()
{

  if (!myAnalyzer.IsDone())
    return 0;

  occ::handle<ShapeExtend_WireData> sbwd = myAnalyzer.WireData();

  int i, nb = sbwd->NbEdges();
  int nbfix = 0;
  for (i = 1; i <= nb; i++)
  {

    if (myAnalyzer.Status(i) > 0)
      nbfix++;
  }
  if (nbfix == 0)
    return 0;

  BRep_Builder B;

  occ::handle<NCollection_HArray1<TopoDS_Shape>> VI = new NCollection_HArray1<TopoDS_Shape>(1, nb);
  occ::handle<NCollection_HArray1<TopoDS_Shape>> VJ = new NCollection_HArray1<TopoDS_Shape>(1, nb);
  occ::handle<NCollection_HArray1<TopoDS_Shape>> EF = new NCollection_HArray1<TopoDS_Shape>(1, nb);
  occ::handle<NCollection_HArray1<double>>       UI = new NCollection_HArray1<double>(1, nb);
  occ::handle<NCollection_HArray1<double>>       UJ = new NCollection_HArray1<double>(1, nb);

  for (i = 1; i <= nb; i++)
  {

    int j    = (i == nb ? 1 : i + 1);
    int stat = myAnalyzer.Status(i);

    ShapeAnalysis_Edge sae;
    TopoDS_Vertex      V1 = sae.LastVertex(sbwd->Edge(i));
    TopoDS_Vertex      V2 = sae.FirstVertex(sbwd->Edge(j));
    VI->SetValue(i, V1);
    VJ->SetValue(j, V2);

    TopoDS_Edge E = sbwd->Edge(i);

    EF->SetValue(i, E);

    double upre = myAnalyzer.UPrevious(i);
    double ufol = myAnalyzer.UFollowing(j);

    occ::handle<Geom_Curve> crv;
    double                  cf, cl;

    if (stat < 4)
    {
      sae.Curve3d(sbwd->Edge(i), crv, cf, cl);
      upre = cl;
    }
    if (stat < 3 || stat == 4)
    {
      sae.Curve3d(sbwd->Edge(j), crv, cf, cl);
      ufol = cf;
    }

    UI->SetValue(i, upre);
    UJ->SetValue(j, ufol);
  }

  if (nbfix == 0)
    return nbfix;

  for (i = 1; i <= nb; i++)
  {
    TopoDS_Edge   E1 = TopoDS::Edge(EF->Value(i));
    TopoDS_Vertex VA, VB;
    E1.Orientation(TopAbs_FORWARD);
    TopExp::Vertices(E1, VA, VB);
    E1.Free(true);
    B.Remove(E1, VA);
    B.Remove(E1, VB);
  }

  double Prec = myAnalyzer.Precision();
  for (i = 1; i <= nb; i++)
  {

    int j    = (i == nb ? 1 : i + 1);
    int stat = myAnalyzer.Status(i);

    TopoDS_Vertex V1   = TopoDS::Vertex(VI->Value(i));
    TopoDS_Vertex V2   = TopoDS::Vertex(VJ->Value(j));
    TopoDS_Edge   E1   = TopoDS::Edge(EF->Value(i));
    TopoDS_Edge   E2   = TopoDS::Edge(EF->Value(j));
    double        upre = UI->Value(i);
    double        ufol = UJ->Value(j);

    if (stat > 2)
      B.UpdateVertex(V1, gp_Pnt(myAnalyzer.Position(i)), Prec);

    if (stat > 0)
    {
      B.UpdateVertex(V1, upre, E1, Prec);
      B.UpdateVertex(V1, ufol, E2, Prec);
      V1.Orientation(TopAbs_FORWARD);
    }

    E2.Free(true);
    B.Add(E2, V1);
    V1.Orientation(TopAbs_REVERSED);

    E1.Free(true);
    B.Add(E1, V1);

    myAnalyzer.SetSameVertex(i);
  }

  for (i = 1; i <= nb; i++)
    sbwd->Set(TopoDS::Edge(EF->Value(i)), i);

  return nbfix;
}
