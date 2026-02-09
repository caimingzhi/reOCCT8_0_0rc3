#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepClass_FaceClassifier.hpp>
#include <TopAbs_State.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
class TopOpeBRep_VPointInter;
class TopOpeBRep_PointClassifier;

class TopOpeBRep_VPointInterClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_VPointInterClassifier();

  Standard_EXPORT TopAbs_State VPointPosition(const TopoDS_Shape&         F,
                                              TopOpeBRep_VPointInter&     VP,
                                              const int                   ShapeIndex,
                                              TopOpeBRep_PointClassifier& PC,
                                              const bool                  AssumeINON,
                                              const double                Tol);

  Standard_EXPORT const TopoDS_Shape& Edge() const;

  Standard_EXPORT double EdgeParameter() const;

private:
  BRepClass_FaceClassifier mySlowFaceClassifier;
  TopAbs_State             myState;
  TopoDS_Shape             myNullShape;
};
