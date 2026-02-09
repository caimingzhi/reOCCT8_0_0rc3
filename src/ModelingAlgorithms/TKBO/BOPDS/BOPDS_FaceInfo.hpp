#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_IndexedMap.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>

class BOPDS_FaceInfo
{
public:
  DEFINE_STANDARD_ALLOC

  BOPDS_FaceInfo();

  virtual ~BOPDS_FaceInfo();

  BOPDS_FaceInfo(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  void Clear();

  void SetIndex(const int theI);

  int Index() const;

  const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& PaveBlocksIn() const;

  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocksIn();

  const NCollection_Map<int>& VerticesIn() const;

  NCollection_Map<int>& ChangeVerticesIn();

  const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& PaveBlocksOn() const;

  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocksOn();

  const NCollection_Map<int>& VerticesOn() const;

  NCollection_Map<int>& ChangeVerticesOn();

  const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& PaveBlocksSc() const;

  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocksSc();

  const NCollection_Map<int>& VerticesSc() const;

  NCollection_Map<int>& ChangeVerticesSc();

protected:
  occ::handle<NCollection_BaseAllocator>               myAllocator;
  int                                                  myIndex;
  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>> myPaveBlocksIn;
  NCollection_Map<int>                                 myVerticesIn;
  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>> myPaveBlocksOn;
  NCollection_Map<int>                                 myVerticesOn;
  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>> myPaveBlocksSc;
  NCollection_Map<int>                                 myVerticesSc;
};

inline BOPDS_FaceInfo::BOPDS_FaceInfo()
    : myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()),
      myIndex(-1),
      myPaveBlocksIn(100, myAllocator),
      myVerticesIn(100, myAllocator),
      myPaveBlocksOn(100, myAllocator),
      myVerticesOn(100, myAllocator),
      myPaveBlocksSc(100, myAllocator),
      myVerticesSc(100, myAllocator)
{
}

inline BOPDS_FaceInfo::BOPDS_FaceInfo(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myAllocator(theAllocator),
      myIndex(-1),
      myPaveBlocksIn(100, myAllocator),
      myVerticesIn(100, myAllocator),
      myPaveBlocksOn(100, myAllocator),
      myVerticesOn(100, myAllocator),
      myPaveBlocksSc(100, myAllocator),
      myVerticesSc(100, myAllocator)
{
}

inline BOPDS_FaceInfo::~BOPDS_FaceInfo()
{
  Clear();
}

inline void BOPDS_FaceInfo::Clear()
{
  myPaveBlocksIn.Clear();
  myVerticesIn.Clear();
  myPaveBlocksOn.Clear();
  myVerticesOn.Clear();
}

inline void BOPDS_FaceInfo::SetIndex(const int theI)
{
  myIndex = theI;
}

inline int BOPDS_FaceInfo::Index() const
{
  return myIndex;
}

inline const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::PaveBlocksIn()
  const
{
  return myPaveBlocksIn;
}

inline NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::ChangePaveBlocksIn()
{
  return myPaveBlocksIn;
}

inline const NCollection_Map<int>& BOPDS_FaceInfo::VerticesIn() const
{
  return myVerticesIn;
}

inline NCollection_Map<int>& BOPDS_FaceInfo::ChangeVerticesIn()
{
  return myVerticesIn;
}

inline const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::PaveBlocksOn()
  const
{
  return myPaveBlocksOn;
}

inline NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::ChangePaveBlocksOn()
{
  return myPaveBlocksOn;
}

inline const NCollection_Map<int>& BOPDS_FaceInfo::VerticesOn() const
{
  return myVerticesOn;
}

inline NCollection_Map<int>& BOPDS_FaceInfo::ChangeVerticesOn()
{
  return myVerticesOn;
}

inline const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::PaveBlocksSc()
  const
{
  return myPaveBlocksSc;
}

inline NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::ChangePaveBlocksSc()
{
  return myPaveBlocksSc;
}

inline const NCollection_Map<int>& BOPDS_FaceInfo::VerticesSc() const
{
  return myVerticesSc;
}

inline NCollection_Map<int>& BOPDS_FaceInfo::ChangeVerticesSc()
{
  return myVerticesSc;
}
