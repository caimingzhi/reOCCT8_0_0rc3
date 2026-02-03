// Created on: 1993-11-10
// Created by: Laurent BOURESCHE
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

#ifndef _ChFiDS_StripeMap_HeaderFile
#define _ChFiDS_StripeMap_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Vertex.hpp>
#include <ChFiDS_Stripe.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Standard_Integer.hpp>
class TopoDS_Vertex;
class ChFiDS_Stripe;

//! encapsulation of IndexedDataMapOfVertexListOfStripe
class ChFiDS_StripeMap
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ChFiDS_StripeMap();

  Standard_EXPORT void Add(const TopoDS_Vertex& V, const occ::handle<ChFiDS_Stripe>& F);

  int Extent() const;

  Standard_EXPORT const NCollection_List<occ::handle<ChFiDS_Stripe>>& FindFromKey(
    const TopoDS_Vertex& V) const;

  const NCollection_List<occ::handle<ChFiDS_Stripe>>& operator()(const TopoDS_Vertex& V) const
  {
    return FindFromKey(V);
  }

  Standard_EXPORT const NCollection_List<occ::handle<ChFiDS_Stripe>>& FindFromIndex(
    const int I) const;

  const NCollection_List<occ::handle<ChFiDS_Stripe>>& operator()(const int I) const
  {
    return FindFromIndex(I);
  }

  const TopoDS_Vertex& FindKey(const int I) const;

  Standard_EXPORT void Clear();

private:
  NCollection_IndexedDataMap<TopoDS_Vertex,
                             NCollection_List<occ::handle<ChFiDS_Stripe>>,
                             TopTools_ShapeMapHasher>
    mymap;
};
// Created on: 1994-01-18
// Created by: Isabelle GRIGNON
// Copyright (c) 1994-1999 Matra Datavision
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

//=================================================================================================

inline int ChFiDS_StripeMap::Extent() const
{
  return mymap.Extent();
}

//=================================================================================================

inline const TopoDS_Vertex& ChFiDS_StripeMap::FindKey(const int I) const
{
  return mymap.FindKey(I);
}


#endif // _ChFiDS_StripeMap_HeaderFile
