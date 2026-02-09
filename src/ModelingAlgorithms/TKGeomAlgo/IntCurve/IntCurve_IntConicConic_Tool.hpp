#pragma once

#include <IntCurve_IntImpConicParConic.hpp>

#include <IntRes2d_Domain.hpp>
#include <IntRes2d_Transition.hpp>
#include <IntRes2d_Position.hpp>

static double PIpPI = M_PI + M_PI;

void Determine_Transition_LC(const IntRes2d_Position,
                             gp_Vec2d&,
                             const gp_Vec2d&,
                             IntRes2d_Transition&,
                             const IntRes2d_Position,
                             gp_Vec2d&,
                             const gp_Vec2d&,
                             IntRes2d_Transition&,
                             const double);

double NormalizeOnCircleDomain(const double Param, const IntRes2d_Domain& Domain);

class Interval
{
public:
  double Binf;
  double Bsup;
  bool   HasFirstBound;
  bool   HasLastBound;
  bool   IsNull;

  Interval();
  Interval(const double a, const double b);
  Interval(const IntRes2d_Domain& Domain);
  Interval(const double a, const bool hf, const double b, const bool hl);
  double   Length();
  Interval IntersectionWithBounded(const Interval& Inter);
};

class PeriodicInterval
{
public:
  double Binf;
  double Bsup;
  bool   isnull;

  void SetNull() { isnull = true; }

  bool IsNull() { return (isnull); }

  void Complement()
  {
    if (!isnull)
    {
      double t = Binf;
      Binf     = Bsup;
      Bsup     = t + PIpPI;
      if (Binf > PIpPI)
      {
        Binf -= PIpPI;
        Bsup -= PIpPI;
      }
    }
  }

  double Length() { return ((isnull) ? -100.0 : std::abs(Bsup - Binf)); }

  PeriodicInterval(const IntRes2d_Domain& Domain)
  {
    isnull = false;
    if (Domain.HasFirstPoint())
      Binf = Domain.FirstParameter();
    else
      Binf = -1.0;
    if (Domain.HasLastPoint())
      Bsup = Domain.LastParameter();
    else
      Bsup = 20.0;
  }

  PeriodicInterval()
  {
    isnull = true;
    Binf = Bsup = 0.0;
  }

  PeriodicInterval(const double a, const double b)
  {
    isnull = false;
    Binf   = a;
    Bsup   = b;
    if ((b - a) < PIpPI)
      this->Normalize();
  }

  void SetValues(const double a, const double b)
  {
    isnull = false;
    Binf   = a;
    Bsup   = b;
    if ((b - a) < PIpPI)
      this->Normalize();
  }

  void Normalize()
  {
    if (!isnull)
    {
      while (Binf > PIpPI)
        Binf -= PIpPI;
      while (Binf < 0.0)
        Binf += PIpPI;
      while (Bsup < Binf)
        Bsup += PIpPI;
      while (Bsup >= (Binf + PIpPI))
        Bsup -= PIpPI;
    }
  }

  PeriodicInterval FirstIntersection(PeriodicInterval& I1);
  PeriodicInterval SecondIntersection(PeriodicInterval& I2);
};
