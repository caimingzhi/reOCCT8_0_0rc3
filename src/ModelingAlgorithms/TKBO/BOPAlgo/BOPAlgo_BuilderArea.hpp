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

class BOPAlgo_BuilderArea : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

  void SetContext(const occ::handle<IntTools_Context>& theContext) { myContext = theContext; }

  const NCollection_List<TopoDS_Shape>& Shapes() const { return myShapes; }

  void SetShapes(const NCollection_List<TopoDS_Shape>& theLS) { myShapes = theLS; }

  const NCollection_List<TopoDS_Shape>& Loops() const { return myLoops; }

  const NCollection_List<TopoDS_Shape>& Areas() const { return myAreas; }

  void SetAvoidInternalShapes(const bool theAvoidInternal)
  {
    myAvoidInternalShapes = theAvoidInternal;
  }

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
