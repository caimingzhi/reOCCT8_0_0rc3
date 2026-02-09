#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Extrema_ExtElSS.hpp>
#include <Extrema_POnSurf.hpp>
#include <NCollection_Sequence.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <Standard_Integer.hpp>
class Adaptor3d_Surface;
class Extrema_POnSurf;

class Extrema_ExtSS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtSS();

  Standard_EXPORT Extrema_ExtSS(const Adaptor3d_Surface& S1,
                                const Adaptor3d_Surface& S2,
                                const double             TolS1,
                                const double             TolS2);

  Standard_EXPORT Extrema_ExtSS(const Adaptor3d_Surface& S1,
                                const Adaptor3d_Surface& S2,
                                const double             Uinf1,
                                const double             Usup1,
                                const double             Vinf1,
                                const double             Vsup1,
                                const double             Uinf2,
                                const double             Usup2,
                                const double             Vinf2,
                                const double             Vsup2,
                                const double             TolS1,
                                const double             TolS2);

  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S2,
                                  const double             Uinf2,
                                  const double             Usup2,
                                  const double             Vinf2,
                                  const double             Vsup2,
                                  const double             TolS1);

  Standard_EXPORT void Perform(const Adaptor3d_Surface& S1,
                               const double             Uinf1,
                               const double             Usup1,
                               const double             Vinf1,
                               const double             Vsup1,
                               const double             TolS1);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool IsParallel() const;

  Standard_EXPORT int NbExt() const;

  Standard_EXPORT double SquareDistance(const int N) const;

  Standard_EXPORT void Points(const int N, Extrema_POnSurf& P1, Extrema_POnSurf& P2) const;

private:
  const Adaptor3d_Surface*              myS2;
  bool                                  myDone;
  bool                                  myIsPar;
  Extrema_ExtElSS                       myExtElSS;
  NCollection_Sequence<Extrema_POnSurf> myPOnS1;
  NCollection_Sequence<Extrema_POnSurf> myPOnS2;
  double                                myuinf1;
  double                                myusup1;
  double                                myvinf1;
  double                                myvsup1;
  double                                myuinf2;
  double                                myusup2;
  double                                myvinf2;
  double                                myvsup2;
  double                                mytolS1;
  double                                mytolS2;
  NCollection_Sequence<double>          mySqDist;
  GeomAbs_SurfaceType                   myStype;
};
