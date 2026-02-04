#pragma once


#include <TopoDS_Shape.hpp>

//! Interface class representing model with associated TopoDS_Shape.
//! Intended for inheritance by structures and algorithms keeping
//! reference TopoDS_Shape.
class IMeshData_Shape : public Standard_Transient
{
public:
  //! Destructor.
  ~IMeshData_Shape() override = default;

  //! Assigns shape to discrete shape.
  void SetShape(const TopoDS_Shape& theShape) { myShape = theShape; }

  //! Returns shape assigned to discrete shape.
  const TopoDS_Shape& GetShape() const { return myShape; }

  DEFINE_STANDARD_RTTIEXT(IMeshData_Shape, Standard_Transient)

protected:
  //! Constructor.
  IMeshData_Shape() {}

  //! Constructor.
  IMeshData_Shape(const TopoDS_Shape& theShape)
      : myShape(theShape)
  {
  }

private:
  TopoDS_Shape myShape;
};

