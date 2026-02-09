#include <Bnd_Box2d.hpp>
#include <NCollection_Array1.hpp>
#include <BndLib_Add2dCurve.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepCheck.hpp>
#include <BRepCheck_Status.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Shared.hpp>
#include <BRepCheck_Wire.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <ElCLib.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <Geom_Curve.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <IntRes2d_Domain.hpp>
#include <IntRes2d_Intersection.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <IntRes2d_IntersectionSegment.hpp>
#include <IntRes2d_Transition.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>

#include <cstdio>
IMPLEMENT_STANDARD_RTTIEXT(BRepCheck_Wire, BRepCheck_Result)

static void Propagate(const NCollection_IndexedDataMap<TopoDS_Shape,
                                                       NCollection_List<TopoDS_Shape>,
                                                       TopTools_ShapeMapHasher>&,
                      const TopoDS_Shape&,
                      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&);

static TopAbs_Orientation GetOrientation(
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&,
  const TopoDS_Edge&);

static void ChoixUV(const TopoDS_Vertex&,
                    const TopoDS_Edge&,
                    const TopoDS_Face&,
                    NCollection_List<TopoDS_Shape>&);

inline bool IsOriented(const TopoDS_Shape& S)
{
  return (S.Orientation() == TopAbs_FORWARD || S.Orientation() == TopAbs_REVERSED);
}

static void CurveDirForParameter(const Geom2dAdaptor_Curve& aC2d,
                                 const double               aPrm,
                                 gp_Pnt2d&                  Pnt,
                                 gp_Vec2d&                  aVec2d);

static bool IsClosed2dForPeriodicFace(const TopoDS_Face&   theFace,
                                      const gp_Pnt2d&      theP1,
                                      const gp_Pnt2d&      theP2,
                                      const TopoDS_Vertex& theVertex);

static bool GetPnt2d(const TopoDS_Vertex& theVertex,
                     const TopoDS_Edge&   theEdge,
                     const TopoDS_Face&   theFace,
                     gp_Pnt2d&            aPnt);

BRepCheck_Wire::BRepCheck_Wire(const TopoDS_Wire& W)
    : myCdone(false),
      myCstat(BRepCheck_NoError),
      myGctrl(false)
{
  Init(W);
}

void BRepCheck_Wire::Minimum()
{
  myCdone = false;
  myGctrl = true;
  if (!myMin)
  {
    occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aNewList =
      new NCollection_Shared<NCollection_List<BRepCheck_Status>>();
    NCollection_List<BRepCheck_Status>& lst = **myMap.Bound(myShape, aNewList);

    TopExp_Explorer exp(myShape, TopAbs_EDGE);
    int             nbedge = 0;
    myMapVE.Clear();

    for (; exp.More(); exp.Next())
    {
      nbedge++;
      TopExp_Explorer expv;
      for (expv.Init(exp.Current(), TopAbs_VERTEX); expv.More(); expv.Next())
      {
        const TopoDS_Shape& vtx   = expv.Current();
        int                 index = myMapVE.FindIndex(vtx);
        if (index == 0)
        {
          NCollection_List<TopoDS_Shape> theListOfShape;
          index = myMapVE.Add(vtx, theListOfShape);
        }
        myMapVE(index).Append(exp.Current());
      }
    }

    if (nbedge == 0)
    {
      BRepCheck::Add(lst, BRepCheck_EmptyWire);
    }

    else if (nbedge >= 2)
    {
      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapE;
      exp.ReInit();
      Propagate(myMapVE, exp.Current(), mapE);
      for (exp.ReInit(); exp.More(); exp.Next())
      {
        if (!mapE.Contains(exp.Current()))
        {
          BRepCheck::Add(lst, BRepCheck_NotConnected);
          break;
        }
      }
    }
    if (lst.IsEmpty())
    {
      lst.Append(BRepCheck_NoError);
    }
    myMapVE.Clear();
    myMin = true;
  }
}

void BRepCheck_Wire::InContext(const TopoDS_Shape& S)
{
  occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aHList;
  {
    std::unique_lock<std::mutex> aLock =
      myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
    if (myMap.IsBound(S))
    {
      return;
    }

    occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aNewList =
      new NCollection_Shared<NCollection_List<BRepCheck_Status>>();
    aHList = *myMap.Bound(S, aNewList);
  }
  NCollection_List<BRepCheck_Status>& lst = *aHList;

  TopExp_Explorer exp(S, TopAbs_WIRE);
  for (; exp.More(); exp.Next())
  {
    if (exp.Current().IsSame(myShape))
    {
      break;
    }
  }
  if (!exp.More())
  {
    BRepCheck::Add(lst, BRepCheck_SubshapeNotInShape);
    return;
  }

  BRepCheck_Status st   = BRepCheck_NoError;
  TopAbs_ShapeEnum styp = S.ShapeType();
  switch (styp)
  {
    case TopAbs_FACE:
    {
      TopoDS_Edge ed1, ed2;
      if (myGctrl)
      {
        st = SelfIntersect(TopoDS::Face(S), ed1, ed2, true);
      }
      if (st != BRepCheck_NoError)
      {
        break;
      }
      st = Closed();
      if (st != BRepCheck_NoError)
      {
        break;
      }
      st = Orientation(TopoDS::Face(S));
      if (st != BRepCheck_NoError)
      {
        break;
      }
      st = Closed2d(TopoDS::Face(S));
      break;
    }
    default:
    {
      break;
    }
  }

  if (st != BRepCheck_NoError)
  {
    BRepCheck::Add(lst, st);
  }

  if (lst.IsEmpty())
  {
    lst.Append(BRepCheck_NoError);
  }
}

void BRepCheck_Wire::Blind()
{
  if (!myBlind)
  {

    myBlind = true;
  }
}

BRepCheck_Status BRepCheck_Wire::Closed(const bool Update)
{
  occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aHList;
  {
    std::unique_lock<std::mutex> aLock =
      myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
    aHList = myMap(myShape);
  }

  NCollection_List<BRepCheck_Status>& aStatusList = *aHList;
  if (myCdone)
  {
    if (Update)
    {
      BRepCheck::Add(aStatusList, myCstat);
    }
    return myCstat;
  }

  myCdone = true;

  NCollection_List<BRepCheck_Status>::Iterator itl(aStatusList);
  if (itl.Value() != BRepCheck_NoError)
  {
    myCstat = itl.Value();
    return myCstat;
  }

  myCstat = BRepCheck_NoError;

  TopExp_Explorer                                        exp, expv;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapS;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher> Cradoc;
  myMapVE.Clear();

  for (exp.Init(myShape, TopAbs_EDGE); exp.More(); exp.Next())
  {
    if (IsOriented(exp.Current()))
    {

      if (!Cradoc.IsBound(exp.Current()))
      {
        NCollection_List<TopoDS_Shape> theListOfShape;
        Cradoc.Bind(exp.Current(), theListOfShape);
      }
      Cradoc(exp.Current()).Append(exp.Current());

      mapS.Add(exp.Current());
      for (expv.Init(exp.Current(), TopAbs_VERTEX); expv.More(); expv.Next())
      {
        if (IsOriented(expv.Current()))
        {
          int index = myMapVE.FindIndex(expv.Current());
          if (index == 0)
          {
            NCollection_List<TopoDS_Shape> theListOfShape1;
            index = myMapVE.Add(expv.Current(), theListOfShape1);
          }
          myMapVE(index).Append(exp.Current());
        }
      }
    }
  }

  int theNbori = mapS.Extent();
  if (theNbori >= 2)
  {
    mapS.Clear();
    for (exp.ReInit(); exp.More(); exp.Next())
    {
      if (IsOriented(exp.Current()))
      {
        break;
      }
    }
    Propagate(myMapVE, exp.Current(), mapS);
  }
  if (theNbori != mapS.Extent())
  {
    myCstat = BRepCheck_NotConnected;
    if (Update)
    {
      BRepCheck::Add(aStatusList, myCstat);
    }
    return myCstat;
  }

  bool yabug = false;
  for (NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
         Iterator itdm(Cradoc);
       itdm.More();
       itdm.Next())
  {
    if (itdm.Value().Extent() >= 3)
    {
      yabug = true;
    }
    else if (itdm.Value().Extent() == 2)
    {
      if (itdm.Value().First().Orientation() == itdm.Value().Last().Orientation())
      {
        yabug = true;
      }
    }
    if (yabug)
    {
      myCstat = BRepCheck_RedundantEdge;
      if (Update)
      {
        BRepCheck::Add(aStatusList, myCstat);
      }
      return myCstat;
    }
  }

  for (int i = 1; i <= myMapVE.Extent(); i++)
  {
    if (myMapVE(i).Extent() % 2 != 0)
    {
      myCstat = BRepCheck_NotClosed;
      if (Update)
      {
        BRepCheck::Add(aStatusList, myCstat);
      }
      return myCstat;
    }
  }

  if (Update)
  {
    BRepCheck::Add(aStatusList, myCstat);
  }
  return myCstat;
}

bool IsDistanceIn3DTolerance(const gp_Pnt& thePnt_f, const gp_Pnt& thePnt_l, const double aTol3d)
{
  double Dist = thePnt_f.Distance(thePnt_l);

  return Dist < aTol3d;
}

static bool IsDistanceIn2DTolerance(const BRepAdaptor_Surface& aFaceSurface,
                                    const gp_Pnt2d&            thePnt,
                                    const gp_Pnt2d&            thePntRef,
                                    const double               aTol3d,
#ifdef OCCT_DEBUG
                                    const bool PrintWarnings = true)
#else
                                    const bool = true)
#endif
{
  double dumax = 0.01 * (aFaceSurface.LastUParameter() - aFaceSurface.FirstUParameter());
  double dvmax = 0.01 * (aFaceSurface.LastVParameter() - aFaceSurface.FirstVParameter());
  double dumin = std::abs(thePnt.X() - thePntRef.X());
  double dvmin = std::abs(thePnt.Y() - thePntRef.Y());

  if ((dumin < dumax) && (dvmin < dvmax))
    return true;

#ifdef OCCT_DEBUG
  if (PrintWarnings)
  {
    std::cout << std::endl;
    std::cout << "--------Function IsDistanceIn2DTolerance(...)----------" << std::endl;
    std::cout << "--- BRepCheck Wire: Not closed in 2D" << std::endl;
    std::cout << "*****************************************************" << std::endl;
    std::cout << "*dumin = " << dumin << "; dumax = " << dumax << std::endl;
    std::cout << "* dvmin = " << dvmin << "; dvmax = " << dvmax << std::endl;
    std::cout << "* (dumin > dumax) or (dvmin > dvmax)." << std::endl;
    std::cout << "*****************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << "UFirst = " << aFaceSurface.FirstUParameter();
    std::cout << "; ULast = " << aFaceSurface.LastUParameter() << std::endl;
    std::cout << "VFirst = " << aFaceSurface.FirstVParameter();
    std::cout << "; VLast = " << aFaceSurface.LastVParameter() << std::endl;
  }
#endif
  dumax = aFaceSurface.UResolution(aTol3d);
  dvmax = aFaceSurface.VResolution(aTol3d);
  gp_Pnt aP;
  gp_Vec aDU, aDV;
  double um = (thePnt.X() + thePntRef.X()) / 2.;
  double vm = (thePnt.Y() + thePntRef.Y()) / 2.;
  aFaceSurface.D1(um, vm, aP, aDU, aDV);
  double aMDU = aDU.Magnitude();
  if (aMDU > Precision::Confusion())
  {
    dumax = std::max((aTol3d / aMDU), dumax);
  }
  double aMDV = aDV.Magnitude();
  if (aMDV > Precision::Confusion())
  {
    dvmax = std::max((aTol3d / aMDV), dvmax);
  }

#ifdef OCCT_DEBUG
  if (PrintWarnings)
  {
    std::cout << "aTol3d = " << aTol3d << "; URes = " << dumax << "; VRes = " << dvmax << std::endl;
    std::cout << "thePnt(" << thePnt.X() << "; " << thePnt.Y() << ")" << std::endl;
    std::cout << "thePntRef(" << thePntRef.X() << "; " << thePntRef.Y() << ")" << std::endl;
  }
#endif

  double aTol2d = 2 * std::max(dumax, dvmax);

#ifdef OCCT_DEBUG
  if ((aTol2d <= 0.0) && (PrintWarnings))
  {
    std::cout << "BRepCheck_Wire : UResolution and VResolution = 0.0 (Face too small ?)"
              << std::endl;
    std::cout.flush();
  }
#endif

  double Dist = std::max(dumin, dvmin);

  return Dist < aTol2d;
}

BRepCheck_Status BRepCheck_Wire::Closed2d(const TopoDS_Face& theFace, const bool Update)
{
  occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aHList;
  {
    std::unique_lock<std::mutex> aLock =
      myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
    aHList = myMap(myShape);
  }
  NCollection_List<BRepCheck_Status>& aStatusList = *aHList;

  BRepCheck_Status aClosedStat = Closed();
  if (aClosedStat != BRepCheck_NoError)
  {
    if (Update)
    {
      BRepCheck::Add(aStatusList, aClosedStat);
    }
    return aClosedStat;
  }

  BRepAdaptor_Surface aFaceSurface(theFace, false);

  int             aNbOrirntedEdges = 0;
  TopExp_Explorer anEdgeExp(myShape, TopAbs_EDGE);
  for (; anEdgeExp.More(); anEdgeExp.Next())
  {
    if (IsOriented(anEdgeExp.Current()))
      aNbOrirntedEdges++;
  }

  if (aNbOrirntedEdges == 0)
  {
    if (Update)
    {
      BRepCheck::Add(aStatusList, aClosedStat);
    }
    return aClosedStat;
  }

  int                    aNbFoundEdges = 0;
  BRepTools_WireExplorer aWireExp(TopoDS::Wire(myShape), theFace);
  TopoDS_Edge            aFirstEdge   = aWireExp.Current();
  TopoDS_Vertex          aFirstVertex = aWireExp.CurrentVertex();
  TopoDS_Edge            aLastEdge;

  for (; aWireExp.More(); aWireExp.Next())
  {
    aNbFoundEdges++;
    aLastEdge = aWireExp.Current();
  }

  if (aNbFoundEdges != aNbOrirntedEdges)
  {
    aClosedStat = BRepCheck_NotClosed;
    if (Update)
    {
      BRepCheck::Add(aStatusList, aClosedStat);
    }
    return aClosedStat;
  }

  double             aF;
  double             aL;
  bool               isFirstInfinite = false;
  bool               isLastInfinite  = false;
  TopAbs_Orientation anOri;

  anOri = aFirstEdge.Orientation();
  BRep_Tool::Range(aFirstEdge, aF, aL);
  if ((anOri == TopAbs_FORWARD && Precision::IsNegativeInfinite(aF))
      || (anOri == TopAbs_REVERSED && Precision::IsPositiveInfinite(aL)))
    isFirstInfinite = true;

  anOri = aLastEdge.Orientation();
  BRep_Tool::Range(aLastEdge, aF, aL);

  if ((anOri == TopAbs_FORWARD && Precision::IsPositiveInfinite(aL))
      || (anOri == TopAbs_REVERSED && Precision::IsNegativeInfinite(aF)))
    isLastInfinite = true;

  if (isFirstInfinite && isLastInfinite)
  {
    if (Update)
    {
      BRepCheck::Add(aStatusList, aClosedStat);
    }
    return aClosedStat;
  }
  else if (aFirstVertex.IsNull())
  {
    aClosedStat = BRepCheck_NotClosed;

    if (Update)
    {
      BRepCheck::Add(aStatusList, aClosedStat);
    }
    return aClosedStat;
  }

  gp_Pnt2d aP_first, aP_last, aP_temp;

  BRep_Tool::UVPoints(aLastEdge, theFace, aP_temp, aP_last);
  if (aLastEdge.Orientation() == TopAbs_REVERSED)
    aP_last = aP_temp;

  if (aFirstEdge.Orientation() == TopAbs_REVERSED)
    BRep_Tool::UVPoints(aFirstEdge, theFace, aP_temp, aP_first);
  else
    BRep_Tool::UVPoints(aFirstEdge, theFace, aP_first, aP_temp);

  if (!IsClosed2dForPeriodicFace(theFace, aP_first, aP_last, aFirstVertex))
  {
    aClosedStat = BRepCheck_NotClosed;
    if (Update)
    {
      BRepCheck::Add(aStatusList, aClosedStat);
    }
    return aClosedStat;
  }

  double aTol3d =
    std::max(BRep_Tool::Tolerance(aFirstVertex), BRep_Tool::Tolerance(aWireExp.CurrentVertex()));

  gp_Pnt aPntRef = BRep_Tool::Pnt(aFirstVertex);
  gp_Pnt aPnt    = BRep_Tool::Pnt(aWireExp.CurrentVertex());

  if (!(IsDistanceIn2DTolerance(aFaceSurface, aP_first, aP_last, aTol3d)))
    aClosedStat = BRepCheck_NotClosed;

  if (!IsDistanceIn3DTolerance(aPntRef, aPnt, aTol3d))
    aClosedStat = BRepCheck_NotClosed;

  if (Update)
  {
    BRepCheck::Add(aStatusList, aClosedStat);
  }
  return aClosedStat;
}

BRepCheck_Status BRepCheck_Wire::Orientation(const TopoDS_Face& F, const bool Update)
{
  BRepCheck_Status                                                    theOstat = Closed();
  occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aHList;
  {
    std::unique_lock<std::mutex> aLock =
      myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
    aHList = myMap(myShape);
  }
  NCollection_List<BRepCheck_Status>& aStatusList = *aHList;

  if (theOstat != BRepCheck_NotClosed && theOstat != BRepCheck_NoError)
  {
    if (Update)
    {
      BRepCheck::Add(aStatusList, theOstat);
    }
    return theOstat;
  }

  theOstat = BRepCheck_NoError;

  TopoDS_Vertex                                          VF, VL;
  TopAbs_Orientation                                     orient, ortmp = TopAbs_FORWARD;
  NCollection_List<TopoDS_Shape>                         ledge, ListOfPassedEdge;
  TopExp_Explorer                                        exp, vte;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapS;
  TopoDS_Edge                                            theEdge, theRef;

  for (exp.Init(myShape, TopAbs_EDGE); exp.More(); exp.Next())
  {
    const TopoDS_Edge& edg = TopoDS::Edge(exp.Current());
    orient                 = edg.Orientation();
    if (IsOriented(edg))
    {
      mapS.Add(edg);
      theEdge = edg;
      theRef  = edg;
      for (vte.Init(edg, TopAbs_VERTEX); vte.More(); vte.Next())
      {
        TopAbs_Orientation vto = vte.Current().Orientation();
        if (vto == TopAbs_FORWARD)
        {
          VF = TopoDS::Vertex(vte.Current());
        }
        else if (vto == TopAbs_REVERSED)
        {
          VL = TopoDS::Vertex(vte.Current());
        }
        if (!VF.IsNull() && !VL.IsNull())
        {
          break;
        }
      }
      if (VF.IsNull() && VL.IsNull())
        theOstat = BRepCheck_InvalidDegeneratedFlag;
      break;
    }
  }

  if (theOstat == BRepCheck_NoError)
  {
    int Index        = 1;
    int nbOriNoDegen = myMapVE.Extent();

    bool isGoFwd = true;

    if (VL.IsNull())
      isGoFwd = false;

    while (Index < nbOriNoDegen)
    {
      ledge.Clear();
      ListOfPassedEdge.Clear();

      int ind;
      if (!VL.IsNull())
      {
        ind = myMapVE.FindIndex(VL);
      }
      else if (!VF.IsNull())
      {
        ind = myMapVE.FindIndex(VF);
      }
      else
      {
        theOstat = BRepCheck_InvalidDegeneratedFlag;
        break;
      }

      for (NCollection_List<TopoDS_Shape>::Iterator itls(myMapVE(ind)); itls.More(); itls.Next())
      {
        const TopoDS_Edge& edg = TopoDS::Edge(itls.Value());

        orient = edg.Orientation();
        if (mapS.Contains(edg))
          ortmp = GetOrientation(mapS, edg);

        if (mapS.Contains(edg) && ortmp == orient && !edg.IsSame(theEdge))
          for (vte.Init(edg, TopAbs_VERTEX); vte.More(); vte.Next())
          {
            TopAbs_Orientation vto = vte.Current().Orientation();
            if (!VL.IsNull())
            {
              if (vto == TopAbs_FORWARD && VL.IsSame(vte.Current()))
              {
                ListOfPassedEdge.Append(edg);
                break;
              }
            }
            else
            {
              if (vto == TopAbs_REVERSED && VF.IsSame(vte.Current()))
              {
                ListOfPassedEdge.Append(edg);
                break;
              }
            }
          }

        if (!mapS.Contains(edg) || ortmp != orient)
        {
          for (vte.Init(edg, TopAbs_VERTEX); vte.More(); vte.Next())
          {
            TopAbs_Orientation vto = vte.Current().Orientation();
            if (!VL.IsNull())
            {
              if (vto == TopAbs_FORWARD && VL.IsSame(vte.Current()))
              {

                if (!F.IsNull() || !BRep_Tool::Degenerated(edg))
                  ledge.Append(edg);
                break;
              }
            }
            else
            {
              if (vto == TopAbs_REVERSED && VF.IsSame(vte.Current()))
              {

                if (!F.IsNull() || !BRep_Tool::Degenerated(edg))
                  ledge.Append(edg);
                break;
              }
            }
          }
        }
      }
      int  nbconnex     = ledge.Extent();
      bool Changedesens = false;
      if (nbconnex == 0)
      {
        if (myCstat == BRepCheck_NotClosed)
        {
          if (VL.IsNull())
          {
            if (Update)
            {
              BRepCheck::Add(aStatusList, theOstat);
            }
            return theOstat;
          }
          else
          {
            Index--;
            VL.Nullify();
            theEdge      = theRef;
            Changedesens = true;
          }
        }
        else
        {
          theOstat = BRepCheck_BadOrientationOfSubshape;
          if (Update)
          {
            BRepCheck::Add(aStatusList, theOstat);
          }
          return theOstat;
        }
      }

      else if (!F.IsNull())
      {
        TopoDS_Vertex pivot;
        if (!VL.IsNull())
        {
          pivot = VL;
        }
        else
        {
          pivot = VF;
        }

        ChoixUV(pivot, theEdge, F, ledge);
        nbconnex = ledge.Extent();
      }

      if (nbconnex >= 2)
      {
        theOstat = BRepCheck_BadOrientationOfSubshape;
        if (Update)
        {
          BRepCheck::Add(aStatusList, theOstat);
        }
        return theOstat;
      }
      else if (nbconnex == 1)
      {

        for (vte.Init(ledge.First(), TopAbs_VERTEX); vte.More(); vte.Next())
        {
          TopAbs_Orientation vto = vte.Current().Orientation();
          if (!VL.IsNull())
          {
            if (vto == TopAbs_REVERSED)
            {
              VL = TopoDS::Vertex(vte.Current());
              break;
            }
          }
          else
          {
            if (vto == TopAbs_FORWARD)
            {
              VF = TopoDS::Vertex(vte.Current());
              break;
            }
          }
        }
        mapS.Add(ledge.First());
        theEdge = TopoDS::Edge(ledge.First());
        if (!vte.More())
        {
          if (!VL.IsNull())
          {
            VL.Nullify();
          }
          else
          {
            VF.Nullify();
          }
        }
      }
      else if (!Changedesens)
      {
        theOstat = BRepCheck_NotClosed;
        if (Update)
        {
          BRepCheck::Add(aStatusList, theOstat);
        }
        return theOstat;
      }

      TopoDS_Vertex aVRef;
      bool          isCheckClose = false;

      if (isGoFwd && !VF.IsNull())
      {
        aVRef        = VF;
        isCheckClose = true;
      }
      else if (!isGoFwd && !VL.IsNull())
      {
        aVRef        = VL;
        isCheckClose = true;
      }

      if (Index == 1 && myCstat != BRepCheck_NotClosed && isCheckClose && !F.IsNull())
      {
        ledge.Clear();

        ind = myMapVE.FindIndex(aVRef);
        for (NCollection_List<TopoDS_Shape>::Iterator itlsh(myMapVE(ind)); itlsh.More();
             itlsh.Next())
        {
          const TopoDS_Edge& edg = TopoDS::Edge(itlsh.Value());
          orient                 = edg.Orientation();
          if (!theRef.IsSame(edg))
          {
            for (vte.Init(edg, TopAbs_VERTEX); vte.More(); vte.Next())
            {
              TopAbs_Orientation vto = vte.Current().Orientation();

              if (vto == TopAbs_REVERSED && aVRef.IsSame(vte.Current()))
              {
                ledge.Append(edg);
                break;
              }
            }
          }
        }

        ChoixUV(aVRef, theRef, F, ledge);
        if (ledge.Extent() == 0)
        {
          theOstat = BRepCheck_NotClosed;
          if (Update)
          {
            BRepCheck::Add(aStatusList, theOstat);
          }
          return theOstat;
        }
      }

      Index++;
    }
  }
  if (Update)
  {
    BRepCheck::Add(aStatusList, theOstat);
  }
  return theOstat;
}

BRepCheck_Status BRepCheck_Wire::SelfIntersect(const TopoDS_Face& F,
                                               TopoDS_Edge&       retE1,
                                               TopoDS_Edge&       retE2,
                                               const bool         Update)
{
  occ::handle<NCollection_Shared<NCollection_List<BRepCheck_Status>>> aHList;
  {
    std::unique_lock<std::mutex> aLock =
      myMutex ? std::unique_lock<std::mutex>(*myMutex) : std::unique_lock<std::mutex>();
    aHList = myMap(myShape);
  }
  NCollection_List<BRepCheck_Status>& aStatusList = *aHList;

  int                                  i, j, Nbedges;
  double                               first1, last1, first2, last2, tolint;
  gp_Pnt2d                             pfirst1, plast1, pfirst2, plast2;
  gp_Pnt                               P3d, P3d2;
  occ::handle<BRepAdaptor_Surface>     HS;
  Geom2dAdaptor_Curve                  C1, C2;
  Geom2dInt_GInter                     Inter;
  IntRes2d_Domain                      myDomain1;
  NCollection_IndexedMap<TopoDS_Shape> EMap;
  NCollection_Map<TopoDS_Shape>        auxmape;

  tolint = 1.e-10;
  HS     = new BRepAdaptor_Surface();
  HS->Initialize(F, false);

  for (TopoDS_Iterator Iter1(myShape); Iter1.More(); Iter1.Next())
  {
    if (Iter1.Value().ShapeType() == TopAbs_EDGE)
    {
      EMap.Add(Iter1.Value());
    }
  }

  Nbedges = EMap.Extent();
  if (!Nbedges)
  {
    if (Update)
    {
      BRepCheck::Add(aStatusList, BRepCheck_EmptyWire);
    }
    return (BRepCheck_EmptyWire);
  }

  IntRes2d_Domain*                              tabDom = new IntRes2d_Domain[Nbedges];
  NCollection_Array1<occ::handle<Geom2d_Curve>> tabCur(1, Nbedges);
  NCollection_Array1<Bnd_Box2d>                 boxes(1, Nbedges);

  for (i = 1; i <= Nbedges; i++)
  {
    const TopoDS_Edge& E1 = TopoDS::Edge(EMap.FindKey(i));
    if (i == 1)
    {
      occ::handle<Geom2d_Curve> pcu = BRep_Tool::CurveOnSurface(E1, F, first1, last1);
      if (pcu.IsNull())
      {
        retE1 = E1;
        if (Update)
        {
          BRepCheck::Add(aStatusList, BRepCheck_SelfIntersectingWire);
        }
        delete[] tabDom;
        return (BRepCheck_SelfIntersectingWire);
      }

      C1.Load(pcu);

      if (!C1.IsPeriodic())
      {
        if (C1.FirstParameter() > first1)
        {
          first1 = C1.FirstParameter();
        }
        if (C1.LastParameter() < last1)
        {
          last1 = C1.LastParameter();
        }
      }

      BRep_Tool::UVPoints(E1, F, pfirst1, plast1);
      myDomain1.SetValues(pfirst1, first1, tolint, plast1, last1, tolint);

      BndLib_Add2dCurve::Add(C1, first1, last1, Precision::PConfusion(), boxes(i));
    }
    else
    {
      C1.Load(tabCur(i));
      myDomain1 = tabDom[i - 1];
    }

    Inter.Perform(C1, myDomain1, tolint, tolint);

    if (Inter.IsDone())
    {
      int nbp = Inter.NbPoints();

      for (int p = 1; p <= nbp; p++)
      {
        const IntRes2d_IntersectionPoint& IP  = Inter.Point(p);
        const IntRes2d_Transition&        Tr1 = IP.TransitionOfFirst();
        const IntRes2d_Transition&        Tr2 = IP.TransitionOfSecond();
        if (Tr1.PositionOnCurve() == IntRes2d_Middle || Tr2.PositionOnCurve() == IntRes2d_Middle)
        {

          bool                          localok = false;
          double                        f, l;
          TopLoc_Location               L;
          const occ::handle<Geom_Curve> ConS = BRep_Tool::Curve(E1, L, f, l);
          if (!ConS.IsNull())
          {

            P3d = ConS->Value(IP.ParamOnFirst());
            P3d.Transform(L.Transformation());
          }
          else
          {
            gp_Pnt2d aP2d = C1.Value(IP.ParamOnFirst());
            P3d           = HS->Value(aP2d.X(), aP2d.Y());
          }

          TopExp_Explorer ExplVtx;
          for (ExplVtx.Init(E1, TopAbs_VERTEX); !localok && ExplVtx.More(); ExplVtx.Next())
          {
            gp_Pnt p3dvtt;
            double tolvtt, p3dvttDistanceP3d;

            const TopoDS_Vertex& vtt = TopoDS::Vertex(ExplVtx.Current());
            p3dvtt                   = BRep_Tool::Pnt(vtt);
            tolvtt                   = BRep_Tool::Tolerance(vtt);
            tolvtt                   = tolvtt * tolvtt;
            p3dvttDistanceP3d        = p3dvtt.SquareDistance(P3d);
            if (p3dvttDistanceP3d <= tolvtt)
            {
              localok = true;
            }
          }
          if (!localok)
          {
            retE1 = E1;
            if (Update)
            {
              BRepCheck::Add(aStatusList, BRepCheck_SelfIntersectingWire);
            }
            delete[] tabDom;
#ifdef OCCT_DEBUG
            static int numpoint = 0;
            std::cout << "point p" << ++numpoint << " " << P3d.X() << " " << P3d.Y() << " "
                      << P3d.Z() << std::endl;
            std::cout.flush();
#endif
            return (BRepCheck_SelfIntersectingWire);
          }
        }
      }
    }

    for (j = i + 1; j <= Nbedges; j++)
    {
      const TopoDS_Edge& E2 = TopoDS::Edge(EMap.FindKey(j));
      if (i == 1)
      {
        tabCur(j) = BRep_Tool::CurveOnSurface(E2, F, first2, last2);
        if (!tabCur(j).IsNull() && last2 > first2)
        {
          C2.Load(tabCur(j));

          if (!C2.IsPeriodic())
          {
            if (C2.FirstParameter() > first2)
            {
              first2 = C2.FirstParameter();
            }
            if (C2.LastParameter() < last2)
            {
              last2 = C2.LastParameter();
            }
          }

          BRep_Tool::UVPoints(E2, F, pfirst2, plast2);
          tabDom[j - 1].SetValues(pfirst2, first2, tolint, plast2, last2, tolint);

          BndLib_Add2dCurve::Add(C2, first2, last2, Precision::PConfusion(), boxes(j));
        }
        else
        {
          delete[] tabDom;
#ifdef OCCT_DEBUG
          std::cout << "BRepCheck_NoCurveOnSurface or BRepCheck_InvalidRange" << std::endl;
          std::cout.flush();
#endif
          if (tabCur(j).IsNull())
          {
            return (BRepCheck_NoCurveOnSurface);
          }
          return (BRepCheck_InvalidRange);
        }
      }
      else
      {
        C2.Load(tabCur(j));
      }

      if (boxes(i).IsOut(boxes(j)))
      {
        continue;
      }

      if (E1.IsSame(E2))
      {
        continue;
      }

      Inter.Perform(C1, myDomain1, C2, tabDom[j - 1], tolint, tolint);

      if (Inter.IsDone())
      {
        int                                                    nbp, nbs;
        double                                                 IP_ParamOnFirst, IP_ParamOnSecond;
        IntRes2d_Transition                                    Tr1, Tr2;
        NCollection_List<TopoDS_Shape>                         CommonVertices;
        NCollection_List<TopoDS_Shape>::Iterator               itl;
        NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> Vmap;

        TopoDS_Iterator it(E1);
        for (; it.More(); it.Next())
        {
          Vmap.Add(it.Value());
        }

        it.Initialize(E2);
        for (; it.More(); it.Next())
        {
          const TopoDS_Shape& V = it.Value();
          if (Vmap.Contains(V))
          {
            CommonVertices.Append(V);
          }
        }

        nbp              = Inter.NbPoints();
        nbs              = Inter.NbSegments();
        IP_ParamOnFirst  = 0.;
        IP_ParamOnSecond = 0.;

        for (int p = 1; p <= nbp; p++)
        {
          const IntRes2d_IntersectionPoint& IP = Inter.Point(p);
          IP_ParamOnFirst                      = IP.ParamOnFirst();
          IP_ParamOnSecond                     = IP.ParamOnSecond();
          Tr1                                  = IP.TransitionOfFirst();
          Tr2                                  = IP.TransitionOfSecond();
          if (Tr1.PositionOnCurve() == IntRes2d_Middle || Tr2.PositionOnCurve() == IntRes2d_Middle)
          {

            bool            localok = false;
            double          f1, l1, f2, l2;
            TopLoc_Location L, L2;

            const occ::handle<Geom_Curve> ConS  = BRep_Tool::Curve(E1, L, f1, l1);
            const occ::handle<Geom_Curve> ConS2 = BRep_Tool::Curve(E2, L2, f2, l2);

            if (f1 - IP_ParamOnFirst > ::Precision::PConfusion()
                || IP_ParamOnFirst - l1 > ::Precision::PConfusion()
                || f2 - IP_ParamOnSecond > ::Precision::PConfusion()
                || IP_ParamOnSecond - l2 > ::Precision::PConfusion())
              continue;
            double tolvtt = 0.;

            if (!ConS.IsNull())
            {
              P3d = ConS->Value(IP_ParamOnFirst);
              P3d.Transform(L.Transformation());
            }
            else
            {
              gp_Pnt2d aP2d = C1.Value(IP_ParamOnFirst);
              P3d           = HS->Value(aP2d.X(), aP2d.Y());
            }

            if (!ConS2.IsNull())
            {
              P3d2 = ConS2->Value(IP_ParamOnSecond);
              P3d2.Transform(L2.Transformation());
            }
            else
            {
              gp_Pnt2d aP2d = C2.Value(IP_ParamOnSecond);
              P3d2          = HS->Value(aP2d.X(), aP2d.Y());
            }

            itl.Initialize(CommonVertices);
            for (; itl.More(); itl.Next())
            {
              double p3dvttDistanceP3d, p3dvttDistanceP3d2;
              gp_Pnt p3dvtt;

              const TopoDS_Vertex& vtt = TopoDS::Vertex(itl.Value());
              p3dvtt                   = BRep_Tool::Pnt(vtt);
              tolvtt                   = BRep_Tool::Tolerance(vtt);
              tolvtt                   = 1.1 * tolvtt;
              tolvtt                   = tolvtt * tolvtt;
              p3dvttDistanceP3d        = p3dvtt.SquareDistance(P3d);
              p3dvttDistanceP3d2       = p3dvtt.SquareDistance(P3d2);

              if (p3dvttDistanceP3d <= tolvtt && p3dvttDistanceP3d2 <= tolvtt)
              {
                localok = true;
                break;
              }
            }

            if (!localok && !CommonVertices.IsEmpty())
            {
#ifdef OCCT_DEBUG
              std::cout << "\n------------------------------------------------------\n"
                        << std::endl;
              std::cout << "\n--- BRepCheck Wire: AutoIntersection Phase1 -> Erreur \n"
                        << std::endl;

#endif
              double distauvtxleplusproche, VParaOnEdge1, VParaOnEdge2;
              gp_Pnt VertexLePlusProche;

              VParaOnEdge1          = 0.;
              VParaOnEdge2          = 0.;
              distauvtxleplusproche = RealLast();

              itl.Initialize(CommonVertices);
              for (; itl.More(); itl.Next())
              {
                double disptvtx;
                gp_Pnt p3dvtt;

                const TopoDS_Vertex& vtt = TopoDS::Vertex(itl.Value());
                p3dvtt                   = BRep_Tool::Pnt(vtt);
                disptvtx                 = P3d.Distance(p3dvtt);
                if (disptvtx < distauvtxleplusproche)
                {
                  VertexLePlusProche    = p3dvtt;
                  distauvtxleplusproche = disptvtx;
                  VParaOnEdge1          = BRep_Tool::Parameter(vtt, E1);
                  VParaOnEdge2          = BRep_Tool::Parameter(vtt, E2);
                }

                else if (IsEqual(distauvtxleplusproche, disptvtx))
                {
                  double newVParaOnEdge1 = BRep_Tool::Parameter(vtt, E1);
                  double newVParaOnEdge2 = BRep_Tool::Parameter(vtt, E2);
                  if (std::abs(IP_ParamOnFirst - VParaOnEdge1)
                        + std::abs(IP_ParamOnSecond - VParaOnEdge2)
                      > std::abs(IP_ParamOnFirst - newVParaOnEdge1)
                          + std::abs(IP_ParamOnSecond - newVParaOnEdge2))
                  {
                    VertexLePlusProche = p3dvtt;
                    VParaOnEdge1       = newVParaOnEdge1;
                    VParaOnEdge2       = newVParaOnEdge2;
                  }
                }
              }

              if (VertexLePlusProche.Distance(P3d) <= gp::Resolution()
                  || VertexLePlusProche.Distance(P3d2) <= gp::Resolution())
              {

                localok = true;
              }
              else
              {
                gp_Lin Lig(VertexLePlusProche, gp_Vec(VertexLePlusProche, P3d));
                double du1   = 0.1 * (IP_ParamOnFirst - VParaOnEdge1);
                double du2   = 0.1 * (IP_ParamOnSecond - VParaOnEdge2);
                double maxd1 = 0., maxd2 = 0.;
                int    k;

                localok      = true;
                double tole1 = BRep_Tool::Tolerance(E1);
                for (k = 2; localok && k < 9; k++)
                {
                  double u = VParaOnEdge1 + k * du1;
                  gp_Pnt P1;

                  if (!ConS.IsNull())
                  {
                    P1 = ConS->Value(u);
                    P1.Transform(L.Transformation());
                  }
                  else
                  {
                    gp_Pnt2d aP2d = C1.Value(u);
                    P1            = HS->Value(aP2d.X(), aP2d.Y());
                  }

                  double d1 = Lig.Distance(P1);
                  if (d1 > maxd1)
                  {
                    maxd1 = d1;
                  }
                  if (d1 > tole1 * 2.0)
                  {
                    localok = false;
                  }
                }

                gp_Dir aTmpDir(P3d2.XYZ().Subtracted(VertexLePlusProche.XYZ()));

                Lig.SetDirection(aTmpDir);

                double tole2 = BRep_Tool::Tolerance(E2);
                for (k = 2; localok && k < 9; k++)
                {
                  double u = VParaOnEdge2 + k * du2;
                  gp_Pnt P2;

                  if (!ConS2.IsNull())
                  {
                    P2 = ConS2->Value(u);
                    P2.Transform(L2.Transformation());
                  }
                  else
                  {
                    gp_Pnt2d aP2d = C2.Value(u);
                    P2            = HS->Value(aP2d.X(), aP2d.Y());
                  }

                  double d2 = Lig.Distance(P2);
                  if (d2 > maxd2)
                  {
                    maxd2 = d2;
                  }
                  if (d2 > tole2 * 2.0)
                  {
                    localok = false;
                  }
                }
#ifdef OCCT_DEBUG
                if (localok)
                {
                  printf("--- BRepCheck Wire: AutoIntersection Phase2 -> Bon \n");
                  printf("--- distance Point Vertex : %10.7g (tol %10.7g)\n",
                         distauvtxleplusproche,
                         tolvtt);
                  printf("--- Erreur Max sur E1 : %10.7g  Tol_Edge:%10.7g\n", maxd1, tole1);
                  printf("--- Erreur Max sur E2 : %10.7g  Tol_Edge:%10.7g\n", maxd2, tole2);
                  fflush(stdout);
                }
                else
                {
                  printf("--- BRepCheck Wire: AutoIntersection Phase2 -> Erreur \n");
                  printf("--- distance Point Vertex : %10.7g (tol %10.7g)\n",
                         distauvtxleplusproche,
                         tolvtt);
                  printf("--- Erreur Max sur E1 : %10.7g  Tol_Edge:%10.7g\n", maxd1, tole1);
                  printf("--- Erreur Max sur E2 : %10.7g  Tol_Edge:%10.7g\n", maxd2, tole2);
                  fflush(stdout);
                }
#endif
              }
            }

            if (!localok)
            {
              retE1 = E1;
              retE2 = E2;
              if (Update)
              {
                BRepCheck::Add(aStatusList, BRepCheck_SelfIntersectingWire);
              }
#ifdef OCCT_DEBUG
              static int numpoint1 = 0;
              std::cout << "point p" << ++numpoint1 << " " << P3d.X() << " " << P3d.Y() << " "
                        << P3d.Z() << std::endl;
              std::cout.flush();
#endif
              delete[] tabDom;
              return (BRepCheck_SelfIntersectingWire);
            }
          }
        }

        for (int s = 1; s <= nbs; ++s)
        {
          const IntRes2d_IntersectionSegment& Seg = Inter.Segment(s);
          if (Seg.HasFirstPoint() && Seg.HasLastPoint())
          {
            bool                       localok;
            int                        k;
            IntRes2d_IntersectionPoint PSeg[2];
            IntRes2d_Position          aPCR1, aPCR2;

            localok = false;
            PSeg[0] = Seg.FirstPoint();
            PSeg[1] = Seg.LastPoint();

            for (k = 0; k < 2; ++k)
            {
              IP_ParamOnFirst  = PSeg[k].ParamOnFirst();
              IP_ParamOnSecond = PSeg[k].ParamOnSecond();
              Tr1              = PSeg[k].TransitionOfFirst();
              Tr2              = PSeg[k].TransitionOfSecond();
              aPCR1            = Tr1.PositionOnCurve();
              aPCR2            = Tr2.PositionOnCurve();

              if (aPCR1 != IntRes2d_Middle && aPCR2 != IntRes2d_Middle)
              {
                GeomAbs_CurveType aCT1, aCT2;

                aCT1 = C1.GetType();
                aCT2 = C2.GetType();
                if (aCT1 == GeomAbs_Line && aCT2 == GeomAbs_Line)
                {

                  double   aPAR_T, aT11, aT12, aT21, aT22, aT1m, aT2m;
                  double   aD2, aTolE1, aTolE2, aTol2;
                  gp_Lin2d aL1, aL2;
                  gp_Pnt2d aP1m;

                  aPAR_T = 0.43213918;

                  aTolE1 = BRep_Tool::Tolerance(E1);
                  aTolE2 = BRep_Tool::Tolerance(E2);
                  aTol2  = aTolE1 + aTolE2;
                  aTol2  = aTol2 * aTol2;

                  aL1 = C1.Line();
                  aL2 = C2.Line();

                  aT11 = PSeg[0].ParamOnFirst();
                  aT12 = PSeg[1].ParamOnFirst();
                  aT21 = PSeg[0].ParamOnSecond();
                  aT22 = PSeg[1].ParamOnSecond();

                  aT1m = (1. - aPAR_T) * aT11 + aPAR_T * aT12;
                  aP1m = C1.Value(aT1m);

                  aD2 = aL2.SquareDistance(aP1m);
                  if (aD2 < aTol2)
                  {
                    aT2m = ElCLib::Parameter(aL2, aP1m);
                    if (aT2m > aT21 && aT2m < aT22)
                    {
                      const gp_Dir2d& aDir1 = aL1.Direction();
                      const gp_Dir2d& aDir2 = aL2.Direction();
                      if (aDir1.IsParallel(aDir2, Precision::Angular()))
                      {
                        localok = false;
                        break;
                      }
                    }
                  }
                }

                localok = true;
                break;
              }

              double                         f, l, tolvtt;
              TopLoc_Location                L, L2;
              const occ::handle<Geom_Curve>& ConS  = BRep_Tool::Curve(E1, L, f, l);
              const occ::handle<Geom_Curve>& ConS2 = BRep_Tool::Curve(E2, L2, f, l);

              if (!ConS.IsNull())
              {
                P3d = ConS->Value(IP_ParamOnFirst);
                P3d.Transform(L.Transformation());
              }
              else
              {
                gp_Pnt2d aP2d = C1.Value(IP_ParamOnFirst);
                P3d           = HS->Value(aP2d.X(), aP2d.Y());
              }
              if (!ConS2.IsNull())
              {
                P3d2 = ConS2->Value(IP_ParamOnSecond);
                P3d2.Transform(L2.Transformation());
              }
              else
              {
                gp_Pnt2d aP2d = C2.Value(IP_ParamOnSecond);
                P3d2          = HS->Value(aP2d.X(), aP2d.Y());
              }

              itl.Initialize(CommonVertices);
              for (; itl.More(); itl.Next())
              {
                double p3dvttDistanceP3d, p3dvttDistanceP3d2;
                gp_Pnt p3dvtt;

                const TopoDS_Vertex& vtt = TopoDS::Vertex(itl.Value());
                p3dvtt                   = BRep_Tool::Pnt(vtt);
                tolvtt                   = BRep_Tool::Tolerance(vtt);
                tolvtt                   = 1.1 * tolvtt;
                tolvtt                   = tolvtt * tolvtt;
                p3dvttDistanceP3d        = p3dvtt.SquareDistance(P3d);
                p3dvttDistanceP3d2       = p3dvtt.SquareDistance(P3d2);
                if (p3dvttDistanceP3d <= tolvtt && p3dvttDistanceP3d2 <= tolvtt)
                {
                  localok = true;
                  break;
                }
              }
              if (localok)
              {
                break;
              }
            }

            if (!localok)
            {
              retE1 = E1;
              retE2 = E2;
              if (Update)
              {
                BRepCheck::Add(aStatusList, BRepCheck_SelfIntersectingWire);
              }
#ifdef OCCT_DEBUG
              static int numpoint1 = 0;
              std::cout << "point p" << ++numpoint1 << " " << P3d.X() << " " << P3d.Y() << " "
                        << P3d.Z() << std::endl;
              std::cout.flush();
#endif
              delete[] tabDom;
              return (BRepCheck_SelfIntersectingWire);
            }
          }
        }
      }
    }
  }

  delete[] tabDom;
  if (Update)
  {
    BRepCheck::Add(aStatusList, BRepCheck_NoError);
  }

  return (BRepCheck_NoError);
}

void BRepCheck_Wire::SetStatus(const BRepCheck_Status theStatus)
{
  BRepCheck::Add(*myMap(myShape), theStatus);
}

void BRepCheck_Wire::GeometricControls(const bool B)
{
  if (myGctrl != B)
  {
    if (B)
    {
      myCdone = false;
    }
    myGctrl = B;
  }
}

bool BRepCheck_Wire::GeometricControls() const
{
  return myGctrl;
}

static void Propagate(const NCollection_IndexedDataMap<TopoDS_Shape,
                                                       NCollection_List<TopoDS_Shape>,
                                                       TopTools_ShapeMapHasher>& mapVE,
                      const TopoDS_Shape&                                        edg,
                      NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>&    mapE)
{
  NCollection_List<TopoDS_Shape> currentEdges;
  currentEdges.Append(edg);

  do
  {
    NCollection_List<TopoDS_Shape>           nextEdges;
    NCollection_List<TopoDS_Shape>::Iterator itrc(currentEdges);
    for (; itrc.More(); itrc.Next())
    {
      const TopoDS_Shape& Edge = itrc.Value();
      if (!mapE.Contains(Edge))
        mapE.Add(Edge);

      TopExp_Explorer ex(Edge, TopAbs_VERTEX);
      for (; ex.More(); ex.Next())
      {
        const TopoDS_Vertex& vtx  = TopoDS::Vertex(ex.Current());
        int                  indv = mapVE.FindIndex(vtx);
        if (indv != 0)
        {
          const NCollection_List<TopoDS_Shape>& edges = mapVE(indv);

          NCollection_List<TopoDS_Shape>::Iterator itl(edges);
          for (; itl.More(); itl.Next())
          {
            const TopoDS_Shape& E = itl.Value();
            if (!Edge.IsSame(E) && !mapE.Contains(E))
            {
              mapE.Add(E);
              nextEdges.Append(E);
            }
          }
        }
      }
    }
    currentEdges = nextEdges;
  } while (!currentEdges.IsEmpty());
}

static TopAbs_Orientation GetOrientation(
  const NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>& mapE,
  const TopoDS_Edge&                                            edg)
{
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itm(mapE);
  for (; itm.More(); itm.Next())
  {
    if (itm.Key().IsSame(edg))
    {
      break;
    }
  }
  return itm.Key().Orientation();
}

void ChoixUV(const TopoDS_Vertex&            theVertex,
             const TopoDS_Edge&              theEdge,
             const TopoDS_Face&              theFace,
             NCollection_List<TopoDS_Shape>& theLOfShape)
{
  NCollection_List<TopoDS_Shape>::Iterator It(theLOfShape);
  while (It.More())
  {
    if (theEdge.IsSame(It.Value()))
      theLOfShape.Remove(It);
    else
      It.Next();
  }

  double aTol3d = BRep_Tool::Tolerance(theVertex);

  int                 anIndex = 0, anIndMin = 0;
  TopoDS_Edge         anEFound;
  gp_Pnt2d            aPntRef, aPnt;
  gp_Vec2d            aDerRef, aDer;
  double              aMinAngle, aMaxAngle, anAngle;
  double              a_gpResolution = gp::Resolution();
  TopAbs_Orientation  aVOrientation, anEdgOrientation;
  double              aParam = 0.0, aFirstParam = 0.0, aLastParam = 0.0, aParPiv = 0.0;
  BRepAdaptor_Surface aFaceSurface(theFace, false);

  occ::handle<Geom2d_Curve> C2d =
    BRep_Tool::CurveOnSurface(theEdge, theFace, aFirstParam, aLastParam);
  if (C2d.IsNull())
    return;

  aVOrientation    = theVertex.Orientation();
  anEdgOrientation = theEdge.Orientation();

  aParPiv   = (aVOrientation == anEdgOrientation) ? aFirstParam : aLastParam;
  aMinAngle = RealLast();
  aMaxAngle = RealFirst();

  CurveDirForParameter(C2d, aParPiv, aPntRef, aDerRef);

  if (aVOrientation != anEdgOrientation)
    aDerRef.Reverse();

  It.Initialize(theLOfShape);

  for (; It.More(); It.Next())
  {
    anIndex++;
    const TopoDS_Edge& anE = TopoDS::Edge(It.Value());
    C2d                    = BRep_Tool::CurveOnSurface(anE, theFace, aFirstParam, aLastParam);
    if (C2d.IsNull())
      continue;
    Geom2dAdaptor_Curve aCA(C2d);

    aParam = (aVOrientation != anE.Orientation()) ? aFirstParam : aLastParam;
    aPnt   = aCA.Value(aParam);

    if (!IsDistanceIn2DTolerance(aFaceSurface, aPnt, aPntRef, aTol3d, false))
      continue;

    CurveDirForParameter(aCA, aParam, aPnt, aDer);

    if (aVOrientation == anE.Orientation())
      aDer.Reverse();

    if ((aDerRef.Magnitude() <= a_gpResolution) || (aDer.Magnitude() <= a_gpResolution))

      continue;

    anAngle = -aDerRef.Angle(aDer);

    if (anAngle < 0.)
      anAngle += 2. * M_PI;

    if (theFace.Orientation() == TopAbs_FORWARD)
    {
      if (anAngle < aMinAngle)
      {
        anIndMin  = anIndex;
        aMinAngle = anAngle;
      }
    }
    else
    {
      if (anAngle > aMaxAngle)
      {
        anIndMin  = anIndex;
        aMaxAngle = anAngle;
      }
    }
  }

  if (anIndMin == 0)
    if (theLOfShape.Extent() == 1)
    {
      bool IsFound = true;
      anEFound     = TopoDS::Edge(theLOfShape.First());

      if (anEFound.IsNull() || BRep_Tool::Degenerated(theEdge) || BRep_Tool::Degenerated(anEFound))
        IsFound = false;
      else if (!IsDistanceIn2DTolerance(aFaceSurface, aPnt, aPntRef, aTol3d))
        IsFound = false;
      else

      {

        BRepAdaptor_Curve bcEdg(theEdge, theFace);
        BRepAdaptor_Curve bcEvois(anEFound, theFace);
        gp_Pnt            pEdg    = bcEdg.Value(aParPiv);
        gp_Pnt            pEFound = bcEvois.Value(aParam);

        IsFound = IsDistanceIn3DTolerance(pEdg, pEFound, aTol3d);
      }

      if (!IsFound)
      {
        theLOfShape.Clear();
      }
    }
    else
    {
      theLOfShape.Clear();
    }
  else
  {
    anIndex = 1;

    while (anIndex < anIndMin)
    {
      theLOfShape.RemoveFirst();
      anIndex++;
    }

    It.Initialize(theLOfShape);
    It.Next();

    while (It.More())
      theLOfShape.Remove(It);
  }
}

void CurveDirForParameter(const Geom2dAdaptor_Curve& aC2d,
                          const double               aPrm,
                          gp_Pnt2d&                  Pnt,
                          gp_Vec2d&                  aVec2d)
{
  double aTol = gp::Resolution();
  int    i;

  aC2d.D1(aPrm, Pnt, aVec2d);

  if (aVec2d.Magnitude() <= aTol)
  {
    for (i = 2; i <= 100; i++)
    {
      aVec2d = aC2d.DN(aPrm, i);
      if (aVec2d.Magnitude() > aTol)
      {
        break;
      }
    }
  }
}

static bool GetPnt2d(const TopoDS_Vertex& theVertex,
                     const TopoDS_Edge&   theEdge,
                     const TopoDS_Face&   theFace,
                     gp_Pnt2d&            aPnt)
{
  occ::handle<Geom2d_Curve> aPCurve;
  double                    aFPar;
  double                    aLPar;
  double                    aParOnEdge;
  TopoDS_Vertex             aFirstVtx;
  TopoDS_Vertex             aLastVtx;

  TopExp::Vertices(theEdge, aFirstVtx, aLastVtx);

  if (!theVertex.IsSame(aFirstVtx) && !theVertex.IsSame(aLastVtx))
    return false;

  aPCurve = BRep_Tool::CurveOnSurface(theEdge, theFace, aFPar, aLPar);

  if (aPCurve.IsNull())
    return false;

  aParOnEdge = BRep_Tool::Parameter(theVertex, theEdge);
  aPnt       = aPCurve->Value(aParOnEdge);

  return true;
}

static bool IsClosed2dForPeriodicFace(const TopoDS_Face&   theFace,
                                      const gp_Pnt2d&      theP1,
                                      const gp_Pnt2d&      theP2,
                                      const TopoDS_Vertex& theVertex)
{

  NCollection_List<TopoDS_Shape>                         aSeamEdges;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> NotSeams;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> ClosedEdges;
  TopExp_Explorer                                        anExp(theFace, TopAbs_EDGE);

  for (; anExp.More(); anExp.Next())
  {
    TopoDS_Edge anEdge = TopoDS::Edge(anExp.Current());

    if (NotSeams.Contains(anEdge))
      continue;

    if (!IsOriented(anEdge) || !BRep_Tool::IsClosed(anEdge, theFace))
    {
      NotSeams.Add(anEdge);
      continue;
    }

    if (!ClosedEdges.Add(anEdge))
      aSeamEdges.Append(anEdge);
  }

  if (aSeamEdges.Extent() == 0)
    return true;

  BRepAdaptor_Surface aFaceSurface(theFace, false);
  double              aTol      = BRep_Tool::Tolerance(theVertex);
  double              aUResol   = aFaceSurface.UResolution(aTol);
  double              aVResol   = aFaceSurface.VResolution(aTol);
  double              aVicinity = std::sqrt(aUResol * aUResol + aVResol * aVResol);
  double              aDistP1P2 = theP1.Distance(theP2);

  NCollection_List<TopoDS_Shape>::Iterator anIter(aSeamEdges);

  for (; anIter.More(); anIter.Next())
  {
    TopoDS_Edge aSeamEdge = TopoDS::Edge(anIter.Value());

    anExp.Init(aSeamEdge, TopAbs_VERTEX);
    for (; anExp.More(); anExp.Next())
    {
      const TopoDS_Shape& aVtx = anExp.Current();

      if (IsOriented(aVtx) && aVtx.IsSame(theVertex))
      {
        gp_Pnt2d aPnt1;
        gp_Pnt2d aPnt2;
        double   a2dTol;

        if (!GetPnt2d(theVertex, aSeamEdge, theFace, aPnt1))
          continue;

        aSeamEdge = TopoDS::Edge(aSeamEdge.Reversed());

        if (!GetPnt2d(theVertex, aSeamEdge, theFace, aPnt2))
          continue;

        a2dTol = aPnt1.Distance(aPnt2) * 1.e-2;
        a2dTol = std::max(a2dTol, aVicinity);

        if (aDistP1P2 > a2dTol)
          return false;
      }
    }
  }

  return true;
}
