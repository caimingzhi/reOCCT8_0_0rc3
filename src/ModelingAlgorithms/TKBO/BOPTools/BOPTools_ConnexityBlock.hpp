#pragma once


#include <NCollection_BaseAllocator.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>

//=================================================================================================

class BOPTools_ConnexityBlock
{
public:
  BOPTools_ConnexityBlock()
      : myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()),
        myRegular(true),
        myShapes(myAllocator),
        myLoops(myAllocator) {};
  //
  BOPTools_ConnexityBlock(const occ::handle<NCollection_BaseAllocator>& theAllocator)
      : myAllocator(theAllocator),
        myRegular(true),
        myShapes(myAllocator),
        myLoops(myAllocator) {};

  //
  const NCollection_List<TopoDS_Shape>& Shapes() const { return myShapes; };

  //
  NCollection_List<TopoDS_Shape>& ChangeShapes() { return myShapes; };

  //
  void SetRegular(const bool theFlag) { myRegular = theFlag; }

  //
  bool IsRegular() const { return myRegular; }

  //
  const NCollection_List<TopoDS_Shape>& Loops() const { return myLoops; };

  //
  NCollection_List<TopoDS_Shape>& ChangeLoops() { return myLoops; };

  //
protected:
  occ::handle<NCollection_BaseAllocator> myAllocator;
  bool                                   myRegular;
  NCollection_List<TopoDS_Shape>         myShapes;
  NCollection_List<TopoDS_Shape>         myLoops;
};

