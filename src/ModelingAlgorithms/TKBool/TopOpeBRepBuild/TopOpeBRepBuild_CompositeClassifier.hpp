#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepBuild_LoopClassifier.hpp>
#include <TopAbs_State.hpp>
class TopOpeBRepBuild_BlockBuilder;
class TopOpeBRepBuild_Loop;
class TopoDS_Shape;

class TopOpeBRepBuild_CompositeClassifier : public TopOpeBRepBuild_LoopClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopAbs_State Compare(const occ::handle<TopOpeBRepBuild_Loop>& L1,
                                       const occ::handle<TopOpeBRepBuild_Loop>& L2) override;

  Standard_EXPORT virtual TopAbs_State CompareShapes(const TopoDS_Shape& B1,
                                                     const TopoDS_Shape& B2) = 0;

  Standard_EXPORT virtual TopAbs_State CompareElementToShape(const TopoDS_Shape& E,
                                                             const TopoDS_Shape& B) = 0;

  Standard_EXPORT virtual void ResetShape(const TopoDS_Shape& B) = 0;

  Standard_EXPORT virtual void ResetElement(const TopoDS_Shape& E) = 0;

  Standard_EXPORT virtual bool CompareElement(const TopoDS_Shape& E) = 0;

  Standard_EXPORT virtual TopAbs_State State() = 0;

protected:
  Standard_EXPORT TopOpeBRepBuild_CompositeClassifier(const TopOpeBRepBuild_BlockBuilder& BB);

  void* myBlockBuilder;
};
