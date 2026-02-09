#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Extrema_ExtElCS.hpp>
#include <Extrema_POnSurf.hpp>
#include <NCollection_Sequence.hpp>
#include <Extrema_POnCurv.hpp>
#include <GeomAbs_SurfaceType.hpp>

class Adaptor3d_Curve;
class Adaptor3d_Surface;
class Extrema_POnCurv;
class Extrema_POnSurf;
class gp_Pnt;

class Extrema_ExtCS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtCS();

  Standard_EXPORT Extrema_ExtCS(const Adaptor3d_Curve&   C,
                                const Adaptor3d_Surface& S,
                                const double             TolC,
                                const double             TolS);

  Standard_EXPORT Extrema_ExtCS(const Adaptor3d_Curve&   C,
                                const Adaptor3d_Surface& S,
                                const double             UCinf,
                                const double             UCsup,
                                const double             Uinf,
                                const double             Usup,
                                const double             Vinf,
                                const double             Vsup,
                                const double             TolC,
                                const double             TolS);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S, const double TolC, const double TolS);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S,
                                  const double             Uinf,
                                  const double             Usup,
                                  const double             Vinf,
                                  const double             Vsup,
                                  const double             TolC,
                                  const double             TolS);

  Standard_EXPORT void Perform(const Adaptor3d_Curve& C, const double Uinf, const double Usup);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT void Points(const int N, Extrema_POnCurv& P1, Extrema_POnSurf& P2) const;

private:
  Standard_EXPORT bool AddSolution(const Adaptor3d_Curve& Curve,
                                   const double           T,
                                   const double           U,
                                   const double           V,
                                   const gp_Pnt&          PointOnCurve,
                                   const gp_Pnt&          PointOnSurf,
                                   const double           SquareDist);

private:
  Extrema_ExtCS(Extrema_ExtCS&)            = delete;
  Extrema_ExtCS& operator=(Extrema_ExtCS&) = delete;

private:
  const Adaptor3d_Surface*              myS;
  bool                                  myDone;
  bool                                  myIsPar;
  Extrema_ExtElCS                       myExtElCS;
  NCollection_Sequence<Extrema_POnSurf> myPOnS;
  NCollection_Sequence<Extrema_POnCurv> myPOnC;
  double                                myuinf;
  double                                myusup;
  double                                myvinf;
  double                                myvsup;
  double                                mytolC;
  double                                mytolS;
  double                                myucinf;
  double                                myucsup;
  NCollection_Sequence<double>          mySqDist;
  GeomAbs_SurfaceType                   myStype;
};
