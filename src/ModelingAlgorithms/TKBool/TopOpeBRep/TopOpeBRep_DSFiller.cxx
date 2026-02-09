#include <Precision.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRep_DSFiller.hpp>
#include <TopOpeBRep_EdgesFiller.hpp>
#include <TopOpeBRep_FaceEdgeFiller.hpp>
#include <TopOpeBRep_FacesFiller.hpp>
#include <TopOpeBRep_ShapeIntersector.hpp>
#include <TopOpeBRep_ShapeIntersector2d.hpp>
#include <TopOpeBRepDS_connex.hpp>
#include <TopOpeBRepDS_EXPORT.hpp>
#include <TopOpeBRepDS_Filter.hpp>
#include <TopOpeBRepDS_GapFiller.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_Reducer.hpp>
#include <TopOpeBRepDS_samdom.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <TopOpeBRepTool_box.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_SC.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>

extern void BREP_sortonparameter(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);
extern void BREP_mergePDS(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

#ifdef OCCT_DEBUG
Standard_EXPORT void debcomplete() {};
Standard_EXPORT void debcompleteds() {};
static int           Vdebfillerds = 0;

void debfillerds(void)
{
  Vdebfillerds++;
}

static int Vdebfillerff = 0;

void debfillerff(void)
{
  Vdebfillerff++;
}

static int Vdebfillerffsd = 0;

void debfillerffsd(void)
{
  Vdebfillerffsd++;
}

static int Vdebfilleree = 0;

void debfilleree(void)
{
  Vdebfilleree++;
}

static int Vdebfillereesd = 0;

void debfillereesd(void)
{
  Vdebfillereesd++;
}

static int Vdebfilleref = 0;

void debfilleref(void)
{
  Vdebfilleref++;
}

static int Vdebfillerfe = 0;

void debfillerfe(void)
{
  Vdebfillerfe++;
}

void debfillerreset(void)
{
  Vdebfillerds = Vdebfillerff = Vdebfilleree = Vdebfilleref = Vdebfillerfe = 0;
}

void debfillerss(const int i1, const int i2)
{
  std::cout << "+ + + + debfillerss " << i1 << " " << i2 << std::endl;
}

  #include <TopOpeBRepTool_KRO.hpp>
Standard_EXPORT TOPKRO KRO_DSFILLER_TOTAL("dsfiller");
extern TOPKRO          KRO_DSFILLER_INTFF;
extern TOPKRO          KRO_DSFILLER_INTEE;
extern TOPKRO          KRO_DSFILLER_INTFE;

static void FUN_RESET_KRO_DSFILLER()
{
  KRO_DSFILLER_TOTAL.Reset();
  KRO_DSFILLER_INTFF.Reset();
  KRO_DSFILLER_INTEE.Reset();
  KRO_DSFILLER_INTFE.Reset();
}

  #include <TopOpeBRep_traceSIFF.hpp>
  #include <BRepTools.hpp>
  #include <TopOpeBRepDS_ShapeShapeInterference.hpp>
  #include <TopOpeBRepDS_CurvePointInterference.hpp>

extern TopOpeBRep_traceSIFF SIFF;

extern bool TopOpeBRepTool_GettraceKRO();
extern bool TopOpeBRep_GettraceSIFF();
extern bool TopOpeBRepTool_GettraceEND();
extern bool TopOpeBRep_GettraceSHA(const int);
extern bool TopOpeBRep_GetcontextNONOG();
#endif

TopOpeBRep_DSFiller::TopOpeBRep_DSFiller()
    : myPShapeClassifier(nullptr)
{
}

TopOpeBRep_DSFiller::~TopOpeBRep_DSFiller()
{
  if (myPShapeClassifier)
  {
    delete myPShapeClassifier;
  }
}

TopOpeBRepTool_PShapeClassifier TopOpeBRep_DSFiller::PShapeClassifier() const
{
  return myPShapeClassifier;
}

void BREP_correctgbound(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();
  int                         i = 1, n = BDS.NbShapes();
  for (; i <= n; i++)
  {
    bool                ehassiv = false;
    const TopoDS_Shape& s       = BDS.Shape(i);
    TopAbs_ShapeEnum    t       = s.ShapeType();
    if (t != TopAbs_EDGE)
      continue;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it;
    it.Initialize(BDS.ChangeShapeInterferences(s));
    if (!it.More())
      continue;
    for (; it.More(); it.Next())
    {
      const occ::handle<TopOpeBRepDS_Interference>&    I = it.Value();
      occ::handle<TopOpeBRepDS_ShapeShapeInterference> SSI =
        occ::down_cast<TopOpeBRepDS_ShapeShapeInterference>(I);
      if (SSI.IsNull())
        continue;
      TopOpeBRepDS_Kind GK = SSI->GeometryType();
      if (GK != TopOpeBRepDS_VERTEX)
        continue;

      ehassiv = true;
      break;
    }

    if (!ehassiv)
      continue;

    NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> imev;
    TopExp::MapShapes(s, TopAbs_VERTEX, imev);

    it.Initialize(BDS.ChangeShapeInterferences(s));
    for (; it.More(); it.Next())
    {
      const occ::handle<TopOpeBRepDS_Interference>&    I = it.Value();
      occ::handle<TopOpeBRepDS_ShapeShapeInterference> SSI =
        occ::down_cast<TopOpeBRepDS_ShapeShapeInterference>(I);
      if (SSI.IsNull())
        continue;
      int               GI = SSI->Geometry();
      TopOpeBRepDS_Kind GK = SSI->GeometryType();
      if (GK != TopOpeBRepDS_VERTEX)
        continue;

      const TopoDS_Shape& v    = BDS.Shape(GI);
      bool                vofe = imev.Contains(v);
      SSI->SetGBound(vofe);
    }

    it.Initialize(BDS.ChangeShapeInterferences(s));
    for (; it.More(); it.Next())
    {
      const occ::handle<TopOpeBRepDS_Interference>&    I = it.Value();
      occ::handle<TopOpeBRepDS_ShapeShapeInterference> SSI =
        occ::down_cast<TopOpeBRepDS_ShapeShapeInterference>(I);
      if (SSI.IsNull())
        continue;
      int               GI = SSI->Geometry();
      TopOpeBRepDS_Kind GK = SSI->GeometryType();
      if (GK != TopOpeBRepDS_VERTEX)
        continue;
      const TopoDS_Shape& v      = BDS.Shape(GI);
      bool                vhassd = HDS->HasSameDomain(v);
      if (!vhassd)
        continue;
      int ivref = BDS.SameDomainRef(v);
      if (ivref == GI)
        continue;

      const TopoDS_Shape& vref    = BDS.Shape(ivref);
      bool                vrefofe = imev.Contains(vref);
      I->SetGeometry(ivref);
      SSI->SetGBound(vrefofe);
    }
  }
  return;
}

bool BREP_UnfillSameDomain(const TopoDS_Shape&                             F1,
                           const TopoDS_Shape&                             F2,
                           const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                           TopOpeBRepTool_ShapeClassifier&                 SC)
{
  bool         unfill = true;
  TopAbs_State st1 = TopAbs_UNKNOWN, st2 = TopAbs_UNKNOWN;
  int          samdom = 1;
  st1                 = SC.StateShapeShape(F1, F2, samdom);
  st2                 = SC.StateShapeShape(F2, F1, samdom);
  unfill              = ((st1 == TopAbs_OUT) && (st2 == TopAbs_OUT))
           || ((st1 == TopAbs_UNKNOWN) && (st2 == TopAbs_UNKNOWN));
  if (unfill)
  {
    TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();
    BDS.UnfillShapesSameDomain(F1, F2);
  }
  return unfill;
}

static bool FUN_shareNOG(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                         const TopoDS_Shape&                             lFF1,
                         const TopoDS_Shape&                             lFF2)
{
  const TopOpeBRepDS_DataStructure&                             BDS = HDS->DS();
  const TopoDS_Face&                                            F1  = TopoDS::Face(lFF1);
  const TopoDS_Face&                                            F2  = TopoDS::Face(lFF2);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> map1;
  TopExp::MapShapes(F1, TopAbs_EDGE, map1);
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> map2;
  TopExp::MapShapes(F2, TopAbs_EDGE, map2);
  double tola = Precision::Angular();

  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lIF1 = BDS.ShapeInterferences(F1);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(lIF1);
  for (; it1.More(); it1.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I1 = it1.Value();
    int                                           G  = I1->Geometry();
    TopOpeBRepDS_Kind                             GT = I1->GeometryType();
    if (GT != TopOpeBRepDS_EDGE)
      continue;
    const TopoDS_Shape& EG = BDS.Shape(G);
    if (map2.Contains(EG))
      return false;
  }
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lIF2 = BDS.ShapeInterferences(F2);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(lIF2);
  for (; it2.More(); it2.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I2 = it2.Value();
    int                                           G  = I2->Geometry();
    TopOpeBRepDS_Kind                             GT = I2->GeometryType();
    if (GT != TopOpeBRepDS_EDGE)
      continue;
    const TopoDS_Shape& EG = BDS.Shape(G);
    if (map1.Contains(EG))
      return false;
  }

  TopExp_Explorer ex1(F1, TopAbs_EDGE);
  for (; ex1.More(); ex1.Next())
  {
    const TopoDS_Edge& e1   = TopoDS::Edge(ex1.Current());
    bool               hsd1 = HDS->HasSameDomain(e1);
    if (hsd1)
    {
      NCollection_List<TopoDS_Shape>::Iterator itsd1(HDS->SameDomain(e1));
      for (; itsd1.More(); itsd1.Next())
      {
        const TopoDS_Shape& e2 = itsd1.Value();
        if (map2.Contains(e2))
          return false;
      }
    }

    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lie1 =
      BDS.ShapeInterferences(e1);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator iter1(lie1);
    for (; iter1.More(); iter1.Next())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I1  = iter1.Value();
      int                                           S1  = I1->Support();
      TopOpeBRepDS_Kind                             ST1 = I1->SupportType();
      if (ST1 != TopOpeBRepDS_EDGE)
        continue;
      const TopoDS_Edge& e2 = TopoDS::Edge(BDS.Shape(S1));
      if (!map2.Contains(e2))
        continue;

      TopOpeBRepDS_Kind GT1 = I1->GeometryType();
      if (GT1 == TopOpeBRepDS_POINT)
      {
        occ::handle<TopOpeBRepDS_CurvePointInterference> CPI1 =
          occ::down_cast<TopOpeBRepDS_CurvePointInterference>(I1);
        double par1 = CPI1->Parameter();
        double par2;
        bool   ok = FUN_tool_parE(e1, par1, e2, par2);
        if (!ok)
        {
#ifdef OCCT_DEBUG
          std::cout << "**********TopOpeBRep FUN_shareNOG**********" << std::endl;
#endif
          return false;
        }
        gp_Vec tge1 = FUN_tool_tggeomE(par1, e1);
        gp_Vec tge2 = FUN_tool_tggeomE(par2, e2);
        double dot  = gp_Dir(tge1).Dot(gp_Dir(tge2));
        double x    = std::abs(1 - std::abs(dot));
        if (x > tola)
          return false;

        gp_Vec xxF1 = FUN_tool_getgeomxx(F1, e1, par1);
        gp_Vec xxF2 = FUN_tool_getgeomxx(F2, e2, par2);
        dot         = gp_Dir(xxF1).Dot(gp_Dir(xxF2));
        if (dot > 0)
          return false;
      }
    }
  }
  return true;
}

void TopOpeBRep_DSFiller::Insert(const TopoDS_Shape&                             aS1,
                                 const TopoDS_Shape&                             aS2,
                                 const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                 const bool                                      orientFORWARD)
{
  InsertIntersection(aS1, aS2, HDS, orientFORWARD);
  Complete(HDS);
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::Insert" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::InsertIntersection(const TopoDS_Shape&                             aS1,
                                             const TopoDS_Shape&                             aS2,
                                             const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                             const bool orientFORWARD)
{
  FBOX_Prepare();
  FC2D_Prepare(aS1, aS2);

  if (myPShapeClassifier == nullptr)
    myPShapeClassifier = new TopOpeBRepTool_ShapeClassifier();
  myFacesFiller.SetPShapeClassifier(myPShapeClassifier);

#ifdef OCCT_DEBUG
  bool tsiff = TopOpeBRep_GettraceSIFF();
  bool tkro  = TopOpeBRepTool_GettraceKRO();
  if (tsiff)
    SIFF.Start("DSFiller debut tsif ", std::cout);
  if (tkro)
  {
    FUN_RESET_KRO_DSFILLER();
    KRO_DSFILLER_TOTAL.Start();
  }
#endif

  if (!CheckInsert(aS1, aS2))
  {
    HDS->AddAncestors(aS1);
    HDS->AddAncestors(aS2);
    FDSCNX_Prepare(aS1, aS2, HDS);
    return;
  }

  TopoDS_Shape S1 = aS1;
  TopoDS_Shape S2 = aS2;
  if (orientFORWARD)
  {
    if (S1.Orientation() == TopAbs_REVERSED)
    {
      S1.Orientation(TopAbs_FORWARD);
    }
    if (S2.Orientation() == TopAbs_REVERSED)
    {
      S2.Orientation(TopAbs_FORWARD);
    }
  }

  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();
  BDS.AddShape(S1, 1);
  BDS.AddShape(S2, 2);
  TopExp_Explorer ex1, ex2;
  for (ex1.Init(S1, TopAbs_SOLID); ex1.More(); ex1.Next())
  {
    const TopoDS_Shape& so1 = ex1.Current();
    for (ex2.Init(S2, TopAbs_SOLID); ex2.More(); ex2.Next())
    {
      const TopoDS_Shape& so2 = ex2.Current();
      BDS.FillShapesSameDomain(so1, so2);
    }
  }

#ifdef OCCT_DEBUG
  debfillerreset();
#endif

  bool         FFsamdom    = true;
  bool         islFFsamdom = false;
  bool         isFF        = false;
  bool         isFFsamdom  = false;
  bool         isEE        = false;
  bool         unfill      = false;
  TopoDS_Shape lFF1, lFF2;

  TopOpeBRepDS_DataStructure& aDataStructure = HDS->ChangeDS();

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapOfRejectedShapesObj =
    aDataStructure.ChangeMapOfRejectedShapesObj();
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>& aMapOfRejectedShapesTool =
    aDataStructure.ChangeMapOfRejectedShapesTool();
  aMapOfRejectedShapesObj.Clear();
  aMapOfRejectedShapesTool.Clear();

  NCollection_List<TopoDS_Shape> aListObj, aListTool;

  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> aMapOfSolids;

  TopExp::MapShapes(S2, TopAbs_SOLID, aMapOfSolids);
  if (!aMapOfSolids.IsEmpty())
    myShapeIntersector.RejectedFaces(S1, S2, aListObj);

  aMapOfSolids.Clear();
  TopExp::MapShapes(S1, TopAbs_SOLID, aMapOfSolids);
  if (!aMapOfSolids.IsEmpty())
    myShapeIntersector.RejectedFaces(S2, S1, aListTool);

  NCollection_List<TopoDS_Shape>::Iterator anIt(aListObj);

  for (; anIt.More(); anIt.Next())
  {
    const TopoDS_Shape& aS = anIt.Value();
    aMapOfRejectedShapesObj.Add(aS);
  }

  NCollection_List<TopoDS_Shape>::Iterator anIt1(aListTool);
  for (; anIt1.More(); anIt1.Next())
  {
    const TopoDS_Shape& aS = anIt1.Value();
    aMapOfRejectedShapesTool.Add(aS);
  }

  myShapeIntersector.InitIntersection(S1, S2);
  while (myShapeIntersector.MoreIntersection())
  {

#ifdef OCCT_DEBUG
    int  i1deb = myShapeIntersector.Index(1);
    int  i2deb = myShapeIntersector.Index(2);
    bool b1deb = TopOpeBRep_GettraceSHA(i1deb);
    bool b2deb = TopOpeBRep_GettraceSHA(i2deb);
    if (b1deb && b2deb)
      debfillerss(i1deb, i2deb);
    debfillerds();
#endif

    const TopoDS_Shape& gs1 = myShapeIntersector.CurrentGeomShape(1);
    const TopoDS_Shape& gs2 = myShapeIntersector.CurrentGeomShape(2);
    TopAbs_ShapeEnum    t1  = gs1.ShapeType();
    TopAbs_ShapeEnum    t2  = gs2.ShapeType();

    isFF       = ((t1 == TopAbs_FACE) && (t2 == TopAbs_FACE));
    isFFsamdom = false;
    isEE       = ((t1 == TopAbs_EDGE) && (t2 == TopAbs_EDGE));
    unfill     = (!isEE && islFFsamdom);

    if (unfill)
    {
      if (myPShapeClassifier == nullptr)
        myPShapeClassifier = new TopOpeBRepTool_ShapeClassifier();
      unfill = BREP_UnfillSameDomain(lFF1, lFF2, HDS, *myPShapeClassifier);
    }

    if (isFF)
    {
#ifdef OCCT_DEBUG
      if (tsiff)
        SIFF.Add(i1deb, i2deb);
      debfillerff();
#endif
      TopOpeBRep_FacesIntersector& FF = myShapeIntersector.ChangeFacesIntersector();
      isFFsamdom                      = FF.SameDomain();
      FFsamdom                        = FFsamdom && isFFsamdom;
      if (isFFsamdom)
      {
        lFF1 = FF.Face(1);
        lFF2 = FF.Face(2);
      }

#ifdef OCCT_DEBUG
      if (isFFsamdom)
        debfillerffsd();
      int exf1 = myShapeIntersector.Index(1);
      int exf2 = myShapeIntersector.Index(2);
      myFacesFiller.SetTraceIndex(exf1, exf2);
#endif
      myFacesFiller.Insert(gs1, gs2, FF, HDS);
    }

    else if ((t1 == TopAbs_EDGE) && (t2 == TopAbs_EDGE))
    {
#ifdef OCCT_DEBUG
      debfilleree();
#endif
      TopOpeBRep_EdgesIntersector& EE = myShapeIntersector.ChangeEdgesIntersector();
      EE.Dimension(2);
#ifdef OCCT_DEBUG
      bool EEsamedomain =
#endif
        EE.SameDomain();
#ifdef OCCT_DEBUG
      if (EEsamedomain)
        debfillereesd();
#endif
      if (islFFsamdom)
      {
        myEdgesFiller.Face(1, lFF1);
        myEdgesFiller.Face(2, lFF2);
      }
      myEdgesFiller.Insert(gs1, gs2, EE, HDS);
    }

    else if ((t1 == TopAbs_FACE) && (t2 == TopAbs_EDGE))
    {
#ifdef OCCT_DEBUG
      debfillerfe();
#endif
      TopOpeBRep_FaceEdgeIntersector& FE = myShapeIntersector.ChangeFaceEdgeIntersector();
      myFaceEdgeFiller.Insert(gs1, gs2, FE, HDS);
    }

    else if ((t1 == TopAbs_EDGE) && (t2 == TopAbs_FACE))
    {
#ifdef OCCT_DEBUG
      debfilleref();
#endif
      TopOpeBRep_FaceEdgeIntersector& FE = myShapeIntersector.ChangeFaceEdgeIntersector();
      myFaceEdgeFiller.Insert(gs2, gs1, FE, HDS);
    }

    islFFsamdom = isFFsamdom;
    myShapeIntersector.NextIntersection();
  }

  if (FFsamdom)
    FUN_ds_FillSDMFaces(HDS);

  else
    FUN_ds_addSEsdm1d(HDS);

  if (FFsamdom)
    HDS->ChangeDS().Isfafa(true);

  if (islFFsamdom && !isEE)
  {
    if (myPShapeClassifier == nullptr)
      myPShapeClassifier = new TopOpeBRepTool_ShapeClassifier();
    unfill = BREP_UnfillSameDomain(lFF1, lFF2, HDS, *myPShapeClassifier);
  }

  BREP_sortonparameter(HDS);
  BREP_correctgbound(HDS);
  BREP_mergePDS(HDS);

  HDS->AddAncestors(S1);
  HDS->AddAncestors(S2);
  FDSCNX_Prepare(aS1, aS2, HDS);
  FDSSDM_prepare(HDS);

#ifdef OCCT_DEBUG
  if (tkro)
    KRO_DSFILLER_TOTAL.Stop();
  if (tsiff)
    SIFF.End("DSFiller fin tsif ", std::cout);
#endif
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::InsertIntersection" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::Complete(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
#ifdef OCCT_DEBUG
  debcomplete();
#endif
  GapFiller(HDS);
  CompleteDS(HDS);
  Filter(HDS);
  Reducer(HDS);
  RemoveUnsharedGeometry(HDS);
  Checker(HDS);
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::Complete" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::GapFiller(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const
{
  TopOpeBRepDS_GapFiller GF(HDS);
  GF.Perform();
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::GapFiller" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::CompleteDS(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const
{
#ifdef OCCT_DEBUG
  debcompleteds();
#endif
  const TopoDS_Shape& S1 = myShapeIntersector.Shape(1);
  const TopoDS_Shape& S2 = myShapeIntersector.Shape(2);
  if (S1.IsNull() || S2.IsNull())
    return;

  FUN_ds_PointToVertex(HDS);
  FUN_ds_redusamsha(HDS);
  FUN_ds_PURGEforE9(HDS);
  FUN_ds_completeforSE8(HDS);
  FUN_ds_completeforSE1(HDS);
  FUN_ds_completeforSE2(HDS);
  FUN_ds_completeforSE3(HDS);
  FUN_ds_completeforSE4(HDS);
  FUN_ds_completeforSE5(HDS);
  FUN_ds_completeforSE6(HDS);

  FUN_ds_completeforE7(HDS);
  FUN_ds_completeforSE9(HDS);
  FUN_ds_complete1dForSESDM(HDS);
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::CompleteDS" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::Filter(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const
{
  TopOpeBRepDS_Filter F(HDS);
  F.ProcessEdgeInterferences();
  F.ProcessCurveInterferences();
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::Filter" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::Reducer(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const
{
  TopOpeBRepDS_Reducer R(HDS);
  R.ProcessEdgeInterferences();
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::Reducer" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::RemoveUnsharedGeometry(
  const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  bool processNOG = true;
#ifdef OCCT_DEBUG
  if (TopOpeBRep_GetcontextNONOG())
    processNOG = false;
#endif
  if (!processNOG)
    return;

  const TopOpeBRepDS_DataStructure& BDS = HDS->DS();
  int                               nbs = BDS.NbShapes();
  for (int i = 1; i <= nbs; i++)
  {
    TopoDS_Shape S = BDS.Shape(i);
    if (S.ShapeType() != TopAbs_FACE)
      continue;
    bool hsd = HDS->HasSameDomain(S);
    if (!hsd)
      continue;
    int rkS = BDS.AncestorRank(S);
    if (rkS != 1)
      continue;
    const NCollection_List<TopoDS_Shape>&    lSsd = BDS.ShapeSameDomain(S);
    NCollection_List<TopoDS_Shape>::Iterator itsd(lSsd);
    for (; itsd.More(); itsd.Next())
    {
      TopoDS_Shape Ssd   = itsd.Value();
      int          rkSsd = BDS.AncestorRank(Ssd);
      if (rkSsd == 1)
        continue;

      bool unfill = ::FUN_shareNOG(HDS, S, Ssd);
      unfill      = unfill && FUN_ds_sdm(BDS, S, Ssd) && FUN_ds_sdm(BDS, Ssd, S);
      if (unfill)
      {
        if (myPShapeClassifier == nullptr)
          myPShapeClassifier = new TopOpeBRepTool_ShapeClassifier();
        unfill = BREP_UnfillSameDomain(S, Ssd, HDS, *myPShapeClassifier);
      }
    }
  }
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::RemoveUnsharedGeometry" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::Checker(const occ::handle<TopOpeBRepDS_HDataStructure>&) const {}

void TopOpeBRep_DSFiller::Insert2d(const TopoDS_Shape&                             aS1,
                                   const TopoDS_Shape&                             aS2,
                                   const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  InsertIntersection2d(aS1, aS2, HDS);
  CompleteDS2d(HDS);
#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::Insert2d" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::InsertIntersection2d(const TopoDS_Shape&                             aS1,
                                               const TopoDS_Shape&                             aS2,
                                               const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  if (myPShapeClassifier == nullptr)
  {
    myPShapeClassifier = new TopOpeBRepTool_ShapeClassifier();
  }
  myFacesFiller.SetPShapeClassifier(myPShapeClassifier);

  if (!ClearShapeSameDomain(aS1, aS2, HDS))
    return;

  const TopoDS_Shape&         S1   = aS1;
  const TopoDS_Shape&         S2   = aS2;
  TopOpeBRepDS_DataStructure& BDS1 = HDS->ChangeDS();
  BDS1.AddShape(S1, 1);
  BDS1.AddShape(S2, 2);

  TopoDS_Shape lFF1, lFF2;
  bool         isFFsamdom = false;

  myShapeIntersector2d.InitIntersection(S1, S2);
  while (myShapeIntersector2d.MoreIntersection())
  {

    const TopoDS_Shape& gs1 = myShapeIntersector2d.CurrentGeomShape(1);
    const TopoDS_Shape& gs2 = myShapeIntersector2d.CurrentGeomShape(2);
    TopAbs_ShapeEnum    t1  = gs1.ShapeType();
    TopAbs_ShapeEnum    t2  = gs2.ShapeType();

    bool isFF   = ((t1 == TopAbs_FACE) && (t2 == TopAbs_FACE));
    bool isEE   = ((t1 == TopAbs_EDGE) && (t2 == TopAbs_EDGE));
    bool unfill = (!isEE && isFFsamdom);
    if (unfill)
    {
      if (myPShapeClassifier == nullptr)
        myPShapeClassifier = new TopOpeBRepTool_ShapeClassifier();

      TopAbs_State st1 = TopAbs_UNKNOWN, st2 = TopAbs_UNKNOWN;
      int          samdom = 1;
      st1                 = myPShapeClassifier->StateShapeShape(lFF1, lFF2, samdom);
      st2                 = myPShapeClassifier->StateShapeShape(lFF2, lFF1, samdom);
      unfill              = ((st1 == TopAbs_OUT) && (st2 == TopAbs_OUT))
               || ((st1 == TopAbs_UNKNOWN) && (st2 == TopAbs_UNKNOWN));
      if (unfill)
      {
        TopOpeBRepDS_DataStructure& BDS2 = HDS->ChangeDS();
        if (!lFF1.IsNull() && !lFF2.IsNull())
          BDS2.UnfillShapesSameDomain(lFF1, lFF2);
      }
    }

    if (isFF)
    {
      isFFsamdom = true;
      myShapeIntersector2d.ChangeEdgesIntersector().SetFaces(gs1, gs2);
      lFF1 = gs1;
      lFF2 = gs2;
      BDS1.FillShapesSameDomain(gs1, gs2);
    }
    else if ((t1 == TopAbs_EDGE) && (t2 == TopAbs_EDGE))
    {
      TopOpeBRep_EdgesIntersector& EE = myShapeIntersector2d.ChangeEdgesIntersector();
      EE.Dimension(2);
      myEdgesFiller.Face(1, lFF1);
      myEdgesFiller.Face(2, lFF2);
      myEdgesFiller.Insert(gs1, gs2, EE, HDS);
    }
    myShapeIntersector2d.NextIntersection();
  }

  BREP_sortonparameter(HDS);
  BREP_correctgbound(HDS);
  BREP_mergePDS(HDS);

#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::InsertIntersection2d" << std::endl;
#endif
}

void TopOpeBRep_DSFiller::CompleteDS2d(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS) const
{
  const TopoDS_Shape& S1 = myShapeIntersector2d.Shape(1);
  const TopoDS_Shape& S2 = myShapeIntersector2d.Shape(2);
  if (S1.IsNull() || S2.IsNull())
    return;
  HDS->AddAncestors(S1);
  HDS->AddAncestors(S2);

  TopOpeBRepDS_Filter F(HDS);
  F.ProcessEdgeInterferences();
  F.ProcessCurveInterferences();
  TopOpeBRepDS_Reducer R(HDS);
  R.ProcessEdgeInterferences();

#ifdef OCCT_DEBUG
  if (TopOpeBRepTool_GettraceEND())
    std::cout << "DSFiller::CompleteDS2d" << std::endl;
#endif
}

bool TopOpeBRep_DSFiller::IsMadeOf1d(const TopoDS_Shape& aS) const
{

  bool             res = false;
  TopAbs_ShapeEnum t   = aS.ShapeType();
  if (t == TopAbs_WIRE)
  {
    res = true;
  }
  else if (t == TopAbs_EDGE)
  {
    res = true;
  }
  else if (t == TopAbs_COMPOUND)
  {
    TopoDS_Iterator it(aS);
    if (!it.More())
    {
      res = false;
    }
    else
    {
      res = true;
      for (; it.More(); it.Next())
      {
        const TopoDS_Shape& S    = it.Value();
        bool                is1d = IsMadeOf1d(S);
        if (!is1d)
        {
          res = false;
          break;
        }
      }
    }
  }
  else
  {
    res = false;
  }

  return res;
}

bool TopOpeBRep_DSFiller::IsContext1d(const TopoDS_Shape& aS) const
{
  bool is1d = IsMadeOf1d(aS);
#ifdef OCCT_DEBUG
  if (is1d)
    std::cout << "TopOpeBRep_DSFiller : 1d" << std::endl;
#endif
  return is1d;
}

void TopOpeBRep_DSFiller::Insert1d(const TopoDS_Shape&                             aS1,
                                   const TopoDS_Shape&                             aS2,
                                   const TopoDS_Face&                              aF1,
                                   const TopoDS_Face&                              aF2,
                                   const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                   const bool                                      orientFORWARD)
{
  if (!CheckInsert(aS1, aS2))
    return;

  TopoDS_Shape S1 = aS1;
  TopoDS_Shape S2 = aS2;
  if (orientFORWARD)
  {
    if (S1.Orientation() == TopAbs_REVERSED)
      S1.Orientation(TopAbs_FORWARD);
    if (S2.Orientation() == TopAbs_REVERSED)
      S2.Orientation(TopAbs_FORWARD);
  }
  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();

  BDS.AddShape(S1, 1);
  BDS.AddShape(S2, 2);

  myShapeIntersector.InitIntersection(S1, S2, aF1, aF2);
  for (; myShapeIntersector.MoreIntersection(); myShapeIntersector.NextIntersection())
  {

    const TopoDS_Shape& gs1 = myShapeIntersector.CurrentGeomShape(1);
    const TopoDS_Shape& gs2 = myShapeIntersector.CurrentGeomShape(2);
    TopAbs_ShapeEnum    t1 = gs1.ShapeType(), t2 = gs2.ShapeType();

    if ((t1 == TopAbs_EDGE) && (t2 == TopAbs_EDGE))
    {
      TopOpeBRep_EdgesIntersector& EE = myShapeIntersector.ChangeEdgesIntersector();
      EE.Dimension(1);
      myEdgesFiller.Insert(gs1, gs2, EE, HDS);
    }
  }

  CompleteDS(HDS);
}

bool TopOpeBRep_DSFiller::CheckInsert(const TopoDS_Shape& aS1, const TopoDS_Shape& aS2) const
{
  return !aS1.IsEqual(aS2);
}

bool TopOpeBRep_DSFiller::ClearShapeSameDomain(const TopoDS_Shape&                             aS1,
                                               const TopoDS_Shape&                             aS2,
                                               const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
{
  TopOpeBRepDS_DataStructure& DS = HDS->ChangeDS();
  const bool                  b  = false;
  if (!CheckInsert(aS1, aS2))
    return b;
  TopExp_Explorer exp1(aS1, TopAbs_FACE), exp2(aS2, TopAbs_FACE);
  for (; exp1.More(); exp1.Next())
  {
    const TopoDS_Shape& Shape1 = exp1.Current();
    if (!HDS->HasShape(Shape1))
      if (HDS->HasSameDomain(Shape1))
      {
        NCollection_List<TopoDS_Shape>& los = DS.ChangeShapeSameDomain(Shape1);
        los.Clear();
      }
  }
  for (; exp2.More(); exp2.Next())
  {
    const TopoDS_Shape& Shape2 = exp2.Current();
    if (HDS->HasShape(Shape2))
      if (HDS->HasSameDomain(Shape2))
      {
        NCollection_List<TopoDS_Shape>& los = DS.ChangeShapeSameDomain(Shape2);
        los.Clear();
      }
  }
  return true;
}

TopOpeBRep_ShapeIntersector& TopOpeBRep_DSFiller::ChangeShapeIntersector()
{
  return myShapeIntersector;
}

TopOpeBRep_ShapeIntersector2d& TopOpeBRep_DSFiller::ChangeShapeIntersector2d()
{
  return myShapeIntersector2d;
}

TopOpeBRep_FacesFiller& TopOpeBRep_DSFiller::ChangeFacesFiller()
{
  return myFacesFiller;
}

TopOpeBRep_EdgesFiller& TopOpeBRep_DSFiller::ChangeEdgesFiller()
{
  return myEdgesFiller;
}

TopOpeBRep_FaceEdgeFiller& TopOpeBRep_DSFiller::ChangeFaceEdgeFiller()
{
  return myFaceEdgeFiller;
}
