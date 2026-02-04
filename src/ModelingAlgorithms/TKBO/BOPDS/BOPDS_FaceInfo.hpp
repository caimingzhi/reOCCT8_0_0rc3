#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_IndexedMap.hpp>
#include <BOPDS_PaveBlock.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>

//! The class BOPDS_FaceInfo is to store
//! handy information about state of face
class BOPDS_FaceInfo
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  BOPDS_FaceInfo();

  virtual ~BOPDS_FaceInfo();

  //! Constructor
  //! @param theAllocator the allocator to manage the memory
  BOPDS_FaceInfo(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  //! Clears the contents
  void Clear();

  //! Modifier
  //! Sets the index of the face <theI>
  void SetIndex(const int theI);

  //! Selector
  //! Returns the index of the face
  //!
  //! In
  int Index() const;

  //! Selector
  //! Returns the pave blocks of the face
  //! that have state In
  const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& PaveBlocksIn() const;

  //! Selector/Modifier
  //! Returns the pave blocks
  //! of the face
  //! that have state In
  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocksIn();

  //! Selector
  //! Returns the list of indices for vertices
  //! of the face
  //! that have state In
  const NCollection_Map<int>& VerticesIn() const;

  //! Selector/Modifier
  //! Returns the list of indices for vertices
  //! of the face
  //! that have state In
  //!
  //! On
  NCollection_Map<int>& ChangeVerticesIn();

  //! Selector
  //! Returns the pave blocks of the face
  //! that have state On
  const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& PaveBlocksOn() const;

  //! Selector/Modifier
  //! Returns the pave blocks
  //! of the face
  //! that have state On
  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocksOn();

  //! Selector
  //! Returns the list of indices for vertices
  //! of the face
  //! that have state On
  const NCollection_Map<int>& VerticesOn() const;

  //! Selector/Modifier
  //! Returns the list of indices for vertices
  //! of the face
  //! that have state On
  //!
  //! Sections
  NCollection_Map<int>& ChangeVerticesOn();

  //! Selector
  //! Returns the pave blocks of the face
  //! that are pave blocks of section edges
  const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& PaveBlocksSc() const;

  NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocksSc();

  //! Selector
  //! Returns the list of indices for section vertices
  //! of the face
  const NCollection_Map<int>& VerticesSc() const;

  //! Selector/Modifier
  //! Returns the list of indices for section vertices
  //! of the face
  //!
  //! Others
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
// Created by: Peter KURNEV
// Copyright (c) 2010-2014 OPEN CASCADE SAS
// Copyright (c) 2007-2010 CEA/DEN, EDF R&D, OPEN CASCADE
// Copyright (c) 2003-2007 OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN, CEDRAT,
//                         EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

//=================================================================================================

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

//=================================================================================================

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

//=======================================================================
// function : ~
// purpose  :
//=======================================================================
inline BOPDS_FaceInfo::~BOPDS_FaceInfo()
{
  Clear();
}

//=================================================================================================

inline void BOPDS_FaceInfo::Clear()
{
  myPaveBlocksIn.Clear();
  myVerticesIn.Clear();
  myPaveBlocksOn.Clear();
  myVerticesOn.Clear();
}

//=================================================================================================

inline void BOPDS_FaceInfo::SetIndex(const int theI)
{
  myIndex = theI;
}

//=================================================================================================

inline int BOPDS_FaceInfo::Index() const
{
  return myIndex;
}

//=================================================================================================

inline const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::PaveBlocksIn()
  const
{
  return myPaveBlocksIn;
}

//=================================================================================================

inline NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::ChangePaveBlocksIn()
{
  return myPaveBlocksIn;
}

//=================================================================================================

inline const NCollection_Map<int>& BOPDS_FaceInfo::VerticesIn() const
{
  return myVerticesIn;
}

//=================================================================================================

inline NCollection_Map<int>& BOPDS_FaceInfo::ChangeVerticesIn()
{
  return myVerticesIn;
}

// On
//=================================================================================================

inline const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::PaveBlocksOn()
  const
{
  return myPaveBlocksOn;
}

//=================================================================================================

inline NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::ChangePaveBlocksOn()
{
  return myPaveBlocksOn;
}

//=================================================================================================

inline const NCollection_Map<int>& BOPDS_FaceInfo::VerticesOn() const
{
  return myVerticesOn;
}

//=================================================================================================

inline NCollection_Map<int>& BOPDS_FaceInfo::ChangeVerticesOn()
{
  return myVerticesOn;
}

// Sc
//=================================================================================================

inline const NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::PaveBlocksSc()
  const
{
  return myPaveBlocksSc;
}

//=================================================================================================

inline NCollection_IndexedMap<occ::handle<BOPDS_PaveBlock>>& BOPDS_FaceInfo::ChangePaveBlocksSc()
{
  return myPaveBlocksSc;
}

//=================================================================================================

inline const NCollection_Map<int>& BOPDS_FaceInfo::VerticesSc() const
{
  return myVerticesSc;
}

//=================================================================================================

inline NCollection_Map<int>& BOPDS_FaceInfo::ChangeVerticesSc()
{
  return myVerticesSc;
}


