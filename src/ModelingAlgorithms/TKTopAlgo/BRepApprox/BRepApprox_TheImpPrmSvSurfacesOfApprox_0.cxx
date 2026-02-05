#include <BRepApprox_TheImpPrmSvSurfacesOfApprox.hpp>

#include <BRepAdaptor_Surface.hpp>
#include <BRepApprox_SurfaceTool.hpp>
#include <IntSurf_Quadric.hpp>
#include <IntSurf_QuadricTool.hpp>
#include <BRepApprox_ApproxLine.hpp>
#include <BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Vec2d.hpp>

#define ThePSurface BRepAdaptor_Surface
#define ThePSurface_hxx <BRepAdaptor_Surface.hpp>
#define ThePSurfaceTool BRepApprox_SurfaceTool
#define ThePSurfaceTool_hxx <BRepApprox_SurfaceTool.hpp>
#define TheISurface IntSurf_Quadric
#define TheISurface_hxx <IntSurf_Quadric.hpp>
#define TheISurfaceTool IntSurf_QuadricTool
#define TheISurfaceTool_hxx <IntSurf_QuadricTool.hpp>
#define Handle_TheLine occ::handle<BRepApprox_ApproxLine>
#define TheLine BRepApprox_ApproxLine
#define TheLine_hxx <BRepApprox_ApproxLine.hpp>
#define ApproxInt_TheZerImpFunc BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox
#define ApproxInt_TheZerImpFunc_hxx <BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox.hpp>
#define ApproxInt_ImpPrmSvSurfaces BRepApprox_TheImpPrmSvSurfacesOfApprox
#define ApproxInt_ImpPrmSvSurfaces_hxx <BRepApprox_TheImpPrmSvSurfacesOfApprox.hpp>
#include <ApproxInt_ImpPrmSvSurfaces.hpp>
