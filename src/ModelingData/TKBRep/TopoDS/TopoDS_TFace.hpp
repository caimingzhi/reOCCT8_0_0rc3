#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

//! A topological part of a surface or of the 2D
//! space. The boundary is a set of wires and
//! vertices.
class TopoDS_TFace : public TopoDS_TShape
{
public:
  //! Creates an empty TFace.
  TopoDS_TFace()

    = default;

  //! returns FACE.
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  //! Returns an empty TFace.
  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TFace, TopoDS_TShape)
};

