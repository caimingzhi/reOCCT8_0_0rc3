#pragma once

#include <IMeshData_Shape.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

class IMeshData_TessellatedShape : public IMeshData_Shape
{
public:
  ~IMeshData_TessellatedShape() override = default;

  double GetDeflection() const { return myDeflection; }

  void SetDeflection(const double theValue) { myDeflection = theValue; }

  DEFINE_STANDARD_RTTIEXT(IMeshData_TessellatedShape, IMeshData_Shape)

protected:
  IMeshData_TessellatedShape()
      : myDeflection(RealLast())
  {
  }

  IMeshData_TessellatedShape(const TopoDS_Shape& theShape)
      : IMeshData_Shape(theShape),
        myDeflection(RealLast())
  {
  }

private:
  double myDeflection;
};
