#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Boolean.hpp>
#include <BRepClass3d_SolidExplorer.hpp>
#include <BRepClass3d_SClassifier.hpp>
class TopoDS_Shape;
class gp_Pnt;

class BRepClass3d_SolidClassifier : public BRepClass3d_SClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass3d_SolidClassifier();

  Standard_EXPORT void Load(const TopoDS_Shape& S);

  Standard_EXPORT BRepClass3d_SolidClassifier(const TopoDS_Shape& S);

  Standard_EXPORT BRepClass3d_SolidClassifier(const TopoDS_Shape& S,
                                              const gp_Pnt&       P,
                                              const double        Tol);

  Standard_EXPORT void Perform(const gp_Pnt& P, const double Tol);

  Standard_EXPORT void PerformInfinitePoint(const double Tol);

  Standard_EXPORT void Destroy();

  ~BRepClass3d_SolidClassifier() { Destroy(); }

private:
  bool                      aSolidLoaded;
  BRepClass3d_SolidExplorer explorer;
  bool                      isaholeinspace;
};
