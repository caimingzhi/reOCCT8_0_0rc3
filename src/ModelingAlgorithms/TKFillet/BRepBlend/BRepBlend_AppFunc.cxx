#include <Blend_Function.hpp>
#include <BRepBlend_AppFunc.hpp>
#include <BRepBlend_Line.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepBlend_AppFunc, BRepBlend_AppFuncRoot)

BRepBlend_AppFunc::BRepBlend_AppFunc(occ::handle<BRepBlend_Line>& Line,
                                     Blend_Function&              Func,
                                     const double                 Tol3d,
                                     const double                 Tol2d)
    : BRepBlend_AppFuncRoot(Line, Func, Tol3d, Tol2d)
{
}

void BRepBlend_AppFunc::Point(const Blend_AppFunction& Func,
                              const double             Param,
                              const math_Vector&       theSol,
                              Blend_Point&             Pnt) const
{
  Pnt.SetValue(Func.Pnt1(), Func.Pnt2(), Param, theSol(1), theSol(2), theSol(3), theSol(4));
}

void BRepBlend_AppFunc::Vec(math_Vector& theSol, const Blend_Point& Pnt) const
{
  Pnt.ParametersOnS1(theSol(1), theSol(2));
  Pnt.ParametersOnS2(theSol(3), theSol(4));
}
