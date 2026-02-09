#include <TopOpeBRepDS_EdgeInterferenceTool.hpp>
#include <TopOpeBRepDS_TKI.hpp>
#include <TopoDS.hpp>
#include <TopExp_Explorer.hpp>
#include <TopExp.hpp>
#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>
#include <Geom_Curve.hpp>
#include <TopOpeBRepDS_define.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepDS_connex.hpp>
#include <TopOpeBRepTool_SC.hpp>

#define MDShcpi occ::handle<TopOpeBRepDS_CurvePointInterference>
#define MAKECPI(IJKLM) (occ::down_cast<TopOpeBRepDS_CurvePointInterference>(IJKLM))

Standard_EXPORT bool FUN_vertexofedge

  (const TopoDS_Shape& V, const TopoDS_Shape& E)
{
  bool            isv = false;
  TopExp_Explorer ex;
  for (ex.Init(E, TopAbs_VERTEX); ex.More(); ex.Next())

    if (ex.Current().IsSame(V))
    {
      isv = true;
      break;
    }
  return isv;
}

static bool FUN_keepEinterference

  (const TopOpeBRepDS_DataStructure&             DS,
   const occ::handle<TopOpeBRepDS_Interference>& I,
   const TopoDS_Shape&                           E)
{
  TopOpeBRepDS_Kind GT1, ST1;
  int               G1, S1;
  FDS_data(I, GT1, G1, ST1, S1);

  bool res = true;
  if (I->IsKind(STANDARD_TYPE(TopOpeBRepDS_EdgeVertexInterference)))
  {

    bool k1 = !::FUN_interfhassupport(DS, I, E);
    res     = k1;

    const TopOpeBRepDS_Transition& T    = I->Transition();
    TopAbs_ShapeEnum               shab = T.ShapeBefore(), shaa = T.ShapeAfter();
    TopAbs_State                   stab = T.Before(), staa = T.After();
    bool                           k2 = ((shab != TopAbs_EDGE) || (stab != TopAbs_ON))
              && ((shaa != TopAbs_EDGE) || (staa != TopAbs_ON));
    res = res && k2;

    const TopoDS_Shape& VG = DS.Shape(I->Geometry());

    {
      TopoDS_Vertex Vf, Vr;
      TopExp::Vertices(TopoDS::Edge(E), Vf, Vr);
      NCollection_List<TopoDS_Shape>::Iterator it(DS.ShapeSameDomain(VG));
      for (; it.More(); it.Next())
      {
        const TopoDS_Shape& Vsd = it.Value();
        if (Vsd.IsSame(Vf))
        {
          break;
        }
        else if (Vsd.IsSame(Vr))
        {
          break;
        }
      }
    }
  }

  else if (I->IsKind(STANDARD_TYPE(TopOpeBRepDS_CurvePointInterference)))
  {
    occ::handle<TopOpeBRepDS_CurvePointInterference> aCPI =
      occ::down_cast<TopOpeBRepDS_CurvePointInterference>(I);

    double eps = Precision::PConfusion();
    double par = aCPI->Parameter();
    double f, l;
    BRep_Tool::Range(TopoDS::Edge(E), f, l);
    if (std::abs(par - f) < eps || std::abs(par - l) < eps)
      res = false;
  }

  return res;
}

Standard_EXPORT int FUN_unkeepEinterferences

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   const TopOpeBRepDS_DataStructure&                         BDS,
   const int                                                 SIX)
{

  const TopoDS_Shape& E = BDS.Shape(SIX);
  bool                isEd;
  isEd = BRep_Tool::Degenerated(TopoDS::Edge(E));

  if (isEd)
  {
    return LI.Extent();
  }

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(LI);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference>& I1 = it1.ChangeValue();
    bool                                    k1 = ::FUN_keepEinterference(BDS, I1, E);
    if (!k1)
    {
      LI.Remove(it1);
      continue;
    }
    else
    {
      it1.Next();
    }
  }
  int n = LI.Extent();
  return n;
}

Standard_EXPORT void FUN_unkeepEsymetrictransitions

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   const TopOpeBRepDS_DataStructure&                         BDS,
   const int                                                 SIX)
{
  const TopoDS_Shape& E = BDS.Shape(SIX);

  bool isEd;
  isEd = BRep_Tool::Degenerated(TopoDS::Edge(E));

  if (isEd)
    return;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;

  it1.Initialize(LI);
  while (it1.More())
  {
    bool                                    it1toremove = false;
    occ::handle<TopOpeBRepDS_Interference>& I1          = it1.ChangeValue();
    TopOpeBRepDS_Kind                       GT1, ST1;
    int                                     G1, S1;
    FDS_data(I1, GT1, G1, ST1, S1);
    TopAbs_ShapeEnum tsb1, tsa1;
    int              isb1, isa1;
    ::FDS_Tdata(I1, tsb1, isb1, tsa1, isa1);
    const TopOpeBRepDS_Transition T1 = I1->Transition();

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it2(it1);
    it2.Next();
    while (it2.More())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I2 = it2.Value();
      TopOpeBRepDS_Kind                             GT2, ST2;
      int                                           G2, S2;
      FDS_data(I2, GT2, G2, ST2, S2);
      TopAbs_ShapeEnum tsb2, tsa2;
      int              isb2, isa2;
      ::FDS_Tdata(I2, tsb2, isb2, tsa2, isa2);
      const TopOpeBRepDS_Transition T2    = I2->Transition();
      bool                          idGS  = (GT2 == GT1 && G2 == G1 && ST2 == ST1 && S2 == S1);
      bool                          idiba = (isb1 == isb2 && isa1 == isa2);
      bool                          cond  = idGS;
      cond                                = cond && idiba;

      if (cond)
      {
        bool idshape   = ::FUN_transitionSHAPEEQUAL(T1, T2);
        bool idstate   = ::FUN_transitionSTATEEQUAL(T1, T2);
        bool newV      = true;
        bool oppostate = false;

        if (newV)
        {

#define M_OUTIN(st1, st2) ((st1 == TopAbs_OUT) && (st2 == TopAbs_IN))
          TopAbs_State t1b = T1.Before(), t2b = T2.Before();
          TopAbs_State t1a = T1.After(), t2a = T2.After();
          oppostate = M_OUTIN(t1b, t2b) || M_OUTIN(t2b, t1b);
          oppostate = oppostate && (M_OUTIN(t1a, t2a) || M_OUTIN(t2a, t1a));
        }

        bool sym;
        if (newV)
          sym = idshape && oppostate;
        else
          sym = idshape && !idstate;

        if (sym)
        {
          LI.Remove(it2);
          it1toremove = true;
        }
        else
          it2.Next();
      }
      else
        it2.Next();
    }
    if (it1toremove)
    {
      LI.Remove(it1);
    }
    else
    {
      it1.Next();
    }
  }
}

Standard_EXPORT void FUN_orderFFsamedomain

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   const occ::handle<TopOpeBRepDS_HDataStructure>&           HDS,
   const int)
{
  TopOpeBRepDS_DataStructure&                              BDS = HDS->ChangeDS();
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LIffsd, LIother;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;

  it1.Initialize(LI);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference>& I1 = it1.ChangeValue();
    TopOpeBRepDS_Kind                       GT1, ST1;
    int                                     G1, S1;
    FDS_data(I1, GT1, G1, ST1, S1);
    TopAbs_ShapeEnum tsb1, tsa1;
    int              isb1, isa1;
    FDS_Tdata(I1, tsb1, isb1, tsa1, isa1);

    bool ffsd = false;
    if (tsb1 == TopAbs_FACE && tsa1 == TopAbs_FACE)
    {

      const TopoDS_Shape& fb    = BDS.Shape(isb1);
      const TopoDS_Shape& fa    = BDS.Shape(isa1);
      bool                ffsd1 = HDS->HasSameDomain(fb);
      bool                ffsd2 = HDS->HasSameDomain(fa);
      ffsd                      = ffsd1 && ffsd2;
    }

    if (ffsd)
      LIffsd.Append(I1);
    else
      LIother.Append(I1);

    LI.Remove(it1);
  }

  LI.Clear();
  LI.Append(LIffsd);
  LI.Append(LIother);
}

Standard_EXPORT void FUN_orderSTATETRANSonG

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   const occ::handle<TopOpeBRepDS_HDataStructure>&,
   const int)
{

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>           L1, L2;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;

  it1.Initialize(LI);
  while (it1.More())
  {
    occ::handle<TopOpeBRepDS_Interference>& I1 = it1.ChangeValue();
    TopOpeBRepDS_Kind                       GT1, ST1;
    int                                     G1, S1;
    TopAbs_ShapeEnum                        tsb1, tsa1;
    int                                     isb1, isa1;
    FDS_Idata(I1, tsb1, isb1, tsa1, isa1, GT1, G1, ST1, S1);
    const TopOpeBRepDS_Transition& T1    = I1->Transition();
    TopAbs_State                   stab1 = T1.Before();
    TopAbs_State                   staa1 = T1.After();

    bool steq = (tsb1 == tsa1 && isb1 == isa1 && stab1 == staa1);
    if (steq)
      L1.Append(I1);
    else
      L2.Append(I1);

    it1.Next();
  }

  LI.Clear();
  LI.Append(L1);
  LI.Append(L2);
}

Standard_EXPORT void FUN_orderSTATETRANS

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   const occ::handle<TopOpeBRepDS_HDataStructure>&           HDS,
   const int                                                 SIX)
{
  TopOpeBRepDS_TKI tki;
  tki.FillOnGeometry(LI);
  tki.Init();
  for (; tki.More(); tki.Next())
  {
    TopOpeBRepDS_Kind                                         K;
    int                                                       G;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.ChangeValue(K, G);
    ::FUN_orderSTATETRANSonG(loi, HDS, SIX);
  }

  LI.Clear();
  tki.Init();
  for (; tki.More(); tki.Next())
  {
    TopOpeBRepDS_Kind                                         K;
    int                                                       G;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.ChangeValue(K, G);
    LI.Append(loi);
  }
}

Standard_EXPORT void FUN_resolveEUNKNOWN

  (NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
   TopOpeBRepDS_DataStructure&                               BDS,
   const int                                                 SIX)
{
  const TopoDS_Shape&                                                E = BDS.Shape(SIX);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1;

  const TopoDS_Edge& EE = TopoDS::Edge(E);
  double             fE, lE;
  BRep_Tool::Range(EE, fE, lE);

  for (it1.Initialize(LI); it1.More(); it1.Next())
  {
    occ::handle<TopOpeBRepDS_Interference>& I1    = it1.ChangeValue();
    const TopOpeBRepDS_Transition&          T1    = I1->Transition();
    bool                                    isunk = T1.IsUnknown();
    if (!isunk)
      continue;

    TopOpeBRepDS_Kind GT1, ST1;
    int               G1, S1;
    TopAbs_ShapeEnum  tsb1, tsa1;
    int               isb1, isa1;
    FDS_Idata(I1, tsb1, isb1, tsa1, isa1, GT1, G1, ST1, S1);
    bool idt  = (tsb1 == TopAbs_FACE && tsa1 == TopAbs_FACE && GT1 == TopOpeBRepDS_POINT
                && ST1 == TopOpeBRepDS_FACE);
    bool idi  = (isb1 == S1 && isa1 == S1);
    bool etgf = idt && idi;
    if (!etgf)
      continue;

    occ::handle<TopOpeBRepDS_CurvePointInterference> cpi = MAKECPI(I1);
    if (cpi.IsNull())
      continue;

    double                  bid;
    occ::handle<Geom_Curve> CE = BRep_Tool::Curve(EE, bid, bid);
    if (CE.IsNull())
      continue;

    double parcpi = cpi->Parameter();
    double ttb    = 0.8;
    double parb   = (1 - ttb) * fE + ttb * parcpi;
    double tta    = 0.2;
    double para   = (1 - tta) * parcpi + tta * lE;
    gp_Pnt Pb;
    CE->D0(parb, Pb);
    gp_Pnt Pa;
    CE->D0(para, Pa);

    BRep_Builder       BB;
    const TopoDS_Face& FS = TopoDS::Face(BDS.Shape(S1));
    TopoDS_Shell       sh;
    BB.MakeShell(sh);
    TopoDS_Solid so;
    BB.MakeSolid(so);
    BB.Add(sh, FS);
    BB.Add(so, sh);
    TopOpeBRepTool_ShapeClassifier& PSC = FSC_GetPSC(so);
    PSC.StateP3DReference(Pb);
    TopAbs_State stateb = PSC.State();
    PSC.StateP3DReference(Pa);
    TopAbs_State statea = PSC.State();
    if (stateb == TopAbs_UNKNOWN || statea == TopAbs_UNKNOWN)
      continue;

    TopOpeBRepDS_Transition& newT1 = I1->ChangeTransition();
    newT1.Set(stateb, statea, tsb1, tsa1);
  }
  FUN_unkeepUNKNOWN(LI, BDS, SIX);
}

Standard_EXPORT void FUN_purgeDSonSE(const occ::handle<TopOpeBRepDS_HDataStructure>&           HDS,
                                     const int                                                 EIX,
                                     NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI)

{

  TopOpeBRepDS_DataStructure& BDS  = HDS->ChangeDS();
  const TopoDS_Edge&          SE   = TopoDS::Edge(BDS.Shape(EIX));
  int                         rkSE = BDS.AncestorRank(SE);
  bool                        isse = BDS.IsSectionEdge(SE);
  if (!isse)
    return;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> fsdmFancSE;

  const NCollection_List<TopoDS_Shape>& lFancSE = FDSCNX_EdgeConnexitySameShape(SE, HDS);
  for (NCollection_List<TopoDS_Shape>::Iterator itf(lFancSE); itf.More(); itf.Next())
  {
    const NCollection_List<TopoDS_Shape>& fsdm = BDS.ShapeSameDomain(itf.Value());
    for (NCollection_List<TopoDS_Shape>::Iterator itsdm(fsdm); itsdm.More(); itsdm.Next())
    {
      const TopoDS_Shape& sdmf  = itsdm.Value();
      int                 sdmrk = BDS.AncestorRank(sdmf);
      if (sdmrk == rkSE)
        continue;
      fsdmFancSE.Add(sdmf);
    }
  }
  if (fsdmFancSE.IsEmpty())
    return;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> newLI;

  TopOpeBRepDS_TKI tki;
  tki.FillOnGeometry(LI);
  for (tki.Init(); tki.More(); tki.Next())
  {

    TopOpeBRepDS_Kind                                         Kcur;
    int                                                       Gcur;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& loi = tki.ChangeValue(Kcur, Gcur);
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it(loi);

    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LIface;
    for (; it.More(); it.Next())
    {
      const occ::handle<TopOpeBRepDS_Interference>& I = it.Value();
      TopOpeBRepDS_Kind                             GT, ST;
      int                                           G, S;
      FDS_data(I, GT, G, ST, S);
      TopAbs_ShapeEnum tsb, tsa;
      int              isb, isa;
      FDS_Tdata(I, tsb, isb, tsa, isa);

      if (tsb != TopAbs_FACE)
      {
        newLI.Append(I);
        continue;
      }
      if (ST != TopOpeBRepDS_FACE)
      {
        newLI.Append(I);
        continue;
      }

      const TopoDS_Shape& f       = BDS.Shape(isb);
      bool                isbound = fsdmFancSE.Contains(f);
      if (isbound)
        LIface.Append(I);
      else
        newLI.Append(I);
    }
  }

  LI.Clear();
  LI.Append(newLI);
}
