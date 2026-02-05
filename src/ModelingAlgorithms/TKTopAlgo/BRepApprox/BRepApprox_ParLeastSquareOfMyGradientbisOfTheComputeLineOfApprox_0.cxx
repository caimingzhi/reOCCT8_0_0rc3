#include <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>
#include <Standard_DimensionError.hpp>
#include <Standard_NoSuchObject.hpp>
#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <AppParCurves_MultiCurve.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <math_Matrix.hpp>

#define MultiLine BRepApprox_TheMultiLineOfApprox
#define MultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define ToolLine BRepApprox_TheMultiLineToolOfApprox
#define ToolLine_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define AppParCurves_LeastSquare BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox
#define AppParCurves_LeastSquare_hxx                                                               \
  <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <AppParCurves_LeastSquare.hpp>
