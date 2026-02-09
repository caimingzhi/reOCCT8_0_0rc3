#include <TopOpeBRepBuild_WireEdgeClassifier.hpp>

#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <BRepClass_FaceClassifier.hpp>
#include <Standard_ProgramError.hpp>
#include <gp_Vec2d.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <TopExp.hpp>

#include <TopOpeBRepTool_GEOMETRY.hpp>

#include <TopOpeBRepTool_PROJECT.hpp>

#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_SC.hpp>
#include <TopOpeBRepTool_TOOL.hpp>

#include <TopOpeBRepBuild_define.hpp>

#ifdef OCCT_DEBUG
static TCollection_AsciiString PRODINS("dins ");
#endif

#define MYBB ((TopOpeBRepBuild_BlockBuilder*)myBlockBuilder)

#define SAME (-1)
#define DIFF (-2)
#define UNKNOWN (0)
#define oneINtwo (1)
#define twoINone (2)

TopOpeBRepBuild_WireEdgeClassifier::TopOpeBRepBuild_WireEdgeClassifier(
  const TopoDS_Shape&                 F,
  const TopOpeBRepBuild_BlockBuilder& BB)
    : TopOpeBRepBuild_CompositeClassifier(BB)
{
  myBCEdge.Face() = TopoDS::Face(F);
}

TopAbs_State TopOpeBRepBuild_WireEdgeClassifier::Compare(
  const occ::handle<TopOpeBRepBuild_Loop>& L1,
  const occ::handle<TopOpeBRepBuild_Loop>& L2)
{
  TopAbs_State state = TopAbs_UNKNOWN;

  bool isshape1 = L1->IsShape();
  bool isshape2 = L2->IsShape();

  if (isshape2 && isshape1)
  {
    const TopoDS_Shape& s1 = L1->Shape();
    const TopoDS_Shape& s2 = L2->Shape();
    state                  = CompareShapes(s1, s2);
  }
  else if (isshape2 && !isshape1)
  {
    TopOpeBRepBuild_BlockIterator Bit1 = L1->BlockIterator();
    Bit1.Initialize();
    bool yena1 = Bit1.More();
    while (yena1)
    {
      const TopoDS_Shape& s1 = MYBB->Element(Bit1);
      const TopoDS_Shape& s2 = L2->Shape();
      state                  = CompareElementToShape(s1, s2);
      yena1                  = false;
      if (state == TopAbs_UNKNOWN)
      {
        if (Bit1.More())
          Bit1.Next();
        yena1 = Bit1.More();
      }
    }
  }
  else if (!isshape2 && isshape1)
  {
    const TopoDS_Shape& s1 = L1->Shape();
    ResetShape(s1);
    TopOpeBRepBuild_BlockIterator Bit2 = L2->BlockIterator();
    for (Bit2.Initialize(); Bit2.More(); Bit2.Next())
    {
      const TopoDS_Shape& s2 = MYBB->Element(Bit2);
      CompareElement(s2);
    }
    state = State();
  }
  else if (!isshape2 && !isshape1)
  {

    if (state == TopAbs_UNKNOWN)
    {
      TopOpeBRepBuild_BlockIterator Bit1 = L1->BlockIterator();
      Bit1.Initialize();
      bool yena1 = Bit1.More();
      while (yena1)
      {
        const TopoDS_Shape& s1 = MYBB->Element(Bit1);
        ResetElement(s1);
        TopOpeBRepBuild_BlockIterator Bit2 = L2->BlockIterator();
        for (Bit2.Initialize(); Bit2.More(); Bit2.Next())
        {
          const TopoDS_Shape& s2 = MYBB->Element(Bit2);
          CompareElement(s2);
        }
        state = State();
        yena1 = false;
        if (state == TopAbs_UNKNOWN)
        {
          if (Bit1.More())
            Bit1.Next();
          yena1 = Bit1.More();
        }
      }
    }

    if (state == TopAbs_UNKNOWN)
    {
      TopoDS_Shape s1 = LoopToShape(L1);
      if (s1.IsNull())
        return state;
      TopoDS_Shape s2 = LoopToShape(L2);
      if (s2.IsNull())
        return state;
      TopOpeBRepTool_ShapeClassifier& SC         = FSC_GetPSC();
      int                             samedomain = SC.SameDomain();
      SC.SameDomain(1);
      SC.SetReference(s2);
      const TopoDS_Shape& AvS = s2;
      state                   = SC.StateShapeReference(s1, AvS);
      SC.SameDomain(samedomain);
    }
  }
  return state;
}

TopoDS_Shape TopOpeBRepBuild_WireEdgeClassifier::LoopToShape(
  const occ::handle<TopOpeBRepBuild_Loop>& L)
{
  myShape.Nullify();
  TopOpeBRepBuild_BlockIterator Bit = L->BlockIterator();
  Bit.Initialize();
  if (!Bit.More())
    return myShape;

  TopoDS_Shape       aLocalShape = myBCEdge.Face();
  const TopoDS_Face& F1          = TopoDS::Face(aLocalShape);

  aLocalShape   = F1.EmptyCopied();
  TopoDS_Face F = TopoDS::Face(aLocalShape);

  BRep_Builder BB;
  TopoDS_Wire  W;
  BB.MakeWire(W);
  for (; Bit.More(); Bit.Next())
  {
    const TopoDS_Edge& E = TopoDS::Edge(MYBB->Element(Bit));
    double             tolE;
    tolE       = BRep_Tool::Tolerance(E);
    bool haspc = FC2D_HasCurveOnSurface(E, F);
    if (!haspc)
    {
      double                    f, l, tolpc;
      occ::handle<Geom2d_Curve> C2D;
      C2D = FC2D_CurveOnSurface(E, F, f, l, tolpc);
      if (!C2D.IsNull())
      {
        double tol = std::max(tolpc, tolE);
        BB.UpdateEdge(E, C2D, F, tol);
      }
    }
    BB.Add(W, E);
  }
  BB.Add(F, W);

  myShape = F;
  return myShape;
}

static gp_Vec FUN_tgINE(const TopoDS_Vertex& v, const TopoDS_Vertex& vl, const TopoDS_Edge& e)

{
  double par = BRep_Tool::Parameter(v, e);
  gp_Vec tg;
  bool   ok = TopOpeBRepTool_TOOL::TggeomE(par, e, tg);
  if (!ok)
    return gp_Vec(0., 0., 0.);
  if (v.IsSame(vl))
    tg.Reverse();
  return tg;
}

TopAbs_State TopOpeBRepBuild_WireEdgeClassifier::CompareShapes(const TopoDS_Shape& B1,
                                                               const TopoDS_Shape& B2)
{

#ifdef OCCT_DEBUG

#endif
  TopAbs_State    state = TopAbs_UNKNOWN;
  TopExp_Explorer ex1(B1, TopAbs_EDGE);
  if (!ex1.More())
    return state;
  for (; ex1.More(); ex1.Next())
  {
    const TopoDS_Edge& e1 = TopoDS::Edge(ex1.Current());
    TopoDS_Vertex      vf1, vl1;
    TopExp::Vertices(e1, vf1, vl1);
    bool                                                          e1clo = vf1.IsSame(vl1);
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mapv1;
    mapv1.Add(vf1);
    mapv1.Add(vl1);

    ResetShape(e1);
    bool            indy = false;
    TopExp_Explorer Ex;
    for (Ex.Init(B2, TopAbs_EDGE); Ex.More(); Ex.Next())
    {

      const TopoDS_Edge& E = TopoDS::Edge(Ex.Current());
      if (E.IsSame(e1))
      {
        state = TopAbs_UNKNOWN;
        break;
      }
      TopoDS_Vertex vf, vl;
      TopExp::Vertices(E, vf, vl);
      bool Eclo   = vf.IsSame(vl);
      bool hasf   = mapv1.Contains(vf);
      bool hasl   = mapv1.Contains(vl);
      bool filter = (hasf || hasl) && (!e1clo) && (!Eclo);
      if (filter)
      {
        TopoDS_Vertex vshared;
        if (hasf)
          vshared = vf;
        if (hasl)
          vshared = vl;
        gp_Vec tg1       = FUN_tgINE(vshared, vl1, e1);
        gp_Vec tg        = FUN_tgINE(vshared, vl, E);
        double dot       = tg1.Dot(tg);
        double tol       = Precision::Angular() * 1.e4;
        bool   undecided = (std::abs(1 + dot) < tol);
        if (undecided)
        {
          indy = true;
        }
      }
      if (indy)
      {
        state = TopAbs_UNKNOWN;
        break;
      }
      CompareElement(E);
      state = State();
    }
    if (state != TopAbs_UNKNOWN)
    {
      break;
    }
  }

  bool resta = (state == TopAbs_UNKNOWN);
  resta      = resta && (B2.ShapeType() == TopAbs_WIRE) && (B1.ShapeType() == TopAbs_WIRE);
  if (resta)
  {
    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mape1;
    TopExp::MapShapes(B1, TopAbs_EDGE, mape1);

    TopExp_Explorer ex2(B2, TopAbs_EDGE);
    for (; ex2.More(); ex2.Next())
    {
      const TopoDS_Edge& E2 = TopoDS::Edge(ex2.Current());
      if (mape1.Contains(E2))
        continue;

      const TopoDS_Face& theFace = myBCEdge.Face();
      BRep_Builder       BB;

      TopoDS_Shape aLocalShape = theFace.Oriented(TopAbs_FORWARD);
      TopoDS_Face  ftmp        = TopoDS::Face(aLocalShape);

      aLocalShape    = ftmp.EmptyCopied();
      TopoDS_Face F2 = TopoDS::Face(aLocalShape);

      BB.Add(F2, TopoDS::Wire(B2));

      BRepAdaptor_Curve2d BC2d(E2, F2);
      double              f, l;
      FUN_tool_bounds(E2, f, l);
      double   x   = 0.45678;
      double   p2  = (1 - x) * l + x * f;
      gp_Pnt2d p2d = BC2d.Value(p2);

      aLocalShape    = ftmp.EmptyCopied();
      TopoDS_Face F1 = TopoDS::Face(aLocalShape);

      BB.Add(F1, TopoDS::Wire(B1));

      double                   tolF1 = BRep_Tool::Tolerance(F1);
      BRepClass_FaceClassifier Fclass(F1, p2d, tolF1);
      state = Fclass.State();
      return state;
    }
  }

  return state;
}

TopAbs_State TopOpeBRepBuild_WireEdgeClassifier::CompareElementToShape(const TopoDS_Shape& EE,
                                                                       const TopoDS_Shape& B)
{

  ResetElement(EE);
  TopExp_Explorer Ex;
  for (Ex.Init(B, TopAbs_EDGE); Ex.More(); Ex.Next())
  {
    const TopoDS_Shape& E = Ex.Current();
    CompareElement(E);
  }
  TopAbs_State state = State();
  return state;
}

void TopOpeBRepBuild_WireEdgeClassifier::ResetShape(const TopoDS_Shape& B)
{
  if (B.ShapeType() == TopAbs_EDGE)
  {
    ResetElement(B);
  }
  else
  {
    TopExp_Explorer ex(B, TopAbs_EDGE);
    if (ex.More())
    {
      const TopoDS_Shape& E = ex.Current();
      ResetElement(E);
    }
  }
}

void TopOpeBRepBuild_WireEdgeClassifier::ResetElement(const TopoDS_Shape& EE)
{
  const TopoDS_Edge&        E = TopoDS::Edge(EE);
  const TopoDS_Face&        F = myBCEdge.Face();
  double                    f2, l2, tolpc;
  occ::handle<Geom2d_Curve> C2D;
  bool                      haspc = FC2D_HasCurveOnSurface(E, F);
  if (!haspc)
  {

    bool trim3d = true;
    C2D         = FC2D_CurveOnSurface(E, F, f2, l2, tolpc, trim3d);

    double       tolE = BRep_Tool::Tolerance(E);
    double       tol  = std::max(tolE, tolpc);
    BRep_Builder BB;
    BB.UpdateEdge(E, C2D, F, tol);
  }

  C2D = FC2D_CurveOnSurface(E, F, f2, l2, tolpc);
  if (C2D.IsNull())
    throw Standard_ProgramError("WEC : ResetElement");

  double t   = 0.397891143689;
  double par = ((1 - t) * f2 + t * l2);
  myPoint2d  = C2D->Value(par);

#ifdef OCCT_DEBUG
  double                  f3, l3;
  occ::handle<Geom_Curve> C3D = BRep_Tool::Curve(E, f3, l3);
  gp_Pnt                  P3D;
  if (!C3D.IsNull())
    P3D = C3D->Value(par);
#endif

  myFirstCompare = true;
}

bool TopOpeBRepBuild_WireEdgeClassifier::CompareElement(const TopoDS_Shape& EE)
{
  bool               bRet = true;
  const TopoDS_Edge& E    = TopoDS::Edge(EE);
  const TopoDS_Face& F    = myBCEdge.Face();

  double                    f2, l2, tolpc;
  occ::handle<Geom2d_Curve> C2D;
  bool                      haspc = FC2D_HasCurveOnSurface(E, F);
  if (!haspc)
  {

    bool trim3d = true;
    C2D         = FC2D_CurveOnSurface(E, F, f2, l2, tolpc, trim3d);

    double       tolE = BRep_Tool::Tolerance(E);
    double       tol  = std::max(tolE, tolpc);
    BRep_Builder BB;
    BB.UpdateEdge(E, C2D, F, tol);
  }

  if (myFirstCompare)
  {
    C2D          = FC2D_CurveOnSurface(E, F, f2, l2, tolpc);
    double   t   = 0.33334567;
    double   par = ((1 - t) * f2 + t * l2);
    gp_Pnt2d p2d = C2D->Value(par);

#ifdef OCCT_DEBUG
    double                  f3, l3;
    occ::handle<Geom_Curve> C3D = BRep_Tool::Curve(E, f3, l3);
    gp_Pnt                  P3D;
    if (!C3D.IsNull())
      P3D = C3D->Value(par);
#endif

    gp_Vec2d v2d(myPoint2d, p2d);
    gp_Lin2d l2d(myPoint2d, v2d);
    double   dist  = myPoint2d.Distance(p2d);
    double   tol2d = Precision::PConfusion();
    myFPC.Reset(l2d, dist, tol2d);
    myFirstCompare = false;
  }

  myBCEdge.Edge()         = E;
  TopAbs_Orientation Eori = E.Orientation();
  myFPC.Compare(myBCEdge, Eori);
#ifdef OCCT_DEBUG

#endif
  return bRet;
}

TopAbs_State TopOpeBRepBuild_WireEdgeClassifier::State()
{
  TopAbs_State state = myFPC.State();
  return state;
}
