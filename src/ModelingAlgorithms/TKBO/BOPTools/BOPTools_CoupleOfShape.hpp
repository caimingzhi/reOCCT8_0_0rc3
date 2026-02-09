#pragma once

#include <TopoDS_Shape.hpp>

class BOPTools_CoupleOfShape
{
public:
  BOPTools_CoupleOfShape() = default;

  ~BOPTools_CoupleOfShape() = default;

  void SetShape1(const TopoDS_Shape& theShape) { myShape1 = theShape; }

  const TopoDS_Shape& Shape1() const { return myShape1; }

  void SetShape2(const TopoDS_Shape& theShape) { myShape2 = theShape; }

  const TopoDS_Shape& Shape2() const { return myShape2; }

protected:
  TopoDS_Shape myShape1;
  TopoDS_Shape myShape2;
};
