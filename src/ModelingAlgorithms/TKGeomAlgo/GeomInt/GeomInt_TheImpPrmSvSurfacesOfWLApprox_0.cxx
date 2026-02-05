#include <GeomInt_TheImpPrmSvSurfacesOfWLApprox.hpp>

#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_HSurfaceTool.hpp>
#include <IntSurf_Quadric.hpp>
#include <IntSurf_QuadricTool.hpp>
#include <IntPatch_WLine.hpp>
#include <GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

#define ThePSurface occ::handle<Adaptor3d_Surface>
#define ThePSurface_hxx <Adaptor3d_Surface.hpp>
#define ThePSurfaceTool Adaptor3d_HSurfaceTool
#define ThePSurfaceTool_hxx <Adaptor3d_HSurfaceTool.hpp>
#define TheISurface IntSurf_Quadric
#define TheISurface_hxx <IntSurf_Quadric.hpp>
#define TheISurfaceTool IntSurf_QuadricTool
#define TheISurfaceTool_hxx <IntSurf_QuadricTool.hpp>
#define Handle_TheLine occ::handle<IntPatch_WLine>
#define TheLine IntPatch_WLine
#define TheLine_hxx <IntPatch_WLine.hpp>
#define ApproxInt_TheZerImpFunc GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox
#define ApproxInt_TheZerImpFunc_hxx <GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox.hpp>
#define ApproxInt_ImpPrmSvSurfaces GeomInt_TheImpPrmSvSurfacesOfWLApprox
#define ApproxInt_ImpPrmSvSurfaces_hxx <GeomInt_TheImpPrmSvSurfacesOfWLApprox.hpp>
#include <ApproxInt_ImpPrmSvSurfaces.hpp>
