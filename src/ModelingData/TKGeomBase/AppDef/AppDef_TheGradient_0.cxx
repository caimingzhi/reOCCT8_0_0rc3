#include <AppDef_TheGradient.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_ParLeastSquareOfTheGradient.hpp>
#include <AppDef_ResConstraintOfTheGradient.hpp>
#include <AppDef_ParFunctionOfTheGradient.hpp>
#include <AppDef_Gradient_BFGSOfTheGradient.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine AppDef_MultiLine
#define MultiLine_hxx <AppDef_MultiLine.hpp>
#define ToolLine AppDef_MyLineTool
#define ToolLine_hxx <AppDef_MyLineTool.hpp>
#define AppParCurves_ParLeastSquare AppDef_ParLeastSquareOfTheGradient
#define AppParCurves_ParLeastSquare_hxx <AppDef_ParLeastSquareOfTheGradient.hpp>
#define AppParCurves_ResConstraint AppDef_ResConstraintOfTheGradient
#define AppParCurves_ResConstraint_hxx <AppDef_ResConstraintOfTheGradient.hpp>
#define AppParCurves_ParFunction AppDef_ParFunctionOfTheGradient
#define AppParCurves_ParFunction_hxx <AppDef_ParFunctionOfTheGradient.hpp>
#define AppParCurves_Gradient_BFGS AppDef_Gradient_BFGSOfTheGradient
#define AppParCurves_Gradient_BFGS_hxx <AppDef_Gradient_BFGSOfTheGradient.hpp>
#define AppParCurves_Gradient AppDef_TheGradient
#define AppParCurves_Gradient_hxx <AppDef_TheGradient.hpp>
#include <AppParCurves_Gradient.hpp>
