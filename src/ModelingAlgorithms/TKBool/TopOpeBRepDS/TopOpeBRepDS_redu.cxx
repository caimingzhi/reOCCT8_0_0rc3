#include <TopOpeBRepTool_GEOMETRY.hpp>

#include <TopOpeBRepTool_PROJECT.hpp>

#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_makeTransition.hpp>

#include <TopOpeBRepDS_ProcessInterferencesTool.hpp>

#include <TopoDS.hpp>
#include <BRep_Tool.hpp>

#define M_FORWARD(st) (st == TopAbs_FORWARD)
#define M_UNKNOWN(st) (st == TopAbs_UNKNOWN)
#define M_REVERSED(st) (st == TopAbs_REVERSED)
#define M_INTERNAL(st) (st == TopAbs_INTERNAL)
#define M_EXTERNAL(st) (st == TopAbs_EXTERNAL)

Standard_EXPORT void FUN_scanloi(const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lI,
                                 NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lFOR,
                                 int&                                                      FOR,
                                 NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lREV,
                                 int&                                                      REV,
                                 NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lINT,
                                 int&                                                      INT,
                                 NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& lEXT,
                                 int&                                                      EXT)
{
  lFOR.Clear();
  lREV.Clear();
  lINT.Clear();
  lEXT.Clear();
  FDS_assign(lI, lEXT);
  FOR = FUN_selectTRAORIinterference(lEXT, TopAbs_FORWARD, lFOR);
  REV = FUN_selectTRAORIinterference(lEXT, TopAbs_REVERSED, lREV);
  INT = FUN_selectTRAORIinterference(lEXT, TopAbs_INTERNAL, lINT);
  EXT = lEXT.Extent();
}

Standard_EXPORT bool FUN_ds_redu2d1d(
  const TopOpeBRepDS_DataStructure&                               BDS,
  const int                                                       ISE,
  const occ::handle<TopOpeBRepDS_Interference>&                   I2d,
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& l1d,
  TopOpeBRepDS_Transition&                                        newT2d)

{
  TopAbs_ShapeEnum  SB2, SA2;
  int               IB2, IA2;
  TopOpeBRepDS_Kind GT2, ST2;
  int               G2, S2;
  FDS_Idata(I2d, SB2, IB2, SA2, IA2, GT2, G2, ST2, S2);
  const TopOpeBRepDS_Transition T2d = I2d->Transition();
  TopAbs_Orientation            O2  = T2d.Orientation(TopAbs_IN);
  newT2d.Index(IB2);
  newT2d.Set(O2);
  bool ok2 = (IB2 == IA2) && (SB2 == TopAbs_FACE) && (GT2 == TopOpeBRepDS_VERTEX);
  if (!ok2)
    return false;

  const TopoDS_Edge& SE = TopoDS::Edge(BDS.Shape(ISE));

  const TopoDS_Face& F    = TopoDS::Face(BDS.Shape(IB2));
  double             tolF = BRep_Tool::Tolerance(F) * 1.e2;
  const TopoDS_Edge& E    = TopoDS::Edge(BDS.Shape(S2));
  double             tolE = BRep_Tool::Tolerance(E) * 1.e2;

  bool EclosingF = FUN_tool_IsClosingE(E, F, F);
  if (EclosingF)
  {
    TopAbs_State stb = T2d.Before(), sta = T2d.After();
    if (stb != sta)
    {
      double pbef = 0, paft = 0, factor = 1.e-4;
      double parSE = FDS_Parameter(I2d);
      double parE;
      bool   ok = FUN_tool_parE(SE, parSE, E, parE, tolE);
      if (!ok)
        return false;
      gp_Pnt2d uv;
      ok = FUN_tool_paronEF(E, parE, F, uv, tolF);
      if (!ok)
        return false;

      TopOpeBRepTool_makeTransition MKT;
      TopAbs_State                  stb1 = TopAbs_UNKNOWN, sta1 = TopAbs_UNKNOWN;
      ok = MKT.Initialize(SE, pbef, paft, parSE, F, uv, factor);
      if (ok)
        ok = MKT.SetRest(E, parE);
      if (ok)
        ok = MKT.MkTonE(stb1, sta1);
      if (ok)
      {
        newT2d.Before(stb1);
        newT2d.After(sta1);
      }
      return ok;
    }
    return false;
  }

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator it1(l1d);
  bool beforeIN1d = false, afterIN1d = false;

  for (; it1.More(); it1.Next())
  {
    const occ::handle<TopOpeBRepDS_Interference>& I1d = it1.Value();
    TopAbs_ShapeEnum                              SB1, SA1;
    int                                           IB1, IA1;
    TopOpeBRepDS_Kind                             GT1, ST1;
    int                                           G1, S1;
    FDS_Idata(I1d, SB1, IB1, SA1, IA1, GT1, G1, ST1, S1);
    if (IB1 != IA1)
      continue;
    TopAbs_Orientation O1 = I1d->Transition().Orientation(TopAbs_IN);

    const TopoDS_Edge& Esd     = TopoDS::Edge(BDS.Shape(IB1));
    bool               isedgeF = FUN_tool_inS(Esd, F);
    if (!isedgeF)
      continue;

    bool bIN = M_INTERNAL(O1) || M_REVERSED(O1);
    bool aIN = M_INTERNAL(O1) || M_FORWARD(O1);
    if (bIN && aIN)
      return false;
    if (bIN)
      beforeIN1d = true;
    if (aIN)
      afterIN1d = true;
  }

  if (beforeIN1d)
    newT2d.Before(TopAbs_IN);
  if (afterIN1d)
    newT2d.After(TopAbs_IN);
  return true;
}

Standard_EXPORT bool FUN_ds_GetTr(

  const TopOpeBRepDS_DataStructure&,
  const int ISE,

  const int,
  const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LIG,
  TopAbs_State&                                                   stb,
  int&                                                            isb,
  int&                                                            bdim,
  TopAbs_State&                                                   sta,
  int&                                                            isa,
  int&                                                            adim)

{
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> LIGcopy;
  FDS_copy(LIG, LIGcopy);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3d;
  FDS_assign(LIG, LIGcopy);
  FUN_selectSKinterference(LIGcopy, TopOpeBRepDS_FACE, l3d);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l2d;
  FDS_assign(LIG, LIGcopy);
  FUN_ds_hasI2d(ISE, LIGcopy, l2d);
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1d;
  FDS_assign(LIG, LIGcopy);
  FUN_selectTRASHAinterference(LIGcopy, TopAbs_EDGE, l1d);

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1dFOR, l1dREV, l1dINT, l1dEXT;
  int                                                      FOR1d, REV1d, INT1d, EXT1d;
  ::FUN_scanloi(l1d, l1dFOR, FOR1d, l1dREV, REV1d, l1dINT, INT1d, l1dEXT, EXT1d);
  bool beforeIN1d = (REV1d + INT1d > 0);
  bool beforeOU1d = (FOR1d + EXT1d) != 0;
  bool afterIN1d  = (FOR1d + INT1d > 0);
  bool afterOU1d  = (REV1d + EXT1d) != 0;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l2dFOR, l2dREV, l2dINT, l2dEXT;
  int                                                      FOR2d, REV2d, INT2d, EXT2d;
  ::FUN_scanloi(l2d, l2dFOR, FOR2d, l2dREV, REV2d, l2dINT, INT2d, l2dEXT, EXT2d);
  bool beforeIN2d = (REV2d + INT2d > 0);
  bool beforeOU2d = (FOR2d + EXT2d) != 0;
  bool afterIN2d  = (FOR2d + INT2d > 0);
  bool afterOU2d  = (REV2d + EXT2d) != 0;

  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3dFOR, l3dREV, l3dINT, l3dEXT;
  int                                                      FOR3d, REV3d, INT3d, EXT3d;
  ::FUN_scanloi(l3d, l3dFOR, FOR3d, l3dREV, REV3d, l3dINT, INT3d, l3dEXT, EXT3d);
  bool beforeIN3d = (REV3d + INT3d > 0);
  bool beforeOU3d = (FOR3d + EXT3d) != 0;
  bool afterIN3d  = (FOR3d + INT3d > 0);
  bool afterOU3d  = (REV3d + EXT3d) != 0;

  stb  = TopAbs_UNKNOWN;
  isb  = 0;
  bdim = 0;
  if (beforeIN1d)
  {
    stb  = TopAbs_IN;
    bdim = 1;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1INb;
    FDS_copy(l1dREV, l1INb);
    FDS_copy(l1dINT, l1INb);
    isb = l1INb.First()->Transition().IndexBefore();
  }
  else if (beforeIN2d)
  {
    stb  = TopAbs_IN;
    bdim = 2;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l2INb;
    FDS_copy(l2dREV, l2INb);
    FDS_copy(l2dINT, l2INb);
    isb = l2INb.First()->Transition().IndexBefore();
  }
  else if (beforeIN3d)
  {
    stb  = TopAbs_IN;
    bdim = 3;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3INb;
    FDS_copy(l3dREV, l3INb);
    FDS_copy(l3dINT, l3INb);
    isb = l3INb.First()->Transition().IndexBefore();
  }
  else if (beforeOU3d)
  {
    stb  = TopAbs_OUT;
    bdim = 3;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3OUb;
    FDS_copy(l3dFOR, l3OUb);
    FDS_copy(l3dEXT, l3OUb);
    isb = l3OUb.First()->Transition().IndexBefore();
  }
  else if (beforeOU2d)
  {
    stb  = TopAbs_OUT;
    bdim = 2;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l2OUb;
    FDS_copy(l2dFOR, l2OUb);
    FDS_copy(l2dEXT, l2OUb);
    isb = l2OUb.First()->Transition().IndexBefore();
  }
  else if (beforeOU1d)
  {
    stb  = TopAbs_OUT;
    bdim = 1;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1OUb;
    FDS_copy(l1dFOR, l1OUb);
    FDS_copy(l1dEXT, l1OUb);
    isb = l1OUb.First()->Transition().IndexBefore();
  }

  sta  = TopAbs_UNKNOWN;
  isa  = 0;
  adim = 0;
  if (afterIN1d)
  {
    sta  = TopAbs_IN;
    adim = 1;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1INb;
    FDS_copy(l1dFOR, l1INb);
    FDS_copy(l1dINT, l1INb);
    isa = l1INb.First()->Transition().IndexAfter();
  }
  else if (afterIN2d)
  {
    sta  = TopAbs_IN;
    adim = 2;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l2INb;
    FDS_copy(l2dFOR, l2INb);
    FDS_copy(l2dINT, l2INb);
    isa = l2INb.First()->Transition().IndexAfter();
  }
  else if (afterIN3d)
  {
    sta  = TopAbs_IN;
    adim = 3;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3INb;
    FDS_copy(l3dFOR, l3INb);
    FDS_copy(l3dINT, l3INb);
    isa = l3INb.First()->Transition().IndexAfter();
  }
  else if (afterOU3d)
  {
    sta  = TopAbs_OUT;
    adim = 3;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l3OUb;
    FDS_copy(l3dREV, l3OUb);
    FDS_copy(l3dEXT, l3OUb);
    isa = l3OUb.First()->Transition().IndexAfter();
  }
  else if (afterOU2d)
  {
    sta  = TopAbs_OUT;
    adim = 2;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l2OUb;
    FDS_copy(l2dREV, l2OUb);
    FDS_copy(l2dEXT, l2OUb);
    isa = l2OUb.First()->Transition().IndexAfter();
  }
  else if (afterOU1d)
  {
    sta  = TopAbs_OUT;
    adim = 1;
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>> l1OUb;
    FDS_copy(l1dREV, l1OUb);
    FDS_copy(l1dEXT, l1OUb);
    isa = l1OUb.First()->Transition().IndexAfter();
  }
  return true;
}
