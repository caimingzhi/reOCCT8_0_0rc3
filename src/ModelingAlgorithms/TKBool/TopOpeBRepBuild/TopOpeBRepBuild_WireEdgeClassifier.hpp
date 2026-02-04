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

//! Classify edges and wires.
//! shapes are Wires, Element are Edge.
class TopOpeBRepBuild_WireEdgeClassifier : public TopOpeBRepBuild_CompositeClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a classifier on edge <F>.
  //! Used to compare edges and wires on the edge <F>.
  Standard_EXPORT TopOpeBRepBuild_WireEdgeClassifier(const TopoDS_Shape&                 F,
                                                     const TopOpeBRepBuild_BlockBuilder& BB);

  Standard_EXPORT TopAbs_State Compare(const occ::handle<TopOpeBRepBuild_Loop>& L1,
                                       const occ::handle<TopOpeBRepBuild_Loop>& L2) override;

  Standard_EXPORT TopoDS_Shape LoopToShape(const occ::handle<TopOpeBRepBuild_Loop>& L);

  //! classify wire <B1> with wire <B2>
  Standard_EXPORT TopAbs_State CompareShapes(const TopoDS_Shape& B1,
                                             const TopoDS_Shape& B2) override;

  //! classify edge <E> with wire <B>
  Standard_EXPORT TopAbs_State CompareElementToShape(const TopoDS_Shape& E,
                                                     const TopoDS_Shape& B) override;

  //! prepare classification involving wire <B>
  //! calls ResetElement on first edge of <B>
  Standard_EXPORT void ResetShape(const TopoDS_Shape& B) override;

  //! prepare classification involving edge <E>
  //! define 2D point (later used in Compare()) on first vertex of edge <E>.
  Standard_EXPORT void ResetElement(const TopoDS_Shape& E) override;

  //! Add the edge <E> in the set of edges used in 2D point
  //! classification.
  Standard_EXPORT bool CompareElement(const TopoDS_Shape& E) override;

  //! Returns state of classification of 2D point, defined by
  //! ResetElement, with the current set of edges, defined by Compare.
  Standard_EXPORT TopAbs_State State() override;

private:
  bool                            myFirstCompare;
  gp_Pnt2d                        myPoint2d;
  BRepClass_Edge                  myBCEdge;
  BRepClass_FacePassiveClassifier myFPC;
  TopoDS_Shape                    myShape;
};

