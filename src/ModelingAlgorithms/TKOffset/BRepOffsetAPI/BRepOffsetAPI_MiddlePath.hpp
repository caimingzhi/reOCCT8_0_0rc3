#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>

class BRepOffsetAPI_MiddlePath : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffsetAPI_MiddlePath(const TopoDS_Shape& aShape,
                                           const TopoDS_Shape& StartShape,
                                           const TopoDS_Shape& EndShape);

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

private:
  TopoDS_Shape                                             myInitialShape;
  TopoDS_Wire                                              myStartWire;
  TopoDS_Wire                                              myEndWire;
  bool                                                     myClosedSection;
  bool                                                     myClosedRing;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>   myStartWireEdges;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>   myEndWireEdges;
  NCollection_Sequence<NCollection_Sequence<TopoDS_Shape>> myPaths;
};
