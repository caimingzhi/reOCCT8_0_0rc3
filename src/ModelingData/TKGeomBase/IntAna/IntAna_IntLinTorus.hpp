#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
class gp_Lin;
class gp_Torus;

class IntAna_IntLinTorus
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna_IntLinTorus();

  Standard_EXPORT IntAna_IntLinTorus(const gp_Lin& L, const gp_Torus& T);

  Standard_EXPORT void Perform(const gp_Lin& L, const gp_Torus& T);

  bool IsDone() const;

  int NbPoints() const;

  const gp_Pnt& Value(const int Index) const;

  double ParamOnLine(const int Index) const;

  void ParamOnTorus(const int Index, double& FI, double& THETA) const;

private:
  bool   done;
  int    nbpt;
  gp_Pnt thePoint[4];
  double theParam[4];
  double theFi[4];
  double theTheta[4];
};

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>

inline bool IntAna_IntLinTorus::IsDone() const
{
  return done;
}

inline int IntAna_IntLinTorus::NbPoints() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return nbpt;
}

inline const gp_Pnt& IntAna_IntLinTorus::Value(const int Index) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > nbpt)
  {
    throw Standard_OutOfRange();
  }
  return thePoint[Index - 1];
}

inline double IntAna_IntLinTorus::ParamOnLine(const int Index) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > nbpt)
  {
    throw Standard_OutOfRange();
  }
  return theParam[Index - 1];
}

inline void IntAna_IntLinTorus::ParamOnTorus(const int Index, double& FI, double& THETA) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (Index <= 0 || Index > nbpt)
  {
    throw Standard_OutOfRange();
  }
  FI    = theFi[Index - 1];
  THETA = theTheta[Index - 1];
}
