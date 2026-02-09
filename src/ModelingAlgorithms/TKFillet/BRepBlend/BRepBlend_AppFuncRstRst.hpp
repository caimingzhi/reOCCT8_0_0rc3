#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepBlend_AppFuncRoot.hpp>
#include <math_Vector.hpp>
class BRepBlend_Line;
class Blend_RstRstFunction;
class Blend_AppFunction;
class Blend_Point;

class BRepBlend_AppFuncRstRst : public BRepBlend_AppFuncRoot
{

public:
  Standard_EXPORT BRepBlend_AppFuncRstRst(occ::handle<BRepBlend_Line>& Line,
                                          Blend_RstRstFunction&        Func,
                                          const double                 Tol3d,
                                          const double                 Tol2d);

  Standard_EXPORT void Point(const Blend_AppFunction& Func,
                             const double             Param,
                             const math_Vector&       Sol,
                             Blend_Point&             Pnt) const override;

  Standard_EXPORT void Vec(math_Vector& Sol, const Blend_Point& Pnt) const override;

  DEFINE_STANDARD_RTTIEXT(BRepBlend_AppFuncRstRst, BRepBlend_AppFuncRoot)
};
