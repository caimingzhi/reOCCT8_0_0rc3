#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

//! A TCompound is an all-purpose set of Shapes.
class TopoDS_TCompound : public TopoDS_TShape
{
public:
  //! Creates an empty TCompound.
  TopoDS_TCompound() { Orientable(false); }

  //! Returns COMPOUND.
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  //! Returns an empty TCompound.
  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TCompound, TopoDS_TShape)
};

