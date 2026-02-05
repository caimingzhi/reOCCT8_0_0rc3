#include <BRepApprox_MyGradientOfTheComputeLineBezierOfApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine BRepApprox_TheMultiLineOfApprox
#define MultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define ToolLine BRepApprox_TheMultiLineToolOfApprox
#define ToolLine_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define AppParCurves_ParLeastSquare                                                                \
  BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox
#define AppParCurves_ParLeastSquare_hxx                                                            \
  <BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define AppParCurves_ResConstraint                                                                 \
  BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox
#define AppParCurves_ResConstraint_hxx                                                             \
  <BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define AppParCurves_ParFunction BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox
#define AppParCurves_ParFunction_hxx                                                               \
  <BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define AppParCurves_Gradient_BFGS                                                                 \
  BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox
#define AppParCurves_Gradient_BFGS_hxx                                                             \
  <BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#define AppParCurves_Gradient BRepApprox_MyGradientOfTheComputeLineBezierOfApprox
#define AppParCurves_Gradient_hxx <BRepApprox_MyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <AppParCurves_Gradient.hpp>
