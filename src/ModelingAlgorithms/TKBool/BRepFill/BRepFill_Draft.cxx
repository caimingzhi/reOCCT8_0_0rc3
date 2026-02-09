#include <BRepFill_Draft.hpp>

#include <BndLib_Add3dCurve.hpp>
#include <BndLib_AddSurface.hpp>
#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAlgoAPI_Section.hpp>
#include <BRepBuilderAPI_Sewing.hpp>
#include <BRepClass3d_SolidClassifier.hpp>
#include <BRepExtrema_DistShapeShape.hpp>
#include <BRepFill_DraftLaw.hpp>
#include <BRepFill_ShapeLaw.hpp>
#include <BRepFill_Sweep.hpp>
#include <BRepLib_FindSurface.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepLib_MakeWire.hpp>
#include <BRepTools.hpp>
#include <Geom_Geometry.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <GeomFill_LocationDraft.hpp>
#include <GeomLProp_SLProps.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <gp_Mat.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <Precision.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Solid.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_List.hpp>

static void ComputeTrsf(const TopoDS_Wire& W, const gp_Dir& D, Bnd_Box& Box, gp_Trsf& Tf)
{

  BRepTools_WireExplorer Exp(W);

  gp_XYZ Bary(0., 0., 0.);
  int    nb;

  for (nb = 0; Exp.More(); Exp.Next())
  {

    Bary += BRep_Tool::Pnt(Exp.CurrentVertex()).XYZ();
    nb++;
  }
  Bary /= nb;

  gp_Ax3 N(Bary, D);
  Tf.SetTransformation(N);
  BRepAdaptor_Curve AC;

  TopoDS_Wire     TheW = W;
  TopLoc_Location Loc(Tf);
  TheW.Location(Loc);

  Box.SetVoid();
  for (Exp.Init(TheW); Exp.More(); Exp.Next())
  {
    AC.Initialize(Exp.Current());

    BndLib_Add3dCurve::Add(AC, 0.1, Box);
  }
}

static double Longueur(const Bnd_Box& WBox, const Bnd_Box& SBox, gp_Dir& D, gp_Pnt& P)
{

  double Xmin, Ymin, Zmin, Xmax, Ymax, Zmax, WZmin, WZmax, L;

  WBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);
  WZmin = Zmin;
  WZmax = Zmax;

  SBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);
  P.SetCoord((Xmin + Xmax) / 2, (Ymin + Ymax) / 2, Zmax);

  if (Zmax < WZmin)
  {

    D.Reverse();
    L = WZmax - Zmin;
    P.SetZ(Zmin);
  }
  else
  {
    L = Zmax - WZmin;
  }
  return L;
}

static bool GoodOrientation(const Bnd_Box&                           B,
                            const occ::handle<BRepFill_LocationLaw>& Law,
                            const gp_Dir&                            D)
{
  double f, l, r, t;
  double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;

  B.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
  gp_Pnt P1(aXmin, aYmin, aZmin), P2(aXmax, aYmax, aZmax);
  gp_Vec V(P1, P2);

  Law->CurvilinearBounds(Law->NbLaw(), f, l);
  r = V.Magnitude() / l;

  int ii, Ind;

  int Nb = (int)(4 + (10 * r));

  r = l / Nb;

  Nb++;

  NCollection_Array1<gp_Pnt>   Pnts(1, Nb);
  occ::handle<Adaptor3d_Curve> AC;
  gp_XYZ                       Bary(0., 0., 0.);

  for (ii = 1; ii <= Nb; ii++)
  {
    Law->Parameter((ii - 1) * r, Ind, t);
    AC = Law->Law(Ind)->GetCurve();
    AC->D0(t, Pnts(ii));
    Bary += Pnts(ii).XYZ();
  }

  Bary /= Nb;
  gp_Pnt Centre(Bary);
  gp_Vec Normal(D.XYZ());
  double Angle = 0;
  gp_Vec Ref(Centre, Pnts(1));

  for (ii = 2; ii <= Nb; ii++)
  {
    gp_Vec R(Centre, Pnts(ii));
    Angle += Ref.AngleWithRef(R, Normal);
    Ref = R;
  }

  return (Angle >= 0);
}

BRepFill_Draft::BRepFill_Draft(const TopoDS_Shape& S, const gp_Dir& Dir, const double Angle)
{
  myLoc.Nullify();
  mySec.Nullify();
  myFaces.Nullify();
  mySections.Nullify();

  switch (S.ShapeType())
  {
    case TopAbs_WIRE:
    {
      myWire = TopoDS::Wire(S);
      break;
    }
    case TopAbs_FACE:
    {
      TopoDS_Iterator Exp(S);
      myWire = TopoDS::Wire(Exp.Value());
      break;
    }
    case TopAbs_SHELL:
    {
      NCollection_List<TopoDS_Shape> List;
      NCollection_IndexedDataMap<TopoDS_Shape,
                                 NCollection_List<TopoDS_Shape>,
                                 TopTools_ShapeMapHasher>
        edgemap;
      TopExp::MapShapesAndAncestors(S, TopAbs_EDGE, TopAbs_FACE, edgemap);
      int iedge, nbf;
      for (iedge = 1; iedge <= edgemap.Extent(); iedge++)
      {
        const TopoDS_Edge& theEdge = TopoDS::Edge(edgemap.FindKey(iedge));

        if (!BRep_Tool::Degenerated(theEdge))
        {
          nbf = edgemap(iedge).Extent();
          if (nbf == 1)
            List.Append(theEdge);
        }
      }

      if (List.Extent() > 0)
      {
        BRepLib_MakeWire MW;
        MW.Add(List);
        BRepLib_WireError Err = MW.Error();
        if (Err == BRepLib_WireDone)
        {
          myWire = MW.Wire();
        }
        else
        {
#ifdef OCCT_DEBUG
          std::cout << "Error in MakeWire" << std::endl;
#endif
          throw Standard_ConstructionError("BRepFill_Draft");
        }
      }
      else
      {
#ifdef OCCT_DEBUG
        std::cout << "No Free Borders !" << std::endl;
#endif
        throw Standard_ConstructionError("BRepFill_Draft");
      }
      break;
    }
    default:
      throw Standard_ConstructionError("BRepFill_Draft");
  }

  if (!myWire.Closed())
  {
    TopoDS_Vertex Vf, Vl;
    TopExp::Vertices(myWire, Vf, Vl);
    if (Vf.IsSame(Vl))
      myWire.Closed(true);
  }

  myAngle = std::abs(Angle);
  myDir   = Dir;
  myTop   = S;
  myDone  = false;
  myTol   = 1.e-4;
  myCont  = GeomAbs_C1;
  SetOptions();
  SetDraft();
}

void BRepFill_Draft::SetOptions(const BRepFill_TransitionStyle Style,
                                const double                   Min,
                                const double                   Max)
{
  myStyle = Style;
  angmin  = Min;
  angmax  = Max;
}

void BRepFill_Draft::SetDraft(const bool Internal)
{
  IsInternal = Internal;
}

void BRepFill_Draft::Perform(const double LengthMax)
{
  occ::handle<Geom_Surface> S;
  S.Nullify();
  Bnd_Box WBox;
  gp_Trsf Trsf;

  ComputeTrsf(myWire, myDir, WBox, Trsf);
  Init(S, LengthMax, WBox);
  BuildShell(S);
  Sewing();
}

void BRepFill_Draft::Perform(const occ::handle<Geom_Surface>& Surface, const bool KeepInsideSurface)
{
  Bnd_Box WBox, SBox;
  gp_Trsf Trsf;
  gp_Pnt  Pt;
  double  L;

  ComputeTrsf(myWire, myDir, WBox, Trsf);

  occ::handle<Geom_Surface> Surf;
  Surf = occ::down_cast<Geom_Surface>(Surface->Transformed(Trsf));
  GeomAdaptor_Surface S1(Surf);

  BndLib_AddSurface::Add(S1, 0.1, SBox);

  L = Longueur(WBox, SBox, myDir, Pt);
  L /= std::abs(std::cos(myAngle));

  Init(Surface, L, WBox);
  BuildShell(Surface, !KeepInsideSurface);
  Sewing();
}

void BRepFill_Draft::Perform(const TopoDS_Shape& StopShape, const bool KeepOutSide)
{
  Bnd_Box WBox, SBox;
  gp_Trsf Trsf;
  gp_Pnt  Pt;
  double  L;

  ComputeTrsf(myWire, myDir, WBox, Trsf);

  Bnd_Box BSurf;
  double  Umin, Umax, Vmin, Vmax;

  occ::handle<Geom_Surface> Surf;

  TopExp_Explorer Ex(StopShape, TopAbs_FACE);

  SBox.SetVoid();
  while (Ex.More())
  {

    BRepTools::UVBounds(TopoDS::Face(Ex.Current()), Umin, Umax, Vmin, Vmax);
    Surf = occ::down_cast<Geom_Surface>(

      BRep_Tool::Surface(TopoDS::Face(Ex.Current()))->Transformed(Trsf));
    GeomAdaptor_Surface S1(Surf);

    BndLib_AddSurface::Add(S1, Umin, Umax, Vmin, Vmax, 0.1, BSurf);
    SBox.Add(BSurf);
    Ex.Next();
  }

  L = Longueur(WBox, SBox, myDir, Pt);
  L /= std::abs(std::cos(myAngle));

  gp_Trsf Inv;
  Inv = Trsf.Inverted();
  Pt.Transform(Inv);
  occ::handle<Geom_Plane> Plan = new (Geom_Plane)(Pt, myDir);
  Surf                         = new (Geom_RectangularTrimmedSurface)(Plan, -L, L, -L, L);

  Init(Plan, L * 1.01, WBox);
  BuildShell(Surf, false);
  Fuse(StopShape, KeepOutSide);
  Sewing();
}

void BRepFill_Draft::Init(const occ::handle<Geom_Surface>&, const double Length, const Bnd_Box& Box)
{
  bool B;

  occ::handle<GeomFill_LocationDraft> Loc = new (GeomFill_LocationDraft)(myDir, myAngle);
  myLoc                                   = new (BRepFill_DraftLaw)(myWire, Loc);

  B = GoodOrientation(Box, myLoc, myDir);

  if (IsInternal ^ (!B))
  {
    myAngle = -myAngle;
    Loc->SetAngle(myAngle);
    myLoc = new (BRepFill_DraftLaw)(myWire, Loc);
  }

  myLoc->CleanLaw(angmin);

  gp_Pnt P(0, 0, 0);
  gp_Vec D(0., 1., 0.);

  double f, l;
  myLoc->Law(1)->GetDomain(f, l);
  gp_Mat M;

  gp_Vec Bid;
  myLoc->Law(1)->D0((f + l) / 2, M, Bid);
  gp_Dir BN(M.Column(2));

  double ang = myDir.Angle(BN);
  if (ang > M_PI / 2)
    D.Reverse();
  occ::handle<Geom_Line> L = new (Geom_Line)(P, D);

  occ::handle<Geom_Curve> TC = new (Geom_TrimmedCurve)(L, 0, Length);

  BRepLib_MakeEdge ME(TC);
  TopoDS_Edge      EG = ME.Edge();

  BRepLib_MakeWire MW(EG);
  TopoDS_Wire      G = MW.Wire();

  mySec = new (BRepFill_ShapeLaw)(G, true);
}

void BRepFill_Draft::BuildShell(const occ::handle<Geom_Surface>& Surf, const bool KeepOutSide)
{

  BRepFill_Sweep Sweep(mySec, myLoc, true);
  Sweep.SetTolerance(myTol);
  Sweep.SetAngularControl(angmin, angmax);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> Dummy;
  NCollection_DataMap<TopoDS_Shape,
                      occ::handle<NCollection_HArray2<TopoDS_Shape>>,
                      TopTools_ShapeMapHasher>
    Dummy2;
  NCollection_DataMap<TopoDS_Shape,
                      occ::handle<NCollection_HArray2<TopoDS_Shape>>,
                      TopTools_ShapeMapHasher>
    Dummy3;
  Sweep.Build(Dummy, Dummy2, Dummy3, myStyle, myCont);
  if (Sweep.IsDone())
  {
    myShape    = Sweep.Shape();
    myShell    = TopoDS::Shell(myShape);
    myFaces    = Sweep.SubShape();
    mySections = Sweep.Sections();
    myDone     = true;

    bool            out = true;
    TopExp_Explorer ex(myShell, TopAbs_FACE);
    TopoDS_Face     F;
    F = TopoDS::Face(ex.Current());
    BRepAdaptor_Surface SF(F);
    double              u, v;
    gp_Pnt              P;
    gp_Vec              V1, V2, V;
    u = SF.FirstUParameter();
    v = SF.FirstVParameter();
    SF.D1(u, v, P, V1, V2);
    V = V1.Crossed(V2);
    if (F.Orientation() == TopAbs_REVERSED)
      V.Reverse();
    if (V.Magnitude() > 1.e-10)
    {
      out = myDir.Angle(V) > M_PI / 2;
    }
    if (out == IsInternal)
    {
      myShell.Reverse();
      myShape.Reverse();
    }
  }
  else
  {
    myDone = false;
    return;
  }

  if (!Surf.IsNull())
  {

    BRepLib_MakeFace MkF;
    MkF.Init(Surf, true, Precision::Confusion());
    Fuse(MkF.Face(), KeepOutSide);
  }
}

bool BRepFill_Draft::Fuse(const TopoDS_Shape& StopShape, const bool KeepOutSide)
{
  BRep_Builder B;
  bool         issolid = false;
  TopoDS_Solid Sol1, Sol2;
  TopAbs_State State1 = TopAbs_OUT, State2 = TopAbs_OUT;

  if (myShape.ShapeType() == TopAbs_SOLID)
  {
    Sol1    = TopoDS::Solid(myShape);
    issolid = true;
  }
  else
  {
    B.MakeSolid(Sol1);
    B.Add(Sol1, myShape);
  }

  switch (StopShape.ShapeType())
  {
    case TopAbs_COMPOUND:
    {
      TopoDS_Iterator It(StopShape);
      return Fuse(It.Value(), KeepOutSide);
    }
    case TopAbs_SOLID:
    {
      Sol2 = TopoDS::Solid(StopShape);
      break;
    }
    case TopAbs_SHELL:
    {
      B.MakeSolid(Sol2);
      B.Add(Sol2, StopShape);
      break;
    }

    case TopAbs_FACE:
    {
      TopoDS_Shell S;
      B.MakeShell(S);
      B.Add(S, StopShape);
      S.Closed(BRep_Tool::IsClosed(S));
      B.MakeSolid(Sol2);
      B.Add(Sol2, S);
      break;
    }

    default:
    {
      return false;
    }
  }

  BOPAlgo_PaveFiller             aPF;
  NCollection_List<TopoDS_Shape> anArgs;
  anArgs.Append(Sol1);
  anArgs.Append(Sol2);
  aPF.SetArguments(anArgs);
  aPF.Perform();
  if (aPF.HasErrors())
    return false;

  BRepAlgoAPI_Section aSec(Sol1, Sol2, aPF);
  const TopoDS_Shape& aSection = aSec.Shape();

  TopExp_Explorer exp(aSection, TopAbs_EDGE);
  if (!exp.More())

    return false;

  if (StopShape.ShapeType() != TopAbs_SOLID)
  {

    TopoDS_Edge                aSEMin;
    double                     Dmin = Precision::Infinite();
    BRepExtrema_DistShapeShape DistTool;
    DistTool.LoadS1(myWire);

    for (; exp.More(); exp.Next())
    {
      const TopoDS_Shape& aSE = exp.Current();
      DistTool.LoadS2(aSE);
      DistTool.Perform();
      if (DistTool.IsDone())
      {
        double D = DistTool.Value();
        if (D < Dmin)
        {
          Dmin   = D;
          aSEMin = TopoDS::Edge(aSE);
          if (Dmin < Precision::Confusion())
            break;
        }
      }
    }

    if (!aSEMin.IsNull())
    {

      occ::handle<Geom_Surface> S;
      occ::handle<Geom2d_Curve> C2d;
      gp_Pnt2d                  P2d;
      double                    f, l;
      TopLoc_Location           L;
      BRep_Tool::CurveOnSurface(aSEMin, C2d, S, L, f, l, 2);

      C2d->D0((f + l) / 2, P2d);
      GeomLProp_SLProps SP(S, P2d.X(), P2d.Y(), 1, 1.e-12);
      if (!SP.IsNormalDefined())
      {
        C2d->D0((3 * f + l) / 4, P2d);
        SP.SetParameters(P2d.X(), P2d.Y());
        if (!SP.IsNormalDefined())
        {
          C2d->D0((f + 3 * l) / 4, P2d);
          SP.SetParameters(P2d.X(), P2d.Y());
        }
      }

      if (SP.IsNormalDefined())
      {

        if (myDir.Angle(SP.Normal()) < M_PI / 2)
          State1 = TopAbs_IN;
        else
          State1 = TopAbs_OUT;
      }
    }
  }

  if (!KeepOutSide)
  {
    if (State2 == TopAbs_IN)
      State2 = TopAbs_OUT;
    else
      State2 = TopAbs_IN;
  }

  BOPAlgo_Builder aBuilder;
  aBuilder.AddArgument(Sol1);
  aBuilder.AddArgument(Sol2);
  aBuilder.PerformWithFiller(aPF);
  if (aBuilder.HasErrors())
    return false;

  TopoDS_Shape                   result;
  occ::handle<BRepTools_History> aHistory = new BRepTools_History;

  bool isSingleOpNeeded = true;

  if (State1 == TopAbs_OUT)
  {
    NCollection_List<TopoDS_Shape> aLO, aLT;
    aLO.Append(Sol1);
    aLT.Append(Sol2);
    aBuilder.BuildBOP(aLO, aLT, BOPAlgo_CUT, Message_ProgressRange());
    if (!aBuilder.HasErrors())
    {
      TopoDS_Solid    aCutMin;
      TopExp_Explorer anExpS(aBuilder.Shape(), TopAbs_SOLID);
      if (anExpS.More())
      {
        aCutMin = TopoDS::Solid(anExpS.Current());
        anExpS.Next();
        if (anExpS.More())
        {
          double                     aDMin = Precision::Infinite();
          BRepExtrema_DistShapeShape DistTool;
          DistTool.LoadS1(myWire);

          for (anExpS.ReInit(); anExpS.More(); anExpS.Next())
          {
            const TopoDS_Shape& aCut = anExpS.Current();
            DistTool.LoadS2(aCut);
            DistTool.Perform();
            if (DistTool.IsDone())
            {
              double D = DistTool.Value();
              if (D < aDMin)
              {
                aDMin   = D;
                aCutMin = TopoDS::Solid(aCut);
              }
            }
          }
        }
      }

      if (!aCutMin.IsNull())
      {

        aHistory->Merge(aLO, aBuilder);

        BOPAlgo_Builder aGluer;
        aGluer.AddArgument(aCutMin);
        aGluer.AddArgument(Sol2);
        aGluer.SetGlue(BOPAlgo_GlueShift);
        aGluer.Perform();

        aLO.Clear();
        aLO.Append(aCutMin);
        aGluer.BuildBOP(aLO, State1, aLT, State2, Message_ProgressRange());

        if (!aGluer.HasErrors())
        {
          aHistory->Merge(aGluer.History());

          result = aGluer.Shape();
          anExpS.Init(result, TopAbs_SOLID);
          isSingleOpNeeded = !anExpS.More();
        }
      }
    }
  }

  if (isSingleOpNeeded)
  {
    aHistory->Clear();

    NCollection_List<TopoDS_Shape> aLO, aLT;
    aLO.Append(Sol1);
    aLT.Append(Sol2);

    aBuilder.BuildBOP(aLO, State1, aLT, State2, Message_ProgressRange());
    if (aBuilder.HasErrors())
      return false;

    aHistory->Merge(aBuilder.History());
    result = aBuilder.Shape();
  }

  if (issolid)
    myShape = result;
  else
  {
    TopExp_Explorer Exp;
    Exp.Init(result, TopAbs_SHELL);
    if (Exp.More())
      myShape = Exp.Current();
  }

  int ii;
  for (ii = 1; ii <= myLoc->NbLaw(); ii++)
  {
    const NCollection_List<TopoDS_Shape>& L = aHistory->Modified(myFaces->Value(1, ii));
    if (L.Extent() > 0)
      myFaces->SetValue(1, ii, L.First());
  }
  for (ii = 1; ii <= myLoc->NbLaw() + 1; ii++)
  {
    const NCollection_List<TopoDS_Shape>& L = aHistory->Modified(mySections->Value(1, ii));
    if (L.Extent() > 0)
      mySections->SetValue(1, ii, L.First());
  }

  return true;
}

bool BRepFill_Draft::Sewing()
{
  bool ToAss;
  bool Ok = false;
  ToAss   = (myTop.ShapeType() != TopAbs_WIRE);

  if ((!ToAss) || (!myDone))
    return false;

  occ::handle<BRepBuilderAPI_Sewing> Ass = new BRepBuilderAPI_Sewing(5 * myTol, true, true, false);
  Ass->Add(myShape);
  Ass->Add(myTop);
  ToAss = true;

  int NbCE;

  Ass->Perform();

  NbCE = Ass->NbContigousEdges();

  if (NbCE > 0)
  {
    TopoDS_Shape res;
    res = Ass->SewedShape();
    if ((res.ShapeType() == TopAbs_SHELL) || (res.ShapeType() == TopAbs_SOLID))
    {
      myShape = res;
      Ok      = true;
    }
    else if (res.ShapeType() == TopAbs_COMPOUND)
    {
      TopoDS_Iterator It(res);
      res = It.Value();
      It.Next();
      if (!It.More())
      {
        myShape = res;
        Ok      = true;
      }
    }
  }

  if (Ok)
  {

    int ii;
    for (ii = 1; ii <= myLoc->NbLaw(); ii++)
    {
      if (Ass->IsModified(myFaces->Value(1, ii)))
        myFaces->SetValue(1, ii, Ass->Modified(myFaces->Value(1, ii)));
    }
    for (ii = 1; ii <= myLoc->NbLaw() + 1; ii++)
    {
      if (Ass->IsModified(mySections->Value(1, ii)))
        mySections->SetValue(1, ii, Ass->Modified(mySections->Value(1, ii)));
    }

    if (myShape.Closed())
    {
      TopoDS_Solid solid;
      BRep_Builder BS;
      BS.MakeSolid(solid);
      BS.Add(solid, TopoDS::Shell(myShape));

      BRepClass3d_SolidClassifier SC(solid);
      SC.PerformInfinitePoint(Precision::Confusion());
      if (SC.State() == TopAbs_IN)
      {
        BS.MakeSolid(solid);
        myShape.Reverse();
        BS.Add(solid, TopoDS::Shell(myShape));
      }
      myShape = solid;
    }
  }
#ifdef OCCT_DEBUG
  else
    std::cout << "Draft : No assembly !" << std::endl;
#endif
  return Ok;
}

const NCollection_List<TopoDS_Shape>& BRepFill_Draft::Generated(const TopoDS_Shape& S)
{
  myGenerated.Clear();
  TopoDS_Edge E;
  int         ii;
  E = TopoDS::Edge(S);
  if (E.IsNull())
  {
    for (ii = 0; ii <= myLoc->NbLaw(); ii++)
      if (E.IsSame(myLoc->Vertex(ii)))
      {
        myGenerated.Append(mySections->Value(1, ii + 1));
        break;
      }
  }
  else
  {
    for (ii = 1; ii <= myLoc->NbLaw(); ii++)
      if (E.IsSame(myLoc->Edge(ii)))
      {
        myGenerated.Append(myFaces->Value(1, ii));
        break;
      }
  }

  return myGenerated;
}

TopoDS_Shape BRepFill_Draft::Shape() const
{
  return myShape;
}

TopoDS_Shell BRepFill_Draft::Shell() const
{
  return myShell;
}

bool BRepFill_Draft::IsDone() const
{
  return myDone;
}
