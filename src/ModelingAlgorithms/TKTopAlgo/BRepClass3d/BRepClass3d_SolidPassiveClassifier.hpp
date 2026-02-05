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

  //! Creates an undefined classifier.
  Standard_EXPORT BRepClass3d_SolidPassiveClassifier();

  //! Starts a classification process. The point to
  //! classify is the origin of the line <L>. <P> is
  //! the original length of the segment on <L> used to
  //! compute intersections. <Tol> is the tolerance
  //! attached to the intersections.
  Standard_EXPORT void Reset(const gp_Lin& L, const double P, const double Tol);

  //! Updates the classification process with the face
  //! <F> from the boundary.
  Standard_EXPORT void Compare(const TopoDS_Face& F, const TopAbs_Orientation Or);

  //! Returns the current value of the parameter.
  double Parameter() const { return myParam; }

  //! Returns True if an intersection is computed.
  bool HasIntersection() const { return hasIntersect; }

  //! Returns the intersecting algorithm.
  BRepClass3d_Intersector3d& Intersector() { return myIntersector; }

  //! Returns the current state of the point.
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
