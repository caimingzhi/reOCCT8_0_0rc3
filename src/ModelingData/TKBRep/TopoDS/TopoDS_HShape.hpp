#pragma once

#include <Standard.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>

//! Class to manipulate a Shape with handle.
class TopoDS_HShape : public Standard_Transient
{

public:
  //! Constructs an empty shape object.
  TopoDS_HShape();

  //! Constructs a shape object defined by the shape aShape.
  TopoDS_HShape(const TopoDS_Shape& aShape);

  //! Loads this shape with the shape aShape.
  void Shape(const TopoDS_Shape& aShape);

  //! Returns a reference to a constant TopoDS_Shape based on this shape.
  const TopoDS_Shape& Shape() const;

  //! Exchanges the TopoDS_Shape object defining this
  //! shape for another one referencing the same underlying shape
  //! Accesses the list of shapes within the underlying
  //! shape referenced by the TopoDS_Shape object.
  //! Returns a reference to a TopoDS_Shape based on
  //! this shape. The TopoDS_Shape can be modified.
  TopoDS_Shape& ChangeShape();

  DEFINE_STANDARD_RTTIEXT(TopoDS_HShape, Standard_Transient)

private:
  TopoDS_Shape myShape;
};

inline TopoDS_HShape::TopoDS_HShape() = default;

//=================================================================================================

inline TopoDS_HShape::TopoDS_HShape(const TopoDS_Shape& aShape)
    : myShape(aShape)
{
}

//=================================================================================================

inline void TopoDS_HShape::Shape(const TopoDS_Shape& aShape)
{
  myShape = aShape;
}

//=================================================================================================

inline const TopoDS_Shape& TopoDS_HShape::Shape() const
{
  return myShape;
}

//=================================================================================================

inline TopoDS_Shape& TopoDS_HShape::ChangeShape()
{
  return myShape;
}
