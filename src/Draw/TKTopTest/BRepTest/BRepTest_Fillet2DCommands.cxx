#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
#include <BRepTest.hpp>
#include <DBRep.hpp>
#include <Draw_Interpretor.hpp>
#include <Draw_Appli.hpp>
#include <BRepFilletAPI_MakeFillet2d.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopExp_Explorer.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>

#include <ChFi2d_FilletAPI.hpp>
#include <ChFi2d_ChamferAPI.hpp>

#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepBuilderAPI_FindPlane.hpp>
#include <BRep_Builder.hpp>

static int chfi2d(Draw_Interpretor& di, int n, const char** a)
{
  if (n < 3)
  {
    di << "chfi2d : not enough args";
    return 1;
  }

  TopoDS_Shape F = DBRep::Get(a[2], TopAbs_FACE);
  if (F.IsNull())
  {
    di << "chfi2d : " << a[2] << " not a face";
    return 1;
  }

  BRepFilletAPI_MakeFillet2d MF(TopoDS::Face(F));
  if (MF.Status() == ChFi2d_NotPlanar)
  {
    di << "chfi2d : not a planar face";
    return 1;
  }

  TopoDS_Shape res;
  bool         partial_result = false;
  int          i              = 3;
  while (i + 1 < n)
  {

    TopoDS_Shape aLocalEdge(DBRep::Get(a[i], TopAbs_EDGE));
    TopoDS_Edge  E1 = TopoDS::Edge(aLocalEdge);
    aLocalEdge      = DBRep::Get(a[i + 1], TopAbs_EDGE);
    TopoDS_Edge E2  = TopoDS::Edge(aLocalEdge);

    if (E1.IsNull() || E2.IsNull())
    {
      di << "chfi2d : " << a[i] << " or " << a[i + 1] << " not an edge";
      if (partial_result)
      {
        di << " WARNING : this is a partial result ";
        DBRep::Set(a[1], res);
      }
      return 1;
    }

    TopoDS_Vertex V;
    if (!TopExp::CommonVertex(E1, E2, V))
    {
      di << "chfi2d " << a[i] << " and " << a[i + 1] << " does not share a vertex";
      if (partial_result)
      {
        di << " WARNING : this is a partial result ";
        DBRep::Set(a[1], res);
      }
      return 1;
    }

    i += 2;
    if (i + 1 >= n)
    {
      di << "chfi2d : not enough args";
      if (partial_result)
      {
        di << " WARNING : this is a partial result ";
        DBRep::Set(a[1], res);
      }
      return 1;
    }

    double p1 = Draw::Atof(a[i + 1]);
    if (*a[i] == 'F')
    {
      MF.AddFillet(V, p1);
    }
    else
    {
      if (i + 2 >= n)
      {
        di << "chfi2d : not enough args";
        if (partial_result)
        {
          di << " WARNING : this is a partial result ";
          DBRep::Set(a[1], res);
        }
        return 1;
      }
      double p2 = Draw::Atof(a[i + 2]);
      if (a[i][2] == 'D')
      {
        MF.AddChamfer(E1, E2, p1, p2);
      }
      else
      {
        MF.AddChamfer(E1, V, p1, p2 * (M_PI / 180.0));
      }
    }

    if (MF.Status() == ChFi2d_TangencyError)
    {
      di << "chfi2d : " << a[i - 2] << " and " << a[i - 1] << " are tangent ";
      if (partial_result)
      {
        di << " WARNING : this is a partial result ";
        DBRep::Set(a[1], res);
      }
      return 1;
    }

    if (MF.Status() == ChFi2d_NotAuthorized)
    {
      di << "chfi2d : " << a[i - 2] << " or " << a[i - 1] << " is not a line or a circle ";
      if (partial_result)
      {
        di << " WARNING : this is a partial result ";
        DBRep::Set(a[1], res);
      }
      return 1;
    }

    if (MF.Status() != ChFi2d_IsDone)
    {
      di << "chfi2d : operation failed on " << a[i - 2];
      if (partial_result)
      {
        di << " WARNING : this is a partial result ";
        DBRep::Set(a[1], res);
      }
      return 1;
    }
    else
    {
      partial_result = true;
      MF.Build();
      res = MF.Shape();
    }

    if (*a[i] == 'F')
    {
      i += 2;
    }
    else
    {
      i += 3;
    }
  }

  MF.Build();
  DBRep::Set(a[1], MF);

  return 0;
}

static occ::handle<Geom_Plane> findPlane(const TopoDS_Shape& S)
{
  occ::handle<Geom_Plane>  plane;
  BRepBuilderAPI_FindPlane planeFinder(S);
  if (planeFinder.Found())
    plane = planeFinder.Plane();
  return plane;
}

static occ::handle<Geom_Plane> findPlane(const TopoDS_Shape& E1, const TopoDS_Shape& E2)
{
  BRep_Builder    B;
  TopoDS_Compound C;
  B.MakeCompound(C);
  B.Add(C, E1);
  B.Add(C, E2);
  return findPlane(C);
}

static gp_Pnt findCommonPoint(const TopoDS_Shape& E1, const TopoDS_Shape& E2)
{
  TopoDS_Vertex v11, v12, v21, v22;
  TopExp::Vertices(TopoDS::Edge(E1), v11, v12);
  TopExp::Vertices(TopoDS::Edge(E2), v21, v22);

  gp_Pnt p11 = BRep_Tool::Pnt(v11);
  gp_Pnt p12 = BRep_Tool::Pnt(v12);
  gp_Pnt p21 = BRep_Tool::Pnt(v21);
  gp_Pnt p22 = BRep_Tool::Pnt(v22);

  gp_Pnt       common;
  const double d1121 = p11.SquareDistance(p21);
  const double d1122 = p11.SquareDistance(p22);
  const double d1221 = p12.SquareDistance(p21);
  const double d1222 = p12.SquareDistance(p22);
  if (d1121 < d1122 && d1121 < d1221 && d1121 < d1222)
    common = p11;
  else if (d1122 < d1121 && d1122 < d1221 && d1122 < d1222)
    common = p11;
  else if (d1221 < d1121 && d1221 < d1122 && d1221 < d1222)
    common = p12;
  else if (d1222 < d1121 && d1222 < d1122 && d1222 < d1221)
    common = p12;

  return common;
}

static gp_Pnt findCommonPoint(const TopoDS_Shape& W)
{

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> vertices;
  TopExp_Explorer                                        aExp(W, TopAbs_VERTEX);
  for (; aExp.More(); aExp.Next())
  {
    if (!vertices.Add(aExp.Current()))
    {
      return BRep_Tool::Pnt(TopoDS::Vertex(aExp.Current()));
    }
  }
  return gp::Origin();
}

static int fillet2d(Draw_Interpretor& di, int n, const char** a)
{
  if (n != 4 && n != 5)
  {
    di << "Usage : fillet2d result wire (or edge1 edge2) radius";
    return 1;
  }

  TopoDS_Shape E1, E2, W;
  if (n == 5)
  {

    E1 = DBRep::Get(a[2], TopAbs_EDGE, true);
    E2 = DBRep::Get(a[3], TopAbs_EDGE, true);
  }
  else
  {

    W = DBRep::Get(a[2], TopAbs_WIRE, true);
  }

  const double radius = Atof(n == 5 ? a[4] : a[3]);

  occ::handle<Geom_Plane> hPlane = n == 5 ? findPlane(E1, E2) : findPlane(W);
  if (hPlane.IsNull())
  {
    di << "Error: the edges are located not in a plane.";
    return 1;
  }

  ChFi2d_FilletAPI algo;
  gp_Pln           plane = hPlane->Pln();
  if (n == 5)
  {
    const TopoDS_Edge& e1 = TopoDS::Edge(E1);
    const TopoDS_Edge& e2 = TopoDS::Edge(E2);
    algo.Init(e1, e2, plane);
  }
  else
  {
    const TopoDS_Wire& w = TopoDS::Wire(W);
    algo.Init(w, plane);
  }
  bool status = algo.Perform(radius);
  if (!status)
  {
    di << "Error: the algorithm failed.";
    return 1;
  }

  gp_Pnt common = n == 5 ? findCommonPoint(E1, E2) : findCommonPoint(W);

  int nbSolutions = algo.NbResults(common);
  if (!nbSolutions)
  {
    di << "Error: no solutions.";
    return 1;
  }

  TopoDS_Edge M1, M2;
  TopoDS_Edge fillet = algo.Result(common, M1, M2);
  if (fillet.IsNull())
  {
    di << "Error: the algorithm produced no result.";
    return 1;
  }

  DBRep::Set(a[1], fillet);

  if (n == 5)
  {
    DBRep::Set(a[2], M1);
    DBRep::Set(a[3], M2);
  }
  else
  {
    BRepBuilderAPI_MakeWire mkWire(M1, fillet, M2);
    if (mkWire.IsDone())
      DBRep::Set(a[1], mkWire.Wire());
    else
      DBRep::Set(a[1], fillet);
  }
  return 0;
}

static int chamfer2d(Draw_Interpretor& di, int n, const char** a)
{
  if (n != 5 && n != 6)
  {
    di << "Usage : chamfer2d result wire (or edge1 edge2) length1 length2";
    return 1;
  }

  TopoDS_Shape W;
  TopoDS_Shape E1, E2;
  if (n == 6)
  {

    E1 = DBRep::Get(a[2], TopAbs_EDGE, true);
    E2 = DBRep::Get(a[3], TopAbs_EDGE, true);
  }
  else
  {
    W = DBRep::Get(a[2], TopAbs_WIRE, true);
  }

  const double length1 = (n == 6) ? Atof(a[4]) : Atof(a[3]);
  const double length2 = (n == 6) ? Atof(a[5]) : Atof(a[4]);

  ChFi2d_ChamferAPI algo;
  if (n == 6)
  {
    const TopoDS_Edge& e1 = TopoDS::Edge(E1);
    const TopoDS_Edge& e2 = TopoDS::Edge(E2);
    algo.Init(e1, e2);
  }
  else
  {
    const TopoDS_Wire& w = TopoDS::Wire(W);
    algo.Init(w);
  }

  algo.Perform();

  TopoDS_Edge M1, M2;
  TopoDS_Edge chamfer = algo.Result(M1, M2, length1, length2);
  if (chamfer.IsNull())
  {
    di << "Error: the algorithm produced no result.";
    return 1;
  }

  if (n == 6)
  {

    DBRep::Set(a[1], chamfer);

    DBRep::Set(a[2], M1);
    DBRep::Set(a[3], M2);
  }
  else
  {
    BRepBuilderAPI_MakeWire mkWire(M1, chamfer, M2);
    if (mkWire.IsDone())
      DBRep::Set(a[1], mkWire.Wire());
    else
      DBRep::Set(a[1], chamfer);
  }

  return 0;
}

void BRepTest::Fillet2DCommands(Draw_Interpretor& theCommands)
{
  static bool done = false;
  if (done)
    return;
  done = true;

  DBRep::BasicCommands(theCommands);

  const char* g = "TOPOLOGY Fillet2D construction commands";

  theCommands.Add("chfi2d",
                  "chfi2d result face [edge1 edge2 (F radius/CDD d1 d2/CDA d ang) ....]",
                  __FILE__,
                  chfi2d,
                  g);
  theCommands.Add("fillet2d",
                  "fillet2d result wire (or edge1 edge2) radius",
                  __FILE__,
                  fillet2d,
                  g);
  theCommands.Add("chamfer2d",
                  "chamfer2d result wire (or edge1 edge2) length1 length2",
                  __FILE__,
                  chamfer2d,
                  g);
}
