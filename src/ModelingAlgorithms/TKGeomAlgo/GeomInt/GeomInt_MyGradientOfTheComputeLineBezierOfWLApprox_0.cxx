#include <GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine GeomInt_TheMultiLineOfWLApprox
#define MultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define ToolLine GeomInt_TheMultiLineToolOfWLApprox
#define ToolLine_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#define AppParCurves_ParLeastSquare                                                                \
  GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox
#define AppParCurves_ParLeastSquare_hxx                                                            \
  <GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define AppParCurves_ResConstraint GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox
#define AppParCurves_ResConstraint_hxx                                                             \
  <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define AppParCurves_ParFunction GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox
#define AppParCurves_ParFunction_hxx                                                               \
  <GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define AppParCurves_Gradient_BFGS GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox
#define AppParCurves_Gradient_BFGS_hxx                                                             \
  <GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define AppParCurves_Gradient GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox
#define AppParCurves_Gradient_hxx <GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <AppParCurves_Gradient.hpp>
