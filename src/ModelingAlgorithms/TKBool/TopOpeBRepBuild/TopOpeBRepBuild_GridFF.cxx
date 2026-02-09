#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_define.hpp>
#include <TopOpeBRepBuild_FaceBuilder.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>
#include <TopOpeBRepBuild_ShapeSet.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepDS.hpp>
#include <TopOpeBRepDS_CurveIterator.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_InterferenceTool.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>
#include <TopOpeBRepTool_ShapeTool.hpp>
#include <TopOpeBRepTool_TOOL.hpp>

#ifdef OCCT_DEBUG
extern void* GFABUMAKEFACEPWES_DEB;
  #define DEBSHASET(sarg, meth, shaset, str)                                                       \
    TCollection_AsciiString sarg((meth));                                                          \
    (sarg) = (sarg) + (shaset).DEBNumber() + (str);
int GLOBAL_iexE = 0;

Standard_EXPORT void debfillw(const int) {}

Standard_EXPORT void debfille(const int) {}

Standard_EXPORT void debffwesON(const int i)
{
  std::cout << "++ debffwesON " << i << std::endl;
}

Standard_EXPORT void debffwesmf(const int i)
{
  std::cout << "++ debffwesmf " << i << std::endl;
}

Standard_EXPORT void debfillf(const int i)
{
  std::cout << "++ debfillf " << i << std::endl;
}

Standard_EXPORT void debsplite(const int i)
{
  std::cout << "++ debsplite " << i << std::endl;
}

Standard_EXPORT void debmergef(const int i)
{
  std::cout << "++ debmergef " << i << std::endl;
}

Standard_IMPORT void debfctwesmess(const int i, const TCollection_AsciiString& s = "");
extern void          debaddpwes(const int                           iFOR,
                                const TopAbs_State                  TB1,
                                const int                           iEG,
                                const TopAbs_Orientation            neworiE,
                                const TopOpeBRepBuild_PBuilder&     PB,
                                const TopOpeBRepBuild_PWireEdgeSet& PWES,
                                const TCollection_AsciiString&      str1,
                                const TCollection_AsciiString&      str2);
#endif

bool                 GLOBAL_faces2d           = false;
Standard_EXPORT bool GLOBAL_classifysplitedge = false;

#define M_IN(st) (st == TopAbs_IN)
#define M_OUT(st) (st == TopAbs_OUT)
#define M_FORWARD(st) (st == TopAbs_FORWARD)
#define M_REVERSED(st) (st == TopAbs_REVERSED)
#define M_INTERNAL(st) (st == TopAbs_INTERNAL)
#define M_EXTERNAL(st) (st == TopAbs_EXTERNAL)

Standard_IMPORT bool FUN_HDS_FACESINTERFER(const TopoDS_Shape&                             F1,
                                           const TopoDS_Shape&                             F2,
                                           const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

static TopAbs_State ClassifyEdgeToSolidByOnePoint(const TopoDS_Edge& E, const TopoDS_Shape& Ref);
static bool         FUN_computeLIFfaces2d(const TopOpeBRepBuild_Builder& BU,
                                          const TopoDS_Face&             F,
                                          const TopoDS_Edge&             E,
                                          TopOpeBRepDS_PDataStructure&   pDS2d);
static bool         FUN_computeLIFfaces2d(const TopOpeBRepBuild_Builder& BU,
                                          const TopoDS_Face&             F,
                                          TopOpeBRepDS_PDataStructure&   pDS2d);

bool TopOpeBRepBuild_FUN_aresamegeom(const TopoDS_Shape& S1, const TopoDS_Shape& S2)
{
  TopoDS_Shape SF1 = S1;
  SF1.Orientation(TopAbs_FORWARD);
  TopoDS_Shape SF2 = S2;
  SF2.Orientation(TopAbs_FORWARD);
  bool same = TopOpeBRepTool_ShapeTool::ShapesSameOriented(SF1, SF2);
  return same;
}

bool FUN_computeLIFfaces2d(const TopOpeBRepBuild_Builder& BU,
                           const TopoDS_Face&             F,
                           const TopoDS_Edge&             E,
                           TopOpeBRepDS_PDataStructure&   pDS2d)

{
  const TopOpeBRepDS_DataStructure&                               BDS = BU.DataStructure()->DS();
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI  = BDS.ShapeInterferences(E);
  int                                                             IE  = BDS.Shape(E);
  int                                                             IF  = BDS.Shape(F);
  int                                                             rkF = BDS.AncestorRank(F);
  bool                                                            hasspE = BU.IsSplit(E, TopAbs_ON);
  if (hasspE)
    hasspE = (BU.Splits(E, TopAbs_ON).Extent() > 0);
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> Ffound;

  NCollection_List<TopoDS_Shape>           Fsdm;
  NCollection_List<TopoDS_Shape>::Iterator itf(BDS.ShapeSameDomain(F));
  for (; itf.More(); itf.Next())
  {
    const TopoDS_Shape& f   = itf.Value();
    int                 rkf = BDS.AncestorRank(f);
    if (rkf == rkF)
      continue;
    Fsdm.Append(f);
  }

  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itI(LI); itI.More();
       itI.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = itI.Value();

    TopAbs_ShapeEnum  SB, SA;
    int               IB, IA;
    TopOpeBRepDS_Kind GT, ST;
    int               G, S;
    FDS_Idata(I, SB, IB, SA, IA, GT, G, ST, S);
    if (ST != TopOpeBRepDS_EDGE)
      return false;

    TopoDS_Face FTRA;
    int         ITRA = IB;
    if (SB == TopAbs_FACE)
      FTRA = TopoDS::Face(BDS.Shape(IB));
    else if (SB == TopAbs_EDGE)
    {
      bool ok = FUN_tool_findAncestor(Fsdm, TopoDS::Edge(BDS.Shape(S)), FTRA);
      ITRA    = BDS.Shape(FTRA);
      if (!ok)
        return false;
    }
    bool found = Ffound.Contains(FTRA);

    double             parE    = FDS_Parameter(I);
    const TopoDS_Edge& ES      = TopoDS::Edge(BDS.Shape(S));
    bool               hasspES = BU.IsSplit(ES, TopAbs_ON);
    if (hasspES)
      hasspE = (BU.Splits(ES, TopAbs_ON).Extent() > 0);

    bool sdm            = FUN_ds_sdm(BDS, E, ES);
    bool mkTonEsdm      = sdm && hasspE && !found;
    bool hasfeiF_E_FTRA = FUN_ds_hasFEI(pDS2d, F, IE, ITRA);
    mkTonEsdm           = mkTonEsdm && !hasfeiF_E_FTRA;
    if (mkTonEsdm)
    {
      Ffound.Add(FTRA);
      TopoDS_Edge             dummy;
      TopOpeBRepDS_Transition newT;
      bool ok = FUN_ds_mkTonFsdm(BU.DataStructure(), IF, ITRA, S, IE, parE, dummy, true, newT);

      if (ok)
      {
        newT.Index(ITRA);
        TopOpeBRepDS_Config                    C = TopOpeBRepDS_SAMEORIENTED;
        occ::handle<TopOpeBRepDS_Interference> newI =
          TopOpeBRepDS_InterferenceTool::MakeFaceEdgeInterference(newT, ITRA, IE, true, C);
        pDS2d->AddShapeInterference(F, newI);
      }
    }
    bool mkTonESsdm    = sdm && hasspES;
    bool hasfeiFRA_E_F = FUN_ds_hasFEI(pDS2d, FTRA, IE, IF);
    mkTonESsdm         = mkTonESsdm && !hasfeiFRA_E_F;
    if (mkTonESsdm)
    {
      TopoDS_Edge             dummy;
      TopOpeBRepDS_Transition newT;

      double parES;
      bool   ok = FUN_tool_parE(E, parE, ES, parES);
      if (!ok)
        continue;
      ok = FUN_ds_mkTonFsdm(BU.DataStructure(), ITRA, IF, IE, S, parES, dummy, true, newT);
      if (ok)
      {
        newT.Index(IF);
        TopOpeBRepDS_Config                    C = TopOpeBRepDS_SAMEORIENTED;
        occ::handle<TopOpeBRepDS_Interference> newI =
          TopOpeBRepDS_InterferenceTool::MakeFaceEdgeInterference(newT, IF, IE, false, C);
        pDS2d->AddShapeInterference(FTRA, newI);
      }

      ok = FUN_ds_mkTonFsdm(BU.DataStructure(), ITRA, IF, IE, IE, parE, dummy, true, newT);
      if (ok)
      {
        newT.Index(IF);
        TopOpeBRepDS_Config                    C = TopOpeBRepDS_SAMEORIENTED;
        occ::handle<TopOpeBRepDS_Interference> newI =
          TopOpeBRepDS_InterferenceTool::MakeFaceEdgeInterference(newT, IF, S, true, C);
        pDS2d->AddShapeInterference(FTRA, newI);
      }
    }

    bool mkTonES        = hasspES;
    bool hasfeiF_S_FTRA = FUN_ds_hasFEI(pDS2d, F, S, ITRA);
    mkTonES             = mkTonES && !hasfeiF_S_FTRA;
    if (mkTonES)
    {
      double parES;
      bool   ok = FUN_tool_parE(E, parE, ES, parES);
      if (!ok)
        continue;

      TopoDS_Edge             dummy;
      TopOpeBRepDS_Transition newT;
      ok = FUN_ds_mkTonFsdm(BU.DataStructure(), IF, ITRA, S, S, parES, dummy, true, newT);

      if (ok)
      {
        newT.Index(ITRA);
        TopOpeBRepDS_Config                    C = TopOpeBRepDS_SAMEORIENTED;
        occ::handle<TopOpeBRepDS_Interference> newI =
          TopOpeBRepDS_InterferenceTool::MakeFaceEdgeInterference(newT, ITRA, S, false, C);
        pDS2d->AddShapeInterference(F, newI);
      }
    }
  }

  return true;
}

bool FUN_computeLIFfaces2d(const TopOpeBRepBuild_Builder& BU,
                           const TopoDS_Face&             F,
                           TopOpeBRepDS_PDataStructure&   pDS2d)
{
  TopExp_Explorer ex(F, TopAbs_EDGE);
  for (; ex.More(); ex.Next())
  {
    const TopoDS_Edge& E  = TopoDS::Edge(ex.Current());
    bool               ok = FUN_computeLIFfaces2d(BU, F, E, pDS2d);
    if (!ok)
      return false;
  }
  return true;
}

Standard_EXPORT TopOpeBRepDS_PDataStructure GLOBAL_DS2d = nullptr;

void TopOpeBRepBuild_Builder::GMergeFaces(const NCollection_List<TopoDS_Shape>& LF1,
                                          const NCollection_List<TopoDS_Shape>& LF2,
                                          const TopOpeBRepBuild_GTopo&          G1)
{
  if (LF1.IsEmpty())
    return;
  if (GLOBAL_DS2d == nullptr)
    GLOBAL_DS2d = (TopOpeBRepDS_PDataStructure) new TopOpeBRepDS_DataStructure();
  GLOBAL_DS2d->Init();

  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);

  const TopoDS_Shape& F1 = LF1.First();
#ifdef OCCT_DEBUG
  int  iF;
  bool tSPS = GtraceSPS(F1, iF);
  if (tSPS)
  {
    std::cout << std::endl << "--- GMergeFaces " << std::endl;
    GdumpSAMDOM(LF1, (char*)"1 : ");
    GdumpSAMDOM(LF2, (char*)"2 : ");
    debmergef(iF);
  }
#endif

  NCollection_List<TopoDS_Shape>::Iterator itF1(LF1);
  for (; itF1.More(); itF1.Next())
    GLOBAL_DS2d->AddShape(itF1.Value(), 1);

  NCollection_List<TopoDS_Shape>::Iterator itF2(LF2);
  for (; itF2.More(); itF2.Next())
    GLOBAL_DS2d->AddShape(itF2.Value(), 2);

  itF1.Initialize(LF1);
  for (; itF1.More(); itF1.Next())
  {
    const TopoDS_Face& FF1 = TopoDS::Face(itF1.Value());
    FUN_computeLIFfaces2d((*this), TopoDS::Face(FF1), GLOBAL_DS2d);
  }

  itF2.Initialize(LF2);
  for (; itF2.More(); itF2.Next())
  {
    const TopoDS_Face& FF2 = TopoDS::Face(itF2.Value());
    FUN_computeLIFfaces2d((*this), TopoDS::Face(FF2), GLOBAL_DS2d);
  }

  {
    for (int ii = 1; ii <= GLOBAL_DS2d->NbShapes(); ii++)
    {
      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI =
        GLOBAL_DS2d->ChangeShapeInterferences(ii);
      FUN_reducedoublons(LI, (*GLOBAL_DS2d), ii);
    }
  }

  myFaceReference = TopoDS::Face(F1);
  TopOpeBRepBuild_WireEdgeSet WES(F1, this);

  GLOBAL_faces2d = true;
  int K1         = 1;
  GFillFacesWESK(LF1, LF2, G1, WES, K1);
  int K3 = 3;
  GFillFacesWESK(LF1, LF2, G1, WES, K3);
  GLOBAL_faces2d = false;

  TopoDS_Shape F1F = LF1.First();
  F1F.Orientation(TopAbs_FORWARD);
  bool                        ForceClass = true;
  TopOpeBRepBuild_FaceBuilder FABU;
  FABU.InitFaceBuilder(WES, F1F, ForceClass);

  NCollection_List<TopoDS_Shape> LFM;

#ifdef OCCT_DEBUG
  GFABUMAKEFACEPWES_DEB = (void*)&WES;
#endif

  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher> MWisOld;
  GFABUMakeFaces(F1F, FABU, LFM, MWisOld);

  NCollection_List<TopoDS_Shape> newLFM;
  RegularizeFaces(F1F, LFM, newLFM);
  LFM.Clear();
  LFM.Assign(newLFM);

  NCollection_List<TopoDS_Shape>::Iterator it1;
  for (it1.Initialize(LF1); it1.More(); it1.Next())
  {
    const TopoDS_Shape& F1x     = it1.Value();
    bool                tomerge = !IsMerged(F1x, TB1);
    if (tomerge)
    {
      ChangeMerged(F1x, TB1) = LFM;
    }
  }

  NCollection_List<TopoDS_Shape>::Iterator it2;
  for (it2.Initialize(LF2); it2.More(); it2.Next())
  {
    const TopoDS_Shape& F2      = it2.Value();
    bool                tomerge = !IsMerged(F2, TB2);
    if (tomerge)
      ChangeMerged(F2, TB2) = LFM;
  }
}

void TopOpeBRepBuild_Builder::GFillFacesWES(const NCollection_List<TopoDS_Shape>&,
                                            const NCollection_List<TopoDS_Shape>&,
                                            const TopOpeBRepBuild_GTopo&,
                                            TopOpeBRepBuild_WireEdgeSet&)
{
}

static bool FUN_validF1edge(const TopoDS_Shape& F)
{
  int                                                           nE = 0;
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mEt;
  TopExp_Explorer                                               exE(F, TopAbs_EDGE);

  for (; exE.More(); exE.Next())
  {
    const TopoDS_Shape& e = exE.Current();
    if (mEt.Contains(e))
      continue;
    mEt.Add(e);
    nE++;
    if (nE > 2)
      break;
  }
  if (nE > 1)
    return true;
  if (nE == 1)
  {
    exE.Init(F, TopAbs_EDGE);
    const TopoDS_Edge& e = TopoDS::Edge(exE.Current());
    TopoDS_Vertex      dummy;
    bool               closed = TopOpeBRepTool_TOOL::ClosedE(e, dummy);
    return closed;
  }
  return false;
}

void TopOpeBRepBuild_Builder::GFillFacesWESMakeFaces(const NCollection_List<TopoDS_Shape>& LLF1,
                                                     const NCollection_List<TopoDS_Shape>& LF2,
                                                     const NCollection_List<TopoDS_Shape>&,
                                                     const TopOpeBRepBuild_GTopo& GM)
{
  TopAbs_State TB1, TB2;
  GM.StatesON(TB1, TB2);
  if (LLF1.IsEmpty())
    return;

  NCollection_List<TopoDS_Shape>           LF1;
  NCollection_List<TopoDS_Shape>::Iterator itf(LLF1);
  const TopOpeBRepDS_DataStructure&        BDS  = myDataStructure->DS();
  int                                      iref = 0;
  for (; itf.More(); itf.Next())
  {
    const TopoDS_Shape& fcur = itf.Value();
    int                 icur = BDS.Shape(fcur);
    iref                     = BDS.SameDomainRef(fcur);
    if (icur == iref)
      LF1.Prepend(fcur);
    else
      LF1.Append(fcur);
  }

  const TopoDS_Shape& FF  = LF1.First().Oriented(TopAbs_FORWARD);
  int                 iFF = BDS.Shape(FF);

  TopOpeBRepBuild_WireEdgeSet WES(FF, this);

#ifdef OCCT_DEBUG
  int  iF;
  bool tSPS = GtraceSPS(FF, iF);
  if (tSPS)
    GdumpSHASTA(iF, TB1, WES, "\n--- GFillFacesWESMakeFaces");
  if (tSPS)
    debfillf(iF);
  if (tSPS)
    debffwesmf(iF);
#endif

  int n1         = 0;
  GLOBAL_faces2d = true;
  int K1         = 1;
  GFillFacesWESK(LF1, LF2, GM, WES, K1);
  GLOBAL_faces2d = false;
  n1             = WES.StartElements().Extent();

  int K2 = 2;
  GFillFacesWESK(LF1, LF2, GM, WES, K2);
  n1 = WES.StartElements().Extent();

  int K3 = 3;
  GFillFacesWESK(LF1, LF2, GM, WES, K3);
  n1 = WES.StartElements().Extent();

  int n2 = WES.StartElements().Extent();
  myEdgeAvoid.Clear();
  GCopyList(WES.StartElements(), (n1 + 1), n2, myEdgeAvoid);
  NCollection_List<TopoDS_Shape> LOF;
  GWESMakeFaces(FF, WES, LOF);

  NCollection_List<TopoDS_Shape>::Iterator itF(LOF);
  while (itF.More())
  {
    const TopoDS_Shape& F     = itF.Value();
    bool                valid = ::FUN_validF1edge(F);
    if (!valid)
      LOF.Remove(itF);
    else
      itF.Next();
  }

  NCollection_List<TopoDS_Shape> LOFS;
  GKeepShapes(FF, myEmptyShapeList, TB1, LOF, LOFS);

  TopAbs_Orientation odsFF = myDataStructure->Shape(iFF).Orientation();
  for (NCollection_List<TopoDS_Shape>::Iterator itt(LOFS); itt.More(); itt.Next())
    itt.ChangeValue().Orientation(odsFF);

  NCollection_List<TopoDS_Shape>::Iterator it1;
  for (it1.Initialize(LF1); it1.More(); it1.Next())
  {
    const TopoDS_Shape& S = it1.Value();
#ifdef OCCT_DEBUG
    int iS;
    GtraceSPS(S, iS);
#endif
    MarkSplit(S, TB1);
    NCollection_List<TopoDS_Shape>& LS1 = ChangeSplit(S, TB1);
    GCopyList(LOFS, LS1);
  }

  NCollection_List<TopoDS_Shape>::Iterator it2;
  for (it2.Initialize(LF2); it2.More(); it2.Next())
  {
    const TopoDS_Shape& S = it2.Value();
#ifdef OCCT_DEBUG
    int iS;
    GtraceSPS(S, iS);
#endif
    MarkSplit(S, TB2);
    NCollection_List<TopoDS_Shape>& LS2 = ChangeSplit(S, TB2);
    GCopyList(LOFS, LS2);
  }
}

void TopOpeBRepBuild_Builder::GFillFaceWES(const TopoDS_Shape&                   FOR1,
                                           const NCollection_List<TopoDS_Shape>& LFclass,
                                           const TopOpeBRepBuild_GTopo&          G1,
                                           TopOpeBRepBuild_WireEdgeSet&          WES)
{
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);
  bool RevOri1 = G1.IsToReverse1();

#ifdef OCCT_DEBUG
  int  iF;
  bool tSPS = GtraceSPS(FOR1, iF);
  if (tSPS)
    GdumpSHASTA(iF, TB1, WES, "--- GFillFaceWES", "START");
  if (tSPS)
    debfillf(iF);
#endif

  bool opeCut   = Opec12() || Opec21();
  bool ComOfCut = opeCut && (TB1 == TB2) && (TB1 == TopAbs_IN);
  bool hsdm     = myDataStructure->HasSameDomain(FOR1);
  if (hsdm && ComOfCut)
    return;

  TopoDS_Shape FF = FOR1;
  FF.Orientation(TopAbs_FORWARD);
  myFaceToFill = TopoDS::Face(FF);

  TopOpeBRepTool_ShapeExplorer exWire(FF, TopAbs_WIRE);
  for (; exWire.More(); exWire.Next())
  {
    TopoDS_Shape W        = exWire.Current();
    bool         hasshape = myDataStructure->HasShape(W);

    if (!hasshape)
    {

      TopAbs_State pos;
      bool         keep = GKeepShape1(W, LFclass, TB1, pos);
      if (keep)
      {
        TopAbs_Orientation oriW    = W.Orientation();
        TopAbs_Orientation neworiW = Orient(oriW, RevOri1);
        W.Orientation(neworiW);
        WES.AddShape(W);
      }
      else if (myProcessON && pos == TopAbs_ON)
        myONElemMap.Add(W);
    }
    else
    {
      GFillWireWES(W, LFclass, G1, WES);
    }
  }

#ifdef OCCT_DEBUG
  if (tSPS)
    GdumpSHASTA(iF, TB1, WES, "--- GFillFaceWES", "END");
#endif

  return;
}

void TopOpeBRepBuild_Builder::GFillWireWES(const TopoDS_Shape&                   W,
                                           const NCollection_List<TopoDS_Shape>& LSclass,
                                           const TopOpeBRepBuild_GTopo&          G1,
                                           TopOpeBRepBuild_WireEdgeSet&          WES)
{
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);

#ifdef OCCT_DEBUG
  int  iW;
  bool tSPS = GtraceSPS(W, iW);
  if (tSPS)
  {
    std::cout << std::endl;
    DEBSHASET(s, "--- GFillWireWES ", WES, " ");
    GdumpSHA(W, (void*)s.ToCString());
    std::cout << std::endl;
    int                          nbe = 0;
    TopOpeBRepTool_ShapeExplorer exE(W, TopAbs_EDGE);
    for (; exE.More(); exE.Next())
      nbe++;
    std::cout << "--- GFillWireWES on W " << iW << " with " << nbe << " edges " << std::endl;
    debfillw(iW);
  }
  GLOBAL_iexE = 0;
#endif

  TopOpeBRepTool_ShapeExplorer exEdge(W, TopAbs_EDGE);
  for (; exEdge.More(); exEdge.Next())
  {
    const TopoDS_Shape& EOR = exEdge.Current();

#ifdef OCCT_DEBUG
    GLOBAL_iexE++;
    if (tSPS)
    {
    }
#endif

    GFillEdgeWES(EOR, LSclass, G1, WES);
  }
}

void TopOpeBRepBuild_Builder::GFillEdgeWES(const TopoDS_Shape&                   EOR,
                                           const NCollection_List<TopoDS_Shape>& LSclass,
                                           const TopOpeBRepBuild_GTopo&          G1,
                                           TopOpeBRepBuild_WireEdgeSet&          WES)
{
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);

#ifdef OCCT_DEBUG
  int  iE;
  bool tSPS = GtraceSPS(EOR, iE);
  if (tSPS)
    std::cout << std::endl;
#endif

#ifdef OCCT_DEBUG
  bool tosplit =
#endif
    GToSplit(EOR, TB1);
#ifdef OCCT_DEBUG
  bool tomerge =
#endif
    GToMerge(EOR);

#ifdef OCCT_DEBUG
  if (tSPS)
    GdumpSHASTA(iE, TB1, WES, "--- GFillEdgeWES ");
  if (tSPS)
    std::cout << " tosplit " << tosplit << " tomerge " << tomerge << std::endl;
  if (tSPS)
    debfille(iE);
#endif

  const TopOpeBRepBuild_GTopo& GME = G1;
  GMergeEdgeWES(EOR, GME, WES);

  TopOpeBRepBuild_GTopo GSE = G1;
  GSE.ChangeConfig(TopOpeBRepDS_UNSHGEOMETRY, TopOpeBRepDS_UNSHGEOMETRY);
  GSplitEdgeWES(EOR, LSclass, GSE, WES);
}

static void FUN_samgeomori(const TopOpeBRepDS_DataStructure& BDS,
                           const int                         iref,
                           const int                         ifil,
                           bool&                             samgeomori)
{
  TopOpeBRepDS_Config cfill = BDS.SameDomainOri(ifil);
  TopAbs_Orientation  oref = BDS.Shape(iref).Orientation(), ofil = BDS.Shape(ifil).Orientation();
  samgeomori = (cfill == TopOpeBRepDS_SAMEORIENTED);
  if (oref == TopAbs::Complement(ofil))
    samgeomori = !samgeomori;
}

#define UNKNOWN (0)
#define ONSAMESHA (1)
#define CLOSESAME (11)
#define ONOPPOSHA (2)
#define CLOSEOPPO (22)
#define FORREVOPPO (222)

void TopOpeBRepBuild_Builder::GSplitEdgeWES(const TopoDS_Shape&                   EOR,
                                            const NCollection_List<TopoDS_Shape>& LSclass,
                                            const TopOpeBRepBuild_GTopo&          G1,
                                            TopOpeBRepBuild_WireEdgeSet&          WES)
{
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);
  bool                              RevOri1 = G1.IsToReverse1();
  TopAbs_Orientation                oriE    = EOR.Orientation();
  TopAbs_Orientation                neworiE = Orient(oriE, RevOri1);
  const TopOpeBRepDS_DataStructure& BDS     = myDataStructure->DS();

  TopAbs_Orientation oEinF;
  int                Oinref = 0;
  bool               hsdm   = myDataStructure->HasSameDomain(myFaceToFill);
  bool               hsdmE  = myDataStructure->HasSameDomain(EOR);
  int                ifil   = myDataStructure->Shape(myFaceToFill);
  int                iref   = myDataStructure->Shape(myFaceReference);
  if (hsdm)
  {
    Oinref = FUN_ds_oriEinF(BDS, TopoDS::Edge(EOR), myFaceReference, oEinF);

    TopAbs_Orientation oEinfill;
    int                Oinfill = FUN_ds_oriEinF(BDS, TopoDS::Edge(EOR), myFaceToFill, oEinfill);
    if (Oinref == Oinfill)
    {

      bool reverse = false;
      if (iref != ifil)
      {

        TopAbs_Orientation oref = myFaceReference.Orientation();
        bool               samegeomori;
        FUN_samgeomori(BDS, iref, ifil, samegeomori);
        reverse = (!samegeomori);
        if (oref == TopAbs_REVERSED)
          reverse = !reverse;
      }

      TopAbs_Orientation oEinfillTOref = reverse ? TopAbs::Complement(oEinfill) : oEinfill;
      bool               same          = (oEinF == oEinfillTOref);
      if (!same && (oEinF != TopAbs_INTERNAL) && (oEinF != TopAbs_EXTERNAL))
        oEinF = oEinfillTOref;
    }
  }
  else
    Oinref = FUN_ds_oriEinF(BDS, TopoDS::Edge(EOR), myFaceToFill, oEinF);
  bool newO = (Oinref == ONSAMESHA) || (Oinref == ONOPPOSHA);

  bool isfafa = (myIsKPart == 3);
  if (isfafa)
    newO = false;

#ifdef OCCT_DEBUG
  int  iEOR;
  bool tSPS = GtraceSPS(EOR, iEOR);
  int  iWESF;
  GtraceSPS(WES.Face(), iWESF);
  if (tSPS)
    GdumpSHASTA(iEOR, TB1, WES, "\n--- GSplitEdgeWES", "START");
  if (tSPS)
    std::cout << " RevOri1 : " << RevOri1 << std::endl;
  if (tSPS)
    debsplite(iEOR);
#endif

  bool tosplit = GToSplit(EOR, TB1);
  if (tosplit)
  {
    GSplitEdge(EOR, G1, LSclass);

    if (myIsKPart == 4)
    {

      TopAbs_State                   aState;
      int                            aRank1;
      NCollection_List<TopoDS_Shape> anAuxList;

      aRank1                     = ShapeRank(EOR);
      const TopoDS_Shape& aSolid = (aRank1 == 1) ? myShape2 : myShape1;

      NCollection_List<TopoDS_Shape>&          aSplitList = ChangeSplit(EOR, TB1);
      NCollection_List<TopoDS_Shape>::Iterator anIt(aSplitList);
      for (; anIt.More(); anIt.Next())
      {
        const TopoDS_Edge& aSplitEdge = TopoDS::Edge(anIt.Value());
        aState                        = ClassifyEdgeToSolidByOnePoint(aSplitEdge, aSolid);
        if (aState == TB1)
        {
          anAuxList.Append(aSplitEdge);
        }
      }

      aSplitList.Clear();

      anIt.Initialize(anAuxList);
      for (; anIt.More(); anIt.Next())
      {
        const TopoDS_Shape& aShape = anIt.Value();
        aSplitList.Append(aShape);
      }
    }
  }

  bool opeFus = Opefus();
  if (opeFus)
    if (TB1 == TopAbs_IN)
      return;

  bool issplit = IsSplit(EOR, TB1);
  if (issplit)
  {
    const NCollection_List<TopoDS_Shape>& LSE = Splits(EOR, TB1);

#ifdef OCCT_DEBUG
    if (tSPS)
    {
      GdumpSHASTA(iEOR, TB1, WES, "--- GSplitEdgeWES", "WES+ Split");
      std::cout << " ";
      TopAbs::Print(TB1, std::cout) << " : " << LSE.Extent() << " edge(s) ";
      TopAbs::Print(neworiE, std::cout);
      std::cout << std::endl;
    }
#endif

    for (NCollection_List<TopoDS_Shape>::Iterator it(LSE); it.More(); it.Next())
    {
      TopoDS_Edge newE = TopoDS::Edge(it.Value());
      if (newO)
      {

        newE.Orientation(oEinF);
        bool dgE = BRep_Tool::Degenerated(TopoDS::Edge(EOR));
        if (!dgE && hsdmE)
        {
          double f, l;
          FUN_tool_bounds(newE, f, l);
          double x   = 0.45678;
          double par = (1 - x) * f + x * l;
          bool   so  = true;
          bool   ok  = FUN_tool_curvesSO(newE, par, TopoDS::Edge(EOR), so);
          if (!ok)
          {
#ifdef OCCT_DEBUG
            std::cout << "GSplitEdgeWES: cannot orient SDM split of an edge" << std::endl;
#endif
          }
          if (!so)
          {
            newE.Reverse();
          }
        }
      }
      else
        newE.Orientation(neworiE);

#ifdef OCCT_DEBUG
      if (tSPS)
        debaddpwes(iWESF,
                   TB1,
                   iEOR,
                   neworiE,
                   (TopOpeBRepBuild_Builder* const)this,
                   &WES,
                   "GSplitEdgeWES ",
                   "WES+ Eisspl ");
#endif

      WES.AddStartElement(newE);
    }
  }

  else
  {

    bool se    = BDS.IsSectionEdge(TopoDS::Edge(EOR));
    bool hs    = myDataStructure->HasShape(EOR);
    bool hg    = myDataStructure->HasGeometry(EOR);
    bool add   = false;
    bool addON = false;

    bool isstart = false;
    isstart      = hs;

    if (se)
    {
      bool             ftg    = !LSclass.IsEmpty();
      TopAbs_ShapeEnum tclass = LSclass.First().ShapeType();
      ftg                     = ftg && (tclass == TopAbs_FACE);
      if (!ftg)
      {
        TopAbs_State pos;
        bool         keepse = GKeepShape1(EOR, LSclass, TB1, pos);
        if (keepse)
          add = true;
        else if (myProcessON && pos == TopAbs_ON)
          addON = true;
      }

#ifdef OCCT_DEBUG
      std::cout << "o-o GridFF ffil F" << ifil << " se E" << iEOR << " / " << iWESF << " ";
      TopAbs::Print(TB1, std::cout);
      std::cout.flush();
      if (!ftg)
      {
        std::cout << " : !ftg --> ";
        GKeepShape(EOR, LSclass, TB1);
        std::cout.flush();
      }
      else
      {
        std::cout << " : ftg --> non gardee" << std::endl;
        std::cout.flush();
      }
#endif
    }
    else
    {
      add           = true;
      bool testkeep = true;
      testkeep      = hs && (!hg);
      if (testkeep)
      {
#ifdef OCCT_DEBUG
        if (tSPS)
        {
          std::cout << "--- GSplitEdgeWES ";
        }
#endif
        TopAbs_State pos;
        bool         keep = GKeepShape1(EOR, LSclass, TB1, pos);
        if (!keep)
        {
          bool testON = (!LSclass.IsEmpty());
          if (testON)
            testON = (LSclass.First().ShapeType() == TopAbs_SOLID);
          if (testON)
            keep = (pos == TopAbs_ON);
          addON = myProcessON && keep;
        }
        add = keep;
      }
    }

    if (add)
    {
      TopoDS_Shape newE = EOR;

      if (newO)
        newE.Orientation(oEinF);

      else if (Oinref == FORREVOPPO)
        newE.Orientation(TopAbs_INTERNAL);

      else
        newE.Orientation(neworiE);
#ifdef OCCT_DEBUG
      if (tSPS)
      {
        DEBSHASET(ss, "--- GSplitEdgeWES ", WES, " WES+ edge ");
        GdumpSHA(newE, (void*)ss.ToCString());
        std::cout << " ";
        TopAbs::Print(TB1, std::cout) << " : 1 edge ";
        TopAbs::Print(neworiE, std::cout);
        std::cout << std::endl;
      }
#endif

      if (isstart)
      {
#ifdef OCCT_DEBUG
        if (tSPS)
          debaddpwes(iWESF,
                     TB1,
                     iEOR,
                     neworiE,
                     (TopOpeBRepBuild_Builder* const)this,
                     &WES,
                     "GSplitEdgeWES ",
                     "WES+ Enospl ");
#endif
        WES.AddStartElement(newE);
      }
      else
      {
        WES.AddElement(newE);
      }
    }

    if (addON)
    {
      TopoDS_Shape newE = EOR;
      newE.Orientation(neworiE);
      myONElemMap.Add(newE);
    }
  }

  if (myProcessON && IsSplit(EOR, TopAbs_ON))
  {
    const NCollection_List<TopoDS_Shape>&    LSE = Splits(EOR, TopAbs_ON);
    NCollection_List<TopoDS_Shape>::Iterator it(LSE);
    for (; it.More(); it.Next())
    {
      TopoDS_Edge newE = TopoDS::Edge(it.Value());
      if (newO)
      {
        newE.Orientation(oEinF);
        bool dgE = BRep_Tool::Degenerated(TopoDS::Edge(EOR));
        if (!dgE && hsdmE)
        {
          double f, l;
          FUN_tool_bounds(newE, f, l);
          double x   = 0.45678;
          double par = (1 - x) * f + x * l;
          bool   so  = true;
          bool   ok  = FUN_tool_curvesSO(newE, par, TopoDS::Edge(EOR), so);
          if (!ok)
          {
#ifdef OCCT_DEBUG
            std::cout << "GSplitEdgeWES: cannot orient SDM split of an edge" << std::endl;
#endif
          }
          if (!so)
            newE.Reverse();
        }
      }
      else
        newE.Orientation(neworiE);
      myONElemMap.Add(newE);
    }
  }

#ifdef OCCT_DEBUG
  if (tSPS)
    GdumpSHASTA(iEOR, TB1, WES, "--- GSplitEdgeWES", "END");
#endif

  return;
}

Standard_IMPORT bool                         FUN_ismotheropedef();
Standard_IMPORT const TopOpeBRepBuild_GTopo& FUN_motherope();
Standard_EXPORT bool                         GLOBAL_IEtoMERGE = false;

#ifdef OCCT_DEBUG
void debmergee(const int) {}
#endif

void TopOpeBRepBuild_Builder::GMergeEdgeWES(const TopoDS_Shape&          EOR,
                                            const TopOpeBRepBuild_GTopo& G1,
                                            TopOpeBRepBuild_WireEdgeSet& WES)
{
#ifdef OCCT_DEBUG
  int iWESF;
  GtraceSPS(WES.Face(), iWESF);
  int  iEOR;
  bool tSPS = GtraceSPS(EOR, iEOR);
  if (tSPS)
  {
    debmergee(iEOR);
    DEBSHASET(s, "\n--- GMergeEdgeWES ", WES, " START ");
    GdumpSHAORIGEO(EOR, (void*)s.ToCString());
    std::cout << std::endl;
  }
#endif

  bool closing = BRep_Tool::IsClosed(TopoDS::Edge(EOR), myFaceToFill);
  if (closing)
    return;

  if (Opefus())
    return;

  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);
  bool               RevOri1 = G1.IsToReverse1();
  TopAbs_Orientation oriE    = EOR.Orientation();
  TopAbs_Orientation neworiE = Orient(oriE, RevOri1);

  bool hassame = myDataStructure->HasSameDomain(EOR);
  if (!hassame)
    return;

  bool Eisref = false;
  if (hassame)
  {
    int                 iEref = myDataStructure->SameDomainReference(EOR);
    const TopoDS_Shape& Eref  = myDataStructure->Shape(iEref);
    Eisref                    = EOR.IsSame(Eref);
  }

  TopAbs_State TBEOR = (Eisref) ? TB1 : TB2;
  if (TBEOR == TopAbs_OUT)
    return;

  bool ismerged = IsMerged(EOR, TBEOR);
  if (ismerged)
  {
    if (!Eisref)
      return;

    const NCollection_List<TopoDS_Shape>&    ME = Merged(EOR, TBEOR);
    NCollection_List<TopoDS_Shape>::Iterator it(ME);
    for (; it.More(); it.Next())
    {
      TopoDS_Shape newE = it.Value();
      newE.Orientation(neworiE);

#ifdef OCCT_DEBUG
      if (tSPS)
        debaddpwes(iWESF,
                   TB1,
                   iEOR,
                   neworiE,
                   (TopOpeBRepBuild_Builder* const)this,
                   &WES,
                   "GMergeEdgeWES ",
                   "WES+ Emerge ");
#endif

      WES.AddStartElement(newE);
    }
    return;
  }

  ChangeMerged(EOR, TBEOR) = myEmptyShapeList;
  TopAbs_State stspEOR;

  stspEOR = TBEOR;

  bool issplit = IsSplit(EOR, stspEOR);
  if (!issplit)
    return;

  ChangeMerged(EOR, TBEOR) = Splits(EOR, stspEOR);

  const NCollection_List<TopoDS_Shape>& ME = Merged(EOR, TBEOR);
#ifdef OCCT_DEBUG
  if (tSPS)
  {
    DEBSHASET(s, "GMergeEdgeWES(1) ", WES, " WES+ Merged ");
    GdumpSHA(EOR, (void*)s.ToCString());
    std::cout << " ";
    TopAbs::Print(TBEOR, std::cout);
    std::cout << " : " << ME.Extent() << " edge" << std::endl;
  }
#endif
  for (NCollection_List<TopoDS_Shape>::Iterator it(ME); it.More(); it.Next())
  {
    TopoDS_Shape newE = it.Value();
    newE.Orientation(neworiE);
    WES.AddStartElement(newE);
  }

#ifdef OCCT_DEBUG
  if (tSPS)
  {
    DEBSHASET(sss, "GMergeEdgeWES ", WES, " END ");
    GdumpSHA(EOR, (void*)sss.ToCString());
    std::cout << std::endl;
  }
#endif
}

void TopOpeBRepBuild_Builder::GSplitEdge(const TopoDS_Shape&                   EOR,
                                         const TopOpeBRepBuild_GTopo&          G1,
                                         const NCollection_List<TopoDS_Shape>& LSclass)
{
  TopAbs_ShapeEnum t1, t2;
  G1.Type(t1, t2);
  TopAbs_State TB1, TB2;
  G1.StatesON(TB1, TB2);

  TopoDS_Shape EF = EOR;
  EF.Orientation(TopAbs_FORWARD);

#ifdef OCCT_DEBUG
  int  iE;
  bool tSPS = GtraceSPS(EOR, iE);
  if (tSPS)
    GdumpSHASTA(EOR, TB1, "--- GSplitEdge ", "\n");
  if (tSPS)
    GdumpEDG(EF);
  if (tSPS)
    debsplite(iE);
#endif

  const TopoDS_Edge& EEF       = TopoDS::Edge(EF);
  bool               isse      = myDataStructure->DS().IsSectionEdge(EEF);
  bool               issplitON = IsSplit(EEF, TopAbs_ON);
  bool               takeON    = (TB1 == TopAbs_IN) && (isse) && (issplitON);
  takeON                       = false;
#ifdef OCCT_DEBUG
  if (tSPS)
    std::cout << "---- takeON mis a 0" << std::endl;
#endif

  if (takeON)
  {

#ifdef OCCT_DEBUG
    if (tSPS)
      GdumpSHASTA(EOR, TB1, "--- GSplitEdge takeON ", "\n");
#endif

    MarkSplit(EF, TB1);
    NCollection_List<TopoDS_Shape>& SSEL = ChangeSplit(EF, TB1);
    SSEL.Clear();
    SSEL = Splits(EEF, TopAbs_ON);
    return;
  }

  NCollection_List<TopoDS_Shape> LOE;

  TopOpeBRepBuild_PaveSet PVS(EF);

  myEdgeReference = TopoDS::Edge(EF);
  GFillPointTopologyPVS(EF, G1, PVS);

  MarkSplit(EF, TB1);

  GPVSMakeEdges(EF, PVS, LOE);

  bool novertex = LOE.IsEmpty();
  if (novertex)
    return;

  NCollection_List<TopoDS_Shape>& SEL = ChangeSplit(EF, TB1);
  SEL.Clear();

  TopOpeBRepDS_Config c1 = G1.Config1(), c2 = G1.Config2();
  bool                UUFACE = (c1 == TopOpeBRepDS_UNSHGEOMETRY && c2 == TopOpeBRepDS_UNSHGEOMETRY);

  bool ONSOLID = false;
  if (!LSclass.IsEmpty())
  {
    TopAbs_ShapeEnum t = LSclass.First().ShapeType();
    ONSOLID            = (t == TopAbs_SOLID);
  }

  bool toclass = UUFACE;
  toclass      = !ONSOLID;

  NCollection_List<TopoDS_Shape>        loos;
  const NCollection_List<TopoDS_Shape>* pls;
  if (GLOBAL_classifysplitedge)
  {
    int          r   = GShapeRank(EOR);
    TopoDS_Shape oos = myShape1;
    if (r == 1)
      oos = myShape2;
    if (!oos.IsNull())
      loos.Append(oos);
    pls = &loos;
  }
  else if (toclass)
  {
    pls = &LSclass;
  }
  else
  {
    pls = &myEmptyShapeList;
  }

  NCollection_List<TopoDS_Shape>           aLON;
  NCollection_List<TopoDS_Shape>::Iterator it(LOE);
  for (; it.More(); it.Next())
  {
    const TopoDS_Shape& aE = it.Value();
    TopAbs_State        pos;
    if (GKeepShape1(aE, *pls, TB1, pos))
      SEL.Append(aE);
    else if (myProcessON && pos == TopAbs_ON)
      aLON.Append(aE);
  }

  if (!aLON.IsEmpty())
  {
    MarkSplit(EF, TopAbs_ON);
    NCollection_List<TopoDS_Shape>& aSLON = ChangeSplit(EF, TopAbs_ON);
    aSLON.Clear();
    aSLON.Append(aLON);
  }
}

#include <BRepClass3d_SolidClassifier.hpp>

TopAbs_State ClassifyEdgeToSolidByOnePoint(const TopoDS_Edge& E, const TopoDS_Shape& Ref)
{
  const double PAR_T = 0.43213918;
  double       f2 = 0., l2 = 0., par = 0.;

  occ::handle<Geom_Curve> C3D = BRep_Tool::Curve(E, f2, l2);
  gp_Pnt                  aP3d;

  if (C3D.IsNull())
  {

    const TopoDS_Vertex& fv = TopExp::FirstVertex(E);
    if (fv.IsNull())
      return TopAbs_UNKNOWN;
    aP3d = BRep_Tool::Pnt(fv);
  }
  else
  {
    par = f2 * PAR_T + (1 - PAR_T) * l2;
    C3D->D0(par, aP3d);
  }

  BRepClass3d_SolidClassifier SC(Ref);
  SC.Perform(aP3d, 1e-7);

  return SC.State();
}
