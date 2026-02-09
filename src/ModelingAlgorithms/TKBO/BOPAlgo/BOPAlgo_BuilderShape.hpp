#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPAlgo_Algo.hpp>
#include <BRepTools_History.hpp>

#include <NCollection_BaseAllocator.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
class TopoDS_Shape;

class BOPAlgo_BuilderShape : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

public:
  const TopoDS_Shape& Shape() const { return myShape; }

public:
  const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& theS)
  {
    if (myFillHistory && myHistory)
      return myHistory->Modified(theS);
    myHistShapes.Clear();
    return myHistShapes;
  }

  const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& theS)
  {
    if (myFillHistory && myHistory)
      return myHistory->Generated(theS);
    myHistShapes.Clear();
    return myHistShapes;
  }

  bool IsDeleted(const TopoDS_Shape& theS)
  {
    return (myFillHistory && myHistory ? myHistory->IsRemoved(theS) : false);
  }

  bool HasModified() const
  {
    return (myFillHistory && myHistory ? myHistory->HasModified() : false);
  }

  bool HasGenerated() const
  {
    return (myFillHistory && myHistory ? myHistory->HasGenerated() : false);
  }

  bool HasDeleted() const { return (myFillHistory && myHistory ? myHistory->HasRemoved() : false); }

  occ::handle<BRepTools_History> History()
  {
    if (myFillHistory)
    {
      if (myHistory.IsNull())

        myHistory = new BRepTools_History();

      return myHistory;
    }

    return nullptr;
  }

public:
  void SetToFillHistory(const bool theHistFlag) { myFillHistory = theHistFlag; }

  bool HasHistory() const { return myFillHistory; }

protected:
  BOPAlgo_BuilderShape()
      : myFillHistory(true)
  {
  }

  BOPAlgo_BuilderShape(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPAlgo_Algo(theAllocator),
        myFillHistory(true)
  {
  }

protected:
  void Clear() override
  {
    BOPAlgo_Algo::Clear();
    myHistory.Nullify();
    myMapShape.Clear();
  }

protected:
  TopoDS_Shape myShape;

  NCollection_List<TopoDS_Shape>                         myHistShapes;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMapShape;

  bool                           myFillHistory;
  occ::handle<BRepTools_History> myHistory;
};
