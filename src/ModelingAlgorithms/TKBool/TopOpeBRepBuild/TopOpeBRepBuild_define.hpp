// Created on: 1997-11-14
// Created by: Jean Yves LEBEY
// Copyright (c) 1997-1999 Matra Datavision
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

#ifndef _TopOpeBRepBuild_define_HeaderFile
#define _TopOpeBRepBuild_define_HeaderFile

#include <TopOpeBRepDS_define.hpp>

#include <TopOpeBRepBuild_PWireEdgeSet.hpp>
#include <TopOpeBRepBuild_WireEdgeSet.hpp>
#include <TopOpeBRepBuild_ShellFaceSet.hpp>
#include <TopOpeBRepBuild_GTopo.hpp>
#include <TopOpeBRepBuild_PaveClassifier.hpp>
#include <TopOpeBRepBuild_PaveSet.hpp>
#include <TopOpeBRepBuild_Pave.hpp>
#include <TopOpeBRepBuild_SolidBuilder.hpp>
#include <TopOpeBRepBuild_FaceBuilder.hpp>
#include <TopOpeBRepBuild_EdgeBuilder.hpp>
#include <TopOpeBRepBuild_Builder.hpp>
#include <TopOpeBRepBuild_PBuilder.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_ShapeListOfShape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopOpeBRepBuild_HBuilder.hpp>

#define MTBpwes TopOpeBRepBuild_PWireEdgeSet
#define MTBwes TopOpeBRepBuild_WireEdgeSet
#define MTBsfs TopOpeBRepBuild_ShellFaceSet
#define MTBgt TopOpeBRepBuild_GTopo
#define MTBpvc TopOpeBRepBuild_PaveClassifier
#define MTBpvs TopOpeBRepBuild_PaveSet
#define MTBhpv occ::handle<TopOpeBRepBuild_Pave>
#define MTBpv TopOpeBRepBuild_Pave
#define MTBsb TopOpeBRepBuild_SolidBuilder
#define MTBfb TopOpeBRepBuild_FaceBuilder
#define MTBeb TopOpeBRepBuild_EdgeBuilder
#define MTBbON TopOpeBRepBuild_BuilderON
#define MTBb TopOpeBRepBuild_Builder
#define MTBpb TopOpeBRepBuild_PBuilder
#define MTBdmiodmosloslos                                                                          \
  NCollection_DataMap<TopoDS_Shape,                                                                \
                      NCollection_List<TopOpeBRepBuild_ShapeListOfShape>,                          \
                      TopTools_ShapeMapHasher>::Iterator
#define MTBdmosloslos                                                                              \
  NCollection_DataMap<TopoDS_Shape,                                                                \
                      NCollection_List<TopOpeBRepBuild_ShapeListOfShape>,                          \
                      TopTools_ShapeMapHasher>
#define MTBlioloslos NCollection_List<TopOpeBRepBuild_ShapeListOfShape>::Iterator
#define MTBloslos NCollection_List<TopOpeBRepBuild_ShapeListOfShape>
#define MTBslos TopOpeBRepBuild_ShapeListOfShape
#define MTBhb occ::handle<TopOpeBRepBuild_HBuilder>

#endif
