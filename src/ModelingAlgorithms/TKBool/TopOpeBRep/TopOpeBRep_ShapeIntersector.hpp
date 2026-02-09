#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepTool_ShapeExplorer.hpp>
#include <TopOpeBRep_ShapeScanner.hpp>
#include <TopOpeBRep_FacesIntersector.hpp>
#include <TopOpeBRep_EdgesIntersector.hpp>
#include <TopOpeBRep_FaceEdgeIntersector.hpp>
#include <TopoDS_Face.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopOpeBRepTool_HBoxTool;

class TopOpeBRep_ShapeIntersector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_ShapeIntersector();

  Standard_EXPORT void InitIntersection(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT void InitIntersection(const TopoDS_Shape& S1,
                                        const TopoDS_Shape& S2,
                                        const TopoDS_Face&  F1,
                                        const TopoDS_Face&  F2);

  Standard_EXPORT const TopoDS_Shape& Shape(const int Index) const;

  Standard_EXPORT bool MoreIntersection() const;

  Standard_EXPORT void NextIntersection();

  Standard_EXPORT TopOpeBRep_FacesIntersector& ChangeFacesIntersector();

  Standard_EXPORT TopOpeBRep_EdgesIntersector& ChangeEdgesIntersector();

  Standard_EXPORT TopOpeBRep_FaceEdgeIntersector& ChangeFaceEdgeIntersector();

  Standard_EXPORT const TopoDS_Shape& CurrentGeomShape(const int Index) const;

  Standard_EXPORT void GetTolerances(double& tol1, double& tol2) const;

  Standard_EXPORT void DumpCurrent(const int K) const;

  Standard_EXPORT int Index(const int K) const;

  Standard_EXPORT void RejectedFaces(const TopoDS_Shape&             anObj,
                                     const TopoDS_Shape&             aReference,
                                     NCollection_List<TopoDS_Shape>& aListOfShape);

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

  Standard_EXPORT void InitFEIntersection();

  Standard_EXPORT void FindFEIntersection();

  Standard_EXPORT bool MoreFECouple() const;

  Standard_EXPORT void NextFECouple();

  Standard_EXPORT void InitEFIntersection();

  Standard_EXPORT void FindEFIntersection();

  Standard_EXPORT bool MoreEFCouple() const;

  Standard_EXPORT void NextEFCouple();

  Standard_EXPORT void InitEEIntersection();

  Standard_EXPORT void FindEEIntersection();

  Standard_EXPORT bool MoreEECouple() const;

  Standard_EXPORT void NextEECouple();

  TopoDS_Shape                         myShape1;
  TopoDS_Shape                         myShape2;
  occ::handle<TopOpeBRepTool_HBoxTool> myHBoxTool;
  TopOpeBRepTool_ShapeExplorer         myFaceExplorer;
  TopOpeBRep_ShapeScanner              myFaceScanner;
  TopOpeBRep_FacesIntersector          myFFIntersector;
  bool                                 myFFSameDomain;
  TopOpeBRepTool_ShapeExplorer         myEdgeExplorer;
  TopOpeBRep_ShapeScanner              myEdgeScanner;
  TopOpeBRep_EdgesIntersector          myEEIntersector;
  TopOpeBRep_FaceEdgeIntersector       myFEIntersector;
  TopoDS_Face                          myEEFace1;
  TopoDS_Face                          myEEFace2;
  bool                                 myIntersectionDone;
  double                               myTol1;
  double                               myTol2;
  bool                                 myFFDone;
  bool                                 myEEFFDone;
  bool                                 myEFDone;
  bool                                 myFEDone;
  bool                                 myEEDone;
  bool                                 myFFInit;
  bool                                 myEEFFInit;
  bool                                 myEFInit;
  bool                                 myFEInit;
  bool                                 myEEInit;
};
