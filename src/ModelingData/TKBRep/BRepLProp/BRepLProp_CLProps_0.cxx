#include <BRepLProp_CLProps.hpp>

#include <LProp_BadContinuity.hpp>
#include <Standard_DomainError.hpp>
#include <Standard_OutOfRange.hpp>
#include <LProp_NotDefined.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
#include <BRepLProp_CurveTool.hpp>

#define Curve BRepAdaptor_Curve
#define Curve_hxx <BRepAdaptor_Curve.hpp>
#define Vec gp_Vec
#define Vec_hxx <gp_Vec.hpp>
#define Pnt gp_Pnt
#define Pnt_hxx <gp_Pnt.hpp>
#define Dir gp_Dir
#define Dir_hxx <gp_Dir.hpp>
#define Tool BRepLProp_CurveTool
#define Tool_hxx <BRepLProp_CurveTool.hpp>
#define LProp_CLProps BRepLProp_CLProps
#define LProp_CLProps_hxx <BRepLProp_CLProps.hpp>
#include <LProp_CLProps.hpp>
