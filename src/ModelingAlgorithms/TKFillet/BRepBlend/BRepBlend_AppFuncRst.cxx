#include <Blend_SurfRstFunction.hpp>
#include <BRepBlend_AppFuncRst.hpp>
#include <BRepBlend_Line.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepBlend_AppFuncRst, BRepBlend_AppFuncRoot)

BRepBlend_AppFuncRst::BRepBlend_AppFuncRst(occ::handle<BRepBlend_Line>& Line,
                                           Blend_SurfRstFunction&       Func,
                                           const double                 Tol3d,
                                           const double                 Tol2d)
    : BRepBlend_AppFuncRoot(Line, Func, Tol3d, Tol2d)
{
}

void BRepBlend_AppFuncRst::Point(const Blend_AppFunction& Func,
                                 const double             Param,
                                 const math_Vector&       theSol,
                                 Blend_Point&             Pnt) const
{
  Pnt.SetValue(Func.Pnt1(), Func.Pnt2(), Param, theSol(1), theSol(2), theSol(3));
}

void BRepBlend_AppFuncRst::Vec(math_Vector& theSol, const Blend_Point& Pnt) const
{
  Pnt.ParametersOnS(theSol(1), theSol(2));
  theSol(3) = Pnt.ParameterOnC();
}
