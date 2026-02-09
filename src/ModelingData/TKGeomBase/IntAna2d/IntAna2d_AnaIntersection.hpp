#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <IntAna2d_IntPoint.hpp>
class gp_Lin2d;
class gp_Circ2d;
class IntAna2d_Conic;
class gp_Elips2d;
class gp_Parab2d;
class gp_Hypr2d;

class IntAna2d_AnaIntersection
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna2d_AnaIntersection();

  Standard_EXPORT IntAna2d_AnaIntersection(const gp_Lin2d& L1, const gp_Lin2d& L2);

  Standard_EXPORT IntAna2d_AnaIntersection(const gp_Circ2d& C1, const gp_Circ2d& C2);

  Standard_EXPORT IntAna2d_AnaIntersection(const gp_Lin2d& L, const gp_Circ2d& C);

  Standard_EXPORT IntAna2d_AnaIntersection(const gp_Lin2d& L, const IntAna2d_Conic& C);

  Standard_EXPORT IntAna2d_AnaIntersection(const gp_Circ2d& C, const IntAna2d_Conic& Co);

  Standard_EXPORT IntAna2d_AnaIntersection(const gp_Elips2d& E, const IntAna2d_Conic& C);

  Standard_EXPORT IntAna2d_AnaIntersection(const gp_Parab2d& P, const IntAna2d_Conic& C);

  Standard_EXPORT IntAna2d_AnaIntersection(const gp_Hypr2d& H, const IntAna2d_Conic& C);

  Standard_EXPORT void Perform(const gp_Lin2d& L1, const gp_Lin2d& L2);

  Standard_EXPORT void Perform(const gp_Circ2d& C1, const gp_Circ2d& C2);

  Standard_EXPORT void Perform(const gp_Lin2d& L, const gp_Circ2d& C);

  Standard_EXPORT void Perform(const gp_Lin2d& L, const IntAna2d_Conic& C);

  Standard_EXPORT void Perform(const gp_Circ2d& C, const IntAna2d_Conic& Co);

  Standard_EXPORT void Perform(const gp_Elips2d& E, const IntAna2d_Conic& C);

  Standard_EXPORT void Perform(const gp_Parab2d& P, const IntAna2d_Conic& C);

  Standard_EXPORT void Perform(const gp_Hypr2d& H, const IntAna2d_Conic& C);

  bool IsDone() const;

  bool IsEmpty() const;

  bool IdenticalElements() const;

  bool ParallelElements() const;

  int NbPoints() const;

  const IntAna2d_IntPoint& Point(const int N) const;

private:
  bool              done;
  bool              para;
  bool              iden;
  bool              empt;
  int               nbp;
  IntAna2d_IntPoint lpnt[4];
};

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>

inline bool IntAna2d_AnaIntersection::IsDone() const
{
  return done;
}

inline bool IntAna2d_AnaIntersection::IsEmpty() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return ((nbp == 0) && (!iden));
}

inline bool IntAna2d_AnaIntersection::IdenticalElements() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return iden;
}

inline bool IntAna2d_AnaIntersection::ParallelElements() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return para;
}

inline int IntAna2d_AnaIntersection::NbPoints() const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  return nbp;
}

inline const IntAna2d_IntPoint& IntAna2d_AnaIntersection::Point(const int N) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  else
  {
    if ((N <= 0) || (N > nbp))
    {
      throw Standard_OutOfRange();
    }
    else
    {
      return lpnt[N - 1];
    }
  }
}
