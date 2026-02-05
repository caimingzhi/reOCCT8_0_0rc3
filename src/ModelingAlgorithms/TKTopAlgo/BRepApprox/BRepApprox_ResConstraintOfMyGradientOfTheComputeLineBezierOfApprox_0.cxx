#include <BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <math_Matrix.hpp>

#define MultiLine BRepApprox_TheMultiLineOfApprox
#define MultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define ToolLine BRepApprox_TheMultiLineToolOfApprox
#define ToolLine_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define AppParCurves_ResolConstraint                                                               \
  BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox
#define AppParCurves_ResolConstraint_hxx                                                           \
  <BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox.hpp>
#include <AppParCurves_ResolConstraint.hpp>
