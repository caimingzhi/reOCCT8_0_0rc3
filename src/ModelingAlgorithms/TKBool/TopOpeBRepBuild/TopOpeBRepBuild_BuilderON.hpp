// Created on: 1993-06-14
// Created by: Jean Yves LEBEY
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

#ifndef _TopOpeBRepBuild_BuilderON_HeaderFile
#define _TopOpeBRepBuild_BuilderON_HeaderFile

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_PBuilder.hpp>
// Created on: 1993-06-17
// Created by: Jean Yves LEBEY
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

#ifndef _TopOpeBRepBuild_PGTopo_HeaderFile
#define _TopOpeBRepBuild_PGTopo_HeaderFile

class TopOpeBRepBuild_GTopo;
typedef TopOpeBRepBuild_GTopo* TopOpeBRepBuild_PGTopo;

#endif // _TopOpeBRepBuild_PGTopo_HeaderFile

#include <TopOpeBRepTool_Plos.hpp>
#include <TopOpeBRepBuild_PWireEdgeSet.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
class TopOpeBRepDS_Interference;

class TopOpeBRepBuild_BuilderON
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_BuilderON();

  Standard_EXPORT TopOpeBRepBuild_BuilderON(const TopOpeBRepBuild_PBuilder&     PB,
                                            const TopoDS_Shape&                 F,
                                            const TopOpeBRepBuild_PGTopo&       PG,
                                            const TopOpeBRepTool_Plos&          PLSclass,
                                            const TopOpeBRepBuild_PWireEdgeSet& PWES);

  Standard_EXPORT void Perform(const TopOpeBRepBuild_PBuilder&     PB,
                               const TopoDS_Shape&                 F,
                               const TopOpeBRepBuild_PGTopo&       PG,
                               const TopOpeBRepTool_Plos&          PLSclass,
                               const TopOpeBRepBuild_PWireEdgeSet& PWES);

  Standard_EXPORT bool GFillONCheckI(const occ::handle<TopOpeBRepDS_Interference>& I) const;

  Standard_EXPORT void GFillONPartsWES1(const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void GFillONPartsWES2(const occ::handle<TopOpeBRepDS_Interference>& I,
                                        const TopoDS_Shape&                           EspON);

  Standard_EXPORT void Perform2d(const TopOpeBRepBuild_PBuilder&     PB,
                                 const TopoDS_Shape&                 F,
                                 const TopOpeBRepBuild_PGTopo&       PG,
                                 const TopOpeBRepTool_Plos&          PLSclass,
                                 const TopOpeBRepBuild_PWireEdgeSet& PWES);

  Standard_EXPORT void GFillONParts2dWES2(const occ::handle<TopOpeBRepDS_Interference>& I,
                                          const TopoDS_Shape&                           EspON);

private:
  TopOpeBRepBuild_PBuilder                                 myPB;
  TopOpeBRepBuild_PGTopo                                   myPG;
  TopOpeBRepTool_Plos                                      myPLSclass;
  TopOpeBRepBuild_PWireEdgeSet                             myPWES;
  TopoDS_Shape                                             myFace;
  NCollection_List<occ::handle<TopOpeBRepDS_Interference>> myFEI;
};

#endif // _TopOpeBRepBuild_BuilderON_HeaderFile
