#include <IntWalk_TheInt2S.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_ConstructionError.hpp>
#include <StdFail_UndefinedDerivative.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <IntWalk_TheFunctionOfTheInt2S.hpp>
#include <math_FunctionSetRoot.hpp>
#include <IntSurf_PntOn2S.hpp>
#include <gp_Dir.hpp>
#include <gp_Dir2d.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define IntImp_TheFunction IntWalk_TheFunctionOfTheInt2S
#define IntImp_TheFunction_hxx <IntWalk_TheFunctionOfTheInt2S.hpp>
#define IntImp_Int2S IntWalk_TheInt2S
#define IntImp_Int2S_hxx <IntWalk_TheInt2S.hpp>
#include <IntImp_Int2S.hpp>
