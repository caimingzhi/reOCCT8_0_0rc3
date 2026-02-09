#include <Convert_PolynomialCosAndSin.hpp>

#include <gp_Trsf2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_XY.hpp>

#include <gp.hpp>
#include <Precision.hpp>
#include <BSplCLib.hpp>

static double Locate(const double                        Angfin,
                     const NCollection_Array1<gp_Pnt2d>& TPoles,
                     const double                        Umin,
                     const double                        Umax)
{
  double umin = Umin;
  double umax = Umax;
  double Ptol = Precision::Angular();
  double Utol = Precision::PConfusion();
  while (std::abs(umax - umin) >= Utol)
  {
    double   ptest = (umax + umin) / 2.;
    gp_Pnt2d valP;
    BSplCLib::D0(ptest, TPoles, BSplCLib::NoWeights(), valP);
    double theta = std::atan2(valP.Y(), valP.X());
    if (theta < 0.)
    {
      theta += 2. * M_PI;
    }
    if (std::abs(theta - Angfin) < Ptol)
    {
      return ptest;
    }
    if (theta < Angfin)
    {
      umin = ptest;
    }
    else if (theta > Angfin)
    {
      umax = ptest;
    }
  }
  return (umin + umax) / 2.;
}

void BuildPolynomialCosAndSin(const double                              UFirst,
                              const double                              ULast,
                              const int                                 num_poles,
                              occ::handle<NCollection_HArray1<double>>& CosNumeratorPtr,
                              occ::handle<NCollection_HArray1<double>>& SinNumeratorPtr,
                              occ::handle<NCollection_HArray1<double>>& DenominatorPtr)
{

  double Delta, locUFirst,

    t_min, t_max, trim_min, trim_max, middle, Angle, PI2 = 2 * M_PI;
  int ii, degree = num_poles - 1;
  locUFirst = UFirst;

  while (locUFirst > PI2)
  {
    locUFirst -= PI2;
  }
  while (locUFirst < -PI2)
  {
    locUFirst += PI2;
  }

  Delta  = ULast - UFirst;
  middle = 0.5e0 * Delta;

  Angle = middle - M_PI;

  NCollection_Array1<gp_Pnt2d> TPoles(1, 8), NewTPoles(1, 8);
  TPoles(1).SetCoord(1., 0.);
  TPoles(2).SetCoord(1., 1.013854);
  TPoles(3).SetCoord(-0.199043, 1.871905);
  TPoles(4).SetCoord(-1.937729, 1.057323);
  TPoles(5).SetCoord(-1.937729, -1.057323);
  TPoles(6).SetCoord(-0.199043, -1.871905);
  TPoles(7).SetCoord(1., -1.013854);
  TPoles(8).SetCoord(1., 0.);
  gp_Trsf2d T;
  T.SetRotation(gp::Origin2d(), Angle);
  for (ii = 1; ii <= num_poles; ii++)
  {
    TPoles(ii).Transform(T);
  }

  t_min = 1.0e0 - (Delta * 1.3e0 / M_PI);
  t_min *= 0.5e0;
  t_min = std::max(t_min, 0.0e0);
  t_max = 1.0e0 + (Delta * 1.3e0 / M_PI);
  t_max *= 0.5e0;
  t_max    = std::min(t_max, 1.0e0);
  trim_max = Locate(Delta, TPoles, t_min, t_max);

  trim_min = 1.0e0 - trim_max;

  double knot_array[2];
  int    mults_array[2];
  knot_array[0]  = 0.0e0;
  knot_array[1]  = 1.0e0;
  mults_array[0] = degree + 1;
  mults_array[1] = degree + 1;

  NCollection_Array1<double> the_knots(knot_array[0], 1, 2), the_new_knots(knot_array[0], 1, 2);
  NCollection_Array1<int>    the_mults(mults_array[0], 1, 2), the_new_mults(mults_array[0], 1, 2);

  BSplCLib::Trimming(degree,
                     false,
                     the_knots,
                     the_mults,
                     TPoles,
                     BSplCLib::NoWeights(),
                     trim_min,
                     trim_max,
                     the_new_knots,
                     the_new_mults,
                     NewTPoles,
                     BSplCLib::NoWeights());

  double   SinD = std::sin(Delta), CosD = std::cos(Delta);
  gp_Pnt2d Pdeb(1., 0.);
  gp_Pnt2d Pfin(CosD, SinD);

  double dtg   = NewTPoles(1).Distance(NewTPoles(2));
  NewTPoles(1) = Pdeb;
  gp_XY theXY(0., dtg);
  Pdeb.ChangeCoord() += theXY;
  NewTPoles(2) = Pdeb;

  dtg                  = NewTPoles(num_poles).Distance(NewTPoles(num_poles - 1));
  NewTPoles(num_poles) = Pfin;
  theXY.SetCoord(dtg * SinD, -dtg * CosD);
  Pfin.ChangeCoord() += theXY;
  NewTPoles(num_poles - 1) = Pfin;

  T.SetRotation(gp::Origin2d(), locUFirst);
  for (ii = 1; ii <= num_poles; ii++)
  {
    NewTPoles(ii).Transform(T);
  }

  for (ii = 1; ii <= num_poles; ii++)
  {
    CosNumeratorPtr->SetValue(ii, NewTPoles(ii).X());
    SinNumeratorPtr->SetValue(ii, NewTPoles(ii).Y());
    DenominatorPtr->SetValue(ii, 1.);
  }
}
