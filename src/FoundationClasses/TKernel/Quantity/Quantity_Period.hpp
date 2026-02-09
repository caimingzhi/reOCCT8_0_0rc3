#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>

class Quantity_Period
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Quantity_Period(const int dd,
                                  const int hh,
                                  const int mn,
                                  const int ss,
                                  const int mis  = 0,
                                  const int mics = 0);

  Standard_EXPORT Quantity_Period(const int ss, const int mics = 0);

  Standard_EXPORT void Values(int& dd, int& hh, int& mn, int& ss, int& mis, int& mics) const;

  Standard_EXPORT void Values(int& ss, int& mics) const;

  Standard_EXPORT void SetValues(const int dd,
                                 const int hh,
                                 const int mn,
                                 const int ss,
                                 const int mis  = 0,
                                 const int mics = 0);

  Standard_EXPORT void SetValues(const int ss, const int mics = 0);

  Standard_EXPORT Quantity_Period Subtract(const Quantity_Period& anOther) const;

  Quantity_Period operator-(const Quantity_Period& anOther) const { return Subtract(anOther); }

  Standard_EXPORT Quantity_Period Add(const Quantity_Period& anOther) const;

  Quantity_Period operator+(const Quantity_Period& anOther) const { return Add(anOther); }

  constexpr bool IsEqual(const Quantity_Period& anOther) const noexcept
  {
    return (mySec == anOther.mySec && myUSec == anOther.myUSec);
  }

  constexpr bool operator==(const Quantity_Period& anOther) const noexcept
  {
    return IsEqual(anOther);
  }

  constexpr bool IsShorter(const Quantity_Period& anOther) const noexcept
  {
    return (mySec < anOther.mySec) || (mySec == anOther.mySec && myUSec < anOther.myUSec);
  }

  constexpr bool operator<(const Quantity_Period& anOther) const noexcept
  {
    return IsShorter(anOther);
  }

  constexpr bool IsLonger(const Quantity_Period& anOther) const noexcept
  {
    return (mySec > anOther.mySec) || (mySec == anOther.mySec && myUSec > anOther.myUSec);
  }

  constexpr bool operator>(const Quantity_Period& anOther) const noexcept
  {
    return IsLonger(anOther);
  }

  Standard_EXPORT static bool IsValid(const int dd,
                                      const int hh,
                                      const int mn,
                                      const int ss,
                                      const int mis  = 0,
                                      const int mics = 0);

  Standard_EXPORT static bool IsValid(const int ss, const int mics = 0);

private:
  int mySec;
  int myUSec;
};
