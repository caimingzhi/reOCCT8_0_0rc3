#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <gp_Pnt2d.hpp>
#include <BRepClass_Edge.hpp>
#include <BRepClass_FacePassiveClassifier.hpp>
#include <TopoDS_Shape.hpp>
#include <TopOpeBRepBuild_CompositeClassifier.hpp>
#include <TopAbs_State.hpp>
class TopOpeBRepBuild_BlockBuilder;
class TopOpeBRepBuild_Loop;

class TopOpeBRepBuild_WireEdgeClassifier : public TopOpeBRepBuild_CompositeClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_WireEdgeClassifier(const TopoDS_Shape&                 F,
                                                     const TopOpeBRepBuild_BlockBuilder& BB);

  Standard_EXPORT TopAbs_State Compare(const occ::handle<TopOpeBRepBuild_Loop>& L1,
                                       const occ::handle<TopOpeBRepBuild_Loop>& L2) override;

  Standard_EXPORT TopoDS_Shape LoopToShape(const occ::handle<TopOpeBRepBuild_Loop>& L);

  Standard_EXPORT TopAbs_State CompareShapes(const TopoDS_Shape& B1,
                                             const TopoDS_Shape& B2) override;

  Standard_EXPORT TopAbs_State CompareElementToShape(const TopoDS_Shape& E,
                                                     const TopoDS_Shape& B) override;

  Standard_EXPORT void ResetShape(const TopoDS_Shape& B) override;

  Standard_EXPORT void ResetElement(const TopoDS_Shape& E) override;

  Standard_EXPORT bool CompareElement(const TopoDS_Shape& E) override;

  Standard_EXPORT TopAbs_State State() override;

private:
  bool                            myFirstCompare;
  gp_Pnt2d                        myPoint2d;
  BRepClass_Edge                  myBCEdge;
  BRepClass_FacePassiveClassifier myFPC;
  TopoDS_Shape                    myShape;
};
