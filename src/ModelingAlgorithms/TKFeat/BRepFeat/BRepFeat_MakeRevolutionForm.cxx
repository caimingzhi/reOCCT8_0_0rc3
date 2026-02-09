#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAlgo.hpp>
#include <BRepAlgoAPI_Common.hpp>
#include <BRepAlgoAPI_Cut.hpp>
#include <BRepAlgoAPI_Section.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <BRepExtrema_ExtCF.hpp>
#include <BRepExtrema_ExtPC.hpp>
#include <BRepFeat.hpp>
#include <BRepFeat_MakeRevolutionForm.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepTools.hpp>
#include <BRepTools_Modifier.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <BRepTopAdaptor_FClass2d.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2dAPI_ExtremaCurveCurve.hpp>
#include <Geom2dAPI_InterCurveCurve.hpp>
#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAPI.hpp>
#include <GeomAPI_ProjectPointOnCurve.hpp>
#include <gp_Ax1.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Vec.hpp>
#include <LocOpe_CSIntersector.hpp>
#include <LocOpe_Gluer.hpp>
#include <LocOpe_PntFace.hpp>
#include <LocOpe_RevolutionForm.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
#include <NCollection_Sequence.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>

#ifdef OCCT_DEBUG
extern bool BRepFeat_GettraceFEAT();
extern bool BRepFeat_GettraceFEATRIB();
#endif

static void MajMap(
  const TopoDS_Shape&,
  const LocOpe_RevolutionForm&,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&,
  TopoDS_Shape&,
  TopoDS_Shape&);

static void SetGluedFaces(
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theSlmap,
  LocOpe_RevolutionForm&,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    SlidingMap,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&);

void BRepFeat_MakeRevolutionForm::Init(const TopoDS_Shape&            Sbase,
                                       const TopoDS_Wire&             W,
                                       const occ::handle<Geom_Plane>& Plane,
                                       const gp_Ax1&                  Axis,
                                       const double                   H1,
                                       const double                   H2,
                                       const int                      Mode,
                                       bool&                          Modify)
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEAT();
  if (trc)
    std::cout << "BRepFeat_MakeRevolutionForm::Init" << std::endl;
#endif
  bool RevolRib = true;
  Done();

  bool Sliding = Modify;

  myAxe                       = Axis;
  occ::handle<Geom_Line> Line = new Geom_Line(Axis);
  double                 LineFirst, LineLast;

  LocOpe_CSIntersector                          ASI(Sbase);
  NCollection_Sequence<occ::handle<Geom_Curve>> scur;
  scur.Clear();
  scur.Append(Line);
  ASI.Perform(scur);
  if (ASI.IsDone() && ASI.NbPoints(1) >= 2)
  {
    LineLast  = ASI.Point(1, ASI.NbPoints(1)).Parameter();
    LineFirst = ASI.Point(1, 1).Parameter();
  }
  else
  {
    LineFirst = RealFirst();
    LineLast  = RealLast();
  }

  occ::handle<Geom2d_Curve> ln2d = GeomAPI::To2d(Line, Plane->Pln());

  TopExp_Explorer exx;
  double          Rad = RealLast();

  exx.Init(W, TopAbs_EDGE);
  for (; exx.More(); exx.Next())
  {
    const TopoDS_Edge&          e = TopoDS::Edge(exx.Current());
    double                      f, l;
    occ::handle<Geom_Curve>     c   = BRep_Tool::Curve(e, f, l);
    occ::handle<Geom2d_Curve>   c2d = GeomAPI::To2d(c, Plane->Pln());
    Geom2dAPI_ExtremaCurveCurve extr(ln2d, c2d, LineFirst, LineLast, f, l);
    double                      L = RealLast();
    if (extr.NbExtrema() >= 1)
    {
      L = extr.LowerDistance();
    }
    gp_Pnt                      p1 = c->Value(f);
    gp_Pnt                      p2 = c->Value(l);
    GeomAPI_ProjectPointOnCurve proj1(p1, Line);
    GeomAPI_ProjectPointOnCurve proj2(p2, Line);
    if (proj1.NbPoints() < 1 || proj2.NbPoints() < 1)
    {
#ifdef OCCT_DEBUG
      if (trc)
        std::cout << " No projection points" << std::endl;
#endif
      myStatusError = BRepFeat_NoProjPt;
      NotDone();
      return;
    }
    double par1 = proj1.Distance(1);
    double par2 = proj2.Distance(1);
    double Par  = std::min(par1, par2);
    if (Par < L)
      L = Par;
    if (L < Rad && L > 0.)
      Rad = L;
  }

  double height = std::min(H1, H2);

  if (Rad <= height)
    Rad = height + 0.01 * height;

  myAngle1 = asin(H1 / Rad) + M_PI / 10.;
  myAngle2 = asin(H2 / Rad) + M_PI / 10.;

  if ((myAngle1 - M_PI / 2) > Precision::Confusion())
    myAngle1 = M_PI / 2;
  if ((myAngle2 - M_PI / 2) > Precision::Confusion())
    myAngle2 = M_PI / 2;

  mySkface.Nullify();
  myPbase.Nullify();

  myFuse = Mode != 0;
#ifdef OCCT_DEBUG
  if (trc)
  {
    if (myFuse)
      std::cout << " Fuse" << std::endl;
    if (!myFuse)
      std::cout << " Cut" << std::endl;
  }
#endif

  myTol = Precision::Confusion();

  exx.Init(W, TopAbs_VERTEX);
  for (; exx.More(); exx.Next())
  {
    const double& tol = BRep_Tool::Tolerance(TopoDS::Vertex(exx.Current()));
    if (tol > myTol)
      myTol = tol;
  }

  exx.Init(Sbase, TopAbs_VERTEX);
  for (; exx.More(); exx.Next())
  {
    const double& tol = BRep_Tool::Tolerance(TopoDS::Vertex(exx.Current()));
    if (tol > myTol)
      myTol = tol;
  }

  TopoDS_Shape aLocalShapeW = W.Oriented(TopAbs_FORWARD);
  myWire                    = TopoDS::Wire(aLocalShapeW);

  myPln     = Plane;
  myHeight1 = H1;
  myHeight2 = H2;

  mySbase = Sbase;
  mySlface.Clear();
  myShape.Nullify();
  myMap.Clear();
  myFShape.Nullify();
  myLShape.Nullify();

  BRep_Builder BB;

  NCollection_List<TopoDS_Shape> theList;

  TopoDS_Shape U;
  U.Nullify();
  gp_Pnt FirstCorner, LastCorner;
  double bnd = HeightMax(mySbase, U, FirstCorner, LastCorner);
  myBnd      = bnd;

  BRepPrimAPI_MakeBox Bndbox(FirstCorner, LastCorner);
  TopoDS_Solid        BndBox = Bndbox.Solid();

  BRepLib_MakeFace PlaneF(myPln->Pln(), -6. * myBnd, 6. * myBnd, -6. * myBnd, 6. * myBnd);
  TopoDS_Face      PlaneFace = TopoDS::Face(PlaneF.Shape());

  BRepAlgoAPI_Common PlaneS(BndBox, PlaneFace);
  TopExp_Explorer    EXP;
  TopoDS_Shape       PlaneSect = PlaneS.Shape();
  EXP.Init(PlaneSect, TopAbs_WIRE);
  TopoDS_Wire      www = TopoDS::Wire(EXP.Current());
  BRepLib_MakeFace Bndface(myPln->Pln(), www, true);
  TopoDS_Face      BndFace = TopoDS::Face(Bndface.Shape());

  TopoDS_Edge   FirstEdge, LastEdge;
  TopoDS_Face   FirstFace, LastFace;
  TopoDS_Vertex FirstVertex, LastVertex;

  bool        OnFirstFace   = false;
  bool        OnLastFace    = false;
  bool        PtOnFirstEdge = false;
  bool        PtOnLastEdge  = false;
  TopoDS_Edge OnFirstEdge, OnLastEdge;
  OnFirstEdge.Nullify();
  OnLastEdge.Nullify();

  bool Data = ExtremeFaces(RevolRib,
                           myBnd,
                           myPln,
                           FirstEdge,
                           LastEdge,
                           FirstFace,
                           LastFace,
                           FirstVertex,
                           LastVertex,
                           OnFirstFace,
                           OnLastFace,
                           PtOnFirstEdge,
                           PtOnLastEdge,
                           OnFirstEdge,
                           OnLastEdge);

  if (!Data)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " No Extreme faces" << std::endl;
#endif
    myStatusError = BRepFeat_NoExtFace;
    NotDone();
    return;
  }

  gp_Pnt CheckPnt = CheckPoint(FirstEdge, bnd / 10., myPln);

  int Concavite = 3;

  myFirstPnt = BRep_Tool::Pnt(FirstVertex);
  myLastPnt  = BRep_Tool::Pnt(LastVertex);

  NCollection_List<TopoDS_Shape> SliList;
  SliList.Append(FirstFace);

  if (Sliding)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " Sliding" << std::endl;
#endif
    occ::handle<Geom_Surface> s = BRep_Tool::Surface(FirstFace);
    if (s->DynamicType() == STANDARD_TYPE(Geom_RectangularTrimmedSurface))
    {
      s = occ::down_cast<Geom_RectangularTrimmedSurface>(s)->BasisSurface();
    }
    if (s->DynamicType() != STANDARD_TYPE(Geom_Plane)
        && s->DynamicType() != STANDARD_TYPE(Geom_CylindricalSurface)
        && s->DynamicType() != STANDARD_TYPE(Geom_ConicalSurface)
        && s->DynamicType() != STANDARD_TYPE(Geom_ToroidalSurface))
      Sliding = false;
  }

  if (Sliding)
  {
    occ::handle<Geom_Surface> ss = BRep_Tool::Surface(LastFace);
    if (ss->DynamicType() == STANDARD_TYPE(Geom_RectangularTrimmedSurface))
    {
      ss = occ::down_cast<Geom_RectangularTrimmedSurface>(ss)->BasisSurface();
    }
    if (ss->DynamicType() != STANDARD_TYPE(Geom_Plane)
        && ss->DynamicType() != STANDARD_TYPE(Geom_CylindricalSurface)
        && ss->DynamicType() != STANDARD_TYPE(Geom_ConicalSurface)
        && ss->DynamicType() != STANDARD_TYPE(Geom_ToroidalSurface))
      Sliding = false;
  }

  gp_Circ                 FirstCircle, LastCircle;
  occ::handle<Geom_Curve> FirstCrv, LastCrv;

  if (Sliding)
  {
    GeomAPI_ProjectPointOnCurve proj(myFirstPnt, Line);
    if (proj.NbPoints() < 1)
    {
#ifdef OCCT_DEBUG
      if (trc)
        std::cout << " No First Point projection" << std::endl;
#endif
      myStatusError = BRepFeat_NoProjPt;
      NotDone();
      return;
    }
    double FirstRayon  = proj.Distance(1);
    gp_Pnt FirstCenter = proj.Point(1);

    GeomAPI_ProjectPointOnCurve proj1(myLastPnt, Line);
    if (proj.NbPoints() < 1)
    {
#ifdef OCCT_DEBUG
      if (trc)
        std::cout << " No Last Point projection" << std::endl;
#endif
      myStatusError = BRepFeat_NoProjPt;
      NotDone();
      return;
    }
    double LastRayon  = proj1.Distance(1);
    gp_Pnt LastCenter = proj1.Point(1);

    gp_Vec  axv(myAxe.Direction());
    gp_Ax2  ax2(FirstCenter, axv);
    gp_Ax2  ax2p(LastCenter, axv);
    gp_Circ theFC(ax2, FirstRayon);
    gp_Circ theLC(ax2p, LastRayon);

    gp_Pnt RFirstPnt1 = myFirstPnt.Rotated(myAxe, myAngle1);
    gp_Pnt RLastPnt1  = myLastPnt.Rotated(myAxe, myAngle1);
    gp_Pnt RFirstPnt2 = myFirstPnt.Rotated(myAxe, -myAngle2);
    gp_Pnt RLastPnt2  = myLastPnt.Rotated(myAxe, -myAngle2);

    BRep_Builder  Bu;
    TopoDS_Vertex v1, v2, v3, v4;
    Bu.MakeVertex(v1, RFirstPnt2, Precision::Confusion());
    Bu.MakeVertex(v2, RFirstPnt1, Precision::Confusion());
    Bu.MakeVertex(v3, RLastPnt2, Precision::Confusion());
    Bu.MakeVertex(v4, RLastPnt1, Precision::Confusion());

    BRepLib_MakeEdge ee1(theFC, v1, v2);
    BRepLib_MakeEdge ee2(theLC, v3, v4);

    if (Sliding && !PtOnFirstEdge)
    {
      BRepExtrema_ExtCF ext1(TopoDS::Edge(ee1.Shape()), FirstFace);
      if (ext1.NbExt() < 1 || ext1.SquareDistance(1) > Precision::SquareConfusion())
        Sliding = false;
    }
    if (Sliding && !PtOnLastEdge)
    {
      BRepExtrema_ExtCF ext2(ee2, LastFace);
      if (ext2.NbExt() < 1 || ext2.SquareDistance(1) > Precision::SquareConfusion())
        Sliding = false;
    }
    if (Sliding && PtOnFirstEdge)
    {
      double f, l;
      FirstCrv = BRep_Tool::Curve(OnFirstEdge, f, l);
      if (FirstCrv->DynamicType() != STANDARD_TYPE(Geom_Circle))
        Sliding = false;
      else
      {
        occ::handle<Geom_Circle> C1   = occ::down_cast<Geom_Circle>(FirstCrv);
        gp_Circ                  Circ = C1->Circ();
        FirstCircle                   = Circ;
        gp_Ax1 circax                 = FirstCircle.Axis();
        if (!circax.IsCoaxial(myAxe, Precision::Confusion(), Precision::Confusion()))
          Sliding = false;
        else
        {

          if (fabs(FirstCircle.Radius() - FirstRayon) >=

              Precision::Confusion())
            Sliding = false;
        }
      }
    }

    if (Sliding && PtOnLastEdge)
    {
      double f, l;
      LastCrv = BRep_Tool::Curve(OnLastEdge, f, l);
      if (LastCrv->DynamicType() != STANDARD_TYPE(Geom_Circle))
        Sliding = false;
      else
      {
        occ::handle<Geom_Circle> C1   = occ::down_cast<Geom_Circle>(LastCrv);
        gp_Circ                  Circ = C1->Circ();
        LastCircle                    = Circ;
        gp_Ax1 circax                 = LastCircle.Axis();
        if (!circax.IsCoaxial(myAxe, Precision::Confusion(), Precision::Confusion()))
          Sliding = false;
        else
        {
          double rad = LastCircle.Radius();

          if (fabs(rad - LastRayon) >= Precision::Confusion())
          {

            Sliding = false;
          }
        }
      }
    }
  }

  if (Sliding)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " still Sliding" << std::endl;
#endif
    TopoDS_Face Prof;
    bool        ProfileOK;
    ProfileOK = SlidingProfile(Prof,
                               RevolRib,
                               myTol,
                               Concavite,
                               myPln,
                               BndFace,
                               CheckPnt,
                               FirstFace,
                               LastFace,
                               FirstVertex,
                               LastVertex,
                               FirstEdge,
                               LastEdge);

    if (!ProfileOK)
    {
#ifdef OCCT_DEBUG
      if (trc)
      {
        std::cout << "Not computable" << std::endl;
        std::cout << "Face profile not computable" << std::endl;
      }
#endif
      myStatusError = BRepFeat_NoFaceProf;
      NotDone();
      return;
    }

    bool falseside = true;
    Sliding        = Propagate(SliList, Prof, myFirstPnt, myLastPnt, falseside);

    if (!falseside)
    {
#ifdef OCCT_DEBUG
      std::cout << " Verify plane and wire orientation" << std::endl;
#endif
      myStatusError = BRepFeat_FalseSide;
      NotDone();
      return;
    }
  }

  TopoDS_Wire w;
  BB.MakeWire(w);
  TopoDS_Edge   thePreviousEdge;
  TopoDS_Vertex theFV;
  thePreviousEdge.Nullify();

  int counter = 1;

  if (Sliding && !myListOfEdges.IsEmpty())
  {
    BRepTools_WireExplorer EX1(myWire);
    for (; EX1.More(); EX1.Next())
    {
      const TopoDS_Edge& E = EX1.Current();
      if (!myLFMap.IsBound(E))
      {
        NCollection_List<TopoDS_Shape> theTmpList;
        myLFMap.Bind(E, theTmpList);
      }
      if (E.IsSame(FirstEdge))
      {
        double                  f, l;
        occ::handle<Geom_Curve> cc = BRep_Tool::Curve(E, f, l);
        gp_Pnt                  pt;
        if (!FirstEdge.IsSame(LastEdge))
        {
          pt = BRep_Tool::Pnt(TopExp::LastVertex(E, true));
        }
        else
        {
          pt          = myLastPnt;
          double fpar = IntPar(cc, myFirstPnt);
          double lpar = IntPar(cc, pt);
          if (fpar > lpar)
          {
            cc = cc->Reversed();
          }
        }
        TopoDS_Edge ee1;
        if (thePreviousEdge.IsNull())
        {
          BRepLib_MakeVertex v1(myFirstPnt);
          BRepLib_MakeVertex v2(pt);
          BRepLib_MakeEdge   e(cc, v1, v2);
          ee1 = TopoDS::Edge(e.Shape());
        }
        else
        {
          const TopoDS_Vertex& v1 = TopExp::LastVertex(thePreviousEdge, true);
          BRepLib_MakeVertex   v2(pt);

          BRepLib_MakeEdge e(cc, v1, v2);
          ee1 = TopoDS::Edge(e.Shape());
        }
        TopoDS_Shape aLocalShape = ee1.Oriented(E.Orientation());
        ee1                      = TopoDS::Edge(aLocalShape);

        if (counter == 1)
          theFV = TopExp::FirstVertex(ee1, true);
        myLFMap(E).Append(ee1);
        BB.Add(w, ee1);
        thePreviousEdge = ee1;
        counter++;
        EX1.Next();
        break;
      }
    }

    if (!FirstEdge.IsSame(LastEdge))
    {
      for (; EX1.More(); EX1.Next())
      {
        const TopoDS_Edge& E = EX1.Current();
        if (!myLFMap.IsBound(E))
        {
          NCollection_List<TopoDS_Shape> thelist1;
          myLFMap.Bind(E, thelist1);
        }
        theList.Append(E);
        double f, l;
        if (!E.IsSame(LastEdge))
        {
          occ::handle<Geom_Curve> ccc = BRep_Tool::Curve(E, f, l);
          TopoDS_Vertex           v1, v2;
          if (!thePreviousEdge.IsNull())
          {
            v1 = TopExp::LastVertex(thePreviousEdge, true);
            v2 = TopExp::LastVertex(E, true);
          }
          else
          {

            v1 = TopExp::FirstVertex(E, true);
            v2 = TopExp::LastVertex(E, true);
          }
          BRepLib_MakeEdge E1(ccc, v1, v2);
          TopoDS_Edge      E11         = TopoDS::Edge(E1.Shape());
          TopoDS_Shape     aLocalShape = E11.Oriented(E.Orientation());
          E11                          = TopoDS::Edge(aLocalShape);

          thePreviousEdge = E11;
          myLFMap(E).Append(E11);
          BB.Add(w, E11);
          if (counter == 1)
            theFV = TopExp::FirstVertex(E11, true);
          counter++;
        }
        else
        {
          occ::handle<Geom_Curve> cc = BRep_Tool::Curve(E, f, l);
          gp_Pnt                  pf = BRep_Tool::Pnt(TopExp::FirstVertex(E, true));
          gp_Pnt                  pl = myLastPnt;
          TopoDS_Edge             ee;
          if (thePreviousEdge.IsNull())
          {
            BRepLib_MakeEdge e(cc, pf, pl);
            ee = TopoDS::Edge(e.Shape());
          }
          else
          {
            const TopoDS_Vertex& v1 = TopExp::LastVertex(thePreviousEdge, true);
            BRepLib_MakeVertex   v2(pl);
            BRepLib_MakeEdge     e(cc, v1, v2);
            ee = TopoDS::Edge(e.Shape());
          }
          TopoDS_Shape aLocalShape = ee.Oriented(E.Orientation());
          ee                       = TopoDS::Edge(aLocalShape);

          BB.Add(w, ee);
          myLFMap(E).Append(ee);
          if (counter == 1)
            theFV = TopExp::FirstVertex(ee, true);
          thePreviousEdge = ee;
          counter++;
          break;
        }
      }
    }

    NCollection_List<TopoDS_Shape>::Iterator it(myListOfEdges);
    bool                                     FirstOK = false;
    bool                                     LastOK  = false;

    gp_Pnt                         theLastPnt = myLastPnt;
    int                            sens       = 0;
    TopoDS_Edge                    theEdge, theLEdge, theFEdge;
    int                            counter1 = counter;
    NCollection_List<TopoDS_Shape> NewListOfEdges;
    NewListOfEdges.Clear();
    while (!FirstOK)
    {
      const TopoDS_Edge&             edg = TopoDS::Edge(it.Value());
      gp_Pnt                         fp, lp;
      double                         f, l;
      occ::handle<Geom_Curve>        ccc = BRep_Tool::Curve(edg, f, l);
      occ::handle<Geom_TrimmedCurve> cc  = new Geom_TrimmedCurve(ccc, f, l);
      if (edg.Orientation() == TopAbs_REVERSED)
        cc->Reverse();

      fp          = cc->Value(cc->FirstParameter());
      lp          = cc->Value(cc->LastParameter());
      double dist = fp.Distance(theLastPnt);
      if (dist <= myTol)
      {
        sens   = 1;
        LastOK = true;
      }
      else
      {
        dist = lp.Distance(theLastPnt);
        if (dist <= myTol)
        {
          sens   = 2;
          LastOK = true;
          cc->Reverse();
        }
      }
      int FirstFlag = 0;
      if (sens == 1 && lp.Distance(myFirstPnt) <= myTol)
      {
        FirstOK   = true;
        FirstFlag = 1;
      }
      else if (sens == 2 && fp.Distance(myFirstPnt) <= myTol)
      {
        FirstOK   = true;
        FirstFlag = 2;
      }

      if (LastOK)
      {
        TopoDS_Edge eeee;
        double      fpar = cc->FirstParameter();
        double      lpar = cc->LastParameter();
        if (!FirstOK)
        {
          if (thePreviousEdge.IsNull())
          {
            BRepLib_MakeEdge e(cc, fpar, lpar);
            eeee = TopoDS::Edge(e.Shape());
          }
          else
          {
            const TopoDS_Vertex& v1 = TopExp::LastVertex(thePreviousEdge, true);
            BRepLib_MakeVertex   v2(cc->Value(lpar));
            BRepLib_MakeEdge     e(cc, v1, v2);
            eeee = TopoDS::Edge(e.Shape());
          }
        }
        else
        {
          if (thePreviousEdge.IsNull())
          {
            BRepLib_MakeVertex v1(cc->Value(fpar));
            BRepLib_MakeEdge   e(cc, v1, theFV);
            eeee = TopoDS::Edge(e.Shape());
          }
          else
          {
            const TopoDS_Vertex& v1 = TopExp::LastVertex(thePreviousEdge, true);
            BRepLib_MakeEdge     e(cc, v1, theFV);
            eeee = TopoDS::Edge(e.Shape());
          }
        }

        thePreviousEdge = eeee;
        BB.Add(w, eeee);
        if (counter == 1)
          theFV = TopExp::FirstVertex(eeee, true);
        counter1++;
        NewListOfEdges.Append(edg);
        theEdge = eeee;

        if (dist <= myTol)
          theFEdge = edg;
        theLastPnt = BRep_Tool::Pnt(TopExp::LastVertex(theEdge, true));
      }

      if (FirstFlag == 1)
      {
        theLEdge = edg;
      }
      else if (FirstFlag == 2)
      {
        theLEdge = theEdge;
      }

      if (LastOK)
      {
        it.Initialize(myListOfEdges);
        LastOK = false;
      }
      else if (it.More())
        it.Next();
      else
      {
        Sliding = false;
        break;
      }
      sens = 0;
    }

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
      SlidMap;
    SlidMap.Clear();

    if (Sliding && counter1 > counter)
    {
      NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
        Iterator      itm;
      TopExp_Explorer EX2(w, TopAbs_EDGE);
      int             ii = 0;
      for (; EX2.More(); EX2.Next())
      {
        const TopoDS_Edge& E = TopoDS::Edge(EX2.Current());
        ii++;
        if (ii >= counter && ii <= counter1)
        {
          it.Initialize(NewListOfEdges);
          int jj = 0;
          for (; it.More(); it.Next())
          {
            const TopoDS_Edge& e2 = TopoDS::Edge(it.Value());
            jj++;
            if (jj == (ii - counter + 1))
            {
              itm.Initialize(mySlface);
              for (; itm.More(); itm.Next())
              {
                const TopoDS_Face&                       fac  = TopoDS::Face(itm.Key());
                const NCollection_List<TopoDS_Shape>&    ledg = itm.Value();
                NCollection_List<TopoDS_Shape>::Iterator itedg(ledg);

                for (; itedg.More(); itedg.Next())
                {
                  const TopoDS_Edge& e1 = TopoDS::Edge(itedg.Value());
                  if (e1.IsSame(e2))
                  {
                    if (!SlidMap.IsBound(fac))
                    {
                      NCollection_List<TopoDS_Shape> thelist2;
                      SlidMap.Bind(fac, thelist2);
                    }
                    SlidMap(fac).Append(E);
                  }
                }
              }
            }
          }
        }
      }
    }

    mySlface.Clear();
    mySlface = SlidMap;
  }

  if (Sliding)
  {
    TopoDS_Face F;
    BB.MakeFace(F, myPln, myTol);
    w.Closed(BRep_Tool::IsClosed(w));
    BB.Add(F, w);
    mySkface = F;
    myPbase  = mySkface;
    mySUntil.Nullify();
  }

  if (!Sliding)
  {
#ifdef OCCT_DEBUG
    if (trc)
    {
      if (Modify)
        std::cout << " Sliding failure" << std::endl;
      std::cout << " no Sliding" << std::endl;
    }
#endif
    TopExp_Explorer        explo1(BndFace, TopAbs_WIRE);
    TopoDS_Wire            WWW = TopoDS::Wire(explo1.Current());
    BRepTools_WireExplorer explo(WWW);
    BRep_Builder           Bu;
    TopoDS_Wire            Wiwiwi;
    Bu.MakeWire(Wiwiwi);
    TopoDS_Vertex NewV1, NewV2, LastV, v;
    NewV1.Nullify();
    NewV2.Nullify();
    LastV.Nullify();

    for (; explo.More(); explo.Next())
    {
      const TopoDS_Edge& e  = TopoDS::Edge(explo.Current());
      TopoDS_Vertex      v1 = TopExp::FirstVertex(e, true);
      TopoDS_Vertex      v2 = TopExp::LastVertex(e, true);

      double                  f, l;
      occ::handle<Geom_Curve> ln = BRep_Tool::Curve(e, f, l);

      occ::handle<Geom2d_Curve> l2d = GeomAPI::To2d(ln, Plane->Pln());
      Geom2dAPI_InterCurveCurve intcc(l2d, ln2d, Precision::Confusion());
      TopoDS_Vertex             VV;
      VV.Nullify();

      if (intcc.NbPoints() > 0)
      {
        gp_Pnt2d P = intcc.Point(1);
        gp_Pnt   point;
        myPln->D0(P.X(), P.Y(), point);
        double par = IntPar(ln, point);
        if (f <= par && l >= par)
        {
          Bu.MakeVertex(VV, point, Precision::Confusion());
        }
      }

      if (VV.IsNull() && NewV1.IsNull())
        continue;

      if (!VV.IsNull() && NewV1.IsNull())
      {
        NewV1 = VV;
        LastV = v2;
        BRepLib_MakeEdge ee1(NewV1, LastV);
        Bu.Add(Wiwiwi, ee1);
        continue;
      }

      if (VV.IsNull() && !NewV1.IsNull())
      {
        BRepLib_MakeEdge ee1(LastV, v2);
        LastV = v2;
        Bu.Add(Wiwiwi, e);
        continue;
      }

      if (!VV.IsNull() && !NewV1.IsNull())
      {
        NewV2 = VV;
        BRepLib_MakeEdge ee1(LastV, NewV2);
        LastV = NewV2;
        Bu.Add(Wiwiwi, ee1);
        BRepLib_MakeEdge ee2(LastV, NewV1);
        Bu.Add(Wiwiwi, ee2);
        break;
      }
    }
    Wiwiwi.Closed(BRep_Tool::IsClosed(Wiwiwi));

    BRepLib_MakeFace newbndface(myPln->Pln(), Wiwiwi, true);
    TopoDS_Face      NewBndFace = TopoDS::Face(newbndface.Shape());

    BRepTopAdaptor_FClass2d Cl(NewBndFace, Precision::Confusion());
    double                  paru, parv;
    ElSLib::Parameters(myPln->Pln(), CheckPnt, paru, parv);
    gp_Pnt2d checkpnt2d(paru, parv);
    if (Cl.Perform(checkpnt2d, true) == TopAbs_OUT)
    {
      BRepAlgoAPI_Cut    c(BndFace, NewBndFace);
      TopExp_Explorer    exp(c.Shape(), TopAbs_WIRE);
      const TopoDS_Wire& aCurWire = TopoDS::Wire(exp.Current());
      BRepLib_MakeFace   ff(myPln->Pln(), aCurWire, true);
      NewBndFace = TopoDS::Face(ff.Shape());
    }

    if (!BRepAlgo::IsValid(NewBndFace))
    {
#ifdef OCCT_DEBUG
      std::cout << "Invalid new bounding face" << std::endl;
#endif
      myStatusError = BRepFeat_InvShape;
      NotDone();
      return;
    }

    BndFace = NewBndFace;

    TopoDS_Face Prof;
    bool        ProfileOK;
    ProfileOK = NoSlidingProfile(Prof,
                                 RevolRib,
                                 myTol,
                                 Concavite,
                                 myPln,
                                 bnd,
                                 BndFace,
                                 CheckPnt,
                                 FirstFace,
                                 LastFace,
                                 FirstVertex,
                                 LastVertex,
                                 FirstEdge,
                                 LastEdge,
                                 OnFirstFace,
                                 OnLastFace);

    if (!ProfileOK)
    {
#ifdef OCCT_DEBUG
      if (trc)
      {
        std::cout << "Not computable" << std::endl;
        std::cout << " Face profile not computable" << std::endl;
      }
#endif
      myStatusError = BRepFeat_NoFaceProf;
      NotDone();
      return;
    }

    bool falseside = true;
    Propagate(SliList, Prof, myFirstPnt, myLastPnt, falseside);

    if (!falseside)
    {
#ifdef OCCT_DEBUG
      std::cout << " Verify plane and wire orientation" << std::endl;
#endif
      myStatusError = BRepFeat_FalseSide;
      NotDone();
      return;
    }

    mySlface.Clear();

    NCollection_List<TopoDS_Shape>::Iterator it;
    it.Initialize(SliList);

    TopoDS_Shape comp;

    BB.MakeShell(TopoDS::Shell(comp));

    for (; it.More(); it.Next())
    {
      BB.Add(comp, it.Value());
    }
    comp.Closed(BRep_Tool::IsClosed(comp));

    mySUntil = comp;

    mySkface = Prof;
    myPbase  = Prof;
  }

  mySliding = Sliding;

  TopExp_Explorer exp;
  for (exp.Init(mySbase, TopAbs_FACE); exp.More(); exp.Next())
  {
    NCollection_List<TopoDS_Shape> thelist3;
    myMap.Bind(exp.Current(), thelist3);
    myMap(exp.Current()).Append(exp.Current());
  }
}

void BRepFeat_MakeRevolutionForm::Add(const TopoDS_Edge& E, const TopoDS_Face& F)
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEAT();
  if (trc)
    std::cout << "BRepFeat_MakeRevolutionForm::Add" << std::endl;
#endif
  if (mySlface.IsEmpty())
  {
    TopExp_Explorer exp;
    for (exp.Init(mySbase, TopAbs_FACE); exp.More(); exp.Next())
    {
      if (exp.Current().IsSame(F))
      {
        break;
      }
    }
    if (!exp.More())
    {
      throw Standard_ConstructionError();
    }

    if (!mySlface.IsBound(F))
    {
      NCollection_List<TopoDS_Shape> thelist;
      mySlface.Bind(F, thelist);
    }
    NCollection_List<TopoDS_Shape>::Iterator itl(mySlface(F));
    for (; itl.More(); itl.Next())
    {
      if (itl.Value().IsSame(E))
      {
        break;
      }
    }
    if (!itl.More())
    {
      mySlface(F).Append(E);
    }
  }
}

void BRepFeat_MakeRevolutionForm::Perform()
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEAT();
  if (trc)
    std::cout << "BRepFeat_MakeRevolutionForm::Perform()" << std::endl;
#endif
  if (mySbase.IsNull() || mySkface.IsNull() || myPbase.IsNull())
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " Fields not initialized" << std::endl;
#endif
    myStatusError = BRepFeat_NotInitialized;
    NotDone();
    return;
  }

  gp_Pnt Pt;

  TopExp_Explorer exx(myPbase, TopAbs_VERTEX);
  for (; exx.More(); exx.Next())
  {
    const TopoDS_Vertex& vv = TopoDS::Vertex(exx.Current());
    if (!vv.IsNull())
    {
      Pt = BRep_Tool::Pnt(vv);
      break;
    }
  }

  if (myAngle2 != 0)
  {
    gp_Trsf T;
    T.SetRotation(myAxe, -myAngle2);
    BRepBuilderAPI_Transform trsf(T);
    trsf.Perform(myPbase, false);
    TopoDS_Face Pbase = TopoDS::Face(trsf.Shape());
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator iter(myLFMap);
    for (; iter.More(); iter.Next())
    {
      const TopoDS_Shape& e1 = iter.Value().First();
      TopExp_Explorer     ex1(myPbase, TopAbs_EDGE);
      TopExp_Explorer     ex2(Pbase, TopAbs_EDGE);
      for (; ex1.More(); ex1.Next())
      {
        if (ex1.Current().IsSame(e1))
        {
          myLFMap(iter.Key()).Clear();
          myLFMap(iter.Key()).Append(ex2.Current());
          break;
        }
        ex2.Next();
      }
    }

    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
      Iterator iter1(mySlface);
    for (; iter1.More(); iter1.Next())
    {
      const TopoDS_Shape& e1 = iter1.Value().First();
      TopExp_Explorer     ex1(myPbase, TopAbs_EDGE);
      TopExp_Explorer     ex2(Pbase, TopAbs_EDGE);
      for (; ex1.More(); ex1.Next())
      {
        if (ex1.Current().IsSame(e1))
        {
          mySlface(iter1.Key()).Clear();
          mySlface(iter1.Key()).Append(ex2.Current());
          break;
        }
        ex2.Next();
      }
    }
    myPbase = Pbase;
    trsf.Perform(mySkface, false);

    mySkface = TopoDS::Face(trsf.Shape());
  }

  LocOpe_RevolutionForm theForm;
  theForm.Perform(myPbase, myAxe, (myAngle1 + myAngle2));
  TopoDS_Shape VraiForm = theForm.Shape();

  MajMap(myPbase, theForm, myMap, myFShape, myLShape);

  myGluedF.Clear();

  gp_Pln           Pln0 = myPln->Pln();
  BRepLib_MakeFace f(Pln0);

  gp_Vec vec1 = myHeight1 * Normal(f, Pt);
  gp_Vec vec2 = -myHeight2 * Normal(f, Pt);

  gp_Pln Pln1 = Pln0.Translated(vec1);
  gp_Pln Pln2 = Pln0.Translated(vec2);

  BRepLib_MakeFace ff1(Pln1);
  BRepLib_MakeFace ff2(Pln2);
  TopoDS_Face      f1 = TopoDS::Face(ff1.Shape());
  TopoDS_Face      f2 = TopoDS::Face(ff2.Shape());
  BRepFeat::FaceUntil(mySbase, f1);
  BRepFeat::FaceUntil(mySbase, f2);

  LocOpe_CSIntersector ASI1(f1);
  LocOpe_CSIntersector ASI2(f2);

  occ::handle<Geom_Line>                        normale = new Geom_Line(Pt, vec1);
  NCollection_Sequence<occ::handle<Geom_Curve>> scur;
  scur.Append(normale);

  ASI1.Perform(scur);
  ASI2.Perform(scur);

  if (!ASI1.IsDone() || !ASI2.IsDone() || ASI1.NbPoints(1) != 1 || ASI2.NbPoints(1) != 1)
  {
#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " Intersection failure" << std::endl;
#endif
    myStatusError = BRepFeat_BadIntersect;
    NotDone();
    return;
  }

  TopAbs_Orientation Ori1 = ASI1.Point(1, 1).Orientation();
  TopAbs_Orientation Ori2 = TopAbs::Reverse(ASI2.Point(1, 1).Orientation());
  TopoDS_Face        FF1  = ASI1.Point(1, 1).Face();
  TopoDS_Face        FF2  = ASI2.Point(1, 1).Face();

  TopoDS_Shape Comp;
  BRep_Builder B;
  B.MakeCompound(TopoDS::Compound(Comp));
  TopoDS_Solid S1 = BRepFeat::Tool(f1, FF1, Ori1);
  TopoDS_Solid S2 = BRepFeat::Tool(f2, FF2, Ori2);
  if (!S1.IsNull())
    B.Add(Comp, S1);
  if (!S2.IsNull())
    B.Add(Comp, S2);

  BRepAlgoAPI_Cut trP(VraiForm, Comp);

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    SlidingMap;

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator it1;
  it1.Initialize(myMap);
  for (; it1.More(); it1.Next())
  {
    const TopoDS_Shape& orig = it1.Key();
    if (it1.Value().IsEmpty())
      continue;
    const TopoDS_Shape& sh = it1.Value().First();
    exx.Init(VraiForm, TopAbs_FACE);
    for (; exx.More(); exx.Next())
    {
      TopoDS_Face     fac = TopoDS::Face(exx.Current());
      TopExp_Explorer exx1(fac, TopAbs_WIRE);
      TopoDS_Wire     thew = TopoDS::Wire(exx1.Current());
      if (thew.IsSame(myFShape))
      {
        const NCollection_List<TopoDS_Shape>& desfaces = trP.Modified(f2);
        myMap(myFShape)                                = desfaces;
        continue;
      }
      else if (thew.IsSame(myLShape))
      {
        const NCollection_List<TopoDS_Shape>& desfaces = trP.Modified(f1);
        myMap(myLShape)                                = desfaces;
        continue;
      }
      if (fac.IsSame(sh))
      {
        if (!trP.IsDeleted(fac))
        {
          const NCollection_List<TopoDS_Shape>& desfaces = trP.Modified(fac);
          if (!desfaces.IsEmpty())
          {
            myMap(orig).Clear();
            myMap(orig) = trP.Modified(fac);
            break;
          }
        }
      }
    }
  }

  exx.Init(VraiForm, TopAbs_FACE);
  for (; exx.More(); exx.Next())
  {
    const TopoDS_Face&             fac = TopoDS::Face(exx.Current());
    NCollection_List<TopoDS_Shape> thelist;
    SlidingMap.Bind(fac, thelist);
    if (trP.IsDeleted(fac))
    {
    }
    else
    {
      const NCollection_List<TopoDS_Shape>& desfaces = trP.Modified(fac);
      if (!desfaces.IsEmpty())
        SlidingMap(fac) = desfaces;
      else
        SlidingMap(fac).Append(fac);
    }
  }

  SetGluedFaces(mySlface, theForm, SlidingMap, myGluedF);

  VraiForm = trP.Shape();

  if (!myGluedF.IsEmpty())
    myPerfSelection = BRepFeat_NoSelection;
  else
    myPerfSelection = BRepFeat_SelectionSh;

  exx.Init(myPbase, TopAbs_EDGE);
  for (; exx.More(); exx.Next())
  {
    const TopoDS_Edge& e = TopoDS::Edge(exx.Current());
    if (!myMap.IsBound(e))
    {
#ifdef OCCT_DEBUG
      if (trc)
        std::cout << " Sliding face not in Base shape" << std::endl;
#endif
      myStatusError = BRepFeat_IncSlidFace;
      NotDone();
      return;
    }
  }

  myGShape = VraiForm;

  if (!myGluedF.IsEmpty() && !mySUntil.IsNull())
  {
#ifdef OCCT_DEBUG
    if (trc)
    {
      std::cout << "The case is not computable" << std::endl;
      std::cout << " Glued faces not empty and Until shape not null" << std::endl;
    }
#endif
    myStatusError = BRepFeat_InvShape;
    NotDone();
    return;
  }

  LFPerform();
}

bool BRepFeat_MakeRevolutionForm::Propagate(NCollection_List<TopoDS_Shape>& SliList,
                                            const TopoDS_Face&              fac,
                                            const gp_Pnt&                   Firstpnt,
                                            const gp_Pnt&                   Lastpnt,
                                            bool&                           falseside)
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEATRIB();
  if (trc)
    std::cout << "BRepFeat_MakeRevolutionForm::Propagate" << std::endl;
#endif
  gp_Pnt Firstpoint = Firstpnt;
  gp_Pnt Lastpoint  = Lastpnt;

  bool        result = true;
  TopoDS_Face CurrentFace, saveFace;
  CurrentFace = TopoDS::Face(SliList.First());
  saveFace    = CurrentFace;

  bool                LastOK = false, FirstOK = false;
  TopoDS_Vertex       v1, v2, v3, v4, Vert;
  BRepAlgoAPI_Section sect(fac, CurrentFace, false);
  sect.Approximation(true);
  sect.Build();
  TopExp_Explorer Ex;
  TopoDS_Edge     e, e1;
  gp_Pnt          FP, LP;
  int             ii = 0;
  for (Ex.Init(sect.Shape(), TopAbs_EDGE); Ex.More(); Ex.Next())
  {
    ii++;
    if (ii == 1)
    {
      e = TopoDS::Edge(Ex.Current());
    }
    else if (ii > 1)
    {
      e1 = TopoDS::Edge(Ex.Current());
      break;
    }
  }
  if (e.IsNull())
  {
    falseside = false;
    return false;
  }

  if (!e1.IsNull())
  {
    double aTolV1, aTolV2;
    myListOfEdges.Clear();
    NCollection_List<TopoDS_Shape> thelist;
    mySlface.Bind(CurrentFace, thelist);
    mySlface(CurrentFace).Append(e1);

    myListOfEdges.Append(e1);

    v1 = TopExp::FirstVertex(e1, true);
    v2 = TopExp::LastVertex(e1, true);

    FP = BRep_Tool::Pnt(v1);
    LP = BRep_Tool::Pnt(v2);

    aTolV1 = BRep_Tool::Tolerance(v1);
    aTolV2 = BRep_Tool::Tolerance(v2);

    if (FP.Distance(Firstpoint) <= aTolV1 || FP.Distance(Lastpoint) <= aTolV1)
    {
      FirstOK = true;
    }
    if (LP.Distance(Firstpoint) <= aTolV2 || LP.Distance(Lastpoint) <= aTolV2)
    {
      LastOK = true;
    }

    if (LastOK && FirstOK)
    {
      return result;
    }

    else
    {
      myListOfEdges.Clear();
    }
  }

  if (!e1.IsNull())
  {
    myListOfEdges.Clear();
    NCollection_List<TopoDS_Shape> thelist1;
    mySlface.Bind(CurrentFace, thelist1);
    mySlface(CurrentFace).Append(e);

    myListOfEdges.Append(e);

    mySlface(CurrentFace).Append(e1);

    v1 = TopExp::FirstVertex(e, true);
    v2 = TopExp::LastVertex(e, true);
    v3 = TopExp::FirstVertex(e1, true);
    v4 = TopExp::LastVertex(e1, true);
    gp_Pnt p1, p2, p3, p4;
    p1 = BRep_Tool::Pnt(v1);
    FP = p1;
    p2 = BRep_Tool::Pnt(v2);
    LP = p2;
    p3 = BRep_Tool::Pnt(v3);
    p4 = BRep_Tool::Pnt(v4);
    if (p1.Distance(Firstpoint) <= BRep_Tool::Tolerance(v1))
    {
      if (p3.Distance(Lastpoint) <= BRep_Tool::Tolerance(v3))
      {
        FirstOK   = true;
        Lastpoint = p4;
      }
      else if (p4.Distance(Lastpoint) <= BRep_Tool::Tolerance(v4))
      {
        FirstOK   = true;
        Lastpoint = p3;
      }
      else
      {
        e1.Nullify();
      }
    }
    else if (p1.Distance(Lastpoint) <= BRep_Tool::Tolerance(v1))
    {
      if (p3.Distance(Firstpoint) <= BRep_Tool::Tolerance(v3))
      {
        FirstOK    = true;
        Firstpoint = p4;
      }
      else if (p4.Distance(Firstpoint) <= BRep_Tool::Tolerance(v4))
      {
        FirstOK    = true;
        Firstpoint = p3;
      }
      else
      {
        e1.Nullify();
      }
    }
    else if (p2.Distance(Firstpoint) <= BRep_Tool::Tolerance(v2))
    {
      if (p3.Distance(Lastpoint) <= BRep_Tool::Tolerance(v3))
      {
        LastOK    = true;
        Lastpoint = p4;
      }
      else if (p4.Distance(Lastpoint) <= BRep_Tool::Tolerance(v4))
      {
        LastOK    = true;
        Lastpoint = p3;
      }
      else
      {
        e1.Nullify();
      }
    }
    else if (p2.Distance(Lastpoint) <= BRep_Tool::Tolerance(v2))
    {
      if (p3.Distance(Firstpoint) <= BRep_Tool::Tolerance(v3))
      {
        LastOK     = true;
        Firstpoint = p4;
      }
      else if (p4.Distance(Firstpoint) <= BRep_Tool::Tolerance(v4))
      {
        LastOK     = true;
        Firstpoint = p3;
      }
      else
      {
        e1.Nullify();
      }
    }
    else
    {
      e = e1;
      e1.Nullify();
    }
  }
  if (e1.IsNull())
  {
    myListOfEdges.Clear();
    NCollection_List<TopoDS_Shape> thelist2;
    mySlface.Bind(CurrentFace, thelist2);
    mySlface(CurrentFace).Append(e);

    myListOfEdges.Append(e);

    v1 = TopExp::FirstVertex(e, true);
    v2 = TopExp::LastVertex(e, true);

    FP = BRep_Tool::Pnt(v1);
    LP = BRep_Tool::Pnt(v2);

    if (FP.Distance(Firstpoint) <= BRep_Tool::Tolerance(v1)
        || FP.Distance(Lastpoint) <= BRep_Tool::Tolerance(v1))
    {
      FirstOK = true;
    }
    if (LP.Distance(Firstpoint) <= BRep_Tool::Tolerance(v2)
        || LP.Distance(Lastpoint) <= BRep_Tool::Tolerance(v2))
    {
      LastOK = true;
    }

    if (LastOK && FirstOK)
    {
      return result;
    }
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    mapedges;
  TopExp::MapShapesAndAncestors(mySbase, TopAbs_EDGE, TopAbs_FACE, mapedges);
  TopExp_Explorer ex;
  TopoDS_Edge     FirstEdge;

  TopoDS_Vertex Vprevious;
  Vprevious.Nullify();
  TopoDS_Vertex Vpreprevious;
  Vpreprevious.Nullify();

  while (!FirstOK)
  {

    gp_Pnt pt;
    if (!v1.IsNull())
      pt = BRep_Tool::Pnt(v1);
    gp_Pnt ptprev;
    if (!Vprevious.IsNull())
      ptprev = BRep_Tool::Pnt(Vprevious);
    gp_Pnt ptpreprev;
    if (!Vpreprevious.IsNull())
      ptpreprev = BRep_Tool::Pnt(Vpreprevious);

    if ((!Vprevious.IsNull() && ptprev.Distance(pt) <= myTol)
        || (!Vpreprevious.IsNull() && ptpreprev.Distance(pt) <= myTol))
    {
      falseside = false;
      return false;
    }

    for (ex.Init(CurrentFace, TopAbs_EDGE); ex.More(); ex.Next())
    {
      const TopoDS_Edge& aCurEdge = TopoDS::Edge(ex.Current());

      BRepExtrema_ExtPC projF(v1, aCurEdge);

      if (projF.IsDone() && projF.NbExt() >= 1)
      {
        double dist2min = RealLast();
        int    index    = 0;
        for (int sol = 1; sol <= projF.NbExt(); sol++)
        {
          if (projF.SquareDistance(sol) <= dist2min)
          {
            index    = sol;
            dist2min = projF.SquareDistance(sol);
          }
        }
        if (index != 0)
        {
          if (dist2min <= BRep_Tool::Tolerance(aCurEdge) * BRep_Tool::Tolerance(aCurEdge))
          {
            FirstEdge = aCurEdge;
            break;
          }
        }
      }
    }

    const NCollection_List<TopoDS_Shape>&    L = mapedges.FindFromKey(FirstEdge);
    NCollection_List<TopoDS_Shape>::Iterator It(L);

    for (; It.More(); It.Next())
    {
      const TopoDS_Face& FF = TopoDS::Face(It.Value());
      if (!FF.IsSame(CurrentFace))
      {
        CurrentFace = FF;
        break;
      }
    }

    BRepAlgoAPI_Section sectf(fac, CurrentFace, false);
    sectf.Approximation(true);
    sectf.Build();

    TopoDS_Edge edg1;
    for (Ex.Init(sectf.Shape(), TopAbs_EDGE); Ex.More(); Ex.Next())
    {
      edg1        = TopoDS::Edge(Ex.Current());
      gp_Pnt ppp1 = BRep_Tool::Pnt(TopExp::FirstVertex(edg1, true));
      gp_Pnt ppp2 = BRep_Tool::Pnt(TopExp::LastVertex(edg1, true));
      if (ppp1.Distance(BRep_Tool::Pnt(v1)) <= BRep_Tool::Tolerance(v1)
          || ppp2.Distance(BRep_Tool::Pnt(v1)) <= BRep_Tool::Tolerance(v1))
        break;
    }

    NCollection_List<TopoDS_Shape> thelist3;
    mySlface.Bind(CurrentFace, thelist3);
    mySlface(CurrentFace).Append(edg1);
    myListOfEdges.Append(edg1);

    if (!edg1.IsNull())
      SliList.Prepend(CurrentFace);
    else
      return false;

    Vert        = TopExp::FirstVertex(edg1, true);
    gp_Pnt PP   = BRep_Tool::Pnt(Vert);
    FP          = BRep_Tool::Pnt(v1);
    double tol  = BRep_Tool::Tolerance(edg1);
    double tol1 = BRep_Tool::Tolerance(v1);
    if (tol1 > tol)
      tol = tol1;
    double dist = PP.Distance(FP);
    if (dist <= tol)
    {
      Vpreprevious = Vprevious;
      Vprevious    = v1;
      v1           = TopExp::LastVertex(edg1, true);
    }
    else
    {
      Vpreprevious = Vprevious;
      Vprevious    = v1;
      v1           = Vert;
    }

    FP = BRep_Tool::Pnt(v1);

    if (FP.Distance(Firstpoint) <= BRep_Tool::Tolerance(v1)
        || FP.Distance(Lastpoint) <= BRep_Tool::Tolerance(v1))
    {
      FirstOK = true;
    }
  }

  CurrentFace = saveFace;
  Vprevious.Nullify();
  Vpreprevious.Nullify();

  while (!LastOK)
  {

    gp_Pnt pt;
    if (!v2.IsNull())
      pt = BRep_Tool::Pnt(v2);
    gp_Pnt ptprev;
    if (!Vprevious.IsNull())
      ptprev = BRep_Tool::Pnt(Vprevious);
    gp_Pnt ptpreprev;
    if (!Vpreprevious.IsNull())
      ptpreprev = BRep_Tool::Pnt(Vpreprevious);

    if ((!Vprevious.IsNull() && ptprev.Distance(pt) <= myTol)
        || (!Vpreprevious.IsNull() && ptpreprev.Distance(pt) <= myTol))
    {
      falseside = false;
      return false;
    }

    for (ex.Init(CurrentFace, TopAbs_EDGE); ex.More(); ex.Next())
    {
      const TopoDS_Edge& aCurEdge = TopoDS::Edge(ex.Current());
      BRepExtrema_ExtPC  projF(v2, aCurEdge);

      if (projF.IsDone() && projF.NbExt() >= 1)
      {
        double dist2min = RealLast();
        int    index    = 0;
        for (int sol = 1; sol <= projF.NbExt(); sol++)
        {
          if (projF.SquareDistance(sol) <= dist2min)
          {
            index    = sol;
            dist2min = projF.SquareDistance(sol);
          }
        }
        if (index != 0)
        {
          if (dist2min <= BRep_Tool::Tolerance(aCurEdge) * BRep_Tool::Tolerance(aCurEdge))
          {
            FirstEdge = aCurEdge;
            break;
          }
        }
      }
    }

    const NCollection_List<TopoDS_Shape>&    L = mapedges.FindFromKey(FirstEdge);
    NCollection_List<TopoDS_Shape>::Iterator It(L);

    for (; It.More(); It.Next())
    {
      const TopoDS_Face& FF = TopoDS::Face(It.Value());
      if (!FF.IsSame(CurrentFace))
      {
        CurrentFace = FF;
        break;
      }
    }

    ii = 0;

    BRepAlgoAPI_Section sectf(fac, CurrentFace, false);
    sectf.Approximation(true);
    sectf.Build();

    TopoDS_Edge edg2;
    for (Ex.Init(sectf.Shape(), TopAbs_EDGE); Ex.More(); Ex.Next())
    {
      edg2        = TopoDS::Edge(Ex.Current());
      gp_Pnt ppp1 = BRep_Tool::Pnt(TopExp::FirstVertex(edg2, true));
      gp_Pnt ppp2 = BRep_Tool::Pnt(TopExp::LastVertex(edg2, true));
      if (ppp1.Distance(BRep_Tool::Pnt(v2)) <= BRep_Tool::Tolerance(v2)
          || ppp2.Distance(BRep_Tool::Pnt(v2)) <= BRep_Tool::Tolerance(v2))
        break;
    }
    NCollection_List<TopoDS_Shape> thelist4;
    mySlface.Bind(CurrentFace, thelist4);
    mySlface(CurrentFace).Append(edg2);
    myListOfEdges.Append(edg2);

    if (!edg2.IsNull())
      SliList.Append(CurrentFace);
    else
      return false;

    Vert      = TopExp::FirstVertex(edg2, true);
    gp_Pnt PP = BRep_Tool::Pnt(Vert);
    FP        = BRep_Tool::Pnt(v2);
    if (PP.Distance(FP) <= BRep_Tool::Tolerance(v2))
    {
      Vpreprevious = Vprevious;
      Vprevious    = v2;
      v2           = TopExp::LastVertex(edg2, true);
    }
    else
    {
      v2 = Vert;
    }
    FP = BRep_Tool::Pnt(v2);

    if (FP.Distance(Firstpoint) <= BRep_Tool::Tolerance(v2)
        || FP.Distance(Lastpoint) <= BRep_Tool::Tolerance(v2))
    {
      LastOK = true;
    }
  }
  if (!e1.IsNull())
    myListOfEdges.Append(e1);
  return result;
}

static void MajMap(
  const TopoDS_Shape&          theB,
  const LocOpe_RevolutionForm& theP,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                theMap,
  TopoDS_Shape& theFShape,
  TopoDS_Shape& theLShape)
{
  TopExp_Explorer exp(theP.FirstShape(), TopAbs_WIRE);
  if (exp.More())
  {
    theFShape = exp.Current();
    NCollection_List<TopoDS_Shape> thelist;
    theMap.Bind(theFShape, thelist);
    for (exp.Init(theP.FirstShape(), TopAbs_FACE); exp.More(); exp.Next())
    {
      const TopoDS_Shape& sh = exp.Current();
      theMap(theFShape).Append(sh);
    }
  }

  exp.Init(theP.LastShape(), TopAbs_WIRE);
  if (exp.More())
  {
    theLShape = exp.Current();
    NCollection_List<TopoDS_Shape> thelist1;
    theMap.Bind(theLShape, thelist1);
    for (exp.Init(theP.LastShape(), TopAbs_FACE); exp.More(); exp.Next())
    {
      const TopoDS_Shape& sh = exp.Current();
      theMap(theLShape).Append(sh);
    }
  }

  for (exp.Init(theB, TopAbs_EDGE); exp.More(); exp.Next())
  {
    if (!theMap.IsBound(exp.Current()))
    {
      NCollection_List<TopoDS_Shape> thelist2;
      theMap.Bind(exp.Current(), thelist2);
      theMap(exp.Current()) = theP.Shapes(exp.Current());
    }
  }
}

static void SetGluedFaces(
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                         theSlmap,
  LocOpe_RevolutionForm& thePrism,
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                                            SlidingMap,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& theMap)
{

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator itm(theSlmap);
  if (!theSlmap.IsEmpty())
  {
    for (; itm.More(); itm.Next())
    {
      const TopoDS_Face&                       fac  = TopoDS::Face(itm.Key());
      const NCollection_List<TopoDS_Shape>&    ledg = itm.Value();
      NCollection_List<TopoDS_Shape>::Iterator it;
      for (it.Initialize(ledg); it.More(); it.Next())
      {
        const NCollection_List<TopoDS_Shape>& gfac = thePrism.Shapes(it.Value());
        if (gfac.Extent() != 1)
        {
#ifdef OCCT_DEBUG
          std::cout << "Pb SetGluedFace" << std::endl;
#endif
        }
        NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
          Iterator iterm(SlidingMap);
        for (; iterm.More(); iterm.Next())
        {
          const TopoDS_Face&                    ff     = TopoDS::Face(iterm.Key());
          const NCollection_List<TopoDS_Shape>& lfaces = iterm.Value();
          if (lfaces.IsEmpty())
            continue;
          const TopoDS_Face& fff = TopoDS::Face(lfaces.First());
          if (gfac.First().IsSame(ff))
            theMap.Bind(fff, fac);
        }
      }
    }
  }
}
