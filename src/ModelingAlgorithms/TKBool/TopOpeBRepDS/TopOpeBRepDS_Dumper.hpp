// Created on: 1994-08-04
// Created by: Jean Yves LEBEY
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

#ifndef _TopOpeBRepDS_Dumper_HeaderFile
#define _TopOpeBRepDS_Dumper_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopOpeBRepDS_HDataStructure;
class TCollection_AsciiString;
class TopoDS_Shape;

class TopOpeBRepDS_Dumper
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Dumper(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT TCollection_AsciiString SDumpRefOri(const TopOpeBRepDS_Kind K, const int I) const;

  Standard_EXPORT TCollection_AsciiString SDumpRefOri(const TopoDS_Shape& S) const;

  Standard_EXPORT TCollection_AsciiString SPrintShape(const int I) const;

  Standard_EXPORT TCollection_AsciiString SPrintShape(const TopoDS_Shape& S) const;

  Standard_EXPORT TCollection_AsciiString
    SPrintShapeRefOri(const TopoDS_Shape& S, const TCollection_AsciiString& B = "") const;

  Standard_EXPORT TCollection_AsciiString
    SPrintShapeRefOri(const NCollection_List<TopoDS_Shape>& L,
                      const TCollection_AsciiString&        B = "") const;

private:
  occ::handle<TopOpeBRepDS_HDataStructure> myHDS;
};

#endif // _TopOpeBRepDS_Dumper_HeaderFile
