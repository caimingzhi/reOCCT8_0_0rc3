#include <BSplCLib.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom_BSplineCurve.hpp>
#include <gp_Pnt2d.hpp>
#include <Hermit.hpp>
#include <Precision.hpp>
#include <Standard_DimensionError.hpp>
#include <Standard_Real.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_HArray1.hpp>

#include <algorithm>

static void HermiteCoeff(const occ::handle<Geom_BSplineCurve>& BS, NCollection_Array1<double>& TAB)

{
  NCollection_Array1<double> Knots(1, BS->NbKnots());
  NCollection_Array1<double> Weights(1, BS->NbPoles());
  NCollection_Array1<int>    Mults(1, BS->NbKnots());

  int    Degree, Index0, Index1;
  double Denom0, Denom1, Deriv0, Deriv1;

  bool Periodic;

  BS->Knots(Knots);
  BSplCLib::Reparametrize(0.0, 1.0, Knots);
  BS->Weights(Weights);
  BS->Multiplicities(Mults);
  Degree   = BS->Degree();
  Periodic = BS->IsPeriodic();
  Index0   = BS->FirstUKnotIndex();
  Index1   = BS->LastUKnotIndex() - 1;

  BSplCLib::D1(0.0,
               Index0,
               Degree,
               Periodic,
               Weights,
               BSplCLib::NoWeights(),
               Knots,
               &Mults,
               Denom0,
               Deriv0);
  BSplCLib::D1(1.0,
               Index1,
               Degree,
               Periodic,
               Weights,
               BSplCLib::NoWeights(),
               Knots,
               &Mults,
               Denom1,
               Deriv1);
  TAB(0) = 1 / Denom0;
  TAB(1) = -Deriv0 / (Denom0 * Denom0);
  TAB(2) = -Deriv1 / (Denom1 * Denom1);
  TAB(3) = 1 / Denom1;
}

static void HermiteCoeff(const occ::handle<Geom2d_BSplineCurve>& BS,
                         NCollection_Array1<double>&             TAB)

{
  NCollection_Array1<double> Knots(1, BS->NbKnots());
  NCollection_Array1<double> Weights(1, BS->NbPoles());
  NCollection_Array1<int>    Mults(1, BS->NbKnots());
  int                        Degree, Index0, Index1;
  double                     Denom0, Denom1,

    Deriv0, Deriv1;
  bool Periodic;

  BS->Knots(Knots);
  BSplCLib::Reparametrize(0.0, 1.0, Knots);
  BS->Weights(Weights);
  BS->Multiplicities(Mults);
  Degree   = BS->Degree();
  Periodic = BS->IsPeriodic();
  Index0   = BS->FirstUKnotIndex();
  Index1   = BS->LastUKnotIndex() - 1;

  BSplCLib::D1(0.0,
               Index0,
               Degree,
               Periodic,
               Weights,
               BSplCLib::NoWeights(),
               Knots,
               &Mults,
               Denom0,
               Deriv0);
  BSplCLib::D1(1.0,
               Index1,
               Degree,
               Periodic,
               Weights,
               BSplCLib::NoWeights(),
               Knots,
               &Mults,
               Denom1,
               Deriv1);
  TAB(0) = 1 / Denom0;
  TAB(1) = -Deriv0 / (Denom0 * Denom0);
  TAB(2) = -Deriv1 / (Denom1 * Denom1);
  TAB(3) = 1 / Denom1;
}

static bool SignDenom(const NCollection_Array1<gp_Pnt2d>& Poles)

{
  bool Result;

  Result = Poles(0).Y() >= 0;
  return Result;
}

static void Polemax(const NCollection_Array1<gp_Pnt2d>& Poles, int& min, int& max)

{

  int i;

  double Max, Min;
  min = 0;
  max = 0;

  Min = Poles(0).Y();

  Max = Poles(0).Y();
  for (i = 1; i <= (Poles.Length() - 1); i++)
  {
    if (Poles(i).Y() < Min)
    {
      Min = Poles(i).Y();
      min = i;
    }
    if (Poles(i).Y() > Max)
    {
      Max = Poles(i).Y();
      max = i;
    }
  }
}

static void PolyTest(const NCollection_Array1<double>&     Herm,
                     const occ::handle<Geom_BSplineCurve>& BS,
                     double&                               U4,
                     double&                               U5,
                     int&                                  boucle,
                     const double                          TolPoles,

                     const double,
                     const double Ux,
                     const double Uy)

{
  int                          index, i, I1 = 0, I2 = 0, I3 = 0, I4 = 0;
  NCollection_Array1<gp_Pnt2d> Polesinit(0, 3);

  occ::handle<NCollection_HArray1<double>> Knots;
  int                                      cas = 0, mark = 0, dercas = 0, min, max;
  double                                   Us1, Us2, a;

  U4 = 0.0;
  U5 = 1.0;
  if (Ux != 1.0)
  {
    BS->LocateU(Ux, 0.0, I1, I2);
    if (Uy != 0.0)
      BS->LocateU(Uy, 0.0, I3, I4);
  }

  if (I1 == I2)
    if ((I3 == I4) || (I3 == 0))
    {
      Knots = new NCollection_HArray1<double>(1, BS->NbKnots());
      for (i = 1; i <= BS->NbKnots(); i++)
        Knots->SetValue(i, BS->Knot(i));
    }
    else
    {
      Knots = new NCollection_HArray1<double>(1, BS->NbKnots() + 1);
      for (i = 1; i <= BS->NbKnots(); i++)
        Knots->SetValue(i, BS->Knot(i));
      Knots->SetValue(BS->NbKnots() + 1, Uy);
    }
  else
  {
    if ((I3 == I4) || (I3 == 0))
    {
      Knots = new NCollection_HArray1<double>(1, BS->NbKnots() + 1);
      for (i = 1; i <= BS->NbKnots(); i++)
        Knots->SetValue(i, BS->Knot(i));
      Knots->SetValue(BS->NbKnots() + 1, Ux);
    }
    else
    {
      Knots = new NCollection_HArray1<double>(1, BS->NbKnots() + 2);
      for (i = 1; i <= BS->NbKnots(); i++)
        Knots->SetValue(i, BS->Knot(i));
      Knots->SetValue(BS->NbKnots() + 1, Ux);
      Knots->SetValue(BS->NbKnots() + 2, Uy);
    }
  }

  NCollection_Array1<double> knots(1, Knots->Length());
  knots = Knots->ChangeArray1();

  std::sort(knots.begin(), knots.end());

  Polesinit(0).SetCoord(0.0, Herm(0));

  Polesinit(1).SetCoord(0.0, Herm(0) + Herm(1) / 3.0);
  Polesinit(2).SetCoord(0.0, Herm(3) - Herm(2) / 3.0);
  Polesinit(3).SetCoord(0.0, Herm(3));

  if (TolPoles != 0.0)
  {
    Polemax(Polesinit, min, max);
    double Polemin = Polesinit(min).Y();
    double Polemax = Polesinit(max).Y();
    if (((Polemax) >= ((1 / TolPoles) * Polemin))
        || ((Polemin == 0.0) && (Polemax >= (1 / TolPoles))))
    {
      if (Polesinit(0).Y() >= (1 / TolPoles) * Polesinit(3).Y()
          || Polesinit(0).Y() <= TolPoles * Polesinit(3).Y())
        throw Standard_DimensionError("Hermit Impossible Tolerance");
      if ((max == 0) || (max == 3))
      {
        for (i = 0; i <= 3; i++)
          Polesinit(i).SetCoord(0.0, (Polesinit(i).Y() - TolPoles * Polemax));
      }
      else if ((max == 1) || (max == 2))
      {
        if ((min == 0) || (min == 3))
        {
          for (i = 0; i <= 3; i++)
            Polesinit(i).SetCoord(0.0, (Polesinit(i).Y() - (1 / TolPoles) * Polemin));
        }
        else
        {
          if ((TolPoles * Polemax < Polesinit(0).Y()) && (TolPoles * Polemax < Polesinit(3).Y()))
          {
            for (i = 0; i <= 3; i++)
              Polesinit(i).SetCoord(0.0, (Polesinit(i).Y() - TolPoles * Polemax));
            mark = 1;
          }
          if ((1 / TolPoles * Polemin > Polesinit(0).Y())
              && (1 / TolPoles * Polemin > Polesinit(3).Y()) && (mark == 0))
          {
            for (i = 0; i <= 3; i++)
              Polesinit(i).SetCoord(0.0, (Polesinit(i).Y() - 1 / TolPoles * Polemin));
            mark = 1;
          }
          if (mark == 0)
          {
            double Pole0, Pole3;
            Pole0 = Polesinit(0).Y();
            Pole3 = Polesinit(3).Y();
            if (Pole0 < 3)
            {
              a = std::log10(Pole3 / Pole0);
              if (boucle == 2)
              {
                for (i = 0; i <= 3; i++)
                  Polesinit(i).SetCoord(
                    0.0,
                    Polesinit(i).Y()
                      - (Pole3 * (std::pow(10.0, (-0.5 * std::log10(TolPoles) - a / 2.0)))));
              }
              if (boucle == 1)
              {
                for (i = 0; i <= 3; i++)
                  Polesinit(i).SetCoord(
                    0.0,
                    Polesinit(i).Y()
                      - (Pole0 * (std::pow(10.0, (a / 2.0 + 0.5 * std::log10(TolPoles))))));
                dercas = 1;
              }
            }
            if (Pole0 > Pole3)
            {
              a = std::log10(Pole0 / Pole3);
              if (boucle == 2)
              {
                for (i = 0; i <= 3; i++)
                  Polesinit(i).SetCoord(
                    0.0,
                    Polesinit(i).Y()
                      - (Pole0 * (std::pow(10.0, (-0.5 * std::log10(TolPoles) - a / 2.0)))));
              }
              if (boucle == 1)
              {
                for (i = 0; i <= 3; i++)
                  Polesinit(i).SetCoord(
                    0.0,
                    Polesinit(i).Y()
                      - (Pole3 * (std::pow(10.0, (a / 2.0 + 0.5 * std::log10(TolPoles))))));
                dercas = 1;
              }
            }
          }
        }
      }
    }
  }

  if (!SignDenom(Polesinit))
  {
    for (index = 0; index <= 3; index++)
      Polesinit(index).SetCoord(0.0, -Polesinit(index).Y());
  }

  if ((Polesinit(1).Y() < 0.0) && (Polesinit(2).Y() >= 0.0))
  {
    Us1 = Polesinit(0).Y() / (Polesinit(0).Y() - Polesinit(1).Y());
    if (boucle == 2)
      Us1 = Us1 * knots(2);
    if (boucle == 1)
      if (Ux != 0.0)
        Us1 = Us1 * Ux;
    BSplCLib::LocateParameter(3, knots, Us1, false, 1, knots.Length(), I1, Us1);
    if (I1 < 2)
      U4 = Us1;
    else
      U4 = knots(I1);
  }

  if ((Polesinit(1).Y() >= 0.0) && (Polesinit(2).Y() < 0.0))
  {
    Us2 = Polesinit(2).Y() / (Polesinit(2).Y() - Polesinit(3).Y());
    if (boucle == 2)
      Us2 = knots(knots.Length() - 1) + Us2 * (1 - knots(knots.Length() - 1));
    if (boucle == 1)
      if (Ux != 0.0)
        Us2 = Uy + Us2 * (1 - Uy);
    BSplCLib::LocateParameter(3, knots, Us2, false, 1, knots.Length(), I1, Us2);
    if (I1 >= (knots.Length() - 1))
      U5 = Us2;
    else
      U5 = knots(I1 + 1);
  }

  if (dercas == 1)
    boucle++;

  if ((Polesinit(1).Y() < 0.0) && (Polesinit(2).Y() < 0.0))
  {
    Us1 = Polesinit(0).Y() / (Polesinit(0).Y() - Polesinit(1).Y());
    Us2 = Polesinit(2).Y() / (Polesinit(2).Y() - Polesinit(3).Y());
    if (boucle != 0)
      if (Ux != 0.0)
      {
        Us1 = Us1 * Ux;
        Us2 = Uy + Us2 * (1 - Uy);
      }
    if (Us2 <= Us1)
    {
      BSplCLib::LocateParameter(3, knots, Us1, false, 1, knots.Length(), I1, Us1);
      if (knots(I1) >= Us2)
        U4 = knots(I1);
      else
      {
        if (I1 >= 2)
        {
          U4 = knots(I1);
          BSplCLib::LocateParameter(3, knots, Us2, false, 1, knots.Length(), I3, Us2);
          if (I3 < (BS->NbKnots() - 1))
          {
            U5  = knots(I3 + 1);
            cas = 1;
          }
        }
        if (cas == 0)
          U4 = (Us1 + Us2) / 2;
      }
    }
    else
    {
      BSplCLib::LocateParameter(3, knots, Us1, false, 1, knots.Length(), I1, Us1);
      if (I1 >= 2)
        U4 = knots(I1);
      else
        U4 = Us1;
      BSplCLib::LocateParameter(3, knots, Us2, false, 1, knots.Length(), I3, Us2);
      if (I3 < (BS->NbKnots() - 1))
        U5 = knots(I3 + 1);
      else
        U5 = Us2;
    }
  }
}

static void PolyTest(const NCollection_Array1<double>&       Herm,
                     const occ::handle<Geom2d_BSplineCurve>& BS,
                     double&                                 U4,
                     double&                                 U5,
                     int&                                    boucle,
                     const double                            TolPoles,

                     const double,
                     const double Ux,
                     const double Uy)

{
  int                          index, i, I1 = 0, I2 = 0, I3 = 0, I4 = 0;
  NCollection_Array1<gp_Pnt2d> Polesinit(0, 3);

  occ::handle<NCollection_HArray1<double>> Knots;
  int                                      cas = 0, mark = 0, dercas = 0, min, max;
  double                                   Us1, Us2, a;

  U4 = 0.0;
  U5 = 1.0;
  if (Ux != 1.0)
  {
    BS->LocateU(Ux, 0.0, I1, I2);
    if (Uy != 0.0)
      BS->LocateU(Uy, 0.0, I3, I4);
  }

  if (I1 == I2)
  {
    if ((I3 == I4) || (I3 == 0))
    {
      Knots = new NCollection_HArray1<double>(1, BS->NbKnots());
      for (i = 1; i <= BS->NbKnots(); i++)
        Knots->SetValue(i, BS->Knot(i));
    }
    else
    {
      Knots = new NCollection_HArray1<double>(1, BS->NbKnots() + 1);
      for (i = 1; i <= BS->NbKnots(); i++)
        Knots->SetValue(i, BS->Knot(i));
      Knots->SetValue(BS->NbKnots() + 1, Uy);
    }
  }
  else
  {
    if ((I3 == I4) || (I3 == 0))
    {
      Knots = new NCollection_HArray1<double>(1, BS->NbKnots() + 1);
      for (i = 1; i <= BS->NbKnots(); i++)
        Knots->SetValue(i, BS->Knot(i));
      Knots->SetValue(BS->NbKnots() + 1, Ux);
    }
    else
    {
      Knots = new NCollection_HArray1<double>(1, BS->NbKnots() + 2);
      for (i = 1; i <= BS->NbKnots(); i++)
        Knots->SetValue(i, BS->Knot(i));
      Knots->SetValue(BS->NbKnots() + 1, Ux);
      Knots->SetValue(BS->NbKnots() + 2, Uy);
    }
  }

  NCollection_Array1<double> knots(1, Knots->Length());
  knots = Knots->ChangeArray1();

  std::sort(knots.begin(), knots.end());

  Polesinit(0).SetCoord(0.0, Herm(0));

  Polesinit(1).SetCoord(0.0, Herm(0) + Herm(1) / 3.0);
  Polesinit(2).SetCoord(0.0, Herm(3) - Herm(2) / 3.0);
  Polesinit(3).SetCoord(0.0, Herm(3));

  if (TolPoles != 0.0)
  {
    Polemax(Polesinit, min, max);
    double Polemin = Polesinit(min).Y();
    double Polemax = Polesinit(max).Y();
    if (((Polemax) >= ((1 / TolPoles) * Polemin))
        || ((Polemin == 0.0) && (Polemax >= (1 / TolPoles))))
    {
      if (Polesinit(0).Y() >= (1 / TolPoles) * Polesinit(3).Y()
          || Polesinit(0).Y() <= TolPoles * Polesinit(3).Y())
        throw Standard_DimensionError("Hermit Impossible Tolerance");
      if ((max == 0) || (max == 3))
      {
        for (i = 0; i <= 3; i++)
          Polesinit(i).SetCoord(0.0, (Polesinit(i).Y() - TolPoles * Polemax));
      }
      else if ((max == 1) || (max == 2))
      {
        if ((min == 0) || (min == 3))
        {
          for (i = 0; i <= 3; i++)
            Polesinit(i).SetCoord(0.0, (Polesinit(i).Y() - (1 / TolPoles) * Polemin));
        }
        else
        {
          if ((TolPoles * Polemax < Polesinit(0).Y()) && (TolPoles * Polemax < Polesinit(3).Y()))
          {
            for (i = 0; i <= 3; i++)
              Polesinit(i).SetCoord(0.0, (Polesinit(i).Y() - TolPoles * Polemax));
            mark = 1;
          }

          if ((1 / TolPoles * Polemin > Polesinit(0).Y())
              && (1 / TolPoles * Polemin > Polesinit(3).Y()) && (mark == 0))
          {
            for (i = 0; i <= 3; i++)
              Polesinit(i).SetCoord(0.0, (Polesinit(i).Y() - 1 / TolPoles * Polemin));
            mark = 1;
          }
          if (mark == 0)
          {
            double Pole0, Pole3;
            Pole0 = Polesinit(0).Y();
            Pole3 = Polesinit(3).Y();
            if (Pole0 < 3)
            {
              a = std::log10(Pole3 / Pole0);
              if (boucle == 2)
              {
                for (i = 0; i <= 3; i++)
                  Polesinit(i).SetCoord(
                    0.0,
                    Polesinit(i).Y()
                      - (Pole3 * (std::pow(10.0, (-0.5 * std::log10(TolPoles) - a / 2.0)))));
              }
              if (boucle == 1)
              {
                for (i = 0; i <= 3; i++)
                  Polesinit(i).SetCoord(
                    0.0,
                    Polesinit(i).Y()
                      - (Pole0 * (std::pow(10.0, (a / 2.0 + 0.5 * std::log10(TolPoles))))));
                dercas = 1;
              }
            }
            if (Pole0 > Pole3)
            {
              a = std::log10(Pole0 / Pole3);
              if (boucle == 2)
              {
                for (i = 0; i <= 3; i++)
                  Polesinit(i).SetCoord(
                    0.0,
                    Polesinit(i).Y()
                      - (Pole0 * (std::pow(10.0, (-0.5 * std::log10(TolPoles) - a / 2.0)))));
              }
              else if (boucle == 1)
              {
                for (i = 0; i <= 3; i++)
                  Polesinit(i).SetCoord(
                    0.0,
                    Polesinit(i).Y()
                      - (Pole3 * (std::pow(10.0, (a / 2.0 + 0.5 * std::log10(TolPoles))))));
                dercas = 1;
              }
            }
          }
        }
      }
    }
  }

  if (!SignDenom(Polesinit))
  {
    for (index = 0; index <= 3; index++)
      Polesinit(index).SetCoord(0.0, -Polesinit(index).Y());
  }

  if ((Polesinit(1).Y() < 0.0) && (Polesinit(2).Y() >= 0.0))
  {
    Us1 = Polesinit(0).Y() / (Polesinit(0).Y() - Polesinit(1).Y());
    if (boucle == 2)
      Us1 = Us1 * knots(2);
    if (boucle == 1)
      if (Ux != 0.0)
        Us1 = Us1 * Ux;
    BSplCLib::LocateParameter(3, knots, Us1, false, 1, knots.Length(), I1, Us1);
    if (I1 < 2)
      U4 = Us1;
    else
      U4 = knots(I1);
  }

  if ((Polesinit(1).Y() >= 0.0) && (Polesinit(2).Y() < 0.0))
  {
    Us2 = Polesinit(2).Y() / (Polesinit(2).Y() - Polesinit(3).Y());
    if (boucle == 2)
      Us2 = knots(knots.Length() - 1) + Us2 * (1 - knots(knots.Length() - 1));
    if (boucle == 1)
      if (Ux != 0.0)
        Us2 = Uy + Us2 * (1 - Uy);
    BSplCLib::LocateParameter(3, knots, Us2, false, 1, knots.Length(), I1, Us2);
    if (I1 >= (knots.Length() - 1))
      U5 = Us2;
    else
      U5 = knots(I1 + 1);
  }

  if (dercas == 1)
    boucle++;

  if ((Polesinit(1).Y() < 0.0) && (Polesinit(2).Y() < 0.0))
  {
    Us1 = Polesinit(0).Y() / (Polesinit(0).Y() - Polesinit(1).Y());
    Us2 = Polesinit(2).Y() / (Polesinit(2).Y() - Polesinit(3).Y());
    if (boucle != 0)
      if (Ux != 0.0)
      {
        Us1 = Us1 * Ux;
        Us2 = Uy + Us2 * (1 - Uy);
      }
    if (Us2 <= Us1)
    {
      BSplCLib::LocateParameter(3, knots, Us1, false, 1, knots.Length(), I1, Us1);
      if (knots(I1) >= Us2)
        U4 = knots(I1);
      else
      {
        if (I1 >= 2)
        {
          U4 = knots(I1);
          BSplCLib::LocateParameter(3, knots, Us2, false, 1, knots.Length(), I3, Us2);
          if (I3 < (BS->NbKnots() - 1))
          {
            U5  = knots(I3 + 1);
            cas = 1;
          }
        }
        if (cas == 0)
          U4 = (Us1 + Us2) / 2;
      }
    }
    else
    {
      BSplCLib::LocateParameter(3, knots, Us1, false, 1, knots.Length(), I1, Us1);
      if (I1 >= 2)
        U4 = knots(I1);
      else
        U4 = Us1;
      BSplCLib::LocateParameter(3, knots, Us2, false, 1, knots.Length(), I3, Us2);
      if (I3 < (BS->NbKnots() - 1))
        U5 = knots(I3 + 1);
      else
        U5 = Us2;
    }
  }
}

static void InsertKnots(occ::handle<Geom2d_BSplineCurve>& BS, const double U4, const double U5)

{
  if (U4 != 0.0)
    BS->InsertKnot(U4);
  if ((U5 != 1.0) && (U5 != U4))
    BS->InsertKnot(U5);
}

static void MovePoles(occ::handle<Geom2d_BSplineCurve>& BS)

{
  gp_Pnt2d P;

  int i;

  for (i = 3; i <= (BS->NbPoles() - 2); i++)
  {
    P.SetCoord(1, (BS->Pole(i).Coord(1)));
    P.SetCoord(2, (BS->Pole(1).Coord(2)));
    BS->SetPole(i, P);
  }
}

occ::handle<Geom2d_BSplineCurve> Hermit::Solution(const occ::handle<Geom_BSplineCurve>& BS,
                                                  const double                          TolPoles,
                                                  const double                          TolKnots)

{
  NCollection_Array1<double> Herm(0, 3);
  double Upos1 = 0.0, Upos2 = 1.0, Ux = 0.0, Uy = 1.0, Utol1 = 0.0, Utol2 = 1.0, Uint1 = 0.0,
         Uint2                        = 1.0;
  int                          boucle = 1;
  NCollection_Array1<double>   Knots(1, 2);
  NCollection_Array1<int>      Multiplicities(1, 2);
  NCollection_Array1<gp_Pnt2d> Poles(1, 4);
  int                          zeroboucle = 0;
  HermiteCoeff(BS, Herm);

  Poles(1).SetCoord(0.0, Herm(0));
  Poles(2).SetCoord(0.0, Herm(0) + Herm(1) / 3.0);
  Poles(3).SetCoord(0.0, Herm(3) - Herm(2) / 3.0);
  Poles(4).SetCoord(0.0, Herm(3));
  Knots(1)          = 0.0;
  Knots(2)          = 1.0;
  Multiplicities(1) = 4;
  Multiplicities(2) = 4;

  occ::handle<Geom2d_BSplineCurve> BS1 = new Geom2d_BSplineCurve(Poles, Knots, Multiplicities, 3);
  occ::handle<Geom2d_BSplineCurve> BS2 = new Geom2d_BSplineCurve(Poles, Knots, Multiplicities, 3);

  PolyTest(Herm,
           BS,
           Upos1,
           Upos2,
           zeroboucle,
           Precision::Confusion(),
           Precision::Confusion(),
           1.0,
           0.0);

  InsertKnots(BS2, Upos1, Upos2);

  if (Upos1 != 0.0)
    if (Upos2 != 1.0)
    {
      Ux = std::min(Upos1, Upos2);
      Uy = std::max(Upos1, Upos2);
    }
    else
    {
      Ux = Upos1;
      Uy = Upos1;
    }
  else
  {
    Ux = Upos2;
    Uy = Upos2;
  }

  Herm(0) = BS2->Pole(1).Y();
  Herm(1) = 3 * (BS2->Pole(2).Y() - BS2->Pole(1).Y());
  Herm(2) = 3 * (BS2->Pole(BS2->NbPoles()).Y() - BS2->Pole(BS2->NbPoles() - 1).Y());
  Herm(3) = BS2->Pole(BS2->NbPoles()).Y();

  PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Ux, Uy);

  InsertKnots(BS2, Utol1, Utol2);

  if (boucle == 2)
  {
    Herm(0) = BS2->Pole(1).Y();
    Herm(1) = 3 * (BS2->Pole(2).Y() - BS2->Pole(1).Y());
    Herm(2) = 3 * (BS2->Pole(BS2->NbPoles()).Y() - BS2->Pole(BS2->NbPoles() - 1).Y());
    Herm(3) = BS2->Pole(BS2->NbPoles()).Y();
    if (Utol1 == 0.0)
    {
      Uint2 = Utol2;
      PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Uint2, 0.0);
    }
    else
    {
      Uint1 = Utol1;
      PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Uint1, 0.0);
    }
    InsertKnots(BS2, Utol1, Utol2);
  }
  if ((BS2->Knot(2) < TolKnots) || (BS2->Knot(BS2->NbKnots() - 1) > (1 - TolKnots)))
    throw Standard_DimensionError("Hermit Impossible Tolerance");
  else
  {
    if ((Upos2 == 1.0) && (Utol2 == 1.0) && (Uint2 == 1.0))
      InsertKnots(BS1, BS2->Knot(2), 1.0);
    else
    {
      if ((Upos1 == 0.0) && (Utol1 == 0.0) && (Uint1 == 0.0))
        InsertKnots(BS1, BS2->Knot(BS2->NbKnots() - 1), 1.0);
      else
        InsertKnots(BS1, BS2->Knot(BS2->NbKnots() - 1), BS2->Knot(2));
    }
    MovePoles(BS1);
  }
  return BS1;
}

occ::handle<Geom2d_BSplineCurve> Hermit::Solution(const occ::handle<Geom2d_BSplineCurve>& BS,
                                                  const double                            TolPoles,
                                                  const double                            TolKnots)

{
  NCollection_Array1<double> Herm(0, 3);
  double Upos1 = 0.0, Upos2 = 1.0, Ux = 0.0, Uy = 1.0, Utol1 = 0.0, Utol2 = 1.0, Uint1 = 0.0,
         Uint2                        = 1.0;
  int                          boucle = 1;
  NCollection_Array1<double>   Knots(1, 2);
  NCollection_Array1<int>      Multiplicities(1, 2);
  NCollection_Array1<gp_Pnt2d> Poles(1, 4);
  int                          zeroboucle = 0;
  HermiteCoeff(BS, Herm);

  Poles(1).SetCoord(0.0, Herm(0));
  Poles(2).SetCoord(0.0, Herm(0) + Herm(1) / 3.0);
  Poles(3).SetCoord(0.0, Herm(3) - Herm(2) / 3.0);
  Poles(4).SetCoord(0.0, Herm(3));
  Knots(1)          = 0.0;
  Knots(2)          = 1.0;
  Multiplicities(1) = 4;
  Multiplicities(2) = 4;

  occ::handle<Geom2d_BSplineCurve> BS1 = new Geom2d_BSplineCurve(Poles, Knots, Multiplicities, 3);
  occ::handle<Geom2d_BSplineCurve> BS2 = new Geom2d_BSplineCurve(Poles, Knots, Multiplicities, 3);

  PolyTest(Herm,
           BS,
           Upos1,
           Upos2,
           zeroboucle,
           Precision::Confusion(),
           Precision::Confusion(),
           1.0,
           0.0);

  InsertKnots(BS2, Upos1, Upos2);

  if (Upos1 != 0.0)
    if (Upos2 != 1.0)
    {
      Ux = std::min(Upos1, Upos2);
      Uy = std::max(Upos1, Upos2);
    }
    else
    {
      Ux = Upos1;
      Uy = Upos1;
    }
  else
  {
    Ux = Upos2;
    Uy = Upos2;
  }

  Herm(0) = BS2->Pole(1).Y();
  Herm(1) = 3 * (BS2->Pole(2).Y() - BS2->Pole(1).Y());
  Herm(2) = 3 * (BS2->Pole(BS2->NbPoles()).Y() - BS2->Pole(BS2->NbPoles() - 1).Y());
  Herm(3) = BS2->Pole(BS2->NbPoles()).Y();

  PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Ux, Uy);

  InsertKnots(BS2, Utol1, Utol2);

  if (boucle == 2)
  {
    Herm(0) = BS2->Pole(1).Y();
    Herm(1) = 3 * (BS2->Pole(2).Y() - BS2->Pole(1).Y());
    Herm(2) = 3 * (BS2->Pole(BS2->NbPoles()).Y() - BS2->Pole(BS2->NbPoles() - 1).Y());
    Herm(3) = BS2->Pole(BS2->NbPoles()).Y();
    if (Utol1 == 0.0)
    {
      Uint2 = Utol2;
      PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Uint2, 0.0);
    }
    else
    {
      Uint1 = Utol1;
      PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Uint1, 0.0);
    }
    InsertKnots(BS2, Utol1, Utol2);
  }
  if ((BS2->Knot(2) < TolKnots) || (BS2->Knot(BS2->NbKnots() - 1) > (1 - TolKnots)))
    throw Standard_DimensionError("Hermit Impossible Tolerance");
  else
  {
    if ((Upos2 == 1.0) && (Utol2 == 1.0) && (Uint2 == 1.0))
      InsertKnots(BS1, BS2->Knot(2), 1.0);
    else
    {
      if ((Upos1 == 0.0) && (Utol1 == 0.0) && (Uint1 == 0.0))
        InsertKnots(BS1, BS2->Knot(BS2->NbKnots() - 1), 1.0);
      else
        InsertKnots(BS1, BS2->Knot(BS2->NbKnots() - 1), BS2->Knot(2));
    }
    MovePoles(BS1);
  }
  return BS1;
}

void Hermit::Solutionbis(const occ::handle<Geom_BSplineCurve>& BS,
                         double&                               Knotmin,
                         double&                               Knotmax,
                         const double                          TolPoles,
                         const double                          TolKnots)

{
  NCollection_Array1<double> Herm(0, 3);
  double Upos1 = 0.0, Upos2 = 1.0, Ux = 0.0, Uy = 1.0, Utol1 = 0.0, Utol2 = 1.0, Uint1 = 0.0,
         Uint2                        = 1.0;
  int                          boucle = 1;
  NCollection_Array1<double>   Knots(1, 2);
  NCollection_Array1<int>      Multiplicities(1, 2);
  NCollection_Array1<gp_Pnt2d> Poles(1, 4);
  int                          zeroboucle = 0;
  HermiteCoeff(BS, Herm);

  Poles(1).SetCoord(0.0, Herm(0));
  Poles(2).SetCoord(0.0, Herm(0) + Herm(1) / 3.0);
  Poles(3).SetCoord(0.0, Herm(3) - Herm(2) / 3.0);
  Poles(4).SetCoord(0.0, Herm(3));
  Knots(1)          = 0.0;
  Knots(2)          = 1.0;
  Multiplicities(1) = 4;
  Multiplicities(2) = 4;

  occ::handle<Geom2d_BSplineCurve> BS2 = new Geom2d_BSplineCurve(Poles, Knots, Multiplicities, 3);

  PolyTest(Herm,
           BS,
           Upos1,
           Upos2,
           zeroboucle,
           Precision::Confusion(),
           Precision::Confusion(),
           1.0,
           0.0);

  InsertKnots(BS2, Upos1, Upos2);

  if (Upos1 != 0.0)
    if (Upos2 != 1.0)
    {
      Ux = std::min(Upos1, Upos2);
      Uy = std::max(Upos1, Upos2);
    }
    else
    {
      Ux = Upos1;
      Uy = Upos1;
    }
  else
  {
    Ux = Upos2;
    Uy = Upos2;
  }

  Herm(0) = BS2->Pole(1).Y();
  Herm(1) = 3 * (BS2->Pole(2).Y() - BS2->Pole(1).Y());
  Herm(2) = 3 * (BS2->Pole(BS2->NbPoles()).Y() - BS2->Pole(BS2->NbPoles() - 1).Y());
  Herm(3) = BS2->Pole(BS2->NbPoles()).Y();

  PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Ux, Uy);

  InsertKnots(BS2, Utol1, Utol2);

  if (boucle == 2)
  {
    Herm(0) = BS2->Pole(1).Y();
    Herm(1) = 3 * (BS2->Pole(2).Y() - BS2->Pole(1).Y());
    Herm(2) = 3 * (BS2->Pole(BS2->NbPoles()).Y() - BS2->Pole(BS2->NbPoles() - 1).Y());
    Herm(3) = BS2->Pole(BS2->NbPoles()).Y();
    if (Utol1 == 0.0)
    {
      Uint2 = Utol2;
      PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Uint2, 0.0);
    }
    else
    {
      Uint1 = Utol1;
      PolyTest(Herm, BS, Utol1, Utol2, boucle, TolPoles, TolKnots, Uint1, 0.0);
    }
    InsertKnots(BS2, Utol1, Utol2);
  }
  if ((BS2->Knot(2) < TolKnots) || (BS2->Knot(BS2->NbKnots() - 1) > (1 - TolKnots)))
    throw Standard_DimensionError("Hermit Impossible Tolerance");
  else
  {
    if ((Upos2 == 1.0) && (Utol2 == 1.0) && (Uint2 == 1.0))
      Knotmin = BS2->Knot(2);
    else
    {
      if ((Upos1 == 0.0) && (Utol1 == 0.0) && (Uint1 == 0.0))
        Knotmax = BS2->Knot(BS2->NbKnots() - 1);
      else
      {
        Knotmin = BS2->Knot(2);
        Knotmax = BS2->Knot(BS2->NbKnots() - 1);
      }
    }
  }
}
