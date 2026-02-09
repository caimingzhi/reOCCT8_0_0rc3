#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Interference.hpp>
#include <NCollection_List.hpp>
#include <NCollection_DataMap.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Transient.hpp>
class TopOpeBRepDS_HDataStructure;
class TopOpeBRepDS_Interference;
class TopOpeBRepDS_Curve;
class TopoDS_Shape;

class TopOpeBRepDS_GapTool : public Standard_Transient
{

public:
  Standard_EXPORT TopOpeBRepDS_GapTool();

  Standard_EXPORT TopOpeBRepDS_GapTool(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT void Init(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& Interferences(
    const int IndexPoint) const;

  Standard_EXPORT const NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& SameInterferences(
    const occ::handle<TopOpeBRepDS_Interference>& I) const;

  Standard_EXPORT NCollection_List<occ::handle<TopOpeBRepDS_Interference>>& ChangeSameInterferences(
    const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT bool Curve(const occ::handle<TopOpeBRepDS_Interference>& I,
                             TopOpeBRepDS_Curve&                           C) const;

  Standard_EXPORT bool EdgeSupport(const occ::handle<TopOpeBRepDS_Interference>& I,
                                   TopoDS_Shape&                                 E) const;

  Standard_EXPORT bool FacesSupport(const occ::handle<TopOpeBRepDS_Interference>& I,
                                    TopoDS_Shape&                                 F1,
                                    TopoDS_Shape&                                 F2) const;

  Standard_EXPORT bool ParameterOnEdge(const occ::handle<TopOpeBRepDS_Interference>& I,
                                       const TopoDS_Shape&                           E,
                                       double&                                       U) const;

  Standard_EXPORT void SetPoint(const occ::handle<TopOpeBRepDS_Interference>& I,
                                const int                                     IndexPoint);

  Standard_EXPORT void SetParameterOnEdge(const occ::handle<TopOpeBRepDS_Interference>& I,
                                          const TopoDS_Shape&                           E,
                                          const double                                  U);

  DEFINE_STANDARD_RTTIEXT(TopOpeBRepDS_GapTool, Standard_Transient)

private:
  occ::handle<TopOpeBRepDS_HDataStructure>                                           myHDS;
  NCollection_DataMap<int, NCollection_List<occ::handle<TopOpeBRepDS_Interference>>> myGToI;
  NCollection_DataMap<occ::handle<TopOpeBRepDS_Interference>, TopoDS_Shape>          myInterToShape;
};
