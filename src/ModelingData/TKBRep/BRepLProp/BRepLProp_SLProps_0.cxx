#include <BRepLProp_SLProps.hpp>

#include <LProp_BadContinuity.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <LProp_NotDefined.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepLProp_SurfaceTool.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_Dir.hpp>

#define Surface BRepAdaptor_Surface
#define Surface_hxx <BRepAdaptor_Surface.hpp>
#define Tool BRepLProp_SurfaceTool
#define Tool_hxx <BRepLProp_SurfaceTool.hpp>
#define LProp_SLProps BRepLProp_SLProps
#define LProp_SLProps_hxx <BRepLProp_SLProps.hpp>
#include <LProp_SLProps.hpp>
