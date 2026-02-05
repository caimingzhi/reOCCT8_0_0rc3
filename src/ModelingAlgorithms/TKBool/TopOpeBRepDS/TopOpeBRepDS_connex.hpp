#pragma once

#include <TopOpeBRepDS_define.hpp>

Standard_EXPORT const NCollection_List<TopoDS_Shape>& FDSCNX_EdgeConnexityShapeIndex(
  const TopoDS_Shape&                             E,
  const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
  const int                                       SI);
Standard_EXPORT const NCollection_List<TopoDS_Shape>& FDSCNX_EdgeConnexitySameShape(
  const TopoDS_Shape&                             E,
  const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);
Standard_EXPORT void FDSCNX_Prepare(const TopoDS_Shape&                             S1,
                                    const TopoDS_Shape&                             S2,
                                    const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);
Standard_EXPORT bool FDSCNX_HasConnexFace(const TopoDS_Shape&                             S,
                                          const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);
Standard_EXPORT void FDSCNX_FaceEdgeConnexFaces(const TopoDS_Shape&                             F,
                                                const TopoDS_Shape&                             E,
                                                const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                                NCollection_List<TopoDS_Shape>&                 LF);
Standard_EXPORT void FDSCNX_Dump(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);
Standard_EXPORT void FDSCNX_Dump(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS, const int I);
Standard_EXPORT void FDSCNX_DumpIndex(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS,
                                      const int                                       I);
