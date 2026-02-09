#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepAdaptor_Curve2d.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepClass_FaceClassifier.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <CSLib_Class2d.hpp>
#include <ElCLib.hpp>
#include <Geom2dInt_Geom2dCurveTool.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <GeomInt.hpp>
#include <GCPnts_QuasiUniformDeflection.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <IntTools_FClass2d.hpp>
#include <Precision.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Vec2d.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_DataMap.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Wire.hpp>
#include <Poly.hpp>

#include <cstdio>

#ifdef DEBUG_PCLASS_POLYGON
  #include <DrawTrSurf.hpp>
  #include <Geom2d_BSplineCurve.hpp>
#endif

IntTools_FClass2d::IntTools_FClass2d() = default;

IntTools_FClass2d::IntTools_FClass2d(const TopoDS_Face& aFace, const double TolUV)
    : Toluv(TolUV),
      Face(aFace)
{
  Init(Face, Toluv);
}

bool IntTools_FClass2d::IsHole() const
{
  return myIsHole;
}

void IntTools_FClass2d::Init(const TopoDS_Face& aFace, const double TolUV)
{
  bool   WireIsNotEmpty, Ancienpnt3dinitialise, degenerated;
  int    firstpoint, NbEdges;
  int    iX, aNbs1, nbs, Avant, BadWire;
  double u, du, Tole, Tol, pfbid, plbid;
  double FlecheU, FlecheV, TolVertex1, TolVertex;
  double uFirst, uLast;
  double aPrCf, aPrCf2;

  TopoDS_Edge                    edge;
  TopoDS_Vertex                  Va, Vb;
  TopAbs_Orientation             Or;
  BRepTools_WireExplorer         aWExp;
  TopExp_Explorer                aExpF, aExp;
  occ::handle<Geom2d_Curve>      aC2D;
  gp_Pnt                         Ancienpnt3d;
  NCollection_Sequence<gp_Pnt2d> SeqPnt2d;
  NCollection_DataMap<int, int>  anIndexMap;
  NCollection_Sequence<gp_Vec2d> aD1Prev;
  NCollection_Sequence<gp_Vec2d> aD1Next;

  aPrCf    = Precision::Confusion();
  aPrCf2   = aPrCf * aPrCf;
  myIsHole = true;

  Toluv = TolUV;
  Face  = aFace;
  Face.Orientation(TopAbs_FORWARD);
  occ::handle<BRepAdaptor_Surface> surf = new BRepAdaptor_Surface();
  surf->Initialize(aFace, false);

  Tole = 0.;
  Tol  = 0.;
  Umin = Vmin = RealLast();
  Umax = Vmax = -Umin;
  BadWire     = 0;

  aExpF.Init(Face, TopAbs_WIRE);
  for (; aExpF.More(); aExpF.Next())
  {
    const TopoDS_Wire& aW = *((TopoDS_Wire*)&aExpF.Current());

    firstpoint            = 1;
    FlecheU               = 0.;
    FlecheV               = 0.;
    TolVertex1            = 0.;
    TolVertex             = 0.;
    WireIsNotEmpty        = false;
    Ancienpnt3dinitialise = false;
    Ancienpnt3d.SetCoord(0., 0., 0.);

    SeqPnt2d.Clear();
    anIndexMap.Clear();
    aD1Prev.Clear();
    aD1Next.Clear();

    NbEdges = 0;
    aExp.Init(aW, TopAbs_EDGE);
    for (; aExp.More(); aExp.Next())
    {
      NbEdges++;
    }

    aWExp.Init(aW, Face);
    for (; aWExp.More(); aWExp.Next())
    {
      NbEdges--;
      edge = aWExp.Current();
      Or   = edge.Orientation();
      if (Or != TopAbs_FORWARD && Or != TopAbs_REVERSED)
      {
        continue;
      }

      aC2D = BRep_Tool::CurveOnSurface(edge, Face, pfbid, plbid);
      if (aC2D.IsNull())
      {
        return;
      }

      BRepAdaptor_Curve2d C(edge, Face);
      BRepAdaptor_Curve   C3d;

      degenerated = false;
      if (BRep_Tool::Degenerated(edge) || BRep_Tool::IsClosed(edge, Face))
      {
        degenerated = true;
      }

      TopExp::Vertices(edge, Va, Vb);

      TolVertex1 = 0.;
      TolVertex  = 0.;
      if (Va.IsNull())
      {
        degenerated = true;
      }
      else
      {
        TolVertex1 = BRep_Tool::Tolerance(Va);
      }
      if (Vb.IsNull())
      {
        degenerated = true;
      }
      else
      {
        TolVertex = BRep_Tool::Tolerance(Vb);
      }

      if (TolVertex < TolVertex1)
      {
        TolVertex = TolVertex1;
      }

      if (!degenerated)
      {

        C3d.Initialize(edge, Face);
        gp_Pnt P3da       = C3d.Value(0.5 * (pfbid + plbid));
        du                = plbid - pfbid;
        const int NBSTEPS = 10;
        double    aPrec2  = 0.25 * Precision::Confusion() * Precision::Confusion();
        degenerated       = true;
        for (int i = 0; i <= NBSTEPS; i++)
        {
          double U    = pfbid + i * du / NBSTEPS;
          gp_Pnt P3db = C3d.Value(U);
          double aR2  = P3da.SquareDistance(P3db);
          if (aR2 > aPrec2)
          {
            degenerated = false;
            break;
          }
        }
      }

      Tole = BRep_Tool::Tolerance(edge);
      if (Tole > Tol)
      {
        Tol = Tole;
      }

      nbs = Geom2dInt_Geom2dCurveTool::NbSamples(C);
      if (nbs > 2)
      {
        nbs *= 4;
      }
      du = (plbid - pfbid) / (double)(nbs - 1);

      if (Or == TopAbs_FORWARD)
      {
        u      = pfbid;
        uFirst = pfbid;
        uLast  = plbid;
      }
      else
      {
        u      = plbid;
        uFirst = plbid;
        uLast  = pfbid;
        du     = -du;
      }

      aNbs1 = nbs + 1;
      NCollection_Array1<double> aPrms(1, aNbs1);

      if (nbs == 2)
      {
        double aCoef = 0.0025;
        aPrms(1)     = uFirst;
        aPrms(2)     = uFirst + aCoef * (uLast - uFirst);
        aPrms(3)     = uLast;
      }
      else if (nbs > 2)
      {
        aNbs1    = nbs;
        aPrms(1) = uFirst;
        for (iX = 2; iX < aNbs1; ++iX)
        {
          aPrms(iX) = u + (iX - 1) * du;
        }
        aPrms(aNbs1) = uLast;
      }

      Avant = SeqPnt2d.Length();
      for (iX = firstpoint; iX <= aNbs1; iX++)
      {
        bool     IsRealCurve3d;
        int      ii;
        double   aDstX;
        gp_Pnt2d P2d;
        gp_Pnt   P3d;

        u   = aPrms(iX);
        P2d = C.Value(u);
        if (P2d.X() < Umin)
          Umin = P2d.X();
        if (P2d.X() > Umax)
          Umax = P2d.X();
        if (P2d.Y() < Vmin)
          Vmin = P2d.Y();
        if (P2d.Y() > Vmax)
          Vmax = P2d.Y();

        aDstX = RealLast();
        if (!degenerated)
        {
          P3d = C3d.Value(u);
          if (!SeqPnt2d.IsEmpty())
          {
            if (Ancienpnt3dinitialise)
            {
              aDstX = P3d.SquareDistance(Ancienpnt3d);
            }
          }
        }

        IsRealCurve3d = true;
        if (aDstX < aPrCf2)
        {
          if (iX > 1)
          {
            double aDstX1;
            gp_Pnt MidP3d;

            MidP3d = C3d.Value(0.5 * (u + aPrms(iX - 1)));
            aDstX1 = P3d.SquareDistance(MidP3d);
            if (aDstX1 < aPrCf2)
            {
              IsRealCurve3d = false;
            }
          }
        }

        if (IsRealCurve3d)
        {
          if (!degenerated)
          {
            Ancienpnt3d           = P3d;
            Ancienpnt3dinitialise = true;
          }
          SeqPnt2d.Append(P2d);
        }

        ii = SeqPnt2d.Length();
        if (ii > (Avant + 4))
        {
          double   ul, dU, dV;
          gp_Pnt2d Pp;

          gp_Lin2d Lin(SeqPnt2d(ii - 2), gp_Dir2d(gp_Vec2d(SeqPnt2d(ii - 2), SeqPnt2d(ii))));
          ul = ElCLib::Parameter(Lin, SeqPnt2d(ii - 1));
          Pp = ElCLib::Value(ul, Lin);
          dU = std::abs(Pp.X() - SeqPnt2d(ii - 1).X());
          dV = std::abs(Pp.Y() - SeqPnt2d(ii - 1).Y());
          if (dU > FlecheU)
          {
            FlecheU = dU;
          }
          if (dV > FlecheV)
          {
            FlecheV = dV;
          }
        }
      }

      if (BadWire)
      {
        continue;
      }

      if (firstpoint == 1)
        firstpoint = 2;
      WireIsNotEmpty = true;

      double   aU = aPrms(1);
      gp_Pnt2d aP;
      gp_Vec2d aV;

      C.D1(aU, aP, aV);

      if (Or == TopAbs_REVERSED)
        aV.Reverse();

      aD1Next.Append(aV);

      aU = aPrms(aNbs1);
      C.D1(aU, aP, aV);

      if (Or == TopAbs_REVERSED)
        aV.Reverse();

      if (NbEdges > 0)
        aD1Prev.Append(aV);
      else
        aD1Prev.Prepend(aV);

      if (Avant > 0)
        anIndexMap.Bind(Avant, aD1Next.Length());
      else
        anIndexMap.Bind(1, aD1Next.Length());
    }

    if (NbEdges)
    {

      NCollection_Array1<gp_Pnt2d> PClass(1, 2);
      gp_Pnt2d                     anInitPnt(0., 0.);

      PClass.Init(anInitPnt);
      TabClass.Append(CSLib_Class2d(PClass, FlecheU, FlecheV, Umin, Vmin, Umax, Vmax));
      BadWire = 1;
      TabOrien.Append(-1);
    }

    else if (WireIsNotEmpty)
    {
      if (SeqPnt2d.Length() > 3)
      {
#ifdef DEBUG_PCLASS_POLYGON
        NCollection_Array1<gp_Pnt2d> PClass(1, nbpnts);
        NCollection_Array1<double>   aKnots(1, nbpnts);
        NCollection_Array1<int>      aMults(1, nbpnts);
        for (int i = 1; i <= nbpnts; i++)
        {
          aKnots(i)  = i;
          aMults(i)  = 1;
          PClass(ii) = SeqPnt2d.Value(ii);
        }
        aMults(1) = aMults(nbpnts)            = 2;
        occ::handle<Geom2d_BSplineCurve> aPol = new Geom2d_BSplineCurve(PClass, aKnots, aMults, 1);
        DrawTrSurf::Set("pol", aPol);
#endif

        double aS   = 0.;
        double aPer = 0.;
        Poly::PolygonProperties(SeqPnt2d, aS, aPer);

        double anExpThick = std::max(2. * std::abs(aS) / aPer, 1e-7);
        double aDefl      = std::max(FlecheU, FlecheV);
        double aDiscrDefl = std::min(aDefl * 0.1, anExpThick * 10.);
        bool   isChanged  = false;
        while (aDefl > anExpThick && aDiscrDefl > 1e-7)
        {

          firstpoint = 1;
          isChanged  = true;
          SeqPnt2d.Clear();
          FlecheU = 0.0;
          FlecheV = 0.0;
          for (aWExp.Init(TopoDS::Wire(aExpF.Current()), Face); aWExp.More(); aWExp.Next())
          {
            edge = aWExp.Current();
            Or   = edge.Orientation();
            if (Or == TopAbs_FORWARD || Or == TopAbs_REVERSED)
            {
              BRep_Tool::Range(edge, Face, pfbid, plbid);
              if (std::abs(plbid - pfbid) < 1.e-9)
                continue;
              BRepAdaptor_Curve2d           C(edge, Face);
              GCPnts_QuasiUniformDeflection aDiscr(C, aDiscrDefl);
              if (!aDiscr.IsDone())
                break;
              int nbp   = aDiscr.NbPoints();
              int iStep = 1, i = 1, iEnd = nbp + 1;
              if (Or == TopAbs_REVERSED)
              {
                iStep = -1;
                i     = nbp;
                iEnd  = 0;
              }
              if (firstpoint == 2)
                i += iStep;
              for (; i != iEnd; i += iStep)
              {
                gp_Pnt2d aP2d = C.Value(aDiscr.Parameter(i));
                SeqPnt2d.Append(aP2d);
              }
              if (nbp > 2)
              {
                int      ii = SeqPnt2d.Length();
                gp_Lin2d Lin(SeqPnt2d(ii - 2), gp_Dir2d(gp_Vec2d(SeqPnt2d(ii - 2), SeqPnt2d(ii))));
                double   ul = ElCLib::Parameter(Lin, SeqPnt2d(ii - 1));
                gp_Pnt2d Pp = ElCLib::Value(ul, Lin);
                double   dU = std::abs(Pp.X() - SeqPnt2d(ii - 1).X());
                double   dV = std::abs(Pp.Y() - SeqPnt2d(ii - 1).Y());
                if (dU > FlecheU)
                  FlecheU = dU;
                if (dV > FlecheV)
                  FlecheV = dV;
              }
              firstpoint = 2;
            }
          }
          anExpThick = std::max(2. * std::abs(aS) / aPer, 1e-7);
          aDefl      = std::max(FlecheU, FlecheV);
          aDiscrDefl = std::min(aDiscrDefl * 0.1, anExpThick * 10.);
        }

        if (isChanged)
        {
          Poly::PolygonProperties(SeqPnt2d, aS, aPer);
        }

        if (FlecheU < Toluv)
          FlecheU = Toluv;

        if (FlecheV < Toluv)
          FlecheV = Toluv;

        TabClass.Append(CSLib_Class2d(SeqPnt2d, FlecheU, FlecheV, Umin, Vmin, Umax, Vmax));

        if (std::abs(aS) < Precision::SquareConfusion())
        {
          BadWire = 1;
          TabOrien.Append(-1);
        }
        else
        {
          if (aS > 0.0)
          {
            myIsHole = false;
            TabOrien.Append(1);
          }
          else
          {
            myIsHole = true;
            TabOrien.Append(0);
          }
        }
      }
      else
      {
        BadWire = 1;
        TabOrien.Append(-1);
        NCollection_Array1<gp_Pnt2d> PPClass(1, 2);
        SeqPnt2d.Clear();
        TabClass.Append(CSLib_Class2d(SeqPnt2d, FlecheU, FlecheV, Umin, Vmin, Umax, Vmax));
      }
    }
  }

  int nbtabclass = TabClass.Length();

  if (nbtabclass > 0)
  {

    if (BadWire)
    {
      TabOrien(1) = -1;
    }

    if (surf->GetType() == GeomAbs_Cone || surf->GetType() == GeomAbs_Cylinder
        || surf->GetType() == GeomAbs_Torus || surf->GetType() == GeomAbs_Sphere
        || surf->GetType() == GeomAbs_SurfaceOfRevolution)
    {
      double uuu = M_PI + M_PI - (Umax - Umin);
      if (uuu < 0)
        uuu = 0;
      U1 = Umin - uuu * 0.5;
      U2 = U1 + M_PI + M_PI;
    }
    else
    {
      U1 = U2 = 0.0;
    }

    if (surf->GetType() == GeomAbs_Torus)
    {
      double uuu = M_PI + M_PI - (Vmax - Vmin);
      if (uuu < 0)
        uuu = 0;

      V1 = Vmin - uuu * 0.5;
      V2 = V1 + M_PI + M_PI;
    }
    else
    {
      V1 = V2 = 0.0;
    }
  }
}

TopAbs_State IntTools_FClass2d::PerformInfinitePoint() const
{
  if (Umax == -RealLast() || Vmax == -RealLast() || Umin == RealLast() || Vmin == RealLast())
  {
    return (TopAbs_IN);
  }
  gp_Pnt2d P(Umin - (Umax - Umin), Vmin - (Vmax - Vmin));
  return (Perform(P, false));
}

TopAbs_State IntTools_FClass2d::Perform(const gp_Pnt2d& _Puv, const bool RecadreOnPeriodic) const
{
  int nbtabclass = TabClass.Length();
  if (nbtabclass == 0)
  {
    return TopAbs_IN;
  }

  double       u       = _Puv.X();
  double       v       = _Puv.Y();
  double       uu      = u;
  double       vv      = v;
  TopAbs_State aStatus = TopAbs_UNKNOWN;

  occ::handle<BRepAdaptor_Surface> surf = new BRepAdaptor_Surface();
  surf->Initialize(Face, false);

  const bool   IsUPer  = surf->IsUPeriodic();
  const bool   IsVPer  = surf->IsVPeriodic();
  const double uperiod = IsUPer ? surf->UPeriod() : 0.0;
  const double vperiod = IsVPer ? surf->VPeriod() : 0.0;

  bool urecadre, vrecadre, bUseClassifier;
  int  dedans = 1;

  urecadre = false;
  vrecadre = false;

  if (RecadreOnPeriodic)
  {
    double du, dv;
    if (IsUPer)
    {
      GeomInt::AdjustPeriodic(uu, Umin, Umax, uperiod, uu, du);
    }

    if (IsVPer)
    {
      GeomInt::AdjustPeriodic(vv, Vmin, Vmax, vperiod, vv, dv);
    }
  }

  for (;;)
  {
    dedans = 1;
    gp_Pnt2d Puv(u, v);
    bUseClassifier = (TabOrien(1) == -1);
    if (!bUseClassifier)
    {
      int n, cur, TabOrien_n;
      for (n = 1; n <= nbtabclass; n++)
      {
        cur        = TabClass(n).SiDans(Puv);
        TabOrien_n = TabOrien(n);

        if (cur == 1)
        {
          if (TabOrien_n == 0)
          {
            dedans = -1;
            break;
          }
        }
        else if (cur == -1)
        {
          if (TabOrien_n == 1)
          {
            dedans = -1;
            break;
          }
        }
        else
        {
          dedans = 0;
          break;
        }
      }

      if (dedans == 0)
      {
        bUseClassifier = true;
      }
      else
      {
        aStatus = (dedans == 1) ? TopAbs_IN : TopAbs_OUT;
      }
    }

    if (bUseClassifier)
    {

      double aURes, aVRes, aFCTol;
      bool   bUIn, bVIn;

      aURes = surf->UResolution(Toluv);
      aVRes = surf->VResolution(Toluv);

      bUIn = (u >= Umin) && (u <= Umax);
      bVIn = (v >= Vmin) && (v <= Vmax);

      if (bUIn == bVIn)
      {
        aFCTol = std::min(aURes, aVRes);
      }
      else
      {
        aFCTol = (!bUIn) ? aURes : aVRes;
      }

      if (myFExplorer.get() == nullptr)
        myFExplorer.reset(new BRepClass_FaceExplorer(Face));

      BRepClass_FClassifier aClassifier;
      aClassifier.Perform(*myFExplorer, Puv, aFCTol);
      aStatus = aClassifier.State();
    }

    if (!RecadreOnPeriodic || (!IsUPer && !IsVPer))
      return aStatus;

    if (aStatus == TopAbs_IN || aStatus == TopAbs_ON)
      return aStatus;

    if (!urecadre)
    {
      u        = uu;
      urecadre = true;
    }
    else
    {
      if (IsUPer)
      {
        u += uperiod;
      }
    }

    if (u > Umax || !IsUPer)
    {
      if (!vrecadre)
      {
        v        = vv;
        vrecadre = true;
      }
      else
      {
        if (IsVPer)
        {
          v += vperiod;
        }
      }

      u = uu;

      if (v > Vmax || !IsVPer)
      {
        return aStatus;
      }
    }
  }
}

TopAbs_State IntTools_FClass2d::TestOnRestriction(const gp_Pnt2d& _Puv,
                                                  const double    Tol,
                                                  const bool      RecadreOnPeriodic) const
{
  int nbtabclass = TabClass.Length();
  if (nbtabclass == 0)
  {
    return TopAbs_IN;
  }

  double u  = _Puv.X();
  double v  = _Puv.Y();
  double uu = u, vv = v;

  occ::handle<BRepAdaptor_Surface> surf = new BRepAdaptor_Surface();
  surf->Initialize(Face, false);
  const bool   IsUPer   = surf->IsUPeriodic();
  const bool   IsVPer   = surf->IsVPeriodic();
  const double uperiod  = IsUPer ? surf->UPeriod() : 0.0;
  const double vperiod  = IsVPer ? surf->VPeriod() : 0.0;
  TopAbs_State aStatus  = TopAbs_UNKNOWN;
  bool         urecadre = false, vrecadre = false;
  int          dedans = 1;

  if (RecadreOnPeriodic)
  {
    double du, dv;
    if (IsUPer)
    {
      GeomInt::AdjustPeriodic(uu, Umin, Umax, uperiod, uu, du);
    }

    if (IsVPer)
    {
      GeomInt::AdjustPeriodic(vv, Vmin, Vmax, vperiod, vv, dv);
    }
  }

  for (;;)
  {
    dedans = 1;
    gp_Pnt2d Puv(u, v);

    if (TabOrien(1) != -1)
    {
      for (int n = 1; n <= nbtabclass; n++)
      {
        int cur = TabClass(n).SiDans_OnMode(Puv, Tol);
        if (cur == 1)
        {
          if (TabOrien(n) == 0)
          {
            dedans = -1;
            break;
          }
        }
        else if (cur == -1)
        {
          if (TabOrien(n) == 1)
          {
            dedans = -1;
            break;
          }
        }
        else
        {
          dedans = 0;
          break;
        }
      }
      if (dedans == 0)
      {
        aStatus = TopAbs_ON;
      }
      if (dedans == 1)
      {
        aStatus = TopAbs_IN;
      }
      if (dedans == -1)
      {
        aStatus = TopAbs_OUT;
      }
    }
    else
    {

      if (myFExplorer.get() == nullptr)
        myFExplorer.reset(new BRepClass_FaceExplorer(Face));

      BRepClass_FClassifier aClassifier;
      aClassifier.Perform(*myFExplorer, Puv, Tol);
      aStatus = aClassifier.State();
    }

    if (!RecadreOnPeriodic || (!IsUPer && !IsVPer))
      return aStatus;
    if (aStatus == TopAbs_IN || aStatus == TopAbs_ON)
      return aStatus;

    if (!urecadre)
    {
      u        = uu;
      urecadre = true;
    }
    else if (IsUPer)
      u += uperiod;
    if (u > Umax || !IsUPer)
    {
      if (!vrecadre)
      {
        v        = vv;
        vrecadre = true;
      }
      else if (IsVPer)
        v += vperiod;

      u = uu;

      if (v > Vmax || !IsVPer)
        return aStatus;
    }
  }
}

IntTools_FClass2d::~IntTools_FClass2d()
{
  TabClass.Clear();
}
