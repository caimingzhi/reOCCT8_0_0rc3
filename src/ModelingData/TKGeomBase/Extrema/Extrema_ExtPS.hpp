#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Extrema_ExtPElS.hpp>
#include <Extrema_GenExtPS.hpp>
#include <Extrema_POnSurf.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Pnt.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <Extrema_ExtFlag.hpp>
#include <Extrema_ExtAlgo.hpp>
#include <Standard_Integer.hpp>
class Extrema_ExtPExtS;
class Extrema_ExtPRevS;
class Adaptor3d_Surface;
class Extrema_POnSurf;

class Extrema_ExtPS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtPS();

  Standard_EXPORT Extrema_ExtPS(const gp_Pnt&            P,
                                const Adaptor3d_Surface& S,
                                const double             TolU,
                                const double             TolV,
                                const Extrema_ExtFlag    F = Extrema_ExtFlag_MINMAX,
                                const Extrema_ExtAlgo    A = Extrema_ExtAlgo_Grad);

  Standard_EXPORT Extrema_ExtPS(const gp_Pnt&            P,
                                const Adaptor3d_Surface& S,
                                const double             Uinf,
                                const double             Usup,
                                const double             Vinf,
                                const double             Vsup,
                                const double             TolU,
                                const double             TolV,
                                const Extrema_ExtFlag    F = Extrema_ExtFlag_MINMAX,
                                const Extrema_ExtAlgo    A = Extrema_ExtAlgo_Grad);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S,
                                  const double             Uinf,
                                  const double             Usup,
                                  const double             Vinf,
                                  const double             Vsup,
                                  const double             TolU,
                                  const double             TolV);

  Standard_EXPORT void Perform(const gp_Pnt& P);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT const Extrema_POnSurf& Point(const int N) const;

  Standard_EXPORT void TrimmedSquareDistances(double& dUfVf,
                                              double& dUfVl,
                                              double& dUlVf,
                                              double& dUlVl,
                                              gp_Pnt& PUfVf,
                                              gp_Pnt& PUfVl,
                                              gp_Pnt& PUlVf,
                                              gp_Pnt& PUlVl) const;

  Standard_EXPORT void SetFlag(const Extrema_ExtFlag F);

  Standard_EXPORT void SetAlgo(const Extrema_ExtAlgo A);

private:
  Standard_EXPORT void TreatSolution(const Extrema_POnSurf& PS, const double Val);

private:
  const Adaptor3d_Surface*              myS;
  bool                                  myDone;
  Extrema_ExtPElS                       myExtPElS;
  Extrema_GenExtPS                      myExtPS;
  NCollection_Sequence<Extrema_POnSurf> myPoints;
  double                                myuinf;
  double                                myusup;
  double                                myvinf;
  double                                myvsup;
  double                                mytolu;
  double                                mytolv;
  double                                d11;
  double                                d12;
  double                                d21;
  double                                d22;
  gp_Pnt                                P11;
  gp_Pnt                                P12;
  gp_Pnt                                P21;
  gp_Pnt                                P22;
  NCollection_Sequence<double>          mySqDist;
  GeomAbs_SurfaceType                   mytype;
  occ::handle<Extrema_ExtPExtS>         myExtPExtS;
  occ::handle<Extrema_ExtPRevS>         myExtPRevS;
};
