#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Algo.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <NCollection_IndexedMap.hpp>
class IntTools_Context;

//! The root class for algorithms to build
//! faces/solids from set of edges/faces
class BOPAlgo_BuilderArea : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

  //! Sets the context for the algorithms
  void SetContext(const occ::handle<IntTools_Context>& theContext) { myContext = theContext; }

  //! Returns the input shapes
  const NCollection_List<TopoDS_Shape>& Shapes() const { return myShapes; }

  //! Sets the shapes for building areas
  void SetShapes(const NCollection_List<TopoDS_Shape>& theLS) { myShapes = theLS; }

  //! Returns the found loops
  const NCollection_List<TopoDS_Shape>& Loops() const { return myLoops; }

  //! Returns the found areas
  const NCollection_List<TopoDS_Shape>& Areas() const { return myAreas; }

  //! Defines the preventing of addition of internal parts into result.
  //! The default value is FALSE, i.e. the internal parts are added into result.
  void SetAvoidInternalShapes(const bool theAvoidInternal)
  {
    myAvoidInternalShapes = theAvoidInternal;
  }

  //! Returns the AvoidInternalShapes flag
  bool IsAvoidInternalShapes() const { return myAvoidInternalShapes; }

protected:
  Standard_EXPORT BOPAlgo_BuilderArea();
  Standard_EXPORT ~BOPAlgo_BuilderArea() override;

  Standard_EXPORT BOPAlgo_BuilderArea(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  virtual void PerformShapesToAvoid(const Message_ProgressRange& theRange) = 0;

  virtual void PerformLoops(const Message_ProgressRange& theRange) = 0;

  virtual void PerformAreas(const Message_ProgressRange& theRange) = 0;

  virtual void PerformInternalShapes(const Message_ProgressRange& theRange) = 0;

  occ::handle<IntTools_Context>        myContext;
  NCollection_List<TopoDS_Shape>       myShapes;
  NCollection_List<TopoDS_Shape>       myLoops;
  NCollection_List<TopoDS_Shape>       myLoopsInternal;
  NCollection_List<TopoDS_Shape>       myAreas;
  NCollection_IndexedMap<TopoDS_Shape> myShapesToAvoid;
  bool                                 myAvoidInternalShapes;
};
