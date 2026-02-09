#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>

class math_TrigonometricFunctionRoots
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT math_TrigonometricFunctionRoots(const double A,
                                                  const double B,
                                                  const double C,
                                                  const double D,
                                                  const double E,
                                                  const double InfBound,
                                                  const double SupBound);

  Standard_EXPORT math_TrigonometricFunctionRoots(const double D,
                                                  const double E,
                                                  const double InfBound,
                                                  const double SupBound);

  Standard_EXPORT math_TrigonometricFunctionRoots(const double C,
                                                  const double D,
                                                  const double E,
                                                  const double InfBound,
                                                  const double SupBound);

  bool IsDone() const;

  bool InfiniteRoots() const;

  double Value(const int Index) const;

  int NbSolutions() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

protected:
  Standard_EXPORT void Perform(const double A,
                               const double B,
                               const double C,
                               const double D,
                               const double E,
                               const double InfBound,
                               const double SupBound);

private:
  int                        NbSol;
  NCollection_Array1<double> Sol;
  bool                       InfiniteStatus;
  bool                       Done;
};

#include <StdFail_InfiniteSolutions.hpp>
#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>

inline bool math_TrigonometricFunctionRoots::InfiniteRoots() const
{
  return InfiniteStatus;
}

inline bool math_TrigonometricFunctionRoots::IsDone() const
{
  return Done;
}

inline Standard_OStream& operator<<(Standard_OStream& o, const math_TrigonometricFunctionRoots& T)
{
  T.Dump(o);
  return o;
}

inline double math_TrigonometricFunctionRoots::Value(const int Index) const
{
  StdFail_InfiniteSolutions_Raise_if(InfiniteStatus, " ");
  StdFail_NotDone_Raise_if(!Done, " ");
  Standard_OutOfRange_Raise_if(Index > NbSol, " ");
  return Sol(Index);
}

inline int math_TrigonometricFunctionRoots::NbSolutions() const
{
  StdFail_InfiniteSolutions_Raise_if(InfiniteStatus, " ");
  StdFail_NotDone_Raise_if(!Done, " ");
  return NbSol;
}
