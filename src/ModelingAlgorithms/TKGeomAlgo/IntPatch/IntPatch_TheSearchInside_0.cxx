#include <IntPatch_TheSearchInside.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <Adaptor3d_TopolTool.hpp>
#include <IntPatch_HInterTool.hpp>
#include <IntPatch_TheSurfFunction.hpp>
#include <IntSurf_InteriorPoint.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define Handle_TheTopolTool occ::handle<Adaptor3d_TopolTool>
#define TheTopolTool Adaptor3d_TopolTool
#define TheTopolTool_hxx <Adaptor3d_TopolTool.hpp>
#define TheSITool IntPatch_HInterTool
#define TheSITool_hxx <IntPatch_HInterTool.hpp>
#define TheFunction IntPatch_TheSurfFunction
#define TheFunction_hxx <IntPatch_TheSurfFunction.hpp>
#define IntStart_SearchInside IntPatch_TheSearchInside
#define IntStart_SearchInside_hxx <IntPatch_TheSearchInside.hpp>
#include <IntStart_SearchInside.hpp>
