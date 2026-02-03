// Created on: 1993-10-29
// Created by: Christophe MARION
// Copyright (c) 1993-1999 Matra Datavision
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

#ifndef _HLRAlgo_PolyInternalData_HeaderFile
#define _HLRAlgo_PolyInternalData_HeaderFile

#include <Standard.hpp>
#include <Standard_Integer.hpp>
#include <HLRAlgo_TriangleData.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <HLRAlgo_PolyInternalSegment.hpp>
#include <HLRAlgo_PolyInternalNode.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

//! to Update OutLines.
class HLRAlgo_PolyInternalData : public Standard_Transient
{

public:
  Standard_EXPORT HLRAlgo_PolyInternalData(const int nbNod, const int nbTri);

  Standard_EXPORT void UpdateLinks(
    NCollection_Array1<HLRAlgo_TriangleData>&                  theTData,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>&           thePISeg,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& thePINod);

  Standard_EXPORT int AddNode(HLRAlgo_PolyInternalNode::NodeData& theNod1RValues,
                              HLRAlgo_PolyInternalNode::NodeData& theNod2RValues,
                              NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& thePINod1,
                              NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& thePINod2,
                              const double                                                theCoef1,
                              const double                                                theX3,
                              const double                                                theY3,
                              const double                                                theZ3);

  Standard_EXPORT void UpdateLinks(
    const int                                                   theIp1,
    const int                                                   theIp2,
    const int                                                   theIp3,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  theTData1,
    NCollection_Array1<HLRAlgo_TriangleData>*&                  theTData2,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           thePISeg1,
    NCollection_Array1<HLRAlgo_PolyInternalSegment>*&           thePISeg2,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& thePINod1,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& thePINod2);

  Standard_EXPORT void Dump() const;

  Standard_EXPORT void IncTData(NCollection_Array1<HLRAlgo_TriangleData>*& TData1,
                                NCollection_Array1<HLRAlgo_TriangleData>*& TData2);

  Standard_EXPORT void IncPISeg(NCollection_Array1<HLRAlgo_PolyInternalSegment>*& PISeg1,
                                NCollection_Array1<HLRAlgo_PolyInternalSegment>*& PISeg2);

  Standard_EXPORT void IncPINod(
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& thePINod1,
    NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>*& thePINod2);

  void DecTData();

  void DecPISeg();

  void DecPINod();

  int NbTData() const;

  int NbPISeg() const;

  int NbPINod() const;

  bool Planar() const;

  void Planar(const bool B);

  bool IntOutL() const;

  void IntOutL(const bool B);

  NCollection_Array1<HLRAlgo_TriangleData>& TData() const;

  NCollection_Array1<HLRAlgo_PolyInternalSegment>& PISeg() const;

  NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& PINod() const;

  DEFINE_STANDARD_RTTIEXT(HLRAlgo_PolyInternalData, Standard_Transient)

private:
  int                                                                     myNbTData;
  int                                                                     myNbPISeg;
  int                                                                     myNbPINod;
  int                                                                     myMxTData;
  int                                                                     myMxPISeg;
  int                                                                     myMxPINod;
  bool                                                                    myIntOutL;
  bool                                                                    myPlanar;
  occ::handle<NCollection_HArray1<HLRAlgo_TriangleData>>                  myTData;
  occ::handle<NCollection_HArray1<HLRAlgo_PolyInternalSegment>>           myPISeg;
  occ::handle<NCollection_HArray1<occ::handle<HLRAlgo_PolyInternalNode>>> myPINod;
};
// Created on: 1993-01-11
// Created by: Christophe MARION
// Copyright (c) 1993-1999 Matra Datavision
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

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_Pnt.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Dir.hpp>
#include <HLRAlgo_TriangleData.hpp>
#include <HLRAlgo_PolyInternalSegment.hpp>
#include <HLRAlgo_PolyInternalNode.hpp>

//=================================================================================================

inline void HLRAlgo_PolyInternalData::DecTData()
{
  myNbTData--;
}

//=================================================================================================

inline void HLRAlgo_PolyInternalData::DecPISeg()
{
  myNbPISeg--;
}

//=================================================================================================

inline void HLRAlgo_PolyInternalData::DecPINod()
{
  myNbPINod--;
}

//=================================================================================================

inline int HLRAlgo_PolyInternalData::NbTData() const
{
  return myNbTData;
}

//=================================================================================================

inline int HLRAlgo_PolyInternalData::NbPISeg() const
{
  return myNbPISeg;
}

//=================================================================================================

inline int HLRAlgo_PolyInternalData::NbPINod() const
{
  return myNbPINod;
}

//=================================================================================================

inline bool HLRAlgo_PolyInternalData::Planar() const
{
  return myPlanar;
}

//=================================================================================================

inline void HLRAlgo_PolyInternalData::Planar(const bool B)
{
  myPlanar = B;
}

//=================================================================================================

inline bool HLRAlgo_PolyInternalData::IntOutL() const
{
  return myIntOutL;
}

//=================================================================================================

inline void HLRAlgo_PolyInternalData::IntOutL(const bool B)
{
  myIntOutL = B;
}

//=================================================================================================

inline NCollection_Array1<HLRAlgo_TriangleData>& HLRAlgo_PolyInternalData::TData() const
{
  return myTData->ChangeArray1();
}

//=================================================================================================

inline NCollection_Array1<occ::handle<HLRAlgo_PolyInternalNode>>& HLRAlgo_PolyInternalData::PINod()
  const
{
  return myPINod->ChangeArray1();
}

//=================================================================================================

inline NCollection_Array1<HLRAlgo_PolyInternalSegment>& HLRAlgo_PolyInternalData::PISeg() const
{
  return myPISeg->ChangeArray1();
}


#endif // _HLRAlgo_PolyInternalData_HeaderFile
