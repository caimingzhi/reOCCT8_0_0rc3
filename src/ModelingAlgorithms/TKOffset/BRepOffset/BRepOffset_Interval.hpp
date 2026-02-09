#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <ChFiDS_TypeOfConcavity.hpp>

class BRepOffset_Interval
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffset_Interval();

  Standard_EXPORT BRepOffset_Interval(const double                 U1,
                                      const double                 U2,
                                      const ChFiDS_TypeOfConcavity Type);

  void First(const double U);

  void Last(const double U);

  void Type(const ChFiDS_TypeOfConcavity T);

  double First() const;

  double Last() const;

  ChFiDS_TypeOfConcavity Type() const;

private:
  double                 f;
  double                 l;
  ChFiDS_TypeOfConcavity type;
};

inline void BRepOffset_Interval::First(const double U)
{
  f = U;
}

inline void BRepOffset_Interval::Last(const double U)
{
  l = U;
}

inline void BRepOffset_Interval::Type(const ChFiDS_TypeOfConcavity T)
{
  type = T;
}

inline double BRepOffset_Interval::First() const
{
  return f;
}

inline double BRepOffset_Interval::Last() const
{
  return l;
}

inline ChFiDS_TypeOfConcavity BRepOffset_Interval::Type() const
{
  return type;
}
