#include <AppDef_MyGradientOfCompute.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_ParLeastSquareOfMyGradientOfCompute.hpp>
#include <AppDef_ResConstraintOfMyGradientOfCompute.hpp>
#include <AppDef_ParFunctionOfMyGradientOfCompute.hpp>
#include <AppDef_Gradient_BFGSOfMyGradientOfCompute.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine AppDef_MultiLine
#define MultiLine_hxx <AppDef_MultiLine.hpp>
#define ToolLine AppDef_MyLineTool
#define ToolLine_hxx <AppDef_MyLineTool.hpp>
#define AppParCurves_ParLeastSquare AppDef_ParLeastSquareOfMyGradientOfCompute
#define AppParCurves_ParLeastSquare_hxx <AppDef_ParLeastSquareOfMyGradientOfCompute.hpp>
#define AppParCurves_ResConstraint AppDef_ResConstraintOfMyGradientOfCompute
#define AppParCurves_ResConstraint_hxx <AppDef_ResConstraintOfMyGradientOfCompute.hpp>
#define AppParCurves_ParFunction AppDef_ParFunctionOfMyGradientOfCompute
#define AppParCurves_ParFunction_hxx <AppDef_ParFunctionOfMyGradientOfCompute.hpp>
#define AppParCurves_Gradient_BFGS AppDef_Gradient_BFGSOfMyGradientOfCompute
#define AppParCurves_Gradient_BFGS_hxx <AppDef_Gradient_BFGSOfMyGradientOfCompute.hpp>
#define AppParCurves_Gradient AppDef_MyGradientOfCompute
#define AppParCurves_Gradient_hxx <AppDef_MyGradientOfCompute.hpp>
#include <AppParCurves_Gradient.hpp>
