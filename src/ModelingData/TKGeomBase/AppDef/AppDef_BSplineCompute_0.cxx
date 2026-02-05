#include <AppDef_BSplineCompute.hpp>

#include <AppDef_MultiLine.hpp>
#include <AppDef_MyLineTool.hpp>
#include <AppDef_MyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute.hpp>
#include <AppDef_MyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ResConstraintOfMyGradientbisOfBSplineCompute.hpp>
#include <AppDef_ParFunctionOfMyGradientbisOfBSplineCompute.hpp>
#include <AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine AppDef_MultiLine
#define MultiLine_hxx <AppDef_MultiLine.hpp>
#define LineTool AppDef_MyLineTool
#define LineTool_hxx <AppDef_MyLineTool.hpp>
#define Approx_MyBSplGradient AppDef_MyBSplGradientOfBSplineCompute
#define Approx_MyBSplGradient_hxx <AppDef_MyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpParLeastSquareOfMyBSplGradient                                                   \
  AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute
#define Approx_BSpParLeastSquareOfMyBSplGradient_hxx                                               \
  <AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpParFunctionOfMyBSplGradient AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute
#define Approx_BSpParFunctionOfMyBSplGradient_hxx                                                  \
  <AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpGradient_BFGSOfMyBSplGradient                                                    \
  AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute
#define Approx_BSpGradient_BFGSOfMyBSplGradient_hxx                                                \
  <AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpParLeastSquareOfMyBSplGradient                                                   \
  AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute
#define Approx_BSpParLeastSquareOfMyBSplGradient_hxx                                               \
  <AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpParFunctionOfMyBSplGradient AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute
#define Approx_BSpParFunctionOfMyBSplGradient_hxx                                                  \
  <AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_BSpGradient_BFGSOfMyBSplGradient                                                    \
  AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute
#define Approx_BSpGradient_BFGSOfMyBSplGradient_hxx                                                \
  <AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute.hpp>
#define Approx_MyGradientbis AppDef_MyGradientbisOfBSplineCompute
#define Approx_MyGradientbis_hxx <AppDef_MyGradientbisOfBSplineCompute.hpp>
#define Approx_ParLeastSquareOfMyGradientbis AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute
#define Approx_ParLeastSquareOfMyGradientbis_hxx                                                   \
  <AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ResConstraintOfMyGradientbis AppDef_ResConstraintOfMyGradientbisOfBSplineCompute
#define Approx_ResConstraintOfMyGradientbis_hxx                                                    \
  <AppDef_ResConstraintOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ParFunctionOfMyGradientbis AppDef_ParFunctionOfMyGradientbisOfBSplineCompute
#define Approx_ParFunctionOfMyGradientbis_hxx                                                      \
  <AppDef_ParFunctionOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_Gradient_BFGSOfMyGradientbis AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute
#define Approx_Gradient_BFGSOfMyGradientbis_hxx                                                    \
  <AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ParLeastSquareOfMyGradientbis AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute
#define Approx_ParLeastSquareOfMyGradientbis_hxx                                                   \
  <AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ResConstraintOfMyGradientbis AppDef_ResConstraintOfMyGradientbisOfBSplineCompute
#define Approx_ResConstraintOfMyGradientbis_hxx                                                    \
  <AppDef_ResConstraintOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_ParFunctionOfMyGradientbis AppDef_ParFunctionOfMyGradientbisOfBSplineCompute
#define Approx_ParFunctionOfMyGradientbis_hxx                                                      \
  <AppDef_ParFunctionOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_Gradient_BFGSOfMyGradientbis AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute
#define Approx_Gradient_BFGSOfMyGradientbis_hxx                                                    \
  <AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute.hpp>
#define Approx_BSplComputeLine AppDef_BSplineCompute
#define Approx_BSplComputeLine_hxx <AppDef_BSplineCompute.hpp>
#include <Approx_BSplComputeLine.hpp>
