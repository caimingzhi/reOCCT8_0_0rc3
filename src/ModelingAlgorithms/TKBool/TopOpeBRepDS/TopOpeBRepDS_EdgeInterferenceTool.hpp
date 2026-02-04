#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_Orientation.hpp>
#include <Standard_Integer.hpp>
#include <TopTrans_CurveTransition.hpp>
class TopoDS_Shape;
class TopOpeBRepDS_Interference;
class TopOpeBRepDS_Point;

//! a tool computing complex transition on Edge.
class TopOpeBRepDS_EdgeInterferenceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_EdgeInterferenceTool();

  Standard_EXPORT void Init(const TopoDS_Shape& E, const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void Add(const TopoDS_Shape&                           E,
                           const TopoDS_Shape&                           V,
                           const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void Add(const TopoDS_Shape&                           E,
                           const TopOpeBRepDS_Point&                     P,
                           const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void Transition(const occ::handle<TopOpeBRepDS_Interference>& I) const;

private:
  TopAbs_Orientation       myEdgeOrientation;
  int                      myEdgeOriented;
  TopTrans_CurveTransition myTool;
};

