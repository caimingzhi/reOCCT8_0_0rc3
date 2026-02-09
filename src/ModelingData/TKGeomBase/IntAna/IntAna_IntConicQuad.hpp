#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <gp_Pnt.hpp>
class gp_Lin;
class IntAna_Quadric;
class gp_Circ;
class gp_Elips;
class gp_Parab;
class gp_Hypr;
class gp_Pln;

class IntAna_IntConicQuad
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntAna_IntConicQuad();

  Standard_EXPORT IntAna_IntConicQuad(const gp_Lin& L, const IntAna_Quadric& Q);

  Standard_EXPORT void Perform(const gp_Lin& L, const IntAna_Quadric& Q);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Circ& C, const IntAna_Quadric& Q);

  Standard_EXPORT void Perform(const gp_Circ& C, const IntAna_Quadric& Q);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Elips& E, const IntAna_Quadric& Q);

  Standard_EXPORT void Perform(const gp_Elips& E, const IntAna_Quadric& Q);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Parab& P, const IntAna_Quadric& Q);

  Standard_EXPORT void Perform(const gp_Parab& P, const IntAna_Quadric& Q);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Hypr& H, const IntAna_Quadric& Q);

  Standard_EXPORT void Perform(const gp_Hypr& H, const IntAna_Quadric& Q);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Lin& L,
                                      const gp_Pln& P,
                                      const double  Tolang,
                                      const double  Tol = 0,
                                      const double  Len = 0);

  Standard_EXPORT void Perform(const gp_Lin& L,
                               const gp_Pln& P,
                               const double  Tolang,
                               const double  Tol = 0,
                               const double  Len = 0);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Circ& C,
                                      const gp_Pln&  P,
                                      const double   Tolang,
                                      const double   Tol);

  Standard_EXPORT void Perform(const gp_Circ& C,
                               const gp_Pln&  P,
                               const double   Tolang,
                               const double   Tol);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Elips& E,
                                      const gp_Pln&   P,
                                      const double    Tolang,
                                      const double    Tol);

  Standard_EXPORT void Perform(const gp_Elips& E,
                               const gp_Pln&   P,
                               const double    Tolang,
                               const double    Tol);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Parab& Pb, const gp_Pln& P, const double Tolang);

  Standard_EXPORT void Perform(const gp_Parab& Pb, const gp_Pln& P, const double Tolang);

  Standard_EXPORT IntAna_IntConicQuad(const gp_Hypr& H, const gp_Pln& P, const double Tolang);

  Standard_EXPORT void Perform(const gp_Hypr& H, const gp_Pln& P, const double Tolang);

  bool IsDone() const;

  bool IsInQuadric() const;

  bool IsParallel() const;

  int NbPoints() const;

  const gp_Pnt& Point(const int N) const;

  double ParamOnConic(const int N) const;

private:
  bool   done;
  bool   parallel;
  bool   inquadric;
  int    nbpts;
  gp_Pnt pnts[4];
  double paramonc[4];
};

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>

inline bool IntAna_IntConicQuad::IsDone() const
{
  return (done);
}

inline bool IntAna_IntConicQuad::IsInQuadric() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return (inquadric);
}

inline bool IntAna_IntConicQuad::IsParallel() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  return (parallel);
}

inline int IntAna_IntConicQuad::NbPoints() const
{
  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (parallel || inquadric)
  {
    throw Standard_DomainError();
  }
  return (nbpts);
}

inline const gp_Pnt& IntAna_IntConicQuad::Point(const int i) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (parallel || inquadric)
  {
    throw Standard_DomainError();
  }
  if ((i > nbpts) || (i <= 0))
  {
    throw Standard_OutOfRange();
  }
  return (pnts[i - 1]);
}

inline double IntAna_IntConicQuad::ParamOnConic(const int i) const
{

  if (!done)
  {
    throw StdFail_NotDone();
  }
  if (parallel || inquadric)
  {
    throw Standard_DomainError();
  }
  if ((i > nbpts) || (i <= 0))
  {
    throw Standard_OutOfRange();
  }
  return (paramonc[i - 1]);
}
