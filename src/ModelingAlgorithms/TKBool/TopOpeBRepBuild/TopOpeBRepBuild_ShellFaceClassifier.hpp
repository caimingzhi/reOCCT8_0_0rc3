#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <TopOpeBRepTool_SolidClassifier.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopOpeBRepBuild_CompositeClassifier.hpp>
#include <TopAbs_State.hpp>
class TopOpeBRepBuild_BlockBuilder;

class TopOpeBRepBuild_ShellFaceClassifier : public TopOpeBRepBuild_CompositeClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_ShellFaceClassifier(const TopOpeBRepBuild_BlockBuilder& BB);

  Standard_EXPORT void Clear();

  Standard_EXPORT TopAbs_State CompareShapes(const TopoDS_Shape& B1,
                                             const TopoDS_Shape& B2) override;

  Standard_EXPORT TopAbs_State CompareElementToShape(const TopoDS_Shape& F,
                                                     const TopoDS_Shape& S) override;

  Standard_EXPORT void ResetShape(const TopoDS_Shape& S) override;

  Standard_EXPORT void ResetElement(const TopoDS_Shape& F) override;

  Standard_EXPORT bool CompareElement(const TopoDS_Shape& F) override;

  Standard_EXPORT TopAbs_State State() override;

private:
  bool                                                                     myFirstCompare;
  gp_Pnt                                                                   myPoint3d;
  TopoDS_Shell                                                             myShell;
  BRep_Builder                                                             myBuilder;
  TopOpeBRepTool_SolidClassifier                                           mySolidClassifier;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myFaceShellMap;
  TopoDS_Shape                                                             myShape;
};
