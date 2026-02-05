#include <IntCurveSurface_TheCSFunctionOfHInter.hpp>

#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <IntCurveSurface_TheHCurveTool.hpp>
#include <math_Matrix.hpp>
#include <gp_Pnt.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheCurve occ::handle<Adaptor3d_Curve>
#define TheCurve_hxx <Adaptor3d_Curve.hpp>
#define TheCurveTool IntCurveSurface_TheHCurveTool
#define TheCurveTool_hxx <IntCurveSurface_TheHCurveTool.hpp>
#define IntImp_ZerCSParFunc IntCurveSurface_TheCSFunctionOfHInter
#define IntImp_ZerCSParFunc_hxx <IntCurveSurface_TheCSFunctionOfHInter.hpp>
#include <IntImp_ZerCSParFunc.hpp>
