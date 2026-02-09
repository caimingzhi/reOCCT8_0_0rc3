#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Lin2d.hpp>
#include <TopTrans_CurveTransition.hpp>
#include <Geom2dHatch_Intersector.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>
#include <TopAbs_Orientation.hpp>
class Standard_DomainError;
class Geom2dAdaptor_Curve;
class Geom2dHatch_Intersector;
class gp_Lin2d;

class Geom2dHatch_FClass2dOfClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dHatch_FClass2dOfClassifier();

  Standard_EXPORT void Reset(const gp_Lin2d& L, const double P, const double Tol);

  Standard_EXPORT void Compare(const Geom2dAdaptor_Curve& E, const TopAbs_Orientation Or);

  double Parameter() const;

  Geom2dHatch_Intersector& Intersector();

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
  Geom2dHatch_Intersector  myIntersector;
  int                      myClosest;
  TopAbs_State             myState;
  bool                     myIsHeadOrEnd;
};

#define TheEdge Geom2dAdaptor_Curve
#define TheEdge_hxx <Geom2dAdaptor_Curve.hpp>
#define TheIntersector Geom2dHatch_Intersector
#define TheIntersector_hxx <Geom2dHatch_Intersector.hpp>
#define TopClass_Classifier2d Geom2dHatch_FClass2dOfClassifier
#define TopClass_Classifier2d_hxx <Geom2dHatch_FClass2dOfClassifier.hpp>

#include <TopClass_Classifier2d_1.hpp>

#undef TheEdge
#undef TheEdge_hxx
#undef TheIntersector
#undef TheIntersector_hxx
#undef TopClass_Classifier2d
#undef TopClass_Classifier2d_hxx
