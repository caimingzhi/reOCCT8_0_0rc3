#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAlgo_FaceRestrictor.hpp>
#include <BRepTopAdaptor_FClass2d.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom_Curve.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomProjLib.hpp>
#include <gp_Pnt2d.hpp>
#include <Precision.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopOpeBRepBuild_WireToFace.hpp>

BRepAlgo_FaceRestrictor::BRepAlgo_FaceRestrictor() = default;

void BRepAlgo_FaceRestrictor::Init(const TopoDS_Face& F,
                                   const bool         Proj,
                                   const bool         CorrectionOrientation)
{
  myFace       = F;
  modeProj     = Proj;
  myCorrection = CorrectionOrientation;
}

void BRepAlgo_FaceRestrictor::Add(TopoDS_Wire& W)
{
  wires.Append(W);
}

void BRepAlgo_FaceRestrictor::Clear()
{
  wires.Clear();
  faces.Clear();
}

static bool ChangePCurve(TopoDS_Edge& E, const occ::handle<Geom_Surface>& S, TopLoc_Location& L)
{
  BRep_Builder              BB;
  occ::handle<Geom_Surface> SE;
  occ::handle<Geom2d_Curve> C2;
  TopLoc_Location           LE;
  double                    f, l;

  BRep_Tool::CurveOnSurface(E, C2, SE, LE, f, l, 1);
  if (!C2.IsNull())
    BB.UpdateEdge(E, C2, S, L, Precision::Confusion());
  return (C2.IsNull());
}

static bool ProjCurve3d(TopoDS_Edge& E, const occ::handle<Geom_Surface>& S, TopLoc_Location& L)
{
  BRep_Builder            BB;
  TopLoc_Location         LE;
  double                  f, l;
  occ::handle<Geom_Curve> C = BRep_Tool::Curve(E, LE, f, l);
  if (C.IsNull())
  {
    return false;
  }
  occ::handle<Geom_TrimmedCurve> CT = new Geom_TrimmedCurve(C, f, l);

  TopLoc_Location LL = L.Inverted().Multiplied(LE);
  CT->Transform(LL.Transformation());

  occ::handle<Geom2d_Curve> C2 = GeomProjLib::Curve2d(CT, S);
  BB.UpdateEdge(E, C2, S, L, Precision::Confusion());
  return true;
}

void BRepAlgo_FaceRestrictor::Perform()
{

  if (myCorrection)
  {
    PerformWithCorrection();
    return;
  }

  myDone = false;
  NCollection_List<TopoDS_Shape>::Iterator it(wires);

  TopLoc_Location                  L;
  const occ::handle<Geom_Surface>& S = BRep_Tool::Surface(myFace, L);

  TopExp_Explorer Exp;

  double f, l;

  TopOpeBRepBuild_WireToFace WTF;

  for (; it.More(); it.Next())
  {

    const TopoDS_Wire& W = TopoDS::Wire(it.Value());

    for (Exp.Init(W, TopAbs_EDGE); Exp.More(); Exp.Next())
    {

      TopoDS_Edge               E  = TopoDS::Edge(Exp.Current());
      occ::handle<Geom2d_Curve> C2 = BRep_Tool::CurveOnSurface(E, S, L, f, l);

      if (C2.IsNull())
      {

        if (modeProj)
        {

          if (!ProjCurve3d(E, S, L))
          {
            return;
          }
        }
        else
        {

          bool YaPCurve = ChangePCurve(E, S, L);
          if (!YaPCurve)
          {
            if (!ProjCurve3d(E, S, L))
            {
              return;
            }
          }
        }
      }
    }
    WTF.AddWire(W);
  }

  WTF.MakeFaces(myFace, faces);

  myDone = true;
}

bool BRepAlgo_FaceRestrictor::IsDone() const
{
  return myDone;
}

bool BRepAlgo_FaceRestrictor::More() const
{
  return (!faces.IsEmpty());
}

void BRepAlgo_FaceRestrictor::Next()
{
  faces.RemoveFirst();
}

TopoDS_Face BRepAlgo_FaceRestrictor::Current() const
{
  return (TopoDS::Face(faces.First()));
}

static bool IsClosed(const TopoDS_Wire& W)

{
  if (W.Closed())
    return true;
  TopoDS_Vertex V1, V2;
  TopExp::Vertices(W, V1, V2);
  return (V1.IsSame(V2));
}

static bool IsInside(const TopoDS_Wire& wir, const TopoDS_Face& F, BRepTopAdaptor_FClass2d&)
{
  TopExp_Explorer exp;
  exp.Init(wir, TopAbs_EDGE);
  if (exp.More())
  {
    const TopoDS_Edge&        edg = TopoDS::Edge(exp.Current());
    double                    f, l;
    occ::handle<Geom2d_Curve> C2d = BRep_Tool::CurveOnSurface(edg, F, f, l);
    double                    prm;

    if (!Precision::IsNegativeInfinite(f) && !Precision::IsPositiveInfinite(l))
    {
      prm = (f + l) / 2.;
    }
    else
    {
      if (Precision::IsNegativeInfinite(f) && Precision::IsPositiveInfinite(l))
      {
        prm = 0.;
      }
      else if (Precision::IsNegativeInfinite(f))
      {
        prm = l - 1.;
      }
      else
      {
        prm = f + 1.;
      }
    }

    gp_Pnt2d                pt2d(C2d->Value(prm));
    BRepTopAdaptor_FClass2d FClass2d(F, Precision::PConfusion());
    TopAbs_State            st2 = FClass2d.Perform(pt2d, false);
    return (st2 == TopAbs_IN);
  }
  return false;
}

static void Store(
  const TopoDS_Wire& W2,
  const TopoDS_Wire& W1,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    keyIsIn,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    keyContains)
{
  if (!keyIsIn.IsBound(W2))
  {
    NCollection_List<TopoDS_Shape> empty;
    keyIsIn.Bind(W2, empty);
  }
  keyIsIn(W2).Append(W1);
  if (!keyContains.IsBound(W1))
  {
    NCollection_List<TopoDS_Shape> empty;
    keyContains.Bind(W1, empty);
  }
  keyContains(W1).Append(W2);
}

static void BuildFaceIn(
  TopoDS_Face&       F,
  const TopoDS_Wire& W,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    KeyContains,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                  KeyIsIn,
  TopAbs_Orientation              Orientation,
  NCollection_List<TopoDS_Shape>& Faces)
{
  BRep_Builder B;

  if (!KeyContains.IsBound(W) || KeyContains(W).IsEmpty())
    return;

  NCollection_List<TopoDS_Shape>::Iterator it;
  for (it.Initialize(KeyContains(W)); it.More(); it.Next())
  {
    const TopoDS_Wire&                       WI = TopoDS::Wire(it.Value());
    NCollection_List<TopoDS_Shape>&          L2 = KeyIsIn(WI);
    NCollection_List<TopoDS_Shape>::Iterator it2;
    for (it2.Initialize(L2); it2.More(); it2.Next())
    {
      if (it2.Value().IsSame(W))
      {
        L2.Remove(it2);
        break;
      }
    }
  }

  NCollection_List<TopoDS_Shape> WireExt;

  for (it.Initialize(KeyContains(W)); it.More(); it.Next())
  {
    const TopoDS_Wire&              WI = TopoDS::Wire(it.Value());
    NCollection_List<TopoDS_Shape>& L2 = KeyIsIn(WI);

    if (L2.IsEmpty())
    {
      WireExt.Append(WI);
    }
  }

  for (it.Initialize(WireExt); it.More(); it.Next())
  {
    const TopoDS_Wire&              WI = TopoDS::Wire(it.Value());
    NCollection_List<TopoDS_Shape>& L2 = KeyIsIn(WI);
    if (L2.IsEmpty())
    {
      if (Orientation == TopAbs_FORWARD)
      {
        TopoDS_Wire NWI(WI);
        NWI.Reverse();

        B.Add(F, NWI);
        BuildFaceIn(F, WI, KeyContains, KeyIsIn, TopAbs_REVERSED, Faces);
      }
      else
      {
        TopoDS_Shape aLocalShape = Faces.First().EmptyCopied();
        TopoDS_Face  NF          = TopoDS::Face(aLocalShape);

        B.Add(NF, WI);
        Faces.Append(NF);
        BuildFaceIn(NF, WI, KeyContains, KeyIsIn, TopAbs_FORWARD, Faces);
      }
    }
  }
}

void BRepAlgo_FaceRestrictor::PerformWithCorrection()
{
  BRep_Builder B;

  myDone = false;
  NCollection_List<TopoDS_Shape>::Iterator it(wires);

  for (; it.More(); it.Next())
  {
    TopoDS_Wire& W           = TopoDS::Wire(it.ChangeValue());
    TopoDS_Shape aLocalShape = myFace.EmptyCopied();
    TopoDS_Face  NF          = TopoDS::Face(aLocalShape);

    NF.Orientation(TopAbs_FORWARD);
    B.Add(NF, W);

    if (IsClosed(W))
    {
      BRepTopAdaptor_FClass2d FClass2d(NF, Precision::PConfusion());
      if (FClass2d.PerformInfinitePoint() != TopAbs_OUT)
      {
        W.Reverse();
      }
    }
  }

  for (it.Initialize(wires); it.More(); it.Next())
  {
    const TopoDS_Wire&                       W1 = TopoDS::Wire(it.Value());
    NCollection_List<TopoDS_Shape>::Iterator it2(wires);

    if (IsClosed(W1))
    {
      TopoDS_Shape aLocalShape = myFace.EmptyCopied();
      TopoDS_Face  NF          = TopoDS::Face(aLocalShape);

      NF.Orientation(TopAbs_FORWARD);
      B.Add(NF, W1);

      BRepTopAdaptor_FClass2d FClass2d(NF, Precision::PConfusion());
      while (it2.More())
      {
        const TopoDS_Wire& W2 = TopoDS::Wire(it2.Value());
        if (!W1.IsSame(W2) && IsInside(W2, NF, FClass2d))
        {
          Store(W2, W1, keyIsIn, keyContains);
        }
        it2.Next();
      }
    }
  }
  NCollection_List<TopoDS_Shape> WireExt;

  for (it.Initialize(wires); it.More(); it.Next())
  {
    const TopoDS_Wire& W = TopoDS::Wire(it.Value());
    if (!keyIsIn.IsBound(W) || keyIsIn(W).IsEmpty())
    {
      WireExt.Append(W);
    }
  }

  for (it.Initialize(WireExt); it.More(); it.Next())
  {
    const TopoDS_Wire& W = TopoDS::Wire(it.Value());
    if (!keyIsIn.IsBound(W) || keyIsIn(W).IsEmpty())
    {
      TopoDS_Shape aLocalShape = myFace.EmptyCopied();
      TopoDS_Face  NewFace     = TopoDS::Face(aLocalShape);

      NewFace.Orientation(TopAbs_FORWARD);
      B.Add(NewFace, W);
      faces.Append(NewFace);

      BuildFaceIn(NewFace, W, keyContains, keyIsIn, TopAbs_FORWARD, faces);
    }
  }
  myDone = true;
}
