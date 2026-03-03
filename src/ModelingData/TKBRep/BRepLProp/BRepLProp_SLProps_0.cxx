#include <BRepLProp_SLProps.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepLProp_SurfaceTool.hpp>

#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>

#include <LProp_SLProps_0.hpp>

#define Surface ::model::adapter::BRepAdaptor_Surface
#define Surface_hxx <BRepAdaptor_Surface.hpp>
#define Tool ::model::localproperties::BRepLProp_SurfaceTool
#define Tool_hxx <BRepLProp_SurfaceTool.hpp>
namespace model { namespace localproperties {
#define LProp_SLProps BRepLProp_SLProps
#define LProp_SLProps_hxx <BRepLProp_SLProps.hpp>
#include <LProp_SLProps.hpp>

}} // namespace model::localproperties
