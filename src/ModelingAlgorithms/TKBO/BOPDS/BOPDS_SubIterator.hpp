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

class BOPDS_SubIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPDS_SubIterator();
  Standard_EXPORT virtual ~BOPDS_SubIterator();

  Standard_EXPORT BOPDS_SubIterator(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  void SetDS(const BOPDS_PDS& pDS) { myDS = pDS; }

  const BOPDS_DS& DS() const { return *myDS; }

  void SetSubSet1(const NCollection_List<int>& theLI)
  {
    mySubSet1 = (NCollection_List<int>*)&theLI;
  }

  const NCollection_List<int>& SubSet1() const { return *mySubSet1; }

  void SetSubSet2(const NCollection_List<int>& theLI)
  {
    mySubSet2 = (NCollection_List<int>*)&theLI;
  }

  const NCollection_List<int>& SubSet2() const { return *mySubSet2; }

  Standard_EXPORT void Initialize();

  bool More() const { return myIterator.More(); }

  void Next() { myIterator.Next(); }

  Standard_EXPORT void Value(int& theIndex1, int& theIndex2) const;

  Standard_EXPORT virtual void Prepare();

  int ExpectedLength() const { return myList.Length(); }

protected:
  Standard_EXPORT virtual void Intersect();

  occ::handle<NCollection_BaseAllocator>   myAllocator;
  BOPDS_PDS                                myDS;
  NCollection_Vector<BOPDS_Pair>           myList;
  NCollection_Vector<BOPDS_Pair>::Iterator myIterator;
  NCollection_List<int>*                   mySubSet1;
  NCollection_List<int>*                   mySubSet2;
};
