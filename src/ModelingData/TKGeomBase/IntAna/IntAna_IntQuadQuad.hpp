#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <IntAna_Curve.hpp>
#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
class gp_Cylinder;
class IntAna_Quadric;
class gp_Cone;

class IntAna_IntQuadQuad
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna_IntQuadQuad();

  Standard_EXPORT IntAna_IntQuadQuad(const gp_Cylinder&    C,
                                     const IntAna_Quadric& Q,
                                     const double          Tol);

  Standard_EXPORT IntAna_IntQuadQuad(const gp_Cone& C, const IntAna_Quadric& Q, const double Tol);

  Standard_EXPORT void Perform(const gp_Cylinder& C, const IntAna_Quadric& Q, const double Tol);

  Standard_EXPORT void Perform(const gp_Cone& C, const IntAna_Quadric& Q, const double Tol);

  bool IsDone() const;

  bool IdenticalElements() const;

  int NbCurve() const;

  Standard_EXPORT const IntAna_Curve& Curve(const int N) const;

  int NbPnt() const;

  Standard_EXPORT const gp_Pnt& Point(const int N) const;

  Standard_EXPORT void Parameters(const int N, double& U1, double& U2) const;

  Standard_EXPORT bool HasNextCurve(const int I) const;

  Standard_EXPORT int NextCurve(const int I, bool& theOpposite) const;

  Standard_EXPORT bool HasPreviousCurve(const int I) const;

  Standard_EXPORT int PreviousCurve(const int I, bool& theOpposite) const;

protected:
  Standard_EXPORT void InternalSetNextAndPrevious();

protected:
  bool         done;
  bool         identical;
  IntAna_Curve TheCurve[12];
  int          previouscurve[12];
  int          nextcurve[12];
  int          NbCurves;
  int          Nbpoints;
  gp_Pnt       Thepoints[2];
  int          myNbMaxCurves;
  double       myEpsilon;
  double       myEpsilonCoeffPolyNull;
};

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>

inline bool IntAna_IntQuadQuad::IsDone() const
{
  return (done);
}

inline bool IntAna_IntQuadQuad::IdenticalElements() const
{
  if (!done)
  {
    throw StdFail_NotDone("IntQuadQuad Not done");
  }
  return (identical);
}

inline int IntAna_IntQuadQuad::NbCurve() const
{
  if (!done)
  {
    throw StdFail_NotDone("IntQuadQuad Not done");
  }
  if (identical)
  {
    throw Standard_DomainError();
  }
  return (NbCurves);
}

inline int IntAna_IntQuadQuad::NbPnt() const
{
  if (!done)
  {
    throw StdFail_NotDone("IntQuadQuad Not done");
  }
  if (identical)
  {
    throw Standard_DomainError();
  }
  return (Nbpoints);
}
