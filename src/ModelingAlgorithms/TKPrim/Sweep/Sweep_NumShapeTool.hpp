#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Sweep_NumShape.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>

//! This class provides the indexation and type analysis
//! services required by the NumShape Directing Shapes of
//! Swept Primitives.
class Sweep_NumShapeTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Create a new NumShapeTool with <aShape>. The Tool
  //! must prepare an indexation for all the subshapes
  //! of this shape.
  Standard_EXPORT Sweep_NumShapeTool(const Sweep_NumShape& aShape);

  //! Returns the number of subshapes in the shape.
  Standard_EXPORT int NbShapes() const;

  //! Returns the index of <aShape>.
  Standard_EXPORT int Index(const Sweep_NumShape& aShape) const;

  //! Returns the Shape at index anIndex
  Standard_EXPORT Sweep_NumShape Shape(const int anIndex) const;

  //! Returns the type of <aShape>.
  Standard_EXPORT TopAbs_ShapeEnum Type(const Sweep_NumShape& aShape) const;

  //! Returns the orientation of <aShape>.
  Standard_EXPORT TopAbs_Orientation Orientation(const Sweep_NumShape& aShape) const;

  //! Returns true if there is a First Vertex in the Shape.
  Standard_EXPORT bool HasFirstVertex() const;

  //! Returns true if there is a Last Vertex in the Shape.
  Standard_EXPORT bool HasLastVertex() const;

  //! Returns the first vertex.
  Standard_EXPORT Sweep_NumShape FirstVertex() const;

  //! Returns the last vertex.
  Standard_EXPORT Sweep_NumShape LastVertex() const;

private:
  Sweep_NumShape myNumShape;
};

