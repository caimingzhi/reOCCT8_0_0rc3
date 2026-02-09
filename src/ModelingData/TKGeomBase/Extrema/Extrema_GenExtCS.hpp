#pragma once

#include <Extrema_FuncExtCS.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>

class Adaptor3d_Curve;
class Adaptor3d_Surface;
class Extrema_POnCurv;
class Extrema_POnSurf;

class Extrema_GenExtCS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_GenExtCS();

  Standard_EXPORT ~Extrema_GenExtCS();

  Standard_EXPORT Extrema_GenExtCS(const Adaptor3d_Curve&   C,
                                   const Adaptor3d_Surface& S,
                                   const int                NbT,
                                   const int                NbU,
                                   const int                NbV,
                                   const double             Tol1,
                                   const double             Tol2);

  Standard_EXPORT Extrema_GenExtCS(const Adaptor3d_Curve&   C,
                                   const Adaptor3d_Surface& S,
                                   const int                NbT,
                                   const int                NbU,
                                   const int                NbV,
                                   const double             tmin,
                                   const double             tsup,
                                   const double             Umin,
                                   const double             Usup,
                                   const double             Vmin,
                                   const double             Vsup,
                                   const double             Tol1,
                                   const double             Tol2);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S,
                                  const int                NbU,
                                  const int                NbV,
                                  const double             Tol2);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S,
                                  const int                NbU,
                                  const int                NbV,
                                  const double             Umin,
                                  const double             Usup,
                                  const double             Vmin,
                                  const double             Vsup,
                                  const double             Tol2);

  Standard_EXPORT void Perform(const Adaptor3d_Curve& C, const int NbT, const double Tol1);

  Standard_EXPORT void Perform(const Adaptor3d_Curve& C,
                               const int              NbT,
                               const double           tmin,
                               const double           tsup,
                               const double           Tol1);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnCurv& PointOnCurve(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& PointOnSurface(const int N) const;

private:
  Standard_EXPORT void GlobMinGenCS(const Adaptor3d_Curve& theC,
                                    const int              theNbParticles,
                                    const math_Vector&     theTUVinf,
                                    const math_Vector&     theTUVsup,
                                    math_Vector&           theTUV);

  Standard_EXPORT void GlobMinConicS(const Adaptor3d_Curve& theC,
                                     const int              theNbParticles,
                                     const math_Vector&     theTUVinf,
                                     const math_Vector&     theTUVsup,
                                     math_Vector&           theTUV);

  Standard_EXPORT void GlobMinCQuadric(const Adaptor3d_Curve& theC,
                                       const int              theNbParticles,
                                       const math_Vector&     theTUVinf,
                                       const math_Vector&     theTUVsup,
                                       math_Vector&           theTUV);

private:
  Extrema_GenExtCS(const Extrema_GenExtCS&)            = delete;
  Extrema_GenExtCS& operator=(const Extrema_GenExtCS&) = delete;

private:
  bool                                     myDone;
  double                                   mytmin;
  double                                   mytsup;
  double                                   myumin;
  double                                   myusup;
  double                                   myvmin;
  double                                   myvsup;
  int                                      mytsample;
  int                                      myusample;
  int                                      myvsample;
  double                                   mytol1;
  double                                   mytol2;
  Extrema_FuncExtCS                        myF;
  const Adaptor3d_Surface*                 myS;
  occ::handle<NCollection_HArray2<gp_Pnt>> mySurfPnts;
};
