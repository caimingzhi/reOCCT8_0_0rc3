

#include <Quantity_Period.hpp>
#include <Quantity_PeriodDefinitionError.hpp>

#include "Quantity_TimeConstants.hpp"

bool Quantity_Period::IsValid(const int dd,
                              const int hh,
                              const int mn,
                              const int ss,
                              const int mis,
                              const int mics)
{
  return (dd >= 0 && hh >= 0 && mn >= 0 && ss >= 0 && mis >= 0 && mics >= 0);
}

bool Quantity_Period::IsValid(const int ss, const int mics)
{
  return (ss >= 0 && mics >= 0);
}

Quantity_Period::Quantity_Period(const int dd,
                                 const int hh,
                                 const int mn,
                                 const int ss,
                                 const int mils,
                                 const int mics)
    : mySec(0),
      myUSec(0)
{

  SetValues(dd, hh, mn, ss, mils, mics);
}

Quantity_Period::Quantity_Period(const int ss, const int mics)
    : mySec(0),
      myUSec(0)
{

  SetValues(ss, mics);
}

void Quantity_Period::Values(int& dd, int& hh, int& mn, int& ss, int& mis, int& mics) const
{
  int carry = mySec;
  dd        = carry / SECONDS_PER_DAY;
  carry -= dd * SECONDS_PER_DAY;
  extractTimeComponents(carry, hh, mn, ss);
  extractMillisAndMicros(myUSec, mis, mics);
}

void Quantity_Period::Values(int& ss, int& mics) const
{

  ss   = mySec;
  mics = myUSec;
}

void Quantity_Period::SetValues(const int dd,
                                const int hh,
                                const int mn,
                                const int ss,
                                const int mils,
                                const int mics)
{
  SetValues((dd * SECONDS_PER_DAY) + (hh * SECONDS_PER_HOUR) + (SECONDS_PER_MINUTE * mn) + ss,
            mils * USECS_PER_MSEC + mics);
}

void Quantity_Period::SetValues(const int ss, const int mics)
{

  if (!Quantity_Period::IsValid(ss, mics))
    throw Quantity_PeriodDefinitionError("Quantity_Period::SetValues invalid parameters");

  mySec  = ss;
  myUSec = mics;
  normalizeAdditionOverflow(mySec, myUSec);
}

Quantity_Period Quantity_Period::Subtract(const Quantity_Period& OtherPeriod) const
{
  Quantity_Period result(mySec, myUSec);

  result.mySec -= OtherPeriod.mySec;
  result.myUSec -= OtherPeriod.myUSec;

  normalizeSubtractionBorrow(result.mySec, result.myUSec);

  if (result.mySec < 0)
  {
    result.mySec = std::abs(result.mySec);
    if (result.myUSec > 0)
    {
      result.mySec--;
      result.myUSec = USECS_PER_SEC - result.myUSec;
    }
  }
  return (result);
}

Quantity_Period Quantity_Period::Add(const Quantity_Period& OtherPeriod) const
{

  Quantity_Period result(mySec, myUSec);
  result.mySec += OtherPeriod.mySec;
  result.myUSec += OtherPeriod.myUSec;
  normalizeAdditionOverflow(result.mySec, result.myUSec);
  return (result);
}
