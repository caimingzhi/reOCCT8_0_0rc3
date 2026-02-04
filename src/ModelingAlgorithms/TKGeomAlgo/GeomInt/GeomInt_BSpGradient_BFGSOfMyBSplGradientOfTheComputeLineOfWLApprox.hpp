#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_BFGS.hpp>
#include <math_Vector.hpp>
class GeomInt_TheMultiLineOfWLApprox;
class GeomInt_TheMultiLineToolOfWLApprox;
class GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox;
class GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox;
class GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox;
class math_MultipleVarFunctionWithGradient;

class GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox : public math_BFGS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox(
    math_MultipleVarFunctionWithGradient& F,
    const math_Vector&                    StartingPoint,
    const double                          Tolerance3d,
    const double                          Tolerance2d,
    const double                          Eps,
    const int                             NbIterations = 200);

  Standard_EXPORT bool IsSolutionReached(math_MultipleVarFunctionWithGradient& F) const override;

private:
  double myTol3d;
  double myTol2d;
};

