#include <BndLib_Add2dCurve.hpp>
#include <BRep_Builder.hpp>
#include <BRep_GCurve.hpp>
#include <BRep_TEdge.hpp>
#include <BRep_Tool.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopOpeBRepTool.hpp>
#include <TopOpeBRepTool_2d.hpp>
#include <TopOpeBRepTool_CORRISO.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <TopoDS_Edge.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopOpeBRepTool_GEOMETRY.hpp>
#include <TopOpeBRepTool_PROJECT.hpp>
#include <TopOpeBRepTool_TOPOLOGY.hpp>
#include <TopOpeBRepTool_PURGE.hpp>
#include <TopOpeBRepTool_TOOL.hpp>
#include <NCollection_Array1.hpp>

#ifdef OCCT_DEBUG
extern bool     TopOpeBRepTool_GettraceCORRISO();
Standard_EXPORT NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> STATIC_PURGE_mapv;
Standard_EXPORT NCollection_IndexedMap<TopoDS_Shape> STATIC_PURGE_mapeds;
extern void                                          FUN_tool_trace(const int Index);
extern void                                          FUN_tool_trace(const gp_Pnt2d p2d);
#endif

static void FUN_RaiseError()
{
#ifdef OCCT_DEBUG

  FUN_REINIT();

#endif
}

static void FUN_Raise()
{
#ifdef OCCT_DEBUG

#endif
}

#define M_FORWARD(sta) (sta == TopAbs_FORWARD)
#define M_REVERSED(sta) (sta == TopAbs_REVERSED)
#define M_INTERNAL(sta) (sta == TopAbs_INTERNAL)
#define M_EXTERNAL(sta) (sta == TopAbs_EXTERNAL)

TopOpeBRepTool_CORRISO::TopOpeBRepTool_CORRISO() = default;

TopOpeBRepTool_CORRISO::TopOpeBRepTool_CORRISO(const TopoDS_Face& Fref)
{
  myFref = Fref;

  FUN_tool_closedS(myFref, myUclosed, myUper, myVclosed, myVper);

  const occ::handle<Geom_Surface>& SU = BRep_Tool::Surface(myFref);
  myGAS                               = GeomAdaptor_Surface(SU);
}

const TopoDS_Face& TopOpeBRepTool_CORRISO::Fref() const
{
  return myFref;
}

const GeomAdaptor_Surface& TopOpeBRepTool_CORRISO::GASref() const
{
  return myGAS;
}

bool TopOpeBRepTool_CORRISO::Refclosed(const int x, double& xperiod) const
{
  if (x == 1)
  {
    xperiod = myUper;
    return myUclosed;
  }
  if (x == 2)
  {
    xperiod = myVper;
    return myVclosed;
  }
  return false;
}

bool TopOpeBRepTool_CORRISO::Init(const TopoDS_Shape& S)
{

  myERep2d.Clear();
  myEds.Clear();
  myVEds.Clear();

  if (S.IsNull())
    return false;
  myS = S;

  TopExp_Explorer ex(S, TopAbs_EDGE);
  for (; ex.More(); ex.Next())
  {
    const TopoDS_Edge& E = TopoDS::Edge(ex.Current());
#ifdef OCCT_DEBUG
    int iE = STATIC_PURGE_mapeds.Add(E);
    (void)iE;
#endif

    myEds.Append(E);

    occ::handle<Geom2d_Curve> PC;
    double                    f, l, tol;
    bool                      hasold = FC2D_HasOldCurveOnSurface(E, myFref, PC);
    PC                               = FC2D_EditableCurveOnSurface(E, myFref, f, l, tol);
    if (!hasold)
      FC2D_AddNewCurveOnSurface(PC, E, myFref, f, l, tol);
    if (PC.IsNull())
      return false;
    TopOpeBRepTool_C2DF C2DF(PC, f, l, tol, myFref);
    myERep2d.Bind(E, C2DF);

    TopExp_Explorer exv(E, TopAbs_VERTEX);
    for (; exv.More(); exv.Next())
    {
      const TopoDS_Vertex& v = TopoDS::Vertex(exv.Current());
#ifdef OCCT_DEBUG
      int aniE = STATIC_PURGE_mapeds.Add(E);
      (void)aniE;
#endif
      bool isb = myVEds.IsBound(v);
      if (isb)
        myVEds.ChangeFind(v).Append(E);
      else
      {
        NCollection_List<TopoDS_Shape> loe;
        loe.Append(E);
        myVEds.Bind(v, loe);
      }
    }
  }
  return true;
}

const TopoDS_Shape& TopOpeBRepTool_CORRISO::S() const
{
  return myS;
}

const NCollection_List<TopoDS_Shape>& TopOpeBRepTool_CORRISO::Eds() const
{
  return myEds;
}

bool TopOpeBRepTool_CORRISO::UVRep(const TopoDS_Edge& E, TopOpeBRepTool_C2DF& C2DF) const
{
  bool isb = myERep2d.IsBound(E);
  if (!isb)
    return false;

  C2DF = myERep2d.Find(E);
  return true;
}

bool TopOpeBRepTool_CORRISO::SetUVRep(const TopoDS_Edge& E, const TopOpeBRepTool_C2DF& C2DF)
{
  bool isb = myERep2d.IsBound(E);
  if (!isb)
    return false;

  myERep2d.ChangeFind(E) = C2DF;
  return true;
}

bool TopOpeBRepTool_CORRISO::Connexity(const TopoDS_Vertex&            V,
                                       NCollection_List<TopoDS_Shape>& Eds) const
{
  bool isb = myVEds.IsBound(V);
  if (!isb)
    return false;

  Eds = myVEds.Find(V);
  return true;
}

bool TopOpeBRepTool_CORRISO::SetConnexity(const TopoDS_Vertex&                  V,
                                          const NCollection_List<TopoDS_Shape>& Eds)
{
  bool isb = myVEds.IsBound(V);
  if (!isb)
    return false;

  myVEds.ChangeFind(V) = Eds;
  return true;
}

bool TopOpeBRepTool_CORRISO::UVClosed() const
{
#ifdef OCCT_DEBUG
  bool trc = TopOpeBRepTool_GettraceCORRISO();
  if (trc)
    std::cout << "** UVClosed" << std::endl;
#endif
  NCollection_DataMap<TopoDS_Shape, int> lfyE;
  int                                    nfybounds   = 3;
  bool                                   stopatfirst = true;
  bool foundfaulty = EdgesWithFaultyUV(myEds, nfybounds, lfyE, stopatfirst);
  return !foundfaulty;
}

double TopOpeBRepTool_CORRISO::Tol(const int I, const double tol3d) const
{
  double tol = (I == 1) ? myGAS.UResolution(tol3d) : myGAS.VResolution(tol3d);
  return tol;
}

static double FUN_getx(const TopoDS_Edge&,
                       const TopOpeBRepTool_C2DF& c2df,
                       const bool                 uiso,
                       const double               par)
{
  gp_Pnt2d uv = TopOpeBRepTool_TOOL::UVF(par, c2df);
  double   x  = (uiso) ? uv.Y() : uv.X();
  return x;
}

bool TopOpeBRepTool_CORRISO::PurgeFyClosingE(const NCollection_List<TopoDS_Shape>& ClEds,
                                             NCollection_List<TopoDS_Shape>&       fyClEds) const
{
  fyClEds.Clear();
#ifdef OCCT_DEBUG
  bool trc = TopOpeBRepTool_GettraceCORRISO();
  if (trc)
    std::cout << "* PurgeFyClosingE" << std::endl;
#endif

  double tttol  = 1.e-8;
  double tttolS = BRep_Tool::Tolerance(myFref);
  double tolu = Tol(1, tttolS), tolv = Tol(2, tttolS);
  double tttuvF = std::max(tolu, tolv);

  NCollection_IndexedMap<TopoDS_Shape>     mapcl;
  NCollection_List<TopoDS_Shape>::Iterator itce(ClEds);
  for (; itce.More(); itce.Next())
    mapcl.Add(itce.Value());

  itce.Initialize(ClEds);
  NCollection_DataMap<TopoDS_Shape, int> fyceds;
  bool                                   found = EdgesWithFaultyUV(ClEds, 3, fyceds);
  if (!found)
    return false;

  if (fyceds.Extent() == 1)
  {
    NCollection_DataMap<TopoDS_Shape, int> fyeds;

    EdgesWithFaultyUV(myEds, 3, fyeds);
    int nfy = fyeds.Extent();

    NCollection_DataMap<TopoDS_Shape, int>::Iterator itm(fyceds);
    const TopoDS_Edge&                               cE = TopoDS::Edge(itm.Key());

    TopAbs_Orientation OocE   = TopAbs::Complement(cE.Orientation());
    bool               isoncE = mapcl.Contains(cE.Oriented(OocE));
    if (isoncE)
    {
      NCollection_Array1<TopoDS_Shape> vcE(1, 2);
      TopOpeBRepTool_TOOL::Vertices(cE, vcE);
      TopAbs_Orientation  ocE     = cE.Orientation();
      double              tttolcE = BRep_Tool::Tolerance(cE);
      double              tttuvcE = std::max(Tol(1, tttolcE), Tol(2, tttolcE));
      TopOpeBRepTool_C2DF cE2d;
      bool                isb = UVRep(cE, cE2d);
      if (!isb)
        return false;

      TopAbs_Orientation oOcE        = TopAbs::Complement(ocE);
      TopoDS_Shape       alocalShape = cE.Oriented(oOcE);
      TopoDS_Edge        OcE         = TopoDS::Edge(alocalShape);

      NCollection_Array1<TopoDS_Shape> vOcE(1, 2);
      TopOpeBRepTool_TOOL::Vertices(OcE, vOcE);
      double              tttolOcE = BRep_Tool::Tolerance(OcE);
      double              tttuvOcE = std::max(Tol(1, tttolOcE), Tol(2, tttolOcE));
      TopOpeBRepTool_C2DF OcE2d;
      bool                isOb = UVRep(OcE, OcE2d);
      if (!isOb)
        return false;

      double   parvce1 = TopOpeBRepTool_TOOL::ParE(1, cE);
      gp_Pnt2d UVvce1  = TopOpeBRepTool_TOOL::UVF(parvce1, cE2d);

      double   parvOcE2 = TopOpeBRepTool_TOOL::ParE(2, OcE);
      gp_Pnt2d UVvOcE2  = TopOpeBRepTool_TOOL::UVF(parvOcE2, OcE2d);
      double   tol      = std::max(tttuvcE, tttuvOcE);
      isoncE            = (UVvce1.Distance(UVvOcE2) < tol);
      if (isoncE && (nfy != 1))
      {
        return false;
      }
    }

    int ivf = itm.Value();
    if (ivf == 3)
    {
      fyClEds.Append(cE);
      return true;
    }
  }
  else if (fyceds.Extent() > 1)
  {

    bool                                             hasinit = false;
    bool                                             isou = false, isov = false;
    gp_Pnt2d                                         o2d;
    gp_Dir2d                                         d2d;
    double                                           xinf = 1.e7, xsup = -1.e7;
    bool                                             infdef = false, supdef = false;
    NCollection_DataMap<TopoDS_Shape, int>::Iterator itm(fyceds);
    for (; itm.More(); itm.Next())
    {
      const TopoDS_Edge&  cE = TopoDS::Edge(itm.Key());
      TopOpeBRepTool_C2DF c2df;
      bool                isb = UVRep(cE, c2df);
      if (!isb)
        return false;

      int      ivf = itm.Value();
      bool     isoux, isovx;
      gp_Pnt2d o2dx;
      gp_Dir2d d2dx;
      bool     uvisox = TopOpeBRepTool_TOOL::UVISO(c2df, isoux, isovx, d2dx, o2dx);
      if (!uvisox)
        return false;

      if (hasinit)
      {
        bool onsamline = (isou && isoux) || (isov && isovx);
        if (!onsamline)
          return false;
      }
      if (!hasinit)
      {
        isou    = isoux;
        isov    = isovx;
        o2d     = o2dx;
        d2d     = d2dx;
        hasinit = true;
      }
      else
      {
        bool onsamline = false;
        if (isou && isoux)
        {
          double du = o2d.X() - o2dx.X();
          onsamline = (std::abs(du) < tolu);
        }
        if (isov && isovx)
        {
          double dv = o2d.Y() - o2dx.Y();
          onsamline = (std::abs(dv) < tolv);
        }
        if (!onsamline)
          return false;
      }
      for (int i = 1; i <= 2; i++)
      {
        double pari     = TopOpeBRepTool_TOOL::ParE(i, cE);
        double xi       = FUN_getx(cE, c2df, isou, pari);
        bool   vifaulty = (ivf == i || ivf == 3);
        bool   inff     = (xi < xinf);
        bool   supl     = (xi > xsup);

        if (inff)
        {
          xinf   = xi;
          infdef = vifaulty;
        }
        if (supl)
        {
          xsup   = xi;
          supdef = vifaulty;
        }
      }
      fyClEds.Append(cE);
    }
    bool toremove = infdef && supdef;
    if (!toremove)
      fyClEds.Clear();
  }
  if (!fyClEds.IsEmpty())
    return true;

  itce.Initialize(ClEds);
  for (; itce.More(); itce.Next())
  {

    const TopoDS_Edge&               cE = TopoDS::Edge(itce.Value());
    NCollection_Array1<TopoDS_Shape> vcE(1, 2);
    TopOpeBRepTool_TOOL::Vertices(cE, vcE);
    TopAbs_Orientation ocE = cE.Orientation();

    double              tttolcE = BRep_Tool::Tolerance(cE);
    double              tttuvcE = std::max(Tol(1, tttolcE), Tol(2, tttolcE));
    TopOpeBRepTool_C2DF cE2d;
    bool                isb = UVRep(cE, cE2d);
    if (!isb)
      return false;
#ifdef OCCT_DEBUG
    int icE = STATIC_PURGE_mapeds.Add(cE);
    if (trc)
      std::cout << "? e" << icE << " :" << std::endl;
#endif

    bool isonOcE2d = false;
    {

      TopAbs_Orientation oOcE        = TopAbs::Complement(ocE);
      TopoDS_Shape       aLocalShape = cE.Oriented(oOcE);
      TopoDS_Edge        OcE         = TopoDS::Edge(aLocalShape);

      NCollection_Array1<TopoDS_Shape> vOcE(1, 2);
      TopOpeBRepTool_TOOL::Vertices(OcE, vOcE);
      bool hasOcE = mapcl.Contains(OcE);
      if (!hasOcE)
        continue;
      double              tttolOcE = BRep_Tool::Tolerance(OcE);
      double              tttuvOcE = std::max(Tol(1, tttolOcE), Tol(2, tttolOcE));
      TopOpeBRepTool_C2DF OcE2d;
      bool                isOb = UVRep(OcE, OcE2d);
      if (!isOb)
        return false;

      double   parvce1 = TopOpeBRepTool_TOOL::ParE(1, cE);
      gp_Pnt2d UVvce1  = TopOpeBRepTool_TOOL::UVF(parvce1, cE2d);

      double   parvOcE2 = TopOpeBRepTool_TOOL::ParE(2, OcE);
      gp_Pnt2d UVvOcE2  = TopOpeBRepTool_TOOL::UVF(parvOcE2, OcE2d);
      double   tol      = std::max(tttuvcE, tttuvOcE);
      isonOcE2d         = (UVvce1.Distance(UVvOcE2) < tol);
    }
    if (!isonOcE2d)
    {
#ifdef OCCT_DEBUG
      if (trc)
        std::cout << "-> valid edge" << std::endl;
#endif
      continue;
    }

    int nvcEok = 0;
    for (int ivce = 1; ivce <= 2; ivce++)
    {

      const TopoDS_Vertex&           vce = TopoDS::Vertex(vcE(ivce));
      NCollection_List<TopoDS_Shape> loe;
      isb = Connexity(vce, loe);

      if (!isb)
        return false;

      double   parvce = TopOpeBRepTool_TOOL::ParE(ivce, cE);
      gp_Pnt2d UVvce  = TopOpeBRepTool_TOOL::UVF(parvce, cE2d);
#ifdef OCCT_DEBUG

      int ivmapv = STATIC_PURGE_mapv.Add(vce);
      if (trc)
      {
        std::cout << " connexity for v(" << ivce << ")=v" << ivmapv;
        FUN_tool_trace(UVvce);
      }
#endif
      double tttolvce = BRep_Tool::Tolerance(vce);
      double tttuvvce = std::max(Tol(1, tttolvce), Tol(2, tttolvce));

      bool vceok = false;
      for (NCollection_List<TopoDS_Shape>::Iterator ite(loe); ite.More(); ite.Next())
      {
        const TopoDS_Edge& E = TopoDS::Edge(ite.Value());

#ifdef OCCT_DEBUG
        int iE = STATIC_PURGE_mapeds.Add(E);
        if (trc)
        {
          std::cout << "    : on e" << iE << std::endl;
        }
#endif

        if (mapcl.Contains(E))
          continue;

        TopOpeBRepTool_C2DF E2d;
        bool                isB2 = UVRep(E, E2d);
        if (!isB2)
          return false;

        double tttolE = BRep_Tool::Tolerance(E);
        double tttuvE = std::max(Tol(1, tttolE), Tol(2, tttolE));

        NCollection_Array1<TopoDS_Shape> vE(1, 2);
        TopOpeBRepTool_TOOL::Vertices(E, vE);
        for (int ive = 1; ive <= 2; ive++)
        {

          const TopoDS_Vertex& ve    = TopoDS::Vertex(vE(ive));
          bool                 samev = ve.IsSame(vce);
          if (!samev)
            continue;
          double   parve = TopOpeBRepTool_TOOL::ParE(ive, E);
          gp_Pnt2d UVve  = TopOpeBRepTool_TOOL::UVF(parve, E2d);
#ifdef OCCT_DEBUG
          if (trc)
          {
            std::cout << "    ve(" << ive << ")";
            FUN_tool_trace(UVve);
          }
#endif
          if (ive == ivce)
            continue;
          double tttolve = BRep_Tool::Tolerance(ve);
          double tttuvve = std::max(Tol(1, tttolve), Tol(2, tttolve));

          tttol = std::max(
            tttol,
            std::max(tttuvF, std::max(tttuvE, std::max(tttuvcE, std::max(tttuvve, tttuvvce)))));

          double dd     = UVve.Distance(UVvce);
          bool   sameuv = (dd < tttol);
          if (myUclosed)
          {
            double xperiod = myUper;
            dd             = (UVve.X() - UVvce.X());
            sameuv         = sameuv || (std::abs(std::abs(dd) - xperiod) < tttol);
          }
          if (myVclosed)
          {
            double xperiod = myVper;
            dd             = (UVve.Y() - UVvce.Y());
            sameuv         = sameuv || (std::abs(std::abs(dd) - xperiod) < tttol);
          }
          if (sameuv)
          {
            vceok = true;
#ifdef OCCT_DEBUG
            if (trc)
            {
              std::cout << " connexity->ok" << std::endl;
            }
#endif
          }
          break;
        }
        if (vceok)
          break;
      }

#ifdef OCCT_DEBUG
      if (trc && !vceok)
      {
        std::cout << " connexity->KO" << std::endl;
      }
#endif
      if (vceok)
        nvcEok++;
    }

    bool isfycE = (nvcEok == 0);

#ifdef OCCT_DEBUG
    if (trc)
    {
      if (isfycE)
        std::cout << "-> faulty edge" << std::endl;
      else
        std::cout << "-> valid edge" << std::endl;
    }
#endif
    if (isfycE)
      fyClEds.Append(cE);
  }
  return (!fyClEds.IsEmpty());
}

#define SPLITEDGE (0)
#define INCREASE (1)
#define DECREASE (-1)

static int FUN_tool_recadre(const double minx,
                            const double maxx,
                            const double xfirst,
                            const double xlast,
                            const double tolx,
                            bool&        maxsup)
{
  int  recadre = 10;
  bool maxinf  = (maxx < xfirst + tolx);
  bool mininf  = (minx < xfirst - tolx);
  maxsup       = (maxx > xlast + tolx);
  bool minsup  = (minx > xlast - tolx);
  bool maxok   = (xfirst - tolx < maxx) && (maxx < xlast + tolx);
  bool minok   = (xfirst - tolx < minx) && (minx < xlast + tolx);

  if (maxinf)
    recadre = INCREASE;
  else if (minsup)
    recadre = DECREASE;
  else if (mininf && maxok)
    recadre = SPLITEDGE;
  else if (minok && maxsup)
    recadre = SPLITEDGE;
  return recadre;
}

int TopOpeBRepTool_CORRISO::EdgeOUTofBoundsUV(const TopoDS_Edge& E,
                                              const bool         onU,
                                              const double       tolx,
                                              double&            parspE) const
{
  int recadre = 10;
  parspE      = -1.e7;
  int isb     = myERep2d.IsBound(E);
  if (!isb)
    return false;

  const TopOpeBRepTool_C2DF&       C2DF = myERep2d.Find(E);
  double                           f, l, tol;
  const occ::handle<Geom2d_Curve>& PC = C2DF.PC(f, l, tol);

  double xfirst = onU ? myGAS.FirstUParameter() : myGAS.FirstVParameter();

  double xlast = onU ? myGAS.LastUParameter() : myGAS.LastVParameter();

  double xperiod = onU ? myUper : myVper;

  bool     isou, isov;
  gp_Pnt2d o2d;
  gp_Dir2d d2d;
  bool     iso = TopOpeBRepTool_TOOL::UVISO(PC, isou, isov, d2d, o2d);

  if (iso)
  {

    bool inX = (onU && isou) || ((!onU) && isov);
    if (inX)
    {

      double xpar     = onU ? o2d.X() : o2d.Y();
      bool   toosmall = (xpar < xfirst - tolx);
      bool   tobig    = (xpar > xfirst + xperiod + tolx);

      if (toosmall)
        recadre = INCREASE;
      if (tobig)
        recadre = DECREASE;
      return recadre;
    }
    bool inY = (onU && isov) || ((!onU) && isou);
    if (inY)
    {

      double   d2ddir  = onU ? d2d.Y() : d2d.X();
      bool     reverse = (d2ddir < 0.);
      double   xfactor = reverse ? -1. : 1.;
      double   max     = reverse ? f : l;
      double   min     = reverse ? l : f;
      gp_Pnt2d maxuv   = PC->Value(max);
      gp_Pnt2d minuv   = PC->Value(min);

      double maxx = onU ? maxuv.X() : maxuv.Y();
      double minx = onU ? minuv.X() : minuv.Y();

      bool maxsup;
      recadre = FUN_tool_recadre(minx, maxx, xfirst, xlast, tolx, maxsup);
      if (recadre == SPLITEDGE)
      {
        double xbound = maxsup ? xperiod : 0.;
        parspE        = max - xfactor * (maxx - xbound);
      }
      return recadre;
    }
  }
  else
  {

    Bnd_Box2d           Bn2d;
    Geom2dAdaptor_Curve GC2d(PC, f, l);
    double              tolE   = BRep_Tool::Tolerance(E);
    double              toladd = std::max(tolE, tol);
    BndLib_Add2dCurve::Add(GC2d, toladd, Bn2d);
    double umin, vmin, umax, vmax;
    Bn2d.Get(umin, vmin, umax, vmax);
    double xmin = onU ? umin : vmin;
    double xmax = onU ? umax : vmax;
    bool   maxsup;
    recadre = FUN_tool_recadre(xmin, xmax, xfirst, xlast, tolx, maxsup);
    if (recadre == SPLITEDGE)
    {

      return 10;
    }
    return recadre;
  }
  return recadre;
}

bool TopOpeBRepTool_CORRISO::EdgesOUTofBoundsUV(const NCollection_List<TopoDS_Shape>&   EdsToCheck,
                                                const bool                              onU,
                                                const double                            tolx,
                                                NCollection_DataMap<TopoDS_Shape, int>& FyEds) const
{
  FyEds.Clear();
  NCollection_List<TopoDS_Shape>::Iterator it(EdsToCheck);
  for (; it.More(); it.Next())
  {
    const TopoDS_Edge& E       = TopoDS::Edge(it.Value());
    double             sspar   = -1.e7;
    int                recadre = EdgeOUTofBoundsUV(E, onU, tolx, sspar);
    if (recadre == SPLITEDGE)
      FUN_Raise();
    if (recadre == INCREASE)
      FyEds.Bind(E, 1);
    if (recadre == DECREASE)
      FyEds.Bind(E, -1);
  }
  return (!FyEds.IsEmpty());
}

bool TopOpeBRepTool_CORRISO::EdgeWithFaultyUV(const TopoDS_Edge& E, int& Ivfaulty) const
{
#ifdef OCCT_DEBUG
  bool trc = TopOpeBRepTool_GettraceCORRISO();
  int  iE  = STATIC_PURGE_mapeds.Add(E);
  if (trc)
    std::cout << "? e" << iE << " :" << std::endl;
#endif
  Ivfaulty      = 0;
  double tttol  = 1.e-8;
  double tttolF = BRep_Tool::Tolerance(TopoDS::Face(myFref));
  double tttuvF = std::max(Tol(1, tttolF), Tol(2, tttolF));
  double tttolE = BRep_Tool::Tolerance(E);
  double tttuvE = std::max(Tol(1, tttolE), Tol(2, tttolE));

  TopAbs_Orientation oE = E.Orientation();
  if (M_INTERNAL(oE) || M_EXTERNAL(oE))
    return false;

  NCollection_Array1<TopoDS_Shape> vEs(1, 2);
  TopOpeBRepTool_TOOL::Vertices(E, vEs);
  bool closed = vEs(1).IsSame(vEs(2));
  if (closed)
  {
#ifdef OCCT_DEBUG
    if (trc)
    {
      std::cout << "closed -> valid edge" << std::endl;
    }
#endif
    return false;
  }

  int nfyv = 0;
  for (int ivE = 1; ivE <= 2; ivE++)
  {

    const TopoDS_Vertex& vE    = TopoDS::Vertex(vEs(ivE));
    double               parvE = TopOpeBRepTool_TOOL::ParE(ivE, E);
    TopOpeBRepTool_C2DF  C2DF;
    bool                 isb = UVRep(E, C2DF);
    if (!isb)
      return false;
    gp_Pnt2d UVvE = TopOpeBRepTool_TOOL::UVF(parvE, C2DF);
#ifdef OCCT_DEBUG

    int ivmapv = STATIC_PURGE_mapv.Add(vE);
    if (trc)
    {
      std::cout << " connexity for v(" << ivE << ")=v" << ivmapv;
      FUN_tool_trace(UVvE);
    }
#endif

    double tttolvE = BRep_Tool::Tolerance(vE);
    double tttuvvE = std::max(Tol(1, tttolvE), Tol(2, tttolvE));

    bool isbound = myVEds.IsBound(vE);
    if (!isbound)
    {
      FUN_RaiseError();
      return false;
    }

    bool                                  vEok = false;
    const NCollection_List<TopoDS_Shape>& loe  = myVEds.Find(vE);

    for (NCollection_List<TopoDS_Shape>::Iterator ite(loe); ite.More(); ite.Next())
    {
      const TopoDS_Edge& e  = TopoDS::Edge(ite.Value());
      TopAbs_Orientation oe = e.Orientation();

#ifdef OCCT_DEBUG
      int ie = STATIC_PURGE_mapeds.Add(e);
      if (trc)
      {
        std::cout << "    : on e" << ie << std::endl;
      }
#endif

      if (e.IsSame(E))
        continue;
      if (M_INTERNAL(oe) || M_EXTERNAL(oe))
        continue;

      bool isBound = myERep2d.IsBound(e);
      if (!isBound)
      {
        FUN_RaiseError();
        return false;
      }
      const TopOpeBRepTool_C2DF& aC2DF = myERep2d.Find(e);

      NCollection_Array1<TopoDS_Shape> ves(1, 2);
      TopOpeBRepTool_TOOL::Vertices(e, ves);
      for (int ive = 1; ive <= 2; ive++)
      {
        const TopoDS_Vertex& ve    = TopoDS::Vertex(ves(ive));
        bool                 samev = ve.IsSame(vE);
        if (!samev)
          continue;

        double   pare = TopOpeBRepTool_TOOL::ParE(ive, e);
        gp_Pnt2d UVve = TopOpeBRepTool_TOOL::UVF(pare, aC2DF);
#ifdef OCCT_DEBUG
        if (trc)
        {
          std::cout << "    ve(" << ive << ")";
          FUN_tool_trace(UVve);
        }
#endif
        if (ive == ivE)
          continue;

        double tttolve = BRep_Tool::Tolerance(ve);
        double tttuvve = std::max(Tol(1, tttolve), Tol(2, tttolve));

        tttol = std::max(
          tttol,
          std::max(tttuvF, std::max(tttuvE, std::max(tttuvE, std::max(tttuvve, tttuvvE)))));
        bool isequal = UVvE.IsEqual(UVve, tttol);
        if (isequal)
        {
          vEok = true;
#ifdef OCCT_DEBUG
          if (trc)
          {
            std::cout << " connexity->ok" << std::endl;
          }
#endif
          break;
        }
      }
      if (vEok)
        break;
    }

    if (!vEok)
    {
      nfyv++;
      Ivfaulty = ivE;
    }
#ifdef OCCT_DEBUG
    if (trc && !vEok)
    {
      std::cout << " connexity->KO" << std::endl;
    }
#endif
  }
  if (nfyv == 2)
    Ivfaulty = 3;
#ifdef OCCT_DEBUG
  if (trc)
  {
    if (Ivfaulty == 0)
      std::cout << "-> valid edge" << std::endl;
    else
      std::cout << "-> faulty edge" << std::endl;
  }
#endif
  return (Ivfaulty != 0);
}

bool TopOpeBRepTool_CORRISO::EdgesWithFaultyUV(const NCollection_List<TopoDS_Shape>&   EdsToCheck,
                                               const int                               nfybounds,
                                               NCollection_DataMap<TopoDS_Shape, int>& FyEds,
                                               const bool stopatfirst) const
{
  FyEds.Clear();
#ifdef OCCT_DEBUG
  int  ifault = 0;
  bool trc    = TopOpeBRepTool_GettraceCORRISO();
  if (trc)
    std::cout << std::endl << "* EdgesWithFaultyUV" << std::endl;
#endif

  NCollection_List<TopoDS_Shape>::Iterator itchk(EdsToCheck);
  for (; itchk.More(); itchk.Next())
  {

    const TopoDS_Edge& Echk     = TopoDS::Edge(itchk.Value());
    int                Ivfaulty = 0;
    bool               faulty   = EdgeWithFaultyUV(Echk, Ivfaulty);
    if (!faulty)
      continue;
    int nfyv = (Ivfaulty == 3) ? 2 : 1;

#ifdef OCCT_DEBUG
    ifault++;
    if (trc)
      std::cout << "e" << STATIC_PURGE_mapeds.FindIndex(Echk) << " has ifyv=" << Ivfaulty
                << std::endl;
#endif

    bool found = false;
    if (nfybounds == 1)
      found = (nfyv == nfybounds);
    else if (nfybounds == 2)
      found = (nfyv == nfybounds);
    else if (nfybounds == 3)
      found = (nfyv > 0);

    if (found)
    {
      FyEds.Bind(Echk, Ivfaulty);
      if (stopatfirst)
        return true;
    }
  }
  int n = FyEds.Extent();
  return (n != 0);
}

bool TopOpeBRepTool_CORRISO::EdgeWithFaultyUV(const NCollection_List<TopoDS_Shape>& EdsToCheck,
                                              const int                             nfybounds,
                                              TopoDS_Shape&                         fyE,
                                              int&                                  Ifaulty) const
{
  NCollection_DataMap<TopoDS_Shape, int> FyEds;
  bool found = EdgesWithFaultyUV(EdsToCheck, nfybounds, FyEds, true);
  if (!found)
    return false;

  NCollection_DataMap<TopoDS_Shape, int>::Iterator itm(FyEds);
  fyE     = itm.Key();
  Ifaulty = itm.Value();
  return true;
}

bool TopOpeBRepTool_CORRISO::TrslUV(const bool                                    onU,
                                    const NCollection_DataMap<TopoDS_Shape, int>& FyEds)
{
  gp_Vec2d tt2d;
  if (onU)
  {
    double uper;
    Refclosed(1, uper);
    if (!uper)
      return false;
    tt2d = gp_Vec2d(uper, 0.);
  }
  else
  {
    double vper;
    Refclosed(2, vper);
    if (!vper)
      return false;
    tt2d = gp_Vec2d(0., vper);
  }
  NCollection_DataMap<TopoDS_Shape, int>::Iterator itm(FyEds);
  for (; itm.More(); itm.Next())
  {
    const TopoDS_Edge&  E = TopoDS::Edge(itm.Key());
    TopOpeBRepTool_C2DF C2DF;
    bool                isb = UVRep(E, C2DF);
    if (!isb)
      return false;

    int itt = itm.Value();
    if (itt == SPLITEDGE)
      return false;
    else if (itt == INCREASE)
      TopOpeBRepTool_TOOL::TrslUV(tt2d, C2DF);
    else if (itt == DECREASE)
      TopOpeBRepTool_TOOL::TrslUV(tt2d.Multiplied(-1.), C2DF);
    else
      return false;
    SetUVRep(E, C2DF);
  }
  return true;
}

bool TopOpeBRepTool_CORRISO::GetnewS(TopoDS_Face& newS) const
{
  newS.Nullify();
  if (myS.ShapeType() != TopAbs_FACE)
    return false;

  newS = TopoDS::Face(myS);
  BRep_Builder BB;

  NCollection_List<TopoDS_Shape>::Iterator it(myEds);
  for (; it.More(); it.Next())
  {
    TopoDS_Edge         E    = TopoDS::Edge(it.Value());
    TopAbs_Orientation  oriE = E.Orientation();
    TopOpeBRepTool_C2DF C2DF;
    bool                isb = UVRep(E, C2DF);
    if (!isb)
      return false;

    double                           f, l, tol;
    const occ::handle<Geom2d_Curve>& PC = C2DF.PC(f, l, tol);
    occ::handle<Geom2d_TrimmedCurve> cu = new Geom2d_TrimmedCurve(PC, f, l);

    TopoDS_Shape aLocalShape = E.Oriented(TopAbs::Complement(oriE));
    TopoDS_Edge  Err         = TopoDS::Edge(aLocalShape);

    TopOpeBRepTool_C2DF C2DFrr;
    bool                isclo = UVRep(Err, C2DFrr);

    if (isclo)
    {
      double                           frr, lrr, tolrr;
      const occ::handle<Geom2d_Curve>& PCrr = C2DFrr.PC(frr, lrr, tolrr);
      occ::handle<Geom2d_TrimmedCurve> curr = new Geom2d_TrimmedCurve(PCrr, frr, lrr);
      if (M_FORWARD(oriE))
        BB.UpdateEdge(E, cu, curr, newS, tol);
    }
    else
      BB.UpdateEdge(E, cu, newS, tol);
  }
  return true;
}

bool TopOpeBRepTool_CORRISO::AddNewConnexity(const TopoDS_Vertex&, const TopoDS_Edge& E)
{

  bool isb = myERep2d.IsBound(E);
  if (!isb)
  {
    occ::handle<Geom2d_Curve> PC;
    double                    f, l, tol;
    bool                      hasold = FC2D_HasOldCurveOnSurface(E, myFref, PC);
    PC                               = FC2D_EditableCurveOnSurface(E, myFref, f, l, tol);
    if (!hasold)
      FC2D_AddNewCurveOnSurface(PC, E, myFref, f, l, tol);
    if (PC.IsNull())
      return false;
    TopOpeBRepTool_C2DF C2DF(PC, f, l, tol, myFref);
    myERep2d.Bind(E, C2DF);
  }

  if (!isb)
    myEds.Append(E);

  TopExp_Explorer exv(E, TopAbs_VERTEX);
  for (; exv.More(); exv.Next())
  {
    const TopoDS_Vertex& v    = TopoDS::Vertex(exv.Current());
    bool                 isbb = myVEds.IsBound(v);
    if (isbb)
      myVEds.ChangeFind(v).Append(E);
    else
    {
      NCollection_List<TopoDS_Shape> loe;
      loe.Append(E);
      myVEds.Bind(v, loe);
    }
  }
  return true;
}

bool TopOpeBRepTool_CORRISO::RemoveOldConnexity(const TopoDS_Vertex&, const TopoDS_Edge& E)
{

  bool isb = myERep2d.IsBound(E);
  if (isb)
    myERep2d.UnBind(E);

  if (isb)
  {
    NCollection_List<TopoDS_Shape>::Iterator it(myEds);
    while (it.More())
    {
      if (it.Value().IsEqual(E))
      {
        myEds.Remove(it);
        break;
      }
      else
        it.Next();
    }
  }

  bool            done = false;
  TopExp_Explorer exv(E, TopAbs_VERTEX);
  for (; exv.More(); exv.Next())
  {
    const TopoDS_Vertex& v        = TopoDS::Vertex(exv.Current());
    bool                 isBoundV = myVEds.IsBound(v);
    if (!isBoundV)
      return false;
    NCollection_List<TopoDS_Shape>&          loe = myVEds.ChangeFind(v);
    NCollection_List<TopoDS_Shape>::Iterator ite(loe);
    while (ite.More())
    {
      if (ite.Value().IsEqual(E))
      {
        done = true;
        loe.Remove(ite);
        break;
      }
      else
        ite.Next();
    }
  }
  return done;
}
