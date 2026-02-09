

#include <Quantity_Date.hpp>
#include <Quantity_DateDefinitionError.hpp>
#include <Quantity_Period.hpp>
#include <Standard_OutOfRange.hpp>

#include "Quantity_TimeConstants.hpp"

namespace
{

  static constexpr int month_table[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  static constexpr int SecondsByYear     = 365 * SECONDS_PER_DAY;
  static constexpr int SecondsByLeapYear = 366 * SECONDS_PER_DAY;

  constexpr int getDaysInMonth(const int theMonth, const int theYear) noexcept
  {
    if (theMonth == 2)
    {
      return Quantity_Date::IsLeap(theYear) ? 29 : 28;
    }
    return month_table[theMonth - 1];
  }
} // namespace

Quantity_Date::Quantity_Date()
    : mySec(0),
      myUSec(0)
{
}

bool Quantity_Date::IsValid(const int mm,
                            const int dd,
                            const int yy,
                            const int hh,
                            const int mn,
                            const int ss,
                            const int mis,
                            const int mics)
{

  if (mm < 1 || mm > 12)
    return false;

  if (yy < 1979)
    return false;

  if (dd < 1 || dd > getDaysInMonth(mm, yy))
    return false;

  if (hh < 0 || hh > 23)
    return false;

  if (mn < 0 || mn > 59)
    return false;

  if (ss < 0 || ss > 59)
    return false;

  if (mis < 0 || mis > 999)
    return false;

  if (mics < 0 || mics > 999)
    return false;

  return true;
}

Quantity_Date::Quantity_Date(const int mm,
                             const int dd,
                             const int yy,
                             const int hh,
                             const int mn,
                             const int ss,
                             const int mis,
                             const int mics)
    : mySec(0),
      myUSec(0)
{

  SetValues(mm, dd, yy, hh, mn, ss, mis, mics);
}

void Quantity_Date::SetValues(const int mm,
                              const int dd,
                              const int yy,
                              const int hh,
                              const int mn,
                              const int ss,
                              const int mis,
                              const int mics)
{

  int i;

  if (!Quantity_Date::IsValid(mm, dd, yy, hh, mn, ss, mis, mics))
    throw Quantity_DateDefinitionError("Quantity_Date::Quantity_Date invalid parameters");

  mySec  = 0;
  myUSec = 0;
  for (i = 1979; i < yy; i++)
  {
    if (!Quantity_Date::IsLeap(i))
      mySec += SecondsByYear;
    else
      mySec += SecondsByLeapYear;
  }

  for (i = 1; i < mm; i++)
  {
    mySec += getDaysInMonth(i, yy) * SECONDS_PER_DAY;
  }

  mySec += SECONDS_PER_DAY * (dd - 1);

  mySec += SECONDS_PER_HOUR * hh;

  mySec += SECONDS_PER_MINUTE * mn;

  mySec += ss;

  myUSec += mis * USECS_PER_MSEC;

  myUSec += mics;
}

void Quantity_Date::Values(int& mm,
                           int& dd,
                           int& yy,
                           int& hh,
                           int& mn,
                           int& ss,
                           int& mis,
                           int& mics) const
{

  int carry;

  for (yy = 1979, carry = mySec;; yy++)
  {
    if (!Quantity_Date::IsLeap(yy))
    {
      if (carry >= SecondsByYear)
        carry -= SecondsByYear;
      else
        break;
    }
    else
    {
      if (carry >= SecondsByLeapYear)
        carry -= SecondsByLeapYear;
      else
        break;
    }
  }

  for (mm = 1;; mm++)
  {
    int i = getDaysInMonth(mm, yy) * SECONDS_PER_DAY;
    if (carry >= i)
      carry -= i;
    else
      break;
  }

  dd = carry / SECONDS_PER_DAY + 1;
  carry -= (dd - 1) * SECONDS_PER_DAY;

  extractTimeComponents(carry, hh, mn, ss);
  extractMillisAndMicros(myUSec, mis, mics);
}

Quantity_Period Quantity_Date::Difference(const Quantity_Date& OtherDate)
{
  int i1, i2;

  if (mySec == 0 && myUSec == 0)
  {
    i1 = OtherDate.mySec;
    i2 = OtherDate.myUSec;
  }
  else
  {
    i1 = mySec - OtherDate.mySec;
    i2 = myUSec - OtherDate.myUSec;
  }

  normalizeSubtractionBorrow(i1, i2);

  if (i1 < 0)
  {
    i1 = -i1;
    if (i2 > 0)
    {
      i1--;
      i2 = USECS_PER_SEC - i2;
    }
  }

  Quantity_Period result(i1, i2);
  return (result);
}

Quantity_Date Quantity_Date::Subtract(const Quantity_Period& During)
{

  int           ss, mics;
  Quantity_Date result;
  result.mySec  = mySec;
  result.myUSec = myUSec;
  During.Values(ss, mics);

  result.mySec -= ss;
  result.myUSec -= mics;

  normalizeSubtractionBorrow(result.mySec, result.myUSec);

  if (result.mySec < 0)
    throw Quantity_DateDefinitionError(
      "Quantity_Date::Subtract : The result date is anterior to Jan,1 1979");

  return (result);
}

Quantity_Date Quantity_Date::Add(const Quantity_Period& During)
{

  Quantity_Date result;
  During.Values(result.mySec, result.myUSec);
  result.mySec += mySec;
  result.myUSec += myUSec;
  normalizeAdditionOverflow(result.mySec, result.myUSec);
  return (result);
}

int Quantity_Date::Year()
{
  int mm, dd, year, hh, mn, ss, mis, mics;
  Values(mm, dd, year, hh, mn, ss, mis, mics);
  return (year);
}

int Quantity_Date::Month()
{
  int mm, dd, yy, hh, mn, ss, mis, mics;
  Values(mm, dd, yy, hh, mn, ss, mis, mics);
  return (mm);
}

int Quantity_Date::Day()
{
  int mm, dd, yy, hh, mn, ss, mis, mics;
  Values(mm, dd, yy, hh, mn, ss, mis, mics);
  return (dd);
}

int Quantity_Date::Hour()
{
  int mm, dd, yy, hh, mn, ss, mis, mics;
  Values(mm, dd, yy, hh, mn, ss, mis, mics);
  return (hh);
}

int Quantity_Date::Minute()
{
  int mm, dd, yy, hh, mn, ss, mis, mics;
  Values(mm, dd, yy, hh, mn, ss, mis, mics);
  return (mn);
}

int Quantity_Date::Second()
{
  int mm, dd, yy, hh, mn, ss, mis, mics;
  Values(mm, dd, yy, hh, mn, ss, mis, mics);
  return (ss);
}

int Quantity_Date::MilliSecond()
{
  int mm, dd, yy, hh, mn, ss, mis, mics;
  Values(mm, dd, yy, hh, mn, ss, mis, mics);
  return (mis);
}

int Quantity_Date::MicroSecond()
{
  int mm, dd, yy, hh, mn, ss, mis, mics;
  Values(mm, dd, yy, hh, mn, ss, mis, mics);
  return (mics);
}
