#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopOpeBRepTool_ShapeExplorer.hpp>
#include <TopOpeBRep_ShapeScanner.hpp>
#include <TopOpeBRep_EdgesIntersector.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
class TopOpeBRepTool_HBoxTool;

class TopOpeBRep_ShapeIntersector2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_ShapeIntersector2d();

  Standard_EXPORT void InitIntersection(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT const TopoDS_Shape& Shape(const int Index) const;

  Standard_EXPORT bool MoreIntersection() const;

  Standard_EXPORT void NextIntersection();

  Standard_EXPORT TopOpeBRep_EdgesIntersector& ChangeEdgesIntersector();

  Standard_EXPORT const TopoDS_Shape& CurrentGeomShape(const int Index) const;

  Standard_EXPORT void DumpCurrent(const int K) const;

  Standard_EXPORT int Index(const int K) const;

private:
  Standard_EXPORT void Reset();

  Standard_EXPORT void Init(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT void SetIntersectionDone();

  Standard_EXPORT void InitFFIntersection();

  Standard_EXPORT void FindFFIntersection();

  Standard_EXPORT bool MoreFFCouple() const;

  Standard_EXPORT void NextFFCouple();

  Standard_EXPORT void InitEEFFIntersection();

  Standard_EXPORT void FindEEFFIntersection();

  Standard_EXPORT bool MoreEEFFCouple() const;

  Standard_EXPORT void NextEEFFCouple();

  TopoDS_Shape                         myShape1;
  TopoDS_Shape                         myShape2;
  occ::handle<TopOpeBRepTool_HBoxTool> myHBoxTool;
  TopOpeBRepTool_ShapeExplorer         myFaceExplorer;
  TopOpeBRep_ShapeScanner              myFaceScanner;
  TopOpeBRepTool_ShapeExplorer         myEdgeExplorer;
  TopOpeBRep_ShapeScanner              myEdgeScanner;
  TopOpeBRep_EdgesIntersector          myEEIntersector;
  bool                                 myIntersectionDone;
  bool                                 myFFDone;
  bool                                 myEEFFDone;
  bool                                 myFFInit;
  bool                                 myEEFFInit;
};
