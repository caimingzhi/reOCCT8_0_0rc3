#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>
class BRepClass3d_SolidExplorer;
class gp_Pnt;

//! Provides an algorithm to classify a point in a solid.
class BRepClass3d_SClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT BRepClass3d_SClassifier();

  //! Constructor to classify the point P with the
  //! tolerance Tol on the solid S.
  Standard_EXPORT BRepClass3d_SClassifier(BRepClass3d_SolidExplorer& S,
                                          const gp_Pnt&              P,
                                          const double               Tol);

  //! Classify the point P with the
  //! tolerance Tol on the solid S.
  Standard_EXPORT void Perform(BRepClass3d_SolidExplorer& S, const gp_Pnt& P, const double Tol);

  //! Classify an infinite point with the
  //! tolerance Tol on the solid S.
  Standard_EXPORT void PerformInfinitePoint(BRepClass3d_SolidExplorer& S, const double Tol);

  //! Returns True if the classification has been
  //! computed by rejection.
  //! The State is then OUT.
  Standard_EXPORT bool Rejected() const;

  //! Returns the result of the classification.
  Standard_EXPORT TopAbs_State State() const;

  //! Returns True when the point is a point of a face.
  Standard_EXPORT bool IsOnAFace() const;

  //! Returns the face used to determine the
  //! classification. When the state is ON, this is the
  //! face containing the point.
  //!
  //! When Rejected() returns True, Face() has no signification.
  Standard_EXPORT TopoDS_Face Face() const;

protected:
  Standard_EXPORT void ForceIn();

  Standard_EXPORT void ForceOut();

private:
  TopoDS_Face myFace;

  //! This variable stores information about algorithm internal state.
  //! Type of this variable differs from TopAbs_State since it contains
  //! additional information about error status.
  //! 1 - Error inside of the algorithm.
  //! 2 - ON.
  //! 3 - IN.
  //! 4 - OUT.
  int myState;
};

