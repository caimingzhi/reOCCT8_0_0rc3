#include <GeomLProp_SLProps.hpp>

#include <Geom_Surface.hpp>
#include <LProp_BadContinuity.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <LProp_NotDefined.hpp>
#include <GeomLProp_SurfaceTool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>

#define Surface occ::handle<Geom_Surface>
#define Surface_hxx <Geom_Surface.hpp>
#define Tool GeomLProp_SurfaceTool
#define Tool_hxx <GeomLProp_SurfaceTool.hpp>
#define LProp_SLProps GeomLProp_SLProps
#define LProp_SLProps_hxx <GeomLProp_SLProps.hpp>
#include <LProp_SLProps.hpp>
