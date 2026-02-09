#include <algorithm>
#include <memory>
#include <TopoDS_Edge.hpp>
#include <Geom_Curve.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_CurveOnSurface.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <BRep_Tool.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <gp_Lin.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Ax1.hpp>

#include <GeomAdaptor_Curve.hpp>
#include <GeomAdaptor_Surface.hpp>
#include <Precision.hpp>
#include <Extrema_ExtCC.hpp>

#include <Extrema_POnCurv.hpp>
#include <IntCurveSurface_HInter.hpp>

#include <math_FunctionSample.hpp>
#include <math_FunctionAllRoots.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Sequence.hpp>

#include <IntSurf_Quadric.hpp>
#include <math_Function.hpp>
#include <math_BrentMinimum.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>
#include <NCollection_Array1.hpp>

#ifdef OCCT_DEBUG
  #include <Geom_Circle.hpp>
  #include <Geom_Ellipse.hpp>
  #include <Geom_Hyperbola.hpp>
  #include <Geom_Parabola.hpp>
  #include <Geom_BezierCurve.hpp>
  #include <Geom_BSplineCurve.hpp>
  #include <GeomLib.hpp>
#endif

static bool IsDegenerated(const occ::handle<Adaptor3d_CurveOnSurface>& theCurve);
static bool IsDegenerated(const IntSurf_Quadric& theQuadric);

static void FindVertex(const TheArc&,
                       const occ::handle<TheTopolTool>&,
                       TheFunction&,
                       IntStart_SequenceOfPathPoint&,
                       const double);

static void BoundedArc(const TheArc&                    A,
                       const occ::handle<TheTopolTool>& Domain,
                       const double                     Pdeb,
                       const double                     Pfin,
                       TheFunction&                     Func,
                       IntStart_SequenceOfPathPoint&    pnt,
                       IntStart_SequenceOfSegment&      seg,
                       const double                     TolBoundary,
                       const double                     TolTangency,
                       bool&                            Arcsol,
                       const bool                       RecheckOnRegularity);

static void PointProcess(const gp_Pnt&,
                         const double,
                         const TheArc&,
                         const occ::handle<TheTopolTool>&,
                         IntStart_SequenceOfPathPoint&,
                         const double,
                         int&);

static int TreatLC(const TheArc&                    A,
                   const occ::handle<TheTopolTool>& aDomain,
                   const IntSurf_Quadric&           aQuadric,
                   const double                     TolBoundary,
                   IntStart_SequenceOfPathPoint&    pnt);

static bool IsRegularity(const TheArc& A, const occ::handle<TheTopolTool>& aDomain);

class MinFunction : public math_Function
{
public:
  MinFunction(TheFunction& theFunc)
      : myFunc(&theFunc) {};

  virtual bool Value(const double theX, double& theFVal)
  {
    if (!myFunc->Value(theX, theFVal))
      return false;

    theFVal *= theFVal;
    return true;
  }

  virtual int GetStateNumber() { return 0; }

private:
  TheFunction* myFunc;
};

void FindVertex(const TheArc&                    A,
                const occ::handle<TheTopolTool>& Domain,
                TheFunction&                     Func,
                IntStart_SequenceOfPathPoint&    pnt,
                const double                     Toler)
{

  TheVertex vtx;
  double    param, valf;
  int       itemp;

  Domain->Initialize(A);
  Domain->InitVertexIterator();
  while (Domain->MoreVertex())
  {
    vtx   = Domain->Vertex();
    param = TheSOBTool::Parameter(vtx, A);

    Func.Value(param, valf);
    if (std::abs(valf) <= Toler)
    {
      itemp = Func.GetStateNumber();
      pnt.Append(IntStart_ThePathPoint(Func.Valpoint(itemp), Toler, vtx, A, param));
    }
    Domain->NextVertex();
  }
}

bool IsDegenerated(const occ::handle<Adaptor3d_CurveOnSurface>& theCurve)
{
  if (theCurve->GetType() == GeomAbs_Circle)
  {
    gp_Circ aCirc = theCurve->Circle();
    if (aCirc.Radius() <= Precision::Confusion())
      return true;
  }
  return false;
}

bool IsDegenerated(const IntSurf_Quadric& theQuadric)
{
  GeomAbs_SurfaceType TypeQuad = theQuadric.TypeQuadric();
  if (TypeQuad == GeomAbs_Cone)
  {
    gp_Cone aCone      = theQuadric.Cone();
    double  aSemiAngle = std::abs(aCone.SemiAngle());
    if (aSemiAngle < 0.02 || aSemiAngle > 1.55)
      return true;
  }
  return false;
}

class SolInfo
{
public:
  SolInfo()
      : myMathIndex(-1),
        myValue(RealLast())
  {
  }

  void Init(const math_FunctionAllRoots& theSolution, const int theIndex)
  {
    myMathIndex = theIndex;
    myValue     = theSolution.GetPoint(theIndex);
  }

  void Init(const IntCurveSurface_HInter& theSolution, const int theIndex)
  {
    myMathIndex = theIndex;
    myValue     = theSolution.Point(theIndex).W();
  }

  double Value() const { return myValue; }

  int Index() const { return myMathIndex; }

  bool operator>(const SolInfo& theOther) const { return myValue > theOther.myValue; }

  bool operator<(const SolInfo& theOther) const { return myValue < theOther.myValue; }

  bool operator==(const SolInfo& theOther) const { return myValue == theOther.myValue; }

  double& ChangeValue() { return myValue; }

private:
  int    myMathIndex;
  double myValue;
};

static void BoundedArc(const TheArc&                    A,
                       const occ::handle<TheTopolTool>& Domain,
                       const double                     Pdeb,
                       const double                     Pfin,
                       TheFunction&                     Func,
                       IntStart_SequenceOfPathPoint&    pnt,
                       IntStart_SequenceOfSegment&      seg,
                       const double                     TolBoundary,
                       const double                     TolTangency,
                       bool&                            Arcsol,
                       const bool                       RecheckOnRegularity)
{

  int i, Nbi = 0, Nbp = 0;

  gp_Pnt ptdeb, ptfin;
  double pardeb = 0., parfin = 0.;
  int    ideb, ifin, range, ranged, rangef;

  double EpsX = 1.e-10;

  int NbEchant = Func.NbSamples();
  if (NbEchant < 100)
    NbEchant = 100;

  double nTolTangency = TolTangency;
  if ((Pfin - Pdeb) < (TolTangency * 10.0))
  {
    nTolTangency = (Pfin - Pdeb) * 0.1;
  }
  if (EpsX > (nTolTangency + nTolTangency))
  {
    EpsX = nTolTangency * 0.1;
  }

  double para = 0, dist, maxdist;

  bool   Rejection = true;
  double maxdr, maxr, minr, ur, dur;
  minr  = RealLast();
  maxr  = -minr;
  maxdr = -minr;
  dur   = (Pfin - Pdeb) * 0.2;
  for (i = 1, ur = Pdeb; i <= 6; i++)
  {
    double F, D;
    if (Func.Values(ur, F, D))
    {
      double lminr, lmaxr;
      if (D < 0.0)
        D = -D;
      D *= dur + dur;
      if (D > maxdr)
        maxdr = D;
      lminr = F - D;
      lmaxr = F + D;
      if (lminr < minr)
        minr = lminr;
      if (lmaxr > maxr)
        maxr = lmaxr;
      if (minr < 0.0 && maxr > 0.0)
      {
        Rejection = false;
        break;
      }
    }
    ur += dur;
  }
  if (Rejection)
  {
    dur = 0.001 + maxdr + (maxr - minr) * 0.1;
    minr -= dur;
    maxr += dur;
    if (minr < 0.0 && maxr > 0.0)
    {
      Rejection = false;
    }
  }

  Arcsol = false;

  if (Rejection == false)
  {
    const IntSurf_Quadric& aQuadric = Func.Quadric();
    GeomAbs_SurfaceType    TypeQuad = aQuadric.TypeQuadric();
    GeomAbs_CurveType      TypeConS = GeomAbs_OtherCurve;

    IntCurveSurface_HInter       IntCS;
    bool                         IsIntCSdone = false;
    NCollection_Sequence<double> Params;

    std::unique_ptr<math_FunctionAllRoots> pSol;

    math_FunctionSample Echant(Pdeb, Pfin, NbEchant);

    bool aelargir = true;

    maxdist = TolBoundary + TolTangency;

    for (i = 1; i <= NbEchant && aelargir; i++)
    {
      double u = Echant.GetParameter(i);
      if (Func.Value(u, dist))
      {
        if (dist > maxdist || -dist > maxdist)
        {
          aelargir = false;
        }
      }
    }
    if (!(aelargir && maxdist < 0.01))
    {
      maxdist = TolBoundary;
    }

    if (TypeQuad != GeomAbs_OtherSurface)
    {

      occ::handle<Adaptor3d_Surface> aSurf = Func.Surface();
      Adaptor3d_CurveOnSurface       ConS(A, aSurf);
      TypeConS = ConS.GetType();
#ifdef OCCT_DEBUG
      occ::handle<Geom_Curve> CurveConS;
      switch (TypeConS)
      {
        case GeomAbs_Line:
        {
          CurveConS = new Geom_Line(ConS.Line());
          break;
        }
        case GeomAbs_Circle:
        {
          CurveConS = new Geom_Circle(ConS.Circle());
          break;
        }
        case GeomAbs_Ellipse:
        {
          CurveConS = new Geom_Ellipse(ConS.Ellipse());
          break;
        }
        case GeomAbs_Hyperbola:
        {
          CurveConS = new Geom_Hyperbola(ConS.Hyperbola());
          break;
        }
        case GeomAbs_Parabola:
        {
          CurveConS = new Geom_Parabola(ConS.Parabola());
          break;
        }
        case GeomAbs_BezierCurve:
        {
          CurveConS = ConS.Bezier();
          break;
        }
        case GeomAbs_BSplineCurve:
        {
          CurveConS = ConS.BSpline();
          break;
        }
        default:
        {
          double MaxDeviation, AverageDeviation;
          GeomLib::BuildCurve3d(1.e-5,
                                ConS,
                                ConS.FirstParameter(),
                                ConS.LastParameter(),
                                CurveConS,
                                MaxDeviation,
                                AverageDeviation);
          break;
        }
      }
#endif
      occ::handle<Adaptor3d_CurveOnSurface> HConS = new Adaptor3d_CurveOnSurface(ConS);
      occ::handle<Geom_Surface>             QuadSurf;
      switch (TypeQuad)
      {
        case GeomAbs_Plane:
        {
          QuadSurf = new Geom_Plane(aQuadric.Plane());
          break;
        }
        case GeomAbs_Cylinder:
        {
          QuadSurf = new Geom_CylindricalSurface(aQuadric.Cylinder());
          break;
        }
        case GeomAbs_Cone:
        {
          QuadSurf = new Geom_ConicalSurface(aQuadric.Cone());
          break;
        }
        case GeomAbs_Sphere:
        {
          QuadSurf = new Geom_SphericalSurface(aQuadric.Sphere());
          break;
        }
        case GeomAbs_Torus:
        {
          QuadSurf = new Geom_ToroidalSurface(aQuadric.Torus());
          break;
        }
        default:
          break;
      }
      occ::handle<GeomAdaptor_Surface> GAHsurf = new GeomAdaptor_Surface(QuadSurf);

      if ((TypeConS == GeomAbs_Line || TypeConS == GeomAbs_Circle || TypeConS == GeomAbs_Ellipse
           || TypeConS == GeomAbs_Parabola || TypeConS == GeomAbs_Hyperbola)
          && TypeQuad != GeomAbs_Torus && !IsDegenerated(HConS) && !IsDegenerated(aQuadric))
      {

        IntCS.Perform(HConS, GAHsurf);
      }

      IsIntCSdone = IntCS.IsDone();
      if (IsIntCSdone)
      {
        Nbp = IntCS.NbPoints();
        Nbi = IntCS.NbSegments();
      }

      if (Nbp == 0 && Nbi == 0)
        IsIntCSdone = false;
    }

    if (!IsIntCSdone)
    {
      pSol.reset(new math_FunctionAllRoots(Func, Echant, EpsX, maxdist, maxdist));

      if (!pSol->IsDone())
      {
        throw Standard_Failure();
      }

      Nbp = pSol->NbPoints();
    }

    if (RecheckOnRegularity && Nbp > 0 && IsRegularity(A, Domain))
    {

      double                theTol = 5.e-4;
      math_FunctionAllRoots SolAgain(Func, Echant, EpsX, theTol, theTol);

      if (!SolAgain.IsDone())
      {
        throw Standard_Failure();
      }

      int Nbi_again = SolAgain.NbIntervals();

      if (Nbi_again > 0)
      {
        int    NbSamples     = 10;
        double delta         = (Pfin - Pdeb) / NbSamples;
        double GlobalTol     = theTol * 10;
        bool   SolOnBoundary = true;
        for (i = 0; i <= NbSamples; i++)
        {
          double aParam = Pdeb + i * delta;
          double aValue;
          Func.Value(aParam, aValue);
          if (std::abs(aValue) > GlobalTol)
          {
            SolOnBoundary = false;
            break;
          }
        }

        if (SolOnBoundary)
        {
          for (i = 1; i <= Nbi_again; i++)
          {
            IntStart_TheSegment newseg;
            newseg.SetValue(A);

            SolAgain.GetInterval(i, pardeb, parfin);

            if (std::abs(pardeb - Pdeb) <= Precision::PConfusion())
              pardeb = Pdeb;
            if (std::abs(parfin - Pfin) <= Precision::PConfusion())
              parfin = Pfin;

            SolAgain.GetIntervalState(i, ideb, ifin);

            ptdeb = Func.Valpoint(ideb);
            ptfin = Func.Valpoint(ifin);

            PointProcess(ptdeb, pardeb, A, Domain, pnt, theTol, ranged);
            newseg.SetLimitPoint(pnt.Value(ranged), true);
            PointProcess(ptfin, parfin, A, Domain, pnt, theTol, rangef);
            newseg.SetLimitPoint(pnt.Value(rangef), false);
            seg.Append(newseg);
          }
          Arcsol = true;
          return;
        }
      }
    }

    if (Nbp)
    {
      NCollection_Array1<SolInfo> aSI(1, Nbp);

      for (i = 1; i <= Nbp; i++)
      {
        if (IsIntCSdone)
          aSI(i).Init(IntCS, i);
        else
          aSI(i).Init(*pSol, i);
      }

      std::sort(aSI.begin(), aSI.end());

      int ip = TreatLC(A, Domain, aQuadric, TolBoundary, pnt);
      if (ip)
      {

        for (i = 1; i < Nbp; i++)
        {
          double parap1 = aSI(i + 1).Value();
          para          = aSI(i).Value();

          double param = (para + parap1) * 0.5;
          double yf    = 0.0;
          double ym    = 0.0;
          double yl    = 0.0;
          if (Func.Value(param, ym) && std::abs(ym) < maxdist)
          {
            double sm    = std::copysign(1., ym);
            bool   aTang = Func.Value(para, yf) && Func.Value(parap1, yl);
            if (aTang)
            {

              aTang = aTang && std::abs(yf) < maxdist && std::abs(yl) < maxdist;
            }
            if (aTang && IsIntCSdone && TypeConS == GeomAbs_Line)
            {

              double sf = std::copysign(1., yf), sl = std::copysign(1., yl);
              aTang = aTang && (sm == sf) && (sm == sl);
            }
            if (aTang)
            {

              double aTol = TolBoundary * 1000.0;
              if (aTol > 0.001)
                aTol = 0.001;

              parap1 = (std::abs(parap1) < 1.e9) ? parap1 : ((parap1 >= 0.) ? 1.e9 : -1.e9);
              para   = (std::abs(para) < 1.e9) ? para : ((para >= 0.) ? 1.e9 : -1.e9);

              int aNbNodes = RealToInt(std::ceil((parap1 - para) / aTol));

              double aVal    = RealLast();
              double aValMax = 0.;

              double aDelta = (parap1 - para) / (aNbNodes + 1.);
              int    ii;
              double aCurPar;
              double aCurVal;

              for (ii = 0; ii <= aNbNodes + 1; ii++)
              {
                aCurPar = (ii < aNbNodes + 1) ? para + ii * aDelta : parap1;

                if (Func.Value(aCurPar, aCurVal))
                {
                  double anAbsVal = std::abs(aCurVal);
                  if (anAbsVal < aVal)
                  {
                    aVal  = anAbsVal;
                    param = aCurPar;
                  }
                  if (anAbsVal > aValMax)
                  {
                    aValMax = anAbsVal;
                  }
                }
              }

              if (IsIntCSdone && aNbNodes > 1)
              {
                aTang = std::abs(param - para) > EpsX && std::abs(parap1 - param) > EpsX
                        && 0.01 * aValMax <= aVal;
              }
              if (aTang)
              {
                aSI(i).ChangeValue()     = Pdeb - 1;
                aSI(i + 1).ChangeValue() = param;
              }
            }
          }
        }

        for (i = 1; i <= Nbp; i++)
        {
          para = aSI(i).Value();
          if ((para - Pdeb) < EpsX || (Pfin - para) < EpsX)
            continue;

          if (!Func.Value(para, dist))
            continue;

          dist = std::abs(dist);

          int anIndx = -1;

          const double aParam = aSI(i).Value();
          if (dist < maxdist)
          {
            if (!IsIntCSdone
                && (std::abs(aParam - Pdeb) <= Precision::PConfusion()
                    || std::abs(aParam - Pfin) <= Precision::PConfusion()))
            {
              anIndx = pSol->GetPointState(aSI(i).Index());
            }
          }

          gp_Pnt aPnt(anIndx < 0 ? Func.LastComputedPoint() : Func.Valpoint(anIndx));

          if (dist > 0.1 * Precision::Confusion())
          {

            const double aFPar = (i == 1) ? Pdeb : (para + aSI(i - 1).Value()) / 2.0;
            const double aLPar = (i == Nbp) ? Pfin : (para + aSI(i + 1).Value()) / 2.0;

            MinFunction       aNewFunc(Func);
            math_BrentMinimum aMin(Precision::Confusion());

            aMin.Perform(aNewFunc, aFPar, para, aLPar);
            if (aMin.IsDone())
            {
              para = aMin.Location();
              const gp_Pnt2d aP2d(A->Value(para));
              aPnt = Func.Surface()->Value(aP2d.X(), aP2d.Y());
            }
          }

          PointProcess(aPnt, para, A, Domain, pnt, TolBoundary, range);
        }
      }
    }

    if (!IsIntCSdone)
      Nbi = pSol->NbIntervals();

    if (!RecheckOnRegularity && Nbp)
    {

      Nbi = 0;
    }

    for (i = 1; i <= Nbi; i++)
    {
      IntStart_TheSegment newseg;
      newseg.SetValue(A);

      if (IsIntCSdone)
      {
        IntCurveSurface_IntersectionSegment IntSeg = IntCS.Segment(i);
        IntCurveSurface_IntersectionPoint   End1   = IntSeg.FirstPoint();
        IntCurveSurface_IntersectionPoint   End2   = IntSeg.SecondPoint();
        pardeb                                     = End1.W();
        parfin                                     = End2.W();
        ptdeb                                      = End1.Pnt();
        ptfin                                      = End2.Pnt();
      }
      else
      {
        pSol->GetInterval(i, pardeb, parfin);
        pSol->GetIntervalState(i, ideb, ifin);

        ptdeb = Func.Valpoint(ideb);
        ptfin = Func.Valpoint(ifin);
      }

      PointProcess(ptdeb, pardeb, A, Domain, pnt, TolBoundary, ranged);
      newseg.SetLimitPoint(pnt.Value(ranged), true);
      PointProcess(ptfin, parfin, A, Domain, pnt, TolBoundary, rangef);
      newseg.SetLimitPoint(pnt.Value(rangef), false);
      seg.Append(newseg);
    }

    if (Nbi == 1)
    {
      if ((std::abs(pardeb - Pdeb) < Precision::PConfusion())
          && (std::abs(parfin - Pfin) < Precision::PConfusion()))
      {
        Arcsol = true;
      }
    }
  }
}

void ComputeBoundsfromInfinite(TheFunction& Func, double& PDeb, double& PFin, int& NbEchant)
{

  NbEchant = 100;

  double U0 = 0.0;
  double dU = 0.001;
  double Dist0, Dist1;

  Func.Value(U0, Dist0);
  Func.Value(U0 + dU, Dist1);
  double dDist = Dist1 - Dist0;
  if (dDist)
  {
    U0 -= dU * Dist0 / dDist;
    PDeb = PFin = U0;
    double Umin = U0 - 1e5;
    Func.Value(Umin, Dist0);
    Func.Value(Umin + dU, Dist1);
    dDist = Dist1 - Dist0;
    if (dDist)
    {
      Umin -= dU * Dist0 / dDist;
    }
    else
    {
      Umin -= 10.0;
    }
    double Umax = U0 + 1e8;
    Func.Value(Umax, Dist0);
    Func.Value(Umax + dU, Dist1);
    dDist = Dist1 - Dist0;
    if (dDist)
    {
      Umax -= dU * Dist0 / dDist;
    }
    else
    {
      Umax += 10.0;
    }
    if (Umin > U0)
    {
      Umin = U0 - 10.0;
    }
    if (Umax < U0)
    {
      Umax = U0 + 10.0;
    }

    PFin = Umax + 10. * (Umax - Umin);
    PDeb = Umin - 10. * (Umax - Umin);
  }
  else
  {

    PDeb = 1e10;
    PFin = -1e10;
  }
}

void PointProcess(const gp_Pnt&                    Pt,
                  const double                     Para,
                  const TheArc&                    A,
                  const occ::handle<TheTopolTool>& Domain,
                  IntStart_SequenceOfPathPoint&    pnt,
                  const double                     Tol,
                  int&                             Range)
{

  int    k;
  bool   found, goon;
  double dist, toler;

  int                   Nbsol = pnt.Length();
  TheVertex             vtx;
  IntStart_ThePathPoint ptsol;

  Domain->Initialize(A);
  Domain->InitVertexIterator();
  found = false;
  goon  = Domain->MoreVertex();
  while (goon)
  {
    vtx   = Domain->Vertex();
    dist  = std::abs(Para - TheSOBTool::Parameter(vtx, A));
    toler = TheSOBTool::Tolerance(vtx, A);
#ifdef OCCT_DEBUG
    if (toler > 0.1)
    {
      std::cout << "IntStart_SearchOnBoundaries_1.gxx  : ** WARNING ** Tol Vertex=" << toler
                << std::endl;
      std::cout << "                                     Ou Edge degenere Ou Kro pointu"
                << std::endl;
      if (toler > 10000)
        toler = 1e-7;
    }
#endif

    if (dist <= toler)
    {

      k     = 1;
      found = (k > Nbsol);
      while (!found)
      {
        ptsol = pnt.Value(k);
        if (!ptsol.IsNew())
        {

          if (Domain->Identical(ptsol.Vertex(), vtx) && ptsol.Arc() == A
              && std::abs(ptsol.Parameter() - Para) <= toler)
          {
            found = true;
          }
          else
          {
            k     = k + 1;
            found = (k > Nbsol);
          }
        }
        else
        {
          k     = k + 1;
          found = (k > Nbsol);
        }
      }
      if (k <= Nbsol)
      {
        Range = k;
      }
      else
      {
        ptsol.SetValue(Pt, Tol, vtx, A, Para);
        pnt.Append(ptsol);
        Range = pnt.Length();
      }
      found = true;
      goon  = false;
    }
    else
    {
      Domain->NextVertex();
      goon = Domain->MoreVertex();
    }
  }

  if (!found)
  {

    bool found_internal = false;
    for (k = 1; k <= pnt.Length(); k++)
    {
      ptsol = pnt.Value(k);
      if (ptsol.Arc() != A || !ptsol.IsNew())
        continue;
      if (std::abs(ptsol.Parameter() - Para) <= Precision::PConfusion())
      {
        found_internal = true;
        Range          = k;
      }
    }

    if (!found_internal)
    {
      double TOL = Tol;
      TOL *= 1000.0;

      if (TOL > 0.005)
        TOL = 0.005;

      ptsol.SetValue(Pt, TOL, A, Para);
      pnt.Append(ptsol);
      Range = pnt.Length();
    }
  }
}

bool IsRegularity(const TheArc&, const occ::handle<TheTopolTool>& aDomain)
{
  void* anEAddress = aDomain->Edge();
  if (anEAddress == NULL)
  {
    return false;
  }

  TopoDS_Edge* anE = (TopoDS_Edge*)anEAddress;

  return (BRep_Tool::HasContinuity(*anE));
}

int TreatLC(const TheArc&                    A,
            const occ::handle<TheTopolTool>& aDomain,
            const IntSurf_Quadric&           aQuadric,
            const double                     TolBoundary,
            IntStart_SequenceOfPathPoint&    pnt)
{
  int anExitCode = 1, aNbExt;

  void* anEAddress = aDomain->Edge();
  if (anEAddress == NULL)
  {
    return anExitCode;
  }

  TopoDS_Edge* anE = (TopoDS_Edge*)anEAddress;

  if (BRep_Tool::Degenerated(*anE))
  {
    return anExitCode;
  }

  GeomAbs_CurveType aTypeE;
  BRepAdaptor_Curve aBAC(*anE);
  aTypeE = aBAC.GetType();

  if (aTypeE != GeomAbs_Line)
  {
    return anExitCode;
  }

  GeomAbs_SurfaceType aTypeS;
  aTypeS = aQuadric.TypeQuadric();

  if (aTypeS != GeomAbs_Cylinder)
  {
    return anExitCode;
  }

  double                  f, l, U1f, U1l, U2f, U2l, UEgde, TOL, aDist, aR, aRRel, Tol;
  occ::handle<Geom_Curve> aCEdge = BRep_Tool::Curve(*anE, f, l);

  gp_Cylinder            aCyl  = aQuadric.Cylinder();
  const gp_Ax1&          anAx1 = aCyl.Axis();
  gp_Lin                 aLin(anAx1);
  occ::handle<Geom_Line> aCAxis = new Geom_Line(aLin);
  aR                            = aCyl.Radius();

  U1f = aCAxis->FirstParameter();
  U1l = aCAxis->LastParameter();

  U2f = aCEdge->FirstParameter();
  U2l = aCEdge->LastParameter();

  GeomAdaptor_Curve C1, C2;

  C1.Load(aCAxis);
  C2.Load(aCEdge);

  Tol = Precision::PConfusion();

  Extrema_ExtCC anExtCC(C1, C2, U1f, U1l, U2f, U2l, Tol, Tol);

  aNbExt = anExtCC.NbExt();
  if (aNbExt != 1)
  {
    return anExitCode;
  }

  gp_Pnt          P1, PEdge;
  Extrema_POnCurv PC1, PC2;

  anExtCC.Points(1, PC1, PC2);

  P1    = PC1.Value();
  PEdge = PC2.Value();

  UEgde = PC2.Parameter();

  aDist = PEdge.Distance(P1);
  aRRel = fabs(aDist - aR) / aR;
  if (aRRel > TolBoundary)
  {
    return anExitCode;
  }

  if (UEgde < (f + TolBoundary) || UEgde > (l - TolBoundary))
  {
    return anExitCode;
  }

  TOL = 1000. * TolBoundary;
  if (TOL > 0.001)
    TOL = 0.001;

  IntStart_ThePathPoint ptsol;
  ptsol.SetValue(PEdge, TOL, A, UEgde);
  pnt.Append(ptsol);

  anExitCode = 0;
  return anExitCode;
}

IntStart_SearchOnBoundaries::IntStart_SearchOnBoundaries()
    : done(false),
      all(false)
{
}

void IntStart_SearchOnBoundaries::Perform(TheFunction&                     Func,
                                          const occ::handle<TheTopolTool>& Domain,
                                          const double                     TolBoundary,
                                          const double                     TolTangency,
                                          const bool                       RecheckOnRegularity)
{

  done = false;
  spnt.Clear();
  sseg.Clear();

  bool   Arcsol;
  double PDeb, PFin, prm, tol;
  int    i, nbknown, nbfound, index;
  gp_Pnt pt;

  Domain->Init();

  if (Domain->More())
  {
    all = true;
  }
  else
  {
    all = false;
  }

  while (Domain->More())
  {
    TheArc A = Domain->Value();
    if (!TheSOBTool::HasBeenSeen(A))
    {
      Func.Set(A);
      FindVertex(A, Domain, Func, spnt, TolBoundary);
      TheSOBTool::Bounds(A, PDeb, PFin);
      if (Precision::IsNegativeInfinite(PDeb) || Precision::IsPositiveInfinite(PFin))
      {
        int NbEchant;
        ComputeBoundsfromInfinite(Func, PDeb, PFin, NbEchant);
      }
      BoundedArc(A,
                 Domain,
                 PDeb,
                 PFin,
                 Func,
                 spnt,
                 sseg,
                 TolBoundary,
                 TolTangency,
                 Arcsol,
                 RecheckOnRegularity);
      all = (all && Arcsol);
    }

    else
    {

      nbfound = spnt.Length();

      nbknown = TheSOBTool::NbPoints(A);
      for (i = 1; i <= nbknown; i++)
      {
        TheSOBTool::Value(A, i, pt, tol, prm);
        if (TheSOBTool::IsVertex(A, i))
        {
          TheVertex vtx;
          TheSOBTool::Vertex(A, i, vtx);
          spnt.Append(IntStart_ThePathPoint(pt, tol, vtx, A, prm));
        }
        else
        {
          spnt.Append(IntStart_ThePathPoint(pt, tol, A, prm));
        }
      }

      nbknown = TheSOBTool::NbSegments(A);
      for (i = 1; i <= nbknown; i++)
      {
        IntStart_TheSegment newseg;
        newseg.SetValue(A);
        if (TheSOBTool::HasFirstPoint(A, i, index))
        {
          newseg.SetLimitPoint(spnt.Value(nbfound + index), true);
        }
        if (TheSOBTool::HasLastPoint(A, i, index))
        {
          newseg.SetLimitPoint(spnt.Value(nbfound + index), false);
        }
        sseg.Append(newseg);
      }
      all = (all & TheSOBTool::IsAllSolution(A));
    }
    Domain->Next();
  }
  done = true;
}
