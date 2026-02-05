#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopTrans_SurfaceTransition.hpp>
#include <TopoDS_Shape.hpp>
#include <gp_Pnt.hpp>
#include <gp_Dir.hpp>
class TopOpeBRepDS_Interference;

//! a tool computing edge / face complex transition,
//! Interferences of edge reference are given by
//! I = (T on face, G = point or vertex, S = edge)
class TopOpeBRepDS_Edge3dInterferenceTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Edge3dInterferenceTool();

  Standard_EXPORT void InitPointVertex(const int IsVertex, const TopoDS_Shape& VonOO);

  Standard_EXPORT void Init(const TopoDS_Shape&                           Eref,
                            const TopoDS_Shape&                           E,
                            const TopoDS_Shape&                           F,
                            const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void Add(const TopoDS_Shape&                           Eref,
                           const TopoDS_Shape&                           E,
                           const TopoDS_Shape&                           F,
                           const occ::handle<TopOpeBRepDS_Interference>& I);

  Standard_EXPORT void Transition(const occ::handle<TopOpeBRepDS_Interference>& I) const;

private:
  int                        myFaceOriented;
  TopTrans_SurfaceTransition myTool;
  double                     myTole;
  bool                       myrefdef;
  int                        myIsVertex;
  TopoDS_Shape               myVonOO;
  gp_Pnt                     myP3d;
  gp_Dir                     myTgtref;
};
