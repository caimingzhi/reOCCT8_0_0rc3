#include <TopOpeBRepDS_InterferenceTool.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>
#include <TopOpeBRepDS_EdgeVertexInterference.hpp>
#include <TopOpeBRepDS_TKI.hpp>
#include <TopoDS.hpp>
#include <BRepAdaptor_Surface.hpp>

#include <BRep_Tool.hpp>
#include <Precision.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
#include <Standard_ProgramError.hpp>
#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepTool_TOOL.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepDS_EXPORT.hpp>

Standard_EXPORT occ::handle<TopOpeBRepDS_Interference> MakeCPVInterference(
  const TopOpeBRepDS_Transition& T,
  const int                      SI,
  const int                      GI,
  const double                   P,
  const TopOpeBRepDS_Kind        GK)

{
  occ::handle<TopOpeBRepDS_Interference> I;
  TopOpeBRepDS_Kind                      SK = TopOpeBRepDS_CURVE;
  I = TopOpeBRepDS_InterferenceTool::MakeCurveInterference(T, SK, SI, GK, GI, P);
  return I;
}

Standard_EXPORT occ::handle<TopOpeBRepDS_Interference> MakeEPVInterference(
  const TopOpeBRepDS_Transition& T,
  const int                      SI,
  const int                      GI,
  const double                   P,
  const TopOpeBRepDS_Kind        GK,
  const bool                     B)

{
  occ::handle<TopOpeBRepDS_Interference> I;
  TopOpeBRepDS_Kind                      SK = TopOpeBRepDS_EDGE;
  if (GK == TopOpeBRepDS_POINT)
  {
    I = TopOpeBRepDS_InterferenceTool::MakeEdgeInterference(T, SK, SI, GK, GI, P);
  }
  else if (GK == TopOpeBRepDS_VERTEX)
  {
    I = TopOpeBRepDS_InterferenceTool::MakeEdgeVertexInterference(T,
                                                                  SI,
                                                                  GI,
                                                                  B,
                                                                  TopOpeBRepDS_UNSHGEOMETRY,
                                                                  P);
    I->GeometryType(GK);
  }
  return I;
}

Standard_EXPORT occ::handle<TopOpeBRepDS_Interference> MakeEPVInterference(
  const TopOpeBRepDS_Transition& T,
  const int                      S,
  const int                      G,
  const double                   P,
  const TopOpeBRepDS_Kind        GK,
  const TopOpeBRepDS_Kind        SK,
  const bool                     B)

{
  occ::handle<TopOpeBRepDS_Interference> I = ::MakeEPVInterference(T, S, G, P, GK, B);
  I->SupportType(SK);
  return I;
}

Standard_EXPORT bool FUN_hasStateShape

  (const TopOpeBRepDS_Transition& T, const TopAbs_State state, const TopAbs_ShapeEnum shape)
{
  TopAbs_State     staB = T.Before(), staA = T.After();
  TopAbs_ShapeEnum shaB = T.ShapeBefore(), shaA = T.ShapeAfter();
  bool             B      = (staB == state) && (shaB == shape);
  bool             A      = (staA == state) && (shaA == shape);
  bool             result = B || A;
  return result;
}

Standard_EXPORT int FUN_selectTRASHAinterference

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
   const TopAbs_ShapeEnum                                    sha2,
   NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L2)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(L1);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference> I1 = it1.Value();
    const TopOpeBRepDS_Transition&         T1 = I1->Transition();

    TopAbs_ShapeEnum shab = T1.ShapeBefore(), shaa = T1.ShapeAfter();
    bool             sel = ((shab == sha2) || (shaa == sha2));
    if (sel)
    {
      L2.Append(I1);
      L1.Remove(it1);
    }
    else
      it1.Next();
  }
  int n2 = L2.Extent();
  return n2;
}

Standard_EXPORT int FUN_selectITRASHAinterference

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
   const int                                                 Index,
   NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L2)
{
  if (Index == 0)
    return 0;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(L1);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference> I1  = it1.Value();
    const TopOpeBRepDS_Transition&         T1  = I1->Transition();
    int                                    Ind = T1.Index();
    if (Ind == Index)
    {
      L2.Append(I1);
      L1.Remove(it1);
    }
    else
      it1.Next();
  }
  int n2 = L2.Extent();
  return n2;
}

Standard_EXPORT int FUN_selectTRAUNKinterference

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
   NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L2)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(L1);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference> I1  = it1.Value();
    const TopOpeBRepDS_Transition&         T1  = I1->Transition();
    bool                                   sel = T1.IsUnknown();
    if (sel)
    {
      L2.Append(I1);
      L1.Remove(it1);
    }
    else
      it1.Next();
  }
  int n2 = L2.Extent();
  return n2;
}

Standard_EXPORT int FUN_selectTRAORIinterference

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
   const TopAbs_Orientation                                  O,
   NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L2)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(L1);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference> I1  = it1.Value();
    const TopOpeBRepDS_Transition&         T1  = I1->Transition();
    TopAbs_Orientation                     ori = T1.Orientation(TopAbs_IN);
    bool                                   sel = (ori == O);
    if (sel)
    {
      L2.Append(I1);
      L1.Remove(it1);
    }
    else
      it1.Next();
  }
  int n2 = L2.Extent();
  return n2;
}

Standard_EXPORT int FUN_selectGKinterference

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
   const TopOpeBRepDS_Kind                                   GK,
   NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L2)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(L1);
  while (it1.More())
  {
    TopOpeBRepDS_Kind gki = it1.Value()->GeometryType();
    if (gki == GK)
    {
      L2.Append(it1.Value());
      L1.Remove(it1);
    }
    else
      it1.Next();
  }
  int n2 = L2.Extent();
  return n2;
}

Standard_EXPORT int FUN_selectSKinterference

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
   const TopOpeBRepDS_Kind                                   SK,
   NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L2)
{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(L1);
  while (it1.More())
  {
    TopOpeBRepDS_Kind ski = it1.Value()->SupportType();
    if (ski == SK)
    {
      L2.Append(it1.Value());
      L1.Remove(it1);
    }
    else
      it1.Next();
  }
  int n2 = L2.Extent();
  return n2;
}

Standard_EXPORT int FUN_selectGIinterference

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
   const int                                                 GI,
   NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L2)
{
  if (GI == 0)
    return 0;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(L1);
  while (it1.More())
  {
    int gi = it1.Value()->Geometry();
    if (gi == GI)
    {
      L2.Append(it1.Value());
      L1.Remove(it1);
    }
    else
      it1.Next();
  }
  int n2 = L2.Extent();
  return n2;
}

Standard_EXPORT int FUN_selectSIinterference

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L1,
   const int                                                 SI,
   NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L2)
{
  if (SI == 0)
    return 0;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(L1);
  while (it1.More())
  {
    int si = it1.Value()->Support();
    if (si == SI)
    {
      L2.Append(it1.Value());
      L1.Remove(it1);
    }
    else
      it1.Next();
  }
  int n2 = L2.Extent();
  return n2;
}

Standard_EXPORT bool FUN_interfhassupport

  (const TopOpeBRepDS_DataStructure&             DS,
   const occ::handle<TopOpeBRepDS_Interference>& I,
   const TopoDS_Shape&                           S)
{
  bool                h     = true;
  const int           index = I->Support();
  const TopoDS_Shape& SofI  = DS.Shape(index);
  h                         = SofI.IsSame(S);
  return h;
}

Standard_EXPORT bool FUN_transitionEQUAL

  (const TopOpeBRepDS_Transition& T1, const TopOpeBRepDS_Transition& T2)
{
  bool id1 = FUN_transitionSTATEEQUAL(T1, T2);
  bool id2 = FUN_transitionSHAPEEQUAL(T1, T2);
  bool id3 = FUN_transitionINDEXEQUAL(T1, T2);
  bool id  = id1 && id2 && id3;
  return id;
}

Standard_EXPORT bool FUN_transitionSTATEEQUAL

  (const TopOpeBRepDS_Transition& T1, const TopOpeBRepDS_Transition& T2)
{
  bool id = T1.Before() == T2.Before() && T1.After() == T2.After();
  return id;
}

Standard_EXPORT bool FUN_transitionSHAPEEQUAL

  (const TopOpeBRepDS_Transition& T1, const TopOpeBRepDS_Transition& T2)
{
  bool id = T1.ShapeBefore() == T2.ShapeBefore() && T1.ShapeAfter() == T2.ShapeAfter();
  return id;
}

Standard_EXPORT bool FUN_transitionINDEXEQUAL

  (const TopOpeBRepDS_Transition& T1, const TopOpeBRepDS_Transition& T2)
{
  bool id = T1.IndexBefore() == T2.IndexBefore() && T1.IndexAfter() == T2.IndexAfter();
  return id;
}

Standard_EXPORT void FUN_reducedoublons

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   const TopOpeBRepDS_DataStructure&                         BDS,
   const int                                                 SIX)
{

  const TopoDS_Shape&                                                E = BDS.Shape(SIX);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;

  it1.Initialize(LI);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference>& I1 = it1.ChangeValue();
    const TopOpeBRepDS_Transition&          T1 = I1->Transition();
    TopOpeBRepDS_Kind                       GT1, ST1;
    int                                     G1, S1;
    FDS_data(I1, GT1, G1, ST1, S1);
    TopAbs_ShapeEnum tsb1, tsa1;
    int              isb1, isa1;
    FDS_Tdata(I1, tsb1, isb1, tsa1, isa1);

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
    it2.Next();
    while (it2.More())
    {

      const occ::handle<TopOpeBRepDS_Interference>& I2 = it2.Value();
      const TopOpeBRepDS_Transition&                T2 = I2->Transition();
      TopOpeBRepDS_Kind                             GT2, ST2;
      int                                           G2, S2;
      FDS_data(I2, GT2, G2, ST2, S2);
      TopAbs_ShapeEnum tsb2, tsa2;
      int              isb2, isa2;
      FDS_Tdata(I2, tsb2, isb2, tsa2, isa2);

      bool idGS = (GT2 == GT1 && G2 == G1 && ST2 == ST1 && S2 == S1);
      if (idGS)
      {

        bool id1 = FUN_transitionSTATEEQUAL(T1, T2);
        bool id2 = FUN_transitionSHAPEEQUAL(T1, T2);
        bool id3 = FUN_transitionINDEXEQUAL(T1, T2);
        bool idT = id1 && id2 && id3;

        if (idT)
        {
          const occ::handle<TopOpeBRepDS_EdgeVertexInterference> EVI1 =
            occ::down_cast<TopOpeBRepDS_EdgeVertexInterference>(I1);
          const occ::handle<TopOpeBRepDS_EdgeVertexInterference> EVI2 =
            occ::down_cast<TopOpeBRepDS_EdgeVertexInterference>(I2);
          bool evi = (!EVI1.IsNull()) && (!EVI2.IsNull());
          if (evi)
          {

            const TopoDS_Vertex& vG = TopoDS::Vertex(BDS.Shape(G1));
            TopoDS_Vertex        OOv;
            bool                 hasOO = FUN_ds_getoov(vG, BDS, OOv);
            TopoDS_Vertex        vclo;
            bool                 Eclosed = TopOpeBRepTool_TOOL::ClosedE(TopoDS::Edge(E), vclo);
            bool                 onvclo  = false;
            if (Eclosed)
            {
              onvclo = vG.IsSame(vG);
              if (hasOO && !onvclo)
                onvclo = vG.IsSame(OOv);
            }
            if (onvclo)
              idT = true;
            else
            {

              double tolE    = FUN_tool_maxtol(E);
              double t       = Precision::Parametric(tolE);
              double t1      = EVI1->Parameter();
              double t2      = EVI2->Parameter();
              double dd      = t1 - t2;
              bool   samepar = (std::abs(dd) <= t);
              idT            = samepar;
            }
          }
        }
        if (idT)
        {

          LI.Remove(it2);
        }
        else
          it2.Next();
      }
      else
        it2.Next();
    }
    it1.Next();
  }
}

Standard_EXPORT void FUN_unkeepUNKNOWN

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   TopOpeBRepDS_DataStructure&,
   const int)
{

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;

  it1.Initialize(LI);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference>& I1    = it1.ChangeValue();
    const TopOpeBRepDS_Transition&          T1    = I1->Transition();
    bool                                    isunk = T1.IsUnknown();

    if (isunk)
    {
      LI.Remove(it1);
    }
    else
      it1.Next();
  }
}

static int FUN_select3dI(const int                                                 SIX,
                         TopOpeBRepDS_DataStructure&                               BDS,
                         NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lFE,
                         NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lFEresi,
                         NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l3dFE)

{
  l3dFE.Clear();
  lFEresi.Clear();
  int n3d = 0;
  int nFE = lFE.Extent();
  if (nFE <= 1)
    return n3d;

  const TopoDS_Edge& E     = TopoDS::Edge(BDS.Shape(SIX));
  int                rankE = BDS.AncestorRank(E);
  TopoDS_Shape       OOv;
  int                OOG = 0, Gsta = 0;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(lFE);
  while (it1.More())
  {

    bool                                          complex3d = false;
    const occ::handle<TopOpeBRepDS_Interference>& I1        = it1.Value();
    TopOpeBRepDS_Kind                             GT1, ST1;
    int                                           G1, S1;
    FDS_data(I1, GT1, G1, ST1, S1);
    TopAbs_ShapeEnum SB1, SA1;
    int              IB1, IA1;
    FDS_Tdata(I1, SB1, IB1, SA1, IA1);
    bool vertex1 = (GT1 == TopOpeBRepDS_VERTEX);

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
    if (it2.More())
      it2.Next();
    else
      break;

    if (vertex1)
    {
      TopoDS_Vertex vG1     = TopoDS::Vertex(BDS.Shape(G1));
      int           rankvG1 = BDS.AncestorRank(vG1);
      bool          G1hsd   = FUN_ds_getVsdm(BDS, G1, OOG);
      if (rankvG1 != rankE)
      {
        OOv  = vG1;
        Gsta = G1hsd ? 3 : 2;
      }
      else
      {
        if (G1hsd)
          OOv = BDS.Shape(OOG);
        Gsta = G1hsd ? 3 : 1;
      }
    }

    while (it2.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I2 = it2.Value();
      TopOpeBRepDS_Kind                             GT2, ST2;
      int                                           G2, S2;
      FDS_data(I2, GT2, G2, ST2, S2);
      TopAbs_ShapeEnum SB2, SA2;
      int              IB2, IA2;
      FDS_Tdata(I2, SB2, IB2, SA2, IA2);

      bool sameG = (GT2 == GT1);
      if (!sameG)
        break;
      sameG = (G2 == G1) || (G2 == OOG);

      const TopoDS_Face& F1 = TopoDS::Face(BDS.Shape(IB1));
      const TopoDS_Face& F2 = TopoDS::Face(BDS.Shape(IB2));

      bool sdmFT = (IB1 == IB2) || FUN_ds_sdm(BDS, F1, F2);

      if (sdmFT)
      {
        lFEresi.Append(I2);
        lFE.Remove(it2);
        continue;
      }

      bool sameS = (ST2 == ST1) && (S2 == S1);

      bool sameSorsharedEbyTRASHA = sameS;
      bool hasOOv                 = (Gsta > 1);
      if (!sameSorsharedEbyTRASHA && hasOOv)
      {
        TopoDS_Shape Eshared;
        bool         foundsh = FUN_tool_Eshared(OOv, F1, F2, Eshared);
        if (!foundsh)
        {
          it2.Next();
          continue;
        }

        sameSorsharedEbyTRASHA = true;
        if (!BDS.HasShape(Eshared))
        {
          int OOrank = BDS.AncestorRank(OOv);
          BDS.AddShape(Eshared, OOrank);
        }
        S1 = BDS.Shape(Eshared);
        S2 = S1;
      }

      if (sameSorsharedEbyTRASHA)
      {
        bool sdm = FUN_ds_sdm(BDS, BDS.Shape(SIX), BDS.Shape(S1));
        if (sdm)
        {
          it2.Next();
          continue;
        }
      }

      if (sameSorsharedEbyTRASHA)
      {
        l3dFE.Append(I2);
        lFE.Remove(it2);
        complex3d = true;
      }
      else
        it2.Next();
    }

    if (complex3d)
    {
      l3dFE.Append(I1);
      lFE.Remove(it1);
    }
    else
      it1.Next();
  }

  n3d       = l3dFE.Extent();
  int nresi = lFEresi.Extent();
  if (nresi == 0)
    return n3d;

  if (n3d != 0)
  {
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(lFEresi);
    while (it.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>&            I   = it.Value();
      int                                                      TRA = I->Transition().Index();
      NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lcopy;
      FDS_assign(l3dFE, lcopy);
      NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lfound;
      int nfound = FUN_selectITRASHAinterference(lcopy, TRA, lfound);
      if (nfound == 0)
        lFE.Remove(it);
      else
        it.Next();
    }
  }
  else
    lFE.Append(lFEresi);
  return n3d;
}

static bool FUN_find3dISEsameISF(
  const occ::handle<TopOpeBRepDS_Interference>&                       I1,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& it2)

{
  TopAbs_Orientation O1 = I1->Transition().Orientation(TopAbs_IN);
  TopOpeBRepDS_Kind  GT1, ST1;
  int                G1, S1;
  FDS_data(I1, GT1, G1, ST1, S1);
  TopAbs_ShapeEnum SB1, SA1;
  int              IB1, IA1;
  FDS_Tdata(I1, SB1, IB1, SA1, IA1);

  while (it2.More())
  {
    occ::handle<TopOpeBRepDS_Interference>& I2 = it2.ChangeValue();
    TopAbs_Orientation                      O2 = I2->Transition().Orientation(TopAbs_IN);
    TopOpeBRepDS_Kind                       GT2, ST2;
    int                                     G2, S2;
    FDS_data(I2, GT2, G2, ST2, S2);
    TopAbs_ShapeEnum SB2, SA2;
    int              IB2, IA2;
    FDS_Tdata(I2, SB2, IB2, SA2, IA2);
    bool sameT = (SB1 == SB2) && (IB1 == IB2) && (O1 == O2);
    bool sameG = (GT1 == GT2) && (G1 == G2);
    if (sameT && sameG)
      return true;
    else
      it2.Next();
  }
  return false;
}

static int FUN_select3dISEsameISF(
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lFE,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l3dFE,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l3dFEresi,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lF,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l3dF)

{

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(l3dFE);
  while (it1.More())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I1 = it1.Value();

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(lF);
    bool found = FUN_find3dISEsameISF(I1, it2);

    if (found)
    {
      l3dF.Append(it2.Value());
      lF.Remove(it2);
      it1.Next();
    }
    else
    {

      NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it3(l3dF);
      found = FUN_find3dISEsameISF(I1, it3);

      if (found)
        l3dFEresi.Append(I1);
      else
        lFE.Append(I1);
      l3dFE.Remove(it1);
    }
  }
  return l3dF.Extent();
}

Standard_EXPORT int FUN_select2dI(const int                                                 SIX,
                                  TopOpeBRepDS_DataStructure&                               BDS,
                                  const TopAbs_ShapeEnum                                    TRASHAk,
                                  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lI,
                                  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l2dI)

{
  l2dI.Clear();
  int n2d = 0;
  int nFE = lI.Extent();
  if (nFE <= 1)
    return n2d;

  bool TonFace = (TRASHAk == TopAbs_FACE);

  NCollection_Map<int>                                     mapftra;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> lIE;
  FDS_copy(BDS.ShapeInterferences(SIX), lIE);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3dF;
  FUN_selectSKinterference(lIE, TopOpeBRepDS_FACE, l3dF);
  for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itt(l3dF); itt.More();
       itt.Next())
    mapftra.Add(itt.Value()->Support());
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>           lII;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(lI);
  while (it1.More())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I       = it1.Value();
    int                                           ITRASHA = I->Transition().Index();
    if (mapftra.Contains(ITRASHA))
    {
      it1.Next();
    }
    else
    {
      lII.Append(I);
      lI.Remove(it1);
    }
  }

  it1.Initialize(lII);
  while (it1.More())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I1 = it1.Value();
    TopOpeBRepDS_Kind                             GT1, ST1;
    int                                           G1, S1;
    FDS_data(I1, GT1, G1, ST1, S1);
    TopAbs_ShapeEnum SB1, SA1;
    int              IB1, IA1;
    FDS_Tdata(I1, SB1, IB1, SA1, IA1);

    if (SB1 != TRASHAk)
    {
      it1.Next();
      continue;
    }

    bool                                                               complex2d = false;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
    if (it2.More())
      it2.Next();
    else
      break;
    while (it2.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I2 = it2.Value();
      TopOpeBRepDS_Kind                             GT2, ST2;
      int                                           G2, S2;
      FDS_data(I2, GT2, G2, ST2, S2);
      TopAbs_ShapeEnum SB2, SA2;
      int              IB2, IA2;
      FDS_Tdata(I2, SB2, IB2, SA2, IA2);

      bool cond = (SB1 == SB2) && (IB1 == IB2) && (IA1 == IA2);
      if (!cond)
      {
        it2.Next();
        continue;
      }

      bool sameG  = (GT2 == GT1) && (G2 == G1);
      bool sameST = (ST2 == ST1);
      cond        = sameG && sameST;
      if (!cond)
      {
        it2.Next();
        continue;
      }

      complex2d = (IB1 == IB2);
      if (TonFace)
      {
        const TopoDS_Face& F1 = TopoDS::Face(BDS.Shape(IB1));
        const TopoDS_Face& F2 = TopoDS::Face(BDS.Shape(IB2));
        complex2d             = complex2d || FUN_ds_sdm(BDS, F1, F2);
      }
      if (complex2d)
      {
        l2dI.Append(I2);
        lII.Remove(it2);
      }
      else
        it2.Next();
    }
    if (complex2d)
    {
      l2dI.Append(I1);
      lII.Remove(it1);
    }
    else
      it1.Next();
  }
  lI.Append(lII);
  n2d = l2dI.Extent();
  return n2d;
}

Standard_EXPORT int FUN_selectpure2dI(
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lF,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&       lFE,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>&       l2dFE)

{
  l2dFE.Clear();
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itFE(lFE);
  while (itFE.More())
  {
    const occ::handle<TopOpeBRepDS_Interference>& IFE = itFE.Value();
    const TopOpeBRepDS_Transition&                TFE = IFE->Transition();
    int                                           IB = TFE.IndexBefore(), IA = TFE.IndexAfter();
    if (IB != IA)
    {
      itFE.Next();
      continue;
    }

    bool foundIF = false;
    for (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator itF(lF); itF.More();
         itF.Next())
    {
      const occ::handle<TopOpeBRepDS_Interference>& IF = itF.Value();
      int                                           S  = IF->Support();
      if (S == IB)
      {
        foundIF = true;
        break;
      }
    }
    if (foundIF)
    {
      itFE.Next();
      continue;
    }

    l2dFE.Append(IFE);
    lFE.Remove(itFE);
  }
  int n2dFE = l2dFE.Extent();
  return n2dFE;
}

Standard_EXPORT int FUN_select1dI(const int                                                 SIX,
                                  TopOpeBRepDS_DataStructure&                               BDS,
                                  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
                                  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l1dI)

{
  l1dI.Clear();
  int n1d = 0;
  int nFE = LI.Extent();
  if (nFE <= 1)
    return n1d;

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
    int                                                       nloi = loi.Extent();

    bool ok = (K == TopOpeBRepDS_VERTEX);
    ok      = ok && (nloi > 1);
    if (!ok)
    {
      newLI.Append(loi);
      continue;
    }

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(loi);
    while (it1.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I1 = it1.Value();
      TopOpeBRepDS_Kind                             GT1, ST1;
      int                                           G1, S1;
      FDS_data(I1, GT1, G1, ST1, S1);
      TopAbs_ShapeEnum SB1, SA1;
      int              IB1, IA1;
      FDS_Tdata(I1, SB1, IB1, SA1, IA1);

      bool cond1 = (SB1 == TopAbs_EDGE) && (IB1 == IA1);
      if (!cond1)
      {
        newLI.Append(I1);
        it1.Next();
        continue;
      }
      cond1 = FUN_ds_sdm(BDS, EIX, BDS.Shape(S1));
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
      while (it2.More())
      {
        const occ::handle<TopOpeBRepDS_Interference>& I2 = it2.Value();
        TopOpeBRepDS_Kind                             GT2, ST2;
        int                                           G2, S2;
        FDS_data(I2, GT2, G2, ST2, S2);
        TopAbs_ShapeEnum SB2, SA2;
        int              IB2, IA2;
        FDS_Tdata(I2, SB2, IB2, SA2, IA2);

        bool cond2 = (SB1 == SB2) && (IB2 == IA2);
        if (!cond2)
        {
          newLI.Append(I2);
          it2.Next();
          continue;
        }
        complex1d = FUN_ds_sdm(BDS, EIX, BDS.Shape(S2));
        if (!complex1d)
        {
          newLI.Append(I2);
          it2.Next();
          continue;
        }

        l1dI.Append(I2);
        it2.Next();
      }
      if (complex1d)
      {
        l1dI.Append(I1);
        it1.Next();
      }
      else
        it1.Next();
    }
  }
  LI.Clear();
  LI.Append(newLI);
  n1d = l1dI.Extent();
  return n1d;
}

Standard_EXPORT void FUN_select3dinterference(
  const int                                                 SIX,
  TopOpeBRepDS_DataStructure&                               BDS,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lF,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l3dF,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lFE,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lFEresi,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l3dFE,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l3dFEresi,
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l2dFE)

{
  const TopoDS_Edge& E    = TopoDS::Edge(BDS.Shape(SIX));
  bool               isdg = BRep_Tool::Degenerated(E);
  if (isdg)
    return;

  l3dF.Clear();
  l3dFE.Clear();

  ::FUN_select3dI(SIX, BDS, lFE, lFEresi, l3dFE);
  ::FUN_select3dISEsameISF(lFE, l3dFE, l3dFEresi, lF, l3dF);
  FUN_select2dI(SIX, BDS, TopAbs_FACE, lFE, l2dFE);
}
