#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopAbs_ShapeEnum.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
class TopoDS_Shape;

//! Describes the ancestors tool needed by
//! the class DSFiller from TopOpeInter.
//!
//! This class has been created because it is not possible
//! to instantiate the argument TheAncestorsTool (of
//! DSFiller from TopOpeInter) with a package (TopExp)
//! giving services as package methods.
class TopOpeBRepTool_AncestorsTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! same as package method TopExp::MapShapeListOfShapes()
  Standard_EXPORT static void MakeAncestors(
    const TopoDS_Shape&                                  S,
    const TopAbs_ShapeEnum                               TS,
    const TopAbs_ShapeEnum                               TA,
    NCollection_IndexedDataMap<TopoDS_Shape,
                               NCollection_List<TopoDS_Shape>,
                               TopTools_ShapeMapHasher>& M);
};

