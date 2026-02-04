#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_LoopClassifier.hpp>
#include <TopAbs_State.hpp>
class TopOpeBRepBuild_BlockBuilder;
class TopOpeBRepBuild_Loop;
class TopoDS_Shape;

//! classify composite Loops, i.e, loops that can be either a Shape, or
//! a block of Elements.
class TopOpeBRepBuild_CompositeClassifier : public TopOpeBRepBuild_LoopClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopAbs_State Compare(const occ::handle<TopOpeBRepBuild_Loop>& L1,
                                       const occ::handle<TopOpeBRepBuild_Loop>& L2) override;

  //! classify shape <B1> with shape <B2>
  Standard_EXPORT virtual TopAbs_State CompareShapes(const TopoDS_Shape& B1,
                                                     const TopoDS_Shape& B2) = 0;

  //! classify element <E> with shape <B>
  Standard_EXPORT virtual TopAbs_State CompareElementToShape(const TopoDS_Shape& E,
                                                             const TopoDS_Shape& B) = 0;

  //! prepare classification involving shape <B>
  //! calls ResetElement on first element of <B>
  Standard_EXPORT virtual void ResetShape(const TopoDS_Shape& B) = 0;

  //! prepare classification involving element <E>.
  Standard_EXPORT virtual void ResetElement(const TopoDS_Shape& E) = 0;

  //! Add element <E> in the set of elements used in classification.
  //! Returns FALSE if the element <E> has been already added to the set of elements,
  //! otherwise returns TRUE.
  Standard_EXPORT virtual bool CompareElement(const TopoDS_Shape& E) = 0;

  //! Returns state of classification of 2D point, defined by
  //! ResetElement, with the current set of elements, defined by Compare.
  Standard_EXPORT virtual TopAbs_State State() = 0;

protected:
  Standard_EXPORT TopOpeBRepBuild_CompositeClassifier(const TopOpeBRepBuild_BlockBuilder& BB);

  void* myBlockBuilder;
};

