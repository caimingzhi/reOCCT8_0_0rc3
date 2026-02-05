#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopAbs_ShapeEnum.hpp>
class TopoDS_Shape;

//! Modifies tolerances of sub-shapes (vertices, edges, faces)
class ShapeFix_ShapeTolerance
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_ShapeTolerance();

  //! Limits tolerances in a shape as follows :
  //! tmin = tmax -> as SetTolerance (forces)
  //! tmin = 0   -> maximum tolerance will be <tmax>
  //! tmax = 0 or not given (more generally, tmax < tmin) ->
  //! <tmax> ignored, minimum will be <tmin>
  //! else, maximum will be <max> and minimum will be <min>
  //! styp = VERTEX : only vertices are set
  //! styp = EDGE   : only edges are set
  //! styp = FACE   : only faces are set
  //! styp = WIRE   : to have edges and their vertices set
  //! styp = other value : all (vertices,edges,faces) are set
  //! Returns True if at least one tolerance of the sub-shape has
  //! been modified
  Standard_EXPORT bool LimitTolerance(const TopoDS_Shape&    shape,
                                      const double           tmin,
                                      const double           tmax = 0.0,
                                      const TopAbs_ShapeEnum styp = TopAbs_SHAPE) const;

  //! Sets (enforces) tolerances in a shape to the given value
  //! styp = VERTEX : only vertices are set
  //! styp = EDGE   : only edges are set
  //! styp = FACE   : only faces are set
  //! styp = WIRE   : to have edges and their vertices set
  //! styp = other value : all (vertices,edges,faces) are set
  Standard_EXPORT void SetTolerance(const TopoDS_Shape&    shape,
                                    const double           preci,
                                    const TopAbs_ShapeEnum styp = TopAbs_SHAPE) const;
};
