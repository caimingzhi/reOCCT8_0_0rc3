#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Edge.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopAbs_State.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_ShapeEnum.hpp>
class gp_Pnt;
class gp_Pnt2d;
class TopOpeBRepDS_Transition;

class TopOpeBRep_FaceEdgeIntersector
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_FaceEdgeIntersector();

  Standard_EXPORT void Perform(const TopoDS_Shape& F, const TopoDS_Shape& E);

  Standard_EXPORT bool IsEmpty();

  Standard_EXPORT const TopoDS_Shape& Shape(const int Index) const;

  Standard_EXPORT void ForceTolerance(const double tol);

  Standard_EXPORT double Tolerance() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT void InitPoint();

  Standard_EXPORT bool MorePoint() const;

  Standard_EXPORT void NextPoint();

  Standard_EXPORT gp_Pnt Value() const;

  Standard_EXPORT double Parameter() const;

  Standard_EXPORT void UVPoint(gp_Pnt2d& P) const;

  Standard_EXPORT TopAbs_State State() const;

  Standard_EXPORT TopOpeBRepDS_Transition
    Transition(const int Index, const TopAbs_Orientation FaceOrientation) const;

  Standard_EXPORT bool IsVertex(const TopoDS_Shape& S,
                                const gp_Pnt&       P,
                                const double        Tol,
                                TopoDS_Vertex&      V);

  Standard_EXPORT bool IsVertex(const int I, TopoDS_Vertex& V);

  Standard_EXPORT int Index() const;

private:
  Standard_EXPORT void ResetIntersection();

  Standard_EXPORT void ShapeTolerances(const TopoDS_Shape& S1, const TopoDS_Shape& S2);

  Standard_EXPORT double ToleranceMax(const TopoDS_Shape& S, const TopAbs_ShapeEnum T) const;

  TopoDS_Face                                             myFace;
  TopoDS_Edge                                             myEdge;
  double                                                  myTol;
  bool                                                    myForceTolerance;
  GeomAdaptor_Curve                                       myCurve;
  bool                                                    myIntersectionDone;
  NCollection_Sequence<IntCurveSurface_IntersectionPoint> mySequenceOfPnt;
  NCollection_Sequence<int>                               mySequenceOfState;
  int                                                     myPointIndex;
  int                                                     myNbPoints;
  TopExp_Explorer                                         myVertexExplorer;
  TopoDS_Shape                                            myNullShape;
  TopoDS_Vertex                                           myNullVertex;
};
