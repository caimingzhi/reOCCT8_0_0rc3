#include <GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>

#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine GeomInt_TheMultiLineOfWLApprox
#define MultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define ToolLine GeomInt_TheMultiLineToolOfWLApprox
#define ToolLine_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#define Squares GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Squares_hxx <GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define ResolCons GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox
#define ResolCons_hxx <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define AppParCurves_Function GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox
#define AppParCurves_Function_hxx                                                                  \
  <GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <AppParCurves_Function.hpp>
