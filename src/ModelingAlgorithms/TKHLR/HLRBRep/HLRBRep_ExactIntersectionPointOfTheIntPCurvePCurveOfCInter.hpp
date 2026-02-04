#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRBRep_TypeDef.hpp>
#include <Standard_Boolean.hpp>
#include <HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter.hpp>
#include <math_Vector.hpp>
class HLRBRep_CurveTool;
class HLRBRep_TheProjPCurOfCInter;
class HLRBRep_TheIntPCurvePCurveOfCInter;
class HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter;
class HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter;

class HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_ExactIntersectionPointOfTheIntPCurvePCurveOfCInter(
    const HLRBRep_CurvePtr& C1,
    const HLRBRep_CurvePtr& C2,
    const double            Tol);

  Standard_EXPORT void Perform(const HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter& Poly1,
                               const HLRBRep_ThePolygon2dOfTheIntPCurvePCurveOfCInter& Poly2,
                               int&                                                    NumSegOn1,
                               int&                                                    NumSegOn2,
                               double&                                                 ParamOnSeg1,
                               double&                                                 ParamOnSeg2);

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

  bool                                                      done;
  int                                                       nbroots;
  double                                                    myTol;
  HLRBRep_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfCInter FctDist;
  math_Vector                                               ToleranceVector;
  math_Vector                                               BInfVector;
  math_Vector                                               BSupVector;
  math_Vector                                               StartingPoint;
  math_Vector                                               Root;
  bool                                                      anErrorOccurred;
};

