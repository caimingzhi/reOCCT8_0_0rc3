

#include <Adaptor2d_Curve2d.hpp>
#include <Adaptor3d_HVertex.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_TopolTool.hpp>
#include <Bnd_Box2d.hpp>
#include <Bnd_Range.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Extrema_ExtPC.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <Geom_Ellipse.hpp>
#include <Geom_Hyperbola.hpp>
#include <Geom_Parabola.hpp>
#include <IntAna_IntQuadQuad.hpp>
#include <IntAna_Curve.hpp>
#include <NCollection_List.hpp>
#include <IntAna_QuadQuadGeo.hpp>
#include <IntAna_Quadric.hpp>
#include <IntPatch_ALine.hpp>
#include <IntPatch_ArcFunction.hpp>
#include <IntPatch_GLine.hpp>
#include <IntPatch_HInterTool.hpp>
#include <IntPatch_ImpImpIntersection.hpp>
#include <IntPatch_RLine.hpp>
#include <IntPatch_ThePathPointOfTheSOnBounds.hpp>
#include <IntPatch_TheSegmentOfTheSOnBounds.hpp>
#include <IntPatch_WLine.hpp>
#include <IntSurf.hpp>
#include <NCollection_IncAllocator.hpp>
#include <Standard_DivideByZero.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Sequence.hpp>
#include <gce_MakeLin.hpp>
#include <gp.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Pln.hpp>
#include <gp_Sphere.hpp>
#include <math_Matrix.hpp>
#include <math_Vector.hpp>

#include <algorithm>

static void PutPointsOnLine(const occ::handle<Adaptor3d_Surface>& S1,
                            const occ::handle<Adaptor3d_Surface>& S2,
                            const NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>&,
                            const NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                            const bool,
                            const occ::handle<Adaptor3d_TopolTool>&,
                            const IntSurf_Quadric&,
                            const IntSurf_Quadric&,
                            const bool,
                            const double);

static bool MultiplePoint(const NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>& listpnt,
                          const occ::handle<Adaptor3d_TopolTool>&                          Domain,
                          const IntSurf_Quadric&                                           QuadSurf,
                          const gp_Vec&                                                    Normale,
                          const NCollection_Sequence<occ::handle<IntPatch_Line>>&          slin,
                          NCollection_Array1<int>&                                         Done,
                          NCollection_Array1<int>&                                         UsedLine,
                          const int                                                        Index,
                          const bool                                                       OnFirst,
                          const double theToler);

static bool PointOnSecondDom(
  const NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>& listpnt,
  const occ::handle<Adaptor3d_TopolTool>&                          Domain,
  const IntSurf_Quadric&                                           QuadSurf,
  const gp_Vec&                                                    Normale,
  const gp_Vec&                                                    Vtgint,
  const occ::handle<IntPatch_Line>&                                lin,
  NCollection_Array1<int>&                                         Done,
  const int                                                        Index,
  const double                                                     theToler);

static bool SingleLine(const gp_Pnt&,
                       const occ::handle<IntPatch_Line>&,
                       const double,
                       double&,
                       gp_Vec&);

static bool FindLine(gp_Pnt&                                                 Psurf,
                     const NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
                     const double                                            Tol,
                     NCollection_List<double>&                               theLParams,
                     gp_Vec&                                                 Vtgtint,
                     int&                                                    theLineIdx,
                     int                                                     OnlyThisLine,
                     const occ::handle<Adaptor2d_Curve2d>&                   thearc,
                     double&                                                 theparameteronarc,
                     gp_Pnt&                                                 thepointonarc,
                     const IntSurf_Quadric&                                  QuadSurf1,
                     const IntSurf_Quadric&                                  QuadSurf2,
                     double&                                                 theOutputToler);

static void ProcessSegments(const NCollection_Sequence<IntPatch_TheSegmentOfTheSOnBounds>&,
                            NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                            const IntSurf_Quadric&,
                            const IntSurf_Quadric&,
                            const bool,
                            const double);

static void ProcessRLine(NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                         const IntSurf_Quadric&,
                         const IntSurf_Quadric&,
                         const double,
                         const bool theIsReqToKeepRLine);

bool IntersectionWithAnArc(gp_Pnt&                               PSurf,
                           const occ::handle<IntPatch_ALine>&    alin,
                           double&                               para,
                           const occ::handle<Adaptor2d_Curve2d>& thearc,
                           double&                               _theparameteronarc,
                           gp_Pnt&                               thepointonarc,
                           const IntSurf_Quadric&                QuadSurf,
                           const double                          u0alin,
                           const double                          u1alin)
{
  double dtheta, theta;
#ifdef OCCT_DEBUG

#endif

  dtheta    = (u1alin - u0alin) * 0.01;
  double du = 0.000000001;
  if (du >= dtheta)
    du = dtheta / 2;
  double distmin = RealLast();

  double thetamin = 0.;

  double theparameteronarc = _theparameteronarc;
  for (double _theta = u0alin + dtheta; _theta <= u1alin - dtheta; _theta += dtheta)
  {
    gp_Pnt P = alin->Value(_theta);
    double d = P.Distance(PSurf);
    if (d < distmin)
    {
      thetamin = _theta;
      distmin  = d;
    }
  }

  double bestpara = 0., besttheta = 0., bestdist = 0., distinit = 0.;

  {
    gp_Pnt pp0 = alin->Value(thetamin);
    double ua0, va0;
    QuadSurf.Parameters(pp0, ua0, va0);
    gp_Pnt2d p2d;
    gp_Vec2d d2d;
    thearc->D1(theparameteronarc, p2d, d2d);
    gp_Vec2d PaPr(gp_Pnt2d(ua0, va0), p2d);
    distinit = PaPr.Magnitude();
  }
  theta = thetamin;

  bool   cpasok = true;
  int    nbiter = 0;
  double drmax  = (thearc->LastParameter() - thearc->FirstParameter()) * 0.05;
  double damax  = (u1alin - u0alin) * 0.05;

  bestdist = RealLast();

  do
  {
    double ua0, va0, ua1, va1;

    gp_Pnt pp0 = alin->Value(theta);
    gp_Pnt pp1 = alin->Value(theta + du);
    QuadSurf.Parameters(pp0, ua0, va0);
    QuadSurf.Parameters(pp1, ua1, va1);

    gp_Vec2d D1a((ua1 - ua0) / du, (va1 - va0) / du);
    gp_Pnt2d p2d;
    gp_Vec2d d2d;
    thearc->D1(theparameteronarc, p2d, d2d);
    gp_Vec2d PaPr(gp_Pnt2d(ua0, va0), p2d);

    double pbd = PaPr.Magnitude();
    if (bestdist > pbd)
    {
      bestdist  = pbd;
      bestpara  = theparameteronarc;
      besttheta = theta;
    }

    D1a.SetCoord(-D1a.X(), -D1a.Y());

    double d = D1a.X() * d2d.Y() - D1a.Y() * d2d.X();

    double da = (-PaPr.X()) * d2d.Y() - (-PaPr.Y()) * d2d.X();
    double dr = D1a.X() * (-PaPr.Y()) - D1a.Y() * (-PaPr.X());
    if (std::abs(d) > 1e-15)
    {
      da /= d;
      dr /= d;
    }
    else
    {
      if (std::abs(PaPr.X()) > std::abs(PaPr.Y()))
      {
        double xx = PaPr.X();
        xx *= 0.5;
        if (D1a.X())
        {
          da = -xx / D1a.X();
        }
        if (d2d.X())
        {
          dr = -xx / d2d.X();
        }
      }
      else
      {
        double yy = PaPr.Y();
        yy *= 0.5;
        if (D1a.Y())
        {
          da = -yy / D1a.Y();
        }
        if (d2d.Y())
        {
          dr = -yy / d2d.Y();
        }
      }
    }

    if (da < -damax)
      da = -damax;
    else if (da > damax)
      da = damax;
    if (dr < -drmax)
      dr = -drmax;
    else if (dr > drmax)
      dr = drmax;

    if (std::abs(da) < 1e-10 && std::abs(dr) < 1e-10)
    {
      para               = theta;
      PSurf              = alin->Value(para);
      _theparameteronarc = theparameteronarc;
      thepointonarc      = alin->Value(para);
      cpasok             = false;

      return (true);
    }
    else
    {
      theta += da;
      theparameteronarc += dr;
      if (theparameteronarc > thearc->LastParameter())
      {
        theparameteronarc = thearc->LastParameter();
      }
      if (theparameteronarc < thearc->FirstParameter())
      {
        theparameteronarc = thearc->FirstParameter();
      }
      if (theta < u0alin)
      {
        theta = u0alin;
      }
      if (theta > u1alin - du)
      {
        theta = u1alin - du - du;
      }
    }
    nbiter++;
  } while (cpasok && nbiter < 20);
  if (bestdist < distinit)
  {
    para               = besttheta;
    PSurf              = alin->Value(para);
    _theparameteronarc = bestpara;
    thepointonarc      = alin->Value(para);

    return (true);
  }

  return (false);
}

static void Recadre(const occ::handle<Adaptor3d_Surface>& myHS1,
                    const occ::handle<Adaptor3d_Surface>& myHS2,
                    double&                               u1,
                    double&                               v1,
                    double&                               u2,
                    double&                               v2)
{
  double              f, l, lmf, fpls2;
  GeomAbs_SurfaceType typs1 = myHS1->GetType();
  GeomAbs_SurfaceType typs2 = myHS2->GetType();

  bool myHS1IsUPeriodic, myHS1IsVPeriodic;
  switch (typs1)
  {
    case GeomAbs_Cylinder:
    case GeomAbs_Cone:
    case GeomAbs_Sphere:
    {
      myHS1IsUPeriodic = true;
      myHS1IsVPeriodic = false;
      break;
    }
    case GeomAbs_Torus:
    {
      myHS1IsUPeriodic = myHS1IsVPeriodic = true;
      break;
    }
    default:
    {

      myHS1IsUPeriodic = myHS1IsVPeriodic = false;
      break;
    }
  }

  bool myHS2IsUPeriodic, myHS2IsVPeriodic;
  switch (typs2)
  {
    case GeomAbs_Cylinder:
    case GeomAbs_Cone:
    case GeomAbs_Sphere:
    {
      myHS2IsUPeriodic = true;
      myHS2IsVPeriodic = false;
      break;
    }
    case GeomAbs_Torus:
    {
      myHS2IsUPeriodic = myHS2IsVPeriodic = true;
      break;
    }
    default:
    {

      myHS2IsUPeriodic = myHS2IsVPeriodic = false;
      break;
    }
  }
  if (myHS1IsUPeriodic)
  {
    lmf   = M_PI + M_PI;
    f     = myHS1->FirstUParameter();
    l     = myHS1->LastUParameter();
    fpls2 = 0.5 * (f + l);
    while ((u1 < f) && ((fpls2 - u1) > (u1 + lmf - fpls2)))
    {
      u1 += lmf;
    }
    while ((u1 > l) && ((u1 - fpls2) > (fpls2 - (u1 - lmf))))
    {
      u1 -= lmf;
    }
  }
  if (myHS1IsVPeriodic)
  {
    lmf   = M_PI + M_PI;
    f     = myHS1->FirstVParameter();
    l     = myHS1->LastVParameter();
    fpls2 = 0.5 * (f + l);
    while ((v1 < f) && ((fpls2 - v1) > (v1 + lmf - fpls2)))
    {
      v1 += lmf;
    }
    while ((v1 > l) && ((v1 - fpls2) > (fpls2 - (v1 - lmf))))
    {
      v1 -= lmf;
    }
  }
  if (myHS2IsUPeriodic)
  {
    lmf   = M_PI + M_PI;
    f     = myHS2->FirstUParameter();
    l     = myHS2->LastUParameter();
    fpls2 = 0.5 * (f + l);
    while ((u2 < f) && ((fpls2 - u2) > (u2 + lmf - fpls2)))
    {
      u2 += lmf;
    }
    while ((u2 > l) && ((u2 - fpls2) > (fpls2 - (u2 - lmf))))
    {
      u2 -= lmf;
    }
  }
  if (myHS2IsVPeriodic)
  {
    lmf   = M_PI + M_PI;
    f     = myHS2->FirstVParameter();
    l     = myHS2->LastVParameter();
    fpls2 = 0.5 * (f + l);
    while ((v2 < f) && ((fpls2 - v2) > (v2 + lmf - fpls2)))
    {
      v2 += lmf;
    }
    while ((v2 > l) && ((v2 - fpls2) > (fpls2 - (v2 - lmf))))
    {
      v2 -= lmf;
    }
  }
}

void PutPointsOnLine(const occ::handle<Adaptor3d_Surface>&                            S1,
                     const occ::handle<Adaptor3d_Surface>&                            S2,
                     const NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>& listpnt,
                     const NCollection_Sequence<occ::handle<IntPatch_Line>>&          slin,
                     const bool                                                       OnFirst,
                     const occ::handle<Adaptor3d_TopolTool>&                          Domain,
                     const IntSurf_Quadric&                                           QuadSurf,
                     const IntSurf_Quadric&                                           OtherQuad,
                     const bool                                                       multpoint,
                     const double                                                     Tolarc)
{

  int nbpnt = listpnt.Length();
  int nblin = slin.Length();

  if (!slin.Length() || !nbpnt)
  {
    return;
  }

  int    i, k;
  int    linenumber;
  double currentparameter, tolerance;
  double U1, V1, U2, V2;
  bool   goon;

  gp_Pnt Psurf, ptbid;
  gp_Vec Normale, Vtgint, Vtgrst;

  gp_Vec   d1u, d1v;
  gp_Pnt2d p2d;
  gp_Vec2d d2d;

  IntSurf_Transition Transline, Transarc;

  occ::handle<Adaptor2d_Curve2d> currentarc;
  occ::handle<Adaptor3d_HVertex> vtx, vtxbis;

  IntPatch_Point                      solpnt;
  IntPatch_ThePathPointOfTheSOnBounds currentpointonrst;
  IntPatch_IType                      TheType;

  NCollection_Array1<int> UsedLine(1, nblin);
  NCollection_Array1<int> Done(1, nbpnt);
  for (i = 1; i <= nbpnt; i++)
    Done(i) = 0;

  for (i = 1; i <= nbpnt; i++)
  {
    if (Done(i) != 1)
    {
      currentpointonrst = listpnt.Value(i);
      Psurf             = currentpointonrst.Value();
      tolerance         = currentpointonrst.Tolerance();

      UsedLine.Init(0);

      goon = true;
      if (multpoint)
      {
        Normale          = QuadSurf.Normale(Psurf);
        currentarc       = currentpointonrst.Arc();
        currentparameter = currentpointonrst.Parameter();
        currentarc->D1(currentparameter, p2d, d2d);
        QuadSurf.D1(p2d.X(), p2d.Y(), ptbid, d1u, d1v);
        Vtgrst.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
        goon = MultiplePoint(listpnt,
                             Domain,
                             QuadSurf,
                             Normale,
                             slin,
                             Done,
                             UsedLine,
                             i,
                             OnFirst,
                             Tolarc);
      }
      if (goon)
      {
        bool linefound = false;

        for (int indiceline = 1; indiceline <= slin.Length(); indiceline++)
        {
          if (UsedLine(indiceline) != 0)
            continue;
          linenumber = indiceline;

          currentpointonrst = listpnt.Value(i);
          currentarc        = currentpointonrst.Arc();
          currentparameter  = currentpointonrst.Parameter();
          Psurf             = currentpointonrst.Value();
          tolerance         = currentpointonrst.Tolerance();

          if (!currentpointonrst.IsNew())
          {
            occ::handle<Adaptor3d_HVertex> aVtx    = currentpointonrst.Vertex();
            double                         aVtxTol = aVtx->Resolution(currentarc);
            double                         aTolAng = 0.01 * tolerance;

            tolerance = std::max(tolerance, aVtxTol);

            gp_Vec aNorm1 = QuadSurf.Normale(Psurf);
            gp_Vec aNorm2 = OtherQuad.Normale(Psurf);

            if (aNorm1.Magnitude() > gp::Resolution() && aNorm2.Magnitude() > gp::Resolution())
            {
              if (aNorm1.IsParallel(aNorm2, aTolAng))
                tolerance = std::sqrt(tolerance);
            }
          }

          gp_Pnt pointonarc;
          Vtgint.SetCoord(0, 0, 0);
          double                   aVertTol = Tolarc;
          NCollection_List<double> aLParams;
          linefound = FindLine(Psurf,
                               slin,
                               tolerance,
                               aLParams,
                               Vtgint,
                               linenumber,
                               indiceline,
                               currentarc,
                               currentparameter,
                               pointonarc,
                               QuadSurf,
                               OtherQuad,
                               aVertTol);
          if (linefound)
          {
            Normale    = QuadSurf.Normale(Psurf);
            currentarc = currentpointonrst.Arc();

            currentarc->D1(currentparameter, p2d, d2d);
            QuadSurf.D1(p2d.X(), p2d.Y(), ptbid, d1u, d1v);
            Vtgrst.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);

            const occ::handle<IntPatch_Line>& lin = slin.Value(linenumber);
            TheType                               = lin->ArcType();

            if (!OnFirst)
            {

              goon = PointOnSecondDom(listpnt,
                                      Domain,
                                      QuadSurf,
                                      Normale,
                                      Vtgint,
                                      lin,
                                      Done,
                                      i,
                                      aVertTol);
            }

            if (goon)
            {

              solpnt.SetValue(Psurf, aVertTol, false);

              U1 = p2d.X();
              V1 = p2d.Y();
              OtherQuad.Parameters(Psurf, U2, V2);

              if (OnFirst)
              {
                Recadre(S1, S2, U1, V1, U2, V2);
                solpnt.SetParameters(U1, V1, U2, V2);
              }
              else
              {
                Recadre(S1, S2, U2, V2, U1, V1);
                solpnt.SetParameters(U2, V2, U1, V1);
              }

              if (!currentpointonrst.IsNew())
              {
                vtx = currentpointonrst.Vertex();
                solpnt.SetVertex(OnFirst, vtx);
              }
              else
              {
              }

              if (Normale.SquareMagnitude() < 1e-16)
              {
                Transline.SetValue(true, IntSurf_Undecided);
                Transarc.SetValue(true, IntSurf_Undecided);
              }
              else
              {
                IntSurf::MakeTransition(Vtgint, Vtgrst, Normale, Transline, Transarc);
              }
              solpnt.SetArc(OnFirst, currentarc, currentparameter, Transline, Transarc);

              for (NCollection_List<double>::Iterator anItr(aLParams); anItr.More(); anItr.Next())
              {
                solpnt.SetParameter(anItr.Value());
                if (TheType == IntPatch_Analytic)
                {
                  occ::down_cast<IntPatch_ALine>(lin)->AddVertex(solpnt);
                }
                else
                {
                  occ::down_cast<IntPatch_GLine>(lin)->AddVertex(solpnt);
                }
              }

              Done(i) = 1;

              if (goon)
              {
                for (k = i + 1; k <= nbpnt; k++)
                {
                  if (Done(k) != 1)
                  {
                    currentpointonrst = listpnt.Value(k);
                    if (!currentpointonrst.IsNew())
                    {
                      vtxbis = currentpointonrst.Vertex();
                      if (vtx.IsNull())
                      {
                      }
                      else if (Domain->Identical(vtx, vtxbis))
                      {
                        solpnt.SetVertex(OnFirst, vtxbis);
                        solpnt.SetTolerance(Tolarc);
                        currentarc       = currentpointonrst.Arc();
                        currentparameter = currentpointonrst.Parameter();

                        currentarc->D1(currentparameter, p2d, d2d);
                        Vtgrst.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                        if (Normale.SquareMagnitude() < 1e-16)
                        {
                          Transline.SetValue(true, IntSurf_Undecided);
                          Transarc.SetValue(true, IntSurf_Undecided);
                        }
                        else
                        {
                          IntSurf::MakeTransition(Vtgint, Vtgrst, Normale, Transline, Transarc);
                        }
                        solpnt.SetArc(OnFirst, currentarc, currentparameter, Transline, Transarc);
                        if (TheType == IntPatch_Analytic)
                        {
                          occ::down_cast<IntPatch_ALine>(lin)->AddVertex(solpnt);
                        }
                        else
                        {
                          occ::down_cast<IntPatch_GLine>(lin)->AddVertex(solpnt);
                        }
                        Done(k) = 1;
                      }
                    }
                  }
                }
              }
            }
          }
          else
          {
            Done(i) = 1;
          }
        }
      }
    }
  }
}

bool MultiplePoint(const NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>& listpnt,
                   const occ::handle<Adaptor3d_TopolTool>&                          Domain,
                   const IntSurf_Quadric&                                           QuadSurf,
                   const gp_Vec&                                                    Normale,
                   const NCollection_Sequence<occ::handle<IntPatch_Line>>&          slin,
                   NCollection_Array1<int>&                                         Done,
                   NCollection_Array1<int>&                                         UsedLine,
                   const int                                                        Index,
                   const bool                                                       OnFirst,
                   const double                                                     theToler)
{

  int            k, ii, jj, nbvtx;
  int            nblin = slin.Length();
  IntPatch_IType TheType;

  IntSurf_Transition Transline, Transarc;

  IntPatch_Point                 intpt;
  occ::handle<Adaptor2d_Curve2d> currentarc;
  occ::handle<Adaptor3d_HVertex> vtx, vtxbis;

  int                                 nbpnt             = listpnt.Length();
  IntPatch_ThePathPointOfTheSOnBounds currentpointonrst = listpnt.Value(Index);
  IntPatch_ThePathPointOfTheSOnBounds otherpt;
  gp_Pnt                              Point = currentpointonrst.Value();
  NCollection_Array1<int>             localdone(1, nbpnt);
  localdone.Init(0);
  for (ii = 1; ii <= nbpnt; ii++)
  {
    localdone(ii) = Done(ii);
  }

  double currentparameter;
  double Paraint;
  gp_Vec Vtgint, Vtgrst;
  gp_Pnt ptbid;

  gp_Vec   d1u, d1v;
  gp_Pnt2d p2d;
  gp_Vec2d d2d;

  bool goon;

  bool Retvalue = true;

  for (ii = 1; ii <= nblin; ii++)
  {
    const occ::handle<IntPatch_Line>& slinValueii = slin.Value(ii);
    TheType                                       = slinValueii->ArcType();
    if (TheType == IntPatch_Analytic)
    {
      nbvtx = occ::down_cast<IntPatch_ALine>(slinValueii)->NbVertex();
    }
    else
    {
      nbvtx = occ::down_cast<IntPatch_GLine>(slinValueii)->NbVertex();
    }
    jj = 1;
    while (jj <= nbvtx)
    {
      if (TheType == IntPatch_Analytic)
      {
        intpt = occ::down_cast<IntPatch_ALine>(slinValueii)->Vertex(jj);
      }
      else
      {
        intpt = occ::down_cast<IntPatch_GLine>(slinValueii)->Vertex(jj);
      }
      if (intpt.IsMultiple()
          && ((OnFirst && !intpt.IsOnDomS1()) || (!OnFirst && !intpt.IsOnDomS2())))
      {
        if (Point.Distance(intpt.Value()) <= intpt.Tolerance())
        {
          Retvalue = false;
          bool foo = SingleLine(Point, slinValueii, intpt.Tolerance(), Paraint, Vtgint);
          if (!foo)
          {
            return false;
          }

          if (!currentpointonrst.IsNew())
          {
            goon = true;
            vtx  = currentpointonrst.Vertex();
            intpt.SetVertex(OnFirst, vtx);
          }
          else
          {
            goon = false;
          }
          currentarc       = currentpointonrst.Arc();
          currentparameter = currentpointonrst.Parameter();
          currentarc->D1(currentparameter, p2d, d2d);
          QuadSurf.D1(p2d.X(), p2d.Y(), ptbid, d1u, d1v);
          Vtgrst.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);

          if (Normale.SquareMagnitude() < 1e-16)
          {
            Transline.SetValue(true, IntSurf_Undecided);
            Transarc.SetValue(true, IntSurf_Undecided);
          }
          else
          {
            IntSurf::MakeTransition(Vtgint, Vtgrst, Normale, Transline, Transarc);
          }

          intpt.SetValue(Point);

          intpt.SetArc(OnFirst, currentarc, currentparameter, Transline, Transarc);
          intpt.SetTolerance(theToler);

          if (TheType == IntPatch_Analytic)
          {
            occ::down_cast<IntPatch_ALine>(slinValueii)->Replace(jj, intpt);
          }
          else
          {
            occ::down_cast<IntPatch_GLine>(slinValueii)->Replace(jj, intpt);
          }
          localdone(Index) = 1;
          if (goon)
          {
            for (k = Index + 1; k <= nbpnt; k++)
            {
              if (Done(k) != 1)
              {
                otherpt = listpnt.Value(k);
                if (!otherpt.IsNew())
                {
                  vtxbis = otherpt.Vertex();
                  if (Domain->Identical(vtx, vtxbis))
                  {
                    intpt.SetVertex(OnFirst, vtxbis);
                    currentarc       = otherpt.Arc();
                    currentparameter = otherpt.Parameter();

                    currentarc->D1(currentparameter, p2d, d2d);
                    Vtgrst.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                    if (Normale.SquareMagnitude() < 1e-16)
                    {
                      Transline.SetValue(true, IntSurf_Undecided);
                      Transarc.SetValue(true, IntSurf_Undecided);
                    }
                    else
                    {
                      IntSurf::MakeTransition(Vtgint, Vtgrst, Normale, Transline, Transarc);
                    }
                    intpt.SetArc(OnFirst, currentarc, currentparameter, Transline, Transarc);
                    intpt.SetTolerance(theToler);
                    if (TheType == IntPatch_Analytic)
                    {
                      occ::down_cast<IntPatch_ALine>(slinValueii)->AddVertex(intpt);
                    }
                    else
                    {
                      occ::down_cast<IntPatch_GLine>(slinValueii)->AddVertex(intpt);
                    }
                    UsedLine(ii) = 1;
                    Retvalue     = true;
                    localdone(k) = 1;
                  }
                }
              }
            }
          }
        }

        jj = jj + 1;
      }
      else
      {
        jj = jj + 1;
      }
    }
  }

  for (ii = 1; ii <= nbpnt; ii++)
  {
    Done(ii) = localdone(ii);
  }

  return Retvalue;
}

bool PointOnSecondDom(const NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds>& listpnt,
                      const occ::handle<Adaptor3d_TopolTool>&                          Domain,
                      const IntSurf_Quadric&                                           QuadSurf,
                      const gp_Vec&                                                    Normale,
                      const gp_Vec&                                                    Vtgint,
                      const occ::handle<IntPatch_Line>&                                lin,
                      NCollection_Array1<int>&                                         Done,
                      const int                                                        Index,
                      const double                                                     theToler)

{
  int            k, jj, nbvtx;
  IntPatch_IType TheType;

  IntSurf_Transition             Transline, Transarc;
  IntPatch_Point                 intpt;
  occ::handle<Adaptor2d_Curve2d> currentarc;
  occ::handle<Adaptor3d_HVertex> vtx, vtxbis;
  gp_Pnt                         ptbid;
  gp_Vec                         Vtgrst;

  gp_Vec   d1u, d1v;
  gp_Pnt2d p2d;
  gp_Vec2d d2d;

  int                                 nbpnt             = listpnt.Length();
  IntPatch_ThePathPointOfTheSOnBounds currentpointonrst = listpnt.Value(Index);
  double                              currentparameter;

  bool goon;
  bool Retvalue = true;

  TheType = lin->ArcType();
  if (TheType == IntPatch_Analytic)
  {
    nbvtx = occ::down_cast<IntPatch_ALine>(lin)->NbVertex();
  }
  else
  {
    nbvtx = occ::down_cast<IntPatch_GLine>(lin)->NbVertex();
  }
  jj = 1;
  while (jj <= nbvtx)
  {
    if (TheType == IntPatch_Analytic)
    {
      intpt = occ::down_cast<IntPatch_ALine>(lin)->Vertex(jj);
    }
    else
    {
      intpt = occ::down_cast<IntPatch_GLine>(lin)->Vertex(jj);
    }
    if (!intpt.IsOnDomS2())
    {
      if (currentpointonrst.Value().Distance(intpt.Value()) <= intpt.Tolerance())
      {
        Retvalue = false;
        if (!currentpointonrst.IsNew())
        {
          goon = true;
          vtx  = currentpointonrst.Vertex();
          intpt.SetVertex(false, vtx);
        }
        else
        {
          goon = false;
        }
        currentarc       = currentpointonrst.Arc();
        currentparameter = currentpointonrst.Parameter();
        currentarc->D1(currentparameter, p2d, d2d);
        QuadSurf.D1(p2d.X(), p2d.Y(), ptbid, d1u, d1v);
        Vtgrst.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
        if (Normale.SquareMagnitude() < 1e-16)
        {
          Transline.SetValue(true, IntSurf_Undecided);
          Transarc.SetValue(true, IntSurf_Undecided);
        }
        else
        {
          IntSurf::MakeTransition(Vtgint, Vtgrst, Normale, Transline, Transarc);
        }
        intpt.SetArc(false, currentarc, currentparameter, Transline, Transarc);
        intpt.SetTolerance(theToler);

        if (TheType == IntPatch_Analytic)
        {
          occ::down_cast<IntPatch_ALine>(lin)->Replace(jj, intpt);
        }
        else
        {
          occ::down_cast<IntPatch_GLine>(lin)->Replace(jj, intpt);
        }
        Done(Index) = 1;

        if (goon)
        {
          for (k = Index + 1; k <= nbpnt; k++)
          {
            if (Done(k) != 1)
            {
              currentpointonrst = listpnt.Value(k);
              if (!currentpointonrst.IsNew())
              {
                vtxbis = currentpointonrst.Vertex();
                if (Domain->Identical(vtx, vtxbis))
                {
                  intpt.SetVertex(false, vtxbis);
                  currentarc       = currentpointonrst.Arc();
                  currentparameter = currentpointonrst.Parameter();
                  currentarc->D1(currentparameter, p2d, d2d);
                  Vtgrst.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                  if (Normale.SquareMagnitude() < 1e-16)
                  {
                    Transline.SetValue(true, IntSurf_Undecided);
                    Transarc.SetValue(true, IntSurf_Undecided);
                  }
                  else
                  {
                    IntSurf::MakeTransition(Vtgint, Vtgrst, Normale, Transline, Transarc);
                  }
                  intpt.SetArc(false, currentarc, currentparameter, Transline, Transarc);
                  intpt.SetTolerance(theToler);
                  if (TheType == IntPatch_Analytic)
                  {
                    occ::down_cast<IntPatch_ALine>(lin)->AddVertex(intpt);
                  }
                  else
                  {
                    occ::down_cast<IntPatch_GLine>(lin)->AddVertex(intpt);
                  }
                  Done(k) = 1;
                }
              }
            }
          }
        }

        jj++;
      }
      else
      {
        jj = jj + 1;
      }
    }
    else
    {
      jj = jj + 1;
    }
    if (TheType == IntPatch_Analytic)
    {
      nbvtx = occ::down_cast<IntPatch_ALine>(lin)->NbVertex();
    }
    else
    {
      nbvtx = occ::down_cast<IntPatch_GLine>(lin)->NbVertex();
    }
  }
  return Retvalue;
}

bool FindLine(gp_Pnt&                                                 Psurf,
              const NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
              const double                                            Tol,
              NCollection_List<double>&                               theLParams,
              gp_Vec&                                                 Vtgtint,
              int&                                                    theLineIdx,
              int                                                     OnlyThisLine,
              const occ::handle<Adaptor2d_Curve2d>&                   thearc,
              double&                                                 theparameteronarc,
              gp_Pnt&                                                 thepointonarc,
              const IntSurf_Quadric&                                  QuadSurf1,
              const IntSurf_Quadric&                                  QuadSurf2,
              double&                                                 theOutputToler)
{
  if ((QuadSurf1.Distance(Psurf) > Tol) || (QuadSurf2.Distance(Psurf) > Tol))
    return false;

  const double   aSqTol     = Tol * Tol;
  double         aSqDistMin = RealLast();
  double         aSqDist, para;
  double         lower, upper;
  gp_Pnt         pt;
  int            i;
  IntPatch_IType typarc;

  double aParaInt = RealLast();
  int    nblin    = slin.Length();
  for (i = 1; i <= nblin; i++)
  {
    if (OnlyThisLine)
    {
      i     = OnlyThisLine;
      nblin = 0;
    }
    const occ::handle<IntPatch_Line>& lin = slin.Value(i);
    typarc                                = lin->ArcType();
    if (typarc == IntPatch_Analytic)
    {
      bool foo;
      lower = occ::down_cast<IntPatch_ALine>(lin)->FirstParameter(foo);
      upper = occ::down_cast<IntPatch_ALine>(lin)->LastParameter(foo);
    }
    else
    {
      if (occ::down_cast<IntPatch_GLine>(lin)->HasFirstPoint())
      {
        lower = occ::down_cast<IntPatch_GLine>(lin)->FirstPoint().ParameterOnLine();
      }
      else
      {
        lower = RealFirst();
      }
      if (occ::down_cast<IntPatch_GLine>(lin)->HasLastPoint())
      {
        upper = occ::down_cast<IntPatch_GLine>(lin)->LastPoint().ParameterOnLine();
      }
      else
      {
        upper = RealLast();
      }
    }

    switch (typarc)
    {
      case IntPatch_Lin:
      {
        para = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Line(), Psurf);
        if (para <= upper && para >= lower)
        {
          pt      = ElCLib::Value(para, occ::down_cast<IntPatch_GLine>(lin)->Line());
          aSqDist = Psurf.SquareDistance(pt);
          if ((aSqDist < aSqTol) && (aSqDist < aSqDistMin))
          {
            aSqDistMin = aSqDist;
            aParaInt   = para;
            theLineIdx = i;
          }
        }
      }
      break;
      case IntPatch_Circle:
      {
        para = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Circle(), Psurf);
        if ((para <= upper && para >= lower)
            || (para + 2. * M_PI <= upper && para + 2. * M_PI >= lower)
            || (para - 2. * M_PI <= upper && para - 2. * M_PI >= lower))
        {
          pt      = ElCLib::Value(para, occ::down_cast<IntPatch_GLine>(lin)->Circle());
          aSqDist = Psurf.SquareDistance(pt);
          if ((aSqDist < aSqTol) && (aSqDist < aSqDistMin))
          {
            aSqDistMin = aSqDist;
            aParaInt   = para;
            theLineIdx = i;
          }
        }
      }
      break;
      case IntPatch_Ellipse:
      {
        para = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Ellipse(), Psurf);
        if ((para <= upper && para >= lower)
            || (para + 2. * M_PI <= upper && para + 2. * M_PI >= lower)
            || (para - 2. * M_PI <= upper && para - 2. * M_PI >= lower))
        {
          pt      = ElCLib::Value(para, occ::down_cast<IntPatch_GLine>(lin)->Ellipse());
          aSqDist = Psurf.SquareDistance(pt);
          if ((aSqDist < aSqTol) && (aSqDist < aSqDistMin))
          {
            aSqDistMin = aSqDist;
            aParaInt   = para;
            theLineIdx = i;
          }
        }
      }
      break;
      case IntPatch_Parabola:
      {

        const gp_Parab& Parab = occ::down_cast<IntPatch_GLine>(lin)->Parabola();
        para                  = ElCLib::Parameter(Parab, Psurf);
        if (para <= upper && para >= lower)
        {
          int amelioration = 0;

          do
          {
            double parabis = para + 0.0000001;

            pt      = ElCLib::Value(para, Parab);
            aSqDist = Psurf.SquareDistance(pt);

            const gp_Pnt ptbis   = ElCLib::Value(parabis, Parab);
            const double distbis = Psurf.Distance(ptbis);
            const double aDist   = std::sqrt(aSqDist);
            const double ddist   = distbis - aDist;

            if ((aSqDist < aSqTol) && (aSqDist < aSqDistMin))
            {
              aSqDistMin = aSqDist;
              aParaInt   = para;
              theLineIdx = i;
            }
            if (aSqDist < Precision::SquarePConfusion())
            {
              amelioration = 100;
            }

            if (ddist > 1.0e-9 || ddist < -1.0e-9)
            {
              para = para - aDist * (parabis - para) / ddist;
            }
            else
            {
              amelioration = 100;
            }
          } while (++amelioration < 5);
        }
      }
      break;
      case IntPatch_Hyperbola:
      {
        para = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Hyperbola(), Psurf);
        if (para <= upper && para >= lower)
        {
          pt      = ElCLib::Value(para, occ::down_cast<IntPatch_GLine>(lin)->Hyperbola());
          aSqDist = Psurf.SquareDistance(pt);
          if ((aSqDist < aSqTol) && (aSqDist < aSqDistMin))
          {
            aSqDistMin = aSqDist;
            aParaInt   = para;
            theLineIdx = i;
          }
        }
      }
      break;

      case IntPatch_Analytic:
      {
        occ::handle<IntPatch_ALine> alin(occ::down_cast<IntPatch_ALine>(lin));
        NCollection_List<double>    aLParams;
        alin->FindParameter(Psurf, aLParams);
        if (!aLParams.IsEmpty())
        {

          aSqDist = RealLast();
          for (NCollection_List<double>::Iterator anItr(aLParams); anItr.More(); anItr.Next())
          {
            pt                = alin->Value(anItr.Value());
            const double aSqD = Psurf.SquareDistance(pt);
            if (aSqD < aSqDist)
            {
              aSqDist = aSqD;
            }
          }

          if (aSqDist < aSqDistMin)
          {
            aSqDistMin = aSqDist;
            theLParams = aLParams;
            theLineIdx = i;
          }
        }
        else
        {

          double theparamonarc = theparameteronarc;

          gp_Pnt CopiePsurf    = Psurf;
          bool   IntersectIsOk = IntersectionWithAnArc(CopiePsurf,
                                                     alin,
                                                     para,
                                                     thearc,
                                                     theparamonarc,
                                                     thepointonarc,
                                                     QuadSurf1,
                                                     lower,
                                                     upper);
          aSqDist              = CopiePsurf.SquareDistance(Psurf);
          if (IntersectIsOk)
          {
            if (aSqDist < aSqTol)
            {
              theparameteronarc = theparamonarc;
              Psurf             = thepointonarc;
              aSqDistMin        = aSqDist;
              theLParams.Append(para);
              theLineIdx = i;
            }
          }
        }
      }
      break;

      case IntPatch_Walking:
      {
      }
      case IntPatch_Restriction:
      {
      }
    }
  }

  if (aSqDistMin == RealLast())
    return false;

  theOutputToler = std::max(theOutputToler, std::sqrt(aSqDistMin));

  typarc = slin.Value(theLineIdx)->ArcType();

  switch (typarc)
  {
    case IntPatch_Lin:
      theLParams.Append(aParaInt);
      Vtgtint = (*((occ::handle<IntPatch_GLine>*)&slin(theLineIdx)))->Line().Direction();
      break;
    case IntPatch_Circle:
      theLParams.Append(aParaInt);
      Vtgtint =
        ElCLib::DN(aParaInt, (*((occ::handle<IntPatch_GLine>*)&slin(theLineIdx)))->Circle(), 1);
      break;
    case IntPatch_Ellipse:
      theLParams.Append(aParaInt);
      Vtgtint =
        ElCLib::DN(aParaInt, (*((occ::handle<IntPatch_GLine>*)&slin(theLineIdx)))->Ellipse(), 1);
      break;
    case IntPatch_Parabola:
      theLParams.Append(aParaInt);
      Vtgtint =
        ElCLib::DN(aParaInt, (*((occ::handle<IntPatch_GLine>*)&slin(theLineIdx)))->Parabola(), 1);
      break;
    case IntPatch_Hyperbola:
      theLParams.Append(aParaInt);
      Vtgtint =
        ElCLib::DN(aParaInt, (*((occ::handle<IntPatch_GLine>*)&slin(theLineIdx)))->Hyperbola(), 1);
      break;

    case IntPatch_Analytic:
    {
      if (!occ::down_cast<IntPatch_ALine>(slin(theLineIdx))->D1(theLParams.Last(), pt, Vtgtint))
      {

        Vtgtint.SetCoord(0.0, 0.0, 0.0);
      }
    }
    break;
    case IntPatch_Walking:
    {
    }
    case IntPatch_Restriction:
    {
    }
  }
  return true;
}

bool SingleLine(const gp_Pnt&                     Psurf,
                const occ::handle<IntPatch_Line>& lin,
                const double                      Tol,
                double&                           Paraint,
                gp_Vec&                           Vtgtint)
{
  IntPatch_IType typarc = lin->ArcType();

  double parproj = 0.;
  gp_Vec tgint;
  gp_Pnt ptproj;
  bool   retvalue;

  switch (typarc)
  {
    case IntPatch_Lin:
      parproj = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Line(), Psurf);
      ElCLib::D1(parproj, occ::down_cast<IntPatch_GLine>(lin)->Line(), ptproj, tgint);
      break;
    case IntPatch_Circle:
      parproj = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Circle(), Psurf);
      ElCLib::D1(parproj, occ::down_cast<IntPatch_GLine>(lin)->Circle(), ptproj, tgint);
      break;
    case IntPatch_Ellipse:
      parproj = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Ellipse(), Psurf);
      ElCLib::D1(parproj, occ::down_cast<IntPatch_GLine>(lin)->Ellipse(), ptproj, tgint);
      break;
    case IntPatch_Parabola:
      parproj = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Parabola(), Psurf);
      ElCLib::D1(parproj, occ::down_cast<IntPatch_GLine>(lin)->Parabola(), ptproj, tgint);
      break;
    case IntPatch_Hyperbola:
      parproj = ElCLib::Parameter(occ::down_cast<IntPatch_GLine>(lin)->Hyperbola(), Psurf);
      ElCLib::D1(parproj, occ::down_cast<IntPatch_GLine>(lin)->Hyperbola(), ptproj, tgint);
      break;
    case IntPatch_Analytic:
    {
      occ::handle<IntPatch_ALine> alin(occ::down_cast<IntPatch_ALine>(lin));
      NCollection_List<double>    aLParams;
      alin->FindParameter(Psurf, aLParams);
      if (!aLParams.IsEmpty())
      {
        ptproj  = Psurf;
        parproj = aLParams.Last();
        gp_Pnt aPtemp;
        if (!alin->D1(parproj, aPtemp, tgint))
        {

          tgint.SetCoord(0.0, 0.0, 0.0);
        }
      }
      else
      {

        return false;
      }
    }
    break;
    case IntPatch_Walking:
    {
    }
    case IntPatch_Restriction:
    {
    }
  }

  if (Psurf.Distance(ptproj) <= Tol)
  {
    Paraint  = parproj;
    Vtgtint  = tgint;
    retvalue = true;
  }
  else
  {
    retvalue = false;
  }
  return retvalue;
}

void ProcessSegments(const NCollection_Sequence<IntPatch_TheSegmentOfTheSOnBounds>& listedg,
                     NCollection_Sequence<occ::handle<IntPatch_Line>>&              slin,
                     const IntSurf_Quadric&                                         Quad1,
                     const IntSurf_Quadric&                                         Quad2,
                     const bool                                                     OnFirst,
                     const double                                                   TolArc)
{
  int i, j, k;
  int nbedg = listedg.Length();
  int Nblines, Nbpts;

  occ::handle<Adaptor2d_Curve2d> arcRef;
  IntPatch_Point                 ptvtx, newptvtx;

  occ::handle<IntPatch_RLine> rline;

  IntPatch_TheSegmentOfTheSOnBounds   thesegsol;
  IntPatch_ThePathPointOfTheSOnBounds PStartf, PStartl;
  bool                                dofirst, dolast, procf, procl;

  double paramf = 0., paraml = 0., U1 = 0., V1 = 0., U2 = 0., V2 = 0.;

  IntPatch_IType     typ;
  IntSurf_TypeTrans  trans1, trans2;
  IntSurf_Transition TRest, TArc;
  gp_Vec             tgline, norm1, norm2, tgarc;
  gp_Pnt             valpt;

  gp_Vec   d1u, d1v;
  gp_Pnt2d p2d;
  gp_Vec2d d2d;

  for (i = 1; i <= nbedg; i++)
  {
    bool EdgeDegenere = false;
    thesegsol         = listedg.Value(i);
    arcRef            = thesegsol.Curve();

    rline = new IntPatch_RLine(false);
    if (OnFirst)
    {
      rline->SetArcOnS1(arcRef);
    }
    else
    {
      rline->SetArcOnS2(arcRef);
    }

    dofirst = false;
    dolast  = false;
    procf   = false;
    procl   = false;

    if (thesegsol.HasFirstPoint())
    {
      dofirst = true;
      PStartf = thesegsol.FirstPoint();
      paramf  = PStartf.Parameter();
    }
    if (thesegsol.HasLastPoint())
    {
      dolast  = true;
      PStartl = thesegsol.LastPoint();
      paraml  = PStartl.Parameter();
    }

    if (dofirst && dolast)
    {
      arcRef->D1(0.5 * (paramf + paraml), p2d, d2d);
      if (OnFirst)
      {
        Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
      }
      else
      {
        Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
      }
      tgline.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);

      if (d1u.Magnitude() < 1e-7)
      {
        EdgeDegenere = true;
        for (int edg = 0; edg <= 10; edg++)
        {
          arcRef->D1(paramf + (paraml - paramf) * edg * 0.1, p2d, d2d);
          if (OnFirst)
          {
            Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
          }
          else
          {
            Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
          }

          if (d1u.Magnitude() > 1e-7)
          {
            EdgeDegenere = false;
          }
        }
        rline = new IntPatch_RLine(false);
        if (OnFirst)
        {
          rline->SetArcOnS1(arcRef);
        }
        else
        {
          rline->SetArcOnS2(arcRef);
        }
      }
      else
      {
        norm2 = Quad2.Normale(valpt);
        norm1 = Quad1.Normale(valpt);

        if (tgline.DotCross(norm2, norm1) > 0.000000001)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (tgline.DotCross(norm2, norm1) < -0.000000001)
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
        rline = new IntPatch_RLine(false, trans1, trans2);
        if (OnFirst)
        {
          rline->SetArcOnS1(arcRef);
        }
        else
        {
          rline->SetArcOnS2(arcRef);
        }
      }
    }
    else
    {
      rline = new IntPatch_RLine(false);
      if (OnFirst)
      {
        rline->SetArcOnS1(arcRef);
      }
      else
      {
        rline->SetArcOnS2(arcRef);
      }
    }

    if (dofirst || dolast)
    {
      Nblines = slin.Length();
      for (j = 1; j <= Nblines; j++)
      {
        const occ::handle<IntPatch_Line>& slinj = slin(j);
        typ                                     = slinj->ArcType();
        if (typ == IntPatch_Analytic)
        {
          Nbpts = occ::down_cast<IntPatch_ALine>(slinj)->NbVertex();
        }
        else if (typ == IntPatch_Restriction)
        {
          Nbpts = occ::down_cast<IntPatch_RLine>(slinj)->NbVertex();
        }
        else
        {
          Nbpts = occ::down_cast<IntPatch_GLine>(slinj)->NbVertex();
        }
        for (k = 1; k <= Nbpts; k++)
        {
          if (typ == IntPatch_Analytic)
          {
            ptvtx = occ::down_cast<IntPatch_ALine>(slinj)->Vertex(k);
          }
          else if (typ == IntPatch_Restriction)
          {
            ptvtx = occ::down_cast<IntPatch_RLine>(slinj)->Vertex(k);
          }
          else
          {
            ptvtx = occ::down_cast<IntPatch_GLine>(slinj)->Vertex(k);
          }

          if (!EdgeDegenere && dofirst)
          {
            if (ptvtx.Value().Distance(PStartf.Value()) <= TolArc)
            {
              ptvtx.SetMultiple(true);
              ptvtx.SetTolerance(TolArc);
              if (typ == IntPatch_Analytic)
              {
                occ::down_cast<IntPatch_ALine>(slinj)->Replace(k, ptvtx);
              }
              else if (typ == IntPatch_Restriction)
              {
                occ::down_cast<IntPatch_RLine>(slinj)->Replace(k, ptvtx);
              }
              else
              {
                occ::down_cast<IntPatch_GLine>(slinj)->Replace(k, ptvtx);
              }
              newptvtx = ptvtx;
              newptvtx.SetParameter(paramf);

              arcRef->D1(paramf, p2d, d2d);
              if (OnFirst)
              {
                Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
              }
              else
              {
                Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
              }
              tgline.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
              if (ptvtx.IsOnDomS1())
              {
                const occ::handle<Adaptor2d_Curve2d>& thearc = ptvtx.ArcOnS1();
                thearc->D1(ptvtx.ParameterOnArc1(), p2d, d2d);
                Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
                tgarc.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                norm1 = d1u.Crossed(d1v);
                if (norm1.SquareMagnitude() < 1e-16)
                {
                  TRest.SetValue(true, IntSurf_Undecided);
                  TArc.SetValue(true, IntSurf_Undecided);
                }
                else
                {
                  IntSurf::MakeTransition(tgline, tgarc, norm1, TRest, TArc);
                }
                newptvtx.SetArc(true, thearc, ptvtx.ParameterOnArc1(), TRest, TArc);
              }
              if (ptvtx.IsOnDomS2())
              {
                const occ::handle<Adaptor2d_Curve2d>& thearc = ptvtx.ArcOnS2();
                thearc->D1(ptvtx.ParameterOnArc2(), p2d, d2d);
                Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
                tgarc.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                norm2 = d1u.Crossed(d1v);
                if (norm2.SquareMagnitude() < 1e-16)
                {
                  TRest.SetValue(true, IntSurf_Undecided);
                  TArc.SetValue(true, IntSurf_Undecided);
                }
                else
                {
                  IntSurf::MakeTransition(tgline, tgarc, norm2, TRest, TArc);
                }
                newptvtx.SetArc(false, thearc, ptvtx.ParameterOnArc2(), TRest, TArc);
              }

              rline->AddVertex(newptvtx);
              if (!procf)
              {
                procf = true;
                rline->SetFirstPoint(rline->NbVertex());
              }
            }
          }
          if (!EdgeDegenere && dolast)
          {
            if (ptvtx.Value().Distance(PStartl.Value()) <= TolArc)
            {
              ptvtx.SetMultiple(true);
              ptvtx.SetTolerance(TolArc);
              if (typ == IntPatch_Analytic)
              {
                occ::down_cast<IntPatch_ALine>(slinj)->Replace(k, ptvtx);
              }
              else if (typ == IntPatch_Restriction)
              {
                occ::down_cast<IntPatch_RLine>(slinj)->Replace(k, ptvtx);
              }
              else
              {
                occ::down_cast<IntPatch_GLine>(slinj)->Replace(k, ptvtx);
              }

              newptvtx = ptvtx;
              newptvtx.SetParameter(paraml);

              arcRef->D1(paraml, p2d, d2d);
              if (OnFirst)
              {
                Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
              }
              else
              {
                Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
              }
              tgline.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
              if (ptvtx.IsOnDomS1())
              {
                const occ::handle<Adaptor2d_Curve2d>& thearc = ptvtx.ArcOnS1();
                thearc->D1(ptvtx.ParameterOnArc1(), p2d, d2d);
                Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
                tgarc.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                norm1 = d1u.Crossed(d1v);
                if (norm1.SquareMagnitude() < 1e-16)
                {
                  TRest.SetValue(true, IntSurf_Undecided);
                  TArc.SetValue(true, IntSurf_Undecided);
                }
                else
                {
                  IntSurf::MakeTransition(tgline, tgarc, norm1, TRest, TArc);
                }
                newptvtx.SetArc(true, thearc, ptvtx.ParameterOnArc1(), TRest, TArc);
              }
              if (ptvtx.IsOnDomS2())
              {
                const occ::handle<Adaptor2d_Curve2d>& thearc = ptvtx.ArcOnS2();
                thearc->D1(ptvtx.ParameterOnArc2(), p2d, d2d);
                Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
                tgarc.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                norm2 = d1u.Crossed(d1v);
                if (norm2.SquareMagnitude() < 1e-16)
                {
                  TRest.SetValue(true, IntSurf_Undecided);
                  TArc.SetValue(true, IntSurf_Undecided);
                }
                else
                {
                  IntSurf::MakeTransition(tgline, tgarc, norm2, TRest, TArc);
                }
                newptvtx.SetArc(false, thearc, ptvtx.ParameterOnArc2(), TRest, TArc);
              }

              rline->AddVertex(newptvtx);
              if (!procl)
              {
                procl = true;
                rline->SetLastPoint(rline->NbVertex());
              }
            }
          }
        }

        if (procf)
        {
          dofirst = false;
        }
        if (procl)
        {
          dolast = false;
        }
      }
    }

    if (dofirst)
    {
      ptvtx.SetValue(PStartf.Value(), PStartf.Tolerance(), false);
      Quad1.Parameters(PStartf.Value(), U1, V1);
      Quad2.Parameters(PStartf.Value(), U2, V2);
      ptvtx.SetParameters(U1, V1, U2, V2);
      ptvtx.SetParameter(paramf);
      if (!PStartf.IsNew())
      {
        IntSurf_Transition Transline;
        IntSurf_Transition Transarc;
        ptvtx.SetVertex(OnFirst, PStartf.Vertex());
        ptvtx.SetArc(OnFirst, PStartf.Arc(), PStartf.Parameter(), Transline, Transarc);
      }

      rline->AddVertex(ptvtx);
      rline->SetFirstPoint(rline->NbVertex());
    }
    if (dolast)
    {
      ptvtx.SetValue(PStartl.Value(), PStartl.Tolerance(), false);
      Quad1.Parameters(PStartl.Value(), U1, V1);
      Quad2.Parameters(PStartl.Value(), U2, V2);
      ptvtx.SetParameters(U1, V1, U2, V2);
      ptvtx.SetParameter(paraml);
      if (!PStartl.IsNew())
      {
        IntSurf_Transition Transline;
        IntSurf_Transition Transarc;

        ptvtx.SetVertex(OnFirst, PStartl.Vertex());
        ptvtx.SetArc(OnFirst, PStartl.Arc(), PStartl.Parameter(), Transline, Transarc);
      }

      rline->AddVertex(ptvtx);
      rline->SetLastPoint(rline->NbVertex());
    }
    slin.Append(rline);
  }
}

inline const gp_Pnt& PointValue(const occ::handle<IntPatch_RLine>& theRLine, const int theIndex)
{
  return theRLine->Point(theIndex).Value();
}

inline const gp_Pnt& VertexValue(const occ::handle<IntPatch_RLine>& theRLine, const int theIndex)
{
  return theRLine->Vertex(theIndex).Value();
}

static double SquareDistance(const occ::handle<IntPatch_GLine>& theGLine,
                             const gp_Pnt&                      theP,
                             Extrema_ExtPC&                     theExtr)
{
  double aSQDist = RealLast();
  switch (theGLine->ArcType())
  {
    case IntPatch_Lin:
      aSQDist = theGLine->Line().SquareDistance(theP);
      break;
    case IntPatch_Circle:
      aSQDist = theGLine->Circle().SquareDistance(theP);
      break;
    default:
      theExtr.Perform(theP);
      if (!theExtr.IsDone() || !theExtr.NbExt())
      {

        return aSQDist;
      }

      aSQDist           = theExtr.SquareDistance(1);
      const int aNbExtr = theExtr.NbExt();
      for (int i = 2; i <= aNbExtr; i++)
      {
        const double aSQD = theExtr.SquareDistance(i);
        if (aSQD < aSQDist)
        {
          aSQDist = aSQD;
        }
      }
  }

  return aSQDist;
}

static bool IsRLineGood(const IntSurf_Quadric&             Quad1,
                        const IntSurf_Quadric&             Quad2,
                        const occ::handle<IntPatch_GLine>& theGLine,
                        const occ::handle<IntPatch_RLine>& theRLine,
                        const double                       theTol)
{
  const double         aSQTol    = theTol * theTol;
  const IntPatch_IType aGType    = theGLine->ArcType();
  int                  aNbPntsM1 = 0;

  const gp_Pnt& (*Value)(const occ::handle<IntPatch_RLine>&, const int);

  if (theRLine->HasPolygon())
  {
    aNbPntsM1 = theRLine->NbPnts() - 1;
    Value     = PointValue;
  }
  else
  {
    aNbPntsM1 = theRLine->NbVertex() - 1;
    Value     = VertexValue;
  }

  if (aNbPntsM1 < 1)
    return false;

  Extrema_ExtPC           anExtr;
  GeomAdaptor_Curve       anAC;
  occ::handle<Geom_Curve> aCurv;

  if (aGType == IntPatch_Ellipse)
    aCurv = new Geom_Ellipse(theGLine->Ellipse());
  else if (aGType == IntPatch_Parabola)
    aCurv = new Geom_Parabola(theGLine->Parabola());
  else if (aGType == IntPatch_Hyperbola)
    aCurv = new Geom_Hyperbola(theGLine->Hyperbola());

  if (!aCurv.IsNull())
  {
    const double anUinf = aCurv->FirstParameter(), anUsup = aCurv->LastParameter();
    anAC.Load(aCurv, anUinf, anUsup);
    anExtr.Initialize(anAC, anUinf, anUsup);
  }

  if (aNbPntsM1 == 1)
  {
    gp_Pnt aP1(Value(theRLine, 1)), aP2(Value(theRLine, 2));

    if (aP1.SquareDistance(aP2) < aSQTol)
    {

      return false;
    }

    gp_Pnt aPMid;
    if (theRLine->IsArcOnS1())
    {
      const occ::handle<Adaptor2d_Curve2d>& anAC2d = theRLine->ArcOnS1();
      const double aParF = anAC2d->FirstParameter(), aParL = anAC2d->LastParameter();
      gp_Pnt2d     aP2d(anAC2d->Value(0.5 * (aParF + aParL)));
      aPMid = Quad1.Value(aP2d.X(), aP2d.Y());
    }
    else
    {
      const occ::handle<Adaptor2d_Curve2d>& anAC2d = theRLine->ArcOnS2();
      const double aParF = anAC2d->FirstParameter(), aParL = anAC2d->LastParameter();
      gp_Pnt2d     aP2d(anAC2d->Value(0.5 * (aParF + aParL)));
      aPMid = Quad2.Value(aP2d.X(), aP2d.Y());
    }

    const double aSQDist = SquareDistance(theGLine, aPMid, anExtr);
    return (aSQDist > aSQTol);
  }

  for (int i = 2; i <= aNbPntsM1; i++)
  {
    const gp_Pnt aP(Value(theRLine, i));
    const double aSQDist = SquareDistance(theGLine, aP, anExtr);

    if (aSQDist > aSQTol)
      return true;
  }

  return false;
}

void ProcessRLine(NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,

                  const IntSurf_Quadric& Quad1,
                  const IntSurf_Quadric& Quad2,
                  const double           _TolArc,
                  const bool             theIsReqToKeepRLine)
{

  double TolArc = 100.0 * _TolArc;
  if (TolArc > 0.1)
    TolArc = 0.1;

  int i, j, k;
  int Nblin, Nbvtx, Nbpt;

  bool OnFirst = false, project = false, keeppoint = false;

  occ::handle<Adaptor2d_Curve2d> arcref;
  double                         paramproj, paramf, paraml;

  NCollection_Sequence<gp_Pnt> seq_Pnt3d;
  NCollection_Sequence<double> seq_Real;

  gp_Pnt ptproj, toproj, valpt;

  gp_Pnt2d           p2d;
  gp_Vec2d           d2d;
  gp_Vec             d1u, d1v, tgrest, tgarc, norm;
  IntSurf_Transition TRest, TArc;
#ifndef OCCT_DEBUG
  double U = 0., V = 0.;
#else
  double U, V;
#endif
  IntPatch_Point Ptvtx, newptvtx;

  IntPatch_IType typ1, typ2;

  Nblin = slin.Length();
  for (i = 1; i <= Nblin; i++)
  {
    const occ::handle<IntPatch_Line>& slini = slin(i);
    typ1                                    = slini->ArcType();

    bool HasToDeleteRLine = false;
    if (typ1 == IntPatch_Restriction)
    {
      seq_Pnt3d.Clear();
      seq_Real.Clear();

      for (j = 1; j <= Nblin; j++)
      {
        const occ::handle<IntPatch_Line>& slinj = slin(j);
        Nbpt                                    = seq_Pnt3d.Length();
        typ2                                    = slinj->ArcType();
        if (typ2 != IntPatch_Restriction)
        {

          if (occ::down_cast<IntPatch_RLine>(slini)->IsArcOnS1())
          {
            OnFirst = true;
            arcref  = occ::down_cast<IntPatch_RLine>(slini)->ArcOnS1();
          }
          else if (occ::down_cast<IntPatch_RLine>(slini)->IsArcOnS2())
          {
            arcref  = occ::down_cast<IntPatch_RLine>(slini)->ArcOnS2();
            OnFirst = false;
          }
          if (occ::down_cast<IntPatch_RLine>(slini)->HasFirstPoint())
          {
            paramf = occ::down_cast<IntPatch_RLine>(slini)->FirstPoint().ParameterOnLine();
          }
          else
          {

            paramf = RealFirst();
          }
          if (occ::down_cast<IntPatch_RLine>(slini)->HasLastPoint())
          {
            paraml = occ::down_cast<IntPatch_RLine>(slini)->LastPoint().ParameterOnLine();
          }
          else
          {

            paraml = RealLast();
          }

          if (typ2 == IntPatch_Analytic)
          {
            Nbvtx = occ::down_cast<IntPatch_ALine>(slinj)->NbVertex();
          }
          else
          {
            Nbvtx = occ::down_cast<IntPatch_GLine>(slinj)->NbVertex();
          }

          bool EdgeDegenere = true;
          for (int edg = 0; EdgeDegenere && edg <= 10; edg++)
          {
            arcref->D1(paramf + (paraml - paramf) * edg * 0.1, p2d, d2d);
            if (OnFirst)
            {
              Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
            }
            else
            {
              Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
            }
            if (d1u.Magnitude() > 1e-7)
            {
              EdgeDegenere = false;
            }
          }

          for (k = 1; !EdgeDegenere && k <= Nbvtx; k++)
          {
            if (typ2 == IntPatch_Analytic)
            {
              Ptvtx = occ::down_cast<IntPatch_ALine>(slinj)->Vertex(k);
            }
            else
            {
              Ptvtx = occ::down_cast<IntPatch_GLine>(slinj)->Vertex(k);
            }
            if ((OnFirst && !Ptvtx.IsOnDomS1()) || (!OnFirst && !Ptvtx.IsOnDomS2()))
            {

              project   = true;
              keeppoint = false;
              toproj    = Ptvtx.Value();

              int jj;
              for (jj = 1; jj <= Nbpt; jj++)
              {

                if (toproj.Distance(seq_Pnt3d(jj)) < _TolArc)
                {
                  project = false;
                  break;
                }
              }
              if (project)
              {
                if (OnFirst)
                {
                  Ptvtx.ParametersOnS1(U, V);
                }
                else
                {
                  Ptvtx.ParametersOnS2(U, V);
                }

                project = IntPatch_HInterTool::Project(arcref, gp_Pnt2d(U, V), paramproj, p2d);

                if (project)
                {
                  if (OnFirst)
                  {
                    ptproj = Quad1.Value(p2d.X(), p2d.Y());
                  }
                  else
                  {
                    ptproj = Quad2.Value(p2d.X(), p2d.Y());
                  }
                  if ((toproj.Distance(ptproj) <= 100 * TolArc) && (paramproj >= paramf)
                      && (paramproj <= paraml))
                  {
                    newptvtx = Ptvtx;
                    newptvtx.SetParameter(paramproj);
                    keeppoint = true;
                    seq_Pnt3d.Append(toproj);
                    seq_Real.Append(paramproj);

                    for (int ri = 1; ri <= Nblin; ri++)
                    {
                      const occ::handle<IntPatch_Line>& slinri = slin(ri);
                      if (slinri->ArcType() == IntPatch_Restriction)
                      {
                        if (OnFirst && occ::down_cast<IntPatch_RLine>(slinri)->IsArcOnS1())
                        {
                          if (arcref == occ::down_cast<IntPatch_RLine>(slinri)->ArcOnS1())
                          {
                            occ::down_cast<IntPatch_RLine>(slinri)->AddVertex(newptvtx);
                          }
                        }
                        else if (!OnFirst && occ::down_cast<IntPatch_RLine>(slinri)->IsArcOnS2())
                        {
                          if (arcref == occ::down_cast<IntPatch_RLine>(slinri)->ArcOnS2())
                          {
                            occ::down_cast<IntPatch_RLine>(slinri)->AddVertex(newptvtx);
                          }
                        }
                      }
                    }
                  }
                }
              }
              else
              {
                keeppoint = true;
                newptvtx  = Ptvtx;
                newptvtx.SetParameter(seq_Real(jj));
              }
              if (keeppoint)
              {
                Ptvtx.SetMultiple(true);
                Ptvtx.SetTolerance(_TolArc);
                newptvtx.SetMultiple(true);

                if (typ2 == IntPatch_Analytic)
                {
                  occ::down_cast<IntPatch_ALine>(slinj)->Replace(k, Ptvtx);
                }
                else
                {
                  occ::down_cast<IntPatch_GLine>(slinj)->Replace(k, Ptvtx);
                }

                if (Ptvtx.IsOnDomS1() || Ptvtx.IsOnDomS2())
                {
                  arcref->D1(newptvtx.ParameterOnLine(), p2d, d2d);

                  if (OnFirst)
                  {
                    Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
                    tgrest.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);

                    const occ::handle<Adaptor2d_Curve2d>& thearc = Ptvtx.ArcOnS2();
                    thearc->D1(Ptvtx.ParameterOnArc2(), p2d, d2d);
                    Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
                    tgarc.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                    norm = d1u.Crossed(d1v);
                    if (norm.SquareMagnitude() < 1e-16)
                    {
                      TRest.SetValue(true, IntSurf_Undecided);
                      TArc.SetValue(true, IntSurf_Undecided);
                    }
                    else
                    {
                      IntSurf::MakeTransition(tgrest, tgarc, norm, TRest, TArc);
                    }
                    newptvtx.SetArc(false, thearc, Ptvtx.ParameterOnArc2(), TRest, TArc);
                  }
                  else
                  {
                    Quad2.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
                    tgrest.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);

                    const occ::handle<Adaptor2d_Curve2d>& thearc = Ptvtx.ArcOnS1();
                    thearc->D1(Ptvtx.ParameterOnArc1(), p2d, d2d);
                    Quad1.D1(p2d.X(), p2d.Y(), valpt, d1u, d1v);
                    tgarc.SetLinearForm(d2d.X(), d1u, d2d.Y(), d1v);
                    norm = d1u.Crossed(d1v);
                    if (norm.SquareMagnitude() < 1e-16)
                    {
                      TRest.SetValue(true, IntSurf_Undecided);
                      TArc.SetValue(true, IntSurf_Undecided);
                    }
                    else
                    {
                      IntSurf::MakeTransition(tgrest, tgarc, norm, TRest, TArc);
                    }
                    newptvtx.SetArc(true, thearc, Ptvtx.ParameterOnArc1(), TRest, TArc);
                  }
                }

                occ::down_cast<IntPatch_RLine>(slini)->AddVertex(newptvtx);
              }
            }
          }

          if (!theIsReqToKeepRLine)
          {
            occ::handle<IntPatch_GLine> aGL = occ::down_cast<IntPatch_GLine>(slinj);

            if (!aGL.IsNull())
            {
              HasToDeleteRLine =
                !IsRLineGood(Quad1, Quad2, aGL, occ::down_cast<IntPatch_RLine>(slini), TolArc);
            }

            if (HasToDeleteRLine)
            {
              break;
            }
          }
        }
      }
    }

    if (HasToDeleteRLine)
    {
      slin.Remove(i);
      i--;
      Nblin = slin.Length();
      continue;
    }
  }
}

static bool IntPP(const IntSurf_Quadric&,
                  const IntSurf_Quadric&,
                  const double,
                  const double,
                  bool&,
                  NCollection_Sequence<occ::handle<IntPatch_Line>>&);

static bool IntPCy(const IntSurf_Quadric&,
                   const IntSurf_Quadric&,
                   const double,
                   const double,
                   const bool,
                   bool&,
                   NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                   const double H = 0.);

static bool IntPSp(const IntSurf_Quadric&,
                   const IntSurf_Quadric&,

                   const double,

                   const double,
                   const bool,
                   bool&,
                   NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                   NCollection_Sequence<IntPatch_Point>&);

static bool IntPCo(const IntSurf_Quadric&,
                   const IntSurf_Quadric&,
                   const double,
                   const double,
                   const bool,
                   bool&,
                   bool&,
                   NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                   NCollection_Sequence<IntPatch_Point>&);

static void ProcessBounds(const occ::handle<IntPatch_ALine>&,
                          const NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                          const IntSurf_Quadric&,
                          const IntSurf_Quadric&,
                          bool&,
                          const gp_Pnt&,
                          const double,
                          bool&,
                          const gp_Pnt&,
                          const double,
                          bool&,
                          const double);

static IntPatch_ImpImpIntersection::IntStatus IntCyCy(
  const IntSurf_Quadric&                            theQuad1,
  const IntSurf_Quadric&                            theQuad2,
  const double                                      theTol3D,
  const double                                      theTol2D,
  const Bnd_Box2d&                                  theUVSurf1,
  const Bnd_Box2d&                                  theUVSurf2,
  bool&                                             isTheEmpty,
  bool&                                             isTheSameSurface,
  bool&                                             isTheMultiplePoint,
  NCollection_Sequence<occ::handle<IntPatch_Line>>& theSlin,
  NCollection_Sequence<IntPatch_Point>&             theSPnt);

static bool IntCySp(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    const bool,
                    bool&,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                    NCollection_Sequence<IntPatch_Point>&);

static bool IntCyCo(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    const bool,
                    bool&,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                    NCollection_Sequence<IntPatch_Point>&);

static bool IntSpSp(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    bool&,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                    NCollection_Sequence<IntPatch_Point>&);

static bool IntCoSp(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    const bool,
                    bool&,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                    NCollection_Sequence<IntPatch_Point>&);

static bool IntCoCo(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    bool&,
                    bool&,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&,
                    NCollection_Sequence<IntPatch_Point>&);

static bool IntPTo(const IntSurf_Quadric&,
                   const IntSurf_Quadric&,
                   const double,
                   const bool,
                   bool&,
                   NCollection_Sequence<occ::handle<IntPatch_Line>>&);

static bool IntCyTo(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    const bool,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&);

static bool IntCoTo(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    const bool,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&);

static bool IntSpTo(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    const bool,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&);

static bool IntToTo(const IntSurf_Quadric&,
                    const IntSurf_Quadric&,
                    const double,
                    bool&,
                    bool&,
                    NCollection_Sequence<occ::handle<IntPatch_Line>>&);

static int SetQuad(const occ::handle<Adaptor3d_Surface>& theS,
                   GeomAbs_SurfaceType&                  theTS,
                   IntSurf_Quadric&                      theQuad);

IntPatch_ImpImpIntersection::IntPatch_ImpImpIntersection()
    : myDone(IntStatus_Fail),
      empt(true),
      tgte(false),
      oppo(false)
{
}

IntPatch_ImpImpIntersection::IntPatch_ImpImpIntersection(const occ::handle<Adaptor3d_Surface>&   S1,
                                                         const occ::handle<Adaptor3d_TopolTool>& D1,
                                                         const occ::handle<Adaptor3d_Surface>&   S2,
                                                         const occ::handle<Adaptor3d_TopolTool>& D2,
                                                         const double TolArc,
                                                         const double TolTang,
                                                         const bool   theIsReqToKeepRLine)
{
  Perform(S1, D1, S2, D2, TolArc, TolTang, theIsReqToKeepRLine);
}

void IntPatch_ImpImpIntersection::Perform(const occ::handle<Adaptor3d_Surface>&   S1,
                                          const occ::handle<Adaptor3d_TopolTool>& D1,
                                          const occ::handle<Adaptor3d_Surface>&   S2,
                                          const occ::handle<Adaptor3d_TopolTool>& D2,
                                          const double                            TolArc,
                                          const double                            TolTang,
                                          const bool theIsReqToKeepRLine)
{
  myDone = IntStatus_Fail;
  spnt.Clear();
  slin.Clear();

  bool isPostProcessingRequired = true;

  empt = true;
  tgte = false;
  oppo = false;

  bool all1      = false;
  bool all2      = false;
  bool SameSurf  = false;
  bool multpoint = false;

  bool nosolonS1 = false;

  bool nosolonS2 = false;

  int                                                       i, nbpt, nbseg;
  NCollection_Sequence<IntPatch_TheSegmentOfTheSOnBounds>   edg1, edg2;
  NCollection_Sequence<IntPatch_ThePathPointOfTheSOnBounds> pnt1, pnt2;

  IntSurf_Quadric      quad1, quad2;
  IntPatch_ArcFunction AFunc;
  const double         Tolang = 1.e-8;
  GeomAbs_SurfaceType  typs1, typs2;
  bool                 bEmpty = false;

  const int iT1 = SetQuad(S1, typs1, quad1);
  const int iT2 = SetQuad(S2, typs2, quad2);

  if (!iT1 || !iT2)
  {
    throw Standard_ConstructionError();
    return;
  }

  const bool bReverse = iT1 > iT2;
  const int  iTT      = iT1 * 10 + iT2;

  switch (iTT)
  {
    case 11:
    {
      if (!IntPP(quad1, quad2, Tolang, TolTang, SameSurf, slin))
      {
        return;
      }
      break;
    }

    case 12:
    case 21:
    {
      double VMin, VMax, H;

      const occ::handle<Adaptor3d_Surface>& aSCyl = bReverse ? S1 : S2;
      VMin                                        = aSCyl->FirstVParameter();
      VMax                                        = aSCyl->LastVParameter();
      H = (Precision::IsNegativeInfinite(VMin) || Precision::IsPositiveInfinite(VMax))
            ? 0
            : (VMax - VMin);

      if (!IntPCy(quad1, quad2, Tolang, TolTang, bReverse, empt, slin, H))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 13:
    case 31:
    {
      if (!IntPCo(quad1, quad2, Tolang, TolTang, bReverse, empt, multpoint, slin, spnt))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 14:
    case 41:
    {
      if (!IntPSp(quad1, quad2, Tolang, TolTang, bReverse, empt, slin, spnt))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 15:
    case 51:
    {
      if (!IntPTo(quad1, quad2, TolTang, bReverse, empt, slin))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 22:
    {
      Bnd_Box2d aBox1, aBox2;

      const double aU1f = S1->FirstUParameter();
      double       aU1l = S1->LastUParameter();
      const double aU2f = S2->FirstUParameter();
      double       aU2l = S2->LastUParameter();

      const double anUperiod = 2.0 * M_PI;

      if (aU1l - aU1f > anUperiod)
        aU1l = aU1f + anUperiod;

      if (aU2l - aU2f > anUperiod)
        aU2l = aU2f + anUperiod;

      aBox1.Add(gp_Pnt2d(aU1f, S1->FirstVParameter()));
      aBox1.Add(gp_Pnt2d(aU1l, S1->LastVParameter()));
      aBox2.Add(gp_Pnt2d(aU2f, S2->FirstVParameter()));
      aBox2.Add(gp_Pnt2d(aU2l, S2->LastVParameter()));

      const double a2DTol =
        std::min(1.0e-4, std::min(S1->UResolution(TolTang), S2->UResolution(TolTang)));

      myDone =
        IntCyCy(quad1, quad2, TolTang, a2DTol, aBox1, aBox2, empt, SameSurf, multpoint, slin, spnt);

      if (myDone == IntPatch_ImpImpIntersection::IntStatus_Fail)
      {
        return;
      }

      bEmpty = empt;
      if (!slin.IsEmpty())
      {
        const occ::handle<IntPatch_WLine>& aWLine = occ::down_cast<IntPatch_WLine>(slin.Value(1));

        if (!aWLine.IsNull())
        {
          isPostProcessingRequired = false;
        }
      }

      break;
    }

    case 23:
    case 32:
    {
      if (!IntCyCo(quad1, quad2, TolTang, bReverse, empt, multpoint, slin, spnt))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 24:
    case 42:
    {
      if (!IntCySp(quad1, quad2, TolTang, bReverse, empt, multpoint, slin, spnt))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 25:
    case 52:
    {
      if (!IntCyTo(quad1, quad2, TolTang, bReverse, empt, slin))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 33:
    {
      if (!IntCoCo(quad1, quad2, TolTang, empt, SameSurf, multpoint, slin, spnt))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 34:
    case 43:
    {
      if (!IntCoSp(quad1, quad2, TolTang, bReverse, empt, multpoint, slin, spnt))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 35:
    case 53:
    {
      if (!IntCoTo(quad1, quad2, TolTang, bReverse, empt, slin))
      {
        return;
      }
      break;
    }

    case 44:
    {
      if (!IntSpSp(quad1, quad2, TolTang, empt, SameSurf, slin, spnt))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 45:
    case 54:
    {
      if (!IntSpTo(quad1, quad2, TolTang, bReverse, empt, slin))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    case 55:
    {
      if (!IntToTo(quad1, quad2, TolTang, SameSurf, empt, slin))
      {
        return;
      }
      bEmpty = empt;
      break;
    }

    default:
    {
      throw Standard_ConstructionError();
      break;
    }
  }

  if (bEmpty)
  {
    if (myDone == IntStatus_Fail)
      myDone = IntStatus_OK;

    return;
  }

  if (isPostProcessingRequired)
  {
    if (!SameSurf)
    {
      AFunc.SetQuadric(quad2);
      AFunc.Set(S1);

      solrst.Perform(AFunc, D1, TolArc, TolTang);
      if (!solrst.IsDone())
      {
        return;
      }

      if (solrst.AllArcSolution() && typs1 == typs2)
      {
        all1 = true;
      }
      nbpt  = solrst.NbPoints();
      nbseg = solrst.NbSegments();
      for (i = 1; i <= nbpt; i++)
      {
        const IntPatch_ThePathPointOfTheSOnBounds& aPt = solrst.Point(i);
        pnt1.Append(aPt);
      }
      for (i = 1; i <= nbseg; i++)
      {
        const IntPatch_TheSegmentOfTheSOnBounds& aSegm = solrst.Segment(i);
        edg1.Append(aSegm);
      }
      nosolonS1 = (nbpt == 0) && (nbseg == 0);

      if (nosolonS1 && all1)
      {
        all1 = false;
      }
    }
    else
    {
      nosolonS1 = true;
    }

    if (!SameSurf)
    {
      AFunc.SetQuadric(quad1);
      AFunc.Set(S2);

      solrst.Perform(AFunc, D2, TolArc, TolTang);
      if (!solrst.IsDone())
      {
        return;
      }

      if (solrst.AllArcSolution() && typs1 == typs2)
      {
        all2 = true;
      }

      nbpt  = solrst.NbPoints();
      nbseg = solrst.NbSegments();
      for (i = 1; i <= nbpt; i++)
      {
        const IntPatch_ThePathPointOfTheSOnBounds& aPt = solrst.Point(i);
        pnt2.Append(aPt);
      }

      for (i = 1; i <= nbseg; i++)
      {
        const IntPatch_TheSegmentOfTheSOnBounds& aSegm = solrst.Segment(i);
        edg2.Append(aSegm);
      }

      nosolonS2 = (nbpt == 0) && (nbseg == 0);

      if (nosolonS2 && all2)
      {
        all2 = false;
      }
    }
    else
    {
      nosolonS2 = true;
    }

    if (SameSurf || (all1 && all2))
    {

      empt = false;
      tgte = true;
      slin.Clear();
      spnt.Clear();

      gp_Pnt Ptreference;

      switch (typs1)
      {
        case GeomAbs_Plane:
        {
          Ptreference = (S1->Plane()).Location();
        }
        break;
        case GeomAbs_Cylinder:
        {
          Ptreference = ElSLib::Value(0., 0., S1->Cylinder());
        }
        break;
        case GeomAbs_Sphere:
        {
          Ptreference = ElSLib::Value(M_PI / 4., M_PI / 4., S1->Sphere());
        }
        break;
        case GeomAbs_Cone:
        {
          Ptreference = ElSLib::Value(0., 10., S1->Cone());
        }
        break;
        case GeomAbs_Torus:
        {
          Ptreference = ElSLib::Value(0., 0., S1->Torus());
        }
        break;
        default:
          break;
      }

      oppo   = quad1.Normale(Ptreference).Dot(quad2.Normale(Ptreference)) < 0.0;
      myDone = IntStatus_OK;
      return;
    }

    if (!nosolonS1 || !nosolonS2)
    {
      empt = false;

      PutPointsOnLine(S1, S2, pnt1, slin, true, D1, quad1, quad2, multpoint, TolArc);

      PutPointsOnLine(S1, S2, pnt2, slin, false, D2, quad2, quad1, multpoint, TolArc);

      if (edg1.Length() != 0)
      {
        ProcessSegments(edg1, slin, quad1, quad2, true, TolArc);
      }

      if (edg2.Length() != 0)
      {
        ProcessSegments(edg2, slin, quad1, quad2, false, TolArc);
      }

      if (edg1.Length() != 0 || edg2.Length() != 0)
      {

        ProcessRLine(slin, quad1, quad2, TolArc, theIsReqToKeepRLine);
      }
    }
    else
    {
      empt = ((slin.Length() == 0) && (spnt.Length() == 0));
    }
  }

  int nblin = slin.Length(), aNbPnt = spnt.Length();

  if (aNbPnt)
  {
    NCollection_Sequence<IntPatch_Point> aSIP;

    for (i = 1; i <= aNbPnt; ++i)
    {
      double       aU1, aV1, aU2, aV2;
      gp_Pnt2d     aP2D;
      TopAbs_State aState1, aState2;

      const IntPatch_Point& aIP = spnt(i);
      aIP.Parameters(aU1, aV1, aU2, aV2);

      aP2D.SetCoord(aU1, aV1);
      aState1 = D1->Classify(aP2D, TolArc);

      aP2D.SetCoord(aU2, aV2);
      aState2 = D2->Classify(aP2D, TolArc);

      if (aState1 != TopAbs_OUT && aState2 != TopAbs_OUT)
      {
        aSIP.Append(aIP);
      }
    }

    spnt.Clear();

    aNbPnt = aSIP.Length();
    for (i = 1; i <= aNbPnt; ++i)
    {
      const IntPatch_Point& aIP = aSIP(i);
      spnt.Append(aIP);
    }
  }

  for (i = 1; i <= nblin; i++)
  {
    IntPatch_IType thetype = slin.Value(i)->ArcType();
    if ((thetype == IntPatch_Ellipse) || (thetype == IntPatch_Circle) || (thetype == IntPatch_Lin)
        || (thetype == IntPatch_Parabola) || (thetype == IntPatch_Hyperbola))
    {
      occ::handle<IntPatch_GLine>& glin = *((occ::handle<IntPatch_GLine>*)&slin.Value(i));
      glin->ComputeVertexParameters(TolArc);
    }
    else if (thetype == IntPatch_Analytic)
    {
      occ::handle<IntPatch_ALine>& aligold = *((occ::handle<IntPatch_ALine>*)&slin.Value(i));
      aligold->ComputeVertexParameters(TolArc);
    }
    else if (thetype == IntPatch_Restriction)
    {
      occ::handle<IntPatch_RLine>& rlig = *((occ::handle<IntPatch_RLine>*)&slin.Value(i));
      rlig->ComputeVertexParameters(TolArc);
    }
  }

  for (i = 1; i <= nblin; i++)
  {
    gp_Pnt         P;
    IntPatch_Point point;
    double         u1, v1, u2, v2;
    if (slin.Value(i)->ArcType() == IntPatch_Circle)
    {
      const occ::handle<IntPatch_GLine>& glin = *((occ::handle<IntPatch_GLine>*)&slin.Value(i));
      if (glin->NbVertex() == 0)
      {
        gp_Circ Circ = glin->Circle();
        P            = ElCLib::Value(0.0, Circ);
        quad1.Parameters(P, u1, v1);
        quad2.Parameters(P, u2, v2);
        point.SetValue(P, TolArc, false);
        point.SetParameters(u1, v1, u2, v2);
        point.SetParameter(0.0);
        glin->AddVertex(point);

        P = ElCLib::Value(0.0, Circ);
        quad1.Parameters(P, u1, v1);
        quad2.Parameters(P, u2, v2);
        point.SetValue(P, TolArc, false);
        point.SetParameters(u1, v1, u2, v2);
        point.SetParameter(M_PI + M_PI);
        glin->AddVertex(point);
      }
    }

    else if (slin.Value(i)->ArcType() == IntPatch_Ellipse)
    {
      const occ::handle<IntPatch_GLine>& glin = *((occ::handle<IntPatch_GLine>*)&slin.Value(i));
      if (glin->NbVertex() == 0)
      {
        gp_Elips Elips = glin->Ellipse();
        P              = ElCLib::Value(0.0, Elips);
        quad1.Parameters(P, u1, v1);
        quad2.Parameters(P, u2, v2);
        point.SetValue(P, TolArc, false);
        point.SetParameters(u1, v1, u2, v2);
        point.SetParameter(0.0);
        glin->AddVertex(point);

        P = ElCLib::Value(0.0, Elips);
        quad1.Parameters(P, u1, v1);
        quad2.Parameters(P, u2, v2);
        point.SetValue(P, TolArc, false);
        point.SetParameters(u1, v1, u2, v2);
        point.SetParameter(M_PI + M_PI);
        glin->AddVertex(point);
      }
    }
  }
  myDone = IntStatus_OK;
}

int SetQuad(const occ::handle<Adaptor3d_Surface>& theS,
            GeomAbs_SurfaceType&                  theTS,
            IntSurf_Quadric&                      theQuad)
{
  theTS    = theS->GetType();
  int iRet = 0;
  switch (theTS)
  {
    case GeomAbs_Plane:
      theQuad.SetValue(theS->Plane());
      iRet = 1;
      break;
    case GeomAbs_Cylinder:
      theQuad.SetValue(theS->Cylinder());
      iRet = 2;
      break;
    case GeomAbs_Cone:
      theQuad.SetValue(theS->Cone());
      iRet = 3;
      break;
    case GeomAbs_Sphere:
      theQuad.SetValue(theS->Sphere());
      iRet = 4;
      break;
    case GeomAbs_Torus:
      theQuad.SetValue(theS->Torus());
      iRet = 5;
      break;
    default:
      break;
  }

  return iRet;
}

static void SeamPosition(const gp_Pnt& aPLoc, const gp_Ax3& aPos, gp_Ax2& aSeamPos);
static void AdjustToSeam(const gp_Cylinder& aQuad, gp_Circ& aCirc);
static void AdjustToSeam(const gp_Sphere& aQuad, gp_Circ& aCirc, const double aTolAng);
static void AdjustToSeam(const gp_Cone& aQuad, gp_Circ& aCirc);
static void AdjustToSeam(const gp_Torus& aQuad, gp_Circ& aCirc);

bool IntPP(const IntSurf_Quadric&                            Quad1,
           const IntSurf_Quadric&                            Quad2,
           const double                                      Tolang,
           const double                                      TolTang,
           bool&                                             Same,
           NCollection_Sequence<occ::handle<IntPatch_Line>>& slin)

{
  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;
  gp_Pln            pl1(Quad1.Plane());
  gp_Pln            pl2(Quad2.Plane());

  IntAna_QuadQuadGeo inter(pl1, pl2, Tolang, TolTang);
  if (!inter.IsDone())
  {
    return false;
  }
  Same   = false;
  typint = inter.TypeInter();
  if (typint == IntAna_Same)
  {
    Same = true;
  }
  else if (typint != IntAna_Empty)
  {
    gp_Lin linsol = inter.Line(1);
    double discri = linsol.Direction().DotCross(Quad2.Normale(linsol.Location()),
                                                Quad1.Normale(linsol.Location()));

    if (discri > 0.0)
    {
      trans1 = IntSurf_Out;
      trans2 = IntSurf_In;
    }
    else
    {
      trans1 = IntSurf_In;
      trans2 = IntSurf_Out;
    }
    occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(linsol, false, trans1, trans2);
    slin.Append(glig);
  }
  return true;
}

bool IntPCy(const IntSurf_Quadric&                            Quad1,
            const IntSurf_Quadric&                            Quad2,
            const double                                      Tolang,
            const double                                      TolTang,
            const bool                                        Reversed,
            bool&                                             Empty,
            NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
            const double                                      H)

{
  gp_Pln      Pl;
  gp_Cylinder Cy;

  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;

  IntAna_QuadQuadGeo inter;
  if (!Reversed)
  {
    Pl = Quad1.Plane();
    Cy = Quad2.Cylinder();
  }
  else
  {
    Pl = Quad2.Plane();
    Cy = Quad1.Cylinder();
  }
  inter.Perform(Pl, Cy, Tolang, TolTang, H);
  if (!inter.IsDone())
  {
    return false;
  }
  typint    = inter.TypeInter();
  int NbSol = inter.NbSolutions();
  Empty     = false;

  switch (typint)
  {
    case IntAna_Empty:
    {
      Empty = true;
    }
    break;

    case IntAna_Line:
    {
      gp_Lin linsol = inter.Line(1);
      gp_Pnt orig(linsol.Location());
      if (NbSol == 1)
      {
        gp_Vec TestCurvature(orig, Cy.Location());
        gp_Vec Normp, Normcyl;
        if (!Reversed)
        {
          Normp   = Quad1.Normale(orig);
          Normcyl = Quad2.Normale(orig);
        }
        else
        {
          Normp   = Quad2.Normale(orig);
          Normcyl = Quad1.Normale(orig);
        }

        IntSurf_Situation situcyl;
        IntSurf_Situation situp;

        if (Normp.Dot(TestCurvature) > 0.)
        {
          situcyl = IntSurf_Outside;
          if (Normp.Dot(Normcyl) > 0.)
          {
            situp = IntSurf_Inside;
          }
          else
          {
            situp = IntSurf_Outside;
          }
        }
        else
        {
          situcyl = IntSurf_Inside;
          if (Normp.Dot(Normcyl) > 0.)
          {
            situp = IntSurf_Outside;
          }
          else
          {
            situp = IntSurf_Inside;
          }
        }
        occ::handle<IntPatch_GLine> glig;
        if (!Reversed)
        {
          glig = new IntPatch_GLine(linsol, true, situp, situcyl);
        }
        else
        {
          glig = new IntPatch_GLine(linsol, true, situcyl, situp);
        }
        slin.Append(glig);
      }
      else
      {

        if (linsol.Direction().DotCross(Quad2.Normale(orig), Quad1.Normale(orig)) > 0.)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(linsol, false, trans1, trans2);
        slin.Append(glig);

        linsol = inter.Line(2);
        orig   = linsol.Location();

        if (linsol.Direction().DotCross(Quad2.Normale(orig), Quad1.Normale(orig)) > 0.)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        glig = new IntPatch_GLine(linsol, false, trans1, trans2);
        slin.Append(glig);
      }
    }
    break;

    case IntAna_Circle:
    {
      gp_Circ cirsol;
      gp_Pnt  ptref;
      gp_Vec  Tgt;

      cirsol = inter.Circle(1);

      AdjustToSeam(Cy, cirsol);

      ElCLib::D1(0., cirsol, ptref, Tgt);

      if (Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref)) > 0.0)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
      slin.Append(glig);
    }
    break;

    case IntAna_Ellipse:
    {
      gp_Elips elipsol = inter.Ellipse(1);
      gp_Pnt   ptref;
      gp_Vec   Tgt;
      ElCLib::D1(0., elipsol, ptref, Tgt);

      if (Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref)) > 0.0)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(elipsol, false, trans1, trans2);
      slin.Append(glig);
    }
    break;

    default:
    {
      return false;
    }
  }
  return true;
}

bool IntPSp(const IntSurf_Quadric& Quad1,
            const IntSurf_Quadric& Quad2,

            const double Tolang,

            const double                                      TolTang,
            const bool                                        Reversed,
            bool&                                             Empty,
            NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
            NCollection_Sequence<IntPatch_Point>&             spnt)

{
  gp_Circ           cirsol;
  gp_Pln            Pl;
  gp_Sphere         Sp;
  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;

  IntAna_QuadQuadGeo inter;
  if (!Reversed)
  {
    Pl = Quad1.Plane();
    Sp = Quad2.Sphere();
  }
  else
  {
    Pl = Quad2.Plane();
    Sp = Quad1.Sphere();
  }
  inter.Perform(Pl, Sp);

  if (!inter.IsDone())
  {
    return false;
  }

  typint = inter.TypeInter();
  Empty  = false;

  switch (typint)
  {
    case IntAna_Empty:
    {
      Empty = true;
    }
    break;

    case IntAna_Point:
    {
      gp_Pnt psol = inter.Point(1);
      double U1, V1, U2, V2;
      Quad1.Parameters(psol, U1, V1);
      Quad2.Parameters(psol, U2, V2);
      IntPatch_Point ptsol;
      ptsol.SetValue(psol, TolTang, true);
      ptsol.SetParameters(U1, V1, U2, V2);
      spnt.Append(ptsol);
    }
    break;

    case IntAna_Circle:
    {
      cirsol = inter.Circle(1);

      AdjustToSeam(Sp, cirsol, Tolang);

      gp_Pnt ptref;
      gp_Vec Tgt;
      ElCLib::D1(0., cirsol, ptref, Tgt);

      if (Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref)) > 0.)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
      slin.Append(glig);
    }
    break;

    default:
    {
      return false;
    }
  }
  return true;
}

bool IntPCo(const IntSurf_Quadric&                            Quad1,
            const IntSurf_Quadric&                            Quad2,
            const double                                      Tolang,
            const double                                      TolTang,
            const bool                                        Reversed,
            bool&                                             Empty,
            bool&                                             Multpoint,
            NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
            NCollection_Sequence<IntPatch_Point>&             spnt)

{
  gp_Pnt apex;

  gp_Pln  Pl;
  gp_Cone Co;

  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;

  IntAna_QuadQuadGeo inter;
  if (!Reversed)
  {
    Pl   = Quad1.Plane();
    Co   = Quad2.Cone();
    apex = Co.Apex();
  }
  else
  {
    Pl   = Quad2.Plane();
    Co   = Quad1.Cone();
    apex = Co.Apex();
  }

  inter.Perform(Pl, Co, Tolang, TolTang);
  if (!inter.IsDone())
  {
    return false;
  }

  typint    = inter.TypeInter();
  int NbSol = inter.NbSolutions();
  Empty     = false;

  switch (typint)
  {
    case IntAna_Point:
    {
      gp_Pnt psol = inter.Point(1);
      double U1, V1, U2, V2;
      Quad1.Parameters(psol, U1, V1);
      Quad2.Parameters(psol, U2, V2);
      IntPatch_Point ptsol;
      ptsol.SetValue(psol, TolTang, false);
      ptsol.SetParameters(U1, V1, U2, V2);
      spnt.Append(ptsol);
    }
    break;

    case IntAna_Line:
    {
      gp_Lin linsol = inter.Line(1);
      if (linsol.Direction().Dot(Co.Axis().Direction()) < 0.)
      {
        linsol.SetDirection(linsol.Direction().Reversed());
      }
      double para = ElCLib::Parameter(linsol, apex);
      gp_Pnt ptbid(ElCLib::Value(para + 5., linsol));
      double U1, V1, U2, V2;
      Quad1.Parameters(apex, U1, V1);
      Quad2.Parameters(apex, U2, V2);

      if (NbSol == 1)
      {
        IntPatch_Point ptsol;
        ptsol.SetValue(apex, TolTang, false);
        ptsol.SetParameters(U1, V1, U2, V2);
        ptsol.SetParameter(para);
        gp_Pnt ptbid2(apex.XYZ() + 5. * Co.Axis().Direction().XYZ());
        gp_Vec TestCurvature(ptbid, ptbid2);
        gp_Vec Normp, Normco;
        if (!Reversed)
        {
          Normp  = Quad1.Normale(ptbid);
          Normco = Quad2.Normale(ptbid);
        }
        else
        {
          Normp  = Quad2.Normale(ptbid);
          Normco = Quad1.Normale(ptbid);
        }
        IntSurf_Situation situco, situco_otherside;
        IntSurf_Situation situp, situp_otherside;

        if (Normp.Dot(TestCurvature) > 0.)
        {
          situco           = IntSurf_Outside;
          situco_otherside = IntSurf_Inside;
          if (Normp.Dot(Normco) > 0.)
          {
            situp           = IntSurf_Inside;
            situp_otherside = IntSurf_Outside;
          }
          else
          {
            situp           = IntSurf_Outside;
            situp_otherside = IntSurf_Inside;
          }
        }
        else
        {
          situco           = IntSurf_Inside;
          situco_otherside = IntSurf_Outside;
          if (Normp.Dot(Normco) > 0.)
          {
            situp           = IntSurf_Outside;
            situp_otherside = IntSurf_Inside;
          }
          else
          {
            situp           = IntSurf_Inside;
            situp_otherside = IntSurf_Outside;
          }
        }

        occ::handle<IntPatch_GLine> glig;
        if (!Reversed)
        {
          glig = new IntPatch_GLine(linsol, true, situp, situco);
        }
        else
        {
          glig = new IntPatch_GLine(linsol, true, situco, situp);
        }
        glig->AddVertex(ptsol);
        glig->SetFirstPoint(1);
        slin.Append(glig);

        linsol.SetDirection(linsol.Direction().Reversed());
        if (!Reversed)
        {
          glig = new IntPatch_GLine(linsol, true, situp_otherside, situco_otherside);
        }
        else
        {
          glig = new IntPatch_GLine(linsol, true, situco_otherside, situp_otherside);
        }
        glig->AddVertex(ptsol);
        glig->SetFirstPoint(1);
        slin.Append(glig);
      }
      else
      {

        if (linsol.Direction().DotCross(Quad2.Normale(ptbid), Quad1.Normale(ptbid)) > 0.)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }

        Multpoint = true;

        IntPatch_Point ptsol;
        ptsol.SetValue(apex, TolTang, false);
        ptsol.SetParameters(U1, V1, U2, V2);
        ptsol.SetParameter(para);
        ptsol.SetMultiple(true);
        occ::handle<IntPatch_GLine> glig;
        glig = new IntPatch_GLine(linsol, false, trans1, trans2);
        glig->AddVertex(ptsol);
        glig->SetFirstPoint(1);
        slin.Append(glig);

        linsol.SetDirection(linsol.Direction().Reversed());
        glig = new IntPatch_GLine(linsol, false, trans1, trans2);
        para = ElCLib::Parameter(linsol, apex);
        ptsol.SetParameter(para);
        glig->AddVertex(ptsol);
        glig->SetFirstPoint(1);
        slin.Append(glig);

        linsol = inter.Line(2);
        if (linsol.Direction().Dot(Co.Axis().Direction()) < 0.)
        {
          linsol.SetDirection(linsol.Direction().Reversed());
        }
        para  = ElCLib::Parameter(linsol, apex);
        ptbid = ElCLib::Value(para + 5., linsol);
        if (linsol.Direction().DotCross(Quad2.Normale(ptbid), Quad1.Normale(ptbid)) > 0.)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        ptsol.SetParameter(para);
        glig = new IntPatch_GLine(linsol, false, trans1, trans2);
        para = ElCLib::Parameter(linsol, apex);
        ptsol.SetParameter(para);
        glig->AddVertex(ptsol);
        glig->SetFirstPoint(1);
        slin.Append(glig);

        linsol.SetDirection(linsol.Direction().Reversed());
        glig = new IntPatch_GLine(linsol, false, trans1, trans2);
        para = ElCLib::Parameter(linsol, apex);
        ptsol.SetParameter(para);
        glig->AddVertex(ptsol);
        glig->SetFirstPoint(1);
        slin.Append(glig);
      }
    }
    break;

    case IntAna_Circle:
    {
      gp_Circ cirsol = inter.Circle(1);

      AdjustToSeam(Co, cirsol);

      gp_Pnt ptref;
      gp_Vec Tgt;
      ElCLib::D1(0., cirsol, ptref, Tgt);

      if (Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref)) > 0.)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
      slin.Append(glig);
    }
    break;

    case IntAna_Ellipse:
    {
      gp_Elips elipsol = inter.Ellipse(1);
      gp_Pnt   ptref;
      gp_Vec   Tgt;
      ElCLib::D1(0., elipsol, ptref, Tgt);

      if (Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref)) > 0.)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(elipsol, false, trans1, trans2);
      slin.Append(glig);
    }
    break;

    case IntAna_Parabola:
    {
      gp_Parab parabsol = inter.Parabola(1);

      gp_Vec Tgtorig(parabsol.YAxis().Direction());
      double ptran =
        Tgtorig.DotCross(Quad2.Normale(parabsol.Location()), Quad1.Normale(parabsol.Location()));
      if (ptran > 0.00000001)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else if (ptran < -0.00000001)
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      else
      {
        trans1 = trans2 = IntSurf_Undecided;
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(parabsol, false, trans1, trans2);
      slin.Append(glig);
    }
    break;

    case IntAna_Hyperbola:
    {
      gp_Pnt tophypr;
      gp_Vec Tgttop;

      for (int i = 1; i <= 2; i++)
      {
        gp_Hypr hyprsol = inter.Hyperbola(i);
        tophypr         = ElCLib::Value(hyprsol.MajorRadius(), hyprsol.XAxis());
        Tgttop          = hyprsol.YAxis().Direction();
        double qwe      = Tgttop.DotCross(Quad2.Normale(tophypr), Quad1.Normale(tophypr));

        if (qwe > 0.00000001)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe < -0.00000001)
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(hyprsol, false, trans1, trans2);
        slin.Append(glig);
      }
    }
    break;

    default:
    {
      return false;
    }
  }
  return true;
}

bool IntPTo(const IntSurf_Quadric&                            theQuad1,
            const IntSurf_Quadric&                            theQuad2,
            const double                                      theTolTang,
            const bool                                        bReversed,
            bool&                                             bEmpty,
            NCollection_Sequence<occ::handle<IntPatch_Line>>& theSeqLin)
{
  const gp_Pln   aPln   = bReversed ? theQuad2.Plane() : theQuad1.Plane();
  const gp_Torus aTorus = bReversed ? theQuad1.Torus() : theQuad2.Torus();

  IntAna_QuadQuadGeo inter(aPln, aTorus, theTolTang);
  bool               bRet = inter.IsDone();

  if (!bRet)
  {
    return bRet;
  }

  IntAna_ResultType typint = inter.TypeInter();
  int               NbSol  = inter.NbSolutions();
  bEmpty                   = false;

  switch (typint)
  {
    case IntAna_Empty:
      bEmpty = true;
      break;

    case IntAna_Circle:
    {
      int               i;
      IntSurf_TypeTrans trans1, trans2;
      gp_Pnt            ptref;
      gp_Vec            Tgt;

      for (i = 1; i <= NbSol; ++i)
      {
        gp_Circ aC = inter.Circle(i);
        if (!aPln.Axis().IsNormal(aTorus.Axis(), Precision::Angular()))
        {
          AdjustToSeam(aTorus, aC);
        }
        ElCLib::D1(0., aC, ptref, Tgt);

        if (Tgt.DotCross(theQuad2.Normale(ptref), theQuad1.Normale(ptref)) > 0.0)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }

        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(aC, false, trans1, trans2);
        theSeqLin.Append(glig);
      }
    }
    break;

    case IntAna_NoGeometricSolution:
    default:
      bRet = false;
      break;
  }

  return bRet;
}

void AdjustToSeam(const gp_Cone& aQuad, gp_Circ& aCirc)
{
  gp_Ax2 aAx2;

  const gp_Pnt& aPLoc = aCirc.Location();
  const gp_Ax3& aAx3  = aQuad.Position();
  SeamPosition(aPLoc, aAx3, aAx2);
  aCirc.SetPosition(aAx2);
}

void AdjustToSeam(const gp_Sphere& aQuad, gp_Circ& aCirc, const double aTolAng)
{
  gp_Ax2 aAx2;

  const gp_Ax1& aAx1C = aCirc.Axis();
  const gp_Ax3& aAx3  = aQuad.Position();
  const gp_Ax1& aAx1Q = aAx3.Axis();

  const gp_Dir& aDirC = aAx1C.Direction();
  const gp_Dir& aDirQ = aAx1Q.Direction();
  if (aDirC.IsParallel(aDirQ, aTolAng))
  {
    const gp_Pnt& aPLoc = aCirc.Location();
    SeamPosition(aPLoc, aAx3, aAx2);
    aCirc.SetPosition(aAx2);
  }
}

void AdjustToSeam(const gp_Cylinder& aQuad, gp_Circ& aCirc)
{
  gp_Ax2 aAx2;

  const gp_Pnt& aPLoc = aCirc.Location();
  const gp_Ax3& aAx3  = aQuad.Position();
  SeamPosition(aPLoc, aAx3, aAx2);
  aCirc.SetPosition(aAx2);
}

void AdjustToSeam(const gp_Torus& aQuad, gp_Circ& aCirc)
{
  gp_Ax2 aAx2;

  const gp_Pnt& aPLoc = aCirc.Location();
  const gp_Ax3& aAx3  = aQuad.Position();
  SeamPosition(aPLoc, aAx3, aAx2);
  aCirc.SetPosition(aAx2);
}

void SeamPosition(const gp_Pnt& aPLoc, const gp_Ax3& aPos, gp_Ax2& aSeamPos)
{
  const gp_Dir& aDZ = aPos.Direction();
  const gp_Dir& aDX = aPos.XDirection();
  gp_Ax2        aAx2(aPLoc, aDZ, aDX);
  aSeamPos = aAx2;
}

static const double aNulValue = 1.0e-11;

static void ShortCosForm(const double theCosFactor,
                         const double theSinFactor,
                         double&      theCoeff,
                         double&      theAngle);

static bool ExploreCurve(const gp_Cone&                  theCo,
                         IntAna_Curve&                   aC,
                         const double                    aTol,
                         NCollection_List<IntAna_Curve>& aLC);

static bool InscribePoint(const double theUfTarget,
                          const double theUlTarget,
                          double&      theUGiven,
                          const double theTol2D,
                          const double thePeriod,
                          const bool   theFlForce);

class ComputationMethods
{

public:
  struct stCoeffsValue
  {
    stCoeffsValue(const gp_Cylinder&, const gp_Cylinder&);

    math_Vector mVecA1;
    math_Vector mVecA2;
    math_Vector mVecB1;
    math_Vector mVecB2;
    math_Vector mVecC1;
    math_Vector mVecC2;
    math_Vector mVecD;

    double mK21;
    double mK11;
    double mL21;
    double mL11;
    double mM1;

    double mK22;
    double mK12;
    double mL22;
    double mL12;
    double mM2;

    double mK1;
    double mL1;
    double mK2;
    double mL2;

    double mFIV1;
    double mPSIV1;
    double mFIV2;
    double mPSIV2;

    double mB;
    double mC;
    double mFI1;
    double mFI2;
  };

  static bool CylCylMonotonicity(const double         theU1par,
                                 const int            theWLIndex,
                                 const stCoeffsValue& theCoeffs,
                                 const double         thePeriod,
                                 bool&                theIsIncreasing);

  static bool CylCylComputeParameters(const double         theU1par,
                                      const int            theWLIndex,
                                      const stCoeffsValue& theCoeffs,
                                      double&              theU2,
                                      double* const        theDelta = nullptr);

  static bool CylCylComputeParameters(const double         theU1,
                                      const double         theU2,
                                      const stCoeffsValue& theCoeffs,
                                      double&              theV1,
                                      double&              theV2);

  static bool CylCylComputeParameters(const double         theU1par,
                                      const int            theWLIndex,
                                      const stCoeffsValue& theCoeffs,
                                      double&              theU2,
                                      double&              theV1,
                                      double&              theV2);
};

ComputationMethods::stCoeffsValue::stCoeffsValue(const gp_Cylinder& theCyl1,
                                                 const gp_Cylinder& theCyl2)
    : mVecA1(-theCyl1.Radius() * theCyl1.XAxis().Direction().XYZ()),
      mVecA2(theCyl2.Radius() * theCyl2.XAxis().Direction().XYZ()),
      mVecB1(-theCyl1.Radius() * theCyl1.YAxis().Direction().XYZ()),
      mVecB2(theCyl2.Radius() * theCyl2.YAxis().Direction().XYZ()),
      mVecC1(theCyl1.Axis().Direction().XYZ()),
      mVecC2(theCyl2.Axis().Direction().XYZ().Reversed()),
      mVecD(theCyl2.Location().XYZ() - theCyl1.Location().XYZ())
{
  enum CoupleOfEquation
  {
    COENONE = 0,
    COE12   = 1,
    COE23   = 2,
    COE13   = 3
  } aFoundCouple = COENONE;

  double aDetV1V2 = 0.0;

  const double aDelta1 = mVecC1(1) * mVecC2(2) - mVecC1(2) * mVecC2(1);
  const double aDelta2 = mVecC1(2) * mVecC2(3) - mVecC1(3) * mVecC2(2);
  const double aDelta3 = mVecC1(1) * mVecC2(3) - mVecC1(3) * mVecC2(1);
  const double anAbsD1 = std::abs(aDelta1);
  const double anAbsD2 = std::abs(aDelta2);
  const double anAbsD3 = std::abs(aDelta3);

  if (anAbsD1 >= anAbsD2)
  {
    if (anAbsD3 > anAbsD1)
    {
      aFoundCouple = COE13;
      aDetV1V2     = aDelta3;
    }
    else
    {
      aFoundCouple = COE12;
      aDetV1V2     = aDelta1;
    }
  }
  else
  {
    if (anAbsD3 > anAbsD2)
    {
      aFoundCouple = COE13;
      aDetV1V2     = aDelta3;
    }
    else
    {
      aFoundCouple = COE23;
      aDetV1V2     = aDelta2;
    }
  }

  if (std::abs(aDetV1V2) < Precision::Angular())
  {
    throw Standard_Failure("Error. Exception in divide by zerro (IntCyCyTrim)!!!!");
  }

  switch (aFoundCouple)
  {
    case COE12:
      break;
    case COE23:
    {
      math_Vector aVTemp(mVecA1);
      mVecA1(1) = aVTemp(2);
      mVecA1(2) = aVTemp(3);
      mVecA1(3) = aVTemp(1);

      aVTemp    = mVecA2;
      mVecA2(1) = aVTemp(2);
      mVecA2(2) = aVTemp(3);
      mVecA2(3) = aVTemp(1);

      aVTemp    = mVecB1;
      mVecB1(1) = aVTemp(2);
      mVecB1(2) = aVTemp(3);
      mVecB1(3) = aVTemp(1);

      aVTemp    = mVecB2;
      mVecB2(1) = aVTemp(2);
      mVecB2(2) = aVTemp(3);
      mVecB2(3) = aVTemp(1);

      aVTemp    = mVecC1;
      mVecC1(1) = aVTemp(2);
      mVecC1(2) = aVTemp(3);
      mVecC1(3) = aVTemp(1);

      aVTemp    = mVecC2;
      mVecC2(1) = aVTemp(2);
      mVecC2(2) = aVTemp(3);
      mVecC2(3) = aVTemp(1);

      aVTemp   = mVecD;
      mVecD(1) = aVTemp(2);
      mVecD(2) = aVTemp(3);
      mVecD(3) = aVTemp(1);

      break;
    }
    case COE13:
    {
      math_Vector aVTemp = mVecA1;
      mVecA1(2)          = aVTemp(3);
      mVecA1(3)          = aVTemp(2);

      aVTemp    = mVecA2;
      mVecA2(2) = aVTemp(3);
      mVecA2(3) = aVTemp(2);

      aVTemp    = mVecB1;
      mVecB1(2) = aVTemp(3);
      mVecB1(3) = aVTemp(2);

      aVTemp    = mVecB2;
      mVecB2(2) = aVTemp(3);
      mVecB2(3) = aVTemp(2);

      aVTemp    = mVecC1;
      mVecC1(2) = aVTemp(3);
      mVecC1(3) = aVTemp(2);

      aVTemp    = mVecC2;
      mVecC2(2) = aVTemp(3);
      mVecC2(3) = aVTemp(2);

      aVTemp   = mVecD;
      mVecD(2) = aVTemp(3);
      mVecD(3) = aVTemp(2);

      break;
    }
    default:
      break;
  }

  mK21 = (mVecC2(2) * mVecB2(1) - mVecC2(1) * mVecB2(2)) / aDetV1V2;

  mK11 = (mVecC2(2) * mVecB1(1) - mVecC2(1) * mVecB1(2)) / aDetV1V2;

  mL21 = (mVecC2(2) * mVecA2(1) - mVecC2(1) * mVecA2(2)) / aDetV1V2;

  mL11 = (mVecC2(2) * mVecA1(1) - mVecC2(1) * mVecA1(2)) / aDetV1V2;

  mM1 = (mVecC2(2) * mVecD(1) - mVecC2(1) * mVecD(2)) / aDetV1V2;

  mK22 = (mVecC1(1) * mVecB2(2) - mVecC1(2) * mVecB2(1)) / aDetV1V2;

  mK12 = (mVecC1(1) * mVecB1(2) - mVecC1(2) * mVecB1(1)) / aDetV1V2;

  mL22 = (mVecC1(1) * mVecA2(2) - mVecC1(2) * mVecA2(1)) / aDetV1V2;

  mL12 = (mVecC1(1) * mVecA1(2) - mVecC1(2) * mVecA1(1)) / aDetV1V2;

  mM2 = (mVecC1(1) * mVecD(2) - mVecC1(2) * mVecD(1)) / aDetV1V2;

  ShortCosForm(mL11, mK11, mK1, mFIV1);
  ShortCosForm(mL21, mK21, mL1, mPSIV1);
  ShortCosForm(mL12, mK12, mK2, mFIV2);
  ShortCosForm(mL22, mK22, mL2, mPSIV2);

  const double aA1 = mVecC1(3) * mK21 + mVecC2(3) * mK22 - mVecB2(3),
               aA2 = mVecC1(3) * mL21 + mVecC2(3) * mL22 - mVecA2(3),
               aB1 = mVecB1(3) - mVecC1(3) * mK11 - mVecC2(3) * mK12,
               aB2 = mVecA1(3) - mVecC1(3) * mL11 - mVecC2(3) * mL12;

  mC = mVecD(3) - mVecC1(3) * mM1 - mVecC2(3) * mM2;

  double aA = 0.0;

  ShortCosForm(aB2, aB1, mB, mFI1);
  ShortCosForm(aA2, aA1, aA, mFI2);

  mB /= aA;
  mC /= aA;
}

class WorkWithBoundaries
{
public:
  enum SearchBoundType
  {
    SearchNONE = 0,
    SearchV1   = 1,
    SearchV2   = 2
  };

  struct StPInfo
  {
    StPInfo()
    {
      mySurfID = 0;
      myU1     = RealLast();
      myV1     = RealLast();
      myU2     = RealLast();
      myV2     = RealLast();
    }

    int mySurfID;

    double myU1;
    double myV1;
    double myU2;
    double myV2;

    bool operator>(const StPInfo& theOther) const { return myU1 > theOther.myU1; }

    bool operator<(const StPInfo& theOther) const { return myU1 < theOther.myU1; }

    bool operator==(const StPInfo& theOther) const { return myU1 == theOther.myU1; }
  };

  WorkWithBoundaries(const IntSurf_Quadric&                   theQuad1,
                     const IntSurf_Quadric&                   theQuad2,
                     const ComputationMethods::stCoeffsValue& theCoeffs,
                     const Bnd_Box2d&                         theUVSurf1,
                     const Bnd_Box2d&                         theUVSurf2,
                     const int                                theNbWLines,
                     const double                             thePeriod,
                     const double                             theTol3D,
                     const double                             theTol2D,
                     const bool                               isTheReverse)
      : myQuad1(theQuad1),
        myQuad2(theQuad2),
        myCoeffs(theCoeffs),
        myUVSurf1(theUVSurf1),
        myUVSurf2(theUVSurf2),
        myNbWLines(theNbWLines),
        myPeriod(thePeriod),
        myTol3D(theTol3D),
        myTol2D(theTol2D),
        myIsReverse(isTheReverse) {};

  const ComputationMethods::stCoeffsValue& SICoeffs() const { return myCoeffs; }

  const IntSurf_Quadric& GetQSurface(const int theIdx) const
  {
    if (theIdx <= 1)
      return myQuad1;

    return myQuad2;
  }

  bool IsReversed() const { return myIsReverse; }

  double Get2dTolerance() const { return myTol2D; }

  double Get3dTolerance() const { return myTol3D; }

  const Bnd_Box2d& UVS1() const { return myUVSurf1; }

  const Bnd_Box2d& UVS2() const { return myUVSurf2; }

  void AddBoundaryPoint(const occ::handle<IntPatch_WLine>& theWL,
                        const double                       theU1,
                        const double                       theU1Min,
                        const double                       theU2,
                        const double                       theV1,
                        const double                       theV1Prev,
                        const double                       theV2,
                        const double                       theV2Prev,
                        const int                          theWLIndex,
                        const bool                         theFlForce,
                        bool&                              isTheFound1,
                        bool&                              isTheFound2) const;

  static bool BoundariesComputing(const ComputationMethods::stCoeffsValue& theCoeffs,
                                  const double                             thePeriod,
                                  Bnd_Range                                theURange[]);

  void BoundaryEstimation(const gp_Cylinder& theCy1,
                          const gp_Cylinder& theCy2,
                          Bnd_Range&         theOutBoxS1,
                          Bnd_Range&         theOutBoxS2) const;

protected:
  bool SearchOnVBounds(const SearchBoundType theSBType,
                       const double          theVzad,
                       const double          theVInit,
                       const double          theInitU2,
                       const double          theInitMainVar,
                       double&               theMainVariableValue) const;

  const WorkWithBoundaries& operator=(const WorkWithBoundaries&);

private:
  friend class ComputationMethods;

  const IntSurf_Quadric&                   myQuad1;
  const IntSurf_Quadric&                   myQuad2;
  const ComputationMethods::stCoeffsValue& myCoeffs;
  const Bnd_Box2d&                         myUVSurf1;
  const Bnd_Box2d&                         myUVSurf2;
  const int                                myNbWLines;
  const double                             myPeriod;
  const double                             myTol3D;
  const double                             myTol2D;
  const bool                               myIsReverse;
};

static void SeekAdditionalPoints(const IntSurf_Quadric&                   theQuad1,
                                 const IntSurf_Quadric&                   theQuad2,
                                 const occ::handle<IntSurf_LineOn2S>&     theLine,
                                 const ComputationMethods::stCoeffsValue& theCoeffs,
                                 const int                                theWLIndex,
                                 const int                                theMinNbPoints,
                                 const int                                theStartPointOnLine,
                                 const int                                theEndPointOnLine,
                                 const double                             theTol2D,
                                 const double                             thePeriodOfSurf2,
                                 const bool                               isTheReverse);

static inline void MinMax(double& theParMIN, double& theParMAX)
{
  if (theParMIN > theParMAX)
  {
    const double aux = theParMAX;
    theParMAX        = theParMIN;
    theParMIN        = aux;
  }
}

static inline void ExtremaLineLine(const gp_Ax1& theC1,
                                   const gp_Ax1& theC2,
                                   const double  theCosA,
                                   const double  theSqSinA,
                                   double&       thePar1,
                                   double&       thePar2)
{
  const gp_Dir &aD1 = theC1.Direction(), &aD2 = theC2.Direction();

  const gp_XYZ aL1L2 = theC2.Location().XYZ() - theC1.Location().XYZ();
  const double aD1L = aD1.XYZ().Dot(aL1L2), aD2L = aD2.XYZ().Dot(aL1L2);

  thePar1 = (aD1L - theCosA * aD2L) / theSqSinA;
  thePar2 = (theCosA * aD1L - aD2L) / theSqSinA;
}

static void VBoundaryPrecise(const math_Matrix& theMatr,
                             const double       theV1AfterDecrByDelta,
                             const double       theV2AfterDecrByDelta,
                             double&            theV1Set,
                             double&            theV2Set)
{

  const int   aNbDim = 3;
  math_Matrix aSyst(1, aNbDim, 1, aNbDim);

  aSyst.SetCol(1, theMatr.Col(1));
  aSyst.SetCol(2, theMatr.Col(2));
  aSyst.SetCol(3, theMatr.Col(4));

  const double aDet = aSyst.Determinant();

  aSyst.SetCol(1, theMatr.Col(3));
  const double aDet1 = aSyst.Determinant();

  aSyst.SetCol(1, theMatr.Col(1));
  aSyst.SetCol(2, theMatr.Col(3));

  const double aDet2 = aSyst.Determinant();

  if (aDet * aDet1 > 0.0)
  {
    theV1Set = theV1AfterDecrByDelta;
  }

  if (aDet * aDet2 > 0.0)
  {
    theV2Set = theV2AfterDecrByDelta;
  }
}

static inline bool DeltaU1Computing(const math_Matrix& theSyst,
                                    const math_Vector& theFree,
                                    double&            theDeltaU1Found)
{
  double aDet = theSyst.Determinant();

  if (std::abs(aDet) > aNulValue)
  {
    math_Matrix aSyst1(theSyst);
    aSyst1.SetCol(2, theFree);

    theDeltaU1Found = std::abs(aSyst1.Determinant() / aDet);
    return true;
  }

  return false;
}

static bool StepComputing(const math_Matrix& theMatr,
                          const double       theV1Cur,
                          const double       theV2Cur,
                          const double       theDeltaV1,
                          const double       theDeltaV2,
                          double&            theDeltaU1Found)
{
#ifdef INTPATCH_IMPIMPINTERSECTION_DEBUG
  bool flShow = false;

  if (flShow)
  {
    printf("{%+10.20f*V1 + %+10.20f*V2 + %+10.20f*dU1 + %+10.20f*dU2 = %+10.20f\n",
           theMatr(1, 1),
           theMatr(1, 2),
           theMatr(1, 3),
           theMatr(1, 4),
           theMatr(1, 5));
    printf("{%+10.20f*V1 + %+10.20f*V2 + %+10.20f*dU1 + %+10.20f*dU2 = %+10.20f\n",
           theMatr(2, 1),
           theMatr(2, 2),
           theMatr(2, 3),
           theMatr(2, 4),
           theMatr(2, 5));
    printf("{%+10.20f*V1 + %+10.20f*V2 + %+10.20f*dU1 + %+10.20f*dU2 = %+10.20f\n",
           theMatr(3, 1),
           theMatr(3, 2),
           theMatr(3, 3),
           theMatr(3, 4),
           theMatr(3, 5));
  }
#endif

  bool isSuccess  = false;
  theDeltaU1Found = RealLast();

  const int aNbDim = 3;

  math_Matrix aSyst(1, aNbDim, 1, aNbDim);
  math_Vector aFree(1, aNbDim);

  double aV1Set = theV1Cur + theDeltaV1, aV2Set = theV2Cur + theDeltaV2;

  VBoundaryPrecise(theMatr, theV1Cur - theDeltaV1, theV2Cur - theDeltaV2, aV1Set, aV2Set);

  aSyst.SetCol(2, theMatr.Col(3));
  aSyst.SetCol(3, theMatr.Col(4));

  for (int i = 0; i < 2; i++)
  {
    if (i == 0)
    {
      aSyst.SetCol(1, theMatr.Col(2));
      aFree.Set(1, aNbDim, theMatr.Col(5) - aV1Set * theMatr.Col(1));
    }
    else
    {
      aSyst.SetCol(1, theMatr.Col(1));
      aFree.Set(1, aNbDim, theMatr.Col(5) - aV2Set * theMatr.Col(2));
    }

    double aNewDU = theDeltaU1Found;
    if (DeltaU1Computing(aSyst, aFree, aNewDU))
    {
      isSuccess = true;
      if (aNewDU < theDeltaU1Found)
      {
        theDeltaU1Found = aNewDU;
      }
    }
  }

  if (!isSuccess)
  {
    aFree = theMatr.Col(5) - aV1Set * theMatr.Col(1) - aV2Set * theMatr.Col(2);
    math_Matrix aSyst1(1, aNbDim, 1, 2);
    aSyst1.SetCol(1, aSyst.Col(2));
    aSyst1.SetCol(2, aSyst.Col(3));

    const double aDet1   = theMatr(1, 3) * theMatr(2, 4) - theMatr(2, 3) * theMatr(1, 4);
    const double aDet2   = theMatr(1, 3) * theMatr(3, 4) - theMatr(3, 3) * theMatr(1, 4);
    const double aDet3   = theMatr(2, 3) * theMatr(3, 4) - theMatr(3, 3) * theMatr(2, 4);
    const double anAbsD1 = std::abs(aDet1);
    const double anAbsD2 = std::abs(aDet2);
    const double anAbsD3 = std::abs(aDet3);

    if (anAbsD1 >= anAbsD2)
    {
      if (anAbsD1 >= anAbsD3)
      {

        if (anAbsD1 <= aNulValue)
          return isSuccess;

        theDeltaU1Found = std::abs(aFree(1) * theMatr(2, 4) - aFree(2) * theMatr(1, 4)) / anAbsD1;
        isSuccess       = true;
      }
      else
      {

        if (anAbsD3 <= aNulValue)
          return isSuccess;

        theDeltaU1Found = std::abs(aFree(2) * theMatr(3, 4) - aFree(3) * theMatr(2, 4)) / anAbsD3;
        isSuccess       = true;
      }
    }
    else
    {
      if (anAbsD2 >= anAbsD3)
      {

        if (anAbsD2 <= aNulValue)
          return isSuccess;

        theDeltaU1Found = std::abs(aFree(1) * theMatr(3, 4) - aFree(3) * theMatr(1, 4)) / anAbsD2;
        isSuccess       = true;
      }
      else
      {

        if (anAbsD3 <= aNulValue)
          return isSuccess;

        theDeltaU1Found = std::abs(aFree(2) * theMatr(3, 4) - aFree(3) * theMatr(2, 4)) / anAbsD3;
        isSuccess       = true;
      }
    }
  }

  return isSuccess;
}

void ProcessBounds(const occ::handle<IntPatch_ALine>&                      alig,
                   const NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
                   const IntSurf_Quadric&                                  Quad1,
                   const IntSurf_Quadric&                                  Quad2,
                   bool&                                                   procf,
                   const gp_Pnt&                                           ptf,
                   const double                                            first,
                   bool&                                                   procl,
                   const gp_Pnt&                                           ptl,
                   const double                                            last,
                   bool&                                                   Multpoint,
                   const double                                            Tol)
{
  int            j, k;
  double         U1, V1, U2, V2;
  IntPatch_Point ptsol;
  double         d;

  if (procf && procl)
  {
    j = slin.Length() + 1;
  }
  else
  {
    j = 1;
  }

  while (j <= slin.Length())
  {
    if (slin.Value(j)->ArcType() == IntPatch_Analytic)
    {
      const occ::handle<IntPatch_ALine>& aligold = *((occ::handle<IntPatch_ALine>*)&slin.Value(j));
      k                                          = 1;

      while (k <= aligold->NbVertex())
      {
        ptsol = aligold->Vertex(k);
        if (!procf)
        {
          d = ptf.Distance(ptsol.Value());
          if (d <= Tol)
          {
            ptsol.SetTolerance(Tol);
            if (!ptsol.IsMultiple())
            {

              Multpoint = true;
              ptsol.SetMultiple(true);
              aligold->Replace(k, ptsol);
            }
            ptsol.SetParameter(first);
            alig->AddVertex(ptsol);
            alig->SetFirstPoint(alig->NbVertex());
            procf = true;

            ptsol = aligold->Vertex(k);
          }
        }
        if (!procl)
        {
          if (ptl.Distance(ptsol.Value()) <= Tol)
          {
            ptsol.SetTolerance(Tol);
            if (!ptsol.IsMultiple())
            {
              Multpoint = true;
              ptsol.SetMultiple(true);
              aligold->Replace(k, ptsol);
            }
            ptsol.SetParameter(last);
            alig->AddVertex(ptsol);
            alig->SetLastPoint(alig->NbVertex());
            procl = true;

            ptsol = aligold->Vertex(k);
          }
        }
        if (procf && procl)
        {
          k = aligold->NbVertex() + 1;
        }
        else
        {
          k = k + 1;
        }
      }
      if (procf && procl)
      {
        j = slin.Length() + 1;
      }
      else
      {
        j = j + 1;
      }
    }
  }

  ptsol.SetTolerance(Tol);
  if (!procf && !procl)
  {
    Quad1.Parameters(ptf, U1, V1);
    Quad2.Parameters(ptf, U2, V2);
    ptsol.SetValue(ptf, Tol, false);
    ptsol.SetParameters(U1, V1, U2, V2);
    ptsol.SetParameter(first);
    if (ptf.Distance(ptl) <= Tol)
    {
      ptsol.SetMultiple(true);
      Multpoint = true;
      alig->AddVertex(ptsol);
      alig->SetFirstPoint(alig->NbVertex());

      ptsol.SetParameter(last);
      alig->AddVertex(ptsol);
      alig->SetLastPoint(alig->NbVertex());
    }
    else
    {
      alig->AddVertex(ptsol);
      alig->SetFirstPoint(alig->NbVertex());
      Quad1.Parameters(ptl, U1, V1);
      Quad2.Parameters(ptl, U2, V2);
      ptsol.SetValue(ptl, Tol, false);
      ptsol.SetParameters(U1, V1, U2, V2);
      ptsol.SetParameter(last);
      alig->AddVertex(ptsol);
      alig->SetLastPoint(alig->NbVertex());
    }
  }
  else if (!procf)
  {
    Quad1.Parameters(ptf, U1, V1);
    Quad2.Parameters(ptf, U2, V2);
    ptsol.SetValue(ptf, Tol, false);
    ptsol.SetParameters(U1, V1, U2, V2);
    ptsol.SetParameter(first);
    alig->AddVertex(ptsol);
    alig->SetFirstPoint(alig->NbVertex());
  }
  else if (!procl)
  {
    Quad1.Parameters(ptl, U1, V1);
    Quad2.Parameters(ptl, U2, V2);
    ptsol.SetValue(ptl, Tol, false);
    ptsol.SetParameters(U1, V1, U2, V2);
    ptsol.SetParameter(last);
    alig->AddVertex(ptsol);
    alig->SetLastPoint(alig->NbVertex());
  }
}

bool CyCyAnalyticalIntersect(const IntSurf_Quadric&                            Quad1,
                             const IntSurf_Quadric&                            Quad2,
                             const IntAna_QuadQuadGeo&                         theInter,
                             const double                                      Tol,
                             bool&                                             Empty,
                             bool&                                             Same,
                             bool&                                             Multpoint,
                             NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
                             NCollection_Sequence<IntPatch_Point>&             spnt)
{
  IntPatch_Point ptsol;

  int i;

  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;

  gp_Elips elipsol;
  gp_Lin   linsol;

  gp_Cylinder Cy1(Quad1.Cylinder());
  gp_Cylinder Cy2(Quad2.Cylinder());

  typint    = theInter.TypeInter();
  int NbSol = theInter.NbSolutions();
  Empty     = false;
  Same      = false;

  switch (typint)
  {
    case IntAna_Empty:
    {
      Empty = true;
    }
    break;

    case IntAna_Same:
    {
      Same = true;
    }
    break;

    case IntAna_Point:
    {
      gp_Pnt psol(theInter.Point(1));
      ptsol.SetValue(psol, Tol, true);

      double U1, V1, U2, V2;
      Quad1.Parameters(psol, U1, V1);
      Quad2.Parameters(psol, U2, V2);

      ptsol.SetParameters(U1, V1, U2, V2);
      spnt.Append(ptsol);
    }
    break;

    case IntAna_Line:
    {
      gp_Pnt ptref;
      if (NbSol == 1)
      {
        linsol = theInter.Line(1);
        ptref  = linsol.Location();

        gp_Dir crb1(gp_Vec(ptref, Cy1.Location()));
        gp_Dir crb2(gp_Vec(ptref, Cy2.Location()));

        gp_Vec            norm1(Quad1.Normale(ptref));
        gp_Vec            norm2(Quad2.Normale(ptref));
        IntSurf_Situation situcyl1;
        IntSurf_Situation situcyl2;

        if (crb1.Dot(crb2) < 0.)
        {

          if (norm1.Dot(crb1) > 0.)
          {
            situcyl2 = IntSurf_Inside;
          }
          else
          {
            situcyl2 = IntSurf_Outside;
          }

          if (norm2.Dot(crb2) > 0.)
          {
            situcyl1 = IntSurf_Inside;
          }
          else
          {
            situcyl1 = IntSurf_Outside;
          }
        }
        else
        {
          if (Cy1.Radius() < Cy2.Radius())
          {
            if (norm1.Dot(crb1) > 0.)
            {
              situcyl2 = IntSurf_Inside;
            }
            else
            {
              situcyl2 = IntSurf_Outside;
            }

            if (norm2.Dot(crb2) > 0.)
            {
              situcyl1 = IntSurf_Outside;
            }
            else
            {
              situcyl1 = IntSurf_Inside;
            }
          }
          else
          {
            if (norm1.Dot(crb1) > 0.)
            {
              situcyl2 = IntSurf_Outside;
            }
            else
            {
              situcyl2 = IntSurf_Inside;
            }

            if (norm2.Dot(crb2) > 0.)
            {
              situcyl1 = IntSurf_Inside;
            }
            else
            {
              situcyl1 = IntSurf_Outside;
            }
          }
        }

        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(linsol, true, situcyl1, situcyl2);
        slin.Append(glig);
      }
      else
      {
        for (i = 1; i <= NbSol; i++)
        {
          linsol     = theInter.Line(i);
          ptref      = linsol.Location();
          gp_Vec lsd = linsol.Direction();

          double qwe = lsd.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
          if (qwe > 0.00000001)
          {
            trans1 = IntSurf_Out;
            trans2 = IntSurf_In;
          }
          else if (qwe < -0.00000001)
          {
            trans1 = IntSurf_In;
            trans2 = IntSurf_Out;
          }
          else
          {
            trans1 = trans2 = IntSurf_Undecided;
          }

          occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(linsol, false, trans1, trans2);
          slin.Append(glig);
        }
      }
    }
    break;

    case IntAna_Ellipse:
    {
      gp_Vec         Tgt;
      gp_Pnt         ptref;
      IntPatch_Point pmult1, pmult2;

      elipsol = theInter.Ellipse(1);

      gp_Pnt pttang1(ElCLib::Value(0.5 * M_PI, elipsol));
      gp_Pnt pttang2(ElCLib::Value(1.5 * M_PI, elipsol));

      Multpoint = true;
      pmult1.SetValue(pttang1, Tol, true);
      pmult2.SetValue(pttang2, Tol, true);
      pmult1.SetMultiple(true);
      pmult2.SetMultiple(true);

      double oU1, oV1, oU2, oV2;
      Quad1.Parameters(pttang1, oU1, oV1);
      Quad2.Parameters(pttang1, oU2, oV2);

      pmult1.SetParameters(oU1, oV1, oU2, oV2);
      Quad1.Parameters(pttang2, oU1, oV1);
      Quad2.Parameters(pttang2, oU2, oV2);

      pmult2.SetParameters(oU1, oV1, oU2, oV2);

      ElCLib::D1(0., elipsol, ptref, Tgt);

      double qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
      if (qwe > 0.00000001)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else if (qwe < -0.00000001)
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      else
      {
        trans1 = trans2 = IntSurf_Undecided;
      }

      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(elipsol, false, trans2, trans1);

      {
        double         aU1, aV1, aU2, aV2;
        IntPatch_Point aIP;
        gp_Pnt         aP(ElCLib::Value(0., elipsol));

        aIP.SetValue(aP, Tol, false);
        aIP.SetMultiple(false);

        Quad1.Parameters(aP, aU1, aV1);
        Quad2.Parameters(aP, aU2, aV2);

        aIP.SetParameters(aU1, aV1, aU2, aV2);

        aIP.SetParameter(0.);
        glig->AddVertex(aIP);
        glig->SetFirstPoint(1);

        aIP.SetParameter(2. * M_PI);
        glig->AddVertex(aIP);
        glig->SetLastPoint(2);
      }

      pmult1.SetParameter(0.5 * M_PI);
      glig->AddVertex(pmult1);

      pmult2.SetParameter(1.5 * M_PI);
      glig->AddVertex(pmult2);

      slin.Append(glig);

      elipsol = theInter.Ellipse(2);

      double param1              = ElCLib::Parameter(elipsol, pttang1);
      double param2              = ElCLib::Parameter(elipsol, pttang2);
      double parampourtransition = 0.0;
      if (param1 < param2)
      {
        pmult1.SetParameter(0.5 * M_PI);
        pmult2.SetParameter(1.5 * M_PI);
        parampourtransition = M_PI;
      }
      else
      {
        pmult1.SetParameter(1.5 * M_PI);
        pmult2.SetParameter(0.5 * M_PI);
        parampourtransition = 0.0;
      }

      ElCLib::D1(parampourtransition, elipsol, ptref, Tgt);

      qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
      if (qwe > 0.00000001)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else if (qwe < -0.00000001)
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      else
      {
        trans1 = trans2 = IntSurf_Undecided;
      }

      glig = new IntPatch_GLine(elipsol, false, trans1, trans2);

      {
        double         aU1, aV1, aU2, aV2;
        IntPatch_Point aIP;
        gp_Pnt         aP(ElCLib::Value(0., elipsol));

        aIP.SetValue(aP, Tol, false);
        aIP.SetMultiple(false);

        Quad1.Parameters(aP, aU1, aV1);
        Quad2.Parameters(aP, aU2, aV2);

        aIP.SetParameters(aU1, aV1, aU2, aV2);

        aIP.SetParameter(0.);
        glig->AddVertex(aIP);
        glig->SetFirstPoint(1);

        aIP.SetParameter(2. * M_PI);
        glig->AddVertex(aIP);
        glig->SetLastPoint(2);
      }

      glig->AddVertex(pmult1);
      glig->AddVertex(pmult2);

      slin.Append(glig);
    }
    break;

    case IntAna_Parabola:
    case IntAna_Hyperbola:
      throw Standard_Failure("IntCyCy(): Wrong intersection type!");

    case IntAna_Circle:

    case IntAna_NoGeometricSolution:
    default:
      return false;
  }

  return true;
}

static void ShortCosForm(const double theCosFactor,
                         const double theSinFactor,
                         double&      theCoeff,
                         double&      theAngle)
{
  theCoeff = sqrt(theCosFactor * theCosFactor + theSinFactor * theSinFactor);
  theAngle = 0.0;
  if (IsEqual(theCoeff, 0.0))
  {
    theAngle = 0.0;
    return;
  }

  theAngle = acos(std::abs(theCosFactor / theCoeff));

  if (theSinFactor > 0.0)
  {
    if (IsEqual(theCosFactor, 0.0))
    {
      theAngle = M_PI / 2.0;
    }
    else if (theCosFactor < 0.0)
    {
      theAngle = M_PI - theAngle;
    }
  }
  else if (IsEqual(theSinFactor, 0.0))
  {
    if (theCosFactor < 0.0)
    {
      theAngle = M_PI;
    }
  }
  if (theSinFactor < 0.0)
  {
    if (theCosFactor > 0.0)
    {
      theAngle = 2.0 * M_PI - theAngle;
    }
    else if (IsEqual(theCosFactor, 0.0))
    {
      theAngle = 3.0 * M_PI / 2.0;
    }
    else if (theCosFactor < 0.0)
    {
      theAngle = M_PI + theAngle;
    }
  }
}

bool ComputationMethods::CylCylMonotonicity(const double         theU1par,
                                            const int            theWLIndex,
                                            const stCoeffsValue& theCoeffs,
                                            const double         thePeriod,
                                            bool&                theIsIncreasing)
{

  bool isPlus = false;

  switch (theWLIndex)
  {
    case 0:
      isPlus = true;
      break;
    case 1:
      isPlus = false;
      break;
    default:

      return false;
  }

  double aU1Temp = theU1par - theCoeffs.mFI1;
  InscribePoint(0, thePeriod, aU1Temp, 0.0, thePeriod, false);

  theIsIncreasing = true;

  if (((M_PI - aU1Temp) < RealSmall()) && (aU1Temp < thePeriod))
  {
    theIsIncreasing = false;
  }

  if (theCoeffs.mB < 0.0)
  {
    theIsIncreasing = !theIsIncreasing;
  }

  if (!isPlus)
  {
    theIsIncreasing = !theIsIncreasing;
  }

  return true;
}

bool ComputationMethods::CylCylComputeParameters(const double         theU1par,
                                                 const int            theWLIndex,
                                                 const stCoeffsValue& theCoeffs,
                                                 double&              theU2,
                                                 double* const        theDelta)
{

  const double aTol0 = std::min(10.0 * Epsilon(1.0) * theCoeffs.mB, aNulValue);
  const double aTol  = 1.0 - aTol0;

  if (theWLIndex < 0 || theWLIndex > 1)
    return false;

  const double aSign = theWLIndex ? -1.0 : 1.0;

  double anArg = cos(theU1par - theCoeffs.mFI1);
  anArg        = theCoeffs.mB * anArg + theCoeffs.mC;

  if (anArg >= aTol)
  {
    if (theDelta)
      *theDelta = 0.0;

    anArg = 1.0;
  }
  else if (anArg <= -aTol)
  {
    if (theDelta)
      *theDelta = 0.0;

    anArg = -1.0;
  }
  else if (theDelta)
  {

    const double aDelta = std::min(1.0 - anArg, 1.0 + anArg);
    Standard_DivideByZero_Raise_if((aDelta * aDelta < RealSmall()) || (aDelta >= 2.0),
                                   "IntPatch_ImpImpIntersection_4.gxx, CylCylComputeParameters()");
    *theDelta = aTol0 / sqrt(aDelta * (2.0 - aDelta));
  }

  theU2 = acos(anArg);
  theU2 = theCoeffs.mFI2 + aSign * theU2;

  return true;
}

bool ComputationMethods::CylCylComputeParameters(const double         theU1,
                                                 const double         theU2,
                                                 const stCoeffsValue& theCoeffs,
                                                 double&              theV1,
                                                 double&              theV2)
{
  theV1 = theCoeffs.mK21 * sin(theU2) + theCoeffs.mK11 * sin(theU1) + theCoeffs.mL21 * cos(theU2)
          + theCoeffs.mL11 * cos(theU1) + theCoeffs.mM1;

  theV2 = theCoeffs.mK22 * sin(theU2) + theCoeffs.mK12 * sin(theU1) + theCoeffs.mL22 * cos(theU2)
          + theCoeffs.mL12 * cos(theU1) + theCoeffs.mM2;

  return true;
}

bool ComputationMethods::CylCylComputeParameters(const double         theU1par,
                                                 const int            theWLIndex,
                                                 const stCoeffsValue& theCoeffs,
                                                 double&              theU2,
                                                 double&              theV1,
                                                 double&              theV2)
{
  if (!CylCylComputeParameters(theU1par, theWLIndex, theCoeffs, theU2))
    return false;

  if (!CylCylComputeParameters(theU1par, theU2, theCoeffs, theV1, theV2))
    return false;

  return true;
}

bool WorkWithBoundaries::SearchOnVBounds(const SearchBoundType theSBType,
                                         const double          theVzad,
                                         const double          theVInit,
                                         const double          theInitU2,
                                         const double          theInitMainVar,
                                         double&               theMainVariableValue) const
{
  const int    aNbDim    = 3;
  const double aMaxError = 4.0 * M_PI;

  theMainVariableValue      = theInitMainVar;
  const double aTol2        = 1.0e-18;
  double       aMainVarPrev = theInitMainVar, aU2Prev = theInitU2, anOtherVar = theVInit;

  math_Matrix aMatr(1, aNbDim, 1, aNbDim);

  double anError     = RealLast();
  double anErrorPrev = anError;
  int    aNbIter     = 0;
  do
  {
    if (++aNbIter > 1000)
      return false;

    const double aSinU1 = sin(aMainVarPrev), aCosU1 = cos(aMainVarPrev), aSinU2 = sin(aU2Prev),
                 aCosU2 = cos(aU2Prev);

    math_Vector aVecFreeMem = (myCoeffs.mVecA2 * aU2Prev + myCoeffs.mVecB2) * aSinU2
                              - (myCoeffs.mVecB2 * aU2Prev - myCoeffs.mVecA2) * aCosU2
                              + (myCoeffs.mVecA1 * aMainVarPrev + myCoeffs.mVecB1) * aSinU1
                              - (myCoeffs.mVecB1 * aMainVarPrev - myCoeffs.mVecA1) * aCosU1
                              + myCoeffs.mVecD;

    math_Vector aMSum(1, 3);

    switch (theSBType)
    {
      case SearchV1:
        aMatr.SetCol(3, myCoeffs.mVecC2);
        aMSum = myCoeffs.mVecC1 * theVzad;
        aVecFreeMem -= aMSum;
        aMSum += myCoeffs.mVecC2 * anOtherVar;
        break;

      case SearchV2:
        aMatr.SetCol(3, myCoeffs.mVecC1);
        aMSum = myCoeffs.mVecC2 * theVzad;
        aVecFreeMem -= aMSum;
        aMSum += myCoeffs.mVecC1 * anOtherVar;
        break;

      default:
        return false;
    }

    aMatr.SetCol(1, myCoeffs.mVecA1 * aSinU1 - myCoeffs.mVecB1 * aCosU1);
    aMatr.SetCol(2, myCoeffs.mVecA2 * aSinU2 - myCoeffs.mVecB2 * aCosU2);

    double aDetMainSyst = aMatr.Determinant();

    if (std::abs(aDetMainSyst) < aNulValue)
    {
      return false;
    }

    math_Matrix aM1(aMatr), aM2(aMatr), aM3(aMatr);
    aM1.SetCol(1, aVecFreeMem);
    aM2.SetCol(2, aVecFreeMem);
    aM3.SetCol(3, aVecFreeMem);

    const double aDetMainVar = aM1.Determinant();
    const double aDetVar1    = aM2.Determinant();
    const double aDetVar2    = aM3.Determinant();

    double aDelta = aDetMainVar / aDetMainSyst - aMainVarPrev;

    if (std::abs(aDelta) > aMaxError)
      return false;

    anError = aDelta * aDelta;
    aMainVarPrev += aDelta;

    aDelta = aDetVar1 / aDetMainSyst - aU2Prev;

    if (std::abs(aDelta) > aMaxError)
      return false;

    anError += aDelta * aDelta;
    aU2Prev += aDelta;

    aDelta = aDetVar2 / aDetMainSyst - anOtherVar;
    anError += aDelta * aDelta;
    anOtherVar += aDelta;

    if (anError > anErrorPrev)
    {
      const double aSinU1Last = sin(aMainVarPrev), aCosU1Last = cos(aMainVarPrev),
                   aSinU2Last = sin(aU2Prev), aCosU2Last = cos(aU2Prev);
      aMSum -= (myCoeffs.mVecA1 * aCosU1Last + myCoeffs.mVecB1 * aSinU1Last
                + myCoeffs.mVecA2 * aCosU2Last + myCoeffs.mVecB2 * aSinU2Last + myCoeffs.mVecD);
      const double aSQNorm = aMSum.Norm2();
      return (aSQNorm < aTol2);
    }
    else
    {
      theMainVariableValue = aMainVarPrev;
    }

    anErrorPrev = anError;
  } while (anError > aTol2);

  theMainVariableValue = aMainVarPrev;

  return true;
}

bool InscribePoint(const double theUfTarget,
                   const double theUlTarget,
                   double&      theUGiven,
                   const double theTol2D,
                   const double thePeriod,
                   const bool   theFlForce)
{
  if (Precision::IsInfinite(theUGiven))
  {
    return false;
  }

  if ((theUfTarget - theUGiven <= theTol2D) && (theUGiven - theUlTarget <= theTol2D))
  {

    if (theFlForce)
    {
      double anUtemp = theUGiven + thePeriod;
      if ((theUfTarget - anUtemp <= theTol2D) && (anUtemp - theUlTarget <= theTol2D))
      {
        theUGiven = anUtemp;
        return true;
      }

      anUtemp = theUGiven - thePeriod;
      if ((theUfTarget - anUtemp <= theTol2D) && (anUtemp - theUlTarget <= theTol2D))
      {
        theUGiven = anUtemp;
      }
    }

    return true;
  }

  const double aUf = theUfTarget - theTol2D;
  const double aUl = aUf + thePeriod;

  theUGiven = ElCLib::InPeriod(theUGiven, aUf, aUl);

  return ((theUfTarget - theUGiven <= theTol2D) && (theUGiven - theUlTarget <= theTol2D));
}

static bool InscribeInterval(const double theUfTarget,
                             const double theUlTarget,
                             Bnd_Range&   theRange,
                             const double theTol2D,
                             const double thePeriod)
{
  double anUpar = 0.0;
  if (!theRange.GetMin(anUpar))
  {
    return false;
  }

  const double aDelta = theRange.Delta();
  if (InscribePoint(theUfTarget,
                    theUlTarget,
                    anUpar,
                    theTol2D,
                    thePeriod,
                    (std::abs(theUlTarget - anUpar) < theTol2D)))
  {
    theRange.SetVoid();
    theRange.Add(anUpar);
    theRange.Add(anUpar + aDelta);
  }
  else
  {
    if (!theRange.GetMax(anUpar))
    {
      return false;
    }

    if (InscribePoint(theUfTarget,
                      theUlTarget,
                      anUpar,
                      theTol2D,
                      thePeriod,
                      (std::abs(theUfTarget - anUpar) < theTol2D)))
    {
      theRange.SetVoid();
      theRange.Add(anUpar);
      theRange.Add(anUpar - aDelta);
    }
    else
    {
      return false;
    }
  }

  return true;
}

static bool ExcludeNearElements(double       theArr[],
                                const int    theNOfMembers,
                                const double theUSurf1f,
                                const double theUSurf1l,
                                const double theTol)
{
  bool aRetVal = false;
  for (int i = 1; i < theNOfMembers; i++)
  {
    double &anA = theArr[i], &anB = theArr[i - 1];

    if (Precision::IsInfinite(anA))
      break;

    if ((anA - anB) < theTol)
    {
      if ((anB != 0.0) && (anB != theUSurf1f) && (anB != theUSurf1l))
        anA = (anA + anB) / 2.0;
      else
        anA = anB;

      anB     = Precision::Infinite();
      aRetVal = true;
    }
  }

  return aRetVal;
}

static bool AddPointIntoWL(const IntSurf_Quadric&                   theQuad1,
                           const IntSurf_Quadric&                   theQuad2,
                           const ComputationMethods::stCoeffsValue& theCoeffs,
                           const bool                               isTheReverse,
                           const bool                               isThePrecise,
                           const gp_Pnt2d&                          thePntOnSurf1,
                           const gp_Pnt2d&                          thePntOnSurf2,
                           const double                             theUfSurf1,
                           const double                             theUlSurf1,
                           const double                             theUfSurf2,
                           const double                             theUlSurf2,
                           const double                             theVfSurf1,
                           const double                             theVlSurf1,
                           const double                             theVfSurf2,
                           const double                             theVlSurf2,
                           const double                             thePeriodOfSurf1,
                           const occ::handle<IntSurf_LineOn2S>&     theLine,
                           const int                                theWLIndex,
                           const double                             theTol3D,
                           const double                             theTol2D,
                           const bool                               theFlBefore  = false,
                           const bool                               theOnlyCheck = false)
{

  gp_Pnt aPt1(theQuad1.Value(thePntOnSurf1.X(), thePntOnSurf1.Y())),
    aPt2(theQuad2.Value(thePntOnSurf2.X(), thePntOnSurf2.Y()));

  double aU1par = thePntOnSurf1.X();

  if (!InscribePoint(theUfSurf1,
                     theUlSurf1,
                     aU1par,
                     theTol2D,
                     thePeriodOfSurf1,
                     aU1par > 0.5 * (theUfSurf1 + theUlSurf1)))
    return false;

  if ((theLine->NbPoints() > 0) && ((theUlSurf1 - theUfSurf1) >= (thePeriodOfSurf1 - theTol2D))
      && (((aU1par + thePeriodOfSurf1 - theUlSurf1) <= theTol2D)
          || ((aU1par - thePeriodOfSurf1 - theUfSurf1) >= theTol2D)))
  {

    double aU1 = 0.0, aV1 = 0.0;
    if (isTheReverse)
    {
      theLine->Value(theLine->NbPoints()).ParametersOnS2(aU1, aV1);
    }
    else
    {
      theLine->Value(theLine->NbPoints()).ParametersOnS1(aU1, aV1);
    }

    const double aDelta = aU1 - aU1par;
    if (2.0 * std::abs(aDelta) > thePeriodOfSurf1)
    {
      aU1par += std::copysign(thePeriodOfSurf1, aDelta);
    }
  }

  double aU2par = thePntOnSurf2.X();
  if (!InscribePoint(theUfSurf2, theUlSurf2, aU2par, theTol2D, thePeriodOfSurf1, false))
    return false;

  double aV1par = thePntOnSurf1.Y();
  if ((aV1par - theVlSurf1 > theTol2D) || (theVfSurf1 - aV1par > theTol2D))
    return false;

  double aV2par = thePntOnSurf2.Y();
  if ((aV2par - theVlSurf2 > theTol2D) || (theVfSurf2 - aV2par > theTol2D))
    return false;

  IntSurf_PntOn2S aPnt;

  if (isTheReverse)
  {
    aPnt.SetValue((aPt1.XYZ() + aPt2.XYZ()) / 2.0, aU2par, aV2par, aU1par, aV1par);
  }
  else
  {
    aPnt.SetValue((aPt1.XYZ() + aPt2.XYZ()) / 2.0, aU1par, aV1par, aU2par, aV2par);
  }

  int aNbPnts = theLine->NbPoints();
  if (aNbPnts > 0)
  {
    double                aUl = 0.0, aVl = 0.0;
    const IntSurf_PntOn2S aPlast = theLine->Value(aNbPnts);
    if (isTheReverse)
      aPlast.ParametersOnS2(aUl, aVl);
    else
      aPlast.ParametersOnS1(aUl, aVl);

    if (!theFlBefore && (aU1par <= aUl))
    {

      aU1par += thePeriodOfSurf1;

      if ((theUfSurf1 - aU1par > theTol2D) || (aU1par - theUlSurf1 > theTol2D))
      {

        return false;
      }
    }

    if (theOnlyCheck)
      return true;

    const double aDTol = 1.0 - Epsilon(1.0);
    if (aPnt.IsSame(aPlast, theTol3D * aDTol, theTol2D * aDTol))
    {
      theLine->RemovePoint(aNbPnts);
    }
  }

  if (theOnlyCheck)
    return true;

  theLine->Add(aPnt);

  if (!isThePrecise)
    return true;

  aNbPnts = theLine->NbPoints();
  if (aNbPnts >= 3)
  {
    double aU1 = 0.0, aU2 = 0.0, aU3 = 0.0, aV = 0.0;
    if (isTheReverse)
    {
      theLine->Value(aNbPnts).ParametersOnS2(aU3, aV);
      theLine->Value(aNbPnts - 1).ParametersOnS2(aU2, aV);
      theLine->Value(aNbPnts - 2).ParametersOnS2(aU1, aV);
    }
    else
    {
      theLine->Value(aNbPnts).ParametersOnS1(aU3, aV);
      theLine->Value(aNbPnts - 1).ParametersOnS1(aU2, aV);
      theLine->Value(aNbPnts - 2).ParametersOnS1(aU1, aV);
    }

    const double aStepPrev = aU2 - aU1;
    const double aStep     = aU3 - aU2;

    const int aDeltaStep = RealToInt(aStepPrev / aStep);

    if ((1 < aDeltaStep) && (aDeltaStep < 2000))
    {

      SeekAdditionalPoints(theQuad1,
                           theQuad2,
                           theLine,
                           theCoeffs,
                           theWLIndex,
                           aDeltaStep,
                           aNbPnts - 2,
                           aNbPnts - 1,
                           theTol2D,
                           thePeriodOfSurf1,
                           isTheReverse);
    }
  }

  return true;
}

void WorkWithBoundaries::AddBoundaryPoint(const occ::handle<IntPatch_WLine>& theWL,
                                          const double                       theU1,
                                          const double                       theU1Min,
                                          const double                       theU2,
                                          const double                       theV1,
                                          const double                       theV1Prev,
                                          const double                       theV2,
                                          const double                       theV2Prev,
                                          const int                          theWLIndex,
                                          const bool                         theFlForce,
                                          bool&                              isTheFound1,
                                          bool&                              isTheFound2) const
{
  double aUSurf1f = 0.0, aUSurf1l = 0.0, aVSurf1f = 0.0, aVSurf1l = 0.0;
  double aUSurf2f = 0.0, aUSurf2l = 0.0, aVSurf2f = 0.0, aVSurf2l = 0.0;

  myUVSurf1.Get(aUSurf1f, aVSurf1f, aUSurf1l, aVSurf1l);
  myUVSurf2.Get(aUSurf2f, aVSurf2f, aUSurf2l, aVSurf2l);

  const int    aSize            = 4;
  const double anArrVzad[aSize] = {aVSurf1f, aVSurf1l, aVSurf2f, aVSurf2l};

  StPInfo aUVPoint[aSize];

  for (int anIDSurf = 0; anIDSurf < 4; anIDSurf += 2)
  {
    const double aVf = (anIDSurf == 0) ? theV1 : theV2,
                 aVl = (anIDSurf == 0) ? theV1Prev : theV2Prev;

    const SearchBoundType aTS = (anIDSurf == 0) ? SearchV1 : SearchV2;

    for (int anIDBound = 0; anIDBound < 2; anIDBound++)
    {
      const int anIndex = anIDSurf + anIDBound;

      aUVPoint[anIndex].mySurfID = anIDSurf;

      if ((std::abs(aVf - anArrVzad[anIndex]) > myTol2D)
          && ((aVf - anArrVzad[anIndex]) * (aVl - anArrVzad[anIndex]) > 0.0))
      {
        continue;
      }

      const bool aRes = SearchOnVBounds(aTS,
                                        anArrVzad[anIndex],
                                        (anIDSurf == 0) ? theV2 : theV1,
                                        theU2,
                                        theU1,
                                        aUVPoint[anIndex].myU1);

      if (!aRes || (aUVPoint[anIndex].myU1 >= theU1) || (aUVPoint[anIndex].myU1 < theU1Min))
      {

        aUVPoint[anIndex].myU1 = RealLast();
        continue;
      }
      else
      {

        double &aU1 = aUVPoint[anIndex].myU1, &aU2 = aUVPoint[anIndex].myU2,
               &aV1 = aUVPoint[anIndex].myV1, &aV2 = aUVPoint[anIndex].myV2;
        aU2 = theU2;
        aV1 = theV1;
        aV2 = theV2;

        if (!ComputationMethods::CylCylComputeParameters(aU1, theWLIndex, myCoeffs, aU2, aV1, aV2))
        {

          aU1 = RealLast();
          continue;
        }

        if (aTS == SearchV1)
          aV1 = anArrVzad[anIndex];
        else
          aV2 = anArrVzad[anIndex];
      }
    }
  }

  std::sort(aUVPoint, aUVPoint + aSize);

  isTheFound1 = isTheFound2 = false;

  for (int i = 0; i < aSize; i++)
  {
    if (aUVPoint[i].myU1 == RealLast())
      break;

    if (!AddPointIntoWL(myQuad1,
                        myQuad2,
                        myCoeffs,
                        myIsReverse,
                        false,
                        gp_Pnt2d(aUVPoint[i].myU1, aUVPoint[i].myV1),
                        gp_Pnt2d(aUVPoint[i].myU2, aUVPoint[i].myV2),
                        aUSurf1f,
                        aUSurf1l,
                        aUSurf2f,
                        aUSurf2l,
                        aVSurf1f,
                        aVSurf1l,
                        aVSurf2f,
                        aVSurf2l,
                        myPeriod,
                        theWL->Curve(),
                        theWLIndex,
                        myTol3D,
                        myTol2D,
                        theFlForce))
    {
      continue;
    }

    if (aUVPoint[i].mySurfID == 0)
    {
      isTheFound1 = true;
    }
    else
    {
      isTheFound2 = true;
    }
  }
}

static void SeekAdditionalPoints(const IntSurf_Quadric&                   theQuad1,
                                 const IntSurf_Quadric&                   theQuad2,
                                 const occ::handle<IntSurf_LineOn2S>&     theLine,
                                 const ComputationMethods::stCoeffsValue& theCoeffs,
                                 const int                                theWLIndex,
                                 const int                                theMinNbPoints,
                                 const int                                theStartPointOnLine,
                                 const int                                theEndPointOnLine,
                                 const double                             theTol2D,
                                 const double                             thePeriodOfSurf2,
                                 const bool                               isTheReverse)
{
  if (theLine.IsNull())
    return;

  int aNbPoints = theEndPointOnLine - theStartPointOnLine + 1;

  double aMinDeltaParam = theTol2D;

  {
    double u1 = 0.0, v1 = 0.0, u2 = 0.0, v2 = 0.0;

    if (isTheReverse)
    {
      theLine->Value(theStartPointOnLine).ParametersOnS2(u1, v1);
      theLine->Value(theEndPointOnLine).ParametersOnS2(u2, v2);
    }
    else
    {
      theLine->Value(theStartPointOnLine).ParametersOnS1(u1, v1);
      theLine->Value(theEndPointOnLine).ParametersOnS1(u2, v2);
    }

    aMinDeltaParam = std::max(std::abs(u2 - u1) / IntToReal(theMinNbPoints), aMinDeltaParam);
  }

  int    aLastPointIndex = theEndPointOnLine;
  double U1prec = 0.0, V1prec = 0.0, U2prec = 0.0, V2prec = 0.0;

  int aNbPointsPrev = 0;
  do
  {
    aNbPointsPrev = aNbPoints;
    for (int fp = theStartPointOnLine, lp = 0; fp < aLastPointIndex; fp = lp + 1)
    {
      double U1f = 0.0, V1f = 0.0;
      double U1l = 0.0, V1l = 0.0;

      double U2f = 0.0, V2f = 0.0;
      double U2l = 0.0, V2l = 0.0;

      lp = fp + 1;

      if (isTheReverse)
      {
        theLine->Value(fp).ParametersOnS2(U1f, V1f);
        theLine->Value(lp).ParametersOnS2(U1l, V1l);

        theLine->Value(fp).ParametersOnS1(U2f, V2f);
        theLine->Value(lp).ParametersOnS1(U2l, V2l);
      }
      else
      {
        theLine->Value(fp).ParametersOnS1(U1f, V1f);
        theLine->Value(lp).ParametersOnS1(U1l, V1l);

        theLine->Value(fp).ParametersOnS2(U2f, V2f);
        theLine->Value(lp).ParametersOnS2(U2l, V2l);
      }

      if (std::abs(U1l - U1f) <= aMinDeltaParam)
      {

        continue;
      }

      U1prec = 0.5 * (U1f + U1l);

      if (!ComputationMethods::CylCylComputeParameters(U1prec,
                                                       theWLIndex,
                                                       theCoeffs,
                                                       U2prec,
                                                       V1prec,
                                                       V2prec))
      {
        continue;
      }

      MinMax(U2f, U2l);
      if (!InscribePoint(U2f, U2l, U2prec, theTol2D, thePeriodOfSurf2, false))
      {
        continue;
      }

      const gp_Pnt aP1(theQuad1.Value(U1prec, V1prec)), aP2(theQuad2.Value(U2prec, V2prec));
      const gp_Pnt aPInt(0.5 * (aP1.XYZ() + aP2.XYZ()));

#ifdef INTPATCH_IMPIMPINTERSECTION_DEBUG
      std::cout << "|P1Pi| = " << aP1.SquareDistance(aPInt)
                << "; |P2Pi| = " << aP2.SquareDistance(aPInt) << std::endl;
#endif

      IntSurf_PntOn2S anIP;
      if (isTheReverse)
      {
        anIP.SetValue(aPInt, U2prec, V2prec, U1prec, V1prec);
      }
      else
      {
        anIP.SetValue(aPInt, U1prec, V1prec, U2prec, V2prec);
      }

      theLine->InsertBefore(lp, anIP);

      aNbPoints++;
      aLastPointIndex++;
    }

    if (aNbPoints >= theMinNbPoints)
    {
      return;
    }
  } while (aNbPoints < theMinNbPoints && (aNbPoints != aNbPointsPrev));
}

bool WorkWithBoundaries::BoundariesComputing(const ComputationMethods::stCoeffsValue& theCoeffs,
                                             const double                             thePeriod,
                                             Bnd_Range                                theURange[])
{

  if (theCoeffs.mB > 0.0)
  {

    if (theCoeffs.mB + std::abs(theCoeffs.mC) < -1.0)
    {

      return false;
    }
    else if (theCoeffs.mB + std::abs(theCoeffs.mC) <= 1.0)
    {

      theURange[0].Add(theCoeffs.mFI1);
      theURange[0].Add(thePeriod + theCoeffs.mFI1);
    }
    else if ((1 + theCoeffs.mC <= theCoeffs.mB) && (theCoeffs.mB <= 1 - theCoeffs.mC))
    {

      double anArg = -(theCoeffs.mC + 1) / theCoeffs.mB;
      if (anArg > 1.0)
        anArg = 1.0;
      if (anArg < -1.0)
        anArg = -1.0;

      const double aDAngle = acos(anArg);
      theURange[0].Add(theCoeffs.mFI1);
      theURange[0].Add(aDAngle + theCoeffs.mFI1);
      theURange[1].Add(thePeriod - aDAngle + theCoeffs.mFI1);
      theURange[1].Add(thePeriod + theCoeffs.mFI1);
    }
    else if ((1 - theCoeffs.mC <= theCoeffs.mB) && (theCoeffs.mB <= 1 + theCoeffs.mC))
    {

      double anArg = (1 - theCoeffs.mC) / theCoeffs.mB;
      if (anArg > 1.0)
        anArg = 1.0;
      if (anArg < -1.0)
        anArg = -1.0;

      const double aDAngle = acos(anArg);
      theURange[0].Add(aDAngle + theCoeffs.mFI1);
      theURange[0].Add(thePeriod - aDAngle + theCoeffs.mFI1);
    }
    else if (theCoeffs.mB - std::abs(theCoeffs.mC) >= 1.0)
    {

      double anArg1 = (1 - theCoeffs.mC) / theCoeffs.mB,
             anArg2 = -(theCoeffs.mC + 1) / theCoeffs.mB;
      if (anArg1 > 1.0)
        anArg1 = 1.0;
      if (anArg1 < -1.0)
        anArg1 = -1.0;

      if (anArg2 > 1.0)
        anArg2 = 1.0;
      if (anArg2 < -1.0)
        anArg2 = -1.0;

      const double aDAngle1 = acos(anArg1), aDAngle2 = acos(anArg2);

      theURange[0].Add(aDAngle1 + theCoeffs.mFI1);
      theURange[0].Add(aDAngle2 + theCoeffs.mFI1);
      theURange[1].Add(thePeriod - aDAngle2 + theCoeffs.mFI1);
      theURange[1].Add(thePeriod - aDAngle1 + theCoeffs.mFI1);
    }
    else
    {
      return false;
    }
  }
  else if (theCoeffs.mB < 0.0)
  {

    if (theCoeffs.mB + std::abs(theCoeffs.mC) > 1.0)
    {

      return false;
    }
    else if (-theCoeffs.mB + std::abs(theCoeffs.mC) <= 1.0)
    {

      theURange[0].Add(theCoeffs.mFI1);
      theURange[0].Add(thePeriod + theCoeffs.mFI1);
    }
    else if ((-theCoeffs.mC - 1 <= theCoeffs.mB) && (theCoeffs.mB <= theCoeffs.mC - 1))
    {

      double anArg = (1 - theCoeffs.mC) / theCoeffs.mB;
      if (anArg > 1.0)
        anArg = 1.0;
      if (anArg < -1.0)
        anArg = -1.0;

      const double aDAngle = acos(anArg);
      theURange[0].Add(theCoeffs.mFI1);
      theURange[0].Add(aDAngle + theCoeffs.mFI1);
      theURange[1].Add(thePeriod - aDAngle + theCoeffs.mFI1);
      theURange[1].Add(thePeriod + theCoeffs.mFI1);
    }
    else if ((theCoeffs.mC - 1 <= theCoeffs.mB) && (theCoeffs.mB <= -theCoeffs.mB - 1))
    {

      double anArg = -(theCoeffs.mC + 1) / theCoeffs.mB;
      if (anArg > 1.0)
        anArg = 1.0;
      if (anArg < -1.0)
        anArg = -1.0;

      const double aDAngle = acos(anArg);
      theURange[0].Add(aDAngle + theCoeffs.mFI1);
      theURange[0].Add(thePeriod - aDAngle + theCoeffs.mFI1);
    }
    else if (-theCoeffs.mB - std::abs(theCoeffs.mC) >= 1.0)
    {

      double anArg1 = -(theCoeffs.mC + 1) / theCoeffs.mB,
             anArg2 = (1 - theCoeffs.mC) / theCoeffs.mB;
      if (anArg1 > 1.0)
        anArg1 = 1.0;
      if (anArg1 < -1.0)
        anArg1 = -1.0;

      if (anArg2 > 1.0)
        anArg2 = 1.0;
      if (anArg2 < -1.0)
        anArg2 = -1.0;

      const double aDAngle1 = acos(anArg1), aDAngle2 = acos(anArg2);
      theURange[0].Add(aDAngle1 + theCoeffs.mFI1);
      theURange[0].Add(aDAngle2 + theCoeffs.mFI1);
      theURange[1].Add(thePeriod - aDAngle2 + theCoeffs.mFI1);
      theURange[1].Add(thePeriod - aDAngle1 + theCoeffs.mFI1);
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }

  return true;
}

static void CriticalPointsComputing(const ComputationMethods::stCoeffsValue& theCoeffs,
                                    const double                             theUSurf1f,
                                    const double                             theUSurf1l,
                                    const double                             theUSurf2f,
                                    const double                             theUSurf2l,
                                    const double                             thePeriod,
                                    const double                             theTol2D,
                                    int&                                     theNbCritPointsMax,
                                    double                                   theU1crit[])
{

  theU1crit[0] = 0.0;
  theU1crit[1] = thePeriod;
  theU1crit[2] = theUSurf1f;
  theU1crit[3] = theUSurf1l;

  const double aCOS = cos(theCoeffs.mFI2);
  const double aBSB = std::abs(theCoeffs.mB);
  if ((theCoeffs.mC - aBSB <= aCOS) && (aCOS <= theCoeffs.mC + aBSB))
  {
    double anArg = (aCOS - theCoeffs.mC) / theCoeffs.mB;
    if (anArg > 1.0)
      anArg = 1.0;
    if (anArg < -1.0)
      anArg = -1.0;

    theU1crit[4] = -acos(anArg) + theCoeffs.mFI1;
    theU1crit[5] = acos(anArg) + theCoeffs.mFI1;
  }

  double aSf = cos(theUSurf2f - theCoeffs.mFI2);
  double aSl = cos(theUSurf2l - theCoeffs.mFI2);
  MinMax(aSf, aSl);

  theU1crit[6] = std::abs((aSl - theCoeffs.mC) / theCoeffs.mB) < 1.0
                   ? -acos((aSl - theCoeffs.mC) / theCoeffs.mB) + theCoeffs.mFI1
                   : Precision::Infinite();
  theU1crit[7] = std::abs((aSf - theCoeffs.mC) / theCoeffs.mB) < 1.0
                   ? -acos((aSf - theCoeffs.mC) / theCoeffs.mB) + theCoeffs.mFI1
                   : Precision::Infinite();
  theU1crit[8] = std::abs((aSf - theCoeffs.mC) / theCoeffs.mB) < 1.0
                   ? acos((aSf - theCoeffs.mC) / theCoeffs.mB) + theCoeffs.mFI1
                   : Precision::Infinite();
  theU1crit[9] = std::abs((aSl - theCoeffs.mC) / theCoeffs.mB) < 1.0
                   ? acos((aSl - theCoeffs.mC) / theCoeffs.mB) + theCoeffs.mFI1
                   : Precision::Infinite();

  theU1crit[10] = theCoeffs.mFI1;
  theU1crit[11] = M_PI + theCoeffs.mFI1;

  for (int i = 0; i < theNbCritPointsMax; i++)
  {
    if (Precision::IsInfinite(theU1crit[i]))
    {
      continue;
    }

    theU1crit[i] = fmod(theU1crit[i], thePeriod);
    if (theU1crit[i] < 0.0)
      theU1crit[i] += thePeriod;
  }

  do
  {
    std::sort(theU1crit, theU1crit + theNbCritPointsMax);
  } while (ExcludeNearElements(theU1crit, theNbCritPointsMax, theUSurf1f, theUSurf1l, theTol2D));

  while (theNbCritPointsMax > 0)
  {
    double& anB = theU1crit[theNbCritPointsMax - 1];
    if (Precision::IsInfinite(anB))
    {
      theNbCritPointsMax--;
      continue;
    }

    if (theNbCritPointsMax == 1)
      break;

    double& anA = theU1crit[0];

    if (std::abs(anB - anA - thePeriod) < theTol2D)
    {
      anA = (anA + anB - thePeriod) / 2.0;
      anB = Precision::Infinite();
      theNbCritPointsMax--;
    }

    break;
  }
}

void WorkWithBoundaries::BoundaryEstimation(const gp_Cylinder& theCy1,
                                            const gp_Cylinder& theCy2,
                                            Bnd_Range&         theOutBoxS1,
                                            Bnd_Range&         theOutBoxS2) const
{
  const gp_Dir &aD1 = theCy1.Axis().Direction(), &aD2 = theCy2.Axis().Direction();
  const double  aR1 = theCy1.Radius(), aR2 = theCy2.Radius();

  const double aCosA   = aD1.Dot(aD2);
  const double aSqSinA = aD1.XYZ().CrossSquareMagnitude(aD2.XYZ());

  if (aSqSinA < Precision::Angular() * Precision::Angular())
    return;

  const double aSinA     = sqrt(aSqSinA);
  const double anAbsCosA = std::abs(aCosA);
  const double aHDV1 = (aR1 * anAbsCosA + aR2) / aSinA, aHDV2 = (aR2 * anAbsCosA + aR1) / aSinA;

#ifdef INTPATCH_IMPIMPINTERSECTION_DEBUG

  std::cout << "Reference values: aHDV1 = " << aHDV1 << "; aHDV2 = " << aHDV2 << std::endl;
#endif

  double aV01 = 0.0, aV02 = 0.0;
  ExtremaLineLine(theCy1.Axis(), theCy2.Axis(), aCosA, aSqSinA, aV01, aV02);

  theOutBoxS1.Add(aV01 - aHDV1);
  theOutBoxS1.Add(aV01 + aHDV1);

  theOutBoxS2.Add(aV02 - aHDV2);
  theOutBoxS2.Add(aV02 + aHDV2);

  theOutBoxS1.Enlarge(Precision::Confusion());
  theOutBoxS2.Enlarge(Precision::Confusion());

  double aU1 = 0.0, aV1 = 0.0, aU2 = 0.0, aV2 = 0.0;
  myUVSurf1.Get(aU1, aV1, aU2, aV2);
  theOutBoxS1.Common(Bnd_Range(aV1, aV2));

  myUVSurf2.Get(aU1, aV1, aU2, aV2);
  theOutBoxS2.Common(Bnd_Range(aV1, aV2));
}

static IntPatch_ImpImpIntersection::IntStatus CyCyNoGeometric(
  const gp_Cylinder&                                theCyl1,
  const gp_Cylinder&                                theCyl2,
  const WorkWithBoundaries&                         theBW,
  Bnd_Range                                         theRange[],
  const int                                         theNbOfRanges,
  bool&                                             isTheEmpty,
  NCollection_Sequence<occ::handle<IntPatch_Line>>& theSlin,
  NCollection_Sequence<IntPatch_Point>&             theSPnt)
{
  double aUSurf1f = 0.0, aUSurf1l = 0.0, aUSurf2f = 0.0, aUSurf2l = 0.0, aVSurf1f = 0.0,
         aVSurf1l = 0.0, aVSurf2f = 0.0, aVSurf2l = 0.0;

  theBW.UVS1().Get(aUSurf1f, aVSurf1f, aUSurf1l, aVSurf1l);
  theBW.UVS2().Get(aUSurf2f, aVSurf2f, aUSurf2l, aVSurf2l);

  Bnd_Range aRangeS1, aRangeS2;
  theBW.BoundaryEstimation(theCyl1, theCyl2, aRangeS1, aRangeS2);
  if (aRangeS1.IsVoid() || aRangeS2.IsVoid())
    return IntPatch_ImpImpIntersection::IntStatus_OK;

  {

    const double aF          = 1.0e+5;
    const double aMaxV1Range = aF * theCyl1.Radius(), aMaxV2Range = aF * theCyl2.Radius();
    if ((aRangeS1.Delta() > aMaxV1Range) || (aRangeS2.Delta() > aMaxV2Range))
      return IntPatch_ImpImpIntersection::IntStatus_InfiniteSectionCurve;
  }

  bool   isGoodIntersection = false;
  double anOptdu            = 0.;
  for (;;)
  {

    const double aToMuchCoeff = 3.;
    const double aCritAngle   = M_PI / 18.;
    double       anR1         = theCyl1.Radius();
    double       anR2         = theCyl2.Radius();
    double       anRmin = 0., anRmax = 0.;

    if (anR1 > aToMuchCoeff * anR2)
    {
      anRmax = anR1;
      anRmin = anR2;
    }
    else if (anR2 > aToMuchCoeff * anR1)
    {
      anRmax = anR2;
      anRmin = anR1;
    }
    else
    {
      break;
    }

    const gp_Ax1& anAx1 = theCyl1.Axis();
    const gp_Ax1& anAx2 = theCyl2.Axis();
    if (!anAx1.IsNormal(anAx2, aCritAngle))
    {
      break;
    }

    gp_Lin anL1(anAx1), anL2(anAx2);
    double aDist = anL1.Distance(anL2);
    if (aDist > anRmax / 2.)
    {
      break;
    }

    isGoodIntersection = true;

    double aDeflection = 0.001;
    int    aNbP        = 3;
    if (anRmin * aDeflection > 1.e-3)
    {
      double anAngle = 1.0e0 - aDeflection;
      anAngle        = 2.0e0 * std::acos(anAngle);
      aNbP           = (int)(2. * M_PI / anAngle) + 1;
    }
    anOptdu = 2. * M_PI_2 / (double)(aNbP - 1);
    break;
  }

  const ComputationMethods::stCoeffsValue& anEquationCoeffs = theBW.SICoeffs();
  const IntSurf_Quadric&                   aQuad1           = theBW.GetQSurface(1);
  const IntSurf_Quadric&                   aQuad2           = theBW.GetQSurface(2);
  const bool                               isReversed       = theBW.IsReversed();
  const double                             aTol2D           = theBW.Get2dTolerance();
  const double                             aTol3D           = theBW.Get3dTolerance();
  const double                             aPeriod          = 2.0 * M_PI;
  int                                      aNbMaxPoints     = 1000;
  int                                      aNbMinPoints     = 200;
  double                                   du;
  if (isGoodIntersection)
  {
    du           = anOptdu;
    aNbMaxPoints = 200;
    aNbMinPoints = 50;
  }
  else
  {
    du = 2. * M_PI / aNbMaxPoints;
  }
  int aNbPts =
    std::min(RealToInt((aUSurf1l - aUSurf1f) / du) + 1, RealToInt(20.0 * theCyl1.Radius()));
  const int    aNbPoints = std::min(std::max(aNbMinPoints, aNbPts), aNbMaxPoints);
  const double aStepMin  = std::max(aTol2D, Precision::PConfusion()),
               aStepMax  = (aUSurf1l - aUSurf1f > M_PI / 100.0)
                             ? (aUSurf1l - aUSurf1f) / IntToReal(aNbPoints)
                             : aUSurf1l - aUSurf1f;

  for (int i = 0; i < theNbOfRanges; i++)
  {
    if (theRange[i].IsVoid())
      continue;

    InscribeInterval(aUSurf1f, aUSurf1l, theRange[i], aTol2D, aPeriod);
  }

  if (theRange[0].Union(theRange[1]))
  {

    theRange[1].SetVoid();
  }

  const int aNbCritPointsMax           = 12;
  double    anU1crit[aNbCritPointsMax] = {Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite(),
                                          Precision::Infinite()};

  int aNbCritPoints = aNbCritPointsMax;
  CriticalPointsComputing(anEquationCoeffs,
                          aUSurf1f,
                          aUSurf1l,
                          aUSurf2f,
                          aUSurf2l,
                          aPeriod,
                          aTol2D,
                          aNbCritPoints,
                          anU1crit);

  enum WLFStatus
  {

    WLFStatus_Absent = 0,

    WLFStatus_Exist = 1,

    WLFStatus_Broken = 2
  };

  const int aNbWLines = 2;
  for (int aCurInterval = 0; aCurInterval < theNbOfRanges; aCurInterval++)
  {

    bool isAddedIntoWL[aNbWLines];
    for (int i = 0; i < aNbWLines; i++)
      isAddedIntoWL[i] = false;

    double anUf = 1.0, anUl = 0.0;
    if (!theRange[aCurInterval].GetBounds(anUf, anUl))
      continue;

    const bool isDeltaPeriod = IsEqual(anUl - anUf, aPeriod);

    for (int i = 0; i < aNbCritPoints; i++)
    {
      InscribePoint(anUf, anUl, anU1crit[i], 0.0, aPeriod, false);
    }

    std::sort(anU1crit, anU1crit + aNbCritPoints);

    while (anUf < anUl)
    {

      double    aU2[aNbWLines], aV1[aNbWLines], aV2[aNbWLines];
      WLFStatus aWLFindStatus[aNbWLines];
      double    aV1Prev[aNbWLines], aV2Prev[aNbWLines];
      double    anUexpect[aNbWLines];
      bool      isAddingWLEnabled[aNbWLines];

      occ::handle<IntSurf_LineOn2S> aL2S[aNbWLines];
      occ::handle<IntPatch_WLine>   aWLine[aNbWLines];
      for (int i = 0; i < aNbWLines; i++)
      {
        aL2S[i]   = new IntSurf_LineOn2S();
        aWLine[i] = new IntPatch_WLine(aL2S[i], false);
        aWLine[i]->SetCreatingWayInfo(IntPatch_WLine::IntPatch_WLImpImp);
        aWLFindStatus[i]     = WLFStatus_Absent;
        isAddingWLEnabled[i] = true;
        aU2[i] = aV1[i] = aV2[i] = 0.0;
        aV1Prev[i] = aV2Prev[i] = 0.0;
        anUexpect[i]            = anUf;
      }

      double aCriticalDelta[aNbCritPointsMax] = {0};
      for (int aCritPID = 0; aCritPID < aNbCritPoints; aCritPID++)
      {

        aCriticalDelta[aCritPID] = anUf - anU1crit[aCritPID];
      }

      double anU1 = anUf, aMinCriticalParam = anUf;
      bool   isFirst = true;

      while (anU1 <= anUl)
      {

        for (int i = 0; i < aNbCritPoints; i++)
        {
          if ((anU1 - anU1crit[i]) * aCriticalDelta[i] < 0.0)
          {

            anU1 = anU1crit[i];

            for (int j = 0; j < aNbWLines; j++)
            {
              aWLFindStatus[j] = WLFStatus_Broken;
              anUexpect[j]     = anU1;
            }

            break;
          }
        }

        if (IsEqual(anU1, anUl))
        {
          for (int i = 0; i < aNbWLines; i++)
          {
            aWLFindStatus[i] = WLFStatus_Broken;
            anUexpect[i]     = anU1;

            if (isDeltaPeriod)
            {

              isAddingWLEnabled[i] = (!isAddedIntoWL[i]);
            }
            else
            {
              isAddingWLEnabled[i] =
                ((aTol2D >= (anUexpect[i] - anU1)) || (aWLFindStatus[i] == WLFStatus_Absent));
            }
          }
        }
        else
        {
          for (int i = 0; i < aNbWLines; i++)
          {
            isAddingWLEnabled[i] =
              ((aTol2D >= (anUexpect[i] - anU1)) || (aWLFindStatus[i] == WLFStatus_Absent));
          }
        }

        for (int i = 0; i < aNbWLines; i++)
        {
          const int aNbPntsWL = aWLine[i].IsNull() ? 0 : aWLine[i]->Curve()->NbPoints();

          if ((aWLFindStatus[i] == WLFStatus_Broken) || (aWLFindStatus[i] == WLFStatus_Absent))
          {

            double aTol = aTol2D;
            ComputationMethods::CylCylComputeParameters(anU1, i, anEquationCoeffs, aU2[i], &aTol);
            InscribePoint(aUSurf2f, aUSurf2l, aU2[i], aTol2D, aPeriod, false);

            aTol = std::max(aTol, aTol2D);

            if (std::abs(aU2[i]) <= aTol)
              aU2[i] = 0.0;
            else if (std::abs(aU2[i] - aPeriod) <= aTol)
              aU2[i] = aPeriod;
            else if (std::abs(aU2[i] - aUSurf2f) <= aTol)
              aU2[i] = aUSurf2f;
            else if (std::abs(aU2[i] - aUSurf2l) <= aTol)
              aU2[i] = aUSurf2l;
          }
          else
          {
            ComputationMethods::CylCylComputeParameters(anU1, i, anEquationCoeffs, aU2[i]);
            InscribePoint(aUSurf2f, aUSurf2l, aU2[i], aTol2D, aPeriod, false);
          }

          if (aNbPntsWL == 0)
          {
            if (((aUSurf2f + aPeriod - aUSurf2l) <= 2.0 * aTol2D)
                && ((std::abs(aU2[i] - aUSurf2f) < aTol2D)
                    || (std::abs(aU2[i] - aUSurf2l) < aTol2D)))
            {

              bool isIncreasing = true;
              ComputationMethods::CylCylMonotonicity(anU1 + aStepMin,
                                                     i,
                                                     anEquationCoeffs,
                                                     aPeriod,
                                                     isIncreasing);

              if (isIncreasing)
              {
                aU2[i] = aUSurf2f;
              }
              else
              {
                aU2[i] = aUSurf2l;
              }
            }
          }
          else
          {
            if (((aUSurf2l - aUSurf2f) >= aPeriod)
                && ((std::abs(aU2[i] - aUSurf2f) < aTol2D)
                    || (std::abs(aU2[i] - aUSurf2l) < aTol2D)))
            {
              double aU2prev = 0.0, aV2prev = 0.0;
              if (isReversed)
                aWLine[i]->Curve()->Value(aNbPntsWL).ParametersOnS1(aU2prev, aV2prev);
              else
                aWLine[i]->Curve()->Value(aNbPntsWL).ParametersOnS2(aU2prev, aV2prev);

              if (2.0 * std::abs(aU2prev - aU2[i]) > aPeriod)
              {
                if (aU2prev > aU2[i])
                  aU2[i] += aPeriod;
                else
                  aU2[i] -= aPeriod;
              }
            }
          }

          ComputationMethods::CylCylComputeParameters(anU1,
                                                      aU2[i],
                                                      anEquationCoeffs,
                                                      aV1[i],
                                                      aV2[i]);

          if (isFirst)
          {
            aV1Prev[i] = aV1[i];
            aV2Prev[i] = aV2[i];
          }
        }

        isFirst = false;

        bool isBroken = false;
        for (int i = 0; i < aNbWLines; i++)
        {
          if (!isAddingWLEnabled[i])
          {
            bool isBoundIntersect = false;
            if ((std::abs(aV1[i] - aVSurf1f) <= aTol2D)
                || ((aV1[i] - aVSurf1f) * (aV1Prev[i] - aVSurf1f) < 0.0))
            {
              isBoundIntersect = true;
            }
            else if ((std::abs(aV1[i] - aVSurf1l) <= aTol2D)
                     || ((aV1[i] - aVSurf1l) * (aV1Prev[i] - aVSurf1l) < 0.0))
            {
              isBoundIntersect = true;
            }
            else if ((std::abs(aV2[i] - aVSurf2f) <= aTol2D)
                     || ((aV2[i] - aVSurf2f) * (aV2Prev[i] - aVSurf2f) < 0.0))
            {
              isBoundIntersect = true;
            }
            else if ((std::abs(aV2[i] - aVSurf2l) <= aTol2D)
                     || ((aV2[i] - aVSurf2l) * (aV2Prev[i] - aVSurf2l) < 0.0))
            {
              isBoundIntersect = true;
            }

            if (aWLFindStatus[i] == WLFStatus_Broken)
              isBroken = true;

            if (!isBoundIntersect)
            {
              continue;
            }
            else
            {
              anUexpect[i] = anU1;
            }
          }

          const bool isInscribe =
            ((aUSurf2f - aU2[i]) <= aTol2D) && ((aU2[i] - aUSurf2l) <= aTol2D)
            && ((aVSurf1f - aV1[i]) <= aTol2D) && ((aV1[i] - aVSurf1l) <= aTol2D)
            && ((aVSurf2f - aV2[i]) <= aTol2D) && ((aV2[i] - aVSurf2l) <= aTol2D);

          const bool isVIntersect =
            (((aVSurf1f - aV1[i]) * (aVSurf1f - aV1Prev[i]) < RealSmall())
             && ((aVSurf1l - aV1[i]) * (aVSurf1l - aV1Prev[i]) < RealSmall()))
            || (((aVSurf2f - aV2[i]) * (aVSurf2f - aV2Prev[i]) < RealSmall())
                && ((aVSurf2l - aV2[i]) * (aVSurf2l - aV2Prev[i]) < RealSmall()));

          bool isFound1 = false, isFound2 = false;
          bool isForce = false;

          if (aWLFindStatus[i] == WLFStatus_Absent)
          {
            if (((aUSurf2l - aUSurf2f) >= aPeriod) && (std::abs(anU1 - aUSurf1l) < aTol2D))
            {
              isForce = true;
            }
          }

          theBW.AddBoundaryPoint(aWLine[i],
                                 anU1,
                                 aMinCriticalParam,
                                 aU2[i],
                                 aV1[i],
                                 aV1Prev[i],
                                 aV2[i],
                                 aV2Prev[i],
                                 i,
                                 isForce,
                                 isFound1,
                                 isFound2);

          const bool isPrevVBound = !isVIntersect
                                    && ((std::abs(aV1Prev[i] - aVSurf1f) <= aTol2D)
                                        || (std::abs(aV1Prev[i] - aVSurf1l) <= aTol2D)
                                        || (std::abs(aV2Prev[i] - aVSurf2f) <= aTol2D)
                                        || (std::abs(aV2Prev[i] - aVSurf2l) <= aTol2D));

          aV1Prev[i] = aV1[i];
          aV2Prev[i] = aV2[i];

          if ((aWLFindStatus[i] == WLFStatus_Exist) && (isFound1 || isFound2) && !isPrevVBound)
          {
            aWLFindStatus[i] = WLFStatus_Broken;
          }
          else if (isInscribe)
          {
            if ((aWLFindStatus[i] == WLFStatus_Absent) && (isFound1 || isFound2))
            {
              aWLFindStatus[i] = WLFStatus_Exist;
            }

            if ((aWLFindStatus[i] != WLFStatus_Broken) || (aWLine[i]->NbPnts() >= 1)
                || IsEqual(anU1, anUl))
            {
              if (aWLine[i]->NbPnts() > 0)
              {
                double aU2p = 0.0, aV2p = 0.0;
                if (isReversed)
                  aWLine[i]->Point(aWLine[i]->NbPnts()).ParametersOnS1(aU2p, aV2p);
                else
                  aWLine[i]->Point(aWLine[i]->NbPnts()).ParametersOnS2(aU2p, aV2p);

                const double aDelta = aU2[i] - aU2p;

                if (2.0 * std::abs(aDelta) > aPeriod)
                {
                  if (aDelta > 0.0)
                  {
                    aU2[i] -= aPeriod;
                  }
                  else
                  {
                    aU2[i] += aPeriod;
                  }
                }
              }

              if (AddPointIntoWL(aQuad1,
                                 aQuad2,
                                 anEquationCoeffs,
                                 isReversed,
                                 true,
                                 gp_Pnt2d(anU1, aV1[i]),
                                 gp_Pnt2d(aU2[i], aV2[i]),
                                 aUSurf1f,
                                 aUSurf1l,
                                 aUSurf2f,
                                 aUSurf2l,
                                 aVSurf1f,
                                 aVSurf1l,
                                 aVSurf2f,
                                 aVSurf2l,
                                 aPeriod,
                                 aWLine[i]->Curve(),
                                 i,
                                 aTol3D,
                                 aTol2D,
                                 isForce))
              {
                if (aWLFindStatus[i] == WLFStatus_Absent)
                {
                  aWLFindStatus[i] = WLFStatus_Exist;
                }
              }
              else if (!isFound1 && !isFound2)
              {
                if (aWLFindStatus[i] == WLFStatus_Exist)
                {
                  aWLFindStatus[i] = WLFStatus_Broken;
                }
              }
            }
          }
          else
          {
            if (aWLFindStatus[i] == WLFStatus_Exist)
            {
              aWLFindStatus[i] = WLFStatus_Broken;
            }
          }

          if (aWLFindStatus[i] == WLFStatus_Broken)
            isBroken = true;
        }

        if (isBroken)
        {
          anUf = anU1;

          bool isAdded = true;

          for (int i = 0; i < aNbWLines; i++)
          {
            if (isAddingWLEnabled[i])
            {
              continue;
            }

            isAdded = false;

            bool isFound1 = false, isFound2 = false;

            theBW.AddBoundaryPoint(aWLine[i],
                                   anU1,
                                   aMinCriticalParam,
                                   aU2[i],
                                   aV1[i],
                                   aV1Prev[i],
                                   aV2[i],
                                   aV2Prev[i],
                                   i,
                                   false,
                                   isFound1,
                                   isFound2);

            if (isFound1 || isFound2)
            {
              isAdded = true;
            }

            if (aWLine[i]->NbPnts() > 0)
            {
              double aU2p = 0.0, aV2p = 0.0;
              if (isReversed)
                aWLine[i]->Point(aWLine[i]->NbPnts()).ParametersOnS1(aU2p, aV2p);
              else
                aWLine[i]->Point(aWLine[i]->NbPnts()).ParametersOnS2(aU2p, aV2p);

              const double aDelta = aU2[i] - aU2p;

              if (2 * std::abs(aDelta) > aPeriod)
              {
                if (aDelta > 0.0)
                {
                  aU2[i] -= aPeriod;
                }
                else
                {
                  aU2[i] += aPeriod;
                }
              }
            }

            if (AddPointIntoWL(aQuad1,
                               aQuad2,
                               anEquationCoeffs,
                               isReversed,
                               true,
                               gp_Pnt2d(anU1, aV1[i]),
                               gp_Pnt2d(aU2[i], aV2[i]),
                               aUSurf1f,
                               aUSurf1l,
                               aUSurf2f,
                               aUSurf2l,
                               aVSurf1f,
                               aVSurf1l,
                               aVSurf2f,
                               aVSurf2l,
                               aPeriod,
                               aWLine[i]->Curve(),
                               i,
                               aTol3D,
                               aTol2D,
                               false))
            {
              isAdded = true;
            }
          }

          if (!isAdded)
          {

            double anUmaxAdded = RealFirst();

            {
              bool isChanged = false;
              for (int i = 0; i < aNbWLines; i++)
              {
                if ((aWLFindStatus[i] == WLFStatus_Absent) || (aWLine[i]->NbPnts() == 0))
                  continue;

                double aU1c = 0.0, aV1c = 0.0;
                if (isReversed)
                  aWLine[i]->Curve()->Value(aWLine[i]->NbPnts()).ParametersOnS2(aU1c, aV1c);
                else
                  aWLine[i]->Curve()->Value(aWLine[i]->NbPnts()).ParametersOnS1(aU1c, aV1c);

                anUmaxAdded = std::max(anUmaxAdded, aU1c);
                isChanged   = true;
              }

              if (!isChanged)
              {

                break;
              }
            }

            for (int i = 0; i < aNbWLines; i++)
            {
              if (isAddingWLEnabled[i])
              {
                continue;
              }

              ComputationMethods::CylCylComputeParameters(anUmaxAdded,
                                                          i,
                                                          anEquationCoeffs,
                                                          aU2[i],
                                                          aV1[i],
                                                          aV2[i]);

              AddPointIntoWL(aQuad1,
                             aQuad2,
                             anEquationCoeffs,
                             isReversed,
                             true,
                             gp_Pnt2d(anUmaxAdded, aV1[i]),
                             gp_Pnt2d(aU2[i], aV2[i]),
                             aUSurf1f,
                             aUSurf1l,
                             aUSurf2f,
                             aUSurf2l,
                             aVSurf1f,
                             aVSurf1l,
                             aVSurf2f,
                             aVSurf2l,
                             aPeriod,
                             aWLine[i]->Curve(),
                             i,
                             aTol3D,
                             aTol2D,
                             false);
            }
          }

          break;
        }

        {

          const double aDeltaV1 = aRangeS1.Delta() / IntToReal(aNbPoints),
                       aDeltaV2 = aRangeS2.Delta() / IntToReal(aNbPoints);

          math_Matrix aMatr(1, 3, 1, 5);

          double aMinUexp = RealLast();

          for (int i = 0; i < aNbWLines; i++)
          {
            if (aTol2D < (anUexpect[i] - anU1))
            {
              continue;
            }

            if (aWLFindStatus[i] == WLFStatus_Absent)
            {
              anUexpect[i] += aStepMax;
              aMinUexp = std::min(aMinUexp, anUexpect[i]);
              continue;
            }

            if (isGoodIntersection)
            {

              anUexpect[i] += aStepMax;
              aMinUexp = std::min(aMinUexp, anUexpect[i]);

              continue;
            }

            double aStepTmp = aStepMax;

            const double aSinU1 = sin(anU1), aCosU1 = cos(anU1), aSinU2 = sin(aU2[i]),
                         aCosU2 = cos(aU2[i]);

            aMatr.SetCol(1, anEquationCoeffs.mVecC1);
            aMatr.SetCol(2, anEquationCoeffs.mVecC2);
            aMatr.SetCol(3, anEquationCoeffs.mVecA1 * aSinU1 - anEquationCoeffs.mVecB1 * aCosU1);
            aMatr.SetCol(4, anEquationCoeffs.mVecA2 * aSinU2 - anEquationCoeffs.mVecB2 * aCosU2);
            aMatr.SetCol(5,
                         anEquationCoeffs.mVecA1 * aCosU1 + anEquationCoeffs.mVecB1 * aSinU1
                           + anEquationCoeffs.mVecA2 * aCosU2 + anEquationCoeffs.mVecB2 * aSinU2
                           + anEquationCoeffs.mVecD);

            if (!StepComputing(aMatr, aV1[i], aV2[i], aDeltaV1, aDeltaV2, aStepTmp))
            {

              anUexpect[i] += aStepMax;
              aMinUexp = std::min(aMinUexp, anUexpect[i]);

              continue;
            }

            if (aStepTmp < aStepMin)
              aStepTmp = aStepMin;

            if (aStepTmp > aStepMax)
              aStepTmp = aStepMax;

            anUexpect[i] = anU1 + aStepTmp;
            aMinUexp     = std::min(aMinUexp, anUexpect[i]);
          }

          anU1 = aMinUexp;
        }

        if (Precision::PConfusion() >= (anUl - anU1))
          anU1 = anUl;

        anUf = anU1;

        for (int i = 0; i < aNbWLines; i++)
        {
          if (aWLine[i]->NbPnts() != 1)
            isAddedIntoWL[i] = false;

          if (anU1 == anUl)
          {
            anUexpect[i] = anUl;
          }
        }
      }

      for (int i = 0; i < aNbWLines; i++)
      {
        if ((aWLine[i]->NbPnts() == 1) && (!isAddedIntoWL[i]))
        {
          isTheEmpty = false;
          double u1, v1, u2, v2;
          aWLine[i]->Point(1).Parameters(u1, v1, u2, v2);
          IntPatch_Point aP;
          aP.SetParameter(u1);
          aP.SetParameters(u1, v1, u2, v2);
          aP.SetTolerance(aTol3D);
          aP.SetValue(aWLine[i]->Point(1).Value());

          if (theSPnt.IsEmpty()
              || !theSPnt.Last().PntOn2S().IsSame(aP.PntOn2S(), Precision::Confusion()))
          {
            theSPnt.Append(aP);
          }
        }
        else if (aWLine[i]->NbPnts() > 1)
        {
          bool isGood = true;

          if (aWLine[i]->NbPnts() == 2)
          {
            const IntSurf_PntOn2S& aPf = aWLine[i]->Point(1);
            const IntSurf_PntOn2S& aPl = aWLine[i]->Point(2);

            if (aPf.IsSame(aPl, Precision::Confusion()))
              isGood = false;
          }
          else if (aWLine[i]->NbPnts() > 2)
          {

            const double aSqTol3D = aTol3D * aTol3D;
            for (int j = 0; j < 2; j++)
            {

              for (;;)
              {
                if (aWLine[i]->NbPnts() >= aNbMaxPoints)
                {
                  break;
                }

                const int anIdx1 = j ? aWLine[i]->NbPnts() - 1 : 2;
                const int anIdx2 = j ? aWLine[i]->NbPnts() : 1;

                const gp_Pnt& aP1 = aWLine[i]->Point(anIdx1).Value();
                const gp_Pnt& aP2 = aWLine[i]->Point(anIdx2).Value();

                const gp_Vec aDir(aP1, aP2);

                if (aDir.SquareMagnitude() < aSqTol3D)
                {
                  break;
                }

                const gp_Vec aN1 = aQuad1.Normale(aP2);
                const gp_Vec aN2 = aQuad2.Normale(aP2);
                const gp_Vec aTg(aN1.Crossed(aN2));

                if (aTg.SquareMagnitude() < Precision::SquareConfusion())
                {

                  break;
                }

                double anAngle = aDir.Angle(aTg);

                if (anAngle > M_PI_2)
                  anAngle -= M_PI;

                if (std::abs(anAngle) > 0.25)
                {
                  const int aNbPntsPrev = aWLine[i]->NbPnts();
                  SeekAdditionalPoints(aQuad1,
                                       aQuad2,
                                       aWLine[i]->Curve(),
                                       anEquationCoeffs,
                                       i,
                                       3,
                                       anIdx1,
                                       anIdx2,
                                       aTol2D,
                                       aPeriod,
                                       isReversed);

                  if (aWLine[i]->NbPnts() == aNbPntsPrev)
                  {

                    break;
                  }
                }
                else
                {

                  break;
                }
              }
            }
          }

          if (isGood)
          {
            isTheEmpty       = false;
            isAddedIntoWL[i] = true;
            SeekAdditionalPoints(aQuad1,
                                 aQuad2,
                                 aWLine[i]->Curve(),
                                 anEquationCoeffs,
                                 i,
                                 aNbPoints,
                                 1,
                                 aWLine[i]->NbPnts(),
                                 aTol2D,
                                 aPeriod,
                                 isReversed);

            aWLine[i]->ComputeVertexParameters(aTol3D);
            theSlin.Append(aWLine[i]);
          }
        }
        else
        {
          isAddedIntoWL[i] = false;
        }

#ifdef INTPATCH_IMPIMPINTERSECTION_DEBUG
        aWLine[i]->Dump(0);
#endif
      }
    }
  }

  for (int aNbPnt = 1; aNbPnt <= theSPnt.Length(); aNbPnt++)
  {
    for (int aNbLin = 1; aNbLin <= theSlin.Length(); aNbLin++)
    {
      occ::handle<IntPatch_WLine> aWLine1(occ::down_cast<IntPatch_WLine>(theSlin.Value(aNbLin)));

      const IntSurf_PntOn2S& aPntFWL1 = aWLine1->Point(1);
      const IntSurf_PntOn2S& aPntLWL1 = aWLine1->Point(aWLine1->NbPnts());

      const IntSurf_PntOn2S aPntCur = theSPnt.Value(aNbPnt).PntOn2S();
      if (aPntCur.IsSame(aPntFWL1, aTol3D) || aPntCur.IsSame(aPntLWL1, aTol3D))
      {
        theSPnt.Remove(aNbPnt);
        aNbPnt--;
        break;
      }
    }
  }

  for (int aNbPnt = 1; aNbPnt <= theSPnt.Length(); aNbPnt++)
  {

    const IntPatch_Point& aPnt2S = theSPnt.Value(aNbPnt);

    double u1, v1, u2, v2;
    aPnt2S.Parameters(u1, v1, u2, v2);

    occ::handle<IntSurf_LineOn2S> aL2S   = new IntSurf_LineOn2S();
    occ::handle<IntPatch_WLine>   aWLine = new IntPatch_WLine(aL2S, false);
    aWLine->SetCreatingWayInfo(IntPatch_WLine::IntPatch_WLImpImp);

    int anIndex = 0;

    double anUf = 0.0, anUl = 0.0, aCurU2 = 0.0;
    if (isReversed)
    {
      anUf   = std::max(u2 - aStepMax, aUSurf1f);
      anUl   = std::min(u2 + aStepMax, aUSurf1l);
      aCurU2 = u1;
    }
    else
    {
      anUf   = std::max(u1 - aStepMax, aUSurf1f);
      anUl   = std::min(u1 + aStepMax, aUSurf1l);
      aCurU2 = u2;
    }

    const double anUinf = anUf, anUsup = anUl, anUmid = 0.5 * (anUf + anUl);

    {

      double aDelta = RealLast();
      for (int i = 0; i < aNbWLines; i++)
      {
        double anU2t = 0.0;
        if (!ComputationMethods::CylCylComputeParameters(anUmid, i, anEquationCoeffs, anU2t))
          continue;

        double aDU2 = fmod(std::abs(anU2t - aCurU2), aPeriod);
        aDU2        = std::min(aDU2, std::abs(aDU2 - aPeriod));
        if (aDU2 < aDelta)
        {
          aDelta  = aDU2;
          anIndex = i;
        }
      }
    }

    double anAddedPar[2] = {isReversed ? u2 : u1, isReversed ? u2 : u1};

    for (int aParID = 0; aParID < 2; aParID++)
    {
      if (aParID == 0)
      {
        anUf = anUinf;
        anUl = anUmid;
      }
      else
      {
        anUf = anUmid;
        anUl = anUsup;
      }

      double &aPar1 = (aParID == 0) ? anUf : anUl, &aPar2 = (aParID == 0) ? anUl : anUf;

      while (std::abs(aPar2 - aPar1) > aStepMin)
      {
        double anUC = 0.5 * (anUf + anUl);
        double aU2 = 0.0, aV1 = 0.0, aV2 = 0.0;
        bool   isDone = ComputationMethods::CylCylComputeParameters(anUC,
                                                                  anIndex,
                                                                  anEquationCoeffs,
                                                                  aU2,
                                                                  aV1,
                                                                  aV2);

        if (isDone)
        {
          if (std::abs(aV1 - aVSurf1f) <= aTol2D)
            aV1 = aVSurf1f;

          if (std::abs(aV1 - aVSurf1l) <= aTol2D)
            aV1 = aVSurf1l;

          if (std::abs(aV2 - aVSurf2f) <= aTol2D)
            aV2 = aVSurf2f;

          if (std::abs(aV2 - aVSurf2l) <= aTol2D)
            aV2 = aVSurf2l;

          isDone = AddPointIntoWL(aQuad1,
                                  aQuad2,
                                  anEquationCoeffs,
                                  isReversed,
                                  true,
                                  gp_Pnt2d(anUC, aV1),
                                  gp_Pnt2d(aU2, aV2),
                                  aUSurf1f,
                                  aUSurf1l,
                                  aUSurf2f,
                                  aUSurf2l,
                                  aVSurf1f,
                                  aVSurf1l,
                                  aVSurf2f,
                                  aVSurf2l,
                                  aPeriod,
                                  aWLine->Curve(),
                                  anIndex,
                                  aTol3D,
                                  aTol2D,
                                  false,
                                  true);
        }

        if (isDone)
        {
          anAddedPar[0] = std::min(anAddedPar[0], anUC);
          anAddedPar[1] = std::max(anAddedPar[1], anUC);
          aPar2         = anUC;
        }
        else
        {
          aPar1 = anUC;
        }
      }
    }

    if (anAddedPar[1] - anAddedPar[0] > aStepMin)
    {
      for (int aParID = 0; aParID < 2; aParID++)
      {
        double aU2 = 0.0, aV1 = 0.0, aV2 = 0.0;
        ComputationMethods::CylCylComputeParameters(anAddedPar[aParID],
                                                    anIndex,
                                                    anEquationCoeffs,
                                                    aU2,
                                                    aV1,
                                                    aV2);

        AddPointIntoWL(aQuad1,
                       aQuad2,
                       anEquationCoeffs,
                       isReversed,
                       true,
                       gp_Pnt2d(anAddedPar[aParID], aV1),
                       gp_Pnt2d(aU2, aV2),
                       aUSurf1f,
                       aUSurf1l,
                       aUSurf2f,
                       aUSurf2l,
                       aVSurf1f,
                       aVSurf1l,
                       aVSurf2f,
                       aVSurf2l,
                       aPeriod,
                       aWLine->Curve(),
                       anIndex,
                       aTol3D,
                       aTol2D,
                       false,
                       false);
      }

      SeekAdditionalPoints(aQuad1,
                           aQuad2,
                           aWLine->Curve(),
                           anEquationCoeffs,
                           anIndex,
                           aNbMinPoints,
                           1,
                           aWLine->NbPnts(),
                           aTol2D,
                           aPeriod,
                           isReversed);

      aWLine->ComputeVertexParameters(aTol3D);
      theSlin.Append(aWLine);

      theSPnt.Remove(aNbPnt);
      aNbPnt--;
    }
  }

  return IntPatch_ImpImpIntersection::IntStatus_OK;
}

IntPatch_ImpImpIntersection::IntStatus IntCyCy(
  const IntSurf_Quadric&                            theQuad1,
  const IntSurf_Quadric&                            theQuad2,
  const double                                      theTol3D,
  const double                                      theTol2D,
  const Bnd_Box2d&                                  theUVSurf1,
  const Bnd_Box2d&                                  theUVSurf2,
  bool&                                             isTheEmpty,
  bool&                                             isTheSameSurface,
  bool&                                             isTheMultiplePoint,
  NCollection_Sequence<occ::handle<IntPatch_Line>>& theSlin,
  NCollection_Sequence<IntPatch_Point>&             theSPnt)
{
  isTheEmpty         = true;
  isTheSameSurface   = false;
  isTheMultiplePoint = false;
  theSlin.Clear();
  theSPnt.Clear();

  const gp_Cylinder aCyl1 = theQuad1.Cylinder(), aCyl2 = theQuad2.Cylinder();

  IntAna_QuadQuadGeo anInter(aCyl1, aCyl2, theTol3D);

  if (!anInter.IsDone())
  {
    return IntPatch_ImpImpIntersection::IntStatus_Fail;
  }

  if (anInter.TypeInter() != IntAna_NoGeometricSolution)
  {
    if (CyCyAnalyticalIntersect(theQuad1,
                                theQuad2,
                                anInter,
                                theTol3D,
                                isTheEmpty,
                                isTheSameSurface,
                                isTheMultiplePoint,
                                theSlin,
                                theSPnt))
    {
      return IntPatch_ImpImpIntersection::IntStatus_OK;
    }
  }

  double aUSBou[2][2], aVSBou[2][2];

  theUVSurf1.Get(aUSBou[0][0], aVSBou[0][0], aUSBou[0][1], aVSBou[0][1]);
  theUVSurf2.Get(aUSBou[1][0], aVSBou[1][0], aUSBou[1][1], aVSBou[1][1]);

  const double aPeriod   = 2.0 * M_PI;
  const int    aNbWLines = 2;

  const ComputationMethods::stCoeffsValue anEquationCoeffs1(aCyl1, aCyl2);
  const ComputationMethods::stCoeffsValue anEquationCoeffs2(aCyl2, aCyl1);

  const int aNbOfBoundaries = 2;
  Bnd_Range anURange[2][aNbOfBoundaries];

  if (!WorkWithBoundaries::BoundariesComputing(anEquationCoeffs1, aPeriod, anURange[0]))
    return IntPatch_ImpImpIntersection::IntStatus_OK;

  if (!WorkWithBoundaries::BoundariesComputing(anEquationCoeffs2, aPeriod, anURange[1]))
    return IntPatch_ImpImpIntersection::IntStatus_OK;

  double                                aSumRange[2] = {0.0, 0.0};
  occ::handle<NCollection_IncAllocator> anAlloc      = new NCollection_IncAllocator;
  for (int aCID = 0; aCID < 2; aCID++)
  {
    anAlloc->Reset(false);
    NCollection_List<Bnd_Range> aListOfRng(anAlloc);

    aListOfRng.Append(anURange[aCID][0]);
    aListOfRng.Append(anURange[aCID][1]);

    const double aSplitArr[3] = {aUSBou[aCID][0], aUSBou[aCID][1], 0.0};

    NCollection_List<Bnd_Range>::Iterator anITrRng;
    for (int aSInd = 0; aSInd < 3; aSInd++)
    {
      NCollection_List<Bnd_Range> aLstTemp(aListOfRng);
      aListOfRng.Clear();
      for (anITrRng.Init(aLstTemp); anITrRng.More(); anITrRng.Next())
      {
        Bnd_Range& aRng = anITrRng.ChangeValue();
        aRng.Split(aSplitArr[aSInd], aListOfRng, aPeriod);
      }
    }

    anITrRng.Init(aListOfRng);
    for (; anITrRng.More(); anITrRng.Next())
    {
      Bnd_Range& aCurrRange = anITrRng.ChangeValue();

      Bnd_Range aBoundR;
      aBoundR.Add(aUSBou[aCID][0]);
      aBoundR.Add(aUSBou[aCID][1]);

      if (!InscribeInterval(aUSBou[aCID][0], aUSBou[aCID][1], aCurrRange, theTol2D, aPeriod))
      {

        double aF = 1.0, aL = 0.0;
        if (!aCurrRange.GetBounds(aF, aL))
          continue;

        if ((aL < aUSBou[aCID][0]))
        {
          aCurrRange.Shift(aPeriod);
        }
        else if (aF > aUSBou[aCID][1])
        {
          aCurrRange.Shift(-aPeriod);
        }
      }

      aBoundR.Common(aCurrRange);

      const double aDelta = aBoundR.Delta();

      if (aDelta > 0.0)
      {
        aSumRange[aCID] += aDelta;
      }
    }
  }

  const bool isToReverse = (aSumRange[1] > aSumRange[0]);

  if (isToReverse)
  {
    const WorkWithBoundaries aBoundWork(theQuad2,
                                        theQuad1,
                                        anEquationCoeffs2,
                                        theUVSurf2,
                                        theUVSurf1,
                                        aNbWLines,
                                        aPeriod,
                                        theTol3D,
                                        theTol2D,
                                        true);

    return CyCyNoGeometric(aCyl2,
                           aCyl1,
                           aBoundWork,
                           anURange[1],
                           aNbOfBoundaries,
                           isTheEmpty,
                           theSlin,
                           theSPnt);
  }
  else
  {
    const WorkWithBoundaries aBoundWork(theQuad1,
                                        theQuad2,
                                        anEquationCoeffs1,
                                        theUVSurf1,
                                        theUVSurf2,
                                        aNbWLines,
                                        aPeriod,
                                        theTol3D,
                                        theTol2D,
                                        false);

    return CyCyNoGeometric(aCyl1,
                           aCyl2,
                           aBoundWork,
                           anURange[0],
                           aNbOfBoundaries,
                           isTheEmpty,
                           theSlin,
                           theSPnt);
  }
}

bool IntCySp(const IntSurf_Quadric&                            Quad1,
             const IntSurf_Quadric&                            Quad2,
             const double                                      Tol,
             const bool                                        Reversed,
             bool&                                             Empty,
             bool&                                             Multpoint,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
             NCollection_Sequence<IntPatch_Point>&             spnt)

{
  int i;

  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;
  IntPatch_Point    ptsol;
  gp_Circ           cirsol;

  gp_Cylinder Cy;
  gp_Sphere   Sp;

  if (!Reversed)
  {
    Cy = Quad1.Cylinder();
    Sp = Quad2.Sphere();
  }
  else
  {
    Cy = Quad2.Cylinder();
    Sp = Quad1.Sphere();
  }
  IntAna_QuadQuadGeo inter(Cy, Sp, Tol);

  if (!inter.IsDone())
  {
    return false;
  }

  typint    = inter.TypeInter();
  int NbSol = inter.NbSolutions();
  Empty     = false;

  switch (typint)
  {
    case IntAna_Empty:
    {
      Empty = true;
    }
    break;

    case IntAna_Point:
    {
      gp_Pnt psol(inter.Point(1));
      double U1, V1, U2, V2;
      Quad1.Parameters(psol, U1, V1);
      Quad2.Parameters(psol, U2, V2);
      ptsol.SetValue(psol, Tol, true);
      ptsol.SetParameters(U1, V1, U2, V2);
      spnt.Append(ptsol);
    }
    break;

    case IntAna_Circle:
    {
      cirsol = inter.Circle(1);
      gp_Vec Tgt;
      gp_Pnt ptref;
      ElCLib::D1(0., cirsol, ptref, Tgt);

      if (NbSol == 1)
      {
        gp_Vec TestCurvature(ptref, Sp.Location());
        gp_Vec Normsp, Normcyl;
        if (!Reversed)
        {
          Normcyl = Quad1.Normale(ptref);
          Normsp  = Quad2.Normale(ptref);
        }
        else
        {
          Normcyl = Quad2.Normale(ptref);
          Normsp  = Quad1.Normale(ptref);
        }

        IntSurf_Situation situcyl;
        IntSurf_Situation situsp;

        if (Normcyl.Dot(TestCurvature) > 0.)
        {
          situsp = IntSurf_Outside;
          if (Normsp.Dot(Normcyl) > 0.)
          {
            situcyl = IntSurf_Inside;
          }
          else
          {
            situcyl = IntSurf_Outside;
          }
        }
        else
        {
          situsp = IntSurf_Inside;
          if (Normsp.Dot(Normcyl) > 0.)
          {
            situcyl = IntSurf_Outside;
          }
          else
          {
            situcyl = IntSurf_Inside;
          }
        }
        occ::handle<IntPatch_GLine> glig;
        if (!Reversed)
        {
          glig = new IntPatch_GLine(cirsol, true, situcyl, situsp);
        }
        else
        {
          glig = new IntPatch_GLine(cirsol, true, situsp, situcyl);
        }
        slin.Append(glig);
      }
      else
      {
        if (Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref)) > 0.0)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
        slin.Append(glig);

        cirsol = inter.Circle(2);
        ElCLib::D1(0., cirsol, ptref, Tgt);
        double qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
        if (qwe > 0.0000001)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe < -0.0000001)
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
        glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
        slin.Append(glig);
      }
    }
    break;

    case IntAna_NoGeometricSolution:
    {
      gp_Pnt             psol;
      double             U1, V1, U2, V2;
      IntAna_IntQuadQuad anaint(Cy, Sp, Tol);
      if (!anaint.IsDone())
      {
        return false;
      }

      if (anaint.NbPnt() == 0 && anaint.NbCurve() == 0)
      {
        Empty = true;
      }
      else
      {
        NbSol = anaint.NbPnt();
        for (i = 1; i <= NbSol; i++)
        {
          psol = anaint.Point(i);
          Quad1.Parameters(psol, U1, V1);
          Quad2.Parameters(psol, U2, V2);
          ptsol.SetValue(psol, Tol, true);
          ptsol.SetParameters(U1, V1, U2, V2);
          spnt.Append(ptsol);
        }

        gp_Pnt       ptvalid, ptf, ptl;
        gp_Vec       tgvalid;
        double       first, last, para;
        IntAna_Curve curvsol;
        bool         tgfound;
        int          kount;

        NbSol = anaint.NbCurve();
        for (i = 1; i <= NbSol; i++)
        {
          curvsol = anaint.Curve(i);
          curvsol.Domain(first, last);
          ptf = curvsol.Value(first);
          ptl = curvsol.Value(last);

          para    = last;
          kount   = 1;
          tgfound = false;

          while (!tgfound)
          {
            para    = (1.123 * first + para) / 2.123;
            tgfound = curvsol.D1u(para, ptvalid, tgvalid);
            if (!tgfound)
            {
              kount++;
              tgfound = kount > 5;
            }
          }
          occ::handle<IntPatch_ALine> alig;
          if (kount <= 5)
          {
            double qwe = tgvalid.DotCross(Quad2.Normale(ptvalid), Quad1.Normale(ptvalid));
            if (qwe > 0.00000001)
            {
              trans1 = IntSurf_Out;
              trans2 = IntSurf_In;
            }
            else if (qwe < -0.00000001)
            {
              trans1 = IntSurf_In;
              trans2 = IntSurf_Out;
            }
            else
            {
              trans1 = trans2 = IntSurf_Undecided;
            }
            alig = new IntPatch_ALine(curvsol, false, trans1, trans2);
          }
          else
          {
            alig = new IntPatch_ALine(curvsol, false);
          }
          bool TempFalse1a = false;
          bool TempFalse2a = false;

          ProcessBounds(alig,
                        slin,
                        Quad1,
                        Quad2,
                        TempFalse1a,
                        ptf,
                        first,
                        TempFalse2a,
                        ptl,
                        last,
                        Multpoint,
                        Tol);
          slin.Append(alig);
        }
      }
    }
    break;

    default:
    {
      return false;
    }
  }
  return true;
}

bool IntCyCo(const IntSurf_Quadric&                            Quad1,
             const IntSurf_Quadric&                            Quad2,
             const double                                      Tol,
             const bool                                        Reversed,
             bool&                                             Empty,
             bool&                                             Multpoint,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
             NCollection_Sequence<IntPatch_Point>&             spnt)

{
  IntPatch_Point ptsol;

  int i;

  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;
  gp_Circ           cirsol;

  gp_Cylinder Cy;
  gp_Cone     Co;

  if (!Reversed)
  {
    Cy = Quad1.Cylinder();
    Co = Quad2.Cone();
  }
  else
  {
    Cy = Quad2.Cylinder();
    Co = Quad1.Cone();
  }
  IntAna_QuadQuadGeo inter(Cy, Co, Tol);

  if (!inter.IsDone())
  {
    return false;
  }

  typint    = inter.TypeInter();
  int NbSol = inter.NbSolutions();
  Empty     = false;

  switch (typint)
  {
    case IntAna_Empty:
    {
      Empty = true;
    }
    break;

    case IntAna_Point:
    {
      gp_Pnt psol(inter.Point(1));
      double U1, V1, U2, V2;
      Quad1.Parameters(psol, U1, V1);
      Quad1.Parameters(psol, U2, V2);
      ptsol.SetValue(psol, Tol, true);
      ptsol.SetParameters(U1, V1, U2, V2);
      spnt.Append(ptsol);
    }
    break;

    case IntAna_Circle:
    {
      gp_Vec Tgt;
      gp_Pnt ptref;
      int    j;
      double qwe;

      for (j = 1; j <= 2; ++j)
      {
        cirsol = inter.Circle(j);
        ElCLib::D1(0., cirsol, ptref, Tgt);
        qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
        if (qwe > 0.00000001)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe < -0.00000001)
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
        slin.Append(glig);
      }
    }
    break;

    case IntAna_NoGeometricSolution:
    {
      gp_Pnt             psol;
      double             U1, V1, U2, V2;
      IntAna_IntQuadQuad anaint(Cy, Co, Tol);
      if (!anaint.IsDone())
      {
        return false;
      }

      if (anaint.NbPnt() == 0 && anaint.NbCurve() == 0)
      {
        Empty = true;
      }
      else
      {
        NbSol = anaint.NbPnt();
        for (i = 1; i <= NbSol; i++)
        {
          psol = anaint.Point(i);
          Quad1.Parameters(psol, U1, V1);
          Quad2.Parameters(psol, U2, V2);
          ptsol.SetValue(psol, Tol, true);
          ptsol.SetParameters(U1, V1, U2, V2);
          spnt.Append(ptsol);
        }

        gp_Pnt ptvalid, ptf, ptl;
        gp_Vec tgvalid;

        double first, last, para;
        bool   tgfound, firstp, lastp, kept;
        int    kount;

        IntAna_Curve                             aC;
        NCollection_List<IntAna_Curve>           aLC;
        NCollection_List<IntAna_Curve>::Iterator aIt;

        NbSol = anaint.NbCurve();
        for (i = 1; i <= NbSol; ++i)
        {
          kept = false;

          aC = anaint.Curve(i);
          aLC.Clear();
          ExploreCurve(Co, aC, 10. * Tol, aLC);

          aIt.Initialize(aLC);
          for (; aIt.More(); aIt.Next())
          {
            IntAna_Curve& curvsol = aIt.ChangeValue();

            curvsol.Domain(first, last);
            firstp = !curvsol.IsFirstOpen();
            lastp  = !curvsol.IsLastOpen();
            if (firstp)
            {
              ptf = curvsol.Value(first);
            }
            if (lastp)
            {
              ptl = curvsol.Value(last);
            }
            para    = last;
            kount   = 1;
            tgfound = false;

            while (!tgfound)
            {
              para    = (1.123 * first + para) / 2.123;
              tgfound = curvsol.D1u(para, ptvalid, tgvalid);
              if (!tgfound)
              {
                kount++;
                tgfound = kount > 5;
              }
            }
            occ::handle<IntPatch_ALine> alig;
            if (kount <= 5)
            {
              double qwe = tgvalid.DotCross(Quad2.Normale(ptvalid), Quad1.Normale(ptvalid));
              if (qwe > 0.00000001)
              {
                trans1 = IntSurf_Out;
                trans2 = IntSurf_In;
              }
              else if (qwe < -0.00000001)
              {
                trans1 = IntSurf_In;
                trans2 = IntSurf_Out;
              }
              else
              {
                trans1 = trans2 = IntSurf_Undecided;
              }
              alig = new IntPatch_ALine(curvsol, false, trans1, trans2);
              kept = true;
            }
            else
            {
              ptvalid = curvsol.Value(para);
              alig    = new IntPatch_ALine(curvsol, false);
              kept    = true;
            }
            if (kept)
            {
              bool Nfirstp = !firstp;
              bool Nlastp  = !lastp;
              ProcessBounds(alig,
                            slin,
                            Quad1,
                            Quad2,
                            Nfirstp,
                            ptf,
                            first,
                            Nlastp,
                            ptl,
                            last,
                            Multpoint,
                            Tol);
              slin.Append(alig);
            }
          }
        }
      }
    }
    break;

    default:
      return false;
  }

  return true;
}

bool ExploreCurve(const gp_Cone&                  theCo,
                  IntAna_Curve&                   theCrv,
                  const double                    theTol,
                  NCollection_List<IntAna_Curve>& theLC)
{
  const double aSqTol = theTol * theTol;
  const gp_Pnt aPapx(theCo.Apex());

  double aT1, aT2;
  theCrv.Domain(aT1, aT2);

  theLC.Clear();

  NCollection_List<double> aLParams;
  theCrv.FindParameter(aPapx, aLParams);
  if (aLParams.IsEmpty())
  {
    theLC.Append(theCrv);
    return false;
  }

  for (NCollection_List<double>::Iterator anItr(aLParams); anItr.More(); anItr.Next())
  {
    double aPrm = anItr.Value();

    if ((aPrm - aT1) < Precision::PConfusion())
      continue;

    bool isLast = false;
    if ((aT2 - aPrm) < Precision::PConfusion())
    {
      aPrm   = aT2;
      isLast = true;
    }

    const gp_Pnt aP   = theCrv.Value(aPrm);
    const double aSqD = aP.SquareDistance(aPapx);
    if (aSqD < aSqTol)
    {
      IntAna_Curve aC1 = theCrv;
      aC1.SetDomain(aT1, aPrm);
      aT1 = aPrm;
      theLC.Append(aC1);
    }

    if (isLast)
      break;
  }

  if (theLC.IsEmpty())
  {
    theLC.Append(theCrv);
    return false;
  }

  if ((aT2 - aT1) > Precision::PConfusion())
  {
    IntAna_Curve aC1 = theCrv;
    aC1.SetDomain(aT1, aT2);
    theLC.Append(aC1);
  }

  return true;
}

bool IntCoCo(const IntSurf_Quadric&                            Quad1,
             const IntSurf_Quadric&                            Quad2,
             const double                                      Tol,
             bool&                                             Empty,
             bool&                                             Same,
             bool&                                             Multpoint,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
             NCollection_Sequence<IntPatch_Point>&             spnt)

{
  int               i, NbSol;
  double            U1, V1, U2, V2;
  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;

  gp_Cone Co1(Quad1.Cone());
  gp_Cone Co2(Quad2.Cone());

  IntAna_QuadQuadGeo inter(Co1, Co2, Tol);
  if (!inter.IsDone())
  {
    return false;
  }

  typint = inter.TypeInter();
  NbSol  = inter.NbSolutions();
  Empty  = false;
  Same   = false;

  switch (typint)
  {
    case IntAna_Empty:
    {
      Empty = true;
    }
    break;

    case IntAna_Same:
    {
      Same = true;
    }
    break;

    case IntAna_Line:
    {
      double                      para, aDot;
      gp_Pnt                      aPApex1, aPApex2, ptbid;
      gp_Lin                      linsol;
      gp_Vec                      NormC1, NormC2;
      IntPatch_Point              aPtsol;
      occ::handle<IntPatch_GLine> glig;

      aPApex1 = Co1.Apex();
      aPApex2 = Co2.Apex();

      if (NbSol == 1)
      {
        IntSurf_Situation situC1, situC2;

        linsol = inter.Line(1);
        para   = ElCLib::Parameter(linsol, aPApex1);
        ptbid  = ElCLib::Value(para + 5., linsol);
        Quad1.Parameters(aPApex1, U1, V1);
        Quad2.Parameters(aPApex1, U2, V2);

        aPtsol.SetValue(aPApex1, Tol, false);
        aPtsol.SetParameters(U1, V1, U2, V2);
        aPtsol.SetParameter(para);

        NormC1 = Quad1.Normale(ptbid);
        NormC2 = Quad2.Normale(ptbid);
        aDot   = NormC1.Dot(NormC2);
        if (aDot < 0.)
        {
          situC1 = IntSurf_Outside;
          situC2 = IntSurf_Outside;
        }
        else
        {
          double aR1, aR2;
          gp_Lin aLAx1(aPApex1, Co1.Axis().Direction());
          gp_Lin aLAx2(aPApex2, Co2.Axis().Direction());

          aR1 = aLAx1.Distance(ptbid);
          aR2 = aLAx2.Distance(ptbid);

          situC1 = IntSurf_Inside;
          situC2 = IntSurf_Outside;
          if (aR1 > aR2)
          {

            situC1 = IntSurf_Outside;

            situC2 = IntSurf_Inside;
          }
        }

        glig = new IntPatch_GLine(linsol, true, situC1, situC2);
        glig->AddVertex(aPtsol);
        glig->SetFirstPoint(1);
        slin.Append(glig);

        linsol.SetDirection(linsol.Direction().Reversed());
        para = ElCLib::Parameter(linsol, aPApex1);
        aPtsol.SetParameter(para);

        glig = new IntPatch_GLine(linsol, true, situC2, situC1);
        glig->AddVertex(aPtsol);
        glig->SetFirstPoint(1);
        slin.Append(glig);
      }

      else if (NbSol == 2)
      {

        for (i = 1; i <= 2; ++i)
        {
          linsol = inter.Line(i);
          para   = ElCLib::Parameter(linsol, aPApex1);
          ptbid  = ElCLib::Value(para + 5., linsol);
          Quad1.Parameters(aPApex1, U1, V1);
          Quad2.Parameters(aPApex1, U2, V2);

          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
          if (linsol.Direction().DotCross(Quad2.Normale(ptbid), Quad1.Normale(ptbid)) > 0.)
          {
            trans1 = IntSurf_Out;
            trans2 = IntSurf_In;
          }

          Multpoint = true;

          aPtsol.SetValue(aPApex1, Tol, false);
          aPtsol.SetParameters(U1, V1, U2, V2);
          aPtsol.SetParameter(para);
          aPtsol.SetMultiple(true);

          glig = new IntPatch_GLine(linsol, false, trans1, trans2);
          glig->AddVertex(aPtsol);
          glig->SetFirstPoint(1);
          slin.Append(glig);

          linsol.SetDirection(linsol.Direction().Reversed());
          para = ElCLib::Parameter(linsol, aPApex1);
          aPtsol.SetParameter(para);
          glig = new IntPatch_GLine(linsol, false, trans1, trans2);
          glig->AddVertex(aPtsol);
          glig->SetFirstPoint(1);
          slin.Append(glig);
        }
      }
    }
    break;

    case IntAna_Point:
    {
      gp_Pnt ptcontact;
      gp_Pnt apex1(Co1.Apex());
      gp_Pnt apex2(Co2.Apex());
      double param1, param2;
      double paramapex1 = ElCLib::LineParameter(Co1.Axis(), apex1);
      double paramapex2 = ElCLib::LineParameter(Co2.Axis(), apex2);
      for (i = 1; i <= NbSol; i++)
      {
        ptcontact = inter.Point(i);
        param1    = ElCLib::LineParameter(Co1.Axis(), ptcontact);
        param2    = ElCLib::LineParameter(Co2.Axis(), ptcontact);

        Quad1.Parameters(ptcontact, U1, V1);
        Quad2.Parameters(ptcontact, U2, V2);

        if (apex1.Distance(ptcontact) <= Tol && apex2.Distance(ptcontact) <= Tol)
        {
          IntPatch_Point ptsol;
          ptsol.SetValue(ptcontact, Tol, false);
          ptsol.SetParameters(U1, V1, U2, V2);
          spnt.Append(ptsol);
        }
        else if (param1 >= paramapex1 && param2 >= paramapex2)
        {
          IntPatch_Point ptsol;
          ptsol.SetValue(ptcontact, Tol, true);
          ptsol.SetParameters(U1, V1, U2, V2);
          spnt.Append(ptsol);
        }
      }
    }
    break;

    case IntAna_Circle:
    {
      IntPatch_Point aPtsol;
      gp_Vec         Tgt;
      gp_Pnt         ptref;
      for (i = 1; i <= NbSol; i++)
      {
        gp_Circ cirsol = inter.Circle(i);
        ElCLib::D1(0., cirsol, ptref, Tgt);
        double qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
        if (qwe > 0.00000001)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe < -0.00000001)
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
        if (inter.HasCommonGen())
        {
          const gp_Pnt& aPChar = inter.PChar();
          Quad1.Parameters(aPChar, U1, V1);
          Quad2.Parameters(aPChar, U2, V2);
          aPtsol.SetValue(aPChar, Tol, false);
          aPtsol.SetParameters(U1, V1, U2, V2);
          aPtsol.SetParameter(0.);
          glig->AddVertex(aPtsol);
        }
        slin.Append(glig);
      }
    }
    break;

    case IntAna_Ellipse:
    {
      IntPatch_Point aPtsol;
      gp_Elips       elipsol = inter.Ellipse(1);

      gp_Vec Tgt;
      gp_Pnt ptref;
      ElCLib::D1(0., elipsol, ptref, Tgt);

      double qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
      if (qwe > 0.00000001)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else if (qwe < -0.00000001)
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      else
      {
        trans1 = trans2 = IntSurf_Undecided;
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(elipsol, false, trans1, trans2);
      if (inter.HasCommonGen())
      {
        const gp_Pnt& aPChar = inter.PChar();
        Quad1.Parameters(aPChar, U1, V1);
        Quad2.Parameters(aPChar, U2, V2);
        aPtsol.SetValue(aPChar, Tol, false);
        aPtsol.SetParameters(U1, V1, U2, V2);
        aPtsol.SetParameter(0.);
        glig->AddVertex(aPtsol);
      }
      slin.Append(glig);
    }
    break;

    case IntAna_Hyperbola:
    {
      IntPatch_Point aPtsol;
      gp_Vec         Tgt;
      gp_Pnt         ptref;
      for (i = 1; i <= 2; i++)
      {
        gp_Hypr hyprsol = inter.Hyperbola(i);
        ElCLib::D1(0., hyprsol, ptref, Tgt);
        double qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
        if (qwe > 0.00000001)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe < -0.00000001)
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(hyprsol, false, trans1, trans2);
        if (inter.HasCommonGen())
        {
          const gp_Pnt& aPChar = inter.PChar();
          Quad1.Parameters(aPChar, U1, V1);
          Quad2.Parameters(aPChar, U2, V2);
          aPtsol.SetValue(aPChar, Tol, false);
          aPtsol.SetParameters(U1, V1, U2, V2);
          aPtsol.SetParameter(0.);
          glig->AddVertex(aPtsol);
        }
        slin.Append(glig);
      }
    }
    break;

    case IntAna_Parabola:
    {
      IntPatch_Point aPtsol;
      gp_Parab       parabsol = inter.Parabola(1);

      gp_Vec Tgtorig(parabsol.YAxis().Direction());
      double ptran =
        Tgtorig.DotCross(Quad2.Normale(parabsol.Location()), Quad1.Normale(parabsol.Location()));
      if (ptran > 0.00000001)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else if (ptran < -0.00000001)
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      else
      {
        trans1 = trans2 = IntSurf_Undecided;
      }

      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(parabsol, false, trans1, trans2);
      if (inter.HasCommonGen())
      {
        const gp_Pnt& aPChar = inter.PChar();
        Quad1.Parameters(aPChar, U1, V1);
        Quad2.Parameters(aPChar, U2, V2);
        aPtsol.SetValue(aPChar, Tol, false);
        aPtsol.SetParameters(U1, V1, U2, V2);
        aPtsol.SetParameter(0.);
        glig->AddVertex(aPtsol);
      }
      slin.Append(glig);
    }
    break;

    case IntAna_NoGeometricSolution:
    {
      gp_Pnt             psol;
      IntAna_IntQuadQuad anaint(Co1, Co2, Tol);
      if (!anaint.IsDone())
      {
        return false;
      }

      if (anaint.NbPnt() == 0 && anaint.NbCurve() == 0)
      {
        Empty = true;
      }
      else
      {
        NbSol = anaint.NbPnt();
        for (i = 1; i <= NbSol; i++)
        {
          psol = anaint.Point(i);
          Quad1.Parameters(psol, U1, V1);
          Quad2.Parameters(psol, U2, V2);
          IntPatch_Point ptsol;
          ptsol.SetValue(psol, Tol, true);
          ptsol.SetParameters(U1, V1, U2, V2);
          spnt.Append(ptsol);
        }

        gp_Pnt ptvalid, ptf, ptl;
        gp_Vec tgvalid;

        double first, last, para;
        bool   tgfound, firstp, lastp, kept;
        int    kount;

        NbSol = anaint.NbCurve();
        for (i = 1; i <= NbSol; i++)
        {
          occ::handle<IntPatch_ALine> alig;
          kept                 = false;
          IntAna_Curve curvsol = anaint.Curve(i);
          curvsol.Domain(first, last);
          firstp = !curvsol.IsFirstOpen();
          lastp  = !curvsol.IsLastOpen();
          if (firstp)
          {
            ptf = curvsol.Value(first);
          }
          if (lastp)
          {
            ptl = curvsol.Value(last);
          }
          para    = last;
          kount   = 1;
          tgfound = false;

          while (!tgfound)
          {
            para    = (1.123 * first + para) / 2.123;
            tgfound = curvsol.D1u(para, ptvalid, tgvalid);
            if (tgvalid.SquareMagnitude() < 1e-14)
            {

              tgfound = false;
            }

            if (!tgfound)
            {
              kount++;
              tgfound = kount > 5;
            }
          }
          if (kount <= 5)
          {
            double qwe = tgvalid.DotCross(Quad2.Normale(ptvalid), Quad1.Normale(ptvalid));
            if (qwe > 0.000000001)
            {
              trans1 = IntSurf_Out;
              trans2 = IntSurf_In;
            }
            else if (qwe < -0.000000001)
            {
              trans1 = IntSurf_In;
              trans2 = IntSurf_Out;
            }
            else
            {
              trans1 = trans2 = IntSurf_Undecided;
            }
            alig = new IntPatch_ALine(curvsol, false, trans1, trans2);
            kept = true;
          }
          else
          {
            ptvalid = curvsol.Value(para);
            alig    = new IntPatch_ALine(curvsol, false);
            kept    = true;
          }
          if (kept)
          {
            bool Nfirstp = !firstp;
            bool Nlastp  = !lastp;
            ProcessBounds(alig,
                          slin,
                          Quad1,
                          Quad2,
                          Nfirstp,
                          ptf,
                          first,
                          Nlastp,
                          ptl,
                          last,
                          Multpoint,
                          Tol);
            slin.Append(alig);
          }
        }
      }
    }
    break;

    default:
    {
      return false;
    }
  }

  if (inter.HasCommonGen())
  {
    double         para;
    IntPatch_Point aPtsol;
    gp_Pnt         aPApex1, aPApex2;
    aPApex1 = Co1.Apex();
    aPApex2 = Co2.Apex();

    gce_MakeLin                 aMkLin(aPApex1, aPApex2);
    const gp_Lin&               linsol = aMkLin.Value();
    occ::handle<IntPatch_GLine> glig =
      new IntPatch_GLine(linsol, true, IntSurf_Undecided, IntSurf_Undecided);

    const gp_Pnt& aPChar = inter.PChar();
    Quad1.Parameters(aPChar, U1, V1);
    Quad2.Parameters(aPChar, U2, V2);
    aPtsol.SetValue(aPChar, Tol, false);
    aPtsol.SetParameters(U1, V1, U2, V2);
    para = ElCLib::Parameter(linsol, aPChar);
    aPtsol.SetParameter(para);
    glig->AddVertex(aPtsol);

    slin.Append(glig);
  }

  return true;
}

bool IntCoSp(const IntSurf_Quadric&                            Quad1,
             const IntSurf_Quadric&                            Quad2,
             const double                                      Tol,
             const bool                                        Reversed,
             bool&                                             Empty,
             bool&                                             Multpoint,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
             NCollection_Sequence<IntPatch_Point>&             spnt)

{
  int i;

  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;

  gp_Sphere Sp;
  gp_Cone   Co;
  double    U1, V1, U2, V2;

  if (!Reversed)
  {
    Co = Quad1.Cone();
    Sp = Quad2.Sphere();
  }
  else
  {
    Co = Quad2.Cone();
    Sp = Quad1.Sphere();
  }
  IntAna_QuadQuadGeo inter(Sp, Co, Tol);

  if (!inter.IsDone())
  {
    return false;
  }

  typint    = inter.TypeInter();
  int NbSol = inter.NbSolutions();
  Empty     = false;

  switch (typint)
  {
    case IntAna_Empty:
    {
      Empty = true;
    }
    break;

    case IntAna_Point:
    {
      gp_Pnt ptcontact;
      gp_Pnt apex(Co.Apex());
      double param;
      double paramapex = ElCLib::LineParameter(Co.Axis(), apex);
      for (i = 1; i <= NbSol; i++)
      {
        ptcontact = inter.Point(i);
        param     = ElCLib::LineParameter(Co.Axis(), ptcontact);
        Quad1.Parameters(ptcontact, U1, V1);
        Quad2.Parameters(ptcontact, U2, V2);

        if (apex.Distance(ptcontact) <= Tol)
        {
          IntPatch_Point ptsol;
          ptsol.SetValue(ptcontact, Tol, false);
          ptsol.SetParameters(U1, V1, U2, V2);
          spnt.Append(ptsol);
        }
        else if (param >= paramapex)
        {
          IntPatch_Point ptsol;
          ptsol.SetValue(ptcontact, Tol, true);
          ptsol.SetParameters(U1, V1, U2, V2);
          spnt.Append(ptsol);
        }
      }
    }
    break;

    case IntAna_Circle:
    {
      gp_Vec Tgt;
      gp_Pnt ptref;

      for (i = 1; i <= NbSol; i++)
      {
        gp_Circ cirsol = inter.Circle(i);

        ElCLib::D1(0., cirsol, ptref, Tgt);
        double qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
        if (qwe > 0.00000001)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe < -0.00000001)
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
        slin.Append(glig);
      }
    }
    break;

    case IntAna_PointAndCircle:
    {
      gp_Vec Tgt;
      gp_Pnt ptref;
      gp_Pnt apex(Co.Apex());
      double param;
      double paramapex = ElCLib::LineParameter(Co.Axis(), apex);

      Quad1.Parameters(apex, U1, V1);
      Quad2.Parameters(apex, U2, V2);
      IntPatch_Point ptsol;
      ptsol.SetValue(apex, Tol, false);
      ptsol.SetParameters(U1, V1, U2, V2);
      spnt.Append(ptsol);

      gp_Circ cirsol = inter.Circle(1);
      param          = ElCLib::LineParameter(Co.Axis(), cirsol.Location());
      ElCLib::D1(0., cirsol, ptref, Tgt);
      double qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));

      if (param >= paramapex)
      {
        if (qwe > Precision::PConfusion())
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe < -Precision::PConfusion())
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
      }
      else
      {
        if (qwe < -Precision::PConfusion())
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe > Precision::PConfusion())
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
      slin.Append(glig);
    }
    break;

    case IntAna_NoGeometricSolution:
    {
      gp_Pnt             psol;
      IntAna_IntQuadQuad anaint(Co, Sp, Tol);
      if (!anaint.IsDone())
      {
        return false;
      }

      if (anaint.NbPnt() == 0 && anaint.NbCurve() == 0)
      {
        Empty = true;
      }
      else
      {
        NbSol = anaint.NbPnt();
        for (i = 1; i <= NbSol; i++)
        {
          psol = anaint.Point(i);
          Quad1.Parameters(psol, U1, V1);
          Quad2.Parameters(psol, U2, V2);
          IntPatch_Point ptsol;
          ptsol.SetValue(psol, Tol, true);
          ptsol.SetParameters(U1, V1, U2, V2);
          spnt.Append(ptsol);
        }

        gp_Pnt ptvalid, ptf, ptl;
        gp_Vec tgvalid;
        double first, last, para;
        bool   tgfound, firstp, lastp, kept;
        int    kount;

        NbSol = anaint.NbCurve();
        for (i = 1; i <= NbSol; i++)
        {
          occ::handle<IntPatch_ALine> alig;
          kept                 = false;
          IntAna_Curve curvsol = anaint.Curve(i);
          curvsol.Domain(first, last);
          firstp = !curvsol.IsFirstOpen();
          lastp  = !curvsol.IsLastOpen();
          if (firstp)
          {
            ptf = curvsol.Value(first);
          }
          if (lastp)
          {
            ptl = curvsol.Value(last);
          }
          para    = last;
          kount   = 1;
          tgfound = false;

          while (!tgfound)
          {
            para    = (1.123 * first + para) / 2.123;
            tgfound = curvsol.D1u(para, ptvalid, tgvalid);
            if (!tgfound)
            {
              kount++;
              tgfound = kount > 5;
            }
          }
          if (kount <= 5)
          {
            para       = ElCLib::LineParameter(Co.Axis(), ptvalid);
            double qwe = tgvalid.DotCross(Quad2.Normale(ptvalid), Quad1.Normale(ptvalid));
            if (qwe > 0.000000001)
            {
              trans1 = IntSurf_Out;
              trans2 = IntSurf_In;
            }
            else if (qwe < -0.000000001)
            {
              trans1 = IntSurf_In;
              trans2 = IntSurf_Out;
            }
            else
            {
              trans1 = trans2 = IntSurf_Undecided;
            }
            alig = new IntPatch_ALine(curvsol, false, trans1, trans2);
            kept = true;
          }
          else
          {
            ptvalid = curvsol.Value(para);
            para    = ElCLib::LineParameter(Co.Axis(), ptvalid);
            alig    = new IntPatch_ALine(curvsol, false);
            kept    = true;
          }
          if (kept)
          {
            bool Nfirstp = !firstp;
            bool Nlastp  = !lastp;
            ProcessBounds(alig,
                          slin,
                          Quad1,
                          Quad2,
                          Nfirstp,
                          ptf,
                          first,
                          Nlastp,
                          ptl,
                          last,
                          Multpoint,
                          Tol);
            slin.Append(alig);
          }
        }
      }
    }
    break;

    default:
    {
      return false;
    }
  }

  return true;
}

bool IntSpSp(const IntSurf_Quadric&                            Quad1,
             const IntSurf_Quadric&                            Quad2,
             const double                                      Tol,
             bool&                                             Empty,
             bool&                                             Same,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& slin,
             NCollection_Sequence<IntPatch_Point>&             spnt)

{
  IntSurf_TypeTrans trans1, trans2;
  IntAna_ResultType typint;
  gp_Sphere         sph1(Quad1.Sphere());
  gp_Sphere         sph2(Quad2.Sphere());

  IntAna_QuadQuadGeo inter(sph1, sph2, Tol);
  if (!inter.IsDone())
  {
    return false;
  }

  typint = inter.TypeInter();
  Empty  = false;
  Same   = false;

  switch (typint)
  {
    case IntAna_Empty:
    {
      Empty = true;
    }
    break;

    case IntAna_Same:
    {
      Same = true;
    }
    break;

    case IntAna_Point:
    {
      gp_Pnt psol(inter.Point(1));
      double U1, V1, U2, V2;
      Quad1.Parameters(psol, U1, V1);
      Quad2.Parameters(psol, U2, V2);
      IntPatch_Point ptsol;
      ptsol.SetValue(psol, Tol, true);
      ptsol.SetParameters(U1, V1, U2, V2);
      spnt.Append(ptsol);
    }
    break;

    case IntAna_Circle:
    {
      gp_Circ cirsol = inter.Circle(1);
      gp_Pnt  ptref;
      gp_Vec  Tgt;
      ElCLib::D1(0., cirsol, ptref, Tgt);

      double qwe = Tgt.DotCross(Quad2.Normale(ptref), Quad1.Normale(ptref));
      if (qwe > 0.00000001)
      {
        trans1 = IntSurf_Out;
        trans2 = IntSurf_In;
      }
      else if (qwe < -0.00000001)
      {
        trans1 = IntSurf_In;
        trans2 = IntSurf_Out;
      }
      else
      {
        trans1 = trans2 = IntSurf_Undecided;
      }
      occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(cirsol, false, trans1, trans2);
      slin.Append(glig);
    }
    break;

    default:
    {
      return false;
    }
  }
  return true;
}

static bool TreatResultTorus(const IntSurf_Quadric&                            theQuad1,
                             const IntSurf_Quadric&                            theQuad2,
                             const IntAna_QuadQuadGeo&                         anInt,
                             bool&                                             bEmpty,
                             NCollection_Sequence<occ::handle<IntPatch_Line>>& theSeqLin);

bool IntCyTo(const IntSurf_Quadric&                            theQuad1,
             const IntSurf_Quadric&                            theQuad2,
             const double                                      theTolTang,
             const bool                                        bReversed,
             bool&                                             bEmpty,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& theSeqLin)
{
  const gp_Cylinder aCyl   = bReversed ? theQuad2.Cylinder() : theQuad1.Cylinder();
  const gp_Torus    aTorus = bReversed ? theQuad1.Torus() : theQuad2.Torus();

  IntAna_QuadQuadGeo anInt(aCyl, aTorus, theTolTang);
  bool               bRet = TreatResultTorus(theQuad1, theQuad2, anInt, bEmpty, theSeqLin);

  return bRet;
}

bool IntCoTo(const IntSurf_Quadric&                            theQuad1,
             const IntSurf_Quadric&                            theQuad2,
             const double                                      theTolTang,
             const bool                                        bReversed,
             bool&                                             bEmpty,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& theSeqLin)
{
  const gp_Cone  aCone  = bReversed ? theQuad2.Cone() : theQuad1.Cone();
  const gp_Torus aTorus = bReversed ? theQuad1.Torus() : theQuad2.Torus();

  IntAna_QuadQuadGeo anInt(aCone, aTorus, theTolTang);
  bool               bRet = TreatResultTorus(theQuad1, theQuad2, anInt, bEmpty, theSeqLin);

  return bRet;
}

bool IntSpTo(const IntSurf_Quadric&                            theQuad1,
             const IntSurf_Quadric&                            theQuad2,
             const double                                      theTolTang,
             const bool                                        bReversed,
             bool&                                             bEmpty,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& theSeqLin)
{
  const gp_Sphere aSphere = bReversed ? theQuad2.Sphere() : theQuad1.Sphere();
  const gp_Torus  aTorus  = bReversed ? theQuad1.Torus() : theQuad2.Torus();

  IntAna_QuadQuadGeo anInt(aSphere, aTorus, theTolTang);
  bool               bRet = TreatResultTorus(theQuad1, theQuad2, anInt, bEmpty, theSeqLin);

  return bRet;
}

bool IntToTo(const IntSurf_Quadric&                            theQuad1,
             const IntSurf_Quadric&                            theQuad2,
             const double                                      theTolTang,
             bool&                                             bSameSurf,
             bool&                                             bEmpty,
             NCollection_Sequence<occ::handle<IntPatch_Line>>& theSeqLin)
{
  const gp_Torus aTorus1 = theQuad1.Torus();
  const gp_Torus aTorus2 = theQuad2.Torus();

  IntAna_QuadQuadGeo anInt(aTorus1, aTorus2, theTolTang);
  bool               bRet = anInt.IsDone();
  if (bRet)
  {
    if (anInt.TypeInter() == IntAna_Same)
    {
      bEmpty    = false;
      bSameSurf = true;
    }
    else
    {
      bRet = TreatResultTorus(theQuad1, theQuad2, anInt, bEmpty, theSeqLin);
    }
  }

  return bRet;
}

static bool TreatResultTorus(const IntSurf_Quadric&                            theQuad1,
                             const IntSurf_Quadric&                            theQuad2,
                             const IntAna_QuadQuadGeo&                         anInt,
                             bool&                                             bEmpty,
                             NCollection_Sequence<occ::handle<IntPatch_Line>>& theSeqLin)
{
  bool bRet = anInt.IsDone();

  if (!bRet)
  {
    return bRet;
  }

  IntAna_ResultType typint = anInt.TypeInter();
  int               NbSol  = anInt.NbSolutions();
  bEmpty                   = false;

  switch (typint)
  {
    case IntAna_Empty:
      bEmpty = true;
      break;

    case IntAna_Circle:
    {
      int               i;
      IntSurf_TypeTrans trans1, trans2;
      gp_Vec            Tgt;
      gp_Pnt            ptref;

      for (i = 1; i <= NbSol; ++i)
      {
        gp_Circ aC = anInt.Circle(i);
        if (theQuad1.TypeQuadric() == theQuad2.TypeQuadric())
        {
          AdjustToSeam(theQuad1.Torus(), aC);
        }
        ElCLib::D1(0., aC, ptref, Tgt);
        double qwe = Tgt.DotCross(theQuad2.Normale(ptref), theQuad1.Normale(ptref));
        if (qwe > 0.00000001)
        {
          trans1 = IntSurf_Out;
          trans2 = IntSurf_In;
        }
        else if (qwe < -0.00000001)
        {
          trans1 = IntSurf_In;
          trans2 = IntSurf_Out;
        }
        else
        {
          trans1 = trans2 = IntSurf_Undecided;
        }

        occ::handle<IntPatch_GLine> glig = new IntPatch_GLine(aC, false, trans1, trans2);
        theSeqLin.Append(glig);
      }
    }
    break;

    case IntAna_NoGeometricSolution:
    default:
      bRet = false;
      break;
  }

  return bRet;
}
