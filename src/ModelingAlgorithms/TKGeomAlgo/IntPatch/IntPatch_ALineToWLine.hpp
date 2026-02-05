#pragma once

#include <Adaptor3d_Surface.hpp>
#include <IntPatch_Line.hpp>
#include <NCollection_Sequence.hpp>
#include <IntSurf_Quadric.hpp>
#include <IntSurf_LineOn2S.hpp>

class IntPatch_ALine;
class IntSurf_PntOn2S;

class IntPatch_ALineToWLine
{
public:
  DEFINE_STANDARD_ALLOC

  //! Constructor
  Standard_EXPORT IntPatch_ALineToWLine(const occ::handle<Adaptor3d_Surface>& theS1,
                                        const occ::handle<Adaptor3d_Surface>& theS2,
                                        const int                             theNbPoints = 200);

  Standard_EXPORT void SetTolOpenDomain(const double aT);

  Standard_EXPORT double TolOpenDomain() const;

  Standard_EXPORT void SetTolTransition(const double aT);

  Standard_EXPORT double TolTransition() const;

  Standard_EXPORT void SetTol3D(const double aT);

  Standard_EXPORT double Tol3D() const;

  //! Converts aline to the set of Walking-lines and adds
  //! them in theLines.
  Standard_EXPORT void MakeWLine(const occ::handle<IntPatch_ALine>&                aline,
                                 NCollection_Sequence<occ::handle<IntPatch_Line>>& theLines) const;

  //! Converts aline (limited by paraminf and paramsup) to the set of
  //! Walking-lines and adds them in theLines.
  Standard_EXPORT void MakeWLine(const occ::handle<IntPatch_ALine>&                aline,
                                 const double                                      paraminf,
                                 const double                                      paramsup,
                                 NCollection_Sequence<occ::handle<IntPatch_Line>>& theLines) const;

protected:
  //! Computes step value to construct point-line. The step depends on
  //! the local curvature of the intersection line computed in thePOn2S.
  //! theTgMagnitude is the magnitude of tangent vector to the intersection
  //! line (in the point thePOn2S).
  //! Computed step is always in the range [theStepMin, theStepMax].
  //! Returns FALSE if the step cannot be computed. In this case, its value
  //! will not be changed.
  Standard_EXPORT bool StepComputing(const occ::handle<IntPatch_ALine>& theALine,
                                     const IntSurf_PntOn2S&             thePOn2S,
                                     const double                       theLastParOfAline,
                                     const double                       theCurParam,
                                     const double                       theTgMagnitude,
                                     const double                       theStepMin,
                                     const double                       theStepMax,
                                     const double                       theMaxDeflection,
                                     double&                            theStep) const;

  //! Compares distances from theMidPt to every quadrics with theMaxDeflection
  //! (maximal distance of two ones is taken into account).
  //! Returns the result of this comparison: -1 - small distance, +1 - big distance,
  //! 0 - Dist == theMaxDeflection. Comparisons are done with internal tolerances.
  Standard_EXPORT int CheckDeflection(const gp_XYZ& theMidPt, const double theMaxDeflection) const;

  //! Returns radius of a circle obtained by intersection the quadric with a plane
  //! goes through thePnt3d perpendicular to the quadric axis. This radius is computed
  //! for both quadrics and minimal value is returned.
  //! This check is made for cone and sphere only.
  Standard_EXPORT double GetSectionRadius(const gp_Pnt& thePnt3d) const;

  //! Corrects the U-parameter of an end point (first or last) of the line
  //! if this end point is a pole.
  //! The line must contain at least 3 points.
  //! This is made for cone and sphere only.
  Standard_EXPORT void CorrectEndPoint(occ::handle<IntSurf_LineOn2S>& theLine,
                                       const int                      theIndex) const;

private:
  occ::handle<Adaptor3d_Surface> myS1;
  occ::handle<Adaptor3d_Surface> myS2;
  IntSurf_Quadric                myQuad1;
  IntSurf_Quadric                myQuad2;

  //! Approximate number of points in resulting
  //! WLine (precise number of points is computed
  //! by the algorithms)
  int    myNbPointsInWline;
  double myTolOpenDomain;
  double myTolTransition;
  double myTol3D;
};
