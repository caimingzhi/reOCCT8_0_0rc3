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

//! Root class for algorithms that has shape as result.
//!
//! The class provides the History mechanism, which allows
//! tracking the modification of the input shapes during
//! the operation. It uses the *BRepTools_History* tool
//! as a storer for history objects.
class BOPAlgo_BuilderShape : public BOPAlgo_Algo
{
public:
  DEFINE_STANDARD_ALLOC

public: //! @name Getting the result
  //! Returns the result of algorithm
  const TopoDS_Shape& Shape() const { return myShape; }

public: //! @name History methods
  //! Returns the list of shapes Modified from the shape theS.
  const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& theS)
  {
    if (myFillHistory && myHistory)
      return myHistory->Modified(theS);
    myHistShapes.Clear();
    return myHistShapes;
  }

  //! Returns the list of shapes Generated from the shape theS.
  const NCollection_List<TopoDS_Shape>& Generated(const TopoDS_Shape& theS)
  {
    if (myFillHistory && myHistory)
      return myHistory->Generated(theS);
    myHistShapes.Clear();
    return myHistShapes;
  }

  //! Returns true if the shape theS has been deleted.
  //! In this case the shape will have no Modified elements,
  //! but can have Generated elements.
  bool IsDeleted(const TopoDS_Shape& theS)
  {
    return (myFillHistory && myHistory ? myHistory->IsRemoved(theS) : false);
  }

  //! Returns true if any of the input shapes has been modified during operation.
  bool HasModified() const
  {
    return (myFillHistory && myHistory ? myHistory->HasModified() : false);
  }

  //! Returns true if any of the input shapes has generated shapes during operation.
  bool HasGenerated() const
  {
    return (myFillHistory && myHistory ? myHistory->HasGenerated() : false);
  }

  //! Returns true if any of the input shapes has been deleted during operation.
  bool HasDeleted() const { return (myFillHistory && myHistory ? myHistory->HasRemoved() : false); }

  //! History Tool
  occ::handle<BRepTools_History> History()
  {
    if (myFillHistory)
    {
      if (myHistory.IsNull())
        // It seems the algorithm has exited with error before filling
        // the history. Initialize the History tool to return the empty
        // History instead of NULL.
        myHistory = new BRepTools_History();

      return myHistory;
    }

    // If the History has not been requested to be filled, return the NULL
    // explicitly as the History may be partially filled for the algorithm's
    // internal needs.
    return nullptr;
  }

public: //! @name Enabling/Disabling the history collection.
  //! Allows disabling the history collection
  void SetToFillHistory(const bool theHistFlag) { myFillHistory = theHistFlag; }

  //! Returns flag of history availability
  bool HasHistory() const { return myFillHistory; }

protected: //! @name Constructors
  //! Empty constructor
  BOPAlgo_BuilderShape()
      : myFillHistory(true)
  {
  }

  //! Constructor with allocator
  BOPAlgo_BuilderShape(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : BOPAlgo_Algo(theAllocator),
        myFillHistory(true)
  {
  }

protected: //! @name Clearing
  //! Clears the content of the algorithm.
  void Clear() override
  {
    BOPAlgo_Algo::Clear();
    myHistory.Nullify();
    myMapShape.Clear();
  }

protected:              //! @name Fields
  TopoDS_Shape myShape; //!< Result of the operation

  NCollection_List<TopoDS_Shape> myHistShapes; //!< Storer for the history shapes
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>
    myMapShape; //!< cached map of all arguments shapes

  bool                           myFillHistory; //!< Controls the history filling
  occ::handle<BRepTools_History> myHistory;     //!< History tool
};

