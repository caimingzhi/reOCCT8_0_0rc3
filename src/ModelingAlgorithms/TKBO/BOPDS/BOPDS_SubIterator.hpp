#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BOPDS_PDS.hpp>
#include <NCollection_Vector.hpp>
#include <BOPDS_Pair.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>

//! The class BOPDS_SubIterator is used to compute intersections between
//! bounding boxes of two sub-sets of BRep sub-shapes of arguments
//! of an operation (see the class BOPDS_DS).
//! The class provides interface to iterate the pairs of intersected sub-shapes.

class BOPDS_SubIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT BOPDS_SubIterator();
  Standard_EXPORT virtual ~BOPDS_SubIterator();

  //! Constructor
  //! theAllocator - the allocator to manage the memory
  Standard_EXPORT BOPDS_SubIterator(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  //! Sets the data structure <pDS> to process.
  //! It is used to access the shapes and their bounding boxes.
  void SetDS(const BOPDS_PDS& pDS) { myDS = pDS; }

  //! Returns the data structure
  const BOPDS_DS& DS() const { return *myDS; }

  //! Sets the first set of indices <theLI> to process
  void SetSubSet1(const NCollection_List<int>& theLI)
  {
    mySubSet1 = (NCollection_List<int>*)&theLI;
  }

  //! Returns the first set of indices to process
  const NCollection_List<int>& SubSet1() const { return *mySubSet1; }

  //! Sets the second set of indices <theLI> to process
  void SetSubSet2(const NCollection_List<int>& theLI)
  {
    mySubSet2 = (NCollection_List<int>*)&theLI;
  }

  //! Returns the second set of indices to process
  const NCollection_List<int>& SubSet2() const { return *mySubSet2; }

  //! Initializes the iterator
  Standard_EXPORT void Initialize();

  //! Returns true if there are more pairs of intersected shapes
  bool More() const { return myIterator.More(); }

  //! Moves iterations ahead
  void Next() { myIterator.Next(); }

  //! Returns indices (DS) of intersected shapes
  //! theIndex1 - the index of the first shape
  //! theIndex2 - the index of the second shape
  Standard_EXPORT void Value(int& theIndex1, int& theIndex2) const;

  //! Perform the intersection algorithm and prepare
  //! the results to be used
  Standard_EXPORT virtual void Prepare();

  //! Returns the number of interfering pairs
  int ExpectedLength() const { return myList.Length(); }

protected:
  //! Performs intersection of bounding boxes
  Standard_EXPORT virtual void Intersect();

  occ::handle<NCollection_BaseAllocator>   myAllocator;
  BOPDS_PDS                                myDS;
  NCollection_Vector<BOPDS_Pair>           myList;
  NCollection_Vector<BOPDS_Pair>::Iterator myIterator;
  NCollection_List<int>*                   mySubSet1;
  NCollection_List<int>*                   mySubSet2;
};

