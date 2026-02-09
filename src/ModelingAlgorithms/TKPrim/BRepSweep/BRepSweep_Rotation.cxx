#include <BRepSweep_Rotation.hpp>

#include <GeomAdaptor_SurfaceOfRevolution.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepTools.hpp>
#include <BRepTools_Quilt.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax3.hpp>
#include <gp_Ax22d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Cone.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>
#include <gp_Trsf.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Sweep_NumShape.hpp>
#include <TopExp.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <Geom_BSplineCurve.hpp>
#include <Geom_BezierCurve.hpp>

#include <TopExp_Explorer.hpp>

static double ComputeTolerance(TopoDS_Edge&                     E,
                               const TopoDS_Face&               F,
                               const occ::handle<Geom2d_Curve>& C)

{
  if (BRep_Tool::Degenerated(E))
    return BRep_Tool::Tolerance(E);

  double first, last;

  occ::handle<Geom_Surface> surf = BRep_Tool::Surface(F);
  occ::handle<Geom_Curve>   c3d  = BRep_Tool::Curve(E, first, last);

  double d2      = 0.;
  int    nn      = 23;
  double unsurnn = 1. / nn;
  for (int i = 0; i <= nn; i++)
  {
    double   t     = unsurnn * i;
    double   u     = first * (1. - t) + last * t;
    gp_Pnt   Pc3d  = c3d->Value(u);
    gp_Pnt2d UV    = C->Value(u);
    gp_Pnt   Pcons = surf->Value(UV.X(), UV.Y());
    if (Precision::IsInfinite(Pcons.X()) || Precision::IsInfinite(Pcons.Y())
        || Precision::IsInfinite(Pcons.Z()))
    {
      d2 = Precision::Infinite();
      break;
    }
    double temp = Pc3d.SquareDistance(Pcons);
    if (temp > d2)
      d2 = temp;
  }
  d2 = 1.5 * sqrt(d2);
  if (d2 < 1.e-7)
    d2 = 1.e-7;
  return d2;
}

static void SetThePCurve(const BRep_Builder&              B,
                         TopoDS_Edge&                     E,
                         const TopoDS_Face&               F,
                         const TopAbs_Orientation         O,
                         const occ::handle<Geom2d_Curve>& C)
{

  double                    f, l;
  occ::handle<Geom2d_Curve> OC;
  TopLoc_Location           SL;
  occ::handle<Geom_Plane>   GP = occ::down_cast<Geom_Plane>(BRep_Tool::Surface(F, SL));
  if (GP.IsNull())
    OC = BRep_Tool::CurveOnSurface(E, F, f, l);
  if (OC.IsNull())
    B.UpdateEdge(E, C, F, ComputeTolerance(E, F, C));
  else
  {
    if (O == TopAbs_REVERSED)
      B.UpdateEdge(E, OC, C, F, ComputeTolerance(E, F, C));
    else
      B.UpdateEdge(E, C, OC, F, ComputeTolerance(E, F, C));
  }
}

BRepSweep_Rotation::BRepSweep_Rotation(const TopoDS_Shape&    S,
                                       const Sweep_NumShape&  N,
                                       const TopLoc_Location& L,
                                       const gp_Ax1&          A,
                                       const double           D,
                                       const bool             C)
    : BRepSweep_Trsf(BRep_Builder(), S, N, L, C),
      myAng(D),
      myAxe(A)

{
  Standard_ConstructionError_Raise_if(D < Precision::Angular(), "BRepSweep_Rotation::Constructor");
  Init();
}

TopoDS_Shape BRepSweep_Rotation::MakeEmptyVertex(const TopoDS_Shape&   aGenV,
                                                 const Sweep_NumShape& aDirV)
{

  Standard_ConstructionError_Raise_if(!myCopy, "BRepSweep_Rotation::MakeEmptyVertex");
  gp_Pnt        P = BRep_Tool::Pnt(TopoDS::Vertex(aGenV));
  TopoDS_Vertex V;
  if (aDirV.Index() == 2)
    P.Transform(myLocation.Transformation());

  myBuilder.Builder().MakeVertex(V, P, BRep_Tool::Tolerance(TopoDS::Vertex(aGenV)));

  if (aDirV.Index() == 1 && IsInvariant(aGenV) && myDirShapeTool.NbShapes() == 3)
  {
    myBuiltShapes(myGenShapeTool.Index(aGenV), 3) = true;
    myShapes(myGenShapeTool.Index(aGenV), 3)      = V;
  }
  return V;
}

TopoDS_Shape BRepSweep_Rotation::MakeEmptyDirectingEdge(const TopoDS_Shape& aGenV,
                                                        const Sweep_NumShape&)
{
  TopoDS_Edge E;
  gp_Pnt      P = BRep_Tool::Pnt(TopoDS::Vertex(aGenV));
  gp_Dir      Dirz(myAxe.Direction());
  gp_Vec      V(Dirz);
  gp_Pnt      O(myAxe.Location());
  O.Translate(V.Dot(gp_Vec(O, P)) * V);
  if (O.IsEqual(P, Precision::Confusion()))
  {

    gp_Ax2                   Axis(O, Dirz);
    occ::handle<Geom_Circle> GC = new Geom_Circle(Axis, 0.);
    myBuilder.Builder().MakeEdge(E, GC, BRep_Tool::Tolerance(TopoDS::Vertex(aGenV)));
    myBuilder.Builder().Degenerated(E, true);
  }
  else
  {
    gp_Ax2                   Axis(O, Dirz, gp_Dir(gp_Vec(O, P)));
    occ::handle<Geom_Circle> GC  = new Geom_Circle(Axis, O.Distance(P));
    double                   tol = BRep_Tool::Tolerance(TopoDS::Vertex(aGenV));
    myBuilder.Builder().MakeEdge(E, GC, tol);
  }
  return E;
}

TopoDS_Shape BRepSweep_Rotation::MakeEmptyGeneratingEdge(const TopoDS_Shape&   aGenE,
                                                         const Sweep_NumShape& aDirV)
{

  TopoDS_Edge E;
  if (BRep_Tool::Degenerated(TopoDS::Edge(aGenE)))
  {
    myBuilder.Builder().MakeEdge(E);
    myBuilder.Builder().UpdateEdge(E, BRep_Tool::Tolerance(TopoDS::Edge(aGenE)));
    myBuilder.Builder().Degenerated(E, true);
  }
  else
  {
    double                  First, Last;
    TopLoc_Location         Loc;
    occ::handle<Geom_Curve> C =
      occ::down_cast<Geom_Curve>(BRep_Tool::Curve(TopoDS::Edge(aGenE), Loc, First, Last)->Copy());
    if (!C.IsNull())
    {
      C->Transform(Loc.Transformation());
      if (aDirV.Index() == 2)
        C->Transform(myLocation.Transformation());
    }
    myBuilder.Builder().MakeEdge(E, C, BRep_Tool::Tolerance(TopoDS::Edge(aGenE)));
  }
  if (aDirV.Index() == 1 && IsInvariant(aGenE) && myDirShapeTool.NbShapes() == 3)
  {
    myBuiltShapes(myGenShapeTool.Index(aGenE), 3) = true;
    myShapes(myGenShapeTool.Index(aGenE), 3)      = E;
  }
  return E;
}

void BRepSweep_Rotation::SetParameters(const TopoDS_Shape& aNewFace,
                                       TopoDS_Shape&       aNewVertex,
                                       const TopoDS_Shape& aGenF,
                                       const TopoDS_Shape& aGenV,
                                       const Sweep_NumShape&)
{

  gp_Pnt2d pnt2d = BRep_Tool::Parameters(TopoDS::Vertex(aGenV), TopoDS::Face(aGenF));
  myBuilder.Builder().UpdateVertex(TopoDS::Vertex(aNewVertex),
                                   pnt2d.X(),
                                   pnt2d.Y(),
                                   TopoDS::Face(aNewFace),
                                   Precision::PConfusion());
}

void BRepSweep_Rotation::SetDirectingParameter(const TopoDS_Shape& aNewEdge,
                                               TopoDS_Shape&       aNewVertex,
                                               const TopoDS_Shape&,
                                               const Sweep_NumShape&,
                                               const Sweep_NumShape& aDirV)
{
  double             param = 0;
  TopAbs_Orientation ori   = TopAbs_FORWARD;
  if (aDirV.Index() == 2)
  {
    param = myAng;
    ori   = TopAbs_REVERSED;
  }
  TopoDS_Vertex V_wnt = TopoDS::Vertex(aNewVertex);
  V_wnt.Orientation(ori);
  myBuilder.Builder().UpdateVertex(V_wnt, param, TopoDS::Edge(aNewEdge), Precision::PConfusion());
}

void BRepSweep_Rotation::SetGeneratingParameter(const TopoDS_Shape& aNewEdge,
                                                TopoDS_Shape&       aNewVertex,
                                                const TopoDS_Shape& aGenE,
                                                const TopoDS_Shape& aGenV,
                                                const Sweep_NumShape&)
{
  TopoDS_Vertex vbid = TopoDS::Vertex(aNewVertex);
  vbid.Orientation(aGenV.Orientation());
  myBuilder.Builder().UpdateVertex(vbid,
                                   BRep_Tool::Parameter(TopoDS::Vertex(aGenV), TopoDS::Edge(aGenE)),
                                   TopoDS::Edge(aNewEdge),
                                   Precision::PConfusion());
}

TopoDS_Shape BRepSweep_Rotation::MakeEmptyFace(const TopoDS_Shape&   aGenS,
                                               const Sweep_NumShape& aDirS)
{
  double                    toler;
  TopoDS_Face               F;
  occ::handle<Geom_Surface> S;
  if (aGenS.ShapeType() == TopAbs_EDGE)
  {
    TopLoc_Location         L;
    double                  First, Last;
    occ::handle<Geom_Curve> C = BRep_Tool::Curve(TopoDS::Edge(aGenS), L, First, Last);
    toler                     = BRep_Tool::Tolerance(TopoDS::Edge(aGenS));
    gp_Trsf Tr                = L.Transformation();
    C                         = occ::down_cast<Geom_Curve>(C->Copy());

    C = new Geom_TrimmedCurve(C, First, Last);

    C->Transform(Tr);

    occ::handle<GeomAdaptor_Curve> HC = new GeomAdaptor_Curve();
    HC->Load(C, First, Last);
    GeomAdaptor_SurfaceOfRevolution AS(HC, myAxe);
    switch (AS.GetType())
    {
      case GeomAbs_Plane:
      {
        occ::handle<Geom_Plane> Pl = new Geom_Plane(AS.Plane());
        S                          = Pl;
      }
      break;
      case GeomAbs_Cylinder:
      {
        occ::handle<Geom_CylindricalSurface> Cy = new Geom_CylindricalSurface(AS.Cylinder());
        S                                       = Cy;
      }
      break;
      case GeomAbs_Sphere:
      {
        occ::handle<Geom_SphericalSurface> Sp = new Geom_SphericalSurface(AS.Sphere());
        S                                     = Sp;
      }
      break;
      case GeomAbs_Cone:
      {
        occ::handle<Geom_ConicalSurface> Co = new Geom_ConicalSurface(AS.Cone());
        S                                   = Co;
      }
      break;
      case GeomAbs_Torus:
      {
        occ::handle<Geom_ToroidalSurface> To = new Geom_ToroidalSurface(AS.Torus());
        S                                    = To;
      }
      break;
      default:
      {
        occ::handle<Geom_SurfaceOfRevolution> Se = new Geom_SurfaceOfRevolution(C, myAxe);
        S                                        = Se;
      }
      break;
    }
  }
  else
  {
    TopLoc_Location L;
    S          = BRep_Tool::Surface(TopoDS::Face(aGenS), L);
    toler      = BRep_Tool::Tolerance(TopoDS::Face(aGenS));
    gp_Trsf Tr = L.Transformation();
    S          = occ::down_cast<Geom_Surface>(S->Copy());
    S->Transform(Tr);
    if (aDirS.Index() == 2)
      S->Transform(myLocation.Transformation());
  }
  myBuilder.Builder().MakeFace(F, S, toler);
  return F;
}

void BRepSweep_Rotation::SetPCurve(const TopoDS_Shape& aNewFace,
                                   TopoDS_Shape&       aNewEdge,
                                   const TopoDS_Shape& aGenF,
                                   const TopoDS_Shape& aGenE,
                                   const Sweep_NumShape&,
                                   const TopAbs_Orientation orien)
{

  double First, Last;
  SetThePCurve(myBuilder.Builder(),
               TopoDS::Edge(aNewEdge),
               TopoDS::Face(aNewFace),
               orien,
               BRep_Tool::CurveOnSurface(TopoDS::Edge(aGenE), TopoDS::Face(aGenF), First, Last));
}

void BRepSweep_Rotation::SetGeneratingPCurve(const TopoDS_Shape& aNewFace,
                                             TopoDS_Shape&       aNewEdge,
                                             const TopoDS_Shape&,
                                             const Sweep_NumShape&,
                                             const Sweep_NumShape&    aDirV,
                                             const TopAbs_Orientation orien)
{
  TopLoc_Location     Loc;
  GeomAdaptor_Surface AS(BRep_Tool::Surface(TopoDS::Face(aNewFace), Loc));
  double              First, Last;
  double              u, v;
  gp_Pnt              point;
  gp_Pnt2d            pnt2d;
  gp_Dir2d            dir2d;
  gp_Lin2d            L;
  if (AS.GetType() == GeomAbs_Plane)
  {
    gp_Pln                  pln = AS.Plane();
    gp_Ax3                  ax3 = pln.Position();
    occ::handle<Geom_Curve> aC  = BRep_Tool::Curve(TopoDS::Edge(aNewEdge), Loc, First, Last);
    occ::handle<Geom_Line>  GL  = occ::down_cast<Geom_Line>(aC);
    if (GL.IsNull())
    {
      occ::handle<Geom_TrimmedCurve> aTrimmedCurve = occ::down_cast<Geom_TrimmedCurve>(aC);
      if (!aTrimmedCurve.IsNull())
      {
        GL = occ::down_cast<Geom_Line>(aTrimmedCurve->BasisCurve());
        if (GL.IsNull())
        {
          throw Standard_ConstructionError("BRepSweep_Rotation::SetGeneratingPCurve");
        }
      }
    }
    gp_Lin gl = GL->Lin();
    gl.Transform(Loc.Transformation());
    point      = gl.Location();
    gp_Dir dir = gl.Direction();
    ElSLib::PlaneParameters(ax3, point, u, v);
    pnt2d.SetCoord(u, v);
    dir2d.SetCoord(dir.Dot(ax3.XDirection()), dir.Dot(ax3.YDirection()));
    L.SetLocation(pnt2d);
    L.SetDirection(dir2d);
  }
  else if (AS.GetType() == GeomAbs_Torus)
  {
    gp_Torus          tor = AS.Torus();
    BRepAdaptor_Curve BC(TopoDS::Edge(aNewEdge));
    double            U = BC.FirstParameter();
    point               = BC.Value(U);
    if (point.Distance(tor.Location()) < Precision::Confusion())
    {
      v = M_PI;

      u = 0.;
    }
    else
    {
      ElSLib::TorusParameters(tor.Position(), tor.MajorRadius(), tor.MinorRadius(), point, u, v);
    }

    v = ElCLib::InPeriod(v, 0., 2 * M_PI);
    if ((2 * M_PI - v) <= Precision::PConfusion())
      v -= 2 * M_PI;
    if (aDirV.Index() == 2)
    {
      double uLeft = u - myAng;
      ElCLib::AdjustPeriodic(-M_PI, M_PI, Precision::PConfusion(), uLeft, u);
    }
    else
    {
      double uRight = u + myAng;
      ElCLib::AdjustPeriodic(-M_PI, M_PI, Precision::PConfusion(), u, uRight);
    }

    pnt2d.SetCoord(u, v - U);
    L.SetLocation(pnt2d);
    L.SetDirection(gp::DY2d());
  }
  else if (AS.GetType() == GeomAbs_Sphere)
  {
    gp_Sphere         sph = AS.Sphere();
    BRepAdaptor_Curve BC(TopoDS::Edge(aNewEdge));
    double            U = BC.FirstParameter();
    point               = BC.Value(U);
    ElSLib::SphereParameters(sph.Position(), sph.Radius(), point, u, v);
    u = 0.;
    if (aDirV.Index() == 2)
      u = myAng;
    pnt2d.SetCoord(u, v - U);
    L.SetLocation(pnt2d);
    L.SetDirection(gp::DY2d());
  }
  else
  {
    double anAngleTemp = 0;
    if (aDirV.Index() == 2)
      anAngleTemp = myAng;
    L.SetLocation(gp_Pnt2d(anAngleTemp, 0));
    L.SetDirection(gp::DY2d());
  }
  occ::handle<Geom2d_Line> GL = new Geom2d_Line(L);
  SetThePCurve(myBuilder.Builder(), TopoDS::Edge(aNewEdge), TopoDS::Face(aNewFace), orien, GL);
}

void BRepSweep_Rotation::SetDirectingPCurve(const TopoDS_Shape& aNewFace,
                                            TopoDS_Shape&       aNewEdge,
                                            const TopoDS_Shape& aGenE,
                                            const TopoDS_Shape& aGenV,
                                            const Sweep_NumShape&,
                                            const TopAbs_Orientation orien)
{
  TopLoc_Location           Loc;
  GeomAdaptor_Surface       AS(BRep_Tool::Surface(TopoDS::Face(aNewFace), Loc));
  double                    par = BRep_Tool::Parameter(TopoDS::Vertex(aGenV), TopoDS::Edge(aGenE));
  gp_Pnt                    p2  = BRep_Tool::Pnt(TopoDS::Vertex(aGenV));
  gp_Pnt2d                  p22d;
  double                    u, v;
  occ::handle<Geom2d_Curve> thePCurve;

  switch (AS.GetType())
  {

    case GeomAbs_Plane:
    {
      gp_Pln pln = AS.Plane();
      gp_Ax3 ax3 = pln.Position();
      gp_Pnt p1  = pln.Location();
      double R   = p1.Distance(p2);
      ElSLib::PlaneParameters(ax3, p2, u, v);
      gp_Dir2d                   dx2d(u, v);
      gp_Ax22d                   axe(gp::Origin2d(), dx2d, gp::DY2d());
      gp_Circ2d                  C(axe, R);
      occ::handle<Geom2d_Circle> GC = new Geom2d_Circle(C);
      thePCurve                     = GC;
    }
    break;

    case GeomAbs_Cone:
    {
      gp_Cone cone = AS.Cone();
      ElSLib::ConeParameters(cone.Position(), cone.RefRadius(), cone.SemiAngle(), p2, u, v);
      p22d.SetCoord(0., v);
      gp_Lin2d                 L(p22d, gp::DX2d());
      occ::handle<Geom2d_Line> GL = new Geom2d_Line(L);
      thePCurve                   = GL;
    }
    break;

    case GeomAbs_Sphere:
    {
      gp_Sphere sph = AS.Sphere();
      ElSLib::SphereParameters(sph.Position(), sph.Radius(), p2, u, v);
      p22d.SetCoord(0., v);
      gp_Lin2d                 L(p22d, gp::DX2d());
      occ::handle<Geom2d_Line> GL = new Geom2d_Line(L);
      thePCurve                   = GL;
    }
    break;

    case GeomAbs_Torus:
    {
      gp_Pnt            p1;
      double            u1, u2, v1, v2;
      gp_Torus          tor = AS.Torus();
      BRepAdaptor_Curve BC(TopoDS::Edge(aGenE));
      p1 = BC.Value(BC.FirstParameter());
      if (p1.Distance(tor.Location()) < Precision::Confusion())
      {
        v1 = M_PI;

        u1 = 0.;
      }
      else
      {
        ElSLib::TorusParameters(tor.Position(), tor.MajorRadius(), tor.MinorRadius(), p1, u1, v1);
      }
      p2 = BC.Value(BC.LastParameter());
      if (p2.Distance(tor.Location()) < Precision::Confusion())
      {
        v2 = M_PI;
      }
      else
      {
        ElSLib::TorusParameters(tor.Position(), tor.MajorRadius(), tor.MinorRadius(), p2, u2, v2);
      }
      ElCLib::AdjustPeriodic(0., 2 * M_PI, Precision::PConfusion(), v1, v2);

      u2 = u1 + myAng;
      ElCLib::AdjustPeriodic(-M_PI, M_PI, Precision::PConfusion(), u1, u2);
      if (aGenV.Orientation() == TopAbs_FORWARD)
      {
        p22d.SetCoord(u1, v1);
      }
      else
      {
        p22d.SetCoord(u1, v2);
      }
      gp_Lin2d                 L(p22d, gp::DX2d());
      occ::handle<Geom2d_Line> GL = new Geom2d_Line(L);
      thePCurve                   = GL;
    }
    break;

    default:
    {
      p22d.SetCoord(0., par);
      gp_Lin2d                 L(p22d, gp::DX2d());
      occ::handle<Geom2d_Line> GL = new Geom2d_Line(L);
      thePCurve                   = GL;
    }
    break;
  }
  SetThePCurve(myBuilder.Builder(),
               TopoDS::Edge(aNewEdge),
               TopoDS::Face(aNewFace),
               orien,
               thePCurve);
}

TopAbs_Orientation BRepSweep_Rotation::DirectSolid(const TopoDS_Shape& aGenS, const Sweep_NumShape&)
{
  double              aU1, aU2, aV1, aV2, aUx, aVx, aX, aMV2, aTol2, aTx;
  TopAbs_Orientation  aOr;
  gp_Pnt              aP;
  gp_Vec              du, dv;
  BRepAdaptor_Surface surf(TopoDS::Face(aGenS));

  aTol2 = Precision::Confusion();
  aTol2 = aTol2 * aTol2;

  const gp_Pnt& aPAxeLoc = myAxe.Location();
  const gp_Dir& aPAxeDir = myAxe.Direction();

  aU1 = surf.FirstUParameter();
  aU2 = surf.LastUParameter();
  aV1 = surf.FirstVParameter();
  aV2 = surf.LastVParameter();

  aTx = 0.5;
  aUx = aTx * (aU1 + aU2);
  aVx = aTx * (aV1 + aV2);
  surf.D1(aUx, aVx, aP, du, dv);

  gp_Vec aV(aPAxeLoc, aP);
  aV.Cross(aPAxeDir);
  aMV2 = aV.SquareMagnitude();
  if (aMV2 < aTol2)
  {
    aTx = 0.43213918;
    aUx = aU1 * (1. - aTx) + aU2 * aTx;
    aVx = aV1 * (1. - aTx) + aV2 * aTx;
    surf.D1(aUx, aVx, aP, du, dv);
    aV.SetXYZ(aP.XYZ() - aPAxeLoc.XYZ());
    aV.Cross(aPAxeDir);
  }

  aX  = aV.DotCross(du, dv);
  aOr = (aX > 0.) ? TopAbs_FORWARD : TopAbs_REVERSED;
  return aOr;
}

bool BRepSweep_Rotation::GGDShapeIsToAdd(const TopoDS_Shape&   aNewShape,
                                         const TopoDS_Shape&   aNewSubShape,
                                         const TopoDS_Shape&   aGenS,
                                         const TopoDS_Shape&   aSubGenS,
                                         const Sweep_NumShape& aDirS) const
{
  bool aRes = true;
  if (aNewShape.ShapeType() == TopAbs_FACE && aNewSubShape.ShapeType() == TopAbs_EDGE
      && aGenS.ShapeType() == TopAbs_EDGE && aSubGenS.ShapeType() == TopAbs_VERTEX
      && aDirS.Type() == TopAbs_EDGE)
  {
    TopLoc_Location     Loc;
    GeomAdaptor_Surface AS(BRep_Tool::Surface(TopoDS::Face(aNewShape), Loc));
    if (AS.GetType() == GeomAbs_Plane)
    {
      return (!IsInvariant(aSubGenS));
    }
    else
    {
      return aRes;
    }
  }
  else
  {
    return aRes;
  }
}

bool BRepSweep_Rotation::GDDShapeIsToAdd(const TopoDS_Shape&   aNewShape,
                                         const TopoDS_Shape&   aNewSubShape,
                                         const TopoDS_Shape&   aGenS,
                                         const Sweep_NumShape& aDirS,
                                         const Sweep_NumShape& aSubDirS) const
{
  if (aNewShape.ShapeType() == TopAbs_SOLID && aNewSubShape.ShapeType() == TopAbs_FACE
      && aGenS.ShapeType() == TopAbs_FACE && aDirS.Type() == TopAbs_EDGE
      && aSubDirS.Type() == TopAbs_VERTEX)
  {
    return (std::abs(myAng - 2 * M_PI) > Precision::Angular());
  }
  else if (aNewShape.ShapeType() == TopAbs_FACE && aNewSubShape.ShapeType() == TopAbs_EDGE
           && aGenS.ShapeType() == TopAbs_EDGE && aDirS.Type() == TopAbs_EDGE
           && aSubDirS.Type() == TopAbs_VERTEX)
  {
    TopLoc_Location     Loc;
    GeomAdaptor_Surface AS(BRep_Tool::Surface(TopoDS::Face(aNewShape), Loc));
    if (AS.GetType() == GeomAbs_Plane)
    {
      return (std::abs(myAng - 2 * M_PI) > Precision::Angular());
    }
    else
    {
      return true;
    }
  }
  else
  {
    return true;
  }
}

bool BRepSweep_Rotation::SeparatedWires(const TopoDS_Shape&   aNewShape,
                                        const TopoDS_Shape&   aNewSubShape,
                                        const TopoDS_Shape&   aGenS,
                                        const TopoDS_Shape&   aSubGenS,
                                        const Sweep_NumShape& aDirS) const
{
  if (aNewShape.ShapeType() == TopAbs_FACE && aNewSubShape.ShapeType() == TopAbs_EDGE
      && aGenS.ShapeType() == TopAbs_EDGE && aSubGenS.ShapeType() == TopAbs_VERTEX
      && aDirS.Type() == TopAbs_EDGE)
  {
    TopLoc_Location     Loc;
    GeomAdaptor_Surface AS(BRep_Tool::Surface(TopoDS::Face(aNewShape), Loc));
    if (AS.GetType() == GeomAbs_Plane)
    {
      return (std::abs(myAng - 2 * M_PI) <= Precision::Angular());
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

TopoDS_Shape BRepSweep_Rotation::SplitShell(const TopoDS_Shape& aNewShape) const
{
  BRepTools_Quilt Q;
  Q.Add(aNewShape);
  return Q.Shells();
}

bool BRepSweep_Rotation::HasShape(const TopoDS_Shape& aGenS, const Sweep_NumShape& aDirS) const
{
  if (aDirS.Type() == TopAbs_EDGE && aGenS.ShapeType() == TopAbs_EDGE)
  {

    const TopoDS_Edge& anEdge = TopoDS::Edge(aGenS);

    if (BRep_Tool::Degenerated(anEdge))
      return false;

    double                  aPFirst, aPLast;
    TopLoc_Location         aLoc;
    occ::handle<Geom_Curve> aCurve = BRep_Tool::Curve(anEdge, aLoc, aPFirst, aPLast);
    if (aCurve.IsNull())
      return false;

    if (IsInvariant(aGenS))
      return false;

    TopExp_Explorer FaceExp(myGenShape, TopAbs_FACE);
    for (; FaceExp.More(); FaceExp.Next())
    {
      TopoDS_Face F = TopoDS::Face(FaceExp.Current());
      if (BRepTools::IsReallyClosed(anEdge, F))
        return false;
    }

    return true;
  }
  else
  {
    return true;
  }
}

bool BRepSweep_Rotation::IsInvariant(const TopoDS_Shape& aGenS) const
{
  if (aGenS.ShapeType() == TopAbs_EDGE)
  {
    BRepAdaptor_Curve aC(TopoDS::Edge(aGenS));
    if (aC.GetType() == GeomAbs_Line || aC.GetType() == GeomAbs_BSplineCurve
        || aC.GetType() == GeomAbs_BezierCurve)
    {
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(TopoDS::Edge(aGenS), V1, V2);
      if (IsInvariant(V1) && IsInvariant(V2))
      {
        if (aC.GetType() == GeomAbs_Line)
          return true;

        double aTol = std::max(BRep_Tool::Tolerance(V1), BRep_Tool::Tolerance(V2));
        gp_Lin Lin(myAxe.Location(), myAxe.Direction());
        const NCollection_Array1<gp_Pnt>& aPoles =
          (aC.GetType() == GeomAbs_BSplineCurve ? aC.BSpline()->Poles() : aC.Bezier()->Poles());

        for (int i = aPoles.Lower(); i <= aPoles.Upper(); i++)
        {
          if (Lin.Distance(aPoles(i)) > aTol)
            return false;
        }
        return true;
      }
    }
  }
  else if (aGenS.ShapeType() == TopAbs_VERTEX)
  {
    gp_Pnt P = BRep_Tool::Pnt(TopoDS::Vertex(aGenS));
    gp_Lin Lin(myAxe.Location(), myAxe.Direction());
    return (Lin.Distance(P) <= BRep_Tool::Tolerance(TopoDS::Vertex(aGenS)));
  }
  return false;
}

double BRepSweep_Rotation::Angle() const
{
  return myAng;
}

gp_Ax1 BRepSweep_Rotation::Axe() const
{
  return myAxe;
}
