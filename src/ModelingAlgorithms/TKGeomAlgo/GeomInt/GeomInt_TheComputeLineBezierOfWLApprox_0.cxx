#include <GeomInt_TheComputeLineBezierOfWLApprox.hpp>

#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>

#define MultiLine GeomInt_TheMultiLineOfWLApprox
#define MultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define LineTool GeomInt_TheMultiLineToolOfWLApprox
#define LineTool_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#define Approx_MyGradient GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_MyGradient_hxx <GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_ParLeastSquareOfMyGradient                                                          \
  GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_ParLeastSquareOfMyGradient_hxx                                                      \
  <GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_ResConstraintOfMyGradient                                                           \
  GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_ResConstraintOfMyGradient_hxx                                                       \
  <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_ParFunctionOfMyGradient                                                             \
  GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_ParFunctionOfMyGradient_hxx                                                         \
  <GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_Gradient_BFGSOfMyGradient                                                           \
  GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_Gradient_BFGSOfMyGradient_hxx                                                       \
  <GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_ParLeastSquareOfMyGradient                                                          \
  GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_ParLeastSquareOfMyGradient_hxx                                                      \
  <GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_ResConstraintOfMyGradient                                                           \
  GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_ResConstraintOfMyGradient_hxx                                                       \
  <GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_ParFunctionOfMyGradient                                                             \
  GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_ParFunctionOfMyGradient_hxx                                                         \
  <GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_Gradient_BFGSOfMyGradient                                                           \
  GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox
#define Approx_Gradient_BFGSOfMyGradient_hxx                                                       \
  <GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox.hpp>
#define Approx_ComputeLine GeomInt_TheComputeLineBezierOfWLApprox
#define Approx_ComputeLine_hxx <GeomInt_TheComputeLineBezierOfWLApprox.hpp>
#include <Approx_ComputeLine.hpp>
