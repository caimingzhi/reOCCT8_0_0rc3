#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class TopOpeBRep_FaceEdgeIntersector;
class TopOpeBRepDS_HDataStructure;
class TopOpeBRepDS_Point;
class TopOpeBRepDS_DataStructure;
class TopOpeBRepDS_Interference;

class TopOpeBRep_FaceEdgeFiller
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_FaceEdgeFiller();

  Standard_EXPORT void Insert(const TopoDS_Shape&                             F,
                              const TopoDS_Shape&                             E,
                              TopOpeBRep_FaceEdgeIntersector&                 FEINT,
                              const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

private:
  Standard_EXPORT bool ScanInterfList(
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
    const TopOpeBRepDS_Point&                                           DSP,
    const TopOpeBRepDS_DataStructure&                                   BDS) const;

  Standard_EXPORT bool GetGeometry(
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>::Iterator& IT,
    const TopOpeBRep_FaceEdgeIntersector&                               EI,
    int&                                                                G,
    const TopOpeBRepDS_DataStructure&                                   DS) const;

  Standard_EXPORT int MakeGeometry(TopOpeBRep_FaceEdgeIntersector& EI,
                                   TopOpeBRepDS_DataStructure&     DS) const;

  Standard_EXPORT bool GetGeometry(
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& L,
    const TopOpeBRepDS_Point&                                       DSP,
    int&                                                            G,
    TopOpeBRepDS_DataStructure&                                     DS) const;

  Standard_EXPORT void StoreInterference(
    const occ::handle<TopOpeBRepDS_Interference>&             I,
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI,
    TopOpeBRepDS_DataStructure&                               BDS) const;
};
