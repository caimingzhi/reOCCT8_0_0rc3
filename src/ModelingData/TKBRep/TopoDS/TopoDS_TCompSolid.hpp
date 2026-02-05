#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_TShape.hpp>

//! A set of solids connected by their faces.
class TopoDS_TCompSolid : public TopoDS_TShape
{
public:
  //! Creates an empty TCompSolid.
  TopoDS_TCompSolid()

    = default;

  //! returns COMPSOLID
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const override;

  //! Returns an empty TCompSolid.
  Standard_EXPORT occ::handle<TopoDS_TShape> EmptyCopy() const override;

  DEFINE_STANDARD_RTTIEXT(TopoDS_TCompSolid, TopoDS_TShape)
};
