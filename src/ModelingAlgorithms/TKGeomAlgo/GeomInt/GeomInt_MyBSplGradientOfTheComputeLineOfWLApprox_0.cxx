#include <GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox.hpp>

#include <Standard_OutOfRange.hpp>
#include <StdFail_NotDone.hpp>
#include <GeomInt_TheMultiLineOfWLApprox.hpp>
#include <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#include <GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>

#define MultiLine GeomInt_TheMultiLineOfWLApprox
#define MultiLine_hxx <GeomInt_TheMultiLineOfWLApprox.hpp>
#define ToolLine GeomInt_TheMultiLineToolOfWLApprox
#define ToolLine_hxx <GeomInt_TheMultiLineToolOfWLApprox.hpp>
#define AppParCurves_BSpParLeastSquare                                                             \
  GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox
#define AppParCurves_BSpParLeastSquare_hxx                                                         \
  <GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define AppParCurves_BSpParFunction GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox
#define AppParCurves_BSpParFunction_hxx                                                            \
  <GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define AppParCurves_BSpGradient_BFGS                                                              \
  GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox
#define AppParCurves_BSpGradient_BFGS_hxx                                                          \
  <GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#define AppParCurves_BSpGradient GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox
#define AppParCurves_BSpGradient_hxx <GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox.hpp>
#include <AppParCurves_BSpGradient.hpp>
