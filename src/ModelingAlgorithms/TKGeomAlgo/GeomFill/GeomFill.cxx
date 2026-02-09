#include <GeomFill.hpp>

#include <Geom_Circle.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_Curve.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_Surface.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomConvert.hpp>
#include <GeomFill_Generator.hpp>
#include <GeomFill_PolynomialConvertor.hpp>
#include <GeomFill_QuasiAngularConvertor.hpp>
#include <gp_Ax3.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>

occ::handle<Geom_Surface> GeomFill::Surface(const occ::handle<Geom_Curve>& Curve1,
                                            const occ::handle<Geom_Curve>& Curve2)

{
  occ::handle<Geom_Curve>   TheCurve1, TheCurve2;
  occ::handle<Geom_Surface> Surf;

  double a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  bool   Trim1 = false, Trim2 = false;
  if (Curve1->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve> Ctrim = occ::down_cast<Geom_TrimmedCurve>(Curve1);
    TheCurve1                            = Ctrim->BasisCurve();
    a1                                   = Ctrim->FirstParameter();
    b1                                   = Ctrim->LastParameter();
    Trim1                                = true;
  }
  else
  {
    TheCurve1 = occ::down_cast<Geom_Curve>(Curve1->Copy());
  }
  if (Curve2->IsKind(STANDARD_TYPE(Geom_TrimmedCurve)))
  {
    occ::handle<Geom_TrimmedCurve> Ctrim = occ::down_cast<Geom_TrimmedCurve>(Curve2);
    TheCurve2                            = Ctrim->BasisCurve();
    a2                                   = Ctrim->FirstParameter();
    b2                                   = Ctrim->LastParameter();
    Trim2                                = true;
  }
  else
  {
    TheCurve2 = occ::down_cast<Geom_Curve>(Curve2->Copy());
  }

  bool IsDone = false;

  if (TheCurve1->IsKind(STANDARD_TYPE(Geom_Line)) && TheCurve2->IsKind(STANDARD_TYPE(Geom_Line))
      && Trim1 && Trim2)
  {

    gp_Lin L1 = (occ::down_cast<Geom_Line>(TheCurve1))->Lin();
    gp_Lin L2 = (occ::down_cast<Geom_Line>(TheCurve2))->Lin();
    gp_Dir D1 = L1.Direction();
    gp_Dir D2 = L2.Direction();

    if (D1.IsParallel(D2, Precision::Angular()))
    {
      gp_Vec P1P2(L1.Location(), L2.Location());
      double proj = P1P2.Dot(D1);

      if (D1.IsEqual(D2, Precision::Angular()))
      {
        if (std::abs(a1 - proj - a2) <= Precision::Confusion()
            && std::abs(b1 - proj - b2) <= Precision::Confusion())
        {
          gp_Ax3                  Ax(L1.Location(), gp_Dir(D1.Crossed(P1P2)), D1);
          occ::handle<Geom_Plane> P = new Geom_Plane(Ax);
          double                  V = P1P2.Dot(Ax.YDirection());
          Surf   = new Geom_RectangularTrimmedSurface(P, a1, b1, std::min(0., V), std::max(0., V));
          IsDone = true;
        }
      }
      if (D1.IsOpposite(D2, Precision::Angular()))
      {
        if (std::abs(a1 - proj + b2) <= Precision::Confusion()
            && std::abs(b1 - proj + a2) <= Precision::Confusion())
        {
          gp_Ax3                  Ax(L1.Location(), gp_Dir(D1.Crossed(P1P2)), D1);
          occ::handle<Geom_Plane> P = new Geom_Plane(Ax);
          double                  V = P1P2.Dot(Ax.YDirection());
          Surf   = new Geom_RectangularTrimmedSurface(P, a1, b1, std::min(0., V), std::max(0., V));
          IsDone = true;
        }
      }
    }
  }

  else if (TheCurve1->IsKind(STANDARD_TYPE(Geom_Circle))
           && TheCurve2->IsKind(STANDARD_TYPE(Geom_Circle)))
  {

    gp_Circ C1 = (occ::down_cast<Geom_Circle>(TheCurve1))->Circ();
    gp_Circ C2 = (occ::down_cast<Geom_Circle>(TheCurve2))->Circ();

    gp_Ax3 A1 = C1.Position();
    gp_Ax3 A2 = C2.Position();

    if (A1.Axis().IsCoaxial(A2.Axis(), Precision::Angular(), Precision::Confusion()))
    {
      double V = gp_Vec(A1.Location(), A2.Location()).Dot(gp_Vec(A1.Direction()));
      if (!Trim1 && !Trim2)
      {
        if (std::abs(C1.Radius() - C2.Radius()) < Precision::Confusion())
        {
          occ::handle<Geom_CylindricalSurface> C = new Geom_CylindricalSurface(A1, C1.Radius());
          Surf = new Geom_RectangularTrimmedSurface(C, std::min(0., V), std::max(0., V), false);
        }
        else
        {
          double Rad = C2.Radius() - C1.Radius();
          double Ang = std::atan(Rad / V);
          if (Ang < 0.)
          {
            A1.ZReverse();
            V   = -V;
            Ang = -Ang;
          }
          occ::handle<Geom_ConicalSurface> C = new Geom_ConicalSurface(A1, Ang, C1.Radius());
          V /= std::cos(Ang);
          Surf = new Geom_RectangularTrimmedSurface(C, std::min(0., V), std::max(0., V), false);
        }
        IsDone = true;
      }
      else if (Trim1 && Trim2)
      {
      }
    }
  }

  if (!IsDone)
  {
    GeomFill_Generator Generator;
    Generator.AddCurve(Curve1);
    Generator.AddCurve(Curve2);
    Generator.Perform(Precision::PConfusion());
    Surf = Generator.Surface();
  }

  return Surf;
}

void GeomFill::GetShape(const double                  MaxAng,
                        int&                          NbPoles,
                        int&                          NbKnots,
                        int&                          Degree,
                        Convert_ParameterisationType& TConv)
{
  switch (TConv)
  {
    case Convert_QuasiAngular:
    {
      NbPoles = 7;
      NbKnots = 2;
      Degree  = 6;
    }
    break;
    case Convert_Polynomial:
    {
      NbPoles = 8;
      NbKnots = 2;
      Degree  = 7;
    }
    break;
    default:
    {
      int NbSpan = (int)(std::ceil(3. * std::abs(MaxAng) / 2. / M_PI));
      NbPoles    = 2 * NbSpan + 1;
      NbKnots    = NbSpan + 1;
      Degree     = 2;
      if (NbSpan == 1)
      {
        TConv = Convert_TgtThetaOver2_1;
      }
      else if (NbSpan == 2)
      {
        TConv = Convert_TgtThetaOver2_2;
      }
      else if (NbSpan == 3)
      {
        TConv = Convert_TgtThetaOver2_3;
      }
    }
  }
}

void GeomFill::GetMinimalWeights(const Convert_ParameterisationType TConv,
                                 const double                       MinAng,
                                 const double                       MaxAng,
                                 NCollection_Array1<double>&        Weights)

{
  if (TConv == Convert_Polynomial)
    Weights.Init(1);
  else
  {
    gp_Ax2                         popAx2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
    gp_Circ                        C(popAx2, 1);
    occ::handle<Geom_TrimmedCurve> Sect1   = new Geom_TrimmedCurve(new Geom_Circle(C), 0., MaxAng);
    occ::handle<Geom_BSplineCurve> CtoBspl = GeomConvert::CurveToBSplineCurve(Sect1, TConv);
    CtoBspl->Weights(Weights);

    NCollection_Array1<double> poids(Weights.Lower(), Weights.Upper());
    double                     angle_min = std::max(Precision::PConfusion(), MinAng);

    occ::handle<Geom_TrimmedCurve> Sect2 = new Geom_TrimmedCurve(new Geom_Circle(C), 0., angle_min);
    CtoBspl                              = GeomConvert::CurveToBSplineCurve(Sect2, TConv);
    CtoBspl->Weights(poids);

    for (int ii = Weights.Lower(); ii <= Weights.Upper(); ii++)
    {
      if (poids(ii) < Weights(ii))
      {
        Weights(ii) = poids(ii);
      }
    }
  }
}

void GeomFill::Knots(const Convert_ParameterisationType TConv, NCollection_Array1<double>& TKnots)
{
  if ((TConv != Convert_QuasiAngular) && (TConv != Convert_Polynomial))
  {
    int    i;
    double val = 0.;
    for (i = TKnots.Lower(); i <= TKnots.Upper(); i++)
    {
      TKnots(i) = val;
      val       = val + 1.;
    }
  }
  else
  {
    TKnots(1) = 0.;
    TKnots(2) = 1.;
  }
}

void GeomFill::Mults(const Convert_ParameterisationType TConv, NCollection_Array1<int>& TMults)
{
  switch (TConv)
  {
    case Convert_QuasiAngular:
    {
      TMults(1) = 7;
      TMults(2) = 7;
    }
    break;
    case Convert_Polynomial:
    {
      TMults(1) = 8;
      TMults(2) = 8;
    }
    break;

    default:
    {

      int i;
      TMults(TMults.Lower()) = 3;
      for (i = TMults.Lower() + 1; i <= TMults.Upper() - 1; i++)
      {
        TMults(i) = 2;
      }
      TMults(TMults.Upper()) = 3;
    }
  }
}

double GeomFill::GetTolerance(const Convert_ParameterisationType TConv,
                              const double                       AngleMin,
                              const double                       Radius,
                              const double                       AngularTol,
                              const double                       SpatialTol)
{
  gp_Ax2                         popAx2(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
  gp_Circ                        C(popAx2, Radius);
  occ::handle<Geom_Circle>       popCircle = new Geom_Circle(C);
  occ::handle<Geom_TrimmedCurve> Sect =
    new Geom_TrimmedCurve(popCircle, 0., std::max(AngleMin, 0.02));

  occ::handle<Geom_BSplineCurve> CtoBspl = GeomConvert::CurveToBSplineCurve(Sect, TConv);
  double                         Dist;
  Dist = CtoBspl->Pole(1).Distance(CtoBspl->Pole(2)) + SpatialTol;
  return Dist * AngularTol / 2;
}

void GeomFill::GetCircle(const Convert_ParameterisationType TConv,
                         const gp_Vec&                      ns1,
                         const gp_Vec&                      ns2,
                         const gp_Vec&                      nplan,
                         const gp_Pnt&                      pts1,
                         const gp_Pnt&                      pts2,
                         const double                       Rayon,
                         const gp_Pnt&                      Center,
                         NCollection_Array1<gp_Pnt>&        Poles,
                         NCollection_Array1<double>&        Weights)
{

  int    i, jj;
  double Cosa, Sina, Angle, Alpha, Cosas2, lambda;
  gp_Vec temp, np2;
  int    low = Poles.Lower();
  int    upp = Poles.Upper();

  Cosa = ns1.Dot(ns2);
  Sina = nplan.Dot(ns1.Crossed(ns2));

  if (Cosa < -1.)
  {
    Cosa = -1;
    Sina = 0;
  }
  if (Cosa > 1.)
  {
    Cosa = 1;
    Sina = 0;
  }
  Angle = std::acos(Cosa);

  if (Sina < 0.)
  {
    if (Cosa > 0.)
      Angle = -Angle;
    else
      Angle = 2. * M_PI - Angle;
  }

  switch (TConv)
  {
    case Convert_QuasiAngular:
    {
      GeomFill_QuasiAngularConvertor QConvertor;
      QConvertor.Init();
      QConvertor.Section(pts1, Center, nplan, Angle, Poles, Weights);
      break;
    }
    case Convert_Polynomial:
    {
      GeomFill_PolynomialConvertor PConvertor;
      PConvertor.Init();
      PConvertor.Section(pts1, Center, nplan, Angle, Poles);
      Weights.Init(1);
      break;
    }
    default:
    {

      int NbSpan = (Poles.Length() - 1) / 2;

      Poles(low)   = pts1;
      Poles(upp)   = pts2;
      Weights(low) = 1;
      Weights(upp) = 1;

      np2 = nplan.Crossed(ns1);

      Alpha  = Angle / ((double)(NbSpan));
      Cosas2 = std::cos(Alpha / 2);

      for (i = 1, jj = low + 2; i <= NbSpan - 1; i++, jj += 2)
      {
        lambda = ((double)(i)) * Alpha;
        Cosa   = std::cos(lambda);
        Sina   = std::sin(lambda);
        temp.SetLinearForm(Cosa - 1, ns1, Sina, np2);
        Poles(jj).SetXYZ(pts1.XYZ() + Rayon * temp.XYZ());
        Weights(jj) = 1;
      }

      lambda = 1. / (2. * Cosas2 * Cosas2);
      for (i = 1, jj = low + 1; i <= NbSpan; i++, jj += 2)
      {
        temp.SetXYZ(Poles(jj - 1).XYZ() + Poles(jj + 1).XYZ() - 2. * Center.XYZ());
        Poles(jj).SetXYZ(Center.XYZ() + lambda * temp.XYZ());
        Weights(jj) = Cosas2;
      }
    }
  }
}

bool GeomFill::GetCircle(const Convert_ParameterisationType TConv,
                         const gp_Vec&                      ns1,
                         const gp_Vec&                      ns2,
                         const gp_Vec&                      dn1w,
                         const gp_Vec&                      dn2w,
                         const gp_Vec&                      nplan,
                         const gp_Vec&                      dnplan,
                         const gp_Pnt&                      pts1,
                         const gp_Pnt&                      pts2,
                         const gp_Vec&                      tang1,
                         const gp_Vec&                      tang2,
                         const double                       Rayon,
                         const double                       DRayon,
                         const gp_Pnt&                      Center,
                         const gp_Vec&                      DCenter,
                         NCollection_Array1<gp_Pnt>&        Poles,
                         NCollection_Array1<gp_Vec>&        DPoles,
                         NCollection_Array1<double>&        Weights,
                         NCollection_Array1<double>&        DWeights)
{
  double Cosa, Sina, Cosas2, Sinas2, Angle, DAngle, Alpha, lambda, Dlambda;
  gp_Vec temp, np2, dnp2;
  int    i, jj;
  int    NbSpan = (Poles.Length() - 1) / 2;
  int    low    = Poles.Lower();
  int    upp    = Poles.Upper();

  Cosa = ns1.Dot(ns2);
  Sina = nplan.Dot(ns1.Crossed(ns2));

  if (Cosa < -1.)
  {
    Cosa = -1;
    Sina = 0;
  }
  if (Cosa > 1.)
  {
    Cosa = 1;
    Sina = 0;
  }
  Angle = std::acos(Cosa);

  if (Sina < 0.)
  {
    if (Cosa > 0.)
      Angle = -Angle;
    else
      Angle = 2. * M_PI - Angle;
  }

  if (std::abs(Sina) > std::abs(Cosa))
  {
    DAngle = -(dn1w.Dot(ns2) + ns1.Dot(dn2w)) / Sina;
  }
  else
  {
    DAngle =
      (dnplan.Dot(ns1.Crossed(ns2)) + nplan.Dot(dn1w.Crossed(ns2) + ns1.Crossed(dn2w))) / Cosa;
  }

  Poles(low)   = pts1;
  Poles(upp)   = pts2;
  Weights(low) = 1;
  Weights(upp) = 1;

  DPoles(low)   = tang1;
  DPoles(upp)   = tang2;
  DWeights(low) = 0;
  DWeights(upp) = 0;

  switch (TConv)
  {
    case Convert_QuasiAngular:
    {
      GeomFill_QuasiAngularConvertor QConvertor;
      QConvertor.Init();
      QConvertor.Section(pts1,
                         tang1,
                         Center,
                         DCenter,
                         nplan,
                         dnplan,
                         Angle,
                         DAngle,
                         Poles,
                         DPoles,
                         Weights,
                         DWeights);
      return true;
    }
    case Convert_Polynomial:
    {
      GeomFill_PolynomialConvertor PConvertor;
      PConvertor.Init();
      PConvertor.Section(pts1, tang1, Center, DCenter, nplan, dnplan, Angle, DAngle, Poles, DPoles);
      Weights.Init(1);
      DWeights.Init(0);
      return true;
    }

    default:

    {
      np2  = nplan.Crossed(ns1);
      dnp2 = dnplan.Crossed(ns1).Added(nplan.Crossed(dn1w));

      Alpha  = Angle / ((double)(NbSpan));
      Cosas2 = std::cos(Alpha / 2);
      Sinas2 = std::sin(Alpha / 2);

      for (i = 1, jj = low + 2; i <= NbSpan - 1; i++, jj += 2)
      {
        lambda = ((double)(i)) * Alpha;
        Cosa   = std::cos(lambda);
        Sina   = std::sin(lambda);
        temp.SetLinearForm(Cosa - 1, ns1, Sina, np2);
        Poles(jj).SetXYZ(pts1.XYZ() + Rayon * temp.XYZ());

        DPoles(jj).SetLinearForm(DRayon, temp, tang1);
        temp.SetLinearForm(-Sina, ns1, Cosa, np2);
        temp.Multiply(((double)(i)) / ((double)(NbSpan)) * DAngle);
        temp.Add(((Cosa - 1) * dn1w).Added(Sina * dnp2));
        DPoles(jj) += Rayon * temp;
      }

      lambda  = 1. / (2. * Cosas2 * Cosas2);
      Dlambda = (lambda * Sinas2 * DAngle) / (Cosas2 * NbSpan);

      for (i = 1, jj = low; i <= NbSpan; i++, jj += 2)
      {
        temp.SetXYZ(Poles(jj).XYZ() + Poles(jj + 2).XYZ() - 2. * Center.XYZ());
        Poles(jj + 1).SetXYZ(Center.XYZ() + lambda * temp.XYZ());
        DPoles(jj + 1).SetLinearForm(Dlambda,
                                     temp,
                                     1. - 2 * lambda,
                                     DCenter,
                                     lambda,
                                     (DPoles(jj) + DPoles(jj + 2)));
      }

      Dlambda = -Sinas2 * DAngle / (2 * NbSpan);
      for (i = low; i < upp; i += 2)
      {
        Weights(i)      = 1.;
        Weights(i + 1)  = Cosas2;
        DWeights(i)     = 0.;
        DWeights(i + 1) = Dlambda;
      }
    }
      return true;
  }
}

bool GeomFill::GetCircle(const Convert_ParameterisationType TConv,
                         const gp_Vec&                      ns1,
                         const gp_Vec&                      ns2,
                         const gp_Vec&                      dn1w,
                         const gp_Vec&                      dn2w,
                         const gp_Vec&                      d2n1w,
                         const gp_Vec&                      d2n2w,
                         const gp_Vec&                      nplan,
                         const gp_Vec&                      dnplan,
                         const gp_Vec&                      d2nplan,
                         const gp_Pnt&                      pts1,
                         const gp_Pnt&                      pts2,
                         const gp_Vec&                      tang1,
                         const gp_Vec&                      tang2,
                         const gp_Vec&                      Dtang1,
                         const gp_Vec&                      Dtang2,
                         const double                       Rayon,
                         const double                       DRayon,
                         const double                       D2Rayon,
                         const gp_Pnt&                      Center,
                         const gp_Vec&                      DCenter,
                         const gp_Vec&                      D2Center,
                         NCollection_Array1<gp_Pnt>&        Poles,
                         NCollection_Array1<gp_Vec>&        DPoles,
                         NCollection_Array1<gp_Vec>&        D2Poles,
                         NCollection_Array1<double>&        Weights,
                         NCollection_Array1<double>&        DWeights,
                         NCollection_Array1<double>&        D2Weights)
{
  double Cosa, Sina, Cosas2, Sinas2;
  double Angle, DAngle, D2Angle, Alpha;
  double lambda, Dlambda, D2lambda, aux;
  gp_Vec temp, dtemp, np2, dnp2, d2np2;
  int    i, jj;
  int    NbSpan = (Poles.Length() - 1) / 2;
  int    low    = Poles.Lower();
  int    upp    = Poles.Upper();

  Cosa = ns1.Dot(ns2);
  Sina = nplan.Dot(ns1.Crossed(ns2));

  if (Cosa < -1.)
  {
    Cosa = -1;
    Sina = 0;
  }
  if (Cosa > 1.)
  {
    Cosa = 1;
    Sina = 0;
  }
  Angle = std::acos(Cosa);

  if (Sina < 0.)
  {
    if (Cosa > 0.)
      Angle = -Angle;
    else
      Angle = 2. * M_PI - Angle;
  }

  if (std::abs(Sina) > std::abs(Cosa))
  {
    aux    = dn1w.Dot(ns2) + ns1.Dot(dn2w);
    DAngle = -aux / Sina;
    D2Angle =
      -(d2n1w.Dot(ns2) + 2 * dn1w.Dot(dn2w) + ns1.Dot(d2n2w)) / Sina
      + aux * (dnplan.Dot(ns1.Crossed(ns2)) + nplan.Dot(dn1w.Crossed(ns2) + ns1.Crossed(dn2w)))
          / (Sina * Sina);
  }
  else
  {
    temp    = dn1w.Crossed(ns2) + ns1.Crossed(dn2w);
    DAngle  = (dnplan.Dot(ns1.Crossed(ns2)) + nplan.Dot(temp)) / Cosa;
    D2Angle = (d2nplan.Dot(ns1.Crossed(ns2)) + 2 * dnplan.Dot(temp)
               + nplan.Dot(d2n1w.Crossed(ns2) + 2 * dn1w.Crossed(dn2w) + ns1.Crossed(d2n2w)))
                / Cosa
              - (dn1w.Dot(ns2) + ns1.Dot(dn2w)) * (dnplan.Dot(ns1.Crossed(ns2)) + nplan.Dot(temp))
                  / (Cosa * Cosa);
  }

  Poles(low)   = pts1;
  Poles(upp)   = pts2;
  Weights(low) = 1;
  Weights(upp) = 1;

  DPoles(low)   = tang1;
  DPoles(upp)   = tang2;
  DWeights(low) = 0;
  DWeights(upp) = 0;

  D2Poles(low)   = Dtang1;
  D2Poles(upp)   = Dtang2;
  D2Weights(low) = 0;
  D2Weights(upp) = 0;

  switch (TConv)
  {
    case Convert_QuasiAngular:
    {
      GeomFill_QuasiAngularConvertor QConvertor;
      QConvertor.Init();
      QConvertor.Section(pts1,
                         tang1,
                         Dtang1,
                         Center,
                         DCenter,
                         D2Center,
                         nplan,
                         dnplan,
                         d2nplan,
                         Angle,
                         DAngle,
                         D2Angle,
                         Poles,
                         DPoles,
                         D2Poles,
                         Weights,
                         DWeights,
                         D2Weights);
      return true;
    }
    case Convert_Polynomial:
    {
      GeomFill_PolynomialConvertor PConvertor;
      PConvertor.Init();
      PConvertor.Section(pts1,
                         tang1,
                         Dtang1,
                         Center,
                         DCenter,
                         D2Center,
                         nplan,
                         dnplan,
                         d2nplan,
                         Angle,
                         DAngle,
                         D2Angle,
                         Poles,
                         DPoles,
                         D2Poles);
      Weights.Init(1);
      DWeights.Init(0);
      D2Weights.Init(0);
      return true;
    }

    default:
    {
      np2   = nplan.Crossed(ns1);
      dnp2  = dnplan.Crossed(ns1).Added(nplan.Crossed(dn1w));
      d2np2 = d2nplan.Crossed(ns1).Added(nplan.Crossed(dn2w));
      d2np2 += 2 * dnplan.Crossed(dn1w);

      Alpha  = Angle / ((double)(NbSpan));
      Cosas2 = std::cos(Alpha / 2);
      Sinas2 = std::sin(Alpha / 2);

      for (i = 1, jj = low + 2; i <= NbSpan - 1; i++, jj += 2)
      {
        lambda = ((double)(i)) * Alpha;
        Cosa   = std::cos(lambda);
        Sina   = std::sin(lambda);
        temp.SetLinearForm(Cosa - 1, ns1, Sina, np2);
        Poles(jj).SetXYZ(pts1.XYZ() + Rayon * temp.XYZ());

        DPoles(jj).SetLinearForm(DRayon, temp, tang1);
        dtemp.SetLinearForm(-Sina, ns1, Cosa, np2);
        aux = ((double)(i)) / ((double)(NbSpan));
        dtemp.Multiply(aux * DAngle);
        dtemp.Add(((Cosa - 1) * dn1w).Added(Sina * dnp2));
        DPoles(jj) += Rayon * dtemp;

        D2Poles(jj).SetLinearForm(D2Rayon, temp, 2 * DRayon, dtemp, Dtang1);
        temp.SetLinearForm(Cosa - 1, dn2w, Sina, d2np2);
        dtemp.SetLinearForm(-Sina, ns1, Cosa, np2);
        temp += (aux * aux * D2Angle) * dtemp;
        dtemp.SetLinearForm(-Sina, dn1w + np2, Cosa, dnp2, -Cosa, ns1);
        temp += (aux * DAngle) * dtemp;
        D2Poles(jj) += Rayon * temp;
      }

      lambda   = 1. / (2. * Cosas2 * Cosas2);
      Dlambda  = (lambda * Sinas2 * DAngle) / (Cosas2 * NbSpan);
      aux      = Sinas2 / Cosas2;
      D2lambda = (Dlambda * aux * DAngle + D2Angle * aux * lambda
                  + (1 + aux * aux) * (DAngle / (2 * NbSpan)) * DAngle * lambda)
                 / NbSpan;
      for (i = 1, jj = low; i <= NbSpan; i++, jj += 2)
      {
        temp.SetXYZ(Poles(jj).XYZ() + Poles(jj + 2).XYZ() - 2. * Center.XYZ());
        Poles(jj + 1).SetXYZ(Center.XYZ() + lambda * temp.XYZ());

        dtemp.SetXYZ(DPoles(jj).XYZ() + DPoles(jj + 2).XYZ() - 2. * DCenter.XYZ());
        DPoles(jj + 1).SetLinearForm(Dlambda, temp, lambda, dtemp, DCenter);
        D2Poles(jj + 1).SetLinearForm(D2lambda,
                                      temp,
                                      2 * Dlambda,
                                      dtemp,
                                      lambda,
                                      (D2Poles(jj) + D2Poles(jj + 2)));
        D2Poles(jj + 1) += (1 - 2 * lambda) * D2Center;
      }

      Dlambda  = -Sinas2 * DAngle / (2 * NbSpan);
      D2lambda = -Sinas2 * D2Angle / (2 * NbSpan) - Cosas2 * std::pow(DAngle / (2 * NbSpan), 2);

      for (i = low; i < upp; i += 2)
      {
        Weights(i)       = 1.;
        Weights(i + 1)   = Cosas2;
        DWeights(i)      = 0.;
        DWeights(i + 1)  = Dlambda;
        D2Weights(i)     = 0.;
        D2Weights(i + 1) = D2lambda;
      }
    }
      return true;
  }
}
