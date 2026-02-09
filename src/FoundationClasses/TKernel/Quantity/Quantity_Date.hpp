#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class Quantity_Period;

class Quantity_Date
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Quantity_Date();

  Standard_EXPORT Quantity_Date(const int mm,
                                const int dd,
                                const int yyyy,
                                const int hh,
                                const int mn,
                                const int ss,
                                const int mis  = 0,
                                const int mics = 0);

  Standard_EXPORT void Values(int& mm,
                              int& dd,
                              int& yy,
                              int& hh,
                              int& mn,
                              int& ss,
                              int& mis,
                              int& mics) const;

  Standard_EXPORT void SetValues(const int mm,
                                 const int dd,
                                 const int yy,
                                 const int hh,
                                 const int mn,
                                 const int ss,
                                 const int mis  = 0,
                                 const int mics = 0);

  Standard_EXPORT Quantity_Period Difference(const Quantity_Date& anOther);

  Standard_EXPORT Quantity_Date Subtract(const Quantity_Period& aPeriod);

  Quantity_Date operator-(const Quantity_Period& aPeriod) { return Subtract(aPeriod); }

  Standard_EXPORT Quantity_Date Add(const Quantity_Period& aPeriod);

  Quantity_Date operator+(const Quantity_Period& aPeriod) { return Add(aPeriod); }

  Standard_EXPORT int Year();

  Standard_EXPORT int Month();

  Standard_EXPORT int Day();

  Standard_EXPORT int Hour();

  Standard_EXPORT int Minute();

  Standard_EXPORT int Second();

  Standard_EXPORT int MilliSecond();

  Standard_EXPORT int MicroSecond();

  constexpr bool IsEqual(const Quantity_Date& anOther) const noexcept
  {
    return (myUSec == anOther.myUSec && mySec == anOther.mySec);
  }

  constexpr bool operator==(const Quantity_Date& anOther) const noexcept
  {
    return IsEqual(anOther);
  }

  constexpr bool IsEarlier(const Quantity_Date& anOther) const noexcept
  {
    return (mySec < anOther.mySec) || (mySec == anOther.mySec && myUSec < anOther.myUSec);
  }

  constexpr bool operator<(const Quantity_Date& anOther) const noexcept
  {
    return IsEarlier(anOther);
  }

  constexpr bool IsLater(const Quantity_Date& anOther) const noexcept
  {
    return (mySec > anOther.mySec) || (mySec == anOther.mySec && myUSec > anOther.myUSec);
  }

  constexpr bool operator>(const Quantity_Date& anOther) const noexcept { return IsLater(anOther); }

  Standard_EXPORT static bool IsValid(const int mm,
                                      const int dd,
                                      const int yy,
                                      const int hh,
                                      const int mn,
                                      const int ss,
                                      const int mis  = 0,
                                      const int mics = 0);

  static constexpr bool IsLeap(const int yy) noexcept
  {
    return ((yy % 4 == 0) && (yy % 100 != 0)) || (yy % 400) == 0;
  }

private:
  int mySec;
  int myUSec;
};
