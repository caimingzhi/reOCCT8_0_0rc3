#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
class TopoDS_Shape;

//! Provides the indexation and type analysis services
//! required by the TopoDS generating Shape of BRepSweep.
class BRepSweep_Tool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Initialize the tool with <aShape>. The IndexTool
  //! must prepare an indexation for all the subshapes
  //! of this shape.
  Standard_EXPORT BRepSweep_Tool(const TopoDS_Shape& aShape);

  //! Returns the number of subshapes in the shape.
  Standard_EXPORT int NbShapes() const;

  //! Returns the index of <aShape>.
  Standard_EXPORT int Index(const TopoDS_Shape& aShape) const;

  //! Returns the Shape at Index anIdex.
  Standard_EXPORT TopoDS_Shape Shape(const int anIndex) const;

  //! Returns the type of <aShape>.
  Standard_EXPORT TopAbs_ShapeEnum Type(const TopoDS_Shape& aShape) const;

  //! Returns the Orientation of <aShape>.
  Standard_EXPORT TopAbs_Orientation Orientation(const TopoDS_Shape& aShape) const;

  //! Set the Orientation of <aShape> with Or.
  Standard_EXPORT void SetOrientation(TopoDS_Shape& aShape, const TopAbs_Orientation Or) const;

private:
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};

