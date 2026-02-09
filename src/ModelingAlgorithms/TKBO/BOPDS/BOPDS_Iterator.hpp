#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <BOPDS_PDS.hpp>
#include <NCollection_Vector.hpp>
#include <BOPDS_Pair.hpp>
#include <BOPTools_BoxTree.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Precision.hpp>
#include <TopAbs_ShapeEnum.hpp>
class IntTools_Context;

class BOPDS_Iterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPDS_Iterator();
  Standard_EXPORT virtual ~BOPDS_Iterator();

  Standard_EXPORT BOPDS_Iterator(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void SetDS(const BOPDS_PDS& pDS);

  Standard_EXPORT const BOPDS_DS& DS() const;

  Standard_EXPORT void Initialize(const TopAbs_ShapeEnum theType1, const TopAbs_ShapeEnum theType2);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT void Value(int& theIndex1, int& theIndex2) const;

  Standard_EXPORT virtual void Prepare(
    const occ::handle<IntTools_Context>& theCtx        = occ::handle<IntTools_Context>(),
    const bool                           theCheckOBB   = false,
    const double                         theFuzzyValue = Precision::Confusion());

  Standard_EXPORT void IntersectExt(const NCollection_Map<int>& theIndicies);

  Standard_EXPORT int ExpectedLength() const;

  Standard_EXPORT int BlockLength() const;

  Standard_EXPORT void SetRunParallel(const bool theFlag);

  Standard_EXPORT bool RunParallel() const;

public:
  static int NbExtInterfs() { return 4; }

protected:
  Standard_EXPORT virtual void Intersect(
    const occ::handle<IntTools_Context>& theCtx        = occ::handle<IntTools_Context>(),
    const bool                           theCheckOBB   = false,
    const double                         theFuzzyValue = Precision::Confusion());

protected:
  occ::handle<NCollection_BaseAllocator> myAllocator;
  int                                    myLength;

  BOPDS_PDS                                          myDS;
  NCollection_Vector<NCollection_Vector<BOPDS_Pair>> myLists;
  NCollection_Vector<BOPDS_Pair>::Iterator           myIterator;
  bool                                               myRunParallel;
  NCollection_Vector<NCollection_Vector<BOPDS_Pair>> myExtLists;

  bool myUseExt;
};
