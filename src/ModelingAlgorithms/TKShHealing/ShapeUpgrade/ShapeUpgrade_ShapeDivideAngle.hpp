#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <ShapeUpgrade_ShapeDivide.hpp>
class TopoDS_Shape;

class ShapeUpgrade_ShapeDivideAngle : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeUpgrade_ShapeDivideAngle(const double MaxAngle);

  Standard_EXPORT ShapeUpgrade_ShapeDivideAngle(const double MaxAngle, const TopoDS_Shape& S);

  Standard_EXPORT void InitTool(const double MaxAngle);

  Standard_EXPORT void SetMaxAngle(const double MaxAngle);

  Standard_EXPORT double MaxAngle() const;
};
