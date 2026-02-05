#include <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine BRepApprox_TheMultiLineOfApprox
#define MultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define ToolLine BRepApprox_TheMultiLineToolOfApprox
#define ToolLine_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define AppParCurves_ParLeastSquare BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_ParLeastSquare_hxx                                                            \
  <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define AppParCurves_ResConstraint BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_ResConstraint_hxx                                                             \
  <BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define AppParCurves_ParFunction BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_ParFunction_hxx                                                               \
  <BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define AppParCurves_Gradient_BFGS BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_Gradient_BFGS_hxx                                                             \
  <BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define AppParCurves_Gradient BRepApprox_MyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_Gradient_hxx <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>
#include <AppParCurves_Gradient.hpp>
