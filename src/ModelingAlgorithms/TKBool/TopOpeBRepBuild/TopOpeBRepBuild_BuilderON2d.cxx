#include <BRep_Tool.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_BuilderON.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepDS.hpp>
#include <TopOpeBRepDS_connex.hpp>
#include <TopOpeBRepDS_EXPORT.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_ShapeShapeInterference.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_SC.hpp>

#define M_OUT(st) (st == TopAbs_OUT)
#define M_IN(st) (st == TopAbs_IN)
#define M_FORWARD(st) (st == TopAbs_FORWARD)
#define M_REVERSED(st) (st == TopAbs_REVERSED)

#ifdef OCCT_DEBUG
Standard_EXPORT bool TopOpeBRepBuild_GetcontextEINTERNAL();
Standard_EXPORT bool TopOpeBRepBuild_GetcontextEEXTERNAL();
Standard_EXPORT void debfillonf(const int iF);

Standard_EXPORT void debON2d(const int iF)
{
  std::cout << "++ debON2d " << iF << " " << std::endl;
}
#endif

Standard_EXPORT TopAbs_State FUN_build_TB(const TopOpeBRepBuild_PBuilder& PB, const int rank);

Standard_EXPORT bool FUN_keepEON(const TopOpeBRepBuild_Builder& B,
                                 const TopoDS_Shape&            sEG,
                                 const TopoDS_Shape&            sFOR,
                                 const TopoDS_Shape&            sFS,
                                 const bool                     EGBoundFOR,
                                 const TopOpeBRepDS_Transition& TFE,
                                 const TopAbs_State             TB1,
                                 const TopAbs_State             TB2);
Standard_EXPORT void FUN_coutmess(const TCollection_AsciiString& m);

Standard_EXPORTEXTERN TopOpeBRepDS_PDataStructure GLOBAL_DS2d;

void TopOpeBRepBuild_BuilderON::Perform2d(const TopOpeBRepBuild_PBuilder&     PB,
                                          const TopoDS_Shape&                 FOR,
                                          const TopOpeBRepBuild_PGTopo&       PG,
                                          const TopOpeBRepTool_Plos&          PLSclass,
                                          const TopOpeBRepBuild_PWireEdgeSet& PWES)
{
  myPB       = PB;
  myFace     = FOR;
  myPG       = PG;
  myPLSclass = PLSclass;
  myPWES     = PWES;

  const TopOpeBRepDS_DataStructure& BDS = myPB->DataStructure()->DS();
  if (GLOBAL_DS2d == nullptr)
    GLOBAL_DS2d = (TopOpeBRepDS_PDataStructure) new TopOpeBRepDS_DataStructure();
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lFEI =
    GLOBAL_DS2d->ShapeInterferences(FOR);

#ifdef OCCT_DEBUG
  int  iFOR;
  bool tFOR = myPB->GtraceSPS(FOR, iFOR);
  if (tFOR)
    debfillonf(iFOR);
  if (tFOR)
    std::cout << std::endl << "LI on F" << iFOR << std::endl;
#endif

  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itI(lFEI); itI.More();
       itI.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = itI.Value();
    TopOpeBRepDS_Kind                             GT, ST;
    int                                           GI, SI;
    FDS_data(I, GT, GI, ST, SI);

    const TopoDS_Edge& EG = TopoDS::Edge(BDS.Shape(GI));
#ifdef OCCT_DEBUG

#endif
    const NCollection_List<TopoDS_Shape>& lEspON = myPB->Splits(EG, TopAbs_ON);
#ifdef OCCT_DEBUG

#endif
    for (NCollection_List<TopoDS_Shape>::Iterator it(lEspON); it.More(); it.Next())
    {
      const TopoDS_Shape& EspON = it.Value();
      GFillONParts2dWES2(I, EspON);
    }
  }
}

void TopOpeBRepBuild_BuilderON::GFillONParts2dWES2(const occ::handle<TopOpeBRepDS_Interference>& I,
                                                   const TopoDS_Shape& EspON)
{
  const occ::handle<TopOpeBRepDS_HDataStructure>&  HDS = myPB->DataStructure();
  const TopOpeBRepDS_DataStructure&                BDS = HDS->DS();
  occ::handle<TopOpeBRepDS_ShapeShapeInterference> SSI(
    occ::down_cast<TopOpeBRepDS_ShapeShapeInterference>(I));
  TopAbs_State TB1, TB2;
  myPG->StatesON(TB1, TB2);
  TopOpeBRepDS_Kind GT, ST;
  int               GI, SI;
  FDS_data(SSI, GT, GI, ST, SI);

  bool               EGBoundFOR = SSI->GBound();
  const TopoDS_Face& FOR        = TopoDS::Face(myFace);
  int                iFOR       = BDS.Shape(FOR);
  const TopoDS_Edge& EG         = TopoDS::Edge(BDS.Shape(GI));
#ifdef OCCT_DEBUG

#endif
  const TopoDS_Face& FS = TopoDS::Face(BDS.Shape(SI));
#ifdef OCCT_DEBUG

#endif
  int rankEG = myPB->GShapeRank(EG);
#ifdef OCCT_DEBUG

#endif

  TopAbs_State TBEG = FUN_build_TB(myPB, rankEG);
#ifdef OCCT_DEBUG

#endif
  bool eghassd = HDS->HasSameDomain(EG);

#ifdef OCCT_DEBUG
  bool tFOR = myPB->GtraceSPS(iFOR);

  if (tFOR)
  {
    debON2d(iFOR);
  }
#endif

  int  iFCX     = SI;
  bool FFinSDSO = true;
#ifdef OCCT_DEBUG

#endif
  bool        FFinSD = true;
  TopoDS_Face FCX    = FS;

#ifdef OCCT_DEBUG

#endif

  TopAbs_Orientation oegFCXF;
  bool               EGBoundFCX = FUN_tool_orientEinFFORWARD(EG, FCX, oegFCXF);
  TopAbs_Orientation oegFCX;
#ifdef OCCT_DEBUG

#endif
  FUN_tool_orientEinF(EG, FCX, oegFCX);

  bool opeFus = myPB->Opefus();
  bool opeCut = myPB->Opec12() || myPB->Opec21();
  bool opeCom = myPB->Opecom();

  bool yap6 = true;
  yap6      = yap6 && FFinSD;

  yap6 = yap6 && (EGBoundFOR || EGBoundFCX);
  yap6 = yap6 && eghassd;

  if (yap6)
  {
#ifdef OCCT_DEBUG
    if (tFOR)
      std::cout << "* yap6 = 1" << std::endl;
#endif
    TopAbs_Orientation neworiE = TopAbs_FORWARD;

    bool b = false;

    bool SO = FFinSDSO;
#ifdef OCCT_DEBUG

#endif
    bool rk1 = (rankEG == 1);
    if (!rk1)
      return;

    TopAbs_Orientation oegFOR;
    bool               shareG = false;
    bool               ok     = false;
    if (EGBoundFCX)
      ok = FUN_ds_shareG(myPB->DataStructure(), iFOR, iFCX, GI, TopoDS::Edge(EspON), shareG);
    else if (EGBoundFOR)
      ok = FUN_ds_shareG(myPB->DataStructure(), iFCX, iFOR, GI, TopoDS::Edge(EspON), shareG);
    if (!ok)
      return;
#ifdef OCCT_DEBUG
    if (tFOR)
      std::cout << " shareG=" << shareG << std::endl;
#endif

    if (SO)
    {

      if (opeFus)
        b = shareG;
      else if (opeCut)
        b = (!shareG) && M_OUT(TBEG);
      else if (opeCom)
        b = shareG;
    }
    if (!b)
      return;

    if (!EGBoundFOR)
    {
      TopAbs_Orientation oegFCXF1;
      FUN_tool_orientEinFFORWARD(EG, FCX, oegFCXF1);
      neworiE = oegFCXF;
    }
    else if (EGBoundFOR)
    {
      FUN_tool_orientEinFFORWARD(EG, TopoDS::Face(FOR), oegFOR);
      neworiE = oegFOR;
    }

    double f, l;
    FUN_tool_bounds(TopoDS::Edge(EspON), f, l);
    double parON = (f + l) * .4352;

    bool ESO;
    ok = FUN_tool_curvesSO(TopoDS::Edge(EspON), parON, EG, ESO);
    if (!ok)
      return;
    if (!ESO)
      neworiE = TopAbs::Complement(neworiE);

    TopAbs_Orientation oFOR = BDS.Shape(iFOR).Orientation();
    TopAbs_Orientation oFCX = BDS.Shape(iFCX).Orientation();
    if (oFOR != oFCX)
      neworiE = TopAbs::Complement(neworiE);

    TopoDS_Shape newE = EspON;
    newE.Orientation(neworiE);
    myPWES->AddStartElement(newE);
#ifdef OCCT_DEBUG
    if (tFOR)
      std::cout << "  add spON e" << GI << std::endl;
#endif
    return;
  }
}
