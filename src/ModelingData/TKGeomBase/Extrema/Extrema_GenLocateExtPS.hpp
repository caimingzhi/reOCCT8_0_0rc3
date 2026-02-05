#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Boolean.hpp>
#include <Extrema_POnSurf.hpp>
class gp_Pnt;
class Adaptor3d_Surface;

//! With a close point, it calculates the distance
//! between a point and a surface.
//! Criteria type is defined in "Perform" method.
class Extrema_GenLocateExtPS
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor.
  Standard_EXPORT Extrema_GenLocateExtPS(const Adaptor3d_Surface& theS,
                                         const double             theTolU = Precision::PConfusion(),
                                         const double theTolV = Precision::PConfusion());

  //! Calculates the extrema between the point and the surface using a close point.
  //! The close point is defined by the parameter values theU0 and theV0.
  //! Type of the algorithm depends on the isDistanceCriteria flag.
  //! If flag value is false - normal projection criteria will be used.
  //! If flag value is true - distance criteria will be used.
  Standard_EXPORT void Perform(const gp_Pnt& theP,
                               const double  theU0,
                               const double  theV0,
                               const bool    isDistanceCriteria = false);

  //! Returns True if the distance is found.
  Standard_EXPORT bool IsDone() const;

  //! Returns the value of the extremum square distance.
  Standard_EXPORT double SquareDistance() const;

  //! Returns the point of the extremum distance.
  Standard_EXPORT const Extrema_POnSurf& Point() const;

  //! Returns True if UV point theU0, theV0 is point of local minimum of square distance between
  //! point theP and points theS(U, V), U, V are in small area around theU0, theV0
  Standard_EXPORT static bool IsMinDist(const gp_Pnt&            theP,
                                        const Adaptor3d_Surface& theS,
                                        const double             theU0,
                                        const double             theV0);

private:
  const Extrema_GenLocateExtPS& operator=(const Extrema_GenLocateExtPS&) = delete;
  Extrema_GenLocateExtPS(const Extrema_GenLocateExtPS&)                  = delete;

  // Input.
  const Adaptor3d_Surface& mySurf;
  double                   myTolU, myTolV;

  // State.
  bool myDone;

  // Result.
  double          mySqDist;
  Extrema_POnSurf myPoint;
};
