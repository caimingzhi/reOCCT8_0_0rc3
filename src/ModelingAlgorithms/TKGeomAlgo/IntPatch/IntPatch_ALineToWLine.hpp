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

  Standard_EXPORT IntPatch_ALineToWLine(const occ::handle<Adaptor3d_Surface>& theS1,
                                        const occ::handle<Adaptor3d_Surface>& theS2,
                                        const int                             theNbPoints = 200);

  Standard_EXPORT void SetTolOpenDomain(const double aT);

  Standard_EXPORT double TolOpenDomain() const;

  Standard_EXPORT void SetTolTransition(const double aT);

  Standard_EXPORT double TolTransition() const;

  Standard_EXPORT void SetTol3D(const double aT);

  Standard_EXPORT double Tol3D() const;

  Standard_EXPORT void MakeWLine(const occ::handle<IntPatch_ALine>&                aline,
                                 NCollection_Sequence<occ::handle<IntPatch_Line>>& theLines) const;

  Standard_EXPORT void MakeWLine(const occ::handle<IntPatch_ALine>&                aline,
                                 const double                                      paraminf,
                                 const double                                      paramsup,
                                 NCollection_Sequence<occ::handle<IntPatch_Line>>& theLines) const;

protected:
  Standard_EXPORT bool StepComputing(const occ::handle<IntPatch_ALine>& theALine,
                                     const IntSurf_PntOn2S&             thePOn2S,
                                     const double                       theLastParOfAline,
                                     const double                       theCurParam,
                                     const double                       theTgMagnitude,
                                     const double                       theStepMin,
                                     const double                       theStepMax,
                                     const double                       theMaxDeflection,
                                     double&                            theStep) const;

  Standard_EXPORT int CheckDeflection(const gp_XYZ& theMidPt, const double theMaxDeflection) const;

  Standard_EXPORT double GetSectionRadius(const gp_Pnt& thePnt3d) const;

  Standard_EXPORT void CorrectEndPoint(occ::handle<IntSurf_LineOn2S>& theLine,
                                       const int                      theIndex) const;

private:
  occ::handle<Adaptor3d_Surface> myS1;
  occ::handle<Adaptor3d_Surface> myS2;
  IntSurf_Quadric                myQuad1;
  IntSurf_Quadric                myQuad2;

  int    myNbPointsInWline;
  double myTolOpenDomain;
  double myTolTransition;
  double myTol3D;
};
