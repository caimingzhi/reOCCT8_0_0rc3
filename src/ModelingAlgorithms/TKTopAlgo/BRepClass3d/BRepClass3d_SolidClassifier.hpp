#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Boolean.hpp>
#include <BRepClass3d_SolidExplorer.hpp>
#include <BRepClass3d_SClassifier.hpp>
class TopoDS_Shape;
class gp_Pnt;

//! Provides an algorithm to classify a point in a solid.
class BRepClass3d_SolidClassifier : public BRepClass3d_SClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  //! empty constructor
  Standard_EXPORT BRepClass3d_SolidClassifier();

  Standard_EXPORT void Load(const TopoDS_Shape& S);

  //! Constructor from a Shape.
  Standard_EXPORT BRepClass3d_SolidClassifier(const TopoDS_Shape& S);

  //! Constructor to classify the point P with the
  //! tolerance Tol on the solid S.
  Standard_EXPORT BRepClass3d_SolidClassifier(const TopoDS_Shape& S,
                                              const gp_Pnt&       P,
                                              const double        Tol);

  //! Classify the point P with the
  //! tolerance Tol on the solid S.
  Standard_EXPORT void Perform(const gp_Pnt& P, const double Tol);

  //! Classify an infinite point with the
  //! tolerance Tol on the solid S.
  //! Useful for compute the orientation of a solid.
  Standard_EXPORT void PerformInfinitePoint(const double Tol);

  Standard_EXPORT void Destroy();

  ~BRepClass3d_SolidClassifier() { Destroy(); }

private:
  bool                      aSolidLoaded;
  BRepClass3d_SolidExplorer explorer;
  bool                      isaholeinspace;
};
