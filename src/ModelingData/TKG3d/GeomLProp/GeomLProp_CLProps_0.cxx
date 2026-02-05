#include <GeomLProp_CLProps.hpp>

#include <Geom_Curve.hpp>
#include <LProp_BadContinuity.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <LProp_NotDefined.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <GeomLProp_CurveTool.hpp>

#define Curve occ::handle<Geom_Curve>
#define Curve_hxx <Geom_Curve.hpp>
#define Vec gp_Vec
#define Vec_hxx <gp_Vec.hpp>
#define Pnt gp_Pnt
#define Pnt_hxx <gp_Pnt.hpp>
#define Dir gp_Dir
#define Dir_hxx <gp_Dir.hpp>
#define Tool GeomLProp_CurveTool
#define Tool_hxx <GeomLProp_CurveTool.hpp>
#define LProp_CLProps GeomLProp_CLProps
#define LProp_CLProps_hxx <GeomLProp_CLProps.hpp>
#include <LProp_CLProps.hpp>
