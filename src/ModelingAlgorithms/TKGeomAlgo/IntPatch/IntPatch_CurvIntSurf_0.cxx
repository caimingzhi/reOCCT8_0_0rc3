#include <IntPatch_CurvIntSurf.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <Adaptor2d_Curve2d.hpp>
#include <IntPatch_HCurve2dTool.hpp>
#include <IntPatch_CSFunction.hpp>
#include <math_FunctionSetRoot.hpp>
#include <gp_Pnt.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheCurve occ::handle<Adaptor2d_Curve2d>
#define TheCurve_hxx <Adaptor2d_Curve2d.hpp>
#define TheCurveTool IntPatch_HCurve2dTool
#define TheCurveTool_hxx <IntPatch_HCurve2dTool.hpp>
#define TheFunction IntPatch_CSFunction
#define TheFunction_hxx <IntPatch_CSFunction.hpp>
#define IntImp_IntCS IntPatch_CurvIntSurf
#define IntImp_IntCS_hxx <IntPatch_CurvIntSurf.hpp>
#include <IntImp_IntCS.hpp>
