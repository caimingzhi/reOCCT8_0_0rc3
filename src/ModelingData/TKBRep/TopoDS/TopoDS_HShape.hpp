#pragma once

#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>

class TopoDS_HShape : public Standard_Transient
{

public:
  TopoDS_HShape();

  TopoDS_HShape(const TopoDS_Shape& aShape);

  void Shape(const TopoDS_Shape& aShape);

  const TopoDS_Shape& Shape() const;

  TopoDS_Shape& ChangeShape();

  DEFINE_STANDARD_RTTIEXT(TopoDS_HShape, Standard_Transient)

private:
  TopoDS_Shape myShape;
};

inline TopoDS_HShape::TopoDS_HShape() = default;

inline TopoDS_HShape::TopoDS_HShape(const TopoDS_Shape& aShape)
    : myShape(aShape)
{
}

inline void TopoDS_HShape::Shape(const TopoDS_Shape& aShape)
{
  myShape = aShape;
}

inline const TopoDS_Shape& TopoDS_HShape::Shape() const
{
  return myShape;
}

inline TopoDS_Shape& TopoDS_HShape::ChangeShape()
{
  return myShape;
}
