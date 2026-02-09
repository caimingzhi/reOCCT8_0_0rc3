#pragma once

#include <BRepClass3d_Intersector3d.hpp>
#include <Standard.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Face.hpp>
#include <gp_Lin.hpp>

class Standard_DomainError;
class BRepClass3d_Intersector3d;
class gp_Lin;
class TopoDS_Face;

class BRepClass3d_SolidPassiveClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass3d_SolidPassiveClassifier();

  Standard_EXPORT void Reset(const gp_Lin& L, const double P, const double Tol);

  Standard_EXPORT void Compare(const TopoDS_Face& F, const TopAbs_Orientation Or);

  double Parameter() const { return myParam; }

  bool HasIntersection() const { return hasIntersect; }

  BRepClass3d_Intersector3d& Intersector() { return myIntersector; }

  TopAbs_State State() const { return myState; }

private:
  bool                      isSet;
  TopoDS_Face               myFace;
  gp_Lin                    myLin;
  double                    myParam;
  double                    myTolerance;
  TopAbs_State              myState;
  bool                      hasIntersect;
  BRepClass3d_Intersector3d myIntersector;
};
