#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter.hpp>
#include <math_Vector.hpp>
class Adaptor2d_Curve2d;
class Geom2dInt_Geom2dCurveTool;
class Geom2dInt_TheProjPCurOfGInter;
class Geom2dInt_TheIntPCurvePCurveOfGInter;
class Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter;
class Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter;

class Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter(
    const Adaptor2d_Curve2d& C1,
    const Adaptor2d_Curve2d& C2,
    const double             Tol);

  Standard_EXPORT void Perform(const Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter& Poly1,
                               const Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter& Poly2,
                               int&                                                      NumSegOn1,
                               int&                                                      NumSegOn2,
                               double& ParamOnSeg1,
                               double& ParamOnSeg2);

  Standard_EXPORT void Perform(const double Uo,
                               const double Vo,
                               const double UInf,
                               const double VInf,
                               const double USup,
                               const double VSup);

  Standard_EXPORT int NbRoots() const;

  Standard_EXPORT void Roots(double& U, double& V);

  Standard_EXPORT bool AnErrorOccurred() const;

private:
  Standard_EXPORT void MathPerform();

  bool                                                        done;
  int                                                         nbroots;
  double                                                      myTol;
  Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter FctDist;
  math_Vector                                                 ToleranceVector;
  math_Vector                                                 BInfVector;
  math_Vector                                                 BSupVector;
  math_Vector                                                 StartingPoint;
  math_Vector                                                 Root;
  bool                                                        anErrorOccurred;
};

