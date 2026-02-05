#include <IntWalk_TheFunctionOfTheInt2S.hpp>

#include <StdFail_UndefinedDerivative.hpp>
#include <Standard_ConstructionError.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <math_Matrix.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define IntImp_ZerParFunc IntWalk_TheFunctionOfTheInt2S
#define IntImp_ZerParFunc_hxx <IntWalk_TheFunctionOfTheInt2S.hpp>
#include <IntImp_ZerParFunc.hpp>
