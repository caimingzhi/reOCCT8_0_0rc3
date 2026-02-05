#include <BRepApprox_TheComputeLineOfApprox.hpp>

#include <BRepApprox_TheMultiLineOfApprox.hpp>
#include <BRepApprox_TheMultiLineToolOfApprox.hpp>
#include <BRepApprox_MyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#include <AppParCurves_MultiBSpCurve.hpp>
#include <AppParCurves_MultiCurve.hpp>

#define MultiLine BRepApprox_TheMultiLineOfApprox
#define MultiLine_hxx <BRepApprox_TheMultiLineOfApprox.hpp>
#define LineTool BRepApprox_TheMultiLineToolOfApprox
#define LineTool_hxx <BRepApprox_TheMultiLineToolOfApprox.hpp>
#define Approx_MyBSplGradient BRepApprox_MyBSplGradientOfTheComputeLineOfApprox
#define Approx_MyBSplGradient_hxx <BRepApprox_MyBSplGradientOfTheComputeLineOfApprox.hpp>
#define Approx_BSpParLeastSquareOfMyBSplGradient                                                   \
  BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox
#define Approx_BSpParLeastSquareOfMyBSplGradient_hxx                                               \
  <BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define Approx_BSpParFunctionOfMyBSplGradient                                                      \
  BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox
#define Approx_BSpParFunctionOfMyBSplGradient_hxx                                                  \
  <BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define Approx_BSpGradient_BFGSOfMyBSplGradient                                                    \
  BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox
#define Approx_BSpGradient_BFGSOfMyBSplGradient_hxx                                                \
  <BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define Approx_BSpParLeastSquareOfMyBSplGradient                                                   \
  BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox
#define Approx_BSpParLeastSquareOfMyBSplGradient_hxx                                               \
  <BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define Approx_BSpParFunctionOfMyBSplGradient                                                      \
  BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox
#define Approx_BSpParFunctionOfMyBSplGradient_hxx                                                  \
  <BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define Approx_BSpGradient_BFGSOfMyBSplGradient                                                    \
  BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox
#define Approx_BSpGradient_BFGSOfMyBSplGradient_hxx                                                \
  <BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox.hpp>
#define Approx_MyGradientbis BRepApprox_MyGradientbisOfTheComputeLineOfApprox
#define Approx_MyGradientbis_hxx <BRepApprox_MyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_ParLeastSquareOfMyGradientbis                                                       \
  BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox
#define Approx_ParLeastSquareOfMyGradientbis_hxx                                                   \
  <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_ResConstraintOfMyGradientbis                                                        \
  BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox
#define Approx_ResConstraintOfMyGradientbis_hxx                                                    \
  <BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_ParFunctionOfMyGradientbis                                                          \
  BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox
#define Approx_ParFunctionOfMyGradientbis_hxx                                                      \
  <BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_Gradient_BFGSOfMyGradientbis                                                        \
  BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox
#define Approx_Gradient_BFGSOfMyGradientbis_hxx                                                    \
  <BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_ParLeastSquareOfMyGradientbis                                                       \
  BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox
#define Approx_ParLeastSquareOfMyGradientbis_hxx                                                   \
  <BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_ResConstraintOfMyGradientbis                                                        \
  BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox
#define Approx_ResConstraintOfMyGradientbis_hxx                                                    \
  <BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_ParFunctionOfMyGradientbis                                                          \
  BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox
#define Approx_ParFunctionOfMyGradientbis_hxx                                                      \
  <BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_Gradient_BFGSOfMyGradientbis                                                        \
  BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox
#define Approx_Gradient_BFGSOfMyGradientbis_hxx                                                    \
  <BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox.hpp>
#define Approx_BSplComputeLine BRepApprox_TheComputeLineOfApprox
#define Approx_BSplComputeLine_hxx <BRepApprox_TheComputeLineOfApprox.hpp>
#include <Approx_BSplComputeLine.hpp>
