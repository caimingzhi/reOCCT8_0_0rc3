#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <math_BFGS.hpp>
#include <math_Vector.hpp>
class AppDef_MultiLine;
class AppDef_MyLineTool;
class AppDef_TheGradient;
class AppDef_ParLeastSquareOfTheGradient;
class AppDef_ResConstraintOfTheGradient;
class AppDef_ParFunctionOfTheGradient;
class math_MultipleVarFunctionWithGradient;

class AppDef_Gradient_BFGSOfTheGradient : public math_BFGS
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT AppDef_Gradient_BFGSOfTheGradient(math_MultipleVarFunctionWithGradient& F,
                                                    const math_Vector& StartingPoint,
                                                    const double       Tolerance3d,
                                                    const double       Tolerance2d,
                                                    const double       Eps,
                                                    const int          NbIterations = 200);

  Standard_EXPORT bool IsSolutionReached(math_MultipleVarFunctionWithGradient& F) const override;

private:
  double myTol3d;
  double myTol2d;
};

