#include <Blend_RstRstFunction.hpp>
#include <BRepBlend_AppFuncRstRst.hpp>
#include <BRepBlend_Line.hpp>
#include <Standard_Type.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepBlend_AppFuncRstRst, BRepBlend_AppFuncRoot)

BRepBlend_AppFuncRstRst::BRepBlend_AppFuncRstRst(occ::handle<BRepBlend_Line>& Line,
                                                 Blend_RstRstFunction&        Func,
                                                 const double                 Tol3d,
                                                 const double                 Tol2d)
    : BRepBlend_AppFuncRoot(Line, Func, Tol3d, Tol2d)
{
}

void BRepBlend_AppFuncRstRst::Point(const Blend_AppFunction& Func,
                                    const double             Param,
                                    const math_Vector&       theSol,
                                    Blend_Point&             Pnt) const
{
  Pnt.SetValue(Func.Pnt1(), Func.Pnt2(), Param, theSol(1), theSol(2));
}

void BRepBlend_AppFuncRstRst::Vec(math_Vector& theSol, const Blend_Point& Pnt) const
{
  theSol(1) = Pnt.ParameterOnC1();
  theSol(2) = Pnt.ParameterOnC2();
}
