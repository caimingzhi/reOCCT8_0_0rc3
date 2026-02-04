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

  //! compute position of VPoint <VP> regarding with face <F>.
  //! <ShapeIndex> (= 1,2) indicates which (u,v) point of <VP> is used.
  //! when state is ON, set VP.EdgeON() with the edge containing <VP>
  //! and associated parameter.
  //! returns state of VP on ShapeIndex.
  Standard_EXPORT TopAbs_State VPointPosition(const TopoDS_Shape&         F,
                                              TopOpeBRep_VPointInter&     VP,
                                              const int                   ShapeIndex,
                                              TopOpeBRep_PointClassifier& PC,
                                              const bool                  AssumeINON,
                                              const double                Tol);

  //! returns the edge containing the VPoint <VP> used in the
  //! last VPointPosition() call. Edge is defined if the state previously
  //! computed is ON, else Edge is a null shape.
  Standard_EXPORT const TopoDS_Shape& Edge() const;

  //! returns the parameter of the VPoint <VP> on Edge()
  Standard_EXPORT double EdgeParameter() const;

private:
  BRepClass_FaceClassifier mySlowFaceClassifier;
  TopAbs_State             myState;
  TopoDS_Shape             myNullShape;
};

