#include <BRepApprox_MyBSplGradientOfTheComputeLineOfApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>

#define MultiLine BRepApprox_TheMultiLineOfApprox
#define MultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define ToolLine BRepApprox_TheMultiLineToolOfApprox
#define ToolLine_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define AppParCurves_BSpParLeastSquare                                                             \
  BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox
#define AppParCurves_BSpParLeastSquare_hxx                                                         \
  <BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define AppParCurves_BSpParFunction                                                                \
  BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox
#define AppParCurves_BSpParFunction_hxx                                                            \
  <BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define AppParCurves_BSpGradient_BFGS                                                              \
  BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox
#define AppParCurves_BSpGradient_BFGS_hxx                                                          \
  <BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define AppParCurves_BSpGradient BRepApprox_MyBSplGradientOfTheComputeLineOfApprox
#define AppParCurves_BSpGradient_hxx <BRepApprox_MyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <AppParCurves_BSpGradient.hpp>
