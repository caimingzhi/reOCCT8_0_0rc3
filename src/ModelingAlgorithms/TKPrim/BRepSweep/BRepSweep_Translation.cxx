#include <BRepSweep_Translation.hpp>

#include <GeomAdaptor_SurfaceOfLinearExtrusion.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepTools.hpp>
#include <Geom2d_Line.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_Surface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>
#include <gp_Lin.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <Sweep_NumShape.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

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
    B.UpdateEdge(E, C, F, Precision::Confusion());
  else
  {
    if (O == TopAbs_REVERSED)
      B.UpdateEdge(E, OC, C, F, Precision::Confusion());
    else
      B.UpdateEdge(E, C, OC, F, Precision::Confusion());
  }
}

BRepSweep_Translation::BRepSweep_Translation(const TopoDS_Shape&    S,
                                             const Sweep_NumShape&  N,
                                             const TopLoc_Location& L,
                                             const gp_Vec&          V,
                                             const bool             C,
                                             const bool             Canonize)
    : BRepSweep_Trsf(BRep_Builder(), S, N, L, C),
      myVec(V),
      myCanonize(Canonize)
{

  Standard_ConstructionError_Raise_if(V.Magnitude() < Precision::Confusion(),
                                      "BRepSweep_Translation::Constructor");
  Init();
}

TopoDS_Shape BRepSweep_Translation::MakeEmptyVertex(const TopoDS_Shape&   aGenV,
                                                    const Sweep_NumShape& aDirV)
{

  Standard_ConstructionError_Raise_if(!myCopy, "BRepSweep_Translation::MakeEmptyVertex");
  gp_Pnt P = BRep_Tool::Pnt(TopoDS::Vertex(aGenV));
  if (aDirV.Index() == 2)
    P.Transform(myLocation.Transformation());
  TopoDS_Vertex V;

  myBuilder.Builder().MakeVertex(V, P, BRep_Tool::Tolerance(TopoDS::Vertex(aGenV)));

  return V;
}

TopoDS_Shape BRepSweep_Translation::MakeEmptyDirectingEdge(const TopoDS_Shape& aGenV,
                                                           const Sweep_NumShape&)
{
  gp_Pnt                 P = BRep_Tool::Pnt(TopoDS::Vertex(aGenV));
  gp_Lin                 L(P, myVec);
  occ::handle<Geom_Line> GL = new Geom_Line(L);
  TopoDS_Edge            E;
  myBuilder.Builder().MakeEdge(E, GL, BRep_Tool::Tolerance(TopoDS::Vertex(aGenV)));
  return E;
}

TopoDS_Shape BRepSweep_Translation::MakeEmptyGeneratingEdge(const TopoDS_Shape&   aGenE,
                                                            const Sweep_NumShape& aDirV)
{

  Standard_ConstructionError_Raise_if(!myCopy, "BRepSweep_Translation::MakeEmptyVertex");
  TopoDS_Edge newE;
  if (BRep_Tool::Degenerated(TopoDS::Edge(aGenE)))
  {
    myBuilder.Builder().MakeEdge(newE);
    myBuilder.Builder().UpdateEdge(newE, BRep_Tool::Tolerance(TopoDS::Edge(aGenE)));
    myBuilder.Builder().Degenerated(newE, true);
  }
  else
  {
    TopLoc_Location         L;
    double                  First, Last;
    occ::handle<Geom_Curve> C = BRep_Tool::Curve(TopoDS::Edge(aGenE), L, First, Last);
    if (!C.IsNull())
    {
      C = occ::down_cast<Geom_Curve>(C->Copy());
      C->Transform(L.Transformation());
      if (aDirV.Index() == 2)
        C->Transform(myLocation.Transformation());
    }
    myBuilder.Builder().MakeEdge(newE, C, BRep_Tool::Tolerance(TopoDS::Edge(aGenE)));
  }
  return newE;
}

void BRepSweep_Translation::SetParameters(const TopoDS_Shape& aNewFace,
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

void BRepSweep_Translation::SetDirectingParameter(const TopoDS_Shape& aNewEdge,
                                                  TopoDS_Shape&       aNewVertex,
                                                  const TopoDS_Shape&,
                                                  const Sweep_NumShape&,
                                                  const Sweep_NumShape& aDirV)
{
  double param = 0;
  if (aDirV.Index() == 2)
    param = myVec.Magnitude();
  myBuilder.Builder().UpdateVertex(TopoDS::Vertex(aNewVertex),
                                   param,
                                   TopoDS::Edge(aNewEdge),
                                   Precision::PConfusion());
}

void BRepSweep_Translation::SetGeneratingParameter(const TopoDS_Shape& aNewEdge,
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

TopoDS_Shape BRepSweep_Translation::MakeEmptyFace(const TopoDS_Shape&   aGenS,
                                                  const Sweep_NumShape& aDirS)
{
  double                    toler;
  TopoDS_Face               F;
  occ::handle<Geom_Surface> S;
  if (myDirShapeTool.Type(aDirS) == TopAbs_EDGE)
  {
    TopLoc_Location         L;
    double                  First, Last;
    occ::handle<Geom_Curve> C = BRep_Tool::Curve(TopoDS::Edge(aGenS), L, First, Last);
    toler                     = BRep_Tool::Tolerance(TopoDS::Edge(aGenS));
    gp_Trsf Tr                = L.Transformation();
    C                         = occ::down_cast<Geom_Curve>(C->Copy());

    C->Transform(Tr);
    gp_Dir D(myVec);
    D.Reverse();

    if (myCanonize)
    {
      occ::handle<GeomAdaptor_Curve>       HC = new GeomAdaptor_Curve(C, First, Last);
      GeomAdaptor_SurfaceOfLinearExtrusion AS(HC, D);
      switch (AS.GetType())
      {

        case GeomAbs_Plane:
          S = new Geom_Plane(AS.Plane());
          break;
        case GeomAbs_Cylinder:
          S = new Geom_CylindricalSurface(AS.Cylinder());
          break;
        default:
          S = new Geom_SurfaceOfLinearExtrusion(C, D);
          break;
      }
    }
    else
    {
      S = new Geom_SurfaceOfLinearExtrusion(C, D);
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
      S->Translate(myVec);
  }
  myBuilder.Builder().MakeFace(F, S, toler);
  return F;
}

void BRepSweep_Translation::SetPCurve(const TopoDS_Shape& aNewFace,
                                      TopoDS_Shape&       aNewEdge,
                                      const TopoDS_Shape& aGenF,
                                      const TopoDS_Shape& aGenE,
                                      const Sweep_NumShape&,
                                      const TopAbs_Orientation)
{

  bool isclosed = BRep_Tool::IsClosed(TopoDS::Edge(aGenE), TopoDS::Face(aGenF));
  if (isclosed)
  {
    double                    First, Last;
    TopoDS_Edge               anE = TopoDS::Edge(aGenE.Oriented(TopAbs_FORWARD));
    occ::handle<Geom2d_Curve> aC1 =
      BRep_Tool::CurveOnSurface(anE, TopoDS::Face(aGenF), First, Last);
    anE.Reverse();
    occ::handle<Geom2d_Curve> aC2 =
      BRep_Tool::CurveOnSurface(anE, TopoDS::Face(aGenF), First, Last);
    myBuilder.Builder().UpdateEdge(TopoDS::Edge(aNewEdge),
                                   aC1,
                                   aC2,
                                   TopoDS::Face(aNewFace),
                                   Precision::PConfusion());
  }
  else
  {
    double First, Last;
    myBuilder.Builder().UpdateEdge(
      TopoDS::Edge(aNewEdge),
      BRep_Tool::CurveOnSurface(TopoDS::Edge(aGenE), TopoDS::Face(aGenF), First, Last),
      TopoDS::Face(aNewFace),
      Precision::PConfusion());
  }
}

void BRepSweep_Translation::SetGeneratingPCurve(const TopoDS_Shape& aNewFace,
                                                TopoDS_Shape&       aNewEdge,
                                                const TopoDS_Shape&,
                                                const Sweep_NumShape&,
                                                const Sweep_NumShape&    aDirV,
                                                const TopAbs_Orientation orien)
{
  TopLoc_Location     Loc;
  GeomAdaptor_Surface AS(BRep_Tool::Surface(TopoDS::Face(aNewFace), Loc));

  gp_Lin2d    L;
  TopoDS_Edge aNewOrientedEdge = TopoDS::Edge(aNewEdge);
  aNewOrientedEdge.Orientation(orien);

  if (AS.GetType() == GeomAbs_Plane)
  {
  }
  else
  {
    double v = 0;
    if (aDirV.Index() == 2)
      v = -myVec.Magnitude();
    L.SetLocation(gp_Pnt2d(0, v));
    L.SetDirection(gp_Dir2d(gp_Dir2d::D::X));

    occ::handle<Geom2d_Line> GL = new Geom2d_Line(L);
    SetThePCurve(myBuilder.Builder(), TopoDS::Edge(aNewEdge), TopoDS::Face(aNewFace), orien, GL);
  }
}

void BRepSweep_Translation::SetDirectingPCurve(const TopoDS_Shape& aNewFace,
                                               TopoDS_Shape&       aNewEdge,
                                               const TopoDS_Shape& aGenE,
                                               const TopoDS_Shape& aGenV,
                                               const Sweep_NumShape&,
                                               const TopAbs_Orientation orien)
{
  TopLoc_Location     Loc;
  GeomAdaptor_Surface AS(BRep_Tool::Surface(TopoDS::Face(aNewFace), Loc));
  gp_Lin2d            L;
  if (AS.GetType() != GeomAbs_Plane)
  {
    L.SetLocation(gp_Pnt2d(BRep_Tool::Parameter(TopoDS::Vertex(aGenV), TopoDS::Edge(aGenE)), 0));
    L.SetDirection(gp_Dir2d(gp_Dir2d::D::NY));

    occ::handle<Geom2d_Line> GL = new Geom2d_Line(L);
    SetThePCurve(myBuilder.Builder(), TopoDS::Edge(aNewEdge), TopoDS::Face(aNewFace), orien, GL);
  }
}

TopAbs_Orientation BRepSweep_Translation::DirectSolid(const TopoDS_Shape& aGenS,
                                                      const Sweep_NumShape&)
{

  BRepAdaptor_Surface surf(TopoDS::Face(aGenS));
  gp_Pnt              P;
  gp_Vec              du, dv;
  surf.D1((surf.FirstUParameter() + surf.LastUParameter()) / 2.,
          (surf.FirstVParameter() + surf.LastVParameter()) / 2.,
          P,
          du,
          dv);

  double             x      = myVec.DotCross(du, dv);
  TopAbs_Orientation orient = (x > 0) ? TopAbs_REVERSED : TopAbs_FORWARD;
  return orient;
}

bool BRepSweep_Translation::GGDShapeIsToAdd(const TopoDS_Shape&,
                                            const TopoDS_Shape&,
                                            const TopoDS_Shape&,
                                            const TopoDS_Shape&,
                                            const Sweep_NumShape&) const
{
  return true;
}

bool BRepSweep_Translation::GDDShapeIsToAdd(const TopoDS_Shape&,
                                            const TopoDS_Shape&,
                                            const TopoDS_Shape&,
                                            const Sweep_NumShape&,
                                            const Sweep_NumShape&) const
{
  return true;
}

bool BRepSweep_Translation::SeparatedWires(const TopoDS_Shape&,
                                           const TopoDS_Shape&,
                                           const TopoDS_Shape&,
                                           const TopoDS_Shape&,
                                           const Sweep_NumShape&) const
{
  return false;
}

bool BRepSweep_Translation::HasShape(const TopoDS_Shape& aGenS, const Sweep_NumShape& aDirS) const
{
  if (myDirShapeTool.Type(aDirS) == TopAbs_EDGE)
  {

    if (myGenShapeTool.Type(aGenS) == TopAbs_EDGE)
    {
      TopoDS_Edge E = TopoDS::Edge(aGenS);

      if (BRep_Tool::Degenerated(E))
      {
        return false;
      }

      TopExp_Explorer FaceExp(myGenShape, TopAbs_FACE);
      for (; FaceExp.More(); FaceExp.Next())
      {
        TopoDS_Face F = TopoDS::Face(FaceExp.Current());
        if (BRepTools::IsReallyClosed(E, F))
          return false;
      }
    }
  }

  return true;
}

bool BRepSweep_Translation::IsInvariant(const TopoDS_Shape&) const
{
  return false;
}

gp_Vec BRepSweep_Translation::Vec() const
{
  return myVec;
}
