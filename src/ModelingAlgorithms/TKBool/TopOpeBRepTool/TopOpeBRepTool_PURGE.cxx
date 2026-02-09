#include <TopOpeBRepTool.hpp>
#include <TopOpeBRepTool_TOOL.hpp>
#include <TopOpeBRepTool_CORRISO.hpp>
#include <TopOpeBRepTool_C2DF.hpp>
#include <gp_Pnt2d.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>

#include <TopExp_Explorer.hpp>
#include <BRep_Builder.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <Standard_Failure.hpp>
#include <TopOpeBRepTool_PURGE.hpp>

#ifdef OCCT_DEBUG

Standard_EXPORT void debcorrUV() {};
extern bool          TopOpeBRepTool_GettracePURGE();
extern bool          TopOpeBRepTool_GettraceCORRISO();
#endif

#define SPLITEDGE (0)
#define INCREASE (1)
#define DECREASE (-1)

#define M_FORWARD(sta) (sta == TopAbs_FORWARD)
#define M_REVERSED(sta) (sta == TopAbs_REVERSED)
#define M_INTERNAL(sta) (sta == TopAbs_INTERNAL)
#define M_EXTERNAL(sta) (sta == TopAbs_EXTERNAL)

static void FUN_addtomap(
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>& map,
  const TopoDS_Shape&                                                                         key,
  const TopoDS_Shape&                                                                         item)
{
  if (map.IsBound(key))
    map.ChangeFind(key).Append(item);
  else
  {
    NCollection_List<TopoDS_Shape> los;
    los.Append(item);
    map.Bind(key, los);
  }
}

static bool FUN_getv(const TopAbs_Orientation& orivine, const TopoDS_Shape& e, TopoDS_Shape& v)
{
  v.Nullify();

  TopAbs_Orientation oe     = e.Orientation();
  bool               isnonO = M_INTERNAL(oe) || M_EXTERNAL(oe);
  TopoDS_Shape       eO;
  if (isnonO)
  {
    eO = e.Oriented(TopAbs_FORWARD);
  }
  else
  {
    eO = e;
  }
  TopExp_Explorer exv(eO, TopAbs_VERTEX);
  for (; exv.More(); exv.Next())
  {
    const TopoDS_Shape& vcur = exv.Current();
    if (vcur.Orientation() == orivine)
    {
      v = vcur;
      return true;
    }
  }
  return false;
}

Standard_EXPORT bool FUN_tool_ClosedW(const TopoDS_Wire& W)
{

  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    mapvFine, mapvRine, mapvIine;

  TopExp_Explorer exe(W, TopAbs_EDGE);
  for (; exe.More(); exe.Next())
  {
    const TopoDS_Shape& e      = exe.Current();
    TopAbs_Orientation  oe     = e.Orientation();
    bool                isnonO = M_INTERNAL(oe) || M_EXTERNAL(oe);
    TopoDS_Shape        eO;
    if (isnonO)
    {
      eO = e.Oriented(TopAbs_FORWARD);
    }
    else
    {
      eO = e;
    }

    TopExp_Explorer exv(eO, TopAbs_VERTEX);
    for (; exv.More(); exv.Next())
    {
      const TopoDS_Shape& v    = exv.Current();
      TopAbs_Orientation  oriv = v.Orientation();
      if (M_FORWARD(oriv))
        FUN_addtomap(mapvFine, v, e);
      if (M_REVERSED(oriv))
        FUN_addtomap(mapvRine, v, e);
      if (M_INTERNAL(oriv))
        FUN_addtomap(mapvIine, v, e);
    }
  }

  if (mapvFine.Extent() == 0)
    return false;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapvok;

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapvonlyFine;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator itvFine(mapvFine);
  for (; itvFine.More(); itvFine.Next())
  {
    const TopoDS_Shape& vFine = itvFine.Key();
    bool                vIine = mapvIine.IsBound(vFine);
    if (vIine)
    {
      mapvok.Add(vFine);
      continue;
    }
    bool vRine = mapvRine.IsBound(vFine);
    if (vRine)
    {
      mapvok.Add(vFine);
      continue;
    }
    mapvonlyFine.Add(vFine);
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> mapvonlyRine;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>::
    Iterator itvRine(mapvRine);
  for (; itvRine.More(); itvRine.Next())
  {
    const TopoDS_Shape& vRine = itvRine.Key();
    bool                vok   = mapvok.Contains(vRine);
    if (vok)
      continue;
    bool vIine = mapvIine.IsBound(vRine);
    if (vIine)
    {
      mapvok.Add(vRine);
      continue;
    }
    mapvonlyRine.Add(vRine);
  }

  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>::Iterator itvonlyFRine;
  int                                                              nmap = 0;
  while (nmap <= 2)
  {
    nmap++;
    bool vFine = (nmap == 1);
    if (vFine)
      itvonlyFRine.Initialize(mapvonlyFine);
    else
      itvonlyFRine.Initialize(mapvonlyRine);

    for (; itvonlyFRine.More(); itvonlyFRine.Next())
    {
      const TopoDS_Shape&            vtocheck = itvonlyFRine.Key();
      NCollection_List<TopoDS_Shape> edsvFRine;
      if (vFine)
        edsvFRine = mapvFine.Find(vtocheck);
      else
        edsvFRine = mapvRine.Find(vtocheck);

      if (edsvFRine.Extent() > 1)
        return false;
      const TopoDS_Shape& e = edsvFRine.First();

      TopAbs_Orientation ovori = vFine ? TopAbs_REVERSED : TopAbs_FORWARD;
      TopoDS_Shape       ov;
      bool               ovfound = FUN_getv(ovori, e, ov);
      if (!ovfound)
        return false;

      TopAbs_Orientation oe = e.Orientation();
      if (M_FORWARD(oe) || M_REVERSED(oe))
        return false;
      if (!mapvok.Contains(ov))
        return false;

      bool ovIine = mapvIine.IsBound(ov);
      if (ovIine)
        continue;
      bool ovFine = mapvRine.IsBound(ov);
      if (!ovFine)
        return false;
      bool ovRine = mapvRine.IsBound(ov);
      if (!ovRine)
        return false;

      const NCollection_List<TopoDS_Shape>& edsovFine = mapvFine.Find(ov);
      const NCollection_List<TopoDS_Shape>& edsovRine = mapvRine.Find(ov);
      if (edsovFine.Extent() > 1)
        continue;
      if (edsovRine.Extent() > 1)
        continue;
      if (edsovFine.First().IsEqual(e))
        return false;
      if (edsovRine.First().IsEqual(e))
        return false;
    }
  }
  return true;
}

bool TopOpeBRepTool::PurgeClosingEdges(
  const TopoDS_Face& Fin,
  const TopoDS_Face& FF,

  const NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>&,
  NCollection_IndexedMap<TopoDS_Shape>& MshNOK)
{

#ifdef OCCT_DEBUG
  bool trc = TopOpeBRepTool_GettracePURGE();
  if (trc)
    std::cout << "\n* PurgeClosingEdges:\n\n";
#endif
  TopOpeBRepTool_CORRISO CORRISO(Fin);
  double                 tolF = BRep_Tool::Tolerance(Fin);
  double                 uperiod;
  bool                   uclosed = CORRISO.Refclosed(1, uperiod);
  double                 vperiod;
  bool                   vclosed = CORRISO.Refclosed(2, vperiod);
  if (!uclosed && !vclosed)
    return false;
  bool   inU  = uclosed;
  double xmin = inU ? (CORRISO.GASref().FirstUParameter()) : (CORRISO.GASref().FirstVParameter());
  double xper = inU ? uperiod : vperiod;
  double tolx = inU ? (CORRISO.Tol(1, tolF)) : (CORRISO.Tol(2, tolF));

  TopExp_Explorer exw(FF, TopAbs_WIRE);
  for (; exw.More(); exw.Next())
  {
    const TopoDS_Shape& W = exw.Current();

    CORRISO.Init(W);
    bool ok = CORRISO.UVClosed();
    if (ok)
      continue;

    NCollection_List<TopoDS_Shape>           cEds;
    NCollection_List<TopoDS_Shape>::Iterator ite(CORRISO.Eds());
    for (; ite.More(); ite.Next())
    {
      const TopoDS_Edge& E       = TopoDS::Edge(ite.Value());
      bool               closing = BRep_Tool::IsClosed(E, Fin);
      if (!closing)
      {
        TopOpeBRepTool_C2DF C2DF;
        bool                isb = CORRISO.UVRep(E, C2DF);
        if (!isb)
          return false;
        bool onclo = TopOpeBRepTool_TOOL::IsonCLO(C2DF, inU, xmin, xper, tolx);
        if (onclo)
          closing = true;
      }
      if (closing)
        cEds.Append(E);
    }
    int  ncE     = cEds.Extent();
    bool nopurge = (ncE <= 1);
    if (nopurge)
      return true;

    NCollection_List<TopoDS_Shape> fyEds;
    bool                           topurge = CORRISO.PurgeFyClosingE(cEds, fyEds);
    if (topurge)
    {
      NCollection_List<TopoDS_Shape>::Iterator it(fyEds);
      for (; it.More(); it.Next())
        MshNOK.Add(it.Value());
      MshNOK.Add(W);
      MshNOK.Add(FF);
    }

#ifdef OCCT_DEBUG
    if (trc && topurge)
      std::cout << "found FAULTY edge = ed" << std::endl;
#endif
  }
  return true;
}

bool TopOpeBRepTool::PurgeClosingEdges(
  const TopoDS_Face&                                                     Fin,
  const NCollection_List<TopoDS_Shape>&                                  LOF,
  const NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>& MWisOld,
  NCollection_IndexedMap<TopoDS_Shape>&                                  MshNOK)
{
  bool uvclosed = FUN_tool_closedS(Fin);
  if (!uvclosed)
    return true;

  NCollection_List<TopoDS_Shape>::Iterator it(LOF);
  for (; it.More(); it.Next())
  {
    const TopoDS_Face& FF = TopoDS::Face(it.Value());
    bool               ok = TopOpeBRepTool::PurgeClosingEdges(Fin, FF, MWisOld, MshNOK);
    if (!ok)
      return false;
  }
  return true;
}

static bool FUN_connexX(const bool                              onU,
                        TopOpeBRepTool_CORRISO&                 CORRISO,
                        const NCollection_List<TopoDS_Shape>&   EdstoCheck,
                        NCollection_DataMap<TopoDS_Shape, int>& fyEds)

{
  fyEds.Clear();
  double tolF  = BRep_Tool::Tolerance(CORRISO.Fref());
  int    Index = onU ? 1 : 2;
  double xperiod;
  bool   xclosed = CORRISO.Refclosed(Index, xperiod);
  if (!xclosed)
    return false;
  double xtol = CORRISO.Tol(Index, tolF);

  TopoDS_Shape fy;
  int          Ify   = 0;
  bool         hasfy = CORRISO.EdgeWithFaultyUV(EdstoCheck, 2, fy, Ify);
  if (!hasfy)
    return false;
  TopOpeBRepTool_C2DF C2DF;
  bool                isb = CORRISO.UVRep(TopoDS::Edge(fy), C2DF);
  if (!isb)
    return false;

  NCollection_Array1<TopoDS_Shape> vfy(1, 2);
  TopOpeBRepTool_TOOL::Vertices(TopoDS::Edge(fy), vfy);
  for (int ii = 1; ii <= 2; ii++)
  {

    const TopoDS_Vertex& vff    = TopoDS::Vertex(vfy(ii));
    double               parvff = TopOpeBRepTool_TOOL::ParE(ii, TopoDS::Edge(fy));
    gp_Pnt2d             uvff   = TopOpeBRepTool_TOOL::UVF(parvff, C2DF);

    NCollection_List<TopoDS_Shape> loe;
    isb = CORRISO.Connexity(vff, loe);
    if (!isb)
      return false;

    NCollection_List<TopoDS_Shape>::Iterator ite(loe);
    for (; ite.More(); ite.Next())
    {
      const TopoDS_Edge&               ee = TopoDS::Edge(ite.Value());
      NCollection_Array1<TopoDS_Shape> vee(1, 2);
      TopOpeBRepTool_TOOL::Vertices(ee, vee);
      for (int ive = 1; ive <= 2; ive++)
      {

        const TopoDS_Vertex& ve    = TopoDS::Vertex(vee(ive));
        bool                 samev = ve.IsSame(vff);
        if (!samev)
          continue;
        if (ive == ii)
          continue;
        TopOpeBRepTool_C2DF C2DFe;
        isb = CORRISO.UVRep(ee, C2DFe);
        if (!isb)
          return false;
        double   paree = TopOpeBRepTool_TOOL::ParE(ive, ee);
        gp_Pnt2d uve   = TopOpeBRepTool_TOOL::UVF(paree, C2DFe);

        double dxx   = onU ? uve.X() - uvff.X() : uve.Y() - uvff.Y();
        bool   isper = (std::abs(xperiod - std::abs(dxx)) < xtol);
        if (!isper)
          continue;

        int recadre = (dxx > 0) ? INCREASE : DECREASE;
        fyEds.Bind(fy, recadre);
      }
    }
  }
  return !fyEds.IsEmpty();
}

bool TopOpeBRepTool::CorrectONUVISO(const TopoDS_Face& Fin, TopoDS_Face& Fsp)

{
#ifdef OCCT_DEBUG
  bool trc = TopOpeBRepTool_GettraceCORRISO();
  if (trc)
    std::cout << "\n####    CorrectONUVISO    ####\n\n";
  debcorrUV();
#endif

  double tolF = BRep_Tool::Tolerance(Fin);

  TopOpeBRepTool_CORRISO CORRISO(Fin);
  double                 uperiod, vperiod;
  bool                   uclosed = CORRISO.Refclosed(1, uperiod);
  bool                   vclosed = CORRISO.Refclosed(2, vperiod);
  if (!uclosed && !vclosed)
    return false;

  CORRISO.Init(Fsp);
  bool ok = CORRISO.UVClosed();
  if (ok)
    return true;

  int i;
  for (i = 1; i <= 2; i++)
  {
    bool                                   onU     = i == 1;
    const NCollection_List<TopoDS_Shape>&  Tocheck = CORRISO.Eds();
    NCollection_DataMap<TopoDS_Shape, int> fyEds;
    ok = ::FUN_connexX(onU, CORRISO, Tocheck, fyEds);
    if (!ok)
      continue;
    ok = CORRISO.TrslUV(onU, fyEds);
    if (!ok)
      continue;
    ok = CORRISO.UVClosed();
    if (!ok)
      continue;
    ok = CORRISO.GetnewS(Fsp);
    return ok;
  }

  for (i = 1; i <= 2; i++)
  {
    bool   onU     = (i == 1);
    double xper    = 0.;
    bool   xclosed = CORRISO.Refclosed(i, xper);
    if (!xclosed)
      continue;
    double tolx = CORRISO.Tol(i, tolF);
    tolx *= 1.e2;
    NCollection_DataMap<TopoDS_Shape, int> FyEds;
    bool hasfy = CORRISO.EdgesOUTofBoundsUV(CORRISO.Eds(), onU, tolx, FyEds);
    if (!hasfy)
      continue;
    ok = CORRISO.TrslUV(onU, FyEds);
    if (!ok)
      return false;
    ok = CORRISO.UVClosed();
    if (!ok)
      continue;
    ok = CORRISO.GetnewS(Fsp);
    return ok;
  }
  return false;
}

bool TopOpeBRepTool::MakeFaces(const TopoDS_Face&                          Fin,
                               const NCollection_List<TopoDS_Shape>&       LOF,
                               const NCollection_IndexedMap<TopoDS_Shape>& MshNOK,
                               NCollection_List<TopoDS_Shape>&             LOFF)
{

  BRep_Builder BB;
  LOFF.Clear();
  NCollection_List<TopoDS_Shape>::Iterator it(LOF);
  for (; it.More(); it.Next())
  {
    const TopoDS_Face& FF    = TopoDS::Face(it.Value());
    bool               valid = !MshNOK.Contains(FF);
    if (valid)
    {
      LOFF.Append(FF);
      continue;
    }

    TopoDS_Shape aLocalShape = Fin.EmptyCopied();
    TopoDS_Face  newFace     = TopoDS::Face(aLocalShape);

    TopExp_Explorer exw(FF, TopAbs_WIRE);

    for (; exw.More(); exw.Next())
    {
      const TopoDS_Wire& W = TopoDS::Wire(exw.Current());
      valid                = !MshNOK.Contains(W);

      if (valid)
      {
        BB.Add(newFace, W);
        continue;
      }

      TopoDS_Wire newWire;
      BB.MakeWire(newWire);
      TopExp_Explorer exe(W, TopAbs_EDGE);
      int             ne = 0;
      for (; exe.More(); exe.Next())
      {
        const TopoDS_Edge& E = TopoDS::Edge(exe.Current());
        valid                = !MshNOK.Contains(E);
        if (!valid)
          continue;

        BB.Add(newWire, E);
        ne++;
      }
      if (ne == 0)
        continue;
      bool closed = FUN_tool_ClosedW(newWire);

      newWire.Closed(closed);
      BB.Add(newFace, newWire);
    }
    LOFF.Append(newFace);
  }
  return true;
}
