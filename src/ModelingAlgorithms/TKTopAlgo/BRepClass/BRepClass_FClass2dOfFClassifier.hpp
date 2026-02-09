#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopTrans_CurveTransition.hpp>
#include <BRepClass_Intersector.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>
#include <TopAbs_Orientation.hpp>
class Standard_DomainError;
class BRepClass_Edge;
class BRepClass_Intersector;
class gp_Lin2d;

class BRepClass_FClass2dOfFClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass_FClass2dOfFClassifier();

  Standard_EXPORT void Reset(const gp_Lin2d& L, const double P, const double Tol);

  Standard_EXPORT void Compare(const BRepClass_Edge& E, const TopAbs_Orientation Or);

  double Parameter() const;

  BRepClass_Intersector& Intersector();

  int ClosestIntersection() const;

  TopAbs_State State() const;

  bool IsHeadOrEnd() const;

private:
  bool                     myIsSet;
  bool                     myFirstCompare;
  bool                     myFirstTrans;
  gp_Lin2d                 myLin;
  double                   myParam;
  double                   myTolerance;
  TopTrans_CurveTransition myTrans;
  BRepClass_Intersector    myIntersector;
  int                      myClosest;
  TopAbs_State             myState;
  bool                     myIsHeadOrEnd;
};

#define TheEdge BRepClass_Edge
#define TheEdge_hxx <BRepClass_Edge.hpp>
#define TheIntersector BRepClass_Intersector
#define TheIntersector_hxx <BRepClass_Intersector.hpp>
#define TopClass_Classifier2d BRepClass_FClass2dOfFClassifier
#define TopClass_Classifier2d_hxx <BRepClass_FClass2dOfFClassifier.hpp>

#include <TopClass_Classifier2d_1.hpp>

#undef TheEdge
#undef TheEdge_hxx
#undef TheIntersector
#undef TheIntersector_hxx
#undef TopClass_Classifier2d
#undef TopClass_Classifier2d_hxx
