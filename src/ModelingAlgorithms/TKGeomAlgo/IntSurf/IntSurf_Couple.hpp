#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>

class IntSurf_Couple
{
public:
  DEFINE_STANDARD_ALLOC

  IntSurf_Couple();

  IntSurf_Couple(const int Index1, const int Index2);

  int First() const;

  int Second() const;

private:
  int firstInteger;
  int secondInteger;
};

inline IntSurf_Couple::IntSurf_Couple()
    : firstInteger(0),
      secondInteger(0)
{
}

inline IntSurf_Couple::IntSurf_Couple(const int Index1, const int Index2)
    : firstInteger(Index1),
      secondInteger(Index2)
{
}

inline int IntSurf_Couple::First() const
{
  return firstInteger;
}

inline int IntSurf_Couple::Second() const
{
  return secondInteger;
}
