#include <Contap_TheSearchInside.hpp>

#include <StdFail_NotDone.hpp>
#include <Standard_OutOfRange.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <Adaptor3d_TopolTool.hpp>
#include <Contap_HContTool.hpp>
#include <Contap_SurfFunction.hpp>
#include <IntSurf_InteriorPoint.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define Handle_TheTopolTool occ::handle<Adaptor3d_TopolTool>
#define TheTopolTool Adaptor3d_TopolTool
#define TheTopolTool_hxx <Adaptor3d_TopolTool.hpp>
#define TheSITool Contap_HContTool
#define TheSITool_hxx <Contap_HContTool.hpp>
#define TheFunction Contap_SurfFunction
#define TheFunction_hxx <Contap_SurfFunction.hpp>
#define IntStart_SearchInside Contap_TheSearchInside
#define IntStart_SearchInside_hxx <Contap_TheSearchInside.hpp>
#include <IntStart_SearchInside.hpp>
