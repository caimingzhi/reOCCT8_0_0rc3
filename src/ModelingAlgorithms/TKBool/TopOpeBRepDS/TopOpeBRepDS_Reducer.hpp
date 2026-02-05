#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_ListOfShapeOn1State.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopOpeBRepDS_HDataStructure;

//! reduce interferences of a data structure (HDS)
//! used in topological operations.
class TopOpeBRepDS_Reducer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Reducer(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT void ProcessFaceInterferences(
    const NCollection_DataMap<TopoDS_Shape,
                              TopOpeBRepDS_ListOfShapeOn1State,
                              TopTools_ShapeMapHasher>& M);

  Standard_EXPORT void ProcessEdgeInterferences();

private:
  occ::handle<TopOpeBRepDS_HDataStructure> myHDS;
};
