#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Handle.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_List.hpp>
class BOPDS_PaveBlock;

class BOPDS_CommonBlock : public Standard_Transient
{

public:
  Standard_EXPORT BOPDS_CommonBlock();

  Standard_EXPORT BOPDS_CommonBlock(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  Standard_EXPORT void AddPaveBlock(const occ::handle<BOPDS_PaveBlock>& aPB);

  Standard_EXPORT void SetPaveBlocks(const NCollection_List<occ::handle<BOPDS_PaveBlock>>& aLPB);

  Standard_EXPORT void AddFace(const int aF);

  Standard_EXPORT void SetFaces(const NCollection_List<int>& aLF);

  Standard_EXPORT void AppendFaces(NCollection_List<int>& aLF);

  Standard_EXPORT const NCollection_List<occ::handle<BOPDS_PaveBlock>>& PaveBlocks() const;

  Standard_EXPORT const NCollection_List<int>& Faces() const;

  Standard_EXPORT const occ::handle<BOPDS_PaveBlock>& PaveBlock1() const;

  Standard_EXPORT occ::handle<BOPDS_PaveBlock>& PaveBlockOnEdge(const int theIndex);

  Standard_EXPORT bool IsPaveBlockOnFace(const int theIndex) const;

  Standard_EXPORT bool IsPaveBlockOnEdge(const int theIndex) const;

  Standard_EXPORT bool Contains(const occ::handle<BOPDS_PaveBlock>& thePB) const;

  Standard_EXPORT bool Contains(const int theF) const;

  Standard_EXPORT void SetEdge(const int theEdge);

  Standard_EXPORT int Edge() const;

  Standard_EXPORT void Dump() const;

  Standard_EXPORT void SetRealPaveBlock(const occ::handle<BOPDS_PaveBlock>& thePB);

  void SetTolerance(const double theTol) { myTolerance = theTol; }

  double Tolerance() const { return myTolerance; }

  DEFINE_STANDARD_RTTIEXT(BOPDS_CommonBlock, Standard_Transient)

protected:
  NCollection_List<occ::handle<BOPDS_PaveBlock>> myPaveBlocks;
  NCollection_List<int>                          myFaces;
  double                                         myTolerance;
};
