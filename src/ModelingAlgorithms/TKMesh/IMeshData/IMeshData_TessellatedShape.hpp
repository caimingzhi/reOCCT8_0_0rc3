#pragma once

#include <IMeshData_Shape.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

//! Interface class representing shaped model with deflection.
class IMeshData_TessellatedShape : public IMeshData_Shape
{
public:
  //! Destructor.
  ~IMeshData_TessellatedShape() override = default;

  //! Gets deflection value for the discrete model.
  double GetDeflection() const { return myDeflection; }

  //! Sets deflection value for the discrete model.
  void SetDeflection(const double theValue) { myDeflection = theValue; }

  DEFINE_STANDARD_RTTIEXT(IMeshData_TessellatedShape, IMeshData_Shape)

protected:
  //! Constructor.
  IMeshData_TessellatedShape()
      : myDeflection(RealLast())
  {
  }

  //! Constructor.
  IMeshData_TessellatedShape(const TopoDS_Shape& theShape)
      : IMeshData_Shape(theShape),
        myDeflection(RealLast())
  {
  }

private:
  double myDeflection;
};
