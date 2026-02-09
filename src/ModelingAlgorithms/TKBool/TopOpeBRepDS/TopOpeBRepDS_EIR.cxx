

#include <BRep_Tool.hpp>
#include <TopExp.hpp>
#include <TopoDS.hpp>
#include <TopOpeBRepDS_connex.hpp>
#include <TopOpeBRepDS_CurvePointInterference.hpp>
#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepDS_Dumper.hpp>
#include <TopOpeBRepDS_Edge3dInterferenceTool.hpp>
#include <TopOpeBRepDS_EdgeInterferenceTool.hpp>
#include <TopOpeBRepDS_EdgeVertexInterference.hpp>
#include <TopOpeBRepDS_EIR.hpp>
#include <TopOpeBRepDS_HDataStructure.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>
#include <TopOpeBRepDS_repvg.hpp>
#include <TopOpeBRepDS_TKI.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_TOOL.hpp>

#define M_FORWARD(O) (O == TopAbs_FORWARD)
#define M_REVERSED(O) (O == TopAbs_REVERSED)
#define M_INTERNAL(O) (O == TopAbs_INTERNAL)
#define M_EXTERNAL(O) (O == TopAbs_EXTERNAL)

static bool CheckInterferenceIsValid(const occ::handle<TopOpeBRepDS_Interference>& I,
                                     const TopoDS_Edge&                            theEdge,
                                     const TopoDS_Edge&                            theSupportEdge,
                                     const TopoDS_Vertex&                          theVertex);

static void FDS_reduceONFACEinterferences(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
  const TopOpeBRepDS_DataStructure&,
  const int)

{

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;

  bool hasONFACE = false;
  for (it1.Initialize(LI); it1.More(); it1.Next())
  {
    occ::handle<TopOpeBRepDS_Interference>& I1 = it1.ChangeValue();
    TopOpeBRepDS_Kind                       GT1, ST1;
    int                                     G1, S1;
    FDS_data(I1, GT1, G1, ST1, S1);
    if (GT1 == TopOpeBRepDS_POINT)
    {
      hasONFACE = FUN_hasStateShape(I1->Transition(), TopAbs_ON, TopAbs_FACE);
      if (hasONFACE)
        break;
    }
  }

  if (hasONFACE)
  {

    it1.Initialize(LI);
    while (it1.More())
    {
      occ::handle<TopOpeBRepDS_Interference>& I1 = it1.ChangeValue();
      TopOpeBRepDS_Kind                       GT1, ST1;
      int                                     G1, S1;
      FDS_data(I1, GT1, G1, ST1, S1);
      if (GT1 == TopOpeBRepDS_POINT)
      {
        hasONFACE = FUN_hasStateShape(I1->Transition(), TopAbs_ON, TopAbs_FACE);
        if (!hasONFACE)
        {
          LI.Remove(it1);
        }
        else
          it1.Next();
      }
      else
        it1.Next();
    }
  }
}

static void FUN_ReducerEdge3d(const int                                                 SIX,
                              TopOpeBRepDS_DataStructure&                               BDS,
                              NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                              NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& reducedLI)

{
  reducedLI.Clear();

  int n3d = LI.Extent();
  if (n3d <= 1)
    return;
  const TopoDS_Edge& E     = TopoDS::Edge(BDS.Shape(SIX));
  int                rankE = BDS.AncestorRank(E);
  TopoDS_Shape       OOv;
  int                Gsta = 0;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;
  it1.Initialize(LI);

  int nLI = LI.Extent();
  if (nLI >= 1)
  {
    while (it1.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I1 = it1.Value();
      TopOpeBRepDS_Kind                             GT1, ST1;
      int                                           G1, S1;
      FDS_data(I1, GT1, G1, ST1, S1);
      TopAbs_ShapeEnum SB1, SA1;
      int              IB1, IA1;
      FDS_Tdata(I1, SB1, IB1, SA1, IA1);
      bool torem = false;
      if (ST1 == TopOpeBRepDS_EDGE)
      {
        const TopoDS_Edge& EE = TopoDS::Edge(BDS.Shape(S1));
        const TopoDS_Face& FF = TopoDS::Face(BDS.Shape(IB1));
        TopAbs_Orientation o;
        bool               ok = FUN_tool_orientEinFFORWARD(EE, FF, o);
        if (ok && (o == TopAbs_EXTERNAL))
          torem = true;
      }
      if (torem)
        LI.Remove(it1);
      else
        it1.Next();
    }
    nLI = LI.Extent();
    if (nLI <= 1)
      return;
  }

  it1.Initialize(LI);
  while (it1.More())
  {

    bool                                          isComplex = false;
    TopOpeBRepDS_Edge3dInterferenceTool           EFITool;
    const occ::handle<TopOpeBRepDS_Interference>& I1 = it1.Value();
    TopOpeBRepDS_Kind                             GT1, ST1;
    int                                           G1, S1;
    FDS_data(I1, GT1, G1, ST1, S1);
    TopAbs_ShapeEnum SB1, SA1;
    int              IB1, IA1;
    FDS_Tdata(I1, SB1, IB1, SA1, IA1);

    TopoDS_Vertex aVertex;

    if ((GT1 == TopOpeBRepDS_VERTEX) && G1 != 0)
    {
      aVertex = TopoDS::Vertex(BDS.Shape(G1));
    }

    if (!CheckInterferenceIsValid(I1, E, TopoDS::Edge(BDS.Shape(S1)), aVertex))
    {
      LI.Remove(it1);
      continue;
    }

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
    if (it2.More())
      it2.Next();
    else
      return;

    while (it2.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I2 = it2.Value();
      TopOpeBRepDS_Kind                             GT2, ST2;
      int                                           G2, S2;
      FDS_data(I2, GT2, G2, ST2, S2);
      TopAbs_ShapeEnum SB2, SA2;
      int              IB2, IA2;
      FDS_Tdata(I2, SB2, IB2, SA2, IA2);

      aVertex.Nullify();

      if ((GT2 == TopOpeBRepDS_VERTEX) && G2 != 0)
      {
        aVertex = TopoDS::Vertex(BDS.Shape(G2));
      }

      if (!CheckInterferenceIsValid(I2, E, TopoDS::Edge(BDS.Shape(S2)), aVertex))
      {
        LI.Remove(it2);
        continue;
      }

      bool sameG = (GT2 == GT1) && (G2 == G1);
      if (!sameG)
        break;

      if (GT1 == TopOpeBRepDS_VERTEX)
      {
        TopoDS_Vertex vG1     = TopoDS::Vertex(BDS.Shape(G1));
        int           rankvG1 = BDS.AncestorRank(vG1);
        int           sdG1;
        bool          G1hsd = FUN_ds_getVsdm(BDS, G1, sdG1);
        if (rankvG1 != rankE)
        {
          OOv  = vG1;
          Gsta = G1hsd ? 3 : 2;
        }
        else
        {
          if (G1hsd)
            OOv = BDS.Shape(sdG1);
          Gsta = G1hsd ? 3 : 1;
        }
      }

      const TopoDS_Face& F1 = TopoDS::Face(BDS.Shape(IB1));
      const TopoDS_Face& F2 = TopoDS::Face(BDS.Shape(IB2));

      bool sameS = (ST2 == ST1) && (S2 == S1);
      if (!sameS)
      {
        TopoDS_Shape Eshared;
        bool         foundsh = FUN_tool_Eshared(OOv, F1, F2, Eshared);
        if (!foundsh)
          return;

        if (!BDS.HasShape(Eshared))
        {
          return;
        }

        S1 = S2 = BDS.Shape(Eshared);
      }

      const TopoDS_Edge& E1 = TopoDS::Edge(BDS.Shape(S1));
      const TopoDS_Edge& E2 = TopoDS::Edge(BDS.Shape(S2));

      bool sdm = FUN_ds_sdm(BDS, E, E1);
      if (sdm)
      {

        it2.Next();
        continue;
      }

      bool init     = !isComplex;
      bool isvertex = (GT1 == TopOpeBRepDS_VERTEX);
      init          = init || isvertex;

      if (init)
      {

        if (isComplex)
        {
          occ::handle<TopOpeBRepDS_Interference> IBID = new TopOpeBRepDS_Interference();
          EFITool.Transition(IBID);
          I1->ChangeTransition().Set(IBID->Transition().Orientation(TopAbs_IN));
        }

        if (!isComplex)
          EFITool.InitPointVertex(Gsta, OOv);
        isComplex = true;
        EFITool.Init(E, E1, F1, I1);
        EFITool.Add(E, E1, F1, I1);
      }

      EFITool.Add(E, E2, F2, I2);
      LI.Remove(it2);
    }

    if (isComplex)
    {
      occ::handle<TopOpeBRepDS_Interference> newI;
      occ::handle<TopOpeBRepDS_Interference> IIBID = new TopOpeBRepDS_Interference();
      EFITool.Transition(IIBID);
      TopOpeBRepDS_Transition T = IIBID->Transition();
      T.Index(IB1);

      bool isevi = I1->IsKind(STANDARD_TYPE(TopOpeBRepDS_EdgeVertexInterference));
      bool iscpi = I1->IsKind(STANDARD_TYPE(TopOpeBRepDS_CurvePointInterference));
      if (isevi)
      {
        occ::handle<TopOpeBRepDS_EdgeVertexInterference> EVI(
          occ::down_cast<TopOpeBRepDS_EdgeVertexInterference>(I1));
        newI = new TopOpeBRepDS_EdgeVertexInterference(T,
                                                       TopOpeBRepDS_FACE,
                                                       IB1,
                                                       G1,
                                                       EVI->GBound(),
                                                       TopOpeBRepDS_UNSHGEOMETRY,
                                                       EVI->Parameter());
      }
      if (iscpi)
      {
        occ::handle<TopOpeBRepDS_CurvePointInterference> CPI(
          occ::down_cast<TopOpeBRepDS_CurvePointInterference>(I1));
        newI = new TopOpeBRepDS_CurvePointInterference(T,
                                                       TopOpeBRepDS_FACE,
                                                       IB1,
                                                       TopOpeBRepDS_POINT,
                                                       G1,
                                                       CPI->Parameter());
      }

      if (!newI.IsNull())
      {
        reducedLI.Append(newI);
        LI.Remove(it1);
      }
    }
    else
      it1.Next();
  }
}

static void FUN_ReducerEdge(const int                                                 SIX,
                            const TopOpeBRepDS_DataStructure&                         BDS,
                            NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                            NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& reducedLI)

{
  FDS_repvg(BDS, SIX, TopOpeBRepDS_VERTEX, LI, reducedLI);
  FDS_reduceONFACEinterferences(LI, BDS, SIX);
  FDS_repvg(BDS, SIX, TopOpeBRepDS_POINT, LI, reducedLI);
}

static void FUN_ReducerSDEdge(const int                                                 SIX,
                              const TopOpeBRepDS_DataStructure&                         BDS,
                              NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                              NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& reducedLI)

{
  reducedLI.Clear();
  int nI = LI.Extent();

  if (nI <= 1)
    return;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> newLI;
  const TopoDS_Shape&                                      EIX = BDS.Shape(SIX);
  TopOpeBRepDS_TKI                                         tki;
  tki.FillOnGeometry(LI);
  for (tki.Init(); tki.More(); tki.Next())
  {
    TopOpeBRepDS_Kind K;
    int               G;
    tki.Value(K, G);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.ChangeValue(K, G);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>  Rloi;

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(loi);
    while (it1.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I1    = it1.Value();
      const TopOpeBRepDS_Transition&                T1    = I1->Transition();
      TopAbs_Orientation                            O1    = T1.Orientation(TopAbs_IN);
      int                                           IB1   = T1.Index();
      bool                                          cond1 = FUN_ds_sdm(BDS, EIX, BDS.Shape(IB1));
      if (!cond1)
      {
        newLI.Append(I1);
        it1.Next();
        continue;
      }

      bool                                                               complex1d = false;
      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
      if (it2.More())
        it2.Next();
      else
        break;

      TopOpeBRepDS_Transition T(TopAbs_IN, TopAbs_IN, TopAbs_EDGE, TopAbs_EDGE);
      while (it2.More())
      {
        const occ::handle<TopOpeBRepDS_Interference>& I2    = it2.Value();
        const TopOpeBRepDS_Transition&                T2    = I2->Transition();
        TopAbs_Orientation                            O2    = T2.Orientation(TopAbs_IN);
        int                                           IB2   = T2.Index();
        bool                                          cond2 = FUN_ds_sdm(BDS, EIX, BDS.Shape(IB2));
        if (!cond2)
        {
          newLI.Append(I2);
          it2.Next();
          continue;
        }

        complex1d = (M_FORWARD(O1) && M_REVERSED(O2));
        complex1d = complex1d || (M_FORWARD(O2) && M_REVERSED(O1));
        if (!complex1d)
        {
          newLI.Append(I2);
          it2.Next();
          continue;
        }

        if (complex1d)
        {
          int IB = (M_REVERSED(O1)) ? IB1 : IB2;
          T.IndexBefore(IB);
          int IA = (M_REVERSED(O1)) ? IB2 : IB1;
          T.IndexAfter(IA);
        }
        loi.Remove(it2);
        break;
      }

      if (complex1d)
      {
        occ::handle<TopOpeBRepDS_EdgeVertexInterference> EVI(
          occ::down_cast<TopOpeBRepDS_EdgeVertexInterference>(I1));
        TopOpeBRepDS_Config cEIX = BDS.SameDomainOri(SIX), c1 = BDS.SameDomainOri(IB1);
        TopOpeBRepDS_Config Conf =
          (cEIX == c1) ? TopOpeBRepDS_SAMEORIENTED : TopOpeBRepDS_DIFFORIENTED;
        occ::handle<TopOpeBRepDS_Interference> newI =
          new TopOpeBRepDS_EdgeVertexInterference(T,
                                                  TopOpeBRepDS_EDGE,
                                                  IB1,
                                                  G,
                                                  EVI->GBound(),
                                                  Conf,
                                                  EVI->Parameter());
        reducedLI.Append(newI);
        it1.Next();
      }
      else
      {
        newLI.Append(I1);
        loi.Remove(it1);
      }
    }
  }

  LI.Clear();
  LI.Append(newLI);
}

static void FUN_reclSE2(const int                                                 SIX,
                        const TopOpeBRepDS_DataStructure&                         BDS,
                        NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                        NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& reducedLI)

{
  reducedLI.Clear();

  const TopoDS_Edge& E = TopoDS::Edge(BDS.Shape(SIX));

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(LI);
  while (it1.More())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I1 = it1.Value();
    TopOpeBRepDS_Kind                             GT1, ST1;
    int                                           G1, S1;
    FDS_data(I1, GT1, G1, ST1, S1);

    const TopOpeBRepDS_Transition& T1 = I1->Transition();
    TopAbs_Orientation             O1 = T1.Orientation(TopAbs_IN);
    if (M_INTERNAL(O1) || M_EXTERNAL(O1))
    {
      it1.Next();
      continue;
    }
    TopAbs_Orientation cO1 = TopAbs::Complement(O1);

    const TopoDS_Vertex& v1 = TopoDS::Vertex(BDS.Shape(G1));
    const TopoDS_Edge&   E1 = TopoDS::Edge(BDS.Shape(S1));
    TopoDS_Vertex        vclo1;
    bool                 iscE1 = TopOpeBRepTool_TOOL::ClosedE(E1, vclo1);
    if (!iscE1)
    {
      it1.Next();
      continue;
    }
    if (!vclo1.IsSame(v1))
    {
      it1.Next();
      continue;
    }

    bool sdm = FUN_ds_sdm(BDS, E, E1);
    if (!sdm)
    {
      it1.Next();
      continue;
    }

    bool                                                               hascO = false;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
    if (it2.More())
      it2.Next();
    else
    {
      it1.Next();
      continue;
    }
    while (it2.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I2 = it2.Value();
      const TopOpeBRepDS_Transition&                T2 = I2->Transition();
      TopAbs_Orientation                            O2 = T2.Orientation(TopAbs_IN);
      TopOpeBRepDS_Kind                             GT2, ST2;
      int                                           G2, S2;
      FDS_data(I2, GT2, G2, ST2, S2);

      if (S1 != S2)
      {
        it2.Next();
        continue;
      }
      if (O2 != cO1)
      {
        it2.Next();
        continue;
      }

      LI.Remove(it2);
      hascO = true;
      break;
    }

    if (hascO)
    {
      I1->ChangeTransition().Set(TopAbs_INTERNAL);
      reducedLI.Append(I1);
      LI.Remove(it1);
    }
    else
      it1.Next();
  }
}

Standard_EXPORT void FUN_reclSE(const int                                                 EIX,
                                const TopOpeBRepDS_DataStructure&                         BDS,
                                NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LOI,
                                NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& RLOI)

{
  TopOpeBRepDS_TKI tki;
  tki.FillOnGeometry(LOI);

  LOI.Clear();
  for (tki.Init(); tki.More(); tki.Next())
  {
    TopOpeBRepDS_Kind K;
    int               G;
    tki.Value(K, G);
    if (K != TopOpeBRepDS_VERTEX)
      continue;

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.ChangeValue(K, G);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>  Rloi;
    int                                                       nloi = loi.Extent();
    if (nloi == 0)
      continue;
    else if (nloi == 1)
      LOI.Append(loi);
    else
    {
      FUN_reclSE2(EIX, BDS, loi, Rloi);
      LOI.Append(loi);
      RLOI.Append(Rloi);
    }
  }
}

static void FUN_unkeepEVIonGb1(const TopOpeBRepDS_DataStructure&                         BDS,
                               const int                                                 EIX,
                               NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)

{

  const TopoDS_Edge& E = TopoDS::Edge(BDS.Shape(EIX));

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(LI);
  while (it.More())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I = it.Value();
    bool evi = I->IsKind(STANDARD_TYPE(TopOpeBRepDS_EdgeVertexInterference));
    if (!evi)
    {
      it.Next();
      continue;
    }
    TopOpeBRepDS_Kind GT, ST;
    int               G, S;
    FDS_data(I, GT, G, ST, S);
    if (GT != TopOpeBRepDS_VERTEX)
    {
      it.Next();
      continue;
    }

    const TopoDS_Vertex& V = TopoDS::Vertex(BDS.Shape(G));
    int                  o = FUN_tool_orientVinE(V, E);
    if (o == 0)
    {
      it.Next();
      continue;
    }

    LI.Remove(it);
  }
}

static void FUN_keepl3dF(const int,
                         const occ::handle<TopOpeBRepDS_HDataStructure>&,
                         const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l3dF,
                         const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LR3dFE,
                         NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&       l3dFkeep)

{
  TopOpeBRepDS_TKI tki;
  tki.FillOnGeometry(l3dF);

  TopOpeBRepDS_TKI tkiR;
  tkiR.FillOnGeometry(LR3dFE);

  for (tki.Init(); tki.More(); tki.Next())
  {
    TopOpeBRepDS_Kind K;
    int               G;
    tki.Value(K, G);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.ChangeValue(K, G);
    tkiR.Init();
    bool isbound = tkiR.IsBound(K, G);
    if (!isbound)
    {
      l3dFkeep.Append(loi);
    }
  }
}

static void FUN_reducepure2dI0(NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                               NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& RLI)

{
  const occ::handle<TopOpeBRepDS_Interference>& I1 = LI.First();
  TopAbs_Orientation                            O1 = I1->Transition().Orientation(TopAbs_IN);
  TopOpeBRepDS_Kind                             GT1, ST1;
  int                                           G1, S1;
  TopAbs_ShapeEnum                              tsb1, tsa1;
  int                                           isb1, isa1;
  FDS_Idata(I1, tsb1, isb1, tsa1, isa1, GT1, G1, ST1, S1);

  const occ::handle<TopOpeBRepDS_Interference>& I2 = LI.Last();
  TopAbs_Orientation                            O2 = I2->Transition().Orientation(TopAbs_IN);
  TopOpeBRepDS_Kind                             GT2, ST2;
  int                                           G2, S2;
  TopAbs_ShapeEnum                              tsb2, tsa2;
  int                                           isb2, isa2;
  FDS_Idata(I2, tsb2, isb2, tsa2, isa2, GT2, G2, ST2, S2);

  if (isb1 == isb2)
    return;

  bool ok = (G1 == G2);
  ok      = ok && (tsb1 == TopAbs_FACE) && (tsb1 == tsb2) && (isb1 == isa1) && (isb2 == isa2);
  if (!ok)
    return;

  bool int12 = M_REVERSED(O1) && M_FORWARD(O2);
  bool int21 = M_REVERSED(O2) && M_FORWARD(O1);
  ok         = int12 || int21;
  if (!ok)
    return;

  TopOpeBRepDS_Transition newT(TopAbs_INTERNAL);
  int                     bef = int12 ? isb1 : isb2;
  int                     aft = int21 ? isb1 : isb2;
  newT.IndexBefore(bef);
  newT.IndexAfter(aft);
  I1->ChangeTransition() = newT;
  RLI.Append(I1);
  LI.Clear();
}

static void FUN_reducepure2dI(NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                              NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& RLI)
{
  TopOpeBRepDS_TKI tki;
  tki.FillOnGeometry(LI);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> newLI;
  for (tki.Init(); tki.More(); tki.Next())
  {
    TopOpeBRepDS_Kind K;
    int               G;
    tki.Value(K, G);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.ChangeValue(K, G);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>  Rloi;
    int                                                       nloi = loi.Extent();
    bool ok = (nloi == 2) && (K == TopOpeBRepDS_POINT);
    if (ok)
      ::FUN_reducepure2dI0(loi, Rloi);
    RLI.Append(Rloi);
    newLI.Append(loi);
  }
  LI.Clear();
  LI.Append(newLI);
}

TopOpeBRepDS_EIR::TopOpeBRepDS_EIR(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS)
    : myHDS(HDS)
{
}

void TopOpeBRepDS_EIR::ProcessEdgeInterferences()
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();
  int                         i, nshape = BDS.NbShapes();
  for (i = 1; i <= nshape; i++)
  {
    const TopoDS_Shape& S = BDS.Shape(i);
    if (S.IsNull())
      continue;
    if (S.ShapeType() == TopAbs_EDGE)
    {
      ProcessEdgeInterferences(i);
    }
  }
}

static void FUN_ProcessEdgeInterferences(
  const int EIX,
  const TopOpeBRepDS_Kind,
  const int,
  const occ::handle<TopOpeBRepDS_HDataStructure>&           HDS,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)
{
  TopOpeBRepDS_DataStructure& BDS = HDS->ChangeDS();
  const TopoDS_Shape&         E   = BDS.Shape(EIX);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lF;
  FUN_selectTRASHAinterference(LI, TopAbs_FACE, lF);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lFE;
  FUN_selectSKinterference(lF, TopOpeBRepDS_EDGE, lFE);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lE;
  FUN_selectTRASHAinterference(LI, TopAbs_EDGE, lE);

  bool isse = BDS.IsSectionEdge(TopoDS::Edge(E));
  if (isse)
  {
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lI2dFE, lRI2dFE;

    FUN_selectpure2dI(lF, lFE, lI2dFE);
    ::FUN_reducepure2dI(lI2dFE, lRI2dFE);
    lFE.Append(lI2dFE);
    lFE.Append(lRI2dFE);
  }

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lFEresi, l3dFE, l3dF, l3dFEresi, l2dFE;
  FUN_select3dinterference(EIX, BDS, lF, l3dF, lFE, lFEresi, l3dFE, l3dFEresi, l2dFE);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1dE;
  FUN_select2dI(EIX, BDS, TopAbs_EDGE, lE, l1dE);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1dEsd;
  FUN_select1dI(EIX, BDS, lE, l1dEsd);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lR3dFE;
  FUN_ReducerEdge3d(EIX, BDS, l3dFE, lR3dFE);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3dFkeep;
  FUN_keepl3dF(EIX, HDS, l3dF, lR3dFE, l3dFkeep);
  lF.Append(l3dFkeep);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LR2dFE;
  FUN_ReducerEdge(EIX, BDS, l2dFE, LR2dFE);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lR1dEsd;
  FUN_ReducerSDEdge(EIX, BDS, l1dEsd, lR1dEsd);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lR1dclosedSE;
  FUN_reclSE(EIX, BDS, l1dE, lR1dclosedSE);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LR1dE;
  FUN_ReducerEdge(EIX, BDS, l1dE, LR1dE);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LRI;
  LRI.Append(lR1dEsd);
  LRI.Append(LR1dE);
  LRI.Append(lR1dclosedSE);
  LRI.Append(LR2dFE);
  LRI.Append(lR3dFE);

  lF.Append(lFE);
  lF.Append(l3dFE);
  lF.Append(l2dFE);
  lE.Append(l1dE);
  lE.Append(l1dEsd);

  LI.Clear();
  LI.Append(LRI);
  LI.Append(lE);
  LI.Append(lF);

  if (isse)
  {
    FUN_unkeepEVIonGb1(BDS, EIX, LI);
  }
}

void TopOpeBRepDS_EIR::ProcessEdgeInterferences(const int EIX)
{
  TopOpeBRepDS_DataStructure& BDS = myHDS->ChangeDS();

  const TopoDS_Edge& E    = TopoDS::Edge(BDS.Shape(EIX));
  bool               isdg = BRep_Tool::Degenerated(E);
  if (isdg)
    return;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI = BDS.ChangeShapeInterferences(EIX);
  TopOpeBRepDS_TKI                                          newtki;
  newtki.FillOnGeometry(LI);
  TopOpeBRepDS_TKI tki;
  tki.FillOnGeometry(LI);
  for (tki.Init(); tki.More(); tki.Next())
  {
    TopOpeBRepDS_Kind K;
    int               G;
    tki.Value(K, G);
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.Value(K, G);
    if (K == TopOpeBRepDS_POINT)
      continue;
    const TopoDS_Shape& vG = BDS.Shape(G);
    TopoDS_Shape        oovG;
    bool                sdm = FUN_ds_getoov(vG, BDS, oovG);
    if (!sdm)
      continue;
    int OOG = BDS.Shape(oovG);
    if (OOG == 0)
      continue;

    bool isb = newtki.IsBound(K, OOG);

    bool isbound = occ::down_cast<TopOpeBRepDS_EdgeVertexInterference>(loi.First())->GBound();
    if (isbound)
    {
      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(loi);
      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>           newloi;
      for (; it.More(); it.Next())
      {
        const occ::handle<TopOpeBRepDS_Interference>& I = it.Value();
        TopOpeBRepDS_Kind                             GT, ST;
        int                                           G1, S;
        FDS_data(I, GT, G1, ST, S);
        double                                 par = FDS_Parameter(I);
        occ::handle<TopOpeBRepDS_Interference> newI =
          MakeEPVInterference(I->Transition(), S, OOG, par, K, ST, false);
        newloi.Append(newI);
      }
      newtki.ChangeInterferences(K, G).Clear();
      if (!isb)
        newtki.Add(K, OOG);
      newtki.ChangeInterferences(K, OOG).Append(newloi);
      continue;
    }

    if (!isb)
      continue;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& li =
      newtki.ChangeInterferences(K, OOG);
    newtki.ChangeInterferences(K, G).Append(li);
  }

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LInew;
  for (newtki.Init(); newtki.More(); newtki.Next())
  {
    TopOpeBRepDS_Kind K;
    int               G;
    newtki.Value(K, G);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = newtki.ChangeValue(K, G);
    ::FUN_ProcessEdgeInterferences(EIX, K, G, myHDS, loi);
    LInew.Append(loi);
  }
  LI.Clear();
  LI.Append(LInew);

  bool performPNC = false;

  if (!performPNC)
    return;

  bool isfafa = BDS.Isfafa();
  if (!isfafa)
  {

    tki.Clear();
    tki.FillOnGeometry(LI);
    LI.Clear();

    for (tki.Init(); tki.More(); tki.Next())
    {
      TopOpeBRepDS_Kind K;
      int               G;
      tki.Value(K, G);
      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.ChangeValue(K, G);
      if (K != TopOpeBRepDS_POINT)
      {
        LI.Append(loi);
        continue;
      }

      const NCollection_List<TopoDS_Shape>& lfx = FDSCNX_EdgeConnexitySameShape(E, myHDS);

      NCollection_List<TopoDS_Shape>::Iterator itlfx(lfx);
      bool                                     curvefound = false;
      for (; itlfx.More(); itlfx.Next())
      {
        const TopoDS_Face& fx = TopoDS::Face(itlfx.Value());

        const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lifx =
          BDS.ShapeInterferences(fx);
        NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itlifx(lifx);
        if (!itlifx.More())
          continue;

        occ::handle<TopOpeBRepDS_Interference> I1;
        TopOpeBRepDS_Kind                      GT1;
        int                                    G1;
        TopOpeBRepDS_Kind                      ST1;
        int                                    S1;
        for (; itlifx.More(); itlifx.Next())
        {
          FDS_data(itlifx, I1, GT1, G1, ST1, S1);
          bool isfci = (GT1 == TopOpeBRepDS_CURVE);
          if (!isfci)
            continue;

          NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lic =
            BDS.ChangeCurveInterferences(G1);
          NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itlic(lic);
          if (!itlic.More())
            continue;

          occ::handle<TopOpeBRepDS_Interference> I2;
          TopOpeBRepDS_Kind                      GT2;
          int                                    G2;
          TopOpeBRepDS_Kind                      ST2;
          int                                    S2;
          for (; itlic.More(); itlic.Next())
          {
            FDS_data(itlic, I2, GT2, G2, ST2, S2);
            bool isp = (GT2 == TopOpeBRepDS_POINT);
            if (!isp)
              continue;
            if (G2 != G)
              continue;
            curvefound = true;
            break;
          }

          if (curvefound)
            break;
        }

        if (curvefound)
          break;
      }

      if (curvefound)
      {
        LI.Append(loi);
      }
    }
  }
}

static bool CheckInterferenceIsValid(const occ::handle<TopOpeBRepDS_Interference>& I,
                                     const TopoDS_Edge&                            theEdge,
                                     const TopoDS_Edge&                            theSupportEdge,
                                     const TopoDS_Vertex&                          theVertex)
{
  double            pref = 0.;
  bool              ok   = false;
  BRepAdaptor_Curve BC(theEdge);

  occ::handle<TopOpeBRepDS_CurvePointInterference> CPI;
  CPI = occ::down_cast<TopOpeBRepDS_CurvePointInterference>(I);

  if (!CPI.IsNull())
  {
    pref = CPI->Parameter();
    ok   = true;
  }

  if (!ok)
  {
    occ::handle<TopOpeBRepDS_EdgeVertexInterference> EVI =
      occ::down_cast<TopOpeBRepDS_EdgeVertexInterference>(I);
    if (!EVI.IsNull())
    {
      pref = EVI->Parameter();
      ok   = true;
    }
  }

  if (!ok)
    return ok;

  gp_Pnt P3d1 = BC.Value(pref);
  double dist, paronSupportE;
  ok = FUN_tool_projPonE(P3d1, theSupportEdge, paronSupportE, dist);

  if (!ok)
    return ok;
  BRepAdaptor_Curve BCtmp(theSupportEdge);
  gp_Pnt            P3d2 = BCtmp.Value(paronSupportE);
  double Tolerance       = (BRep_Tool::Tolerance(theEdge) > BRep_Tool::Tolerance(theSupportEdge))
                             ? BRep_Tool::Tolerance(theEdge)
                             : BRep_Tool::Tolerance(theSupportEdge);
  if (!theVertex.IsNull())
  {
    Tolerance =
      (BRep_Tool::Tolerance(theVertex) > Tolerance) ? BRep_Tool::Tolerance(theVertex) : Tolerance;
  }
  if (P3d1.Distance(P3d2) > Tolerance)
  {
    ok = false;
  }

  return ok;
}
