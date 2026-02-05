#include <LProp3d_SLProps.hpp>

#include <Adaptor3d_Surface.hpp>
#include <LProp_BadContinuity.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <LProp_NotDefined.hpp>
#include <LProp3d_SurfaceTool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>

#define Surface occ::handle<Adaptor3d_Surface>
#define Surface_hxx <Adaptor3d_Surface.hpp>
#define Tool LProp3d_SurfaceTool
#define Tool_hxx <LProp3d_SurfaceTool.hpp>
#define LProp_SLProps LProp3d_SLProps
#define LProp_SLProps_hxx <LProp3d_SLProps.hpp>
#include <LProp_SLProps.hpp>
