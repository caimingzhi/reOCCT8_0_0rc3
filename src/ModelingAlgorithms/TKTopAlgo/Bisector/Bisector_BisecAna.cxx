#include <Bisector_BisecAna.hpp>
#include <ElCLib.hpp>
#include <GccAna_Circ2dBisec.hpp>
#include <GccAna_CircLin2dBisec.hpp>
#include <GccAna_CircPnt2dBisec.hpp>
#include <GccAna_LinPnt2dBisec.hpp>
#include <GccAna_Pnt2dBisec.hpp>
#include <GccInt_BLine.hpp>
#include <GccInt_IType.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Geometry.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_Line.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_Point.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Trsf2d.hpp>
#include <gp_Vec2d.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <StdFail_NotDone.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Bisector_BisecAna, Bisector_Curve)

static bool Degenerate(occ::handle<GccInt_Bisec>& aBisector, const double Tolerance);

Bisector_BisecAna::Bisector_BisecAna() = default;

double Bisector_BisecAna::Distance(const gp_Pnt2d&                  apoint,
                                   const occ::handle<GccInt_Bisec>& abisector,
                                   const gp_Vec2d&                  afirstvector,
                                   const gp_Vec2d&                  asecondvector,
                                   const gp_Vec2d&                  VecRef,
                                   const double                     adirection,
                                   double&                          aparameter,
                                   bool&                            asense,
                                   bool&                            astatus,
                                   bool                             IsBisecOfTwoLines)
{
  astatus = true;

  gp_Hypr2d  gphyperbola;
  gp_Parab2d gpparabola;
  gp_Elips2d gpellipse;
  gp_Circ2d  gpcircle;
  gp_Lin2d   gpline;

  double   distance = 0.;
  gp_Vec2d tangent;
  gp_Pnt2d point;

  GccInt_IType type = abisector->ArcType();

  if (type == GccInt_Lin)
  {
    gpline     = abisector->Line();
    aparameter = ElCLib::Parameter(gpline, apoint);
    ElCLib::D1(aparameter, gpline, point, tangent);
  }
  else if (type == GccInt_Cir)
  {
    gpcircle   = abisector->Circle();
    aparameter = ElCLib::Parameter(gpcircle, apoint);
    ElCLib::D1(aparameter, gpcircle, point, tangent);
  }
  else if (type == GccInt_Hpr)
  {
    gphyperbola = abisector->Hyperbola();
    aparameter  = ElCLib::Parameter(gphyperbola, apoint);
    ElCLib::D1(aparameter, gphyperbola, point, tangent);
  }
  else if (type == GccInt_Par)
  {
    gpparabola = abisector->Parabola();
    aparameter = ElCLib::Parameter(gpparabola, apoint);
    ElCLib::D1(aparameter, gpparabola, point, tangent);
  }
  else if (type == GccInt_Ell)
  {
    gpellipse  = abisector->Ellipse();
    aparameter = ElCLib::Parameter(gpellipse, apoint);
    ElCLib::D1(aparameter, gpellipse, point, tangent);
  }

  distance = apoint.Distance(point);

  gp_Dir2d afirstdir(afirstvector);
  gp_Dir2d aseconddir(asecondvector);
  gp_Dir2d tangdir(tangent);
  gp_Dir2d secdirrev = aseconddir.Reversed();

  if (asense)
  {

    double SinPlat = 1.e-3;
    if (std::abs(afirstdir ^ aseconddir) < SinPlat)
    {
      if (afirstdir * aseconddir >= 0.0)
      {

        if (std::abs(tangdir * afirstdir) < 0.5)
        {
          astatus = false;
        }
      }
      else
      {

        if (std::abs(tangdir * afirstdir) > 0.5)
        {
          astatus = false;
        }
      }
    }
    else if ((afirstdir ^ tangdir) * (tangdir ^ aseconddir) < -1.E-8)
    {
      astatus = false;
    }
  }
  else
  {
    asense = true;

    if (!IsBisecOfTwoLines)
    {

      double aTol = 1.e-4;

      if ((afirstdir ^ secdirrev) * adirection < -0.1)
      {
        if ((afirstdir ^ tangdir) * adirection < aTol && (secdirrev ^ tangdir) * adirection < aTol)
          asense = false;
      }
      else if ((afirstdir ^ secdirrev) * adirection > 0.1)
      {
        if ((afirstdir ^ tangdir) * adirection < aTol || (secdirrev ^ tangdir) * adirection < aTol)
          asense = false;
      }
      else
      {
        if (afirstdir.Dot(secdirrev) > 0.)
        {
          if ((afirstdir ^ tangdir) * adirection < 0.)
            asense = false;
        }
        else
        {

          if (afirstdir.Dot(tangdir) < 0.)
            asense = false;
        }
      }

      if (VecRef.SquareMagnitude() != 0)
      {
        gp_Dir2d DirRef = VecRef;
        if (tangdir * DirRef < 0.)
          asense = false;
      }
    }
  }
  return distance;
}

void Bisector_BisecAna::Perform(const occ::handle<Geom2d_Curve>& afirstcurve,
                                const occ::handle<Geom2d_Curve>& asecondcurve,
                                const gp_Pnt2d&                  apoint,
                                const gp_Vec2d&                  afirstvector,
                                const gp_Vec2d&                  asecondvector,
                                const double                     adirection,
                                const GeomAbs_JoinType           ajointype,
                                const double                     tolerance,
                                const bool                       oncurve)
{

  bool             ok;
  double           distanceptsol, parameter, firstparameter = 0.;
  bool             thesense = false, sense;
  double           distancemini;
  int              nbsolution;
  constexpr double PreConf = Precision::Confusion();

  occ::handle<Standard_Type> type1 = afirstcurve->DynamicType();
  occ::handle<Standard_Type> type2 = asecondcurve->DynamicType();
  occ::handle<Geom2d_Curve>  CurveF;
  occ::handle<Geom2d_Curve>  CurveE;
  occ::handle<GccInt_Bisec>  TheSol;

  gp_Vec2d LineBisVec(0., 0.);
  gp_Vec2d tan1, tan2;
  gp_Pnt2d Pnt1, Pnt2;
  afirstcurve->D1(afirstcurve->LastParameter(), Pnt1, tan1);
  asecondcurve->D1(asecondcurve->FirstParameter(), Pnt2, tan2);
  if (!oncurve)
  {
    LineBisVec = gp_Vec2d(Pnt1, Pnt2);
    LineBisVec.Rotate(M_PI / 2.);
  }

  tan1.Reverse();

  if (type1 == STANDARD_TYPE(Geom2d_TrimmedCurve))
    CurveF = occ::down_cast<Geom2d_TrimmedCurve>(afirstcurve)->BasisCurve();
  else
    CurveF = afirstcurve;

  if (type2 == STANDARD_TYPE(Geom2d_TrimmedCurve))
    CurveE = occ::down_cast<Geom2d_TrimmedCurve>(asecondcurve)->BasisCurve();
  else
    CurveE = asecondcurve;

  type1         = CurveF->DynamicType();
  type2         = CurveE->DynamicType();
  int       cas = 0;
  gp_Circ2d circle1, circle2;
  gp_Lin2d  line1, line2;

  if (type1 == STANDARD_TYPE(Geom2d_Circle))
  {
    if (type2 == STANDARD_TYPE(Geom2d_Circle))
    {
      cas                           = 1;
      occ::handle<Geom2d_Circle> C1 = occ::down_cast<Geom2d_Circle>(CurveF);
      circle1                       = C1->Circ2d();
      occ::handle<Geom2d_Circle> C2 = occ::down_cast<Geom2d_Circle>(CurveE);
      circle2                       = C2->Circ2d();
    }
    else if (type2 == STANDARD_TYPE(Geom2d_Line))
    {
      cas                           = 2;
      occ::handle<Geom2d_Circle> C1 = occ::down_cast<Geom2d_Circle>(CurveF);
      circle1                       = C1->Circ2d();
      occ::handle<Geom2d_Line> L2   = occ::down_cast<Geom2d_Line>(CurveE);
      line2                         = L2->Lin2d();
    }
    else
    {
      std::cout << "Not yet implemented" << std::endl;
    }
  }
  else if (type1 == STANDARD_TYPE(Geom2d_Line))
  {
    if (type2 == STANDARD_TYPE(Geom2d_Circle))
    {
      cas                           = 2;
      occ::handle<Geom2d_Circle> C1 = occ::down_cast<Geom2d_Circle>(CurveE);
      circle1                       = C1->Circ2d();
      occ::handle<Geom2d_Line> L2   = occ::down_cast<Geom2d_Line>(CurveF);
      line2                         = L2->Lin2d();
    }
    else if (type2 == STANDARD_TYPE(Geom2d_Line))
    {
      cas                         = 3;
      occ::handle<Geom2d_Line> L1 = occ::down_cast<Geom2d_Line>(CurveF);
      line1                       = L1->Lin2d();
      occ::handle<Geom2d_Line> L2 = occ::down_cast<Geom2d_Line>(CurveE);
      line2                       = L2->Lin2d();
    }
    else
    {
      std::cout << "Not yet implemented" << std::endl;
    }
  }
  else
  {
    std::cout << "Not yet implemented" << std::endl;
  }

  switch (cas)
  {

    case 1:
    {
      double radius1 = circle1.Radius();
      double radius2 = circle2.Radius();

      if (circle1.Location().IsEqual(circle2.Location(), PreConf)
          && (std::abs(radius1 - radius2) <= PreConf))
      {
        gp_Pnt2d P1 = afirstcurve->Value(afirstcurve->LastParameter());
        gp_Pnt2d P2 = asecondcurve->Value(asecondcurve->FirstParameter());
        gp_Pnt2d PMil;
        gp_Lin2d line;
        PMil = gp_Pnt2d((P1.X() + P2.X()) / 2., (P1.Y() + P2.Y()) / 2.);

        if (!circle1.Location().IsEqual(PMil, PreConf))
        {

          line = gp_Lin2d(
            PMil,
            gp_Dir2d(circle1.Location().X() - PMil.X(), circle1.Location().Y() - PMil.Y()));
        }
        else if (radius1 >= PreConf)
        {

          line =
            gp_Lin2d(circle1.Location(),
                     gp_Dir2d(P1.Y() - circle1.Location().Y(), circle1.Location().X() - P1.X()));
        }
        else
        {

          line = gp_Lin2d(circle1.Location(), gp_Dir2d(gp_Dir2d::D::X));
        }

        occ::handle<GccInt_Bisec> solution = new GccInt_BLine(line);
        sense                              = false;

        if (oncurve)
          distanceptsol =
            Distance(apoint, solution, tan2, tan1, LineBisVec, adirection, parameter, sense, ok);
        else
          distanceptsol = Distance(apoint,
                                   solution,
                                   afirstvector,
                                   asecondvector,
                                   LineBisVec,
                                   adirection,
                                   parameter,
                                   sense,
                                   ok);

        occ::handle<Geom2d_Curve> bisectorcurve = new Geom2d_Line(line);
        if (!sense)
          thebisector = new Geom2d_TrimmedCurve(bisectorcurve, parameter, -Precision::Infinite());
        else
        {
          double parameter2;
          parameter2 = ElCLib::Parameter(line, circle1.Location());
          parameter2 += 1.e-8;
          thebisector = new Geom2d_TrimmedCurve(bisectorcurve, parameter, parameter2);
        }
        break;
      }

      if (radius1 < radius2)
      {
        gp_Circ2d circle = circle1;
        circle1          = circle2;
        circle2          = circle;

        double radius = radius1;
        radius1       = radius2;
        radius2       = radius;
      }

      double EntreAxe       = circle1.Location().Distance(circle2.Location());
      double D1             = 0.5 * (radius1 - EntreAxe - radius2);
      bool   CirclesTangent = false;

      if (oncurve && std::abs(D1) < PreConf && tan1.IsParallel(tan2, 1.e-8))
      {

        circle1.SetRadius(radius1 - D1);
        circle2.SetRadius(radius2 + D1);
        CirclesTangent = true;
      }
      else
      {
        D1 = 0.5 * (radius1 - EntreAxe + radius2);

        if (oncurve && std::abs(D1) < PreConf && tan1.IsParallel(tan2, 1.e-8))
        {

          circle1.SetRadius(radius1 - D1);
          circle2.SetRadius(radius2 - D1);
          CirclesTangent = true;
        }
      }

      GccAna_Circ2dBisec Bisector(circle1, circle2);

      distancemini = Precision::Infinite();

      if (Bisector.IsDone())
      {
        nbsolution = Bisector.NbSolutions();
        for (int i = 1; i <= nbsolution; i++)
        {
          occ::handle<GccInt_Bisec> solution = Bisector.ThisSolution(i);
          Degenerate(solution, tolerance);
          sense = true;
          if (oncurve)
          {
            distanceptsol =
              Distance(apoint, solution, tan1, tan2, LineBisVec, adirection, parameter, sense, ok);
          }
          else
          {
            ok = true;
          }

          if (ok)
          {
            sense = false;

            if (oncurve)
              distanceptsol = Distance(apoint,
                                       solution,
                                       tan2,
                                       tan1,
                                       LineBisVec,
                                       adirection,
                                       parameter,
                                       sense,
                                       ok);
            else
              distanceptsol = Distance(apoint,
                                       solution,
                                       afirstvector,
                                       asecondvector,
                                       LineBisVec,
                                       adirection,
                                       parameter,
                                       sense,
                                       ok);

            if (distanceptsol <= distancemini)
            {
              TheSol         = solution;
              firstparameter = parameter;
              thesense       = sense;
              distancemini   = distanceptsol;
            }
          }
        }
        if (!TheSol.IsNull())
        {
          occ::handle<Geom2d_Curve> bisectorcurve;
          GccInt_IType              type = TheSol->ArcType();
          if (type == GccInt_Lin)
          {
            gp_Lin2d gpline = TheSol->Line();
            bisectorcurve   = new Geom2d_Line(gpline);

            double secondparameter = Precision::Infinite();
            if (!thesense)
              secondparameter = -Precision::Infinite();

            if (oncurve)
            {

              if (CirclesTangent)
              {

                if (distancemini > tolerance)
                {
                  gp_Pnt2d aPloc = gpline.Location();
                  gp_Dir2d aNewDir(apoint.XY() - aPloc.XY());
                  gp_Lin2d aNewLin(aPloc, aNewDir);
                  gp_Pnt2d aCC2     = circle2.Location();
                  double   aNewDMin = aNewLin.Distance(apoint);
                  double   aTolConf = 1.e-3;

                  if (aNewLin.Distance(aCC2) <= aTolConf)
                  {
                    distancemini   = aNewDMin;
                    firstparameter = ElCLib::Parameter(aNewLin, apoint);
                    bisectorcurve  = new Geom2d_Line(aNewLin);
                  }
                }

                if (tan1.Dot(tan2) < 0.)
                {

                  double Par1   = ElCLib::Parameter(gpline, circle1.Location());
                  double Par2   = ElCLib::Parameter(gpline, circle2.Location());
                  double MinPar = std::min(Par1, Par2);
                  double MaxPar = std::max(Par1, Par2);

                  if (!thesense)
                  {
                    if (MaxPar < firstparameter)
                      secondparameter = MaxPar - 1.E-8;
                    else if (MinPar < firstparameter)
                      secondparameter = MinPar - 1.E-8;
                  }
                  else
                  {
                    if (MinPar > firstparameter)
                      secondparameter = MinPar + 1.E-8;
                    else if (MaxPar > firstparameter)
                      secondparameter = MaxPar + 1.E-8;
                  }
                }
              }
            }

            thebisector = new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, secondparameter);
          }
          else if (type == GccInt_Cir)
          {
            bisectorcurve = new Geom2d_Circle(TheSol->Circle());
            if (!thesense)
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve,
                                                    firstparameter - 2.0 * M_PI,
                                                    firstparameter,
                                                    thesense);
            else
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve,
                                                    firstparameter,
                                                    firstparameter + 2.0 * M_PI,
                                                    thesense);
          }
          else if (type == GccInt_Hpr)
          {
            bisectorcurve = new Geom2d_Hyperbola(TheSol->Hyperbola());
            if (!thesense)
              thebisector =
                new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, -Precision::Infinite());
            else
              thebisector =
                new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, Precision::Infinite());
          }
          else if (type == GccInt_Ell)
          {
            bisectorcurve = new Geom2d_Ellipse(TheSol->Ellipse());
            if (!thesense)
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve,
                                                    firstparameter - 2.0 * M_PI,
                                                    firstparameter,
                                                    thesense);
            else
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve,
                                                    firstparameter,
                                                    firstparameter + 2.0 * M_PI,
                                                    thesense);
          }
        }
      }
    }
    break;

    case 2:
    {

      if (oncurve)
      {
        double radius1 = circle1.Radius();
        double D1      = (line2.Distance(circle1.Location()) - radius1);

        if (std::abs(D1) < PreConf && tan1.IsParallel(tan2, 1.e-8))
        {

          circle1.SetRadius(radius1 + D1);
        }
      }

      GccAna_CircLin2dBisec Bisector(circle1, line2);

      distancemini = Precision::Infinite();

      if (Bisector.IsDone())
      {
        nbsolution = Bisector.NbSolutions();
        for (int i = 1; i <= nbsolution; i++)
        {
          occ::handle<GccInt_Bisec> solution = Bisector.ThisSolution(i);
          Degenerate(solution, tolerance);
          sense = true;
          distanceptsol =
            Distance(apoint, solution, tan1, tan2, LineBisVec, adirection, parameter, sense, ok);
          if (ok || !oncurve)
          {
            sense = false;

            if (oncurve)
              distanceptsol = Distance(apoint,
                                       solution,
                                       tan2,
                                       tan1,
                                       LineBisVec,
                                       adirection,
                                       parameter,
                                       sense,
                                       ok);
            else
              distanceptsol = Distance(apoint,
                                       solution,
                                       afirstvector,
                                       asecondvector,
                                       LineBisVec,
                                       adirection,
                                       parameter,
                                       sense,
                                       ok);

            if (distanceptsol <= distancemini)
            {
              TheSol         = solution;
              firstparameter = parameter;
              thesense       = sense;
              distancemini   = distanceptsol + 1.e-8;
            }
          }
        }
        if (!TheSol.IsNull())
        {
          GccInt_IType              type = TheSol->ArcType();
          occ::handle<Geom2d_Curve> bisectorcurve;
          if (type == GccInt_Lin)
          {

            gp_Pnt2d circlecenter;
            gp_Lin2d gpline;
            double   secondparameter;

            circlecenter    = circle1.Location();
            gpline          = TheSol->Line();
            secondparameter = ElCLib::Parameter(gpline, circlecenter);
            bisectorcurve   = new Geom2d_Line(gpline);

            if (!thesense)
            {
              if (secondparameter > firstparameter)
              {
                secondparameter = -Precision::Infinite();
              }
              else
              {
                secondparameter = secondparameter - 1.E-8;
              }
            }
            else
            {
              if (secondparameter < firstparameter)
              {
                secondparameter = Precision::Infinite();
              }
              else
              {
                secondparameter = secondparameter + 1.E-8;
              }
            }

            thebisector = new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, secondparameter);
          }
          else if (type == GccInt_Par)
          {
            bisectorcurve                = new Geom2d_Parabola(TheSol->Parabola());
            gp_Pnt2d     apex            = bisectorcurve->Value(0.);
            gp_Pnt2d     firstpnt        = bisectorcurve->Value(firstparameter);
            double       ChordLen        = apex.Distance(firstpnt);
            const double TolPar          = 1.e-5;
            double       secondparameter = Precision::Infinite();
            if (!thesense)
            {
              if (ajointype == GeomAbs_Intersection && TolPar < firstparameter
                  && ChordLen >= circle1.Radius())
                secondparameter = 0.;
              thebisector =
                new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, -secondparameter);
            }
            else
            {
              if (ajointype == GeomAbs_Intersection && firstparameter < -TolPar
                  && ChordLen >= circle1.Radius())
                secondparameter = 0.;
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, secondparameter);
            }
          }
        }
      }
    }
    break;

    case 3:
    {
      gp_Dir2d Direc1(line1.Direction());
      gp_Dir2d Direc2(line2.Direction());
      gp_Lin2d line;
      distancemini = Precision::Infinite();

      if (Direc1.IsParallel(Direc2, 1.e-8))
      {

        if (line1.Distance(line2.Location()) / 2. <= Precision::Confusion())
          line = gp_Lin2d(apoint, gp_Dir2d(-line1.Direction().Y(), line1.Direction().X()));
        else
          line = gp_Lin2d(apoint, line2.Direction());

        occ::handle<GccInt_Bisec> solution = new GccInt_BLine(line);

        sense = false;

        if (oncurve)
          distanceptsol =
            Distance(apoint, solution, tan2, tan1, LineBisVec, adirection, parameter, sense, ok);
        else
          distanceptsol = Distance(apoint,
                                   solution,
                                   afirstvector,
                                   asecondvector,
                                   LineBisVec,
                                   adirection,
                                   parameter,
                                   sense,
                                   ok);

        firstparameter = parameter;
        occ::handle<Geom2d_Curve> bisectorcurve;
        bisectorcurve = new Geom2d_Line(line);
        if (!sense)
          thebisector =
            new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, -Precision::Infinite());
        else
          thebisector =
            new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, Precision::Infinite());
      }
      else
      {
        gp_Lin2d                  l(apoint, gp_Dir2d(Direc2.XY() - Direc1.XY()));
        occ::handle<GccInt_Bisec> solution = new GccInt_BLine(l);
        bool                      isOk;
        sense = false;

        if (oncurve)
          distanceptsol =
            Distance(apoint, solution, tan2, tan1, LineBisVec, adirection, parameter, sense, isOk);
        else
          distanceptsol = Distance(apoint,
                                   solution,
                                   afirstvector,
                                   asecondvector,
                                   LineBisVec,
                                   adirection,
                                   parameter,
                                   sense,
                                   isOk,
                                   true);

        if (isOk || !oncurve)
        {
          thesense     = sense;
          distancemini = distanceptsol;
        }
        TheSol = new GccInt_BLine(l);
        occ::handle<Geom2d_Curve> bisectorcurve;
        bisectorcurve = new Geom2d_Line(TheSol->Line());
        if (!thesense)
          thebisector = new Geom2d_TrimmedCurve(bisectorcurve, 0., -Precision::Infinite());
        else
          thebisector = new Geom2d_TrimmedCurve(bisectorcurve, 0., Precision::Infinite());
      }
    }
    break;

    default:
      throw StdFail_NotDone();
      break;
  }
}

void Bisector_BisecAna::Perform(const occ::handle<Geom2d_Curve>& afirstcurve,
                                const occ::handle<Geom2d_Point>& asecondpoint,
                                const gp_Pnt2d&                  apoint,
                                const gp_Vec2d&                  afirstvector,
                                const gp_Vec2d&                  asecondvector,
                                const double                     adirection,
                                const double                     tolerance,
                                const bool                       oncurve)
{
  bool                      ok;
  bool                      thesense = false, sense;
  double                    distanceptsol, parameter, firstparameter = 0., secondparameter;
  gp_Vec2d                  VecRef(0., 0.);
  occ::handle<Geom2d_Curve> curve;
  occ::handle<GccInt_Bisec> TheSol;

  gp_Circ2d circle;
  gp_Lin2d  line;
  gp_Pnt2d  circlecenter;

  int cas = 0;

  occ::handle<Standard_Type> aFirstCurveType = afirstcurve->DynamicType();

  if (aFirstCurveType == STANDARD_TYPE(Geom2d_TrimmedCurve))
  {
    curve = occ::down_cast<Geom2d_TrimmedCurve>(afirstcurve)->BasisCurve();
  }
  else
  {
    curve = afirstcurve;
  }

  aFirstCurveType = curve->DynamicType();
  const gp_Pnt2d aPoint(asecondpoint->Pnt2d());
  (void)aPoint;
  if (aFirstCurveType == STANDARD_TYPE(Geom2d_Circle))
  {
    cas                           = 1;
    occ::handle<Geom2d_Circle> C1 = occ::down_cast<Geom2d_Circle>(curve);
    circle                        = C1->Circ2d();
  }
  else if (aFirstCurveType == STANDARD_TYPE(Geom2d_Line))
  {
    cas                         = 2;
    occ::handle<Geom2d_Line> L1 = occ::down_cast<Geom2d_Line>(curve);
    line                        = L1->Lin2d();
  }
  else
  {
    std::cout << "Not yet implemented" << std::endl;
  }

  switch (cas)
  {

    case 1:
    {
      GccAna_CircPnt2dBisec Bisector(circle, asecondpoint->Pnt2d(), tolerance);
      double                distancemini = Precision::Infinite();
      if (Bisector.IsDone())
      {
        int nbsolution = Bisector.NbSolutions();
        for (int i = 1; i <= nbsolution; i++)
        {
          occ::handle<GccInt_Bisec> solution = Bisector.ThisSolution(i);
          Degenerate(solution, tolerance);
          sense         = false;
          distanceptsol = Distance(apoint,
                                   solution,
                                   afirstvector,
                                   asecondvector,
                                   VecRef,
                                   adirection,
                                   parameter,
                                   sense,
                                   ok);

          if (distanceptsol <= distancemini)
          {
            TheSol         = solution;
            firstparameter = parameter;
            thesense       = sense;
            distancemini   = distanceptsol;
          }
        }
        if (!TheSol.IsNull())
        {
          GccInt_IType              aSolType = TheSol->ArcType();
          occ::handle<Geom2d_Curve> bisectorcurve;
          if (aSolType == GccInt_Lin)
          {

            circlecenter    = circle.Location();
            line            = TheSol->Line();
            secondparameter = ElCLib::Parameter(line, circlecenter);
            bisectorcurve   = new Geom2d_Line(line);

            if (!thesense)
            {
              if (secondparameter > firstparameter)
              {
                secondparameter = -Precision::Infinite();
              }
              else
              {
                secondparameter = secondparameter - 1.E-8;
              }
            }
            else
            {
              if (secondparameter < firstparameter)
              {
                secondparameter = Precision::Infinite();
              }
              else
              {
                secondparameter = secondparameter + 1.E-8;
              }
            }

            thebisector = new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, secondparameter);
          }
          else if (aSolType == GccInt_Cir)
          {
            bisectorcurve = new Geom2d_Circle(TheSol->Circle());
            if (!thesense)
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve,
                                                    firstparameter - 2.0 * M_PI,
                                                    firstparameter,
                                                    thesense);
            else
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve,
                                                    firstparameter,
                                                    firstparameter + 2.0 * M_PI,
                                                    thesense);
          }
          else if (aSolType == GccInt_Hpr)
          {
            bisectorcurve = new Geom2d_Hyperbola(TheSol->Hyperbola());
            if (!thesense)
              thebisector =
                new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, -Precision::Infinite());
            else
              thebisector =
                new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, Precision::Infinite());
          }
          else if (aSolType == GccInt_Ell)
          {
            bisectorcurve = new Geom2d_Ellipse(TheSol->Ellipse());
            if (!thesense)
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve,
                                                    firstparameter - 2.0 * M_PI,
                                                    firstparameter,
                                                    thesense);
            else
              thebisector = new Geom2d_TrimmedCurve(bisectorcurve,
                                                    firstparameter,
                                                    firstparameter + 2.0 * M_PI,
                                                    thesense);
          }
        }
      }
    }
    break;

    case 2:
    {
      GccAna_LinPnt2dBisec Bisector(line, asecondpoint->Pnt2d());

#ifdef OCCT_DEBUG
      gp_Vec2d V(line.Direction());
#else
      line.Direction();
#endif
      occ::handle<GccInt_Bisec> solution = Bisector.ThisSolution();
      Degenerate(solution, tolerance);
      GccInt_IType              type = solution->ArcType();
      occ::handle<Geom2d_Curve> bisectorcurve;

      if (type == GccInt_Lin)
      {
        bisectorcurve = new Geom2d_Line(solution->Line());
      }
      else if (type == GccInt_Par)
      {
        bisectorcurve = new Geom2d_Parabola(solution->Parabola());
      }
      sense         = false;
      distanceptsol = Distance(apoint,
                               solution,
                               afirstvector,
                               asecondvector,
                               VecRef,
                               adirection,
                               parameter,
                               sense,
                               ok);

      if (ok || !oncurve)
      {
        firstparameter = parameter;
        thesense       = sense;
      }

      if (!thesense)
        thebisector =
          new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, -Precision::Infinite());
      else
        thebisector = new Geom2d_TrimmedCurve(bisectorcurve, firstparameter, Precision::Infinite());
    }
    break;

    default:
    {
      std::cout << "Not yet implemented" << std::endl;
      break;
    }
  }
}

void Bisector_BisecAna::Perform(const occ::handle<Geom2d_Point>& afirstpoint,
                                const occ::handle<Geom2d_Curve>& asecondcurve,
                                const gp_Pnt2d&                  apoint,
                                const gp_Vec2d&                  afirstvector,
                                const gp_Vec2d&                  asecondvector,
                                const double                     adirection,

                                const double,
                                const bool oncurve)

{
  double adirectionreverse = -adirection;
  Perform(asecondcurve,
          afirstpoint,
          apoint,
          asecondvector,
          afirstvector,
          adirectionreverse,

          0.,

          oncurve);
}

void Bisector_BisecAna::Perform(const occ::handle<Geom2d_Point>& afirstpoint,
                                const occ::handle<Geom2d_Point>& asecondpoint,
                                const gp_Pnt2d&                  apoint,
                                const gp_Vec2d&                  afirstvector,
                                const gp_Vec2d&                  asecondvector,
                                const double                     adirection,

                                const double,
                                const bool oncurve)
{
  bool     sense, ok;
  double   parameter;
  gp_Vec2d VecRef(0., 0.);

  GccAna_Pnt2dBisec         bisector(afirstpoint->Pnt2d(), asecondpoint->Pnt2d());
  gp_Lin2d                  line     = bisector.ThisSolution();
  occ::handle<GccInt_Bisec> solution = new GccInt_BLine(line);

  sense = false;
  Distance(apoint, solution, afirstvector, asecondvector, VecRef, adirection, parameter, sense, ok);
  if (ok || !oncurve)
  {
    occ::handle<Geom2d_Curve> bisectorcurve = new Geom2d_Line(line);
    if (!sense)
      thebisector = new Geom2d_TrimmedCurve(bisectorcurve, parameter, -Precision::Infinite());
    else
      thebisector = new Geom2d_TrimmedCurve(bisectorcurve, parameter, Precision::Infinite());
  }
}

bool Bisector_BisecAna::IsExtendAtStart() const
{
  return false;
}

bool Bisector_BisecAna::IsExtendAtEnd() const
{
  return false;
}

void Bisector_BisecAna::SetTrim(const occ::handle<Geom2d_Curve>&) {}

void Bisector_BisecAna::SetTrim(const double uf, const double ul)
{
  thebisector->SetTrim(uf, ul);
}

void Bisector_BisecAna::Reverse()
{
  thebisector->Reverse();
}

double Bisector_BisecAna::ReversedParameter(const double U) const
{
  return thebisector->ReversedParameter(U);
}

bool Bisector_BisecAna::IsCN(const int N) const
{
  return thebisector->IsCN(N);
}

occ::handle<Geom2d_Geometry> Bisector_BisecAna::Copy() const
{
  occ::handle<Bisector_BisecAna> C = new Bisector_BisecAna();
  C->Init(occ::down_cast<Geom2d_TrimmedCurve>(thebisector->Copy()));
  return C;
}

void Bisector_BisecAna::Transform(const gp_Trsf2d& T)
{
  thebisector->Transform(T);
}

double Bisector_BisecAna::FirstParameter() const
{

  return thebisector->FirstParameter();
}

double Bisector_BisecAna::LastParameter() const
{
  return thebisector->LastParameter();
}

bool Bisector_BisecAna::IsClosed() const
{
  return thebisector->BasisCurve()->IsClosed();
}

bool Bisector_BisecAna::IsPeriodic() const
{
  return thebisector->BasisCurve()->IsPeriodic();
}

GeomAbs_Shape Bisector_BisecAna::Continuity() const
{
  return thebisector->Continuity();
}

void Bisector_BisecAna::D0(const double U, gp_Pnt2d& P) const
{
  thebisector->BasisCurve()->D0(U, P);
}

void Bisector_BisecAna::D1(const double U, gp_Pnt2d& P, gp_Vec2d& V1) const
{
  thebisector->BasisCurve()->D1(U, P, V1);
}

void Bisector_BisecAna::D2(const double U, gp_Pnt2d& P, gp_Vec2d& V1, gp_Vec2d& V2) const
{
  thebisector->BasisCurve()->D2(U, P, V1, V2);
}

void Bisector_BisecAna::D3(const double U,
                           gp_Pnt2d&    P,
                           gp_Vec2d&    V1,
                           gp_Vec2d&    V2,
                           gp_Vec2d&    V3) const
{
  thebisector->BasisCurve()->D3(U, P, V1, V2, V3);
}

gp_Vec2d Bisector_BisecAna::DN(const double U, const int N) const
{
  return thebisector->BasisCurve()->DN(U, N);
}

occ::handle<Geom2d_Curve> Bisector_BisecAna::Geom2dCurve() const
{
  return thebisector->BasisCurve();
}

double Bisector_BisecAna::ParameterOfStartPoint() const
{
  return thebisector->FirstParameter();
}

double Bisector_BisecAna::ParameterOfEndPoint() const
{
  return thebisector->LastParameter();
}

double Bisector_BisecAna::Parameter(const gp_Pnt2d& P) const
{
  gp_Hypr2d  gphyperbola;
  gp_Parab2d gpparabola;
  gp_Elips2d gpellipse;
  gp_Circ2d  gpcircle;
  gp_Lin2d   gpline;

  occ::handle<Geom2d_Curve>  BasisCurve = thebisector->BasisCurve();
  occ::handle<Standard_Type> Type       = BasisCurve->DynamicType();

  if (Type == STANDARD_TYPE(Geom2d_Line))
  {
    gpline = occ::down_cast<Geom2d_Line>(BasisCurve)->Lin2d();
    return ElCLib::Parameter(gpline, P);
  }
  else if (Type == STANDARD_TYPE(Geom2d_Circle))
  {
    gpcircle = occ::down_cast<Geom2d_Circle>(BasisCurve)->Circ2d();
    return ElCLib::Parameter(gpcircle, P);
  }
  else if (Type == STANDARD_TYPE(Geom2d_Hyperbola))
  {
    gphyperbola = occ::down_cast<Geom2d_Hyperbola>(BasisCurve)->Hypr2d();
    return ElCLib::Parameter(gphyperbola, P);
  }
  else if (Type == STANDARD_TYPE(Geom2d_Parabola))
  {
    gpparabola = occ::down_cast<Geom2d_Parabola>(BasisCurve)->Parab2d();
    return ElCLib::Parameter(gpparabola, P);
  }
  else if (Type == STANDARD_TYPE(Geom2d_Ellipse))
  {
    gpellipse = occ::down_cast<Geom2d_Ellipse>(BasisCurve)->Elips2d();
    return ElCLib::Parameter(gpellipse, P);
  }
  return 0.;
}

int Bisector_BisecAna::NbIntervals() const
{
  return 1;
}

double Bisector_BisecAna::IntervalFirst(const int I) const
{
  if (I != 1)
    throw Standard_OutOfRange();
  return FirstParameter();
}

double Bisector_BisecAna::IntervalLast(const int I) const
{
  if (I != 1)
    throw Standard_OutOfRange();
  return LastParameter();
}

void Bisector_BisecAna::Init(const occ::handle<Geom2d_TrimmedCurve>& Bis)
{
  thebisector = Bis;
}

bool Degenerate(occ::handle<GccInt_Bisec>& aBisector, const double Tolerance)
{
  bool Degeneree = false;

  gp_Hypr2d  gphyperbola;
  gp_Parab2d gpparabola;
  gp_Elips2d gpellipse;

  occ::handle<GccInt_Bisec> NewBisector;

  GccInt_IType type = aBisector->ArcType();

  if (type == GccInt_Hpr)
  {
    gphyperbola = aBisector->Hyperbola();

    if (gphyperbola.MajorRadius() < Tolerance)
    {
      gp_Lin2d gpline(gphyperbola.YAxis());
      NewBisector = new GccInt_BLine(gpline);
      aBisector   = NewBisector;
      Degeneree   = true;
    }
    if (gphyperbola.MinorRadius() < Tolerance)
    {
      gp_Lin2d gpline(gphyperbola.XAxis());
      NewBisector = new GccInt_BLine(gpline);
      aBisector   = NewBisector;
      Degeneree   = true;
    }
  }
  else if (type == GccInt_Par)
  {
    gpparabola = aBisector->Parabola();

    if (gpparabola.Focal() < Tolerance)
    {
      gp_Lin2d gpline(gpparabola.MirrorAxis());
      NewBisector = new GccInt_BLine(gpline);
      aBisector   = NewBisector;
      Degeneree   = true;
    }
  }
  else if (type == GccInt_Ell)
  {
    gpellipse = aBisector->Ellipse();

    if (gpellipse.MinorRadius() < Tolerance)
    {
      gp_Lin2d gpline(gpellipse.XAxis());
      NewBisector = new GccInt_BLine(gpline);
      aBisector   = NewBisector;
      Degeneree   = true;
    }
  }
  return Degeneree;
}

static void Indent(const int Offset)
{
  if (Offset > 0)
  {
    for (int i = 0; i < Offset; i++)
    {
      std::cout << " ";
    }
  }
}

void Bisector_BisecAna::Dump(const int, const int Offset) const
{
  Indent(Offset);
  std::cout << "Bisector_BisecAna" << std::endl;
  Indent(Offset);
}
