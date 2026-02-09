

#include <Adaptor2d_OffsetCurve.hpp>
#include <ElCLib.hpp>
#include <GccEnt_BadQualifier.hpp>
#include <GccEnt_QualifiedCirc.hpp>
#include <GccEnt_QualifiedLin.hpp>
#include <Geom2dGcc_Circ2d2TanRadGeo.hpp>
#include <Geom2dGcc_CurveTool.hpp>
#include <Geom2dGcc_QCurve.hpp>
#include <Geom2dInt_GInter.hpp>
#include <gp_Ax2d.hpp>
#include <gp_Circ2d.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Pnt2d.hpp>
#include <IntRes2d_Domain.hpp>
#include <IntRes2d_IntersectionPoint.hpp>
#include <Standard_NegativeValue.hpp>
#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <NCollection_Array1.hpp>

static const int aNbSolMAX = 16;

Geom2dGcc_Circ2d2TanRadGeo::Geom2dGcc_Circ2d2TanRadGeo(const GccEnt_QualifiedLin& Qualified1,
                                                       const Geom2dGcc_QCurve&    Qualified2,
                                                       const double               Radius,
                                                       const double               Tolerance)
    :

      cirsol(1, aNbSolMAX),
      qualifier1(1, aNbSolMAX),
      qualifier2(1, aNbSolMAX),
      TheSame1(1, aNbSolMAX),
      TheSame2(1, aNbSolMAX),
      pnttg1sol(1, aNbSolMAX),
      pnttg2sol(1, aNbSolMAX),
      par1sol(1, aNbSolMAX),
      par2sol(1, aNbSolMAX),
      pararg1(1, aNbSolMAX),
      pararg2(1, aNbSolMAX)
{

  double                     Tol      = std::abs(Tolerance);
  double                     thefirst = -100000.;
  double                     thelast  = 100000.;
  double                     firstparam;
  double                     lastparam;
  gp_Dir2d                   dirx(gp_Dir2d::D::X);
  NCollection_Array1<double> cote1(1, 2);
  NCollection_Array1<double> cote2(1, 2);
  int                        nbrcote1 = 0;
  int                        nbrcote2 = 0;
  WellDone                            = false;
  NbrSol                              = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsOutside() || Qualified1.IsUnqualified())
      || !(Qualified2.IsEnclosed() || Qualified2.IsEnclosing() || Qualified2.IsOutside()
           || Qualified2.IsUnqualified()))
  {

    throw GccEnt_BadQualifier();
    return;
  }
  gp_Lin2d            L1    = Qualified1.Qualified();
  double              x1dir = (L1.Direction()).X();
  double              y1dir = (L1.Direction()).Y();
  double              lxloc = (L1.Location()).X();
  double              lyloc = (L1.Location()).Y();
  gp_Pnt2d            origin1(lxloc, lyloc);
  gp_Dir2d            normL1(-y1dir, x1dir);
  Geom2dAdaptor_Curve Cu2 = Qualified2.Qualified();
  if (Radius < 0.0)
  {
    throw Standard_NegativeValue();
  }
  else
  {
    if (Qualified1.IsEnclosed() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsEnclosed() && Qualified2.IsOutside())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote2(1) = -Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = -Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsOutside())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = -Radius;
      cote2(1) = -Radius;
    }
    if (Qualified1.IsEnclosed() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 1;
      nbrcote2 = 2;
      cote1(1) = Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    if (Qualified1.IsUnqualified() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 2;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 1;
      nbrcote2 = 2;
      cote1(1) = -Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    if (Qualified1.IsUnqualified() && Qualified2.IsOutside())
    {

      nbrcote1 = 2;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = -Radius;
    }
    else if (Qualified1.IsUnqualified() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 2;
      nbrcote2 = 2;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    gp_Dir2d Dir(-y1dir, x1dir);
    for (int jcote1 = 1; jcote1 <= nbrcote1; jcote1++)
    {
      gp_Pnt2d        Point(L1.Location().XY() + cote1(jcote1) * Dir.XY());
      gp_Lin2d        Line(Point, L1.Direction());
      IntRes2d_Domain D1;
      for (int jcote2 = 1; jcote2 <= nbrcote2 && NbrSol < aNbSolMAX; jcote2++)
      {
        occ::handle<Geom2dAdaptor_Curve> HCu2 = new Geom2dAdaptor_Curve(Cu2);

        Adaptor2d_OffsetCurve C2(HCu2, -cote2(jcote2));
        firstparam = std::max(C2.FirstParameter(), thefirst);
        lastparam  = std::min(C2.LastParameter(), thelast);
        IntRes2d_Domain                    D2(C2.Value(firstparam),
                           firstparam,
                           Tol,
                           C2.Value(lastparam),
                           lastparam,
                           Tol);
        Geom2dInt_TheIntConicCurveOfGInter Intp(Line, D1, C2, D2, Tol, Tol);
        if (Intp.IsDone())
        {
          if (!Intp.IsEmpty())
          {
            for (int i = 1; i <= Intp.NbPoints() && NbrSol < aNbSolMAX; i++)
            {
              NbrSol++;
              gp_Pnt2d Center(Intp.Point(i).Value());
              cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

              gp_Dir2d dc1(origin1.XY() - Center.XY());
              qualifier2(NbrSol) = Qualified2.Qualifier();
              if (!Qualified1.IsUnqualified())
              {
                qualifier1(NbrSol) = Qualified1.Qualifier();
              }
              else if (dc1.Dot(normL1) > 0.0)
              {
                qualifier1(NbrSol) = GccEnt_outside;
              }
              else
              {
                qualifier1(NbrSol) = GccEnt_enclosed;
              }
              TheSame1(NbrSol)  = 0;
              TheSame2(NbrSol)  = 0;
              pararg1(NbrSol)   = Intp.Point(i).ParamOnFirst();
              pararg2(NbrSol)   = Intp.Point(i).ParamOnSecond();
              pnttg1sol(NbrSol) = ElCLib::Value(pararg1(NbrSol), L1);
              pnttg2sol(NbrSol) = Geom2dGcc_CurveTool::Value(Cu2, pararg2(NbrSol));
              par1sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
              par2sol(NbrSol)   = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
            }
          }
          WellDone = true;
        }
      }
    }
  }
}

Geom2dGcc_Circ2d2TanRadGeo::Geom2dGcc_Circ2d2TanRadGeo(const GccEnt_QualifiedCirc& Qualified1,
                                                       const Geom2dGcc_QCurve&     Qualified2,
                                                       const double                Radius,
                                                       const double                Tolerance)
    :

      cirsol(1, aNbSolMAX),
      qualifier1(1, aNbSolMAX),
      qualifier2(1, aNbSolMAX),
      TheSame1(1, aNbSolMAX),
      TheSame2(1, aNbSolMAX),
      pnttg1sol(1, aNbSolMAX),
      pnttg2sol(1, aNbSolMAX),
      par1sol(1, aNbSolMAX),
      par2sol(1, aNbSolMAX),
      pararg1(1, aNbSolMAX),
      pararg2(1, aNbSolMAX)
{

  double                     Tol      = std::abs(Tolerance);
  double                     thefirst = -100000.;
  double                     thelast  = 100000.;
  double                     firstparam;
  double                     lastparam;
  gp_Dir2d                   dirx(gp_Dir2d::D::X);
  NCollection_Array1<double> cote1(1, 2);
  NCollection_Array1<double> cote2(1, 2);
  int                        nbrcote1 = 0;
  int                        nbrcote2 = 0;
  WellDone                            = false;
  NbrSol                              = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified())
      || !(Qualified2.IsEnclosed() || Qualified2.IsEnclosing() || Qualified2.IsOutside()
           || Qualified2.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  gp_Circ2d           C1 = Qualified1.Qualified();
  gp_Pnt2d            center1(C1.Location());
  Geom2dAdaptor_Curve Cu2 = Qualified2.Qualified();
  if (Radius < 0.0)
  {
    throw Standard_NegativeValue();
  }
  else
  {
    if (Qualified1.IsEnclosed() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsEnclosed() && Qualified2.IsOutside())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote2(1) = -Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = -Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsOutside())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = -Radius;
      cote2(1) = -Radius;
    }
    if (Qualified1.IsEnclosed() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 1;
      nbrcote2 = 2;
      cote1(1) = Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    if (Qualified1.IsUnqualified() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 2;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 1;
      nbrcote2 = 2;
      cote1(1) = -Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    if (Qualified1.IsUnqualified() && Qualified2.IsOutside())
    {

      nbrcote1 = 2;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = -Radius;
    }
    else if (Qualified1.IsUnqualified() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 2;
      nbrcote2 = 2;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    double                             R1 = C1.Radius();
    Geom2dInt_TheIntConicCurveOfGInter Intp;
    for (int jcote1 = 1; jcote1 <= nbrcote1 && NbrSol < aNbSolMAX; jcote1++)
    {
      gp_Circ2d       Circ(C1.XAxis(), R1 + cote1(jcote1));
      IntRes2d_Domain D1(ElCLib::Value(0., Circ),
                         0.,
                         Tol,
                         ElCLib::Value(2. * M_PI, Circ),
                         2. * M_PI,
                         Tol);
      D1.SetEquivalentParameters(0., 2. * M_PI);
      for (int jcote2 = 1; jcote2 <= nbrcote2; jcote2++)
      {
        occ::handle<Geom2dAdaptor_Curve> HCu2 = new Geom2dAdaptor_Curve(Cu2);

        Adaptor2d_OffsetCurve C2(HCu2, -cote2(jcote2));
        firstparam = std::max(C2.FirstParameter(), thefirst);
        lastparam  = std::min(C2.LastParameter(), thelast);
        IntRes2d_Domain D2(C2.Value(firstparam),
                           firstparam,
                           Tol,
                           C2.Value(lastparam),
                           lastparam,
                           Tol);
        Intp.Perform(Circ, D1, C2, D2, Tol, Tol);
        if (Intp.IsDone())
        {
          if (!Intp.IsEmpty())
          {
            for (int i = 1; i <= Intp.NbPoints() && NbrSol < aNbSolMAX; i++)
            {
              NbrSol++;
              gp_Pnt2d Center(Intp.Point(i).Value());
              cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

#ifdef OCCT_DEBUG
              gp_Dir2d dir1(Center.XY() - center1.XY());
#else
              Center.XY();
              center1.XY();
#endif
              double distcc1 = Center.Distance(center1);
              if (!Qualified1.IsUnqualified())
              {
                qualifier1(NbrSol) = Qualified1.Qualifier();
              }
              else if (std::abs(distcc1 + Radius - R1) < Tol)
              {
                qualifier1(NbrSol) = GccEnt_enclosed;
              }
              else if (std::abs(distcc1 - R1 - Radius) < Tol)
              {
                qualifier1(NbrSol) = GccEnt_outside;
              }
              else
              {
                qualifier1(NbrSol) = GccEnt_enclosing;
              }
              qualifier2(NbrSol) = Qualified2.Qualifier();
              TheSame1(NbrSol)   = 0;
              TheSame2(NbrSol)   = 0;
              pararg1(NbrSol)    = Intp.Point(i).ParamOnFirst();
              pararg2(NbrSol)    = Intp.Point(i).ParamOnSecond();
              pnttg1sol(NbrSol)  = ElCLib::Value(pararg1(NbrSol), C1);
              pnttg2sol(NbrSol)  = Geom2dGcc_CurveTool::Value(Cu2, pararg2(NbrSol));
              par1sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
              par2sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
            }
          }
          WellDone = true;
        }
      }
    }
  }
}

Geom2dGcc_Circ2d2TanRadGeo::Geom2dGcc_Circ2d2TanRadGeo(const Geom2dGcc_QCurve& Qualified1,
                                                       const gp_Pnt2d&         Point2,
                                                       const double            Radius,
                                                       const double            Tolerance)
    :

      cirsol(1, aNbSolMAX),
      qualifier1(1, aNbSolMAX),
      qualifier2(1, aNbSolMAX),
      TheSame1(1, aNbSolMAX),
      TheSame2(1, aNbSolMAX),
      pnttg1sol(1, aNbSolMAX),
      pnttg2sol(1, aNbSolMAX),
      par1sol(1, aNbSolMAX),
      par2sol(1, aNbSolMAX),
      pararg1(1, aNbSolMAX),
      pararg2(1, aNbSolMAX)
{

  double                     Tol      = std::abs(Tolerance);
  double                     thefirst = -100000.;
  double                     thelast  = 100000.;
  double                     firstparam;
  double                     lastparam;
  gp_Dir2d                   dirx(gp_Dir2d::D::X);
  NCollection_Array1<double> cote1(1, 2);
  int                        nbrcote1 = 0;
  WellDone                            = false;
  NbrSol                              = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  Geom2dAdaptor_Curve Cu1 = Qualified1.Qualified();
  if (Radius < 0.0)
  {
    throw Standard_NegativeValue();
  }
  else
  {
    if (Qualified1.IsEnclosed())
    {

      nbrcote1 = 1;
      cote1(1) = Radius;
    }
    else if (Qualified1.IsOutside())
    {

      nbrcote1 = 1;
      cote1(1) = -Radius;
    }
    else if (Qualified1.IsUnqualified())
    {

      nbrcote1 = 2;
      cote1(1) = Radius;
      cote1(2) = -Radius;
    }
    gp_Circ2d       Circ(gp_Ax2d(Point2, gp_Dir2d(gp_Dir2d::D::X)), Radius);
    IntRes2d_Domain D1(ElCLib::Value(0., Circ),
                       0.,
                       Tol,
                       ElCLib::Value(M_PI + M_PI, Circ),
                       M_PI + M_PI,
                       Tol);
    D1.SetEquivalentParameters(0., M_PI + M_PI);
    Geom2dInt_TheIntConicCurveOfGInter Intp;
    for (int jcote1 = 1; jcote1 <= nbrcote1 && NbrSol < aNbSolMAX; jcote1++)
    {
      occ::handle<Geom2dAdaptor_Curve> HCu1 = new Geom2dAdaptor_Curve(Cu1);

      Adaptor2d_OffsetCurve Cu2(HCu1, -cote1(jcote1));
      firstparam = std::max(Cu2.FirstParameter(), thefirst);
      lastparam  = std::min(Cu2.LastParameter(), thelast);
      IntRes2d_Domain D2(Cu2.Value(firstparam),
                         firstparam,
                         Tol,
                         Cu2.Value(lastparam),
                         lastparam,
                         Tol);
      Intp.Perform(Circ, D1, Cu2, D2, Tol, Tol);
      if (Intp.IsDone())
      {
        if (!Intp.IsEmpty())
        {
          for (int i = 1; i <= Intp.NbPoints() && NbrSol < aNbSolMAX; i++)
          {
            NbrSol++;
            gp_Pnt2d Center(Intp.Point(i).Value());
            cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

            qualifier1(NbrSol) = Qualified1.Qualifier();
            qualifier2(NbrSol) = GccEnt_noqualifier;
            TheSame1(NbrSol)   = 0;
            TheSame2(NbrSol)   = 0;
            pararg1(NbrSol)    = Intp.Point(i).ParamOnSecond();
            pararg2(NbrSol)    = 0.;
            pnttg1sol(NbrSol)  = Geom2dGcc_CurveTool::Value(Cu1, pararg1(NbrSol));
            pnttg2sol(NbrSol)  = Point2;
            par1sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
            par2sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
          }
        }
        WellDone = true;
      }
    }
  }
}

static void PrecRoot(const Adaptor2d_OffsetCurve& theC1,
                     const Adaptor2d_OffsetCurve& theC2,
                     const double                 theU0,
                     const double                 theV0,
                     double&                      theUfinal,
                     double&                      theVfinal)
{

  theUfinal = theU0;
  theVfinal = theV0;

  const int aNbIterMax = 100;

  double   aU = theU0, aV = theV0;
  gp_Pnt2d aPu, aPv;
  gp_Vec2d aD1u, aD1v, aD2u, aD2v;

  int aNbIter = 0;

  double aStepU = 0.0, aStepV = 0.0;

  double aSQDistPrev = RealFirst();

  theC1.D2(aU, aPu, aD1u, aD2u);
  theC2.D2(aV, aPv, aD1v, aD2v);

  const double aCrProd = std::abs(aD1u.Crossed(aD1v));
  if (aCrProd * aCrProd > 1.0e-6 * aD1u.SquareMagnitude() * aD1v.SquareMagnitude())
  {

    return;
  }

  do
  {
    aNbIter++;

    gp_Vec2d aVuv(aPv, aPu);

    double aSQDist = aVuv.SquareMagnitude();
    if (IsEqual(aSQDist, 0.0))
      break;

    if ((aNbIter == 1) || (aSQDist < aSQDistPrev))
    {
      aSQDistPrev = aSQDist;
      theUfinal   = aU;
      theVfinal   = aV;
    }

    double aG1 = aD1u.Magnitude();
    double aG2 = aD1v.Magnitude();

    if (IsEqual(aG1, 0.0) || IsEqual(aG2, 0.0))
    {
      break;
    }

    double aF1 = aVuv.Dot(aD1u);
    double aF2 = aVuv.Dot(aD1v);

    double aFIu  = aVuv.Dot(aD2u);
    double aFIv  = aVuv.Dot(aD2v);
    double aPSIu = aD1u.Dot(aD2u);
    double aPSIv = aD1v.Dot(aD2v);

    double aTheta = aD1u * aD1v;

    double aS1 = aF1 / aG1;
    double aS2 = aF2 / aG2;

    double aDS1u = (aG1 * aG1 + aFIu) / aG1 - (aS1 * aPSIu / (aG1 * aG1));
    double aDS1v = -aTheta / aG1;
    double aDS2u = aTheta / aG2;
    double aDS2v = (aFIv - aG2 * aG2) / aG2 - (aS2 * aPSIv / (aG2 * aG2));

    double aDet = aDS1u * aDS2v - aDS1v * aDS2u;

    if (IsEqual(aDet, 0.0))
    {
      if (!IsEqual(aStepV, 0.0) && !IsEqual(aDS1u, 0.0))
      {
        aV += aStepV;
        aU = aU - (aDS1v * aStepV - aS1) / aDS1u;
      }
      else if (!IsEqual(aStepU, 0.0) && !IsEqual(aDS1v, 0.0))
      {
        aU += aStepU;
        aV = aV - (aDS1u * aStepU - aS1) / aDS1v;
      }
      else
      {
        break;
      }
    }
    else
    {
      aStepU = -(aS1 * aDS2v - aS2 * aDS1v) / aDet;
      aStepV = -(aS2 * aDS1u - aS1 * aDS2u) / aDet;

      if (std::abs(aStepU) < Epsilon(std::abs(aU)))
      {
        if (std::abs(aStepV) < Epsilon(std::abs(aV)))
        {
          break;
        }
      }

      aU += aStepU;
      aV += aStepV;
    }

    theC1.D2(aU, aPu, aD1u, aD2u);
    theC2.D2(aV, aPv, aD1v, aD2v);
  } while (aNbIter <= aNbIterMax);
}

Geom2dGcc_Circ2d2TanRadGeo::Geom2dGcc_Circ2d2TanRadGeo(const Geom2dGcc_QCurve& Qualified1,
                                                       const Geom2dGcc_QCurve& Qualified2,
                                                       const double            Radius,
                                                       const double            Tolerance)
    :

      cirsol(1, aNbSolMAX),
      qualifier1(1, aNbSolMAX),
      qualifier2(1, aNbSolMAX),
      TheSame1(1, aNbSolMAX),
      TheSame2(1, aNbSolMAX),
      pnttg1sol(1, aNbSolMAX),
      pnttg2sol(1, aNbSolMAX),
      par1sol(1, aNbSolMAX),
      par2sol(1, aNbSolMAX),
      pararg1(1, aNbSolMAX),
      pararg2(1, aNbSolMAX)
{

  double Tol = std::abs(Tolerance);
#ifdef OCCT_DEBUG
  const double thefirst = -100000.;
  const double thelast  = 100000.;
#endif
  gp_Dir2d                   dirx(gp_Dir2d::D::X);
  NCollection_Array1<double> cote1(1, 2);
  NCollection_Array1<double> cote2(1, 2);
  int                        nbrcote1 = 0;
  int                        nbrcote2 = 0;
  WellDone                            = false;
  NbrSol                              = 0;
  if (!(Qualified1.IsEnclosed() || Qualified1.IsEnclosing() || Qualified1.IsOutside()
        || Qualified1.IsUnqualified())
      || !(Qualified2.IsEnclosed() || Qualified2.IsEnclosing() || Qualified2.IsOutside()
           || Qualified2.IsUnqualified()))
  {
    throw GccEnt_BadQualifier();
    return;
  }
  Geom2dAdaptor_Curve Cu1 = Qualified1.Qualified();
  Geom2dAdaptor_Curve Cu2 = Qualified2.Qualified();
  if (Radius < 0.0)
  {
    throw Standard_NegativeValue();
  }
  else
  {
    if (Qualified1.IsEnclosed() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsEnclosed() && Qualified2.IsOutside())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote2(1) = -Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = -Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsOutside())
    {

      nbrcote1 = 1;
      nbrcote2 = 1;
      cote1(1) = -Radius;
      cote2(1) = -Radius;
    }
    if (Qualified1.IsEnclosed() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 1;
      nbrcote2 = 2;
      cote1(1) = Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    if (Qualified1.IsUnqualified() && Qualified2.IsEnclosed())
    {

      nbrcote1 = 2;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = Radius;
    }
    else if (Qualified1.IsOutside() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 1;
      nbrcote2 = 2;
      cote1(1) = -Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    if (Qualified1.IsUnqualified() && Qualified2.IsOutside())
    {

      nbrcote1 = 2;
      nbrcote2 = 1;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = -Radius;
    }
    else if (Qualified1.IsUnqualified() && Qualified2.IsUnqualified())
    {

      nbrcote1 = 2;
      nbrcote2 = 2;
      cote1(1) = Radius;
      cote1(2) = -Radius;
      cote2(1) = Radius;
      cote2(2) = -Radius;
    }
    Geom2dInt_GInter Intp;
    for (int jcote1 = 1; jcote1 <= nbrcote1; jcote1++)
    {
      occ::handle<Geom2dAdaptor_Curve> HCu1 = new Geom2dAdaptor_Curve(Cu1);

      Adaptor2d_OffsetCurve C1(HCu1, -cote1(jcote1));
#ifdef OCCT_DEBUG
      double          firstparam = std::max(C1.FirstParameter(), thefirst);
      double          lastparam  = std::min(C1.LastParameter(), thelast);
      IntRes2d_Domain D2C1(C1.Value(firstparam),
                           firstparam,
                           Tol,
                           C1.Value(lastparam),
                           lastparam,
                           Tol);
#endif
      for (int jcote2 = 1; jcote2 <= nbrcote2 && NbrSol < aNbSolMAX; jcote2++)
      {
        occ::handle<Geom2dAdaptor_Curve> HCu2 = new Geom2dAdaptor_Curve(Cu2);

        Adaptor2d_OffsetCurve C2(HCu2, -cote2(jcote2));
#ifdef OCCT_DEBUG
        firstparam = std::max(C2.FirstParameter(), thefirst);
        lastparam  = std::min(C2.LastParameter(), thelast);
        IntRes2d_Domain D2C2(C2.Value(firstparam),
                             firstparam,
                             Tol,
                             C2.Value(lastparam),
                             lastparam,
                             Tol);
#endif
        Intp.Perform(C1, C2, Tol, Tol);
        if (Intp.IsDone())
        {
          if (!Intp.IsEmpty())
          {
            constexpr double aSQApproxTol = Precision::Approximation() * Precision::Approximation();
            for (int i = 1; i <= Intp.NbPoints() && NbrSol < aNbSolMAX; i++)
            {
              double aU0 = Intp.Point(i).ParamOnFirst();
              double aV0 = Intp.Point(i).ParamOnSecond();

              double aU1 = aU0 - Precision::PApproximation();
              double aV1 = aV0 - Precision::PApproximation();

              double aU2 = aU0 + Precision::PApproximation();
              double aV2 = aV0 + Precision::PApproximation();

              gp_Pnt2d P11 = C1.Value(aU1);
              gp_Pnt2d P12 = C2.Value(aV1);
              gp_Pnt2d P21 = C1.Value(aU2);
              gp_Pnt2d P22 = C2.Value(aV2);

              double aDist1112 = P11.SquareDistance(P12);
              double aDist1122 = P11.SquareDistance(P22);

              double aDist1221 = P12.SquareDistance(P21);
              double aDist2122 = P21.SquareDistance(P22);

              if ((std::min(aDist1112, aDist1122) <= aSQApproxTol)
                  && (std::min(aDist1221, aDist2122) <= aSQApproxTol))
              {
                PrecRoot(C1, C2, aU0, aV0, aU0, aV0);
              }

              NbrSol++;
              gp_Pnt2d Center(C1.Value(aU0));
              cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center, dirx), Radius);

              qualifier1(NbrSol) = Qualified1.Qualifier();
              qualifier1(NbrSol) = Qualified1.Qualifier();
              TheSame1(NbrSol)   = 0;
              TheSame2(NbrSol)   = 0;
              pararg1(NbrSol)    = Intp.Point(i).ParamOnFirst();
              pararg2(NbrSol)    = Intp.Point(i).ParamOnSecond();
              pnttg1sol(NbrSol)  = Geom2dGcc_CurveTool::Value(Cu1, pararg1(NbrSol));
              pnttg2sol(NbrSol)  = Geom2dGcc_CurveTool::Value(Cu2, pararg2(NbrSol));
              par1sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg1sol(NbrSol));
              par2sol(NbrSol)    = ElCLib::Parameter(cirsol(NbrSol), pnttg2sol(NbrSol));
            }
          }

          WellDone = true;
        }
      }
    }
  }
}

bool Geom2dGcc_Circ2d2TanRadGeo::IsDone() const
{
  return WellDone;
}

int Geom2dGcc_Circ2d2TanRadGeo::NbSolutions() const
{
  return NbrSol;
}

gp_Circ2d Geom2dGcc_Circ2d2TanRadGeo::ThisSolution(const int Index) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  return cirsol(Index);
}

void Geom2dGcc_Circ2d2TanRadGeo::WhichQualifier(const int        Index,
                                                GccEnt_Position& Qualif1,
                                                GccEnt_Position& Qualif2) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    Qualif1 = qualifier1(Index);
    Qualif2 = qualifier2(Index);
  }
}

void Geom2dGcc_Circ2d2TanRadGeo::Tangency1(const int Index,
                                           double&   ParSol,
                                           double&   ParArg,
                                           gp_Pnt2d& PntSol) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    if (TheSame1(Index) == 0)
    {
      ParSol = par1sol(Index);
      ParArg = pararg1(Index);
      PntSol = gp_Pnt2d(pnttg1sol(Index));
    }
    else
    {
      throw StdFail_NotDone();
    }
  }
}

void Geom2dGcc_Circ2d2TanRadGeo::Tangency2(const int Index,
                                           double&   ParSol,
                                           double&   ParArg,
                                           gp_Pnt2d& PntSol) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  else if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }
  else
  {
    if (TheSame2(Index) == 0)
    {
      ParSol = par2sol(Index);
      ParArg = pararg2(Index);
      PntSol = gp_Pnt2d(pnttg2sol(Index));
    }
    else
    {
      throw StdFail_NotDone();
    }
  }
}

bool Geom2dGcc_Circ2d2TanRadGeo::IsTheSame1(const int Index) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }

  if (TheSame1(Index) == 0)
  {
    return false;
  }
  return true;
}

bool Geom2dGcc_Circ2d2TanRadGeo::IsTheSame2(const int Index) const
{
  if (!WellDone)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > NbrSol)
  {
    throw Standard_OutOfRange();
  }

  if (TheSame2(Index) == 0)
  {
    return false;
  }
  return true;
}
