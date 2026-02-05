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

//! It calculates all the extremum distances
//! between a curve and a surface.
//! These distances can be minimum or maximum.
class Extrema_ExtCS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_ExtCS();

  //! It calculates all the distances between C and S.
  Standard_EXPORT Extrema_ExtCS(const Adaptor3d_Curve&   C,
                                const Adaptor3d_Surface& S,
                                const double             TolC,
                                const double             TolS);

  //! It calculates all the distances between C and S.
  //! UCinf and UCmax are the start and end parameters
  //! of the curve.
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

  //! Initializes the fields of the algorithm.
  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S, const double TolC, const double TolS);

  //! Initializes the fields of the algorithm.
  Standard_EXPORT void Initialize(const Adaptor3d_Surface& S,
                                  const double             Uinf,
                                  const double             Usup,
                                  const double             Vinf,
                                  const double             Vsup,
                                  const double             TolC,
                                  const double             TolS);

  //! Computes the distances.
  //! An exception is raised if the fields have not been
  //! initialized.
  Standard_EXPORT void Perform(const Adaptor3d_Curve& C, const double Uinf, const double Usup);

  //! Returns True if the distances are found.
  Standard_EXPORT bool IsDone() const;

  //! Returns True if the curve is on a parallel surface.
  Standard_EXPORT bool IsParallel() const;

  //! Returns the number of extremum distances.
  Standard_EXPORT int NbExt() const;

  //! Returns the value of the Nth resulting square distance.
  Standard_EXPORT double SquareDistance(const int N) const;

  //! Returns the point of the Nth resulting distance.
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
  // disallow copies
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
