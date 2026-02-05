#include <AppDef_MyBSplGradientOfBSplineCompute.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>

#define MultiLine AppDef_MultiLine
#define MultiLine_hxx <AppDef_MultiLine.hpp>
#define ToolLine AppDef_MyLineTool
#define ToolLine_hxx <AppDef_MyLineTool.hpp>
#define AppParCurves_BSpParLeastSquare AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute
#define AppParCurves_BSpParLeastSquare_hxx                                                         \
  <AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute.hpp>
#define AppParCurves_BSpParFunction AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute
#define AppParCurves_BSpParFunction_hxx <AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute.hpp>
#define AppParCurves_BSpGradient_BFGS AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute
#define AppParCurves_BSpGradient_BFGS_hxx                                                          \
  <AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute.hpp>
#define AppParCurves_BSpGradient AppDef_MyBSplGradientOfBSplineCompute
#define AppParCurves_BSpGradient_hxx <AppDef_MyBSplGradientOfBSplineCompute.hpp>
#include <AppParCurves_BSpGradient.hpp>
