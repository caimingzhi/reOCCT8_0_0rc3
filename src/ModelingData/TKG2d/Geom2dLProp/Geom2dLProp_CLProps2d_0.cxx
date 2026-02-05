#include <Geom2dLProp_CLProps2d.hpp>

#include <Geom2d_Curve.hpp>
#include <LProp_BadContinuity.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <LProp_NotDefined.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Dir2d.hpp>
#include <Geom2dLProp_Curve2dTool.hpp>

#define Curve occ::handle<Geom2d_Curve>
#define Curve_hxx <Geom2d_Curve.hpp>
#define Vec gp_Vec2d
#define Vec_hxx <gp_Vec2d.hpp>
#define Pnt gp_Pnt2d
#define Pnt_hxx <gp_Pnt2d.hpp>
#define Dir gp_Dir2d
#define Dir_hxx <gp_Dir2d.hpp>
#define Tool Geom2dLProp_Curve2dTool
#define Tool_hxx <Geom2dLProp_Curve2dTool.hpp>
#define LProp_CLProps Geom2dLProp_CLProps2d
#define LProp_CLProps_hxx <Geom2dLProp_CLProps2d.hpp>
#include <LProp_CLProps.hpp>
