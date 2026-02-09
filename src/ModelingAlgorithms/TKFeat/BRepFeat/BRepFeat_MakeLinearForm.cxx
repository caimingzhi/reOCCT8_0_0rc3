#include <BRep_Builder.hpp>
#include <BRep_Tool.hpp>
#include <BRepAlgoAPI_Common.hpp>
#include <BRepAlgoAPI_Section.hpp>
#include <BRepBuilderAPI.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <BRepExtrema_ExtCF.hpp>
#include <BRepExtrema_ExtPC.hpp>
#include <BRepExtrema_ExtPF.hpp>
#include <BRepFeat.hpp>
#include <BRepFeat_MakeLinearForm.hpp>
#include <BRepLib_MakeEdge.hpp>
#include <BRepLib_MakeFace.hpp>
#include <BRepLib_MakeVertex.hpp>
#include <BRepLib_MakeWire.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepTools.hpp>
#include <BRepTools_Modifier.hpp>
#include <BRepTools_TrsfModification.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <LocOpe_Gluer.hpp>
#include <LocOpe_LinearForm.hpp>
#include <Precision.hpp>
#include <Standard_ConstructionError.hpp>
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
  const LocOpe_LinearForm&,
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&,
  TopoDS_Shape&,
  TopoDS_Shape&);

static void SetGluedFaces(
  const NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
    theSlmap,
  LocOpe_LinearForm&,
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&);

void BRepFeat_MakeLinearForm::Init(const TopoDS_Shape&            Sbase,
                                   const TopoDS_Wire&             W,
                                   const occ::handle<Geom_Plane>& Plane,
                                   const gp_Vec&                  Direc,
                                   const gp_Vec&                  Direc1,
                                   const int                      Mode,
                                   const bool                     Modify)
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEAT();
  if (trc)
    std::cout << "BRepFeat_MakeLinearForm::Init" << std::endl;
#endif
  bool RevolRib = false;
  Done();
  myGenerated.Clear();

  bool Sliding = Modify;
  myLFMap.Clear();

  myShape.Nullify();
  myMap.Clear();
  myFShape.Nullify();
  myLShape.Nullify();
  mySbase = Sbase;
  mySkface.Nullify();
  myPbase.Nullify();

  myGShape.Nullify();
  mySUntil.Nullify();
  myListOfEdges.Clear();
  mySlface.Clear();

  TopoDS_Shape aLocalShapeW = W.Oriented(TopAbs_FORWARD);
  myWire                    = TopoDS::Wire(aLocalShapeW);

  myDir  = Direc;
  myDir1 = Direc1;
  myPln  = Plane;

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

  TopExp_Explorer exx;
  exx.Init(myWire, TopAbs_VERTEX);
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

  gp_Vec nulldir(0, 0, 0);
  if (!myDir1.IsEqual(nulldir, myTol, myTol))
  {
    double ang = myDir1.Angle(myDir);
    if (ang != M_PI)
    {
#ifdef OCCT_DEBUG
      if (trc)
        std::cout << " Directions must be opposite" << std::endl;
#endif
      myStatusError = BRepFeat_BadDirect;
      NotDone();
      return;
    }
  }
  else
  {

#ifdef OCCT_DEBUG
    if (trc)
      std::cout << " Rib is centre" << std::endl;
#endif
    const gp_Vec& DirTranslation = (Direc + Direc1) * 0.5;
    gp_Trsf       T;
    T.SetTranslation(DirTranslation);
    BRepBuilderAPI_Transform trf(T);
    trf.Perform(myWire);
    myWire = TopoDS::Wire(trf.Shape());
    myDir  = Direc - DirTranslation;
    myDir1 = Direc1 - DirTranslation;
    myPln->Transform(T);
  }

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
    Sliding                     = false;
    occ::handle<Geom_Surface> s = BRep_Tool::Surface(FirstFace);
    if (s->DynamicType() == STANDARD_TYPE(Geom_RectangularTrimmedSurface))
    {
      s = occ::down_cast<Geom_RectangularTrimmedSurface>(s)->BasisSurface();
    }
    if (s->DynamicType() == STANDARD_TYPE(Geom_Plane)
        || s->DynamicType() == STANDARD_TYPE(Geom_CylindricalSurface))
    {

      Sliding = true;
    }
  }

  if (Sliding)
  {
    gp_Pnt p1(myFirstPnt.X() + myDir.X(), myFirstPnt.Y() + myDir.Y(), myFirstPnt.Z() + myDir.Z());
    BRepLib_MakeEdge  ee1(myFirstPnt, p1);
    BRepExtrema_ExtCF ext1(ee1, FirstFace);
    if (ext1.NbExt() == 1
        && ext1.SquareDistance(1)
             <= BRep_Tool::Tolerance(FirstFace) * BRep_Tool::Tolerance(FirstFace))
    {
      gp_Pnt p2(myLastPnt.X() + myDir.X(), myLastPnt.Y() + myDir.Y(), myLastPnt.Z() + myDir.Z());
      BRepLib_MakeEdge  ee2(myLastPnt, p2);
      BRepExtrema_ExtCF ext2(ee2, LastFace);
      Sliding = ext2.NbExt() == 1
                && ext2.SquareDistance(1)
                     <= BRep_Tool::Tolerance(LastFace) * BRep_Tool::Tolerance(LastFace);
    }
    else
    {
      Sliding = false;
    }
  }

  if (!myDir1.IsEqual(nulldir, Precision::Confusion(), Precision::Confusion()))
  {
    if (Sliding)
    {
      gp_Pnt            p1(myFirstPnt.X() + myDir1.X(),
                myFirstPnt.Y() + myDir1.Y(),
                myFirstPnt.Z() + myDir1.Z());
      BRepLib_MakeEdge  ee1(myFirstPnt, p1);
      BRepExtrema_ExtCF ext1(ee1, FirstFace);
      if (ext1.NbExt() == 1
          && ext1.SquareDistance(1)
               <= BRep_Tool::Tolerance(FirstFace) * BRep_Tool::Tolerance(FirstFace))
      {
        gp_Pnt            p2(myLastPnt.X() + myDir1.X(),
                  myLastPnt.Y() + myDir1.Y(),
                  myLastPnt.Z() + myDir1.Z());
        BRepLib_MakeEdge  ee2(myLastPnt, p2);
        BRepExtrema_ExtCF ext2(ee2, LastFace);
        Sliding = ext2.NbExt() == 1
                  && ext2.SquareDistance(1)
                       <= BRep_Tool::Tolerance(LastFace) * BRep_Tool::Tolerance(LastFace);
      }
      else
      {
        Sliding = false;
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
      std::cout << "Verify plane and wire orientation" << std::endl;
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
        cc                         = new Geom_TrimmedCurve(cc, f, l);
        gp_Pnt pt;
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
            BB.UpdateVertex(v1, dist);
            BRepLib_MakeVertex v2(cc->Value(lpar));
            TopoDS_Vertex      nv = v2.Vertex();
            BRepLib_MakeEdge   e(cc, v1, nv);
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
        myListOfEdges.Remove(it);
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
      std::cout << "Verify plane and wire orientation" << std::endl;
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

void BRepFeat_MakeLinearForm::Add(const TopoDS_Edge& E, const TopoDS_Face& F)
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEAT();
  if (trc)
    std::cout << "BRepFeat_MakeLinearForm::Add" << std::endl;
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

void BRepFeat_MakeLinearForm::Perform()
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEAT();
  if (trc)
    std::cout << "BRepFeat_MakeLinearForm::Perform()" << std::endl;
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

  gp_Vec nulldir(0, 0, 0);

  double Length = myDir.Magnitude() + myDir1.Magnitude();

  myGluedF.Clear();

  if (!mySUntil.IsNull())
    myPerfSelection = BRepFeat_SelectionU;
  else
    myPerfSelection = BRepFeat_NoSelection;

  gp_Dir dir(myDir);
  gp_Vec V = Length * dir;

  LocOpe_LinearForm theForm;

  if (myDir1.IsEqual(nulldir, Precision::Confusion(), Precision::Confusion()))
    theForm.Perform(myPbase, V, myFirstPnt, myLastPnt);
  else
    theForm.Perform(myPbase, V, myDir1, myFirstPnt, myLastPnt);

  TopoDS_Shape VraiForm = theForm.Shape();

  myFacesForDraft.Append(theForm.FirstShape());
  myFacesForDraft.Append(theForm.LastShape());
  MajMap(myPbase, theForm, myMap, myFShape, myLShape);

  TopExp_Explorer exx(myPbase, TopAbs_EDGE);
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
  SetGluedFaces(mySlface, theForm, myGluedF);

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

bool BRepFeat_MakeLinearForm::Propagate(NCollection_List<TopoDS_Shape>& SliList,
                                        const TopoDS_Face&              fac,
                                        const gp_Pnt&                   Firstpnt,
                                        const gp_Pnt&                   Lastpnt,
                                        bool&                           falseside)
{
#ifdef OCCT_DEBUG
  bool trc = BRepFeat_GettraceFEATRIB();
  if (trc)
    std::cout << "BRepFeat_MakeLinearForm::Propagate" << std::endl;
#endif
  gp_Pnt Firstpoint = Firstpnt;
  gp_Pnt Lastpoint  = Lastpnt;

  bool        result = true;
  TopoDS_Face CurrentFace, saveFace;
  CurrentFace = TopoDS::Face(SliList.First());
  saveFace    = CurrentFace;

  bool          LastOK = false, FirstOK = false;
  bool          v1OK = false, v2OK = false;
  TopoDS_Vertex v1, v2, v3, v4, ve1, ve2;

  BRepAlgoAPI_Section sect(fac, CurrentFace, false);

  sect.Approximation(true);
  sect.Build();

  TopExp_Explorer Ex;
  TopoDS_Edge     eb, ec;
  gp_Pnt          p1, p2;
  double          t1 = 0., t2 = 0.;
  bool            c1f, c2f, c1l, c2l;

  for (Ex.Init(sect.Shape(), TopAbs_EDGE); Ex.More(); Ex.Next())
  {
    ec  = TopoDS::Edge(Ex.Current());
    v1  = TopExp::FirstVertex(ec, true);
    v2  = TopExp::LastVertex(ec, true);
    p1  = BRep_Tool::Pnt(v1);
    p2  = BRep_Tool::Pnt(v2);
    t1  = BRep_Tool::Tolerance(v1);
    t2  = BRep_Tool::Tolerance(v2);
    c1f = p1.Distance(Firstpoint) <= t1;
    c2f = p2.Distance(Firstpoint) <= t2;
    c1l = p1.Distance(Lastpoint) <= t1;
    c2l = p2.Distance(Lastpoint) <= t2;
    if (c1f || c2f || c1l || c2l)
    {
      eb = ec;
      if (c1f || c1l)
        v1OK = true;
      if (c2f || c2l)
        v2OK = true;
      if (c1f || c2f)
        FirstOK = true;
      if (c1l || c2l)
        LastOK = true;
      break;
    }
  }

  if (eb.IsNull())
  {
    falseside = false;
    return false;
  }
  NCollection_List<TopoDS_Shape> thelist;
  mySlface.Bind(CurrentFace, thelist);
  mySlface(CurrentFace).Append(eb);

  myListOfEdges.Clear();
  myListOfEdges.Append(eb);

  if (LastOK && FirstOK)
  {
    return result;
  }

  NCollection_IndexedDataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    mapedges;
  TopExp::MapShapesAndAncestors(mySbase, TopAbs_EDGE, TopAbs_FACE, mapedges);
  TopExp_Explorer ex;
  TopoDS_Edge     FirstEdge;
  BRep_Builder    BB;

  TopoDS_Vertex Vprevious;
  gp_Pnt        ptprev;
  double        dp;

  while (!(LastOK && FirstOK))
  {
    if (v1OK)
    {
      Vprevious = v2;
      ptprev    = p2;
    }
    else
    {
      Vprevious = v1;
      ptprev    = p1;
    }

    for (ex.Init(CurrentFace, TopAbs_EDGE); ex.More(); ex.Next())
    {
      const TopoDS_Edge& rfe = TopoDS::Edge(ex.Current());

      BRepExtrema_ExtPC projF(Vprevious, rfe);

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
          if (dist2min <= BRep_Tool::Tolerance(rfe) * BRep_Tool::Tolerance(rfe))
          {
            FirstEdge = rfe;

            if (result)
            {
              result = false;
              ve1    = TopExp::FirstVertex(rfe, true);
              ve2    = TopExp::LastVertex(rfe, true);
              BRepExtrema_ExtPF perp(ve1, fac);
              if (perp.IsDone())
              {
                gp_Pnt pe1 = perp.Point(1);
                perp.Perform(ve2, fac);
                if (perp.IsDone())
                {
                  gp_Pnt pe2 = perp.Point(1);
                  if (pe1.Distance(pe2) <= BRep_Tool::Tolerance(rfe))
                    result = true;
                }
              }
            }
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
      edg1 = TopoDS::Edge(Ex.Current());
      v1   = TopExp::FirstVertex(edg1, true);
      v2   = TopExp::LastVertex(edg1, true);
      t1   = BRep_Tool::Tolerance(v1);
      t2   = BRep_Tool::Tolerance(v2);
      p1   = BRep_Tool::Pnt(v1);
      p2   = BRep_Tool::Pnt(v2);
      v1OK = p1.Distance(ptprev) <= t1;
      v2OK = p2.Distance(ptprev) <= t2;
      if (v1OK || v2OK)
        break;
    }

    if (v1OK)
    {
      if (!FirstOK)
      {
        dp = p2.Distance(Firstpoint);
        if (dp <= 2 * t2)
        {
          FirstOK = true;
          BB.UpdateVertex(v2, dp);
        }
      }
      if (!LastOK)
      {
        dp = p2.Distance(Lastpoint);
        if (dp <= 2 * t2)
        {
          LastOK = true;
          BB.UpdateVertex(v2, dp);
        }
      }
    }
    else if (v2OK)
    {
      if (!FirstOK)
      {
        dp = p1.Distance(Firstpoint);
        if (dp <= 2 * t1)
        {
          FirstOK = true;
          BB.UpdateVertex(v1, dp);
        }
      }
      if (!LastOK)
      {
        dp = p1.Distance(Lastpoint);
        if (dp <= 2 * t1)
        {
          LastOK = true;
          BB.UpdateVertex(v1, dp);
        }
      }
    }
    else
    {

      return false;
    }
    NCollection_List<TopoDS_Shape> thelist1;
    mySlface.Bind(CurrentFace, thelist1);
    mySlface(CurrentFace).Append(edg1);
    myListOfEdges.Append(edg1);
  }

  return result;
}

static void MajMap(
  const TopoDS_Shape&      theB,
  const LocOpe_LinearForm& theP,
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
      theMap(theFShape).Append(exp.Current());
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
      theMap(theLShape).Append(exp.Current());
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
  LocOpe_LinearForm&                                                        thePrism,
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
        theMap.Bind(gfac.First(), fac);
      }
    }
  }
}
