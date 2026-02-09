#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>
class TopOpeBRepDS_HDataStructure;
class TopOpeBRepDS_GapTool;
class TopOpeBRepDS_Association;
class TopOpeBRepDS_Interference;
class TopoDS_Shape;
class TopoDS_Face;
class TopoDS_Edge;

class TopOpeBRepDS_GapFiller
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_GapFiller(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT void Perform();

  Standard_EXPORT void FindAssociatedPoints(
    const occ::handle<TopOpeBRepDS_Interference>&             I,
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT bool CheckConnexity(NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT void AddPointsOnShape(
    const TopoDS_Shape&                                       S,
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT void AddPointsOnConnexShape(
    const TopoDS_Shape&                                             F,
    const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT void FilterByFace(const TopoDS_Face&                                        F,
                                    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT void FilterByEdge(const TopoDS_Edge&                                        E,
                                    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT void FilterByIncidentDistance(
    const TopoDS_Face&                                        F,
    const occ::handle<TopOpeBRepDS_Interference>&             I,
    NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& LI);

  Standard_EXPORT bool IsOnFace(const occ::handle<TopOpeBRepDS_Interference>& I,
                                const TopoDS_Face&                            F) const;

  Standard_EXPORT bool IsOnEdge(const occ::handle<TopOpeBRepDS_Interference>& I,
                                const TopoDS_Edge&                            E) const;

  Standard_EXPORT void BuildNewGeometries();

  Standard_EXPORT void ReBuildGeom(const occ::handle<TopOpeBRepDS_Interference>& I1,
                                   NCollection_Map<int>&                         Done);

private:
  occ::handle<TopOpeBRepDS_HDataStructure> myHDS;
  occ::handle<TopOpeBRepDS_GapTool>        myGapTool;
  occ::handle<TopOpeBRepDS_Association>    myAsso;
};
