#include <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <math_Matrix.hpp>

#define MultiLine GeomInt_TheMultiLineOfWLApprox
#define MultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define ToolLine GeomInt_TheMultiLineToolOfWLApprox
#define ToolLine_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#define AppParCurves_ResolConstraint                                                               \
  GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox
#define AppParCurves_ResolConstraint_hxx                                                           \
  <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <AppParCurves_ResolConstraint.hpp>
