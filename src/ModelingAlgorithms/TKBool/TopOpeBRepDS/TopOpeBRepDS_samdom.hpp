#pragma once


#include <TopOpeBRepDS_define.hpp>

Standard_EXPORT void FDSSDM_prepare(const occ::handle<TopOpeBRepDS_HDataStructure>&);
Standard_EXPORT void FDSSDM_makes1s2(const TopoDS_Shape&             S,
                                     NCollection_List<TopoDS_Shape>& L1,
                                     NCollection_List<TopoDS_Shape>& L2);
Standard_EXPORT void FDSSDM_s1s2makesordor(const NCollection_List<TopoDS_Shape>& L1,
                                           const NCollection_List<TopoDS_Shape>& L2,
                                           const TopoDS_Shape&                   S,
                                           NCollection_List<TopoDS_Shape>&       LSO,
                                           NCollection_List<TopoDS_Shape>&       LDO);
Standard_EXPORT void FDSSDM_s1s2(const TopoDS_Shape&             S,
                                 NCollection_List<TopoDS_Shape>& LS1,
                                 NCollection_List<TopoDS_Shape>& LS2);
Standard_EXPORT void FDSSDM_sordor(const TopoDS_Shape&             S,
                                   NCollection_List<TopoDS_Shape>& LSO,
                                   NCollection_List<TopoDS_Shape>& LDO);
Standard_EXPORT bool FDSSDM_contains(const TopoDS_Shape&                   S,
                                     const NCollection_List<TopoDS_Shape>& L);
Standard_EXPORT void FDSSDM_copylist(const NCollection_List<TopoDS_Shape>& Lin,
                                     const int                             I1,
                                     const int                             I2,
                                     NCollection_List<TopoDS_Shape>&       Lou);
Standard_EXPORT void FDSSDM_copylist(const NCollection_List<TopoDS_Shape>& Lin,
                                     NCollection_List<TopoDS_Shape>&       Lou);

