#include <IntCurveSurface_TheExactHInter.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <Adaptor3d_Curve.hpp>
#include <IntCurveSurface_TheHCurveTool.hpp>
#include <IntCurveSurface_TheCSFunctionOfHInter.hpp>
#include <math_FunctionSetRoot.hpp>
#include <gp_Pnt.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheCurve occ::handle<Adaptor3d_Curve>
#define TheCurve_hxx <Adaptor3d_Curve.hpp>
#define TheCurveTool IntCurveSurface_TheHCurveTool
#define TheCurveTool_hxx <IntCurveSurface_TheHCurveTool.hpp>
#define TheFunction IntCurveSurface_TheCSFunctionOfHInter
#define TheFunction_hxx <IntCurveSurface_TheCSFunctionOfHInter.hpp>
#define IntImp_IntCS IntCurveSurface_TheExactHInter
#define IntImp_IntCS_hxx <IntCurveSurface_TheExactHInter.hpp>
#include <IntImp_IntCS.hpp>
