#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopOpeBRepDS_ListOfShapeOn1State.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopOpeBRepDS_HDataStructure;
class TopoDS_Edge;
class TopoDS_Shape;

class TopOpeBRepDS_TOOL
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static int EShareG(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                     const TopoDS_Edge&                              E,
                                     NCollection_List<TopoDS_Shape>&                 lEsd);

  Standard_EXPORT static bool ShareG(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                     const int                                       is1,
                                     const int                                       is2);

  Standard_EXPORT static bool GetEsd(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                     const TopoDS_Shape&                             S,
                                     const int                                       ie,
                                     int&                                            iesd);

  Standard_EXPORT static bool ShareSplitON(
    const occ::handle<TopOpeBRepDS_HDataStructure>&     HDS,
    const NCollection_DataMap<TopoDS_Shape,
                              TopOpeBRepDS_ListOfShapeOn1State,
                              TopTools_ShapeMapHasher>& MspON,
    const int                                           i1,
    const int                                           i2,
    TopoDS_Shape&                                       spON);

  Standard_EXPORT static bool GetConfig(const occ::handle<TopOpeBRepDS_HDataStructure>&     HDS,
                                        const NCollection_DataMap<TopoDS_Shape,
                                                                  TopOpeBRepDS_ListOfShapeOn1State,
                                                                  TopTools_ShapeMapHasher>& MEspON,
                                        const int                                           ie,
                                        const int                                           iesd,
                                        int&                                                conf);
};

