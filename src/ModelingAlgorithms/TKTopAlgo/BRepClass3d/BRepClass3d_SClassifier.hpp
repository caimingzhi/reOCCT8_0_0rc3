#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <Standard_Integer.hpp>
#include <TopAbs_State.hpp>
class BRepClass3d_SolidExplorer;
class gp_Pnt;

class BRepClass3d_SClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass3d_SClassifier();

  Standard_EXPORT BRepClass3d_SClassifier(BRepClass3d_SolidExplorer& S,
                                          const gp_Pnt&              P,
                                          const double               Tol);

  Standard_EXPORT void Perform(BRepClass3d_SolidExplorer& S, const gp_Pnt& P, const double Tol);

  Standard_EXPORT void PerformInfinitePoint(BRepClass3d_SolidExplorer& S, const double Tol);

  Standard_EXPORT bool Rejected() const;

  Standard_EXPORT TopAbs_State State() const;

  Standard_EXPORT bool IsOnAFace() const;

  Standard_EXPORT TopoDS_Face Face() const;

protected:
  Standard_EXPORT void ForceIn();

  Standard_EXPORT void ForceOut();

private:
  TopoDS_Face myFace;

  int myState;
};
