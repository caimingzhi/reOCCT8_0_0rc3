#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <BRepTools_ReShape.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Standard_Integer.hpp>
#include <ShapeExtend_Status.hpp>
class TopoDS_Shape;

#ifdef Status
  #undef Status
#endif

class ShapeBuild_ReShape : public BRepTools_ReShape
{

public:
  Standard_EXPORT ShapeBuild_ReShape();

  Standard_EXPORT virtual TopoDS_Shape Apply(const TopoDS_Shape&    shape,
                                             const TopAbs_ShapeEnum until,
                                             const int              buildmode);

  Standard_EXPORT TopoDS_Shape Apply(const TopoDS_Shape&    shape,
                                     const TopAbs_ShapeEnum until = TopAbs_SHAPE) override;

  Standard_EXPORT int Status(const TopoDS_Shape& shape,
                             TopoDS_Shape&       newsh,
                             const bool          last = false) override;

  Standard_EXPORT virtual bool Status(const ShapeExtend_Status status) const;

  DEFINE_STANDARD_RTTIEXT(ShapeBuild_ReShape, BRepTools_ReShape)
};
