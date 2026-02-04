#pragma once


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

