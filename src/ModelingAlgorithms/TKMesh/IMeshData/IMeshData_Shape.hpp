#pragma once

#include <TopoDS_Shape.hpp>

class IMeshData_Shape : public Standard_Transient
{
public:
  ~IMeshData_Shape() override = default;

  void SetShape(const TopoDS_Shape& theShape) { myShape = theShape; }

  const TopoDS_Shape& GetShape() const { return myShape; }

  DEFINE_STANDARD_RTTIEXT(IMeshData_Shape, Standard_Transient)

protected:
  IMeshData_Shape() {}

  IMeshData_Shape(const TopoDS_Shape& theShape)
      : myShape(theShape)
  {
  }

private:
  TopoDS_Shape myShape;
};
