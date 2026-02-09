#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Boolean.hpp>
#include <Extrema_POnSurf.hpp>
class gp_Pnt;
class Adaptor3d_Surface;

class Extrema_GenLocateExtPS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Extrema_GenLocateExtPS(const Adaptor3d_Surface& theS,
                                         const double             theTolU = Precision::PConfusion(),
                                         const double theTolV = Precision::PConfusion());

  Standard_EXPORT void Perform(const gp_Pnt& theP,
                               const double  theU0,
                               const double  theV0,
                               const bool    isDistanceCriteria = false);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double SquareDistance() const;

  Standard_EXPORT const Extrema_POnSurf& Point() const;

  Standard_EXPORT static bool IsMinDist(const gp_Pnt&            theP,
                                        const Adaptor3d_Surface& theS,
                                        const double             theU0,
                                        const double             theV0);

private:
  const Extrema_GenLocateExtPS& operator=(const Extrema_GenLocateExtPS&) = delete;
  Extrema_GenLocateExtPS(const Extrema_GenLocateExtPS&)                  = delete;

  const Adaptor3d_Surface& mySurf;
  double                   myTolU, myTolV;

  bool myDone;

  double          mySqDist;
  Extrema_POnSurf myPoint;
};
