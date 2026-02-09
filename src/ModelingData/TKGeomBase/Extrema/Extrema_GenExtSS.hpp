#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <Extrema_FuncExtSS.hpp>

class Adaptor3d_Surface;
class Extrema_POnSurf;

class Extrema_GenExtSS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_GenExtSS();

  Standard_EXPORT ~Extrema_GenExtSS();

  Standard_EXPORT Extrema_GenExtSS(const Adaptor3d_Surface& S1,
                                   const Adaptor3d_Surface& S2,
                                   const int                NbU,
                                   const int                NbV,
                                   const double             Tol1,
                                   const double             Tol2);

  Standard_EXPORT Extrema_GenExtSS(const Adaptor3d_Surface& S1,
                                   const Adaptor3d_Surface& S2,
                                   const int                NbU,
                                   const int                NbV,
                                   const double             U1min,
                                   const double             U1sup,
                                   const double             V1min,
                                   const double             V1sup,
                                   const double             U2min,
                                   const double             U2sup,
                                   const double             V2min,
                                   const double             V2sup,
                                   const double             Tol1,
                                   const double             Tol2);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S2,
                                  const int                NbU,
                                  const int                NbV,
                                  const double             Tol2);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S2,
                                  const int                NbU,
                                  const int                NbV,
                                  const double             U2min,
                                  const double             U2sup,
                                  const double             V2min,
                                  const double             V2sup,
                                  const double             Tol2);

  Standard_EXPORT void Perform(const Adaptor3d_Surface& S1, const double Tol1);

  Standard_EXPORT void Perform(const Adaptor3d_Surface& S1,
                               const double             U1min,
                               const double             U1sup,
                               const double             V1min,
                               const double             V1sup,
                               const double             Tol1);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& PointOnS1(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& PointOnS2(const int N) const;

private:
  Extrema_GenExtSS(const Extrema_GenExtSS&)            = delete;
  Extrema_GenExtSS& operator=(const Extrema_GenExtSS&) = delete;

private:
  bool                                     myDone;
  bool                                     myInit;
  double                                   myu1min;
  double                                   myu1sup;
  double                                   myv1min;
  double                                   myv1sup;
  double                                   myu2min;
  double                                   myu2sup;
  double                                   myv2min;
  double                                   myv2sup;
  int                                      myusample;
  int                                      myvsample;
  occ::handle<NCollection_HArray2<gp_Pnt>> mypoints1;
  occ::handle<NCollection_HArray2<gp_Pnt>> mypoints2;
  double                                   mytol1;
  double                                   mytol2;
  Extrema_FuncExtSS                        myF;
  const Adaptor3d_Surface*                 myS2;
};
