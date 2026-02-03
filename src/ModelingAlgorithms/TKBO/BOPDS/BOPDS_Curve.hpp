// Created by: Peter KURNEV
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

#ifndef _BOPDS_Curve_HeaderFile
#define _BOPDS_Curve_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Bnd_Box.hpp>
#include <IntTools_Curve.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
class IntTools_Curve;
class Bnd_Box;
class BOPDS_PaveBlock;

//! The class BOPDS_Curve is to store
//! the information about intersection curve
class BOPDS_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  BOPDS_Curve();

  virtual ~BOPDS_Curve();

  //! Constructor
  //! @param theAllocator the allocator to manage the memory
  BOPDS_Curve(const occ::handle<NCollection_BaseAllocator>& theAllocator);

  //! Modifier
  //! Sets the curve <theC>
  void SetCurve(const IntTools_Curve& theC);

  //! Selector
  //! Returns the curve
  const IntTools_Curve& Curve() const;

  //! Modifier
  //! Sets the bounding box <theBox> of the curve
  void SetBox(const Bnd_Box& theBox);

  //! Selector
  //! Returns the bounding box of the curve
  const Bnd_Box& Box() const;

  //! Selector/Modifier
  //! Returns the bounding box of the curve
  Bnd_Box& ChangeBox();

  void SetPaveBlocks(const NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB);

  //! Selector
  //! Returns the list of pave blocks
  //! of the curve
  const NCollection_List<occ::handle<BOPDS_PaveBlock>>& PaveBlocks() const;

  //! Selector/Modifier
  //! Returns the list of pave blocks
  //! of the curve
  NCollection_List<occ::handle<BOPDS_PaveBlock>>& ChangePaveBlocks();

  //! Creates initial pave block
  //! of the curve
  void InitPaveBlock1();

  //! Selector/Modifier
  //! Returns initial pave block
  //! of the curve
  occ::handle<BOPDS_PaveBlock>& ChangePaveBlock1();

  //! Selector
  //! Returns list of indices of technologic vertices
  //! of the curve
  const NCollection_List<int>& TechnoVertices() const;

  //! Selector/Modifier
  //! Returns list of indices of technologic vertices
  //! of the curve
  NCollection_List<int>& ChangeTechnoVertices();

  //! Query
  //! Returns true if at least one pave block of the curve
  //! has edge
  bool HasEdge() const;

  //! Sets the tolerance for the curve.
  void SetTolerance(const double theTol) { myTolerance = theTol; }

  //! Returns the tolerance of the curve
  double Tolerance() const { return myTolerance; }

  //! Returns the tangential tolerance of the curve
  double TangentialTolerance() const { return myCurve.TangentialTolerance(); }

protected:
  occ::handle<NCollection_BaseAllocator>         myAllocator;
  IntTools_Curve                                 myCurve;
  NCollection_List<occ::handle<BOPDS_PaveBlock>> myPaveBlocks;
  NCollection_List<int>                          myTechnoVertices;
  Bnd_Box                                        myBox;
  double                                         myTolerance;
};
// Created by: Peter KURNEV
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

#include <BOPDS_PaveBlock.hpp>

//=================================================================================================

inline BOPDS_Curve::BOPDS_Curve()
    : myAllocator(NCollection_BaseAllocator::CommonBaseAllocator()),
      myPaveBlocks(myAllocator),
      myTechnoVertices(myAllocator),
      myTolerance(0.)
{
}

//=================================================================================================

inline BOPDS_Curve::BOPDS_Curve(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : myAllocator(theAllocator),
      myPaveBlocks(myAllocator),
      myTechnoVertices(myAllocator),
      myTolerance(0.)
{
}

//=================================================================================================

inline BOPDS_Curve::~BOPDS_Curve() = default;

//=================================================================================================

inline void BOPDS_Curve::SetCurve(const IntTools_Curve& theCurve)
{
  myCurve = theCurve;
}

//=================================================================================================

inline const IntTools_Curve& BOPDS_Curve::Curve() const
{
  return myCurve;
}

//=================================================================================================

inline void BOPDS_Curve::SetPaveBlocks(const NCollection_List<occ::handle<BOPDS_PaveBlock>>& theLPB)
{
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aIt;
  //
  myPaveBlocks.Clear();
  aIt.Initialize(theLPB);
  for (; aIt.More(); aIt.Next())
  {
    myPaveBlocks.Append(aIt.Value());
  }
}

//=================================================================================================

inline const NCollection_List<occ::handle<BOPDS_PaveBlock>>& BOPDS_Curve::PaveBlocks() const
{
  return myPaveBlocks;
}

//=================================================================================================

inline NCollection_List<occ::handle<BOPDS_PaveBlock>>& BOPDS_Curve::ChangePaveBlocks()
{
  return myPaveBlocks;
}

//=================================================================================================

inline void BOPDS_Curve::InitPaveBlock1()
{
  if (!myPaveBlocks.Extent())
  {
    occ::handle<BOPDS_PaveBlock> aPB = new BOPDS_PaveBlock;
    myPaveBlocks.Append(aPB);
  }
}

//=================================================================================================

inline occ::handle<BOPDS_PaveBlock>& BOPDS_Curve::ChangePaveBlock1()
{
  occ::handle<BOPDS_PaveBlock>* pPB = (occ::handle<BOPDS_PaveBlock>*)&myPaveBlocks.First();
  return *pPB;
}

//=================================================================================================

inline const NCollection_List<int>& BOPDS_Curve::TechnoVertices() const
{
  return myTechnoVertices;
}

//=================================================================================================

inline NCollection_List<int>& BOPDS_Curve::ChangeTechnoVertices()
{
  return myTechnoVertices;
}

//=================================================================================================

inline void BOPDS_Curve::SetBox(const Bnd_Box& theBox)
{
  myBox = theBox;
}

//=================================================================================================

inline const Bnd_Box& BOPDS_Curve::Box() const
{
  return myBox;
}

//=================================================================================================

inline Bnd_Box& BOPDS_Curve::ChangeBox()
{
  return myBox;
}

//=================================================================================================

inline bool BOPDS_Curve::HasEdge() const
{
  bool                                                     bFlag;
  NCollection_List<occ::handle<BOPDS_PaveBlock>>::Iterator aItPB;
  //
  bFlag = false;
  aItPB.Initialize(myPaveBlocks);
  for (; aItPB.More(); aItPB.Next())
  {
    const occ::handle<BOPDS_PaveBlock>& aPB = aItPB.Value();
    bFlag                                   = aPB->HasEdge();
    if (bFlag)
    {
      break;
    }
  }
  return bFlag;
}


#endif // _BOPDS_Curve_HeaderFile
